//
// Created by Nikita on 17.11.2020.
//

#include "Loaders/ObjLoader.h"

#include <Types/Geometry/Mesh3D.h>
#include <Debug.h>
#include <typeinfo>
#include <ResourceManager/ResourceManager.h>

#include <tinyobjloader/tiny_obj_loader.cc>
#include <Types/Geometry/Mesh3D.h>
#include <Types/Material.h>

using namespace Framework::Helper;

namespace Framework::Graphics::ObjLoader {
    std::vector<Types::Mesh *> ObjLoader::Load(const std::string &path, bool withIndices, Types::MeshType type) {
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
