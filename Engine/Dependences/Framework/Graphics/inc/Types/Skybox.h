//
// Created by Nikita on 20.11.2020.
//

#ifndef GAMEENGINE_SKYBOX_H
#define GAMEENGINE_SKYBOX_H

#include <Types/Texture.h>
#include <vector>
#include <Environment/Environment.h>
#include <glm/glm.hpp>

namespace Framework::Graphics {
    class Camera;
    class Shader;
}

namespace Framework::Graphics::Types {
    class Skybox {
    private:
        Skybox();
        ~Skybox();
    private:
        bool Calculate();
    private:
        Environment*                    m_env           = nullptr;
        Render*                         m_render        = nullptr;

        unsigned int                    m_VAO           = 0;
        unsigned int                    m_cubeMap       = 0;

        std::string                     m_name          = "Unnamed";

        unsigned int                    m_width         = 0;
        unsigned int                    m_height        = 0;

        glm::vec3                       m_position      = {0,0,0};

        std::vector<unsigned char*>     m_data          = std::vector<unsigned char*>();

        bool                            m_isCalculated  = false;
        bool                            m_isDestroy     = false;
        volatile bool                   m_isVideoFree   = false;
        bool                            m_isUse         = false;

        Shader*                         m_shader        = nullptr;
        std::string                     m_shaderName    = "Unnamed";
    public:
        /// WARNING: Call only from render!
        bool FreeVideoMemory();

        inline void SetIsVideoFree(bool value){
            this->m_isVideoFree = value;
        }

        bool SetRender(Render* render);
        [[nodiscard]] inline unsigned int GetCubeMap() const noexcept { return m_cubeMap; }
        void Draw(Camera* camera);
        bool AwaitDestroy();
        bool Free();
    public:
        static Skybox* Load(std::string name, const std::string& shader_name);
    };
}

#endif //GAMEENGINE_SKYBOX_H
