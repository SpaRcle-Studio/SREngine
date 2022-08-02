//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_VERTICES_H
#define GAMEENGINE_VERTICES_H

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>

#include <Utils/Common/StringFormat.h>
#include <Utils/Common/Vertices.hpp>
#include <Utils/Common/Enumerations.h>

namespace SR_GRAPH_NS::Vertices {
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
        return SR_UTILS_NS::Format("{ %f, %f, %f }", vec3.x, vec3.y, vec3.z);
    }

    static std::string ToString(const glm::vec2& vec2) {
        return SR_UTILS_NS::Format("{ %f, %f }", vec2.x, vec2.y);
    }

    struct StaticMeshVertex {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 norm;
        glm::vec3 tang;
        glm::vec3 bitang;

        static constexpr SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(StaticMeshVertex);
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, pos)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    offsetof(StaticMeshVertex, uv)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, norm)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, tang)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, bitang)));

            return descriptions;
        }

        bool operator==(const StaticMeshVertex& other) const {
            return pos       == other.pos
                   && uv     == other.uv
                   && norm   == other.norm
                   && bitang == other.bitang
                   && tang   == other.tang;
        }

        SR_NODISCARD std::string ToString() const {
            return "{ " + Vertices::ToString(pos) + ", " + Vertices::ToString(uv) + " }";
        }
    };
    typedef std::vector<StaticMeshVertex> StaticMeshVertices;

    struct UIVertex {
        glm::vec3 pos;
        glm::vec2 uv;

        static constexpr SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(UIVertex);
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(UIVertex, pos)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    offsetof(UIVertex, uv)));

            return descriptions;
        }

        bool operator==(const UIVertex& other) const {
            return pos       == other.pos
                   && uv     == other.uv;
        }

        SR_NODISCARD std::string ToString() const {
            return "{ " + Vertices::ToString(pos) + ", " + Vertices::ToString(uv) + " }";
        }
    };
    typedef std::vector<UIVertex> UIVertices;

    static std::string ToString(const std::vector<uint32_t>& indices) {
        std::string str = std::to_string(indices.size()) + " indices: \n";
        for (uint32_t i = 0; i < indices.size() - 1; i++)
            str += std::to_string(indices[i]) + ", ";
        if (!indices.empty())
            str += std::to_string(indices[indices.size() - 1]);
        return str;
    }

    static std::string ToString(const std::vector<StaticMeshVertex>& vertices) {
        std::string str = std::to_string(vertices.size()) + " vertices: \n";
        for (uint32_t i = 0; i < vertices.size() - 1; i++)
            str += vertices[i].ToString() + ",\n";
        if (!vertices.empty())
            str += vertices[vertices.size() - 1].ToString();
        return str;
    }

    struct SimpleVertex {
        glm::vec3 pos;

        static SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(SimpleVertex);
        }

        bool operator==(const SimpleVertex& other) const {
            return pos == other.pos;
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(SimpleVertex, pos)));

            return descriptions;
        }
    };
    typedef std::vector<SimpleVertex> SimpleVertices;

    SR_ENUM_CLASS(Type,
        Unknown,
        StaticMeshVertex,
        SkinnedMeshVertex,
        SimpleVertex,
        UIVertex,
    )

    static uint32_t GetVertexSize(Type type) {
        switch (type) {
            case Type::StaticMeshVertex:
                return sizeof(StaticMeshVertex);
            case Type::SimpleVertex:
                return sizeof(SimpleVertex);
            case Type::UIVertex:
                return sizeof(UIVertex);
            default:
                SRAssert(false);
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
            case Type::StaticMeshVertex:
                info.m_attributes = StaticMeshVertex::GetAttributes();
                info.m_descriptions = { StaticMeshVertex::GetDescription() };
                break;
            case Type::SimpleVertex:
                info.m_attributes = SimpleVertex::GetAttributes();
                info.m_descriptions = { SimpleVertex::GetDescription() };
                break;
            case Type::UIVertex:
                info.m_attributes = UIVertex::GetAttributes();
                info.m_descriptions = { UIVertex::GetDescription() };
                break;
            default: {
                SR_ERROR("Vertices::GetVertexInfo() : unknown type! \n\tType: " + std::to_string((int) type));
                SRAssert(false);
                break;
            }
        }
        return info;
    }

    template<typename T> static std::vector<T> CastVertices(const std::vector<SR_UTILS_NS::Vertex>& raw) {
        auto vertices = std::vector<T>();

        vertices.reserve(raw.size());

        if constexpr (std::is_same<Vertices::SimpleVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(Vertices::SimpleVertex{
                        .pos = *reinterpret_cast<glm::vec3*>((void*)&vertex.position),
                });
            }
        }

        if constexpr (std::is_same<Vertices::UIVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(Vertices::UIVertex{
                        .pos = *reinterpret_cast<glm::vec3*>((void*)&vertex.position),
                        .uv  = *reinterpret_cast<glm::vec2*>((void*)&vertex.uv),
                });
            }
        }

        if constexpr (std::is_same<Vertices::StaticMeshVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(Vertices::StaticMeshVertex{
                        .pos    = *reinterpret_cast<glm::vec3*>((void*)&vertex.position),
                        .uv     = *reinterpret_cast<glm::vec2*>((void*)&vertex.uv),
                        .norm   = *reinterpret_cast<glm::vec3*>((void*)&vertex.normal),
                        .tang   = *reinterpret_cast<glm::vec3*>((void*)&vertex.tangent),
                        .bitang = *reinterpret_cast<glm::vec3*>((void*)&vertex.bitangent),
                });
            }
        }

        return vertices;
    }
}

namespace std {
    template <class T> static inline void hash_combine(std::size_t & s, const T & v) {
        std::hash<T> h;
        s ^= h(v) + 0x9e3779b9 + (s << 6) + (s >> 2);
    }

    template<> struct hash<SR_GRAPH_NS::Vertices::StaticMeshVertex> {
        size_t operator()(SR_GRAPH_NS::Vertices::StaticMeshVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<glm::vec3>(res, vertex.pos);
            hash_combine<glm::vec2>(res, vertex.uv);
            hash_combine<glm::vec3>(res, vertex.norm);
            hash_combine<glm::vec3>(res, vertex.tang);
            return res;
        }
    };

    template<> struct hash<SR_GRAPH_NS::Vertices::UIVertex> {
        size_t operator()(SR_GRAPH_NS::Vertices::UIVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<glm::vec3>(res, vertex.pos);
            hash_combine<glm::vec2>(res, vertex.uv);
            return res;
        }
    };

    template<> struct hash<SR_GRAPH_NS::Vertices::SimpleVertex> {
        size_t operator()(SR_GRAPH_NS::Vertices::SimpleVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<glm::vec3>(res, vertex.pos);
            return res;
        }
    };
}

#endif //GAMEENGINE_VERTICES_H
