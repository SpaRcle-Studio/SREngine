//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>

#define ConfigureShader(shader) \
            shader->SetMat4("modelMat", m_modelMat); \
            shader->SetVec3("color", m_material->m_color); \
            shader->SetIVec2("config", { (int)m_material->m_bloom, (int)this->m_isSelected }); \

bool Framework::Graphics::Types::Mesh3D::Calculate()  {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    bool iboOK = ((m_IBO != SR_ID_INVALID && m_useIndices) || !m_useIndices);
    if (m_VBO != SR_ID_INVALID && iboOK && !m_hasErrors) {
        this->m_isCalculated = true;
        return true;
    }

    if (!IsCanCalculate())
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh3D::Calculate() : calculating \"" + m_geometry_name + "\"...");

    m_barycenter = Vertices::Barycenter(m_vertices);

    if (m_VBO = Memory::MeshManager::Instance().CopyIfExists<Mesh3D, Memory::MeshManager::VBO>(m_resource_id); m_VBO == SR_ID_INVALID) {
        if (m_VBO = this->m_env->CalculateVBO(m_vertices.data(), Vertices::Type::Mesh3DVertex, m_countVertices); m_VBO == SR_ID_INVALID) {
            Debug::Error("Mesh3D::Calculate() : failed calculate VBO \"" + m_geometry_name + "\" mesh!");
            this->m_hasErrors = true;
            return false;
        } else
            Memory::MeshManager::Instance().Register<Mesh3D, Memory::MeshManager::VBO>(m_resource_id, m_VBO);
    }

    return IndexedMesh::Calculate();
}

Framework::Graphics::Types::Mesh *Framework::Graphics::Types::Mesh3D::Copy(Mesh* mesh) const {
    const std::lock_guard<std::recursive_mutex> locker(m_mutex);

    Mesh3D* mesh3D = dynamic_cast<Mesh3D *>(mesh ? mesh : new Mesh3D(m_geometry_name));
    mesh3D = dynamic_cast<Mesh3D *>(IndexedMesh::Copy(mesh3D));

    if (mesh3D->IsCalculated()) {
        mesh3D->m_VBO = Memory::MeshManager::Instance().CopyIfExists<Mesh3D, Memory::MeshManager::VBO>(m_resource_id);
        mesh3D->m_vertices = m_vertices;
    }

    return mesh3D;
}

bool Framework::Graphics::Types::Mesh3D::FreeVideoMemory() {
    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
        Helper::Debug::Log("Mesh3D::FreeVideoMemory() : free \"" + m_geometry_name + "\" mesh video memory...");

    using namespace Memory;

    if (MeshManager::Instance().Free<Mesh3D, MeshManager::VBO>(m_resource_id) == MeshManager::FreeResult::Freed) {
        if (!m_env->FreeVBO(m_VBO))
            Debug::Error("Mesh:FreeVideoMemory() : failed free VBO! Something went wrong...");
    }

    return IndexedMesh::FreeVideoMemory();
}

void Framework::Graphics::Types::Mesh3D::SetVertexArray(const std::any& vertices) {
    try {
        auto mesh3DVertices = std::any_cast<Vertices::Mesh3DVertices>(vertices);
        this->m_countVertices = mesh3DVertices.size();
        this->m_vertices      = mesh3DVertices;
        this->m_isCalculated  = false;
    }
    catch (const std::bad_any_cast& e) {
        Helper::Debug::Error("Mesh3D::SetVertexArray() : failed to cast any to vertices! \n\tMessage: " + std::string(e.what()));
    }
}

void Framework::Graphics::Types::Mesh3D::DrawVulkan()  {
    if (!this->IsReady() || m_isDestroy)
        return;

    if (!m_isCalculated)
        if (m_hasErrors || !this->Calculate())
            return;

    if (m_descriptorSet < 0) {
        if (m_descriptorSet = m_env->AllocDescriptorSet({ DescriptorType::Uniform }); m_descriptorSet < 0) {
            Helper::Debug::Error("Mesh3D::DrawVulkan() : failed to calculate descriptor set!");
            m_hasErrors = true; return;
        }

        if (m_UBO = m_env->AllocateUBO(sizeof(Mesh3dUBO)); m_UBO < 0) {
            Helper::Debug::Error("Mesh3D::DrawVulkan() : failed to allocate uniform buffer object!");
            m_hasErrors = true; return;
        }

        this->m_env->UpdateDescriptorSets(m_descriptorSet, {
                { DescriptorType::Uniform, { 0, m_UBO                                 } },
                { DescriptorType::Uniform, { 1, Shader::GetCurrentShader()->GetUBO(0) } },
        });

        Mesh3dUBO ubo = { m_modelMat }; m_env->UpdateUBO(m_UBO, &ubo, sizeof(Mesh3dUBO));

        //!==========================

        m_env->BindDescriptorSet(m_descriptorSet);
        this->m_material->UseVulkan();
    }

    this->m_env->BindDescriptorSet(m_descriptorSet);

    this->m_env->DrawIndices(this->m_countIndices);
}

void Framework::Graphics::Types::Mesh3D::DrawOpenGL()  {
    if (m_isDestroy || (!m_isCalculated && !this->Calculate()))
        return;

    if (!m_shader) {
        ConfigureShader(Shader::GetDefaultGeometryShader())
        this->m_material->UseWithDefShader();
    }
    else {
        ConfigureShader(m_shader)
        this->m_material->UseOpenGL();
    }

    if (!m_useIndices)
        this->m_env->DrawTriangles(m_countVertices);
    else
        Helper::Debug::Error("Mesh::DrawOpenGL() : isn't support indices!");
}
