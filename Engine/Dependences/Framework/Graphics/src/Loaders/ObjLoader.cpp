//
// Created by Nikita on 17.11.2020.
//

#include "Loaders/ObjLoader.h"

#include <Types/Mesh.h>
#include <Debug.h>
#include <Environment/Vertex.h>
#include <FileSystem/FileSystem.h>
#include <ResourceManager/ResourceManager.h>
#include <Utils/StringUtils.h>

#include <tinyobjloader/tiny_obj_loader.cc>

#include <Render/Shader.h>
#include <Types/Material.h>

using namespace Framework::Helper;

namespace Framework::Graphics {
    std::vector<Mesh *> ObjLoader::LoadWithIndices(const std::string &path) {
        std::vector<Mesh*> meshes = std::vector<Mesh *>();
        m_mutex.lock();

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, path.c_str())) {
            Helper::Debug::Error("ObjLoader::LoadWithIndices() : failed open file!\n\tWarn: " + warn + "\n\tError: " + err);
            m_mutex.unlock();
            return {};
        }

        for (const auto& shape : shapes) {
            Mesh* mesh = new Mesh(nullptr, new Material(nullptr, nullptr, nullptr, nullptr), shape.name);

            auto vertices = std::vector<Vertex>();
            auto indices = std::vector<unsigned int>();

            std::unordered_map<Vertex, uint32_t> uniqueVertices{};

            for (const auto& index : shape.mesh.indices) {
                Vertex vertex = {};

                vertex.position = {
                        attrib.vertices[3 * index.vertex_index + 0],
                        attrib.vertices[3 * index.vertex_index + 1],
                        attrib.vertices[3 * index.vertex_index + 2]
                };

                vertex.texCoords = {
                        //attrib.texcoords[2 * index.texcoord_index + 0],
                        //attrib.texcoords[2 * index.texcoord_index + 1]

                               attrib.texcoords[2 * index.texcoord_index + 0],
                        1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
                };

                vertex.color = { 1.0f, 1.0f, 1.0f };

                // TODO: CHECK CORRECTLY!
                vertex.normal = {
                        attrib.normals[3 * index.normal_index + 0],
                        attrib.normals[3 * index.normal_index + 1],
                        attrib.normals[3 * index.normal_index + 2]
                };
                vertex.tangent = { 0, 0, 0 };

                //============================================

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(uniqueVertices[vertex]);
            }

            mesh->SetVertexArray(vertices);
            mesh->SetIndexArray(indices);

            meshes.push_back(mesh);
        }

        m_mutex.unlock();
        return meshes;
    }

    std::vector<Mesh *> Framework::Graphics::ObjLoader::Load(const std::string& path) {
        std::vector<Mesh*> meshes = std::vector<Mesh *>();

        m_mutex.lock();

        m_file_name = path; //ResourceManager::GetResourcesFolder() + "/Models/"+path+".obj";

        if (Debug::GetLevel() >= Debug::Level::High)
            Debug::Log("ObjLoader::Load() : loading \""+path+"\" obj model...");

        {
            m_temp_meshes.clear();
            Clear();

            char* data = FileSystem::Load(m_file_name);
            if (!data) {
                Debug::Error("ObjLoader::Load() : failed read file!");
                m_mutex.unlock();
                return std::vector<Mesh*>();
            }


            ProcessFile(data);
            if (m_temp_meshes.empty()) {
                Debug::Error("ObjLoader::Load() : Failed load model!\n\tPath : " + m_file_name);
                Clear();
            }

            delete[] data;
        }

        meshes = m_temp_meshes;

        m_mutex.unlock();

        return meshes;
    }

    void ObjLoader::AddMesh() {
        if (!m_temp_vertexes.empty()) {
            Mesh* mesh = new Mesh(nullptr, new Material(nullptr, nullptr, nullptr, nullptr), ObjLoader::m_current_object);
            //Mesh* mesh = new Mesh(Shader::GetDefaultGeometryShader(), new Material(nullptr, nullptr, nullptr, nullptr), ObjLoader::m_current_object);
            mesh->GetMaterial()->SetMesh(mesh);
            mesh->SetVertexArray(m_temp_vertexes);
            m_temp_meshes.push_back(mesh);
        }
        m_temp_vertexes.clear();
        m_temp_indices.clear();
    }

    void ObjLoader::Clear() {
        m_current_object.clear();

        m_pos_vertex.clear();
        m_pos_texture.clear();
        m_pos_normal.clear();

        m_temp_vertexes.clear();
        m_temp_indices.clear();

        m_line_number = 0;
    }

    void ObjLoader::ProcessFace(char **elems) {
        glm::vec3 face;
        glm::vec3 uv;
        glm::vec3 norm_index;

        unsigned char count = StringUtils::MathCount(elems[0], '/');

        float* indexes_1 = StringUtils::SplitFloats(elems[0], '/', 0, count + 1);
        float* indexes_2 = StringUtils::SplitFloats(elems[1], '/', 0, count + 1);
        float* indexes_3 = StringUtils::SplitFloats(elems[2], '/', 0, count + 1);

        face.x = indexes_1[0];
        face.y = indexes_2[0];
        face.z = indexes_3[0];

        if (count > 0) { // Texture coords
            uv.x = indexes_1[1];
            uv.y = indexes_2[1];
            uv.z = indexes_3[1];
        }
        // And
        if (count > 1) { // Normal coords
            norm_index.x = indexes_1[2];
            norm_index.y = indexes_2[2];
            norm_index.z = indexes_3[2];
        }

        {
            delete[] indexes_1;
            delete[] indexes_2;
            delete[] indexes_3;
        }

        switch (count) {
            case 1: // With texture
                m_temp_vertexes.push_back({ { m_pos_vertex[face.x - 1.f] }, m_pos_texture[uv.x - 1.f], {1,1,1}, {0,0,0} }); //z
                m_temp_vertexes.push_back({ { m_pos_vertex[face.y - 1.f] }, m_pos_texture[uv.y - 1.f], {1,1,1}, {0,0,0} }); //x
                m_temp_vertexes.push_back({ { m_pos_vertex[face.z - 1.f] }, m_pos_texture[uv.z - 1.f], {1,1,1}, {0,0,0} }); //y
                break;
            case 2: // With normal
            {
                //!====================================[TANGENT]========================================
                glm::vec3 edge1 = m_pos_vertex[face.y - 1.f] - m_pos_vertex[face.x - 1.f];    // pos2 - pos1
                glm::vec3 edge2 = m_pos_vertex[face.z - 1.f] - m_pos_vertex[face.x - 1.f];    // pos3 - pos1
                glm::vec2 deltaUV1 = m_pos_texture[uv.y - 1.f] - m_pos_texture[uv.x - 1.f];   // uv2 - uv1
                glm::vec2 deltaUV2 = m_pos_texture[uv.z - 1.f] - m_pos_texture[uv.x - 1.f];   // uv3 - uv1

                float f = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV2.x * deltaUV1.y);

                float tan_x = f * (deltaUV2.y * edge1.x - deltaUV1.y * edge2.x);
                float tan_y = f * (deltaUV2.y * edge1.y - deltaUV1.y * edge2.y);
                float tan_z = f * (deltaUV2.y * edge1.z - deltaUV1.y * edge2.z);
                //!====================================[TANGENT]========================================

                m_temp_vertexes.push_back(
                        {{m_pos_vertex[face.x - 1.f]}, m_pos_texture[uv.x - 1.f], m_pos_normal[norm_index.x - 1],
                         {1,1,1},
                         {tan_x, tan_y, tan_z}}); //z
                m_temp_vertexes.push_back(
                        {{m_pos_vertex[face.y - 1.f]}, m_pos_texture[uv.y - 1.f], m_pos_normal[norm_index.y - 1],
                         {1,1,1},
                         {tan_x, tan_y, tan_z}}); //x
                m_temp_vertexes.push_back(
                        {{m_pos_vertex[face.z - 1.f]}, m_pos_texture[uv.z - 1.f], m_pos_normal[norm_index.z - 1],
                         {1,1,1},
                         {tan_x, tan_y, tan_z}}); //y
                break;
            }
            default: break;
        }

        /*
        switch (count) {
            case 1: // With texture
                m_temp_vertexes.push_back({ { m_pos_vertex[face.x - 1.f] }, m_pos_texture[uv.x - 1.f], {0,0,0}, {0,0,0} }); //z
                m_temp_vertexes.push_back({ { m_pos_vertex[face.y - 1.f] }, m_pos_texture[uv.y - 1.f], {0,0,0}, {0,0,0} }); //x
                m_temp_vertexes.push_back({ { m_pos_vertex[face.z - 1.f] }, m_pos_texture[uv.z - 1.f], {0,0,0}, {0,0,0} }); //y
                break;
            case 2: // With normal
                //TODO: todo math tangents
                m_temp_vertexes.push_back({ { m_pos_vertex[face.x - 1.f] }, m_pos_texture[uv.x - 1.f], {0,0,0}, {0,0,0} }); //z
                m_temp_vertexes.push_back({ { m_pos_vertex[face.y - 1.f] }, m_pos_texture[uv.y - 1.f], {0,0,0}, {0,0,0} }); //x
                m_temp_vertexes.push_back({ { m_pos_vertex[face.z - 1.f] }, m_pos_texture[uv.z - 1.f], {0,0,0}, {0,0,0} }); //y
                break;
            default: break;
        }*/
    }

    bool ObjLoader::ProcessLine(char *line) {
        m_line_number++;

        unsigned long len = StringUtils::FastStrLen(line);
        if (len > 1) {
            switch (line[0]) {
                case '#':
                    break; // Comment
                case 'o':
                    if (!m_current_object.empty()) {
                        AddMesh();
                    }
                    m_current_object = std::string(line).substr(2);
                    break; // Object
                case 'g':
                    if (!m_current_object.empty()) {
                        AddMesh();
                    }
                    m_current_object = std::string(line).substr(2);
                    break;
                case 'v':
                    switch (line[1]) {
                        case ' ': {
                            m_pos_vertex.push_back(StringUtils::MakeVec3FromString(line, ' ', 2 + ((line[2] == ' ')))); //TODO: Warning! Check another project if mesh not correct!
                            break; // Vertex
                        }
                        case 't': {
                            m_pos_texture.push_back(StringUtils::MakeVec2FromString(line, ' ', 2 + ((line[2] == ' ')))); //TODO: Warning! Check another project if mesh not correct!
                            break; // Texture coord
                        }
                        case 'n':
                            m_pos_normal.push_back(StringUtils::MakeVec3FromString(line, ' ', 3));
                            break; // Normal
                        default: break;
                    }
                    break;
                case 'f': {
                    if (StringUtils::MathCount(line, ' ') > 3)
                    {
                        Debug::Error("ObjLoader::ProcessLine() : model is not triangulate!");
                        return false;
                    }

                    char** elems = StringUtils::Split(line, ' ', 2, 3);

                    ProcessFace(elems);

                    delete[] elems[0];
                    delete[] elems[1];
                    delete[] elems[2];
                    delete[] elems;
                    break; // Face
                }
                default: break;
            }
        }
        return true;
    }

    bool ObjLoader::ProcessFile(const char *data) {
        long len = strlen(data), count = 0, last = 0;
        long line_number = 0;
        for (int i = 0; i < len; i++) {
            count++;
            if (data[i] == '\n' || i + 1 == len) {
                line_number++;

                char* line = new char[count + 1]; strcpy(line, "");

                strncat(line, data + last, i + 1 == len ? count : count - 1);
                last = i + 1;

                if (!ProcessLine(line))
                {
                    return false;
                    delete[] line;
                }

                delete[] line;

                count = 0;
            }
        }
        AddMesh();
        return true;
    }


}
