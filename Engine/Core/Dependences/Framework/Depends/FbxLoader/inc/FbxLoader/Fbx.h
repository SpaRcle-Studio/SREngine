//
// Created by Monika on 26.07.2021.
//

#ifndef FBXLOADER_FBX_H
#define FBXLOADER_FBX_H

#include <FbxLoader/Mesh.h>
#include <FbxLoader/Node.h>
#include <FbxLoader/ISerializable.h>

namespace FbxLoader {
    typedef std::pair<uint32_t, uint32_t> MaterialRange;

    struct ObjectType {

    };

    struct Definitions : public Tools::ISerializable {
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        uint32_t version = 0;
        uint32_t count   = 0;

        void Clear();
    };

    class NodeAttribute : public Tools::ISerializable {
    public:
        NodeAttribute() = default;
        ~NodeAttribute() override = default;

    public:
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

    public:
        uint64_t    id = 0;
        std::string name;
        std::string type;

    };

    struct RawGeometry : public Tools::ISerializable, public Tools::NonCopyable {
    public:
        RawGeometry() = default;
        ~RawGeometry() override = default;

    public:
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        [[nodiscard]] bool Valid() const;

        RawGeometry(RawGeometry&& geometry)  noexcept {
            id = std::exchange(geometry.id, {});
            name = std::exchange(geometry.name, {});
            type = std::exchange(geometry.type, {});
            vertices = std::exchange(geometry.vertices, {});
            indices = std::exchange(geometry.indices, {});
            materials = std::exchange(geometry.materials, {});
        }

        RawGeometry& operator=(RawGeometry&& geometry) noexcept {
            id = std::exchange(geometry.id, {});
            name = std::exchange(geometry.name, {});
            type = std::exchange(geometry.type, {});
            vertices = std::exchange(geometry.vertices, {});
            indices = std::exchange(geometry.indices, {});
            materials = std::exchange(geometry.materials, {});
            return *this;
        }

    public:
        uint64_t    id = 0;
        std::string name;
        std::string type;

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::vector<MaterialRange> materials;

    };

    struct RawModel : public Tools::ISerializable, public Tools::NonCopyable {
    public:
        RawModel() = default;
        ~RawModel() override = default;

    public:
        void Save(std::ofstream &file) const override;
        void Load(std::ifstream &file) override;

        [[nodiscard]] bool Valid() const;

        RawModel(RawModel&& model) noexcept {
            id = std::exchange(model.id, {});
            name = std::exchange(model.name, {});
            type = std::exchange(model.type, {});
            Translation = std::exchange(model.Translation, {});
            Rotation = std::exchange(model.Rotation, {});
            Scale = std::exchange(model.Scale, {});
        }

        RawModel& operator=(RawModel&& model) noexcept {
            id = std::exchange(model.id, {});
            name = std::exchange(model.name, {});
            type = std::exchange(model.type, {});
            Translation = std::exchange(model.Translation, {});
            Rotation = std::exchange(model.Rotation, {});
            Scale = std::exchange(model.Scale, {});
            return *this;
        }

    public:
        uint64_t    id = 0;
        std::string name;
        std::string type;

        vec3 Translation;
        vec3 Rotation;
        vec3 Scale;

    };

    struct Objects : public Tools::ISerializable {
        [[nodiscard]] bool Ready() const { return !(nodeAttributes.empty() && geometries.empty()); }

        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        void Clear();

        std::vector<NodeAttribute> nodeAttributes;
        std::vector<RawGeometry>   geometries;
        std::vector<RawModel>      models;
    };

    struct Connections : public Tools::ISerializable {
        using Connection = std::pair<uint64_t, uint64_t>;

        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        void Clear();

        std::vector<Connection> geometryToModel;
        std::vector<Connection> materialToModel;
        std::vector<Connection> textureToMaterial;
        std::vector<Connection> videoToTexture;
        std::vector<Connection> nodeAttributeToModel;
        std::vector<Connection> modelToModel;
    };

    struct RawFbx : public Tools::ISerializable {
        void Save(std::ofstream& file) const override;
        void Load(std::ifstream& file) override;

        [[nodiscard]] std::vector<RawGeometry>& GetShapes() { return objects.geometries; }

        [[nodiscard]] bool Valid() const {
            return !objects.geometries.empty() ||
                   !objects.nodeAttributes.empty();
        }

        void Clear() {
            definitions.Clear();
            objects.Clear();
            connections.Clear();
        }

        Definitions definitions;
        Objects     objects;
        Connections connections;

    };
}

#endif //FBXLOADER_FBX_H
