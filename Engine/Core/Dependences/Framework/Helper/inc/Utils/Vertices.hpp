//
// Created by Monika on 25.03.2022.
//

#ifndef SRENGINE_SKYBOXCONSTANTS_H
#define SRENGINE_SKYBOXCONSTANTS_H

#include <macros.h>
#include <vector>
#include <FbxLoader/Loader.h>

namespace SR_UTILS_NS {
    const std::vector<uint32_t> SKYBOX_INDICES = { 0,1,2,0,2,3,2,1,4,5,2,4,6,0,3,6,3,7,5,4,6,7,5,6,3,2,5,3,5,7,4,1,0,6,4,0 };

    const std::vector<FbxLoader::Vertex> SKYBOX_INDEXED_VERTICES = {
            FbxLoader::Vertex(1, -1, 1),
            FbxLoader::Vertex(-1, -1, 1),
            FbxLoader::Vertex(-1, 1, 1),
            FbxLoader::Vertex(1, 1, 1),
            FbxLoader::Vertex(-1, -1, -1),
            FbxLoader::Vertex(-1, 1, -1),
            FbxLoader::Vertex(1, -1, -1),
            FbxLoader::Vertex(1, 1, -1),
    };

    template<typename T> static std::vector<T> IndexedVerticesToNonIndexed(
            const std::vector<T>& vertices,
            const std::vector<uint32_t>& indices)
    {
        auto rawVertices = std::vector<T>();

        for (const auto& index : indices)
            rawVertices.emplace_back(vertices[index]);

        return rawVertices;
    }
}

#endif //SRENGINE_SKYBOXCONSTANTS_H
