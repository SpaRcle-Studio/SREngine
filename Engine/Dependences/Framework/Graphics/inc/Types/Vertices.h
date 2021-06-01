//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_VERTICES_H
#define GAMEENGINE_VERTICES_H

#include <iostream>
#include <vector>
#include <string>
#include <macros.h>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

#define SR_VERTEX_DESCRIPTION size_t

namespace Framework::Graphics::Vertices {
    enum class Attribute {
        FLOAT_R32G32B32A32,
        FLOAT_R32G32B32,
        FLOAT_R32G32,
    };

    struct Mesh3DVertex {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 norm;
        glm::vec3 tang;

        static SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(Mesh3DVertex);
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(Mesh3DVertex, pos)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    offsetof(Mesh3DVertex, uv)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(Mesh3DVertex, norm)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(Mesh3DVertex, tang)));

            return descriptions;
        }

        bool operator==(const Mesh3DVertex& other) const {
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


namespace std {
    template <class T> static inline void hash_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
    }

    template<> struct std::hash<Framework::Graphics::Vertices::Mesh3DVertex> {
        size_t operator()(Framework::Graphics::Vertices::Mesh3DVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<glm::vec3>(res, vertex.pos);
            hash_combine<glm::vec2>(res, vertex.uv);
            //hash_combine<glm::vec3>(res, vertex.color);
            hash_combine<glm::vec3>(res, vertex.norm);
            hash_combine<glm::vec3>(res, vertex.tang);
            return res;
        }
    };
}

#endif //GAMEENGINE_VERTICES_H
