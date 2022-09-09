//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>
#include <Utils/Types/RawMesh.h>
#include <Types/Material.h>
#include <Environment/Environment.h>
#include <Types/Uniforms.h>
#include <Types/Shader.h>
#include <Utils/Types/DataStorage.h>

namespace SR_GTYPES_NS {
    Mesh3D::Mesh3D()
        : IndexedMesh(MeshType::Static)
    {
        /// override component
        Component::InitComponent<Mesh3D>();
    }

    Mesh3D::~Mesh3D() {
        SetRawMesh(nullptr);
    }

    bool Mesh3D::Calculate()  {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (m_isCalculated)
            return true;

        const bool iboOK = m_IBO != SR_ID_INVALID;
        if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
            m_isCalculated = true;
            return true;
        }

        if (!IsCanCalculate()) {
            return false;
        }

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Mesh3D::Calculate() : calculating \"" + m_geometryName + "\"...");
        }

        auto&& vertices = Vertices::CastVertices<Vertices::StaticMeshVertex>(m_rawMesh->GetVertices(m_meshId));

        //for (auto&& index : GetIndices()) {
        //    SR_LOG(vertices[index].ToString());
        //}

        if (!CalculateVBO<Vertices::VertexType::StaticMeshVertex>(vertices))
            return false;

        return IndexedMesh::Calculate();
    }

    SR_UTILS_NS::IResource* Mesh3D::Copy(IResource* destination) const {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        auto* mesh3D = dynamic_cast<Mesh3D *>(destination ? destination : new Mesh3D());
        mesh3D = dynamic_cast<Mesh3D *>(IndexedMesh::Copy(mesh3D));

        mesh3D->SetRawMesh(m_rawMesh);
        mesh3D->m_meshId = m_meshId;

        if (mesh3D->IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            mesh3D->m_VBO = manager.CopyIfExists<Vertices::VertexType::StaticMeshVertex, Memory::MeshMemoryType::VBO>(GetResourceId());
        }

        return mesh3D;
    }

    void Mesh3D::FreeVideoMemory() {
        SR_LOCK_GUARD_INHERIT(SR_UTILS_NS::IResource);

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Mesh3D::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");
        }

        if (!FreeVBO<Vertices::VertexType::StaticMeshVertex>()) {
            SR_ERROR("Mesh3D::FreeVideoMemory() : failed to free VBO!");
        }

        IndexedMesh::FreeVideoMemory();
    }

    void Mesh3D::Draw() {
        if (!IsActive() || IsDestroyed())
            return;

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

        auto&& shader = m_material->GetShader();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = m_uboManager.ReAllocateUBO(m_virtualUBO, shader->GetUBOBlockSize(), shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                m_uboManager.BindUBO(m_virtualUBO);
            }
            else {
                m_pipeline->ResetDescriptorSet();
                m_hasErrors = true;
                return;
            }

            shader->InitUBOBlock();
            shader->Flush();

            m_material->UseSamplers();
        }

        switch (m_uboManager.BindUBO(m_virtualUBO)) {
            case Memory::UBOManager::BindResult::Duplicated:
                shader->InitUBOBlock();
                shader->Flush();
                m_material->UseSamplers();
                SR_FALLTHROUGH;
            case Memory::UBOManager::BindResult::Success:
                m_pipeline->DrawIndices(m_countIndices);
                break;
            case Memory::UBOManager::BindResult::Failed:
            default:
                break;
        }
    }

    SR_HTYPES_NS::Marshal SR_GTYPES_NS::Mesh3D::Save(SR_UTILS_NS::SavableFlags flags) const {
        SR_HTYPES_NS::Marshal marshal = Component::Save(flags);

        marshal.Write(static_cast<int32_t>(m_type));

        /// TODO: use unicode
        marshal.Write(GetResourcePath().ToString());
        marshal.Write(m_meshId);

        marshal.Write(m_material ? m_material->GetResourceId() : "None");

        return marshal;
    }

    SR_UTILS_NS::Component *SR_GTYPES_NS::Mesh3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto &&type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto &&path = marshal.Read<std::string>();
        const auto &&id = marshal.Read<uint32_t>();

        const auto &&material = marshal.Read<std::string>();

        if (id < 0) {
            return nullptr;
        }

        auto &&pMesh = Mesh::Load(path, type, id);

        if (pMesh && material != "None") {
            if (auto&& pMaterial = Types::Material::Load(material)) {
                pMesh->SetMaterial(pMaterial);
            }
            else
                SR_ERROR("Mesh3D::LoadComponent() : failed to load material! Name: " + material);
        }

        return pMesh;
    }

    bool Mesh3D::Unload() {
        SetRawMesh(nullptr);
        return true;
    }

    bool Mesh3D::Load() {
        if (auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(GetResourcePath())) {
            if (m_meshId >= pRawMesh->GetMeshesCount()) {
                if (pRawMesh->GetCountUses() == 0) {
                    SRHalt("Mesh3D::Load() : count uses is zero! Unresolved situation...");
                    pRawMesh->Destroy();
                }
                return false;
            }

            m_countIndices = pRawMesh->GetIndicesCount(m_meshId);
            m_countVertices = pRawMesh->GetVerticesCount(m_meshId);

            SetGeometryName(pRawMesh->GetGeometryName(m_meshId));
            SetRawMesh(pRawMesh);

            return true;
        }

        return false;
    }

    void Mesh3D::SetRawMesh(SR_HTYPES_NS::RawMesh *pRaw) {
        if (m_rawMesh) {
            RemoveDependency(m_rawMesh);
        }

        if (pRaw) {
            AddDependency(pRaw);
        }

        m_rawMesh = pRaw;
    }

    std::vector<uint32_t> Mesh3D::GetIndices() const {
        return m_rawMesh->GetIndices(m_meshId);
    }

    bool Mesh3D::IsCanCalculate() const {
        return m_rawMesh && m_meshId < m_rawMesh->GetMeshesCount() && Mesh::IsCanCalculate();
    }

    bool Mesh3D::Reload() {
        SR_SHADER_LOG("Mesh3D::Reload() : reloading \"" + GetResourceId() + "\" mesh...");

        m_loadState = LoadState::Reloading;

        Unload();

        if (!Load()) {
            return false;
        }

        m_loadState = LoadState::Loaded;

        UpdateResources();

        return true;
    }
}