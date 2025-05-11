

# File Vertices.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Types**](dir_c1000ee3da93f5d04a34b48b4ba0b616.md) **>** [**Vertices.h**](Graphics_2inc_2Graphics_2Types_2Vertices_8h.md)

[Go to the documentation of this file](Graphics_2inc_2Graphics_2Types_2Vertices_8h.md)


```C++
//
// Created by Nikita on 30.05.2021.
//

#ifndef SR_ENGINE_VERTICES_H
#define SR_ENGINE_VERTICES_H

#include <Graphics/macros.h>

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
        UINT_R32           = 1 << 6,
        INT_R32            = 1 << 7,
    };

    static std::string ToString(const glm::vec3& vec3) {
        return SR_FORMAT("[ {}, {}, {} ]", vec3.x, vec3.y, vec3.z);
    }

    static std::string ToString(const glm::vec2& vec2) {
        return SR_FORMAT("[ {}, {} ]", vec2.x, vec2.y);
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

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes(bool asTypes) {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            if (asTypes) {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
            }
            else {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, pos)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    offsetof(StaticMeshVertex, uv)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, norm)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, tang)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(StaticMeshVertex, bitang)));
            }

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

        uint32_t weightsCount = 0;

        glm::vec2 weights[SR_MAX_BONES_ON_VERTEX];

        static SR_FORCE_INLINE std::vector<std::string> GetNames() {
            std::vector<std::string> names = {
                    "VERTEX", "UV", "NORMAL", "TANGENT", "BITANGENT", "WEIGHTS_COUNT", "WEIGHTS"
            };

            //for (uint8_t i = 0; i < SR_MAX_BONES_ON_VERTEX; ++i) {
            //    names.emplace_back("WEIGHT" + std::to_string(i));
            //}
            return names;
        }

        static constexpr SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
            return sizeof(SkinnedMeshVertex);
        }

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes(bool asTypes) {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            if (asTypes) {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::UINT_R32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32, SR_MAX_BONES_ON_VERTEX));
            }
            else {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, pos)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    SR_OFFSETOF(SkinnedMeshVertex, uv)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, norm)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, tang)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, SR_OFFSETOF(SkinnedMeshVertex, bitang)));
                descriptions.emplace_back(std::pair(Attribute::UINT_R32, SR_OFFSETOF(SkinnedMeshVertex, weightsCount)));

                for (uint8_t i = 0; i < SR_MAX_BONES_ON_VERTEX; ++i) {
                    descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32, SR_OFFSETOF(SkinnedMeshVertex, weights[i])));
                }
            }

            return descriptions;
        }

        bool operator==(const SkinnedMeshVertex& other) const {
            return pos       == other.pos
                   && uv     == other.uv
                   && norm   == other.norm
                   && bitang == other.bitang
                   && tang   == other.tang
                   && weightsCount  == other.weightsCount
            ;
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

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes(bool asTypes) {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            if (asTypes) {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    1));
            }
            else {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(UIVertex, pos)));
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32,    offsetof(UIVertex, uv)));
            }

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

        static SR_FORCE_INLINE std::vector<std::pair<Attribute, size_t>> GetAttributes(bool asTypes) {
            auto descriptions = std::vector<std::pair<Attribute, size_t>>();

            if (asTypes) {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, 1));
            }
            else {
                descriptions.emplace_back(std::pair(Attribute::FLOAT_R32G32B32, offsetof(SimpleVertex, pos)));
            }

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
        std::vector<std::pair<Vertices::Attribute, size_t >> m_attributes;
        std::vector<std::pair<Vertices::Attribute, size_t >> m_types;
        std::vector<std::string> m_names;
    };

    SR_MAYBE_UNUSED static VertexInfo GetVertexInfo(VertexType type) {
        VertexInfo info = {};
        switch (type) {
            case VertexType::SkinnedMeshVertex:
                info.m_attributes = SkinnedMeshVertex::GetAttributes(false);
                info.m_types = SkinnedMeshVertex::GetAttributes(true);
                info.m_descriptions = { SkinnedMeshVertex::GetDescription() };
                info.m_names = SkinnedMeshVertex::GetNames();
                break;
            case VertexType::StaticMeshVertex:
                info.m_attributes = StaticMeshVertex::GetAttributes(false);
                info.m_types = StaticMeshVertex::GetAttributes(true);
                info.m_descriptions = { StaticMeshVertex::GetDescription() };
                info.m_names = StaticMeshVertex::GetNames();
                break;
            case VertexType::SimpleVertex:
                info.m_attributes = SimpleVertex::GetAttributes(false);
                info.m_types = SimpleVertex::GetAttributes(true);
                info.m_descriptions = { SimpleVertex::GetDescription() };
                info.m_names = SimpleVertex::GetNames();
                break;
            case VertexType::UIVertex:
                info.m_attributes = UIVertex::GetAttributes(false);
                info.m_types = UIVertex::GetAttributes(true);
                info.m_descriptions = { UIVertex::GetDescription() };
                info.m_names = UIVertex::GetNames();
                break;
            case VertexType::None:
                break;
            default: {
                SR_ERROR("Vertices::GetVertexInfo() : unknown type! \n\tType: " + SR_UTILS_NS::EnumReflector::ToStringAtom(type).ToStringRef());
                SRHalt0();
                break;
            }
        }
        return info;
    }

    template<typename T> static std::vector<T> CastVertices(const SR_UTILS_NS::Vertex* pData, uint32_t count) {
        SR_TRACY_ZONE;

        auto vertices = std::vector<T>();

        vertices.reserve(count);

        if constexpr (std::is_same<Vertices::SimpleVertex, T>::value) {
            for (uint32_t i = 0; i < count; i++) {
                vertices.emplace_back(T {
                        .pos = *reinterpret_cast<glm::vec3*>((void*)&pData[i].position),
                });
            }
        }

        if constexpr (std::is_same<Vertices::UIVertex, T>::value) {
            for (uint32_t i = 0; i < count; i++) {
                vertices.emplace_back(T {
                        .pos = *reinterpret_cast<glm::vec3*>((void*)&pData[i].position),
                        .uv  = *reinterpret_cast<glm::vec2*>((void*)&pData[i].uv),
                });
            }
        }

        if constexpr (std::is_same<Vertices::StaticMeshVertex, T>::value) {
            for (uint32_t i = 0; i < count; i++) {
                vertices.emplace_back(T {
                        .pos    = *reinterpret_cast<glm::vec3*>((void*)&pData[i].position),
                        .uv     = *reinterpret_cast<glm::vec2*>((void*)&pData[i].uv),
                        .norm   = *reinterpret_cast<glm::vec3*>((void*)&pData[i].normal),
                        .tang   = *reinterpret_cast<glm::vec3*>((void*)&pData[i].tangent),
                        .bitang = *reinterpret_cast<glm::vec3*>((void*)&pData[i].bitangent),
                });
            }
        }

        if constexpr (std::is_same<Vertices::SkinnedMeshVertex, T>::value) {
            for (uint32_t i = 0; i < count; i++) {
                T vertex;
                vertex.pos    = *reinterpret_cast<glm::vec3*>((void*)&pData[i].position);
                vertex.uv     = *reinterpret_cast<glm::vec2*>((void*)&pData[i].uv);
                vertex.norm   = *reinterpret_cast<glm::vec3*>((void*)&pData[i].normal);
                vertex.tang   = *reinterpret_cast<glm::vec3*>((void*)&pData[i].tangent);
                vertex.bitang = *reinterpret_cast<glm::vec3*>((void*)&pData[i].bitangent);
                vertex.weightsCount = *reinterpret_cast<uint32_t*>((void*)&pData[i].weightsNum);
                for (uint32_t j = 0; j < SR_MAX_BONES_ON_VERTEX; j++) {
                    vertex.weights[j].x = static_cast<float>(pData[i].weights[j].boneId);
                    vertex.weights[j].y = pData[i].weights[j].weight;
                }
                vertices.emplace_back(vertex);
            }
        }

        if (count != vertices.size()) {
            SRHalt("Vertices::CastVertices() : sizes is different!");
        }

        return vertices;
    }

    template<typename T> static std::vector<T> CastVertices(const std::vector<SR_UTILS_NS::Vertex>& raw) {
        return CastVertices<T>(raw.data(), raw.size());
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

#endif //SR_ENGINE_VERTICES_H
```


