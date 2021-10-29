//
// Created by Nikita on 02.06.2021.
//

#include <Types/Geometry/Mesh3D.h>

#include <Memory/MeshManager.h>

// TODO: UNSAFE SHIT!

struct VidMemInfo {
    uint32_t m_usages;
    uint32_t m_vidId;
};

typedef std::map<std::string, VidMemInfo> VideoResources;

inline static VideoResources VBOs = VideoResources();
inline static VideoResources IBOs = VideoResources();

bool Framework::Graphics::Types::Mesh3D::Calculate()  {
    const std::lock_guard<std::mutex> locker(m_mutex);

    if ((m_VBO >= 0 || m_IBO >= 0) && !m_hasErrors) {
        this->m_isCalculated = true;
        return true;
    }

    if (!IsCanCalculate())
        return false;

    if (Debug::GetLevel() >= Debug::Level::High)
        Debug::Log("Mesh3D::Calculate() : calculating \"" + m_geometry_name + "\"...");

    /*if (auto VBO = Memory::MeshManager::Instance().Find<Mesh3D>(m_resource_id, Memory::MeshManager::VBO))
        m_VBO = static_cast<int32_t>(VBO->Copy());
    else {

    }

    if (m_useIndices) {
        if (auto IBO = Memory::MeshManager::Instance().Find<Mesh3D>(m_resource_id, Memory::MeshManager::IBO))
            m_IBO = static_cast<int32_t>(IBO->Copy());
        else {

        }
    }*/

    /* Check exists pre-calculated meshes */
    {
        if (auto exists = VBOs.find(m_resource_id); exists != VBOs.end()) {
            if (Debug::GetLevel() >= Debug::Level::High)
                Debug::Log("Mesh3D::Calculate() : copy VBO...");

            m_VBO = (int)exists->second.m_vidId;
            exists->second.m_usages++;
        }

        if (m_useIndices)
            if (auto exists = IBOs.find(m_resource_id); exists != IBOs.end()) {
                if (Debug::GetLevel() >= Debug::Level::High)
                    Debug::Log("Mesh3D::Calculate() : copy IBO...");

                m_IBO = (int)exists->second.m_vidId;
                exists->second.m_usages++;
            }
    }

    if (m_VBO < 0) {
        if (!this->m_env->CalculateVBO(m_VBO, m_vertices.data(), Vertices::Type::Mesh3DVertex, m_countVertices)) {
            Debug::Error("Mesh3D::Calculate() : failed calculate VBO \"" + m_geometry_name + "\" mesh!");
            this->m_hasErrors = true;
            return false;
        }

        m_barycenter = Vertices::Barycenter(m_vertices);
        VBOs[m_resource_id] = VidMemInfo{ .m_usages = 1, .m_vidId = (uint32_t)m_VBO };
    }

    if (m_useIndices && m_IBO < 0) {
        if (!this->m_env->CalculateIBO(m_IBO, m_indices.data(), sizeof(uint32_t), m_countIndices, m_VBO)) {
            Debug::Error("Mesh3D::Calculate() : failed calculate IBO \"" + m_geometry_name + "\" mesh!");
            this->m_hasErrors = true;
            return false;
        }

        IBOs[m_resource_id] = VidMemInfo{ .m_usages = 1, .m_vidId = (uint32_t)m_IBO };
    }

    m_isCalculated = true;
    return true;
}

Framework::Graphics::Types::Mesh *Framework::Graphics::Types::Mesh3D::Copy() const {
    const std::lock_guard<std::mutex> locker(m_mutex);

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
        if (m_VBO != -1) VBOs[m_resource_id].m_usages++;
        if (m_IBO != -1) IBOs[m_resource_id].m_usages++;

        copy->m_VBO = m_VBO;
        copy->m_IBO = m_IBO;
        copy->m_UBO = -1;
        copy->m_descriptorSet = -1;
    } else {
        copy->m_vertices = m_vertices;
        copy->m_indices  = m_indices;
    }

    copy->m_resource_id   = m_resource_id;

    copy->m_isCalculated  = m_isCalculated;
    copy->m_autoRemove    = m_autoRemove;
    copy->m_modelMat      = m_modelMat;

    return copy;
}

bool Framework::Graphics::Types::Mesh3D::FreeVideoMemory() {
    if (Helper::Debug::GetLevel() >= Helper::Debug::Level::High)
        Helper::Debug::Log("Mesh3D::FreeVideoMemory() : free \"" + m_geometry_name + "\" mesh video memory...");

    if (m_VBO >= 0) {
        if (VBOs[m_resource_id].m_usages--; VBOs[m_resource_id].m_usages == 0) {
            if (!m_env->FreeVBO(m_VBO)) {
                Debug::Error("Mesh:FreeVideoMemory() : failed free VBO! Something went wrong...");
                return false;
            } else
                VBOs.erase(m_resource_id);
        }
    }
    else {
        Debug::Error("Mesh:FreeVideoMemory() : VBO is not exists! Something went wrong...");
        return false;
    }

    if (m_IBO >= 0) {
        if (IBOs[m_resource_id].m_usages--; IBOs[m_resource_id].m_usages == 0) {
            if (!m_env->FreeIBO(m_IBO)) {
                Debug::Error("Mesh:FreeVideoMemory() : failed free IBO! Something went wrong...");
                return false;
            } else
                IBOs.erase(m_resource_id);
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
        Mesh3dUBO ubo = { m_modelMat };
        m_env->UpdateUBO(m_UBO, &ubo, sizeof(Mesh3dUBO));
    }
}
