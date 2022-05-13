//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>
#include <Types/RawMesh.h>
#include <Types/Material.h>
#include <Environment/Environment.h>
#include <Types/Uniforms.h>
#include <Render/Shader.h>
#include <Render/Render.h>

bool Framework::Graphics::Types::Mesh3D::Calculate()  {
    const std::lock_guard<std::recursive_mutex> lock(m_mutex);

    if (m_isCalculated)
        return true;

    const bool iboOK = m_IBO != SR_ID_INVALID;
    if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
        m_isCalculated = true;
        return true;
    }

    if (!IsCanCalculate())
        return false;

    if (SR_UTILS_NS::Debug::GetLevel() >= SR_UTILS_NS::Debug::Level::High)
        SR_LOG("Mesh3D::Calculate() : calculating \"" + m_geometryName + "\"...");

    ///TODO: if (!m_vertices.empty())
    ///    m_barycenter = Vertices::Barycenter(m_vertices);
    ///SRAssert(m_barycenter != Math::FVector3(Math::UnitMAX));

    auto&& vertices = Vertices::CastVertices<Vertices::StaticMeshVertex>(m_rawMesh->GetVertices(m_meshId));

    if (!CalculateVBO<Vertices::Type::StaticMeshVertex>(vertices.data()))
        return false;

    return IndexedMesh::Calculate();
}

Framework::Helper::IResource* Framework::Graphics::Types::Mesh3D::Copy(IResource* destination) const {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    auto* mesh3D = dynamic_cast<Mesh3D *>(destination ? destination : new Mesh3D(m_geometryName));
    mesh3D = dynamic_cast<Mesh3D *>(IndexedMesh::Copy(mesh3D));

    if (mesh3D->IsCalculated()) {
        auto &&manager = Memory::MeshManager::Instance();
        mesh3D->m_VBO = manager.CopyIfExists<Vertices::Type::StaticMeshVertex, Memory::MeshManager::VBO>(GetResourceId());
    }

    return mesh3D;
}

bool Framework::Graphics::Types::Mesh3D::FreeVideoMemory() {
    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
        SR_LOG("Mesh3D::FreeVideoMemory() : free \"" + m_geometryName + "\" mesh video memory...");

    if (!FreeVBO<Vertices::Type::StaticMeshVertex>())
        return false;

    return IndexedMesh::FreeVideoMemory();
}

void Framework::Graphics::Types::Mesh3D::DrawVulkan() {
    if (!IsReady() || IsDestroyed())
        return;

    if ((!m_isCalculated && !Calculate()) || m_hasErrors)
        return;

    auto &&shader = m_material->GetShader();

    if (m_dirtyMaterial)
    {
        m_dirtyMaterial = false;

        if (m_descriptorSet >= 0 && !m_env->FreeDescriptorSet(&m_descriptorSet)) {
            SR_ERROR("Mesh::FreeVideoMemory() : failed to free descriptor set!");
        }

        if (m_UBO >= 0 && !m_env->FreeUBO(&m_UBO)) {
            SR_ERROR("Mesh::FreeVideoMemory() : failed to free uniform buffer object!");
        }

        if (shader->GetUBOBlockSize() > 0) {
            if (m_descriptorSet = m_env->AllocDescriptorSet({DescriptorType::Uniform}); m_descriptorSet < 0) {
                SR_ERROR("Mesh3D::DrawVulkan() : failed to calculate descriptor set!");
                m_hasErrors = true;
                return;
            }

            if (m_UBO = m_env->AllocateUBO(shader->GetUBOBlockSize()); m_UBO < 0) {
                SR_ERROR("Mesh3D::DrawVulkan() : failed to allocate uniform buffer object!");
                m_hasErrors = true;
                return;
            }

            m_env->BindUBO(m_UBO);
            m_env->BindDescriptorSet(m_descriptorSet);
        }
        else if (shader->GetSamplersCount() > 0) {
            if (m_descriptorSet = m_env->AllocDescriptorSet({DescriptorType::CombinedImage}); m_descriptorSet < 0) {
                SR_ERROR("Mesh3D::DrawVulkan() : failed to calculate descriptor set!");
                m_hasErrors = true;
                return;
            }
            m_env->BindDescriptorSet(m_descriptorSet);
        }
        else
            m_env->ResetDescriptorSet();

        shader->InitUBOBlock();
        shader->Flush();

        m_material->UseSamplers();
    }

    if (m_descriptorSet != SR_ID_INVALID) {
        m_env->BindDescriptorSet(m_descriptorSet);
    }

    m_env->DrawIndices(m_countIndices);
}

void Framework::Graphics::Types::Mesh3D::DrawOpenGL() {
    if (IsDestroyed() || (!m_isCalculated && !Calculate()))
        return;

    //m_material->UseOpenGL();
    //m_env->DrawTriangles(m_countVertices);
}

void Framework::Graphics::Types::Mesh3D::UpdateUBO() {
    if (m_UBO >= 0 && m_material && !m_hasErrors) {
        //Mesh3dUBO ubo = { m_modelMat, m_material->GetColor(MAT_PROPERTY_DIFFUSE_COLOR).ToGLM() };
        //m_env->UpdateUBO(m_UBO, &ubo, sizeof(Mesh3dUBO));
    }


}

SR_HTYPES_NS::Marshal SR_GTYPES_NS::Mesh3D::Save(SR_UTILS_NS::SavableFlags flags) const {
    SR_HTYPES_NS::Marshal marshal = Component::Save(flags);

    marshal.Write(IsEnabled());
    marshal.Write(static_cast<int32_t>(m_type));

    marshal.Write(GetResourcePath());
    marshal.Write(m_meshId);
    marshal.Write(IsInverse());

    marshal.Write(m_material ? m_material->GetResourceId() : "None");

    return marshal;
}

SR_UTILS_NS::Component *SR_GTYPES_NS::Mesh3D::LoadComponent(SR_HTYPES_NS::Marshal& marshal, const SR_HTYPES_NS::DataStorage *dataStorage) {
    const auto &&enabled = marshal.Read<bool>();
    const auto &&type = static_cast<MeshType>(marshal.Read<int32_t>());

    const auto &&path = marshal.Read<std::string>();
    const auto &&id = marshal.Read<uint32_t>();
    const auto &&inverse = marshal.Read<bool>();

    const auto &&material = marshal.Read<std::string>();

    Render *render = dataStorage->GetPointer<Render>("Render");

    if (!render) {
        SRAssert(false);
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

        render->RegisterMesh(pMesh);
        /// TODO: mesh->WaitCalculate();
    }

    return pMesh;
}
