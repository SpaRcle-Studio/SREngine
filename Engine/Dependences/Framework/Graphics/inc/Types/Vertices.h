//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_VERTICES_H
#define GAMEENGINE_VERTICES_H

#include <iostream>
#include <vector>
#include <string>
#include <macros.h>

#define SR_VERTEX_DESCRIPTION size_t

namespace Framework::Graphics::Vertices {
    enum class Attribute {
        FLOAT_R32G32B32A32,
        FLOAT_R32G32B32,
        FLOAT_R32G32,
    };

    struct Model3DVertex {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 norm;
        glm::vec3 tang;

        static SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(Model3DVertex);
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(Model3DVertex, pos)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    offsetof(Model3DVertex, uv)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(Model3DVertex, norm)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(Model3DVertex, tang)));

            return descriptions;
        }

        bool operator==(const Model3DVertex& other) const {
            return pos      == other.pos
                   && uv    == other.uv
                   && norm  == other.norm
                   && tang  == other.tang;
        }
    };

    struct SkyboxVertex {
        glm::vec3 pos;

        static SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(SkyboxVertex);
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(SkyboxVertex, pos)));

            return descriptions;
        }
    };
}

#endif //GAMEENGINE_VERTICES_H
