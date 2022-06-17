//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>
#include <Utils/Types/RawMesh.h>
#include <Types/Material.h>
#include <Environment/Environment.h>
#include <Types/Uniforms.h>
#include <Render/Shader.h>
#include <Render/Render.h>

namespace SR_GTYPES_NS {
    bool Mesh3D::Calculate()  {
        SR_SCOPED_LOCK

        if (m_isCalculated)
            return true;

        const bool iboOK = m_IBO != SR_ID_INVALID;
        if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
            m_isCalculated = true;
            return true;
        }

        if (!IsCanCalculate())
            return false;

        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Mesh3D::Calculate() : calculating \"" + m_geometryName + "\"...");
        }

        auto&& vertices = Vertices::CastVertices<Vertices::StaticMeshVertex>(m_rawMesh->GetVertices(m_meshId));

        if (!CalculateVBO<Vertices::Type::StaticMeshVertex>(vertices))
            return false;

        return IndexedMesh::Calculate();
    }

    SR_UTILS_NS::IResource* Mesh3D::Copy(IResource* destination) const {
        SR_SCOPED_LOCK

        auto* mesh3D = dynamic_cast<Mesh3D *>(destination ? destination : new Mesh3D(m_geometryName));
        mesh3D = dynamic_cast<Mesh3D *>(IndexedMesh::Copy(mesh3D));

        if (mesh3D->IsCalculated()) {
            auto &&manager = Memory::MeshManager::Instance();
            mesh3D->m_VBO = manager.CopyIfExists<Vertices::Type::StaticMeshVertex, Memory::MeshMemoryType::VBO>(GetResourceId());
        }

        return mesh3D;
    }

    bool Mesh3D::FreeVideoMemory() {
        if (SR_UTILS_NS::Debug::Instance().GetLevel() >= SR_UTILS_NS::Debug::Level::High) {
            SR_LOG("Mesh3D::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");
        }

        if (!FreeVBO<Vertices::Type::StaticMeshVertex>())
            return false;

        return IndexedMesh::FreeVideoMemory();
    }

    void Mesh3D::DrawVulkan() {
        if (!IsActive() || IsDestroyed())
            return;

        if ((!m_isCalculated && !Calculate()) || m_hasErrors)
            return;

        auto&& shader = m_material->GetShader();
        auto&& uboManager = Memory::UBOManager::Instance();

        if (m_dirtyMaterial)
        {
            m_dirtyMaterial = false;

            m_virtualUBO = uboManager.ReAllocateUBO(m_virtualUBO, shader->GetUBOBlockSize(), shader->GetSamplersCount());

            if (m_virtualUBO != SR_ID_INVALID) {
                uboManager.BindUBO(m_virtualUBO);
            }
            else
                m_env->ResetDescriptorSet();

            shader->InitUBOBlock();
            shader->Flush();

            m_material->UseSamplers();
        }

        uboManager.BindUBO(m_virtualUBO);

        m_env->DrawIndices(m_countIndices);
    }

    void Mesh3D::DrawOpenGL() {
        if (IsDestroyed() || (!m_isCalculated && !Calculate()))
            return;
    }

    SR_HTYPES_NS::Marshal SR_GTYPES_NS::Mesh3D::Save(SR_UTILS_NS::SavableFlags flags) const {
        SR_HTYPES_NS::Marshal marshal = Component::Save(flags);

        marshal.Write(static_cast<int32_t>(m_type));

        /// TODO: use unicode
        marshal.Write(GetResourcePath().ToString());
        marshal.Write(m_meshId);
        marshal.Write(IsInverse());

        marshal.Write(m_material ? m_material->GetResourceId() : "None");

        return marshal;
    }

    SR_UTILS_NS::Component *SR_GTYPES_NS::Mesh3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
        const auto &&type = static_cast<MeshType>(marshal.Read<int32_t>());

        const auto &&path = marshal.Read<std::string>();
        const auto &&id = marshal.Read<uint32_t>();
        const auto &&inverse = marshal.Read<bool>();

        const auto &&material = marshal.Read<std::string>();

        Render* pRender = dataStorage->GetPointer<Render>();

        if (!SRVerifyFalse(!pRender)) {
            return nullptr;
        }

        auto &&pMesh = Load(path, type, id);

        if (pMesh) {
            if (material != "None") {
                if (Material *pMaterial = Material::Load(material)) {
                    pMesh->SetMaterial(pMaterial);
                }
                else
                    SR_ERROR("Mesh3D::LoadComponent() : failed to load material! Name: " + material);
            }

            pRender->RegisterMesh(pMesh);
            /// TODO: mesh->WaitCalculate();
        }

        return pMesh;
    }
}