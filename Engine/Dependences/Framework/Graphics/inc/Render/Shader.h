//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <Environment/Environment.h>
#include <glm/glm.hpp>
#include <string>
#include <Debug.h>
#include <macros.h>

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
        const Environment*          m_env          = nullptr;
        Render*                     m_render       = nullptr;
        std::string                 m_name         = "Unnamed";
    private:
        bool Link();
        bool Compile();
    public:
        [[nodiscard]] SR_FORCE_INLINE static Shader* GetDefaultGeometryShader() noexcept {
            //if (!g_stdGeometry)
            //    Helper::Debug::Error("Shader::GetDefaultGeometryShader() : shader is nullptr!");

            return g_stdGeometry;
        }
        static bool SetStandartGeometryShader(Shader* shader) noexcept;
    public:
        [[nodiscard]] SR_FORCE_INLINE std::string GetName() const noexcept {
            return m_name;
        }
    public:
        bool Use() noexcept;
        bool Init();
        ///\warning Call only from OpenGL context!
        void Free();
    public:
        SR_FORCE_INLINE void SetBool(const char* name, const bool& v)         const noexcept { m_env->SetBool(m_ID, name, v); }
        SR_FORCE_INLINE void SetFloat(const char* name, const float& v)       const noexcept { m_env->SetFloat(m_ID, name, v); }
        SR_FORCE_INLINE void SetInt(const char* name, const int& v)           const noexcept { m_env->SetInt(m_ID, name, v); }
        SR_FORCE_INLINE void SetMat4(const char* name, const glm::mat4& v)    const noexcept { m_env->SetMat4(m_ID, name, v); }
        SR_FORCE_INLINE void SetVec4(const char* name,const glm::vec4& v)    const noexcept { m_env->SetVec4(m_ID, name, v); } // TODO
        SR_FORCE_INLINE void SetVec3(const char* name,const glm::vec3& v)    const noexcept { m_env->SetVec3(m_ID, name, v); }
        SR_FORCE_INLINE void SetVec2(const char* name,const glm::vec2& v)    const noexcept { m_env->SetVec2(m_ID, name, v); }
        SR_FORCE_INLINE void SetIVec2(const char* name,const glm::ivec2& v)  const noexcept { m_env->SetIVec2(m_ID, name, v); }
    };
}

#endif //GAMEENGINE_SHADER_H
