//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_VERTEX_H
#define GAMEENGINE_VERTEX_H

#include <glm/glm.hpp>

namespace Framework::Graphics {
    struct Vertex{
        glm::vec3 position;
        glm::vec2 texCoords;
        glm::vec3 normal;
        glm::vec3 tangent;

        //glm::u8vec4 bonesIds = {0, 0, 0, 0};
        //glm::u8vec4 bonesWeights = {0, 0, 0, 0};
    };
}
/*
    int boneID1;
    int boneID2;
    int boneID3;
    int boneID4;
 */

#endif //GAMEENGINE_VERTEX_H
