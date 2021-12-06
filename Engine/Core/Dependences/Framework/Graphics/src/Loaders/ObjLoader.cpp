//
// Created by Nikita on 17.11.2020.
//

#include "Loaders/ObjLoader.h"
#include <ResourceManager/ResourceManager.h>

using namespace Framework::Helper;

namespace Framework::Graphics::ObjLoader {
    std::vector<Types::Mesh *> Load(const std::string &path, bool withIndices, Framework::Graphics::Types::MeshType type) {
        switch (type) {
            case Types::MeshType::Static:
                return Load<Types::Mesh3D>(path, withIndices);
            case Types::MeshType::Wireframe:
                return Load<Types::DebugWireframeMesh>(path, withIndices);
            case Types::MeshType::Skinned:
            case Types::MeshType::Unknown:
            default:
                return {};
        }
    }
}
