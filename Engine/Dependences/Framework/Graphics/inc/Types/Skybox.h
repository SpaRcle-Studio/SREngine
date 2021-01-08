//
// Created by Nikita on 20.11.2020.
//

#ifndef GAMEENGINE_SKYBOX_H
#define GAMEENGINE_SKYBOX_H

#include <Types/Texture.h>
#include <vector>
#include <Environment/Environment.h>
#include <glm/glm.hpp>

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
    public:
        /// WARNING: Call only from render!
        bool FreeVideoMemory();

        inline void SetIsVideoFree(bool value){
            this->m_isVideoFree = value;
        }

        inline bool SetRender(Render* render){
            if (m_render){
                Debug::Error("Skybox::SetRender() : render already set!");
                return false;
            }

            this->m_render = render;
            return true;
        }
        inline unsigned int GetCubeMap() noexcept { return m_cubeMap; }
        void Draw();
        bool AwaitDestroy();
        bool Free();
    public:
        static Skybox* Load(std::string name);
    };
}

#endif //GAMEENGINE_SKYBOX_H
