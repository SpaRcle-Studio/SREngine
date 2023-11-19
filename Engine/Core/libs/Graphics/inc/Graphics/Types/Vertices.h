//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_VERTICES_H
#define GAMEENGINE_VERTICES_H

#include <Utils/Math/Vector2.h>
#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>

#include <Utils/Common/StringFormat.h>
#include <Utils/Common/Vertices.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Profile/TracyContext.h>

namespace SR_GRAPH_NS::Vertices {
    enum class Attribute {
        Unknown            = 0,

        FLOAT_R32G32B32A32 = 1 << 0,
        FLOAT_R32G32B32    = 1 << 1,
        FLOAT_R32G32       = 1 << 2,

        INT_R32G32B32A32   = 1 << 3,
        INT_R32G32B32      = 1 << 4,
        INT_R32G32         = 1 << 5,
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

        static SR_FORCE_INLINE std::vector<std::string> GetNames() {
            return { "VERTEX", "UV", "NORMAL", "TANGENT", "BITANGENT" };
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
            return SR_FORMAT("[ {}, {}, {}, {}, {} ],",
                    Vertices::ToString(pos).c_str(),
                    Vertices::ToString(uv).c_str(),
                    Vertices::ToString(norm).c_str(),
                    Vertices::ToString(bitang).c_str(),
                    Vertices::ToString(tang).c_str()
            );
        }
    };
    typedef std::vector<StaticMeshVertex> StaticMeshVertices;

    struct SkinnedMeshVertex {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 norm;
        glm::vec3 tang;
        glm::vec3 bitang;

        /// x - bone id, y - weight
        glm::vec2 weights[SR_MAX_BONES_ON_VERTEX];

        static SR_FORCE_INLINE std::vector<std::string> GetNames() {
            return {
                    "VERTEX", "UV", "NORMAL", "TANGENT", "BITANGENT",
                    "WEIGHT0", "WEIGHT1" , "WEIGHT2", "WEIGHT3",
                    "WEIGHT4", "WEIGHT5", "WEIGHT6", "WEIGHT7",
            };
        }

