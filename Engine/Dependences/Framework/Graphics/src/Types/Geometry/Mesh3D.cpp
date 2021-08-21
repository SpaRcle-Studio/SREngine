//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>

// TODO: UNSAFE SHIT!

inline static std::map<uint32_t, unsigned long> VBO_usages = std::map<unsigned int, unsigned long>();
inline static std::map<uint32_t, unsigned long> IBO_usages = std::map<unsigned int, unsigned long>();
inline static std::map<std::string, std::pair<uint32_t, uint32_t>> VBOandIBO_names = std::map<std::string, std::pair<uint32_t, uint32_t>>();

bool Framework::Graphics::Types::Mesh3D::Calculate()  {
    if (m_VBO >= 0 || m_IBO >= 0) {
        this->m_isCalculated = true;
        return true;
    }

    if (!m_render){
        Debug::Error("Mesh3D::Calculate() : mesh is not register in render!");
        return false;
    }

    if (!m_shader){
        if (!Shader::GetDefaultGeometryShader()) {
            Debug::Error("Mesh3D::Calculate() : mesh have not shader!");
            return false;
        }
    }

    if (!m_material){
        Debug::Error("Mesh3D::Calculate() : mesh have not material!");
        return false;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh3D::Calculate() : calculating \""+ m_geometry_name +"\"...");

    m_mutex.lock();

    {
        /* Check exists pre-calculated meshes */
        auto exists = VBOandIBO_names.find(m_resource_id);
        if (exists != VBOandIBO_names.end()) {
            if (Debug::GetLevel() >= Debug::Level::High)
                Debug::Log("Mesh3D::Calculate() : copy VBO and IBO...");

            m_VBO = (int)exists->second.first;
            m_IBO = (int)exists->second.second;

            VBO_usages[m_VBO]++;
            IBO_usages[m_IBO]++;
            m_isCalculated = true;
            m_mutex.unlock();

            return true;
        }
    }

    if (!this->m_env->CalculateVBO(m_VBO, m_vertices.data(), Vertices::Type::Mesh3DVertex, m_countVertices)) {
        Debug::Error("Mesh3D::Calculate() : failed calculate VBO \"" + m_geometry_name + "\" mesh!");
        this->m_hasErrors = true;
        m_mutex.unlock();
        return false;
    } else
        m_barycenter = Vertices::Barycenter(m_vertices);

    if (m_useIndices)
        if (!this->m_env->CalculateIBO(m_IBO, m_indices.data(), sizeof(uint32_t), m_countIndices, m_VBO)) {
            Debug::Error("Mesh3D::Calculate() : failed calculate IBO \"" + m_geometry_name + "\" mesh!");
            this->m_hasErrors = true;
            m_mutex.unlock();
            return false;
        }

    VBOandIBO_names[m_resource_id] = std::pair((uint32_t)m_VBO, (uint32_t)m_IBO);
    VBO_usages[(uint32_t)m_VBO]++;

    if (m_useIndices)
        IBO_usages[(uint32_t)m_IBO]++;

    m_isCalculated = true;

    m_mutex.unlock();

    return true;
}

Framework::Graphics::Types::Mesh *Framework::Graphics::Types::Mesh3D::Copy() const {
    if (m_isDestroy) {
        Debug::Error("Mesh3D::Copy() : mesh already destroyed!");
        return nullptr;
    }

    if (Debug::GetLevel() >= Debug::Level::Full)
        Debug::Log("Mesh3D::Copy() : copy \""+m_resource_id+ "\" mesh...");

    if (!m_material){
        Debug::Error("Mesh3D::Copy() : material is nullptr! Something went wrong...");
        return nullptr;
    }

    m_mutex.lock();

    auto* mat = new Material(
            m_material->m_diffuse,
            m_material->m_normal,
            m_material->m_specular,
            m_material->m_glossiness
    );

    auto* copy = new Mesh3D(this->m_shader, mat, this->m_geometry_name);

    {
        mat->m_mesh        = copy;
        mat->m_bloom       = m_material->m_bloom;
        mat->m_transparent = m_material->m_transparent;
        mat->m_color       = m_material->m_color;
    }

    copy->m_countVertices = m_countVertices;
    copy->m_countIndices  = m_countIndices;
    copy->m_useIndices    = m_useIndices;

    copy->m_barycenter = m_barycenter;
    copy->m_position   = m_position;
    copy->m_rotation   = m_rotation;
    copy->m_scale      = m_scale;

    if (m_isCalculated) {
        if (m_VBO != -1) VBO_usages[m_VBO]++;
        if (m_IBO != -1) IBO_usages[m_IBO]++;

        copy->m_VBO = m_VBO;
        copy->m_IBO = m_IBO;
        copy->m_UBO = -1;
        copy->m_descriptorSet = -1;
    } else {
        copy->m_vertices = m_vertices;
        copy->m_indices  = m_indices;
    }

    copy->m_resource_id   = m_resource_id;

    //!? copy->m_isCalculated  = false;
    copy->m_isCalculated  = m_isCalculated;
    copy->m_autoRemove    = m_autoRemove;
    copy->m_modelMat      = m_modelMat;

    m_mutex.unlock();

    return copy;
}

