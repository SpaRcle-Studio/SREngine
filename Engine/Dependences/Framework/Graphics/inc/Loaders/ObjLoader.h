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
#include <glm/glm.hpp>
#include <Types/Vertices.h>
#include <tinyobjloader/tiny_obj_loader.h>

namespace static_if_detail {
    struct identity {
        template<typename T>
        T operator()(T&& x) const {
            return std::forward<T>(x);
        }
    };

    template<bool Cond>
    struct statement {
        template<typename F>
        void then(const F& f){
            f(identity());
        }

        template<typename F>
        void else_(const F&){}
    };

    template<>
    struct statement<false> {
        template<typename F>
        void then(const F&){}

        template<typename F>
        void else_(const F& f){
            f(identity());
        }
    };
} //end of namespace static_if_detail

template<bool Cond, typename F>
static_if_detail::statement<Cond> static_if(F const& f){
    static_if_detail::statement<Cond> if_;
    if_.then(f);
    return if_;
}

namespace Framework::Graphics::Types{
    class Mesh;
}

namespace Framework::Graphics {
    namespace Vertices {
        struct Mesh3DVertex;
    }

    using namespace Types;
    class ObjLoader {
        ObjLoader()           = delete;
        ObjLoader(ObjLoader&) = delete;
        ~ObjLoader()          = delete;
    private:
        inline static std::vector<Mesh*>			      m_temp_meshes	    = std::vector<Mesh*>();

        inline static std::vector<Vertices::Mesh3DVertex> m_temp_vertexes   = std::vector<Vertices::Mesh3DVertex>();
        inline static std::vector<unsigned int>		      m_temp_indices    = std::vector<unsigned int>();

        inline static std::vector<glm::vec3>		      m_pos_vertex		= std::vector<glm::vec3>();
        inline static std::vector<glm::vec2>		      m_pos_texture		= std::vector<glm::vec2>();
        inline static std::vector<glm::vec3>		      m_pos_normal		= std::vector<glm::vec3>();
    private:
        inline static unsigned long long			      m_line_number		= 0;
        inline static std::string					      m_current_object	= "";

        inline static std::mutex                          m_mutex           = std::mutex();
        inline static std::string					      m_file_name       = "";
    private:
        static void AddMesh();
        static void Clear();
        static void ProcessFace(char** elems);
        static bool ProcessLine(char* line);
        static bool ProcessFile(const char* data);
    public:
        static std::vector<Mesh*> Load(const std::string& path);
        static std::vector<Mesh*> LoadWithIndices(const std::string& path);

        template<typename T> static std::vector<std::pair<std::vector<uint32_t>, std::vector<T>>> LoadSourceWithIndices(const std::string& path) {
            std::vector<std::pair<std::vector<uint32_t>, std::vector<T>>> source = { };

            tinyobj::attrib_t attrib;
            std::vector<tinyobj::shape_t> shapes;
            std::vector<tinyobj::material_t> materials;
            std::string warn, err;

            if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
                Helper::Debug::Error("ObjLoader::LoadSourceWithIndices() : failed open file!\n\tWarn: " + warn + "\n\tError: " + err);
                return {};
            }

            for (const auto& shape : shapes) {
                auto vertices = std::vector<T>();
                auto indices = std::vector<uint32_t>();

                std::unordered_map<T, uint32_t> uniqueVertices {};

                for (const auto& index : shape.mesh.indices) {
                    T vertex = { };

                    vertex.pos = {
                            attrib.vertices[3 * index.vertex_index + 0],
                            attrib.vertices[3 * index.vertex_index + 1],
                            attrib.vertices[3 * index.vertex_index + 2]
                    };

                    static_if<std::is_same<Vertices::Mesh3DVertex, T>::value>([&](auto f){
                        vertex.uv = {
                                attrib.texcoords[2 * index.texcoord_index + 0],
                                1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                        };

                        // TODO: CHECK CORRECTLY!
                        vertex.norm = {
                                attrib.normals[3 * index.normal_index + 0],
                                attrib.normals[3 * index.normal_index + 1],
                                attrib.normals[3 * index.normal_index + 2]
                        };

                        vertex.tang = { 0, 0, 0 };
                    });

                    if (uniqueVertices.count(vertex) == 0) {
                        uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                        vertices.push_back(vertex);
                    }

                    indices.push_back(uniqueVertices[vertex]);
                }

                source.emplace_back(std::pair(indices, vertices));
            }
            return source;
        }
    };
}

#endif //GAMEENGINE_OBJLOADER_H
