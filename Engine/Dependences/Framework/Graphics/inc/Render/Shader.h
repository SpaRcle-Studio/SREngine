//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <Environment/Environment.h>
#include <glm/glm.hpp>
#include <string>
#include <Debug.h>

namespace Framework::Graphics {
    class Render;

    class Shader {
    private:
        ~Shader() = default;
    public:
        Shader(Render* render, const std::string& name);
        Shader(Shader&) = delete;
    private:
        unsigned int                m_ID           = 0;
        unsigned int                m_fragment     = 0;
        unsigned int                m_vertex       = 0;

        bool                        m_isLink       = false;
        bool                        m_isCompile    = false;
        bool                        m_isError      = false;
        bool                        m_isInit       = false;
    private:
        inline static Shader*       g_stdGeometry  = nullptr;
    private:
        Environment*                m_env          = nullptr;
        Render*                     m_render       = nullptr;
        std::string                 m_name         = "Unnamed";
    private:
        bool Link();
        bool Compile();
    public:
        static Shader* GetStandartGeometryShader() noexcept;
        static bool SetStandartGeometryShader(Shader* shader) noexcept;
    public:
        bool Use();
        bool Init();
        ///\warning Call only from OpenGL context!
        void Free();
    public:
        void SetBool(const std::string& name, bool v)       const noexcept;
        void SetFloat(const std::string& name, float v)     const noexcept;
        void SetInt(const std::string& name, int v)         const noexcept;
        void SetMat4(const std::string& name, glm::mat4 v)  const noexcept;
        void SetVec4(const std::string& name, glm::vec4 v)  const noexcept;
        void SetVec3(const std::string& name, glm::vec3 v)  const noexcept;
        void SetVec2(const std::string& name, glm::vec2 v)  const noexcept;
    };
}

#endif //GAMEENGINE_SHADER_H