bool Framework::Graphics::Types::Mesh3D::FreeVideoMemory() {
    if (m_VBO >= 0) {
        int i = VBO_usages[m_VBO];
        VBO_usages[m_VBO]--;
        if (VBO_usages[m_VBO] == 0)
            if (!m_env->FreeVBO(m_VBO)) {
                Debug::Error("Mesh:FreeVideoMemory() : failed free VBO! Something went wrong...");
                return false;
            }
    }
    else {
        Debug::Error("Mesh:FreeVideoMemory() : VBO is not exists! Something went wrong...");
        return false;
    }

    if (m_IBO >= 0) {
        IBO_usages[m_IBO]--;
        if (IBO_usages[m_IBO] == 0)
            if (!m_env->FreeIBO(m_IBO)) {
                Debug::Error("Mesh:FreeVideoMemory() : failed free IBO! Something went wrong...");
                return false;
            }
    }
    else if (m_useIndices){
        Debug::Error("Mesh:FreeVideoMemory() : IBO is not exists! Something went wrong...");
        return false;
    }

    //! the set of descriptors and the uniform buffer are allocated at the first drawing call.
    if (m_pipeline == PipeLine::Vulkan) {
        if (m_descriptorSet >= 0) {
            this->m_env->FreeDescriptorSet(m_descriptorSet);
            this->m_descriptorSet = -5;
        }

        if (m_UBO >= 0) {
            if (!this->m_env->FreeUBO(m_UBO)) {
                Helper::Debug::Error("Mesh3D::FreeVideoMemory() : failed to free uniform buffer object!");
                return false;
            }
        }
    }

    this->m_isCalculated = false;
    return true;
}

void Framework::Graphics::Types::Mesh3D::ReCalcModel() {
    glm::mat4 modelMat = glm::mat4(1.0f);

    if (m_pipeline == PipeLine::OpenGL) {
        modelMat = glm::translate(modelMat, {
                -m_position.x,
                m_position.y,
                m_position.z //-m_position.z
        });

        modelMat *= mat4_cast(glm::quat(glm::radians(glm::vec3(
                {
                        m_rotation.x,//-m_rotation.x,
                        -m_rotation.y,// + 180.f, //-m_rotation.y + 180.f,
                        m_rotation.z // SEE: change form -m_rotation.z
                }
        ))));
    } else {
        modelMat = glm::translate(modelMat, {
                m_position.x,
                m_position.y,
                m_position.z
        });

        modelMat *= mat4_cast(glm::quat(glm::radians(glm::vec3(
                {
                        m_rotation.x,//-m_rotation.x,
                        m_rotation.y,// + 180.f, //-m_rotation.y + 180.f,
                        -m_rotation.z // SEE: change form -m_rotation.z
                }
        ))));
    }

    modelMat = glm::scale(modelMat, m_inverse ? -m_scale.ToGLM() : m_scale.ToGLM());

    this->m_modelMat = modelMat;

    if (m_UBO >= 0) {
        Mesh3DUBO ubo = { m_modelMat };
        m_env->UpdateUBO(m_UBO, &ubo, sizeof(Mesh3DUBO));
    }
}
