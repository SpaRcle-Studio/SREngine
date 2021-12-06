//
// Created by Monika on 26.07.2021.
//

#ifndef FBXLOADER_FBX_H
#define FBXLOADER_FBX_H

#include <FbxLoader/Mesh.h>
#include <FbxLoader/Node.h>

namespace FbxLoader {
    struct ObjectType {

    };

    struct Definitions {
        uint32_t version;
        uint32_t count;
        std::vector<ObjectType> objectTypes;
    };

    struct NodeAttribute {
        uint64_t    id;
        std::string name;
        std::string type;
    };

    struct Geometry {
        uint64_t    id;
        std::string name;
        std::string type;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
    };

    struct Objects {
        std::vector<NodeAttribute> nodeAttributes;
        std::vector<Geometry>      geometries;

        [[nodiscard]] bool Ready() const { return !(nodeAttributes.empty() && geometries.empty()); }
    };

    struct Fbx {
        Definitions definitions;
        Objects     objects;

        [[nodiscard]] std::vector<Geometry> GetShapes() const { return objects.geometries; }
    };
}

#endif //FBXLOADER_FBX_H