        static constexpr SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(SkinnedMeshVertex);
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes() {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, pos)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    SR_OFFSETOF(SkinnedMeshVertex, uv)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, norm)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, tang)));
            descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, bitang)));

            for (uint8_t i = 0; i < SR_MAX_BONES_ON_VERTEX; ++i) {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32, SR_OFFSETOF(SkinnedMeshVertex, weights[i])));
            }

            return descriptions;
        }

        bool operator==(const SkinnedMeshVertex& other) const {
            return pos       == other.pos
                   && uv     == other.uv
                   && norm   == other.norm
                   && bitang == other.bitang
                   && tang   == other.tang;
            //TODO:А что если 2 вершины в одном месте, а весы различны?
        }

        SR_NODISCARD std::string ToString() const {
            return SR_FORMAT("[ {}, {}, {}, {}, {} ],",
                             Vertices::ToString(pos).c_str(),
                             Vertices::ToString(uv).c_str(),
                             Vertices::ToString(norm).c_str(),
                             Vertices::ToString(bitang).c_str(),
                             Vertices::ToString(tang).c_str()
            );
        }
    };
    typedef std::vector<SkinnedMeshVertex> SkinnedMeshVertices;

    struct UIVertex {
        glm::vec3 pos;
        glm::vec2 uv;

        static constexpr SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(UIVertex);
        }

        static SR_FORCE_INLINE std::vector<std::string> GetNames() {
            return { "VERTEX", "UV" };
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

    SR_MAYBE_UNUSED static std::string ToString(const std::vector<uint32_t>& indices) {
        std::string str = std::to_string(indices.size()) + " indices: \n";
        for (uint32_t i = 0; i < indices.size() - 1; i++)
            str += std::to_string(indices[i]) + ", ";
        if (!indices.empty())
            str += std::to_string(indices[indices.size() - 1]);
        return str;
    }

    SR_MAYBE_UNUSED static std::string ToString(const std::vector<StaticMeshVertex>& vertices) {
        std::string str = std::to_string(vertices.size()) + " vertices: \n";
        for (uint32_t i = 0; i < vertices.size() - 1; i++)
            str += vertices[i].ToString() + ",\n";
        if (!vertices.empty())
            str += vertices[vertices.size() - 1].ToString();
        return str;
    }

    struct SimpleVertex {
        glm::vec3 pos;

        static SR_FORCE_INLINE std::vector<std::string> GetNames() {
            return { "VERTEX" };
        }

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

    SR_ENUM_NS_CLASS(VertexType,
        Unknown,
        None,
        StaticMeshVertex,
        SkinnedMeshVertex,
        SimpleVertex,
        UIVertex
    )

    SR_MAYBE_UNUSED static uint32_t GetVertexSize(VertexType type) {
        switch (type) {
            case VertexType::StaticMeshVertex:
                return sizeof(StaticMeshVertex);
            case VertexType::SkinnedMeshVertex:
                return sizeof(SkinnedMeshVertex);
            case VertexType::SimpleVertex:
                return sizeof(SimpleVertex);
            case VertexType::UIVertex:
                return sizeof(UIVertex);
            default:
                SRHalt0();
                return 0;
        }
    }

    template<typename V> SR_MATH_NS::FVector3 Barycenter(const std::vector<V>& vertices) {
        auto x = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.x; return sum; }();
        auto y = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.y; return sum; }();
        auto z = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.z; return sum; }();

        return SR_MATH_NS::FVector3(x, y, z) / vertices.size();
    }

    struct VertexInfo {
        std::vector<SR_VERTEX_DESCRIPTION> m_descriptions;
        std::vector<std::pair<Vertices::Attribute, size_t>> m_attributes;
        std::vector<std::string> m_names;
    };

    SR_MAYBE_UNUSED static VertexInfo GetVertexInfo(VertexType type) {
        VertexInfo info = {};
        switch (type) {
            case VertexType::SkinnedMeshVertex:
                info.m_attributes = SkinnedMeshVertex::GetAttributes();
                info.m_descriptions = { SkinnedMeshVertex::GetDescription() };
                info.m_names = SkinnedMeshVertex::GetNames();
                break;
            case VertexType::StaticMeshVertex:
                info.m_attributes = StaticMeshVertex::GetAttributes();
                info.m_descriptions = { StaticMeshVertex::GetDescription() };
                info.m_names = StaticMeshVertex::GetNames();
                break;
            case VertexType::SimpleVertex:
                info.m_attributes = SimpleVertex::GetAttributes();
                info.m_descriptions = { SimpleVertex::GetDescription() };
                info.m_names = SimpleVertex::GetNames();
                break;
            case VertexType::UIVertex:
                info.m_attributes = UIVertex::GetAttributes();
                info.m_descriptions = { UIVertex::GetDescription() };
                info.m_names = UIVertex::GetNames();
                break;
            case VertexType::None:
                break;
            default: {
                SR_ERROR("Vertices::GetVertexInfo() : unknown type! \n\tType: " + SR_UTILS_NS::EnumReflector::ToString(type).ToStringRef());
                SRHalt0();
                break;
            }
        }
        return info;
    }

    template<typename T> static std::vector<T> CastVertices(const std::vector<SR_UTILS_NS::Vertex>& raw) {
        SR_TRACY_ZONE;

        auto vertices = std::vector<T>();

        vertices.reserve(raw.size());

        if constexpr (std::is_same<Vertices::SimpleVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(T {
                        .pos = *reinterpret_cast<glm::vec3*>((void*)&vertex.position),
                });
            }
        }

        if constexpr (std::is_same<Vertices::UIVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(T {
                        .pos = *reinterpret_cast<glm::vec3*>((void*)&vertex.position),
                        .uv  = *reinterpret_cast<glm::vec2*>((void*)&vertex.uv),
                });
            }
        }

        if constexpr (std::is_same<Vertices::StaticMeshVertex, T>::value) {
            for (const auto& vertex : raw) {
                vertices.emplace_back(T {
                        .pos    = *reinterpret_cast<glm::vec3*>((void*)&vertex.position),
                        .uv     = *reinterpret_cast<glm::vec2*>((void*)&vertex.uv),
                        .norm   = *reinterpret_cast<glm::vec3*>((void*)&vertex.normal),
                        .tang   = *reinterpret_cast<glm::vec3*>((void*)&vertex.tangent),
                        .bitang = *reinterpret_cast<glm::vec3*>((void*)&vertex.bitangent),
                });
            }
        }

        if constexpr (std::is_same<Vertices::SkinnedMeshVertex, T>::value) {
            for (const auto& rawVertex : raw) {
                T vertex;
                vertex.pos    = *reinterpret_cast<glm::vec3*>((void*)&rawVertex.position);
                vertex.uv     = *reinterpret_cast<glm::vec2*>((void*)&rawVertex.uv);
                vertex.norm   = *reinterpret_cast<glm::vec3*>((void*)&rawVertex.normal);
                vertex.tang   = *reinterpret_cast<glm::vec3*>((void*)&rawVertex.tangent);
                vertex.bitang = *reinterpret_cast<glm::vec3*>((void*)&rawVertex.bitangent);
                for (uint32_t i = 0; i < SR_MAX_BONES_ON_VERTEX; i++) {
                    vertex.weights[i].x = static_cast<float>(rawVertex.weights[i].boneId);
                    vertex.weights[i].y = rawVertex.weights[i].weight;
                }
                vertices.emplace_back(vertex);
            }
        }

        if (raw.size() != vertices.size()) {
            SRHalt("Vertices::CastVertices() : sizes is different!");
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
            hash_combine<float>(res, vertex.pos.x);
            hash_combine<float>(res, vertex.pos.y);
            hash_combine<float>(res, vertex.pos.z);
            hash_combine<float>(res, vertex.uv.x);
            hash_combine<float>(res, vertex.uv.y);
            hash_combine<float>(res, vertex.norm.x);
            hash_combine<float>(res, vertex.norm.y);
            hash_combine<float>(res, vertex.norm.z);
            hash_combine<float>(res, vertex.tang.x);
            hash_combine<float>(res, vertex.tang.y);
            hash_combine<float>(res, vertex.tang.z);
            return res;
        }
    };

    template<> struct hash<SR_GRAPH_NS::Vertices::UIVertex> {
        size_t operator()(SR_GRAPH_NS::Vertices::UIVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<float>(res, vertex.pos.x);
            hash_combine<float>(res, vertex.pos.y);
            hash_combine<float>(res, vertex.pos.z);
            hash_combine<float>(res, vertex.uv.x);
            hash_combine<float>(res, vertex.uv.y);
            return res;
        }
    };

    template<> struct hash<SR_GRAPH_NS::Vertices::SimpleVertex> {
        size_t operator()(SR_GRAPH_NS::Vertices::SimpleVertex const& vertex) const {
            std::size_t res = 0;
            hash_combine<float>(res, vertex.pos.x);
            hash_combine<float>(res, vertex.pos.y);
            hash_combine<float>(res, vertex.pos.z);
            return res;
        }
    };
}

#endif //GAMEENGINE_VERTICES_H
