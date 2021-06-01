//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_VERTEX_H
#define GAMEENGINE_VERTEX_H

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>

/*
namespace Framework::Graphics {
    struct Vertex{
        glm::vec3 position;
        glm::vec2 texCoords;
        glm::vec3 color;
        glm::vec3 normal;
        glm::vec3 tangent;

        //glm::u8vec4 bonesIds = {0, 0, 0, 0};
        //glm::u8vec4 bonesWeights = {0, 0, 0, 0};

        bool operator==(const Vertex& other) const {
            return position == other.position
            && color        == other.color
            && texCoords    == other.texCoords
            && normal       == other.normal
            && tangent      == other.tangent;
        }
    };
}

namespace std {
    //template<> struct hash<Framework::Graphics::Vertex> {
    //    size_t operator()(Framework::Graphics::Vertex const& vertex) const {
    //        return ((hash<glm::vec3>()(vertex.position) ^ (hash<glm::vec3>()(vertex.color) << 1)) >> 1) ^ (hash<glm::vec2>()(vertex.texCoords) << 1);
    //    }
    //};

    template <class T> static inline void hash_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
    }

    template<> struct std::hash<Framework::Graphics::Vertex> {
        size_t operator()(Framework::Graphics::Vertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<glm::vec3>(res, vertex.position);
            hash_combine<glm::vec2>(res, vertex.texCoords);
            hash_combine<glm::vec3>(res, vertex.color);
            hash_combine<glm::vec3>(res, vertex.normal);
            hash_combine<glm::vec3>(res, vertex.tangent);
            return res;
        }
    };
}
*/

/*
    int boneID1;
    int boneID2;
    int boneID3;
    int boneID4;
 */

#endif //GAMEENGINE_VERTEX_H
