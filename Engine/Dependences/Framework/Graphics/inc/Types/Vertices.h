//
// Created by Nikita on 30.05.2021.
//

#ifndef GAMEENGINE_VERTICES_H
#define GAMEENGINE_VERTICES_H

#include <iostream>
#include <vector>
#include <string>
#include <macros.h>
#include <variant>

#include <glm/glm.hpp>
#include <glm/gtx/hash.hpp>
#include <glm/gtx/string_cast.hpp>

#include <Math/Vector3.h>

#define SR_VERTEX_DESCRIPTION size_t

namespace Framework::Graphics::Vertices {
    static std::string format(const char *fmt, ...)
    {
        va_list args;
        va_start(args, fmt);
        std::vector<char> v(1024);
        while (true)
        {
            va_list args2;
            va_copy(args2, args);
            int res = vsnprintf(v.data(), v.size(), fmt, args2);
            if ((res >= 0) && (res < static_cast<int>(v.size())))
            {
                va_end(args);
                va_end(args2);
                return std::string(v.data());
            }
            size_t size;
            if (res < 0)
                size = v.size() * 2;
            else
                size = static_cast<size_t>(res) + 1;
            v.clear();
            v.resize(size);
            va_end(args2);
        }
    }

    enum class Attribute {
        FLOAT_R32G32B32A32,
        FLOAT_R32G32B32,
        FLOAT_R32G32,
    };

    static std::string ToString(const glm::vec3& vec3) {
        return format("{ %f, %f, %f }", vec3.x, vec3.y, vec3.z);
    }

    static std::string ToString(const glm::vec2& vec2) {
        return format("{ %f, %f }", vec2.x, vec2.y);
    }

    struct Mesh3DVertex {
        glm::vec3 pos;
        glm::vec2 uv;
        glm::vec3 norm;
        glm::vec3 tang;

        static SR_FORCE_INLINE SR_VERTEX_DESCRIPTION GetDescription() {
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

    enum class Type {
        Mesh3DVertex, SkyboxVertex
    };

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

    template<typename V> Helper::Math::Vector3 Barycenter(const std::vector<V>& vertices) {
        auto x = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.x; return sum; }();
        auto y = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.y; return sum; }();
        auto z = [vertices]() { float sum = 0.f; for (const auto& v : vertices) sum += v.pos.z; return sum; }();

        return Helper::Math::Vector3(x, y, z) / vertices.size();
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
