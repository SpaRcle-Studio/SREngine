//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_OBJLOADER_H
#define GAMEENGINE_OBJLOADER_H

#include <string>
#include <vector>
#include <mutex>
#include <utility>
#include <map>
#include <iomanip>
#include <Debug.h>
#include <glm/glm.hpp>
#include <Types/Vertices.h>
#include "../../../Depends/tinyobjloader/inc/tiny_obj_loader.h"
#include <Memory/MeshAllocator.h>

namespace Framework::Graphics::Types {
    class Mesh;
    enum class MeshType;
}

namespace Framework::Graphics {
    namespace Vertices {
        struct Mesh3DVertex;
    }

    namespace ObjLoader {
        template<typename T> struct Shape {
            std::string m_name;
            std::vector<uint32_t> m_indices;
            std::vector<T> m_vertices;
        };

        std::vector<Types::Mesh*> Load(const std::string& path, bool withIndices, Framework::Graphics::Types::MeshType type);

        template<typename T> std::vector<Shape<T>> LoadSourceWithIndices(const std::string& path) {
            std::vector<Shape<T>> source = { };

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warn, err;

            if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
                Helper::Debug::Error("ObjLoader::LoadSourceWithIndices() : failed open file!\n\tWarn: " + warn + "\n\tError: " + err);
                return {};
            }

            for (auto& shape : shapes) {
                auto vertices = std::vector<T>();
                auto indices = std::vector<uint32_t>();

                std::unordered_map<T, uint32_t> uniqueVertices {};

                if (shape.mesh.indices.empty()) {
                    for (uint32_t i = 0; i < static_cast<uint32_t>(attrib.vertices.size() / 3); ++i) {
                        tinyobj::index_t index = {};

                        index.vertex_index = i;

                        shape.mesh.indices.emplace_back(index);
                    }
                }

                for (const auto& index : shape.mesh.indices) {
                    T vertex = T();

                    vertex.pos = glm::vec3 {
                            (float_t)attrib.vertices[3 * index.vertex_index + 0],
                            (float_t)attrib.vertices[3 * index.vertex_index + 1],
                            (float_t)attrib.vertices[3 * index.vertex_index + 2]
                    };

                    if constexpr (std::is_same<Vertices::Mesh3DVertex, T>::value) {
                        vertex.uv = {
                                attrib.texcoords[2 * index.texcoord_index + 0],
                                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                        };

                        vertex.norm = {
                                attrib.normals[3 * index.normal_index + 0],
                                attrib.normals[3 * index.normal_index + 1],
                                attrib.normals[3 * index.normal_index + 2]
                        };

                        vertex.tang = { 0, 0, 0 };
                    };

                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                        vertices.push_back(vertex);
                    }

                    indices.push_back(uniqueVertices[vertex]);
                }

                source.emplace_back(Shape<T> { shape.name, indices, vertices });
            }
            return source;
        }

        template<typename T> std::vector<Types::Mesh*> Load(const std::string& path, bool withIndices) {
            auto meshes = std::vector<Types::Mesh*>();

            auto shapes = LoadSourceWithIndices<typename T::VertexType>(path);

            for (const auto [name, indices, vertices] : shapes) {
                auto *mesh = Memory::MeshAllocator::Allocate<T>();
                mesh->SetGeometryName(name);
                mesh->SetMaterial(new Types::Material());

                if (withIndices) {
                    mesh->SetVertexArray(vertices);
                    mesh->SetIndexArray(indices);
                } else {
                    auto rawVertices = std::vector<typename T::VertexType>();

                    for (const auto& index : indices)
                        rawVertices.emplace_back(vertices[index]);

                    mesh->SetVertexArray(rawVertices);
                }

                meshes.push_back(mesh);
            }

            return meshes;
        }
    };
}

#endif //GAMEENGINE_OBJLOADER_H
