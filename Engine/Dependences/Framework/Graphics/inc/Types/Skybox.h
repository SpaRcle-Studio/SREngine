//
// Created by Nikita on 20.11.2020.
//

#ifndef GAMEENGINE_SKYBOX_H
#define GAMEENGINE_SKYBOX_H

#include <Types/Texture.h>
#include <vector>
#include <Environment/Environment.h>

namespace Framework::Graphics::Types {
    class Skybox {
    private:
        Skybox();
        ~Skybox();
    private:
        Environment*                    m_env           = nullptr;

        std::string                     m_name          = "Unnamed";

        unsigned int                    m_width         = 0;
        unsigned int                    m_height        = 0;

        std::vector<unsigned char*>     m_data          = std::vector<unsigned char*>();

        bool                            m_isCalculated  = false;
    public:
        static Skybox* Load(std::string name, std::string ext);
    };
}

#endif //GAMEENGINE_SKYBOX_H
