//
// Created by Nikita on 20.11.2020.
//

#ifndef GAMEENGINE_SKYBOX_H
#define GAMEENGINE_SKYBOX_H

#include <Types/Texture.h>
#include <vector>

namespace Framework::Graphics::Types {
    class Skybox {
    public:

    private:
        std::vector<Texture*> m_sides = std::vector<Texture*>();
    };
}

#endif //GAMEENGINE_SKYBOX_H
