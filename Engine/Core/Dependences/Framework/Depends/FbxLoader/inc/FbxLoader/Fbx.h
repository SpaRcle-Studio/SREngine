//
// Created by Monika on 26.07.2021.
//

#ifndef FBXLOADER_FBX_H
#define FBXLOADER_FBX_H

#include <FbxLoader/Mesh.h>
#include <FbxLoader/Node.h>
#include <FbxLoader/ISerializable.h>

namespace FbxLoader {
    typedef std::pair<uint32_t, uint32_t> Material;

    struct ObjectType {

    };

    struct Definitions : public Tools::ISerializable {
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        uint32_t version = 0;
        uint32_t count   = 0;
    };

    class NodeAttribute : public Tools::ISerializable {
    public:
        NodeAttribute();
        ~NodeAttribute() override = default;

    public:
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

    public:
        uint64_t    id;
        std::string name;
        std::string type;

    };

    struct Geometry : public Tools::ISerializable {
    public:
        Geometry();

    public:
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

    public:
        uint64_t    id;
        std::string name;
        std::string type;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<Material> materials;

    };

    struct Objects : public Tools::ISerializable {
        [[nodiscard]] bool Ready() const { return !(nodeAttributes.empty() && geometries.empty()); }

        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        std::vector<NodeAttribute> nodeAttributes;
        std::vector<Geometry>      geometries;
    };

    struct Fbx : public Tools::ISerializable {
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        [[nodiscard]] std::vector<Geometry> GetShapes() const { return objects.geometries; }

        Definitions definitions;
        Objects     objects;

    };
}

#endif //FBXLOADER_FBX_H
