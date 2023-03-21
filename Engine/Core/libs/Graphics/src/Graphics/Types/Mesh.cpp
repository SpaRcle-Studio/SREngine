//
// Created by Nikita on 17.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/ResourceManager/IResource.h>

#include <Graphics/Types/Mesh.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Utils/MeshUtils.h>

namespace SR_GRAPH_NS::Types {
    Mesh::Mesh(MeshType type)
        : m_uboManager(Memory::UBOManager::Instance())
        , m_meshType(type)
        , m_material(nullptr)
    { }

    Mesh::~Mesh() {
        SetMaterial(nullptr);
        SRAssert(m_virtualUBO == SR_ID_INVALID);
    }

    Mesh::Ptr Mesh::Load(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id) {
        if (auto&& pMesh = TryLoad(std::move(path), type, id)) {
            return pMesh;
        }

        SR_ERROR("Mesh::Load() : failed to load mesh!\n\tPath: " + path.ToStringRef() + "\n\tId: " + std::to_string(id));

        return nullptr;
    }

    Mesh::Ptr Mesh::TryLoad(const SR_UTILS_NS::Path& path, MeshType type, uint32_t id) {
        SR_GLOBAL_LOCK

        static auto&& resourceManager = SR_UTILS_NS::ResourceManager::Instance();

        SR_MAYBE_UNUSED SR_HTYPES_NS::SingletonRecursiveLockGuard lock(&resourceManager);

        Mesh::Ptr pMesh = nullptr;
        bool exists = false;

        /// Проверяем существование меша
        SR_HTYPES_NS::RawMesh* pRawMesh = nullptr;
        if ((pRawMesh = SR_HTYPES_NS::RawMesh::Load(path))) {
            exists = id < pRawMesh->GetMeshesCount();
        }
        else {
            return nullptr;
        }

        if (!exists || !(pMesh = CreateMeshByType(type))) {
            pRawMesh->CheckResourceUsage();
            return nullptr;
        }

        if (auto&& pRawMeshHolder = dynamic_cast<SR_HTYPES_NS::IRawMeshHolder*>(pMesh)) {
            pRawMeshHolder->SetRawMesh(pRawMesh);
            pRawMeshHolder->SetMeshId(id);
        }
        else {
            SRHalt("Mesh is not a raw mesh holder! Memory leak...");
            pRawMesh->CheckResourceUsage();
            return nullptr;
        }

        return pMesh;
    }

    std::vector<Mesh::Ptr> Mesh::Load(const SR_UTILS_NS::Path& path, MeshType type) {
        std::vector<Mesh::Ptr> meshes;

        uint32_t id = 0;
        while (auto&& pMesh = TryLoad(path, type, id)) {
            meshes.emplace_back(pMesh);
            ++id;
        }

        if (meshes.empty()) {
            SR_ERROR("Mesh::Load() : failed to load mesh! Path: " + path.ToString());
        }

        return meshes;
    }

    bool Mesh::IsCanCalculate() const {
        return true;
    }

    void Mesh::FreeVideoMemory() {
        if (m_virtualUBO != SR_ID_INVALID && !m_uboManager.FreeUBO(&m_virtualUBO)) {
            SR_ERROR("Mesh::FreeVideoMemory() : failed to free virtual uniform buffer object!");
        }

        IGraphicsResource::FreeVideoMemory();
    }

    bool Mesh::Calculate() {
        m_isCalculated = true;
        /// чтобы в случае перезагрузки обновить все связанные данные
        m_dirtyMaterial = true;
        return true;
    }

    void Mesh::SetMaterial(const SR_UTILS_NS::Path& path) {
        SetMaterial(Material::Load(path));
    }

    void Mesh::SetMaterial(MaterialPtr pMaterial) {
        if (pMaterial == m_material) {
            return;
        }

        m_dirtyMaterial = true;

        if (m_material) {
            m_material->RemoveUsePoint();
        }

        if ((m_material = pMaterial)) {
            m_material->AddUsePoint();
        }

        if (m_isCalculated && m_pipeline) {
            m_pipeline->SetBuildState(false);
        }
    }

    Mesh::ShaderPtr Mesh::GetShader() const {
        return m_material ? m_material->GetShader() : nullptr;
    }

    void Mesh::UseMaterial() {
        m_material->Use();
    }

    void Mesh::BindMesh() const {
        if (auto&& VBO = GetVBO(); VBO != SR_ID_INVALID) {
            m_pipeline->BindVBO(VBO);
        }

        if (auto&& IBO = GetIBO(); IBO != SR_ID_INVALID) {
            m_pipeline->BindIBO(IBO);
        }
    }

    const SR_MATH_NS::Matrix4x4& Mesh::GetModelMatrix() const {
        static SR_MATH_NS::Matrix4x4 matrix4X4 = SR_MATH_NS::Matrix4x4::Identity();
        return matrix4X4;
    }

    void Mesh::UseSamplers() {
        if (!m_material) {
            return;
        }

        m_material->UseSamplers();
    }

    std::string Mesh::GetMeshIdentifier() const {
        static const std::string empty;
        return empty;
    }

    void Mesh::MarkMeshDestroyed() {
        SRAssert(!m_isMeshDestroyed);

        m_isMeshDestroyed = true;

        if (!IsGraphicsResourceRegistered()) {
            delete this;
        }
    }
}

