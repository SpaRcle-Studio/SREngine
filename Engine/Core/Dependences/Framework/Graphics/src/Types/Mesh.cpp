//
// Created by Nikita on 17.11.2020.
//

#include <Types/Mesh.h>
#include <Utils/ECS/Component.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/ResourceManager/IResource.h>

#include <Types/Geometry/Mesh3D.h>
#include <Types/Geometry/DebugWireframeMesh.h>
#include <UI/Sprite2D.h>
#include <Render/RenderContext.h>

namespace SR_GRAPH_NS::Types {
    Mesh::Mesh(MeshType type)
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(Mesh), true /** auto remove */)
        , m_uboManager(Memory::UBOManager::Instance())
        , m_pipeline(Environment::Get())
        , m_type(type)
        , m_material(nullptr)
    {
        Component::InitComponent<Mesh>();
    }

    Mesh::~Mesh() {
        SetMaterial(nullptr);
    }

    bool Mesh::Destroy() {
        if (IsDestroyed()) {
            SRHalt("The mesh already destroyed!");
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Mesh::Destroy() : destroy \"" + m_geometryName + "\"...");
        }

        return IResource::Destroy();
    }

    Mesh *Mesh::Load(SR_UTILS_NS::Path path, MeshType type, uint32_t id) {
        auto &&pMesh = TryLoad(std::move(path), type, id);

        SRVerifyFalse2(!pMesh, "Mesh is not found! Id: " + SR_UTILS_NS::ToString(id));

        return pMesh;
    }

    Mesh *Mesh::TryLoad(SR_UTILS_NS::Path rawPath, MeshType type, uint32_t id) {
        SR_GLOBAL_LOCK

        static auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        auto&& path = rawPath.SelfRemoveSubPath(resourceManager.GetResPathRef());
        auto&& resourceId = SR_UTILS_NS::EnumReflector::ToString(type) + "-" + std::to_string(id) + "|" + path.ToString();

        Mesh *pMesh = nullptr;

        if ((pMesh = resourceManager.Find<Mesh>(resourceId))) {
            SRVerifyFalse(!(pMesh = reinterpret_cast<Mesh *>(pMesh->Copy(nullptr))));
            return pMesh;
        }

        bool exists = false;

        /// Проверяем существование меша
        SR_HTYPES_NS::RawMesh* pRawMesh = nullptr;
        if ((pRawMesh = SR_HTYPES_NS::RawMesh::Load(path))) {
            pRawMesh->AddUsePoint();
            exists = id < pRawMesh->GetMeshesCount();
        }
        else {
            return nullptr;
        }

        if (!exists) {
            pRawMesh->RemoveUsePoint();
            return nullptr;
        }

        switch (type) {
            case MeshType::Static: {
                auto&& pMesh3D = new Types::Mesh3D();
                pMesh3D->m_meshId = id;
                pMesh = pMesh3D;
                break;
            }
            case MeshType::Wireframe: {
                auto &&pWireframe = new Types::DebugWireframeMesh();
                pWireframe->m_meshId = id;
                pMesh = pWireframe;
                break;
            }
            case MeshType::Sprite2D:
                pMesh = new UI::Sprite2D();
                break;
            case MeshType::Unknown:
            case MeshType::Skinned:
            default:
                SRAssert(false);
                pRawMesh->RemoveUsePoint();
                return pMesh;
        }

        if (pMesh) {
            pMesh->SetId(resourceId, false /** auto register */);

            if (!pMesh->Reload()) {
                pRawMesh->RemoveUsePoint();
                delete pMesh;
                return nullptr;
            }

            /// отложенная ручная регистрация
            SR_UTILS_NS::ResourceManager::Instance().RegisterResource(pMesh);
        }

        pRawMesh->RemoveUsePoint();

        return pMesh;
    }

    std::vector<Mesh*> Mesh::Load(SR_UTILS_NS::Path path, MeshType type) {
        std::vector<Mesh*> meshes;

        uint32_t id = 0;
        while (auto &&pMesh = TryLoad(path, type, id)) {
            meshes.emplace_back(pMesh);
            ++id;
        }

        if (meshes.empty()) {
            SR_ERROR("Mesh::Load() : failed to load mesh! Path: " + path.ToString());
        }

        return meshes;
    }

    void Mesh::OnAttached() {
        AddUsePoint();

        GetRenderScene().Do([this](SR_GRAPH_NS::RenderScene *ptr) {
            ptr->Register(this);
        });

        Component::OnAttached();
    }

    void Mesh::OnDestroy() {
        Component::OnDestroy();

        auto&& renderScene = GetRenderScene();

        /// после вызова данная сущность может быть уничтожена
        RemoveUsePoint();

        renderScene->SetDirty();
    }

    bool Mesh::IsCanCalculate() const {
        return true;
    }

    SR_MATH_NS::FVector3 Mesh::GetBarycenter() const {
        //auto baryMat = SR_MATH_NS::Matrix4x4(m_barycenter, SR_MATH_NS::FVector3(), 1.0);
        //auto rotateMat = SR_MATH_NS::Matrix4x4(0.0, m_rotation.InverseAxis(2).ToQuat(), 1.0);

        //return (rotateMat * baryMat).GetTranslate();

        return SR_MATH_NS::FVector3();
    }

    SR_UTILS_NS::IResource *Mesh::Copy(IResource *destination) const {
        if (IsDestroyed()) {
            SR_ERROR("Mesh::Copy() : mesh is already destroyed!");
            return nullptr;
        }

        Mesh *mesh = reinterpret_cast<Mesh *>(destination);
        if (!mesh) {
            SR_ERROR("Mesh::Copy() : impossible to copy basic mesh!");
            return nullptr;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::Full) {
            SR_LOG("Mesh::Copy() : copy \"" + std::string(GetResourceId()) + "\" mesh...");
        }

        /// mesh->SetMaterial(m_material);

        mesh->m_resourcePath = m_resourcePath;

        mesh->m_geometryName = m_geometryName;
        mesh->m_barycenter = m_barycenter;

        mesh->m_isCalculated.store(m_isCalculated);
        mesh->m_hasErrors.store(false);

        return SR_UTILS_NS::IResource::Copy(mesh);
    }

    void Mesh::FreeVideoMemory() {
        if (m_pipeline->GetPipeLine() == PipeLine::Vulkan) {
            if (m_virtualUBO != SR_ID_INVALID && !m_uboManager.FreeUBO(&m_virtualUBO)) {
                SR_ERROR("Mesh::FreeVideoMemory() : failed to free virtual uniform buffer object!");
            }
        }

        m_isCalculated = false;
    }

    bool Mesh::Calculate() {
        m_isCalculated = true;
        return true;
    }

    void Mesh::SetMaterial(Material *material) {
        if (material == m_material) {
            return;
        }

        m_dirtyMaterial = true;

        if (m_material) {
            RemoveDependency(m_material);
        }

        if ((m_material = material)) {
            AddDependency(m_material);
        }

        if (m_isCalculated && m_pipeline) {
            m_pipeline->SetBuildState(false);
        }
    }

    SR_UTILS_NS::Path Mesh::GetResourcePath() const {
        if (m_resourcePath.empty()) {
            m_resourcePath = SR_UTILS_NS::Path(
                    std::move(SR_UTILS_NS::StringUtils::SubstringView(GetResourceId(), '|', 1)),
                    true /** fast */
            );
        }

        return m_resourcePath;
    }

    Shader *Mesh::GetShader() const {
        return m_material ? m_material->GetShader() : nullptr;
    }

    void Mesh::OnResourceUpdated(IResource *pResource, int32_t depth) {
        if (dynamic_cast<Material*>(pResource) == m_material && m_material) {
            m_dirtyMaterial = true;
        }

        IResource::OnResourceUpdated(pResource, depth);
    }

    void Mesh::OnEnable() {
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
        Component::OnEnable();
    }

    void Mesh::OnDisable() {
        if (auto&& renderScene = GetRenderScene()) {
            renderScene->SetDirty();
        }
        Component::OnDisable();
    }

    Mesh::RenderScenePtr Mesh::GetRenderScene() {
        if (!m_renderScene.Valid()) {
            m_renderScene = TryGetScene().Do<RenderScenePtr>([](SR_WORLD_NS::Scene* ptr) {
                return ptr->GetDataStorage().GetValue<RenderScenePtr>();
            }, RenderScenePtr());
        }

        return m_renderScene;
    }

    void Mesh::SetContext(const Mesh::RenderContextPtr &context) {
        if ((m_context = context)) {
            m_pipeline = m_context->GetPipeline();
        }
        else {
            SRHalt("Context is invalid!");
        }
    }

    const SR_MATH_NS::Matrix4x4 &Mesh::GetModelMatrix() const {
        if (auto&& pTransform = GetTransform()) {
            return pTransform->GetMatrix();
        }

        static SR_MATH_NS::Matrix4x4 matrix4X4 = SR_MATH_NS::Matrix4x4::Identity();
        return matrix4X4;
    }

    bool Mesh::ExecuteInEditMode() const {
        return true;
    }

    SR_MATH_NS::FVector3 Mesh::GetTranslation() const {
        if (auto&& pParent = GetParent()) {
            return pParent->GetTransform()->GetTranslation();
        }

        return SR_MATH_NS::FVector3::Zero();
    }
}

