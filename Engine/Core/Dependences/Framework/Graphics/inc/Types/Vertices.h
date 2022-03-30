//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_VERTICES_H
#define GAMEENGINE_VERTICES_H

#include <Debug.h>
#include <Math/Vector3.h>
#include <Utils/Enumerations.h>
#include <Utils/StringFormat.h>
#include <FbxLoader/Mesh.h>

namespace Framework::Graphics::Vertices {
    enum class Attribute {
        Unknown            = 0,

        FLOAT_R32G32B32A32 = 1 << 0,
        FLOAT_R32G32B32    = 1 << 1,
        FLOAT_R32G32       = 1 << 2,

        INT_R32G32B32A32   = 1 << 3,
        INT_R32G32B32      = 1 << 4,
        INT_R32G32         = 1 << 5,

        VECTOR4            = FLOAT_R32G32B32A32 | INT_R32G32B32A32,
        VECTOR3            = FLOAT_R32G32B32 | INT_R32G32B32,
        VECTOR2            = FLOAT_R32G32 | INT_R32G32,
    };

    static std::string ToString(const glm::vec3& vec3) {
        return Helper::Format("{ %f, %f, %f }", vec3.x, vec3.y, vec3.z);
    }

    static std::string ToString(const glm::vec2& vec2) {
        return Helper::Format("{ %f, %f }", vec2.x, vec2.y);
    }

    struct Mesh3DVertex {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 norm;
        glm::vec3 tang;

        static constexpr SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
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

        [[nodiscard]] std::string ToString() const {
            return "{ " + Vertices::ToString(pos) + ", " + Vertices::ToString(uv) + " }";
        }
    };
    typedef std::vector<Mesh3DVertex> Mesh3DVertices;

    static std::string ToString(const std::vector<uint32_t>& indices) {
        std::string str = std::to_string(indices.size()) + " indices: \n";
        for (uint32_t i = 0; i < indices.size() - 1; i++)
            str += std::to_string(indices[i]) + ", ";
        if (!indices.empty())
            str += std::to_string(indices[indices.size() - 1]);
        return str;
    }

    static std::string ToString(const std::vector<Mesh3DVertex>& vertices) {
        std::string str = std::to_string(vertices.size()) + " vertices: \n";
        for (uint32_t i = 0; i < vertices.size() - 1; i++)
            str += vertices[i].ToString() + ",\n";
        if (!vertices.empty())
            str += vertices[vertices.size() - 1].ToString();
        return str;
    }

    struct SkyboxVertex {
        glm::vec3 pos;

        static SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(SkyboxVertex);
        }

        bool operator==(const SkyboxVertex& other) const {
            return pos == other.pos;
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(SkyboxVertex, pos)));

            return descriptions;
        }
    };
    typedef std::vector<SkyboxVertex> SkyboxVertices;

    SR_ENUM_CLASS(Type,
        Unknown,
        Mesh3DVertex,
        SkyboxVertex
    )

    static uint32_t GetVertexSize(Type type) {
        switch (type) {
            case Type::Mesh3DVertex:
                return sizeof(Mesh3DVertex);
            case Type::SkyboxVertex:
                return sizeof(SkyboxVertex);
            default:
                Helper::Debug::Error("Vertices::GetVertexSize() : unknown type!");
                return 0;
        }
    }

    template<typename V> Helper::Math::FVector3 Barycenter(const std::vector<V>& vertices) {
        auto x = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.x; return sum; }();
        auto y = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.y; return sum; }();
        auto z = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.z; return sum; }();

        return Helper::Math::FVector3(x, y, z) / vertices.size();
    }

    struct VertexInfo {
        std::vector<SR_VERTEX_DESCRIPTION> m_descriptions;
        std::vector<std::pair<Vertices::Attribute, size_t>> m_attributes;
    };

    static VertexInfo GetVertexInfo(Type type) {
        VertexInfo info = {};
        switch (type) {
            case Type::Mesh3DVertex:
                info.m_attributes = Mesh3DVertex::GetAttributes();
                info.m_descriptions = { Mesh3DVertex::GetDescription() };
                break;
            case Type::SkyboxVertex:
                info.m_attributes = SkyboxVertex::GetAttributes();
                info.m_descriptions = { SkyboxVertex::GetDescription() };
                break;;
            default:
                Helper::Debug::Error("Vertices::GetVertexInfo() : unknown type! \n\tType: " + std::to_string((int)type));
                break;
        }
        return info;
    }

    template<typename T> static std::vector<T> CastVertices(const std::vector<FbxLoader::Vertex>& raw) {
        auto vertices = std::vector<T>();

        if constexpr (std::is_same<Vertices::SkyboxVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(Vertices::SkyboxVertex{
                        .pos = { vertex.pos.x, vertex.pos.y, vertex.pos.z },
                });
            }
        }

        if constexpr (std::is_same<Vertices::Mesh3DVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(Vertices::Mesh3DVertex{
                        .pos = { vertex.pos.x, vertex.pos.y, vertex.pos.z },
                        .uv  = { vertex.uv.x, vertex.uv.y },
                });
            }
        }

        return vertices;
    }
}

namespace std {
    template <class T> static inline void hash_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s^= h(v) + 0x9e3779b9 + (s<< 6) + (s>> 2);
    }

    template<> struct hash<Framework::Graphics::Vertices::Mesh3DVertex> {
        size_t operator()(Framework::Graphics::Vertices::Mesh3DVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<glm::vec3>(res, vertex.pos);
            hash_combine<glm::vec2>(res, vertex.uv);
            hash_combine<glm::vec3>(res, vertex.norm);
            hash_combine<glm::vec3>(res, vertex.tang);
            return res;
        }
    };

    template<> struct hash<Framework::Graphics::Vertices::SkyboxVertex> {
        size_t operator()(Framework::Graphics::Vertices::SkyboxVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<glm::vec3>(res, vertex.pos);
            return res;
        }
    };
}

#endif //GAMEENGINE_VERTICES_H
