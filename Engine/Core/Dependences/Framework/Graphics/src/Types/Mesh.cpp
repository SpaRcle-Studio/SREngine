//
// Created by Nikita on 17.11.2020.
//

#include <Types/Mesh.h>
#include <Memory/MeshAllocator.h>
#include <ECS/Component.h>
#include <ResourceManager/ResourceManager.h>
#include <ResourceManager/IResource.h>

namespace SR_GRAPH_NS::Types {
    Mesh::Mesh(MeshType type, std::string name)
        : IResource(typeid(Mesh).name())
        , m_env(Environment::Get())
        , m_type(type)
        , m_pipeline(Environment::Get()->GetPipeLine())
        , m_material(nullptr)
        , m_geometryName(std::move(name))
    {
        Component::InitComponent<Mesh>();
    }

    Mesh::~Mesh() {
        SetRawMesh(nullptr);
        SetMaterial(nullptr);
    }

    bool Mesh::Destroy() {
        if (IsDestroyed())
            return false;

        if (Debug::GetLevel() >= Debug::Level::High) {
            SR_LOG("Mesh::Destroy() : destroy \"" + m_geometryName + "\"...");
        }

        return IResource::Destroy();
    }

    Mesh *Mesh::Load(const std::string &localPath, MeshType type, uint32_t id) {
        auto &&pMesh = TryLoad(localPath, type, id);

        SRVerifyFalse2(!pMesh, "Mesh not found! Path: " + localPath + "; Id: " + Helper::ToString(id));

        return pMesh;
    }

    Mesh *Mesh::TryLoad(const std::string &localPath, MeshType type, uint32_t id) {
        SR_GLOBAL_LOCK

        const auto &resourceId = Helper::Format("%s-%u|%s", EnumMeshTypeToString(type).c_str(), id, localPath.c_str());

        Mesh *mesh = nullptr;

        if (Mesh *pMesh = ResourceManager::Instance().Find<Mesh>(resourceId)) {
            SRVerifyFalse(!(mesh = dynamic_cast<Mesh *>(pMesh->Copy(nullptr))));
            return mesh;
        }

        auto pRaw = Helper::Types::RawMesh::Load(localPath);

        if (!pRaw) {
            return nullptr;
        }

        if (id >= pRaw->GetMeshesCount()) {
            if (pRaw->GetCountUses() == 0) {
                SR_WARN("Mesh::TryLoad() : count uses is zero! Unresolved situation...\n\tPath: " + localPath +
                        "\n\tId: " + Helper::ToString(id));
                SRAssert(false);
                pRaw->Destroy();
            }
            return nullptr;
        }

        switch (type) {
            case MeshType::Static:
                mesh = Memory::MeshAllocator::Allocate<Mesh3D>();
                break;
            case MeshType::Wireframe:
                mesh = Memory::MeshAllocator::Allocate<DebugWireframeMesh>();
                break;
            case MeshType::Unknown:
            case MeshType::Skinned:
                SRAssert(false);
                return mesh;
        }

        if (mesh) {
            /// id меша нужно устанавливать перед id ресурса, так как когда ставится id ресурса он автоматически регистрируется
            /// и другой поток может его подхватить
            mesh->m_meshId = id;

            mesh->SetRawMesh(pRaw);
            mesh->SetGeometryName(pRaw->GetGeometryName(id));
            mesh->SetMaterial(Material::GetDefault());

            mesh->SetId(resourceId);
        }

        SRAssert(mesh);

        return mesh;
    }

    std::vector<Mesh *> Mesh::Load(const std::string &localPath, MeshType type) {
        std::vector<Mesh *> meshes;

        uint32_t id = 0;
        while (auto &&pMesh = TryLoad(localPath, type, id)) {
            meshes.emplace_back(pMesh);
            ++id;
        }

        if (meshes.empty()) {
            SR_ERROR("Mesh::Load() : failed to load mesh! Path: " + localPath);
        }

        return meshes;
    }

    void Mesh::OnDestroy() {
        Destroy();

        if (m_render) {
            m_render->RemoveMesh(this);
        }
        else if (IsCalculated()) {
            SR_ERROR("Mesh::OnDestroyGameObject() : render is not set! Something went wrong...");
        }
    }

    bool Mesh::IsCanCalculate() const {
        if (!m_render) {
            SR_ERROR("Mesh::IsCanCalculate() : mesh is not register in render!");
            return false;
        }

        if (!m_material) {
            SR_ERROR("Mesh::IsCanCalculate() : mesh have not material!");
            return false;
        }

        return true;
    }

    Math::FVector3 Mesh::GetBarycenter() const {
        auto baryMat = Math::Matrix4x4(m_barycenter, Math::FVector3(), 1.0);
        auto rotateMat = Math::Matrix4x4(0.0, m_rotation.InverseAxis(2).ToQuat(), 1.0);

        return (rotateMat * baryMat).GetTranslate();
    }

