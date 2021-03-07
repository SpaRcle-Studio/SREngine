//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_OBJLOADER_H
#define GAMEENGINE_OBJLOADER_H

#include <string>
#include <vector>
#include <mutex>
#include <glm/glm.hpp>

namespace Framework::Graphics::Types{
    class Mesh;
}

namespace Framework::Graphics {
    struct Vertex;

    using namespace Types;
    class ObjLoader {
        ObjLoader()             = delete;
        ObjLoader(ObjLoader&)   = delete;
        ~ObjLoader()            = delete;
    private:
        inline static std::vector<Mesh*>			m_temp_meshes		= std::vector<Mesh*>();

        inline static std::vector<Vertex>			m_temp_vertexes     = std::vector<Vertex>();
        inline static std::vector<unsigned int>		m_temp_indices		= std::vector<unsigned int>();

        inline static std::vector<glm::vec3>		m_pos_vertex		= std::vector<glm::vec3>();
        inline static std::vector<glm::vec2>		m_pos_texture		= std::vector<glm::vec2>();
        inline static std::vector<glm::vec3>		m_pos_normal		= std::vector<glm::vec3>();
    private:
        inline static unsigned long long			m_line_number		= 0;
        inline static std::string					m_current_object	= "";

        inline static std::mutex                    m_mutex             = std::mutex();
        inline static std::string					m_file_name			= "";
    private:
        static void AddMesh();
        static void Clear();
        static void ProcessFace(char** elems);
        static bool ProcessLine(char* line);
        static bool ProcessFile(const char* data);
    public:
        static std::vector<Mesh*> Load(std::string path);
    };
}

#endif //GAMEENGINE_OBJLOADER_H
