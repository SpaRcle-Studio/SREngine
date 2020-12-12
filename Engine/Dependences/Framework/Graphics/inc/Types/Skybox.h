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

        unsigned int                    m_VAO           = 0;
        unsigned int                    m_cubeMap       = 0;

        std::string                     m_name          = "Unnamed";

        unsigned int                    m_width         = 0;
        unsigned int                    m_height        = 0;

        glm::vec3                       m_position      = {0,0,0};

        std::vector<unsigned char*>     m_data          = std::vector<unsigned char*>();

        bool                            m_isCalculated  = false;
        bool                            m_isDestroy     = false;
        bool                            m_isUse         = false;
    public:
        inline unsigned int GetCubeMap() noexcept { return m_cubeMap; }
        void Draw();
        void AwaitDestroy();
        bool Free();
    public:
        static Skybox* Load(std::string name, std::string ext);
    };
}

#endif //GAMEENGINE_SKYBOX_H
