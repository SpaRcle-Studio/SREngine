//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>

// TODO: UNSAFE SHIT!

inline static std::map<unsigned int, unsigned long> VAO_usages = std::map<unsigned int, unsigned long>();
inline static std::map<std::string, unsigned int>   VAO_names = std::map<std::string, unsigned int>();

inline static std::map<uint32_t, unsigned long> VBO_usages = std::map<unsigned int, unsigned long>();
inline static std::map<uint32_t, unsigned long> IBO_usages = std::map<unsigned int, unsigned long>();
inline static std::map<std::string, std::pair<uint32_t, uint32_t>> VBOandIBO_names = std::map<std::string, std::pair<uint32_t, uint32_t>>();

bool Framework::Graphics::Types::Mesh3D::Calculate()  {
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

    m_mutex.lock();

    {
        /* Check exists pre-calculated meshes */
        if (m_env->GetPipeLine() == PipeLine::OpenGL) {
            unsigned int exists = VAO_names[m_resource_id];
            if (exists) {
                if (Debug::GetLevel() >= Debug::Level::High)
                    Debug::Log("Mesh3D::Calculate() : copy VAO...");

                m_VAO = (int) exists;

                VAO_usages[m_VAO]++;
                m_isCalculated = true;
                m_mutex.unlock();

                return true;
            }
        }
        else {
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
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh3D::Calculate() : calculating \""+ m_geometry_name +"\"...");

    if (m_env->GetPipeLine() == PipeLine::OpenGL) {
        if (!this->m_env->CalculateVAO(reinterpret_cast<unsigned int &>(m_VAO), m_vertices, m_countVertices)) {
            Debug::Error("Mesh3D::Calculate() : failed calculate \"" + m_geometry_name + "\" mesh!");
            m_mutex.unlock();
            return false;
        }

        VAO_usages[m_VAO]++;
        VAO_names[m_resource_id] = m_VAO;
    }
    else {
        if (!this->m_env->CalculateVBO(reinterpret_cast<unsigned int &>(m_VBO), m_vertices.data(), sizeof(Vertices::Mesh3DVertex), m_countVertices)) {
            Debug::Error("Mesh3D::Calculate() : failed calculate VBO \"" + m_geometry_name + "\" mesh!");
            this->m_hasErrors = true;
            m_mutex.unlock();
            return false;
        }

        if (!this->m_env->CalculateIBO(reinterpret_cast<unsigned int &>(m_IBO), m_indices.data(), sizeof(uint32_t), m_countIndices)) {
            Debug::Error("Mesh3D::Calculate() : failed calculate IBO \"" + m_geometry_name + "\" mesh!");
            this->m_hasErrors = true;
            m_mutex.unlock();
            return false;
        }

        VBOandIBO_names[m_resource_id] = std::pair((uint32_t)m_VBO, (uint32_t)m_IBO);
        int i = VBO_usages[m_VBO];
        VBO_usages[(uint32_t)m_VBO]++;
        int i2 = VBO_usages[m_VBO];
        IBO_usages[(uint32_t)m_IBO]++;
    }

    m_isCalculated = true;

    m_mutex.unlock();

    return true;
}

Framework::Graphics::Types::Mesh *Framework::Graphics::Types::Mesh3D::Copy() {
    if (m_isDestroy) {
        Debug::Error("Mesh3D::Copy() : mesh already destroyed!");
        return nullptr;
    }

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh3D::Copy() : copy \""+m_resource_id+ "\" mesh...");

    if (!m_material){
        Debug::Error("Mesh3D::Copy() : material is nullptr! Something went wrong...");
        return nullptr;
    }

    m_mutex.lock();

    Material* mat = new Material(
            m_material->m_diffuse,
            m_material->m_normal,
            m_material->m_specular,
            m_material->m_glossiness
    );

    Mesh3D* copy = new Mesh3D(this->m_shader, mat, this->m_geometry_name);

    {
        mat->m_mesh         = copy;
        mat->m_bloom        = m_material->m_bloom;
        mat->m_transparent  = m_material->m_transparent;
        mat->m_color        = m_material->m_color;
    }

    copy->m_countVertices = m_countVertices;
    copy->m_countIndices  = m_countIndices;
    copy->m_useIndices    = m_useIndices;

    copy->m_position = m_position;
    copy->m_rotation = m_rotation;
    copy->m_scale    = m_scale;

    if (m_isCalculated) {
        if (m_VAO != -1) VAO_usages[m_VAO]++;
        if (m_VBO != -1) VBO_usages[m_VBO]++;
        if (m_IBO != -1) IBO_usages[m_IBO]++;

        copy->m_VAO = m_VAO;
        copy->m_VBO = m_VBO;
        copy->m_IBO = m_IBO;
    }else{
        copy->m_vertices = m_vertices;
        copy->m_indices  = m_indices;
    }

    copy->m_isCalculated = m_isCalculated;
    copy->m_autoRemove = m_autoRemove;
    copy->m_modelMat = m_modelMat;

    copy->m_resource_id = m_resource_id;

    m_mutex.unlock();

    return copy;
}

bool Framework::Graphics::Types::Mesh3D::FreeVideoMemory() {
    if (m_env->GetPipeLine() == PipeLine::OpenGL) {
        if (m_VAO > 0) {
            VAO_usages[m_VAO]--;
            if (VAO_usages[m_VAO] == 0)
                m_env->FreeMesh(m_VAO);
            m_isCalculated = false;
            return true;
        } else {
            Debug::Error("Mesh:FreeVideoMemory() : VAO is zero! Something went wrong...");
            return false;
        }
    }
    else {
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
        else {
            Debug::Error("Mesh:FreeVideoMemory() : IBO is not exists! Something went wrong...");
            return false;
        }

        this->m_isCalculated = false;
        return true;
    }
}