    IResource *Mesh::Copy(IResource *destination) const {
        if (IsDestroyed()) {
            SR_ERROR("Mesh::Copy() : mesh already destroyed!");
            return nullptr;
        }

        Mesh *mesh = dynamic_cast<Mesh *>(destination);
        if (!mesh) {
            SR_ERROR("Mesh::Copy() : impossible to copy basic mesh!");
            return nullptr;
        }

        if (Debug::GetLevel() >= Debug::Level::Full)
            SR_LOG("Mesh::Copy() : copy \"" + GetResourceId() + "\" mesh...");

        mesh->m_meshId = m_meshId;

        mesh->SetMaterial(m_material);
        mesh->SetRawMesh(m_rawMesh);

        mesh->m_barycenter = m_barycenter;
        mesh->m_position = m_position;
        mesh->m_rotation = m_rotation;
        mesh->m_scale = m_scale;
        mesh->m_skew = m_skew;

        mesh->m_modelMat = m_modelMat;
        mesh->m_isCalculated.store(m_isCalculated);
        mesh->m_hasErrors.store(false);

        return Helper::IResource::Copy(mesh);
    }

    bool Mesh::FreeVideoMemory() {
        if (m_pipeline == PipeLine::Vulkan) {
            if (m_descriptorSet >= 0 && !m_env->FreeDescriptorSet(&m_descriptorSet)) {
                SR_ERROR("Mesh::FreeVideoMemory() : failed to free descriptor set!");
            }

            if (m_UBO >= 0 && !m_env->FreeUBO(&m_UBO)) {
                SR_ERROR("Mesh::FreeVideoMemory() : failed to free uniform buffer object!");
            }
        }

        m_isCalculated = false;

        return true;
    }

    void Mesh::ReCalcModel() {
        Math::Matrix4x4 modelMat = Math::Matrix4x4::FromTranslate(m_position);

        if (m_pipeline == PipeLine::OpenGL) {
            modelMat *= Math::Matrix4x4::FromScale(m_skew.InverseAxis(0));
            modelMat *= Math::Matrix4x4::FromEulers(m_rotation.InverseAxis(1));
        }
        else {
            modelMat *= Math::Matrix4x4::FromScale(m_skew);
            modelMat *= Math::Matrix4x4::FromEulers(m_rotation);
        }

        modelMat *= Math::Matrix4x4::FromScale(m_inverse ? -m_scale : m_scale);

        m_modelMat = modelMat.ToGLM();
    }

    void Mesh::WaitCalculate() const {
        ret:
        if (!m_render) {
            SRAssert2(false, Helper::Format("Mesh::WaitCalculate() : There is no destination render!"
                                            " The geometry will never be calculated. \nName: %s",
                                            m_geometryName.c_str()).c_str());
            return;
        }

        if (m_isCalculated)
            return;

        goto ret;
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

        if (m_isCalculated)
            Environment::Get()->SetBuildState(false);
    }

    void Mesh::OnMove(const Math::FVector3 &newValue) {
        m_position = newValue;
        ReCalcModel();
    }

    void Mesh::OnRotate(const Math::FVector3 &newValue) {
        m_rotation = newValue;
        ReCalcModel();
    }

    void Mesh::OnScaled(const Math::FVector3 &newValue) {
        m_scale = newValue;
        ReCalcModel();
    }

    void Mesh::OnSkewed(const Math::FVector3 &newValue) {
        m_skew = newValue;
        ReCalcModel();
    }

    void Mesh::OnTransparencyChanged() {
        if (m_render) {
            m_render->ReRegisterMesh(this);
        }
    }

    std::string Mesh::GetResourcePath() const {
        return StringUtils::Substring(GetResourceId(), '|', 1);
    }

    void Mesh::SetRawMesh(Helper::Types::RawMesh *pRaw) {
        if (m_rawMesh && pRaw) {
            SRAssert(false);
            return;
        }

        if (m_rawMesh) {
            RemoveDependency(m_rawMesh);
        }

        if (pRaw) {
            AddDependency(pRaw);
        }

        m_rawMesh = pRaw;
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

    bool Mesh::HaveDefMaterial() const {
        return !(!m_material || m_material != Material::GetDefault());
    }

    void Mesh::OnEnabled() {
        m_env->SetBuildState(false);
        Component::OnEnabled();
    }

    void Mesh::OnDisabled() {
        m_env->SetBuildState(false);
        Component::OnDisabled();
    }

    bool Mesh::CanDraw() const {
        if (!IsActive() || IsDestroyed())
            return false;

        if (m_hasErrors)
            return false;

        return true;
    }
}

