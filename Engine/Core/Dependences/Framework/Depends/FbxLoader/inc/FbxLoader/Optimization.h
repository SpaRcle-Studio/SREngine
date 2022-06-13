//
// Created by Monika on 01.04.2022.
//

#ifndef SRENGINE_OPTIMIZATION_H
#define SRENGINE_OPTIMIZATION_H

#include <FbxLoader/Mesh.h>
#include <FbxLoader/Node.h>
#include <FbxLoader/ISerializable.h>

namespace FbxLoader {
    class Material : public Tools::ISerializable, public Tools::NonCopyable {
        vec3 m_ambientColor;
        vec3 m_diffuseColor;
        vec3 m_specularColor;

        std::string m_diffuse;

    };

    class Model : public Tools::ISerializable, public Tools::NonCopyable {
        std::string m_name;

        vec3 Translation;
        vec3 Rotation;
        vec3 Scale;

        std::vector<Vertex> m_vertices;
        std::vector<uint32_t> m_indices;
        std::vector<uint64_t> m_materials;
    };

    class Fbx : public Tools::ISerializable, public Tools::NonCopyable {
        /// resources
        std::vector<Material> m_materials;

        /// data
        std::vector<Model> m_models;
    };
}

#endif //SRENGINE_OPTIMIZATION_H
