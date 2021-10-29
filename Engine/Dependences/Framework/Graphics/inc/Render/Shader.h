//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <Environment/Environment.h>
#include <glm/glm.hpp>
#include <iostream>
#include <string>
#include <map>
#include <Debug.h>
#include <macros.h>

#include <Types/Vertices.h>
#include <Types/Uniforms.h>

namespace Framework::Graphics {
    typedef int ShaderFlags;

    /*
       0 - binding
       1 - type
       2 - ubo size
    */
    typedef std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>> UBOInfos;

    typedef std::vector<std::pair<Vertices::Attribute, size_t>> VertexAttributes;
    typedef std::vector<SR_VERTEX_DESCRIPTION> VertexDescriptions;

    class Render;

    class Shader {
    private:
        ~Shader() = default;
    public:
        Shader(Render* render, const std::string& name);
        Shader(Shader&) = delete;
    public:
        typedef enum {
            Geometry = 0,
            Skybox = 1,
            Transparent = 2,
            DebugWireframe = 3,
        } StandardID;
        typedef enum {
            None         = 0,
            Diffuse      = 1 << 0,
            Normal       = 1 << 1,
            Specular     = 1 << 2,
            Glossiness   = 1 << 3,
            Alpha        = 1 << 4,
            ForwardLight = 1 << 5,
            GBuffer      = 1 << 6,
            MAX = Diffuse | Normal | Specular | Glossiness | Alpha | ForwardLight | GBuffer
        } Flags;
    private:
        SR_SHADER_PROGRAM     m_shaderProgram        = SR_NULL_SHADER;
        void*                 m_shaderTempData       = nullptr;

        bool                  m_isLink               = false;
        bool                  m_isCompile            = false;
        bool                  m_isError              = false;
        bool                  m_isInit               = false;
    private:
        inline static Shader* g_currentShader        = nullptr;
        inline static Shader* g_stdGeometry          = nullptr;
    private: // For vulkan
        SRShaderCreateInfo    m_shaderCreateInfo     = {};
        VertexAttributes      m_verticesAttributes   = {};
        VertexDescriptions    m_verticesDescription  = {};

        int32_t*              m_sharedUniforms       = nullptr;
        uint32_t              m_countSharedUniforms  = 0;
        int32_t               m_fbo                  = -1;

        UBOInfos              m_uniformsInfo         = {};
    private:
        Environment*          m_env                  = nullptr;
        Render*               m_render               = nullptr;
        std::string           m_name                 = "Unnamed";
        std::string           m_path                 = "Unknown";
    private:
        bool Init();
        bool Link();
        bool Compile();
    public:
        SR_FORCE_INLINE static Shader* GetCurrentShader() { return g_currentShader; }
        SR_FORCE_INLINE static void UnUseShaders() {
            Environment::Get()->UnUseShader();
            g_currentShader = nullptr;
        }

        /**
         * шейдер будет загружен в соответствии с данными в /Shaders/CreateInfo.xml
         * name - уникальное имя этого шейдера из конфига
         * */
        static Shader* Load(Render* render, const std::string& name);

        [[nodiscard]] SR_FORCE_INLINE static Shader* GetDefaultGeometryShader() noexcept {
        #ifndef SR_RELEASE
            if (!g_stdGeometry)
                Helper::Debug::Error("Shader::GetDefaultGeometryShader() : shader is nullptr!");
        #endif
            return g_stdGeometry;
        }
        static bool SetStandardGeometryShader(Shader* shader) noexcept;
    public:
        [[nodiscard]] SR_FORCE_INLINE int32_t GetID() {
            if (!m_isInit) {
                if (m_isError)
                    return false;

                if (!this->Init()) {
                    Helper::Debug::Error("Shader::GetID() : failed initialize shader!");
                    this->m_isError = true;
                    return -1;
                }
                this->m_isInit = true;
            }

            return m_shaderProgram;
        }
        [[nodiscard]] SR_FORCE_INLINE std::string GetName() const noexcept { return m_name; }
        [[nodiscard]] SR_FORCE_INLINE int32_t GetUBO(const uint32_t& index) const {
            if (index >= m_countSharedUniforms) {
                Helper::Debug::Error("Shader::GetUBO() : index out of range! \n\tCount uniforms: " +
                    std::to_string(m_countSharedUniforms) + "\n\tIndex: " + std::to_string(index));
                return -1;
            }
            return m_sharedUniforms[index];
        }
    public:
        [[nodiscard]] SR_FORCE_INLINE bool Complete() const noexcept { return m_isInit; }
        bool Use() noexcept;
        ///\warning Call only from OpenGL context!
        void Free();
        bool SetVertex(
                const std::vector<SR_VERTEX_DESCRIPTION>& descriptions,
                const std::vector<std::pair<Vertices::Attribute, size_t>>& attributes);

        /*
         * 0 - binding
         * 1 - type
         * 2 - ubo size
         */
        bool SetUniforms(const std::vector<std::pair<std::pair<uint32_t, UBOType>, uint64_t>>& uniforms);
        bool SetCreateInfo(SRShaderCreateInfo shaderCreateInfo);

        void CopyVertexAndUniformsInfo(const Shader* source);
    public:
        SR_FORCE_INLINE void SetUBO(const uint32_t& binding, void* data) {

        }

        SR_FORCE_INLINE void SetBool(const char* name, const bool& v)         const noexcept {
            //m_env->SetBoolOfLocation(this->m_fields.find(name)->second, v);
            //m_env->SetBool(m_ID, name, v);
            m_env->SetBool(this->m_shaderProgram, name, v);
        }
        SR_FORCE_INLINE void SetFloat(const char* name, const float& v)       const noexcept {
            //m_env->SetFloatOfLocation(this->m_fields.find(name)->second, v);
            //m_env->SetFloat(m_ID, name, v);
            m_env->SetFloat(this->m_shaderProgram, name, v);
        }
        SR_FORCE_INLINE void SetInt(const char* name, const int& v)            const noexcept {
            //m_env->SetIntOfLocation(m_fields.find(name)->second, v);
           // m_env->SetInt(m_ID, name, v);
            m_env->SetInt(this->m_shaderProgram, name, v);
        }
        SR_FORCE_INLINE void SetMat4(const char* name, const glm::mat4& v)    const noexcept {
            //m_env->SetMat4OfLocation(this->m_fields.find(name)->second, v);
           //m_env->SetMat4(m_ID, name, v);
            m_env->SetMat4(this->m_shaderProgram, name, v);
        }
        //SR_FORCE_INLINE void SetVec4(const char* name, const glm::vec4& v)    const noexcept {
            //m_env->SetVec4(m_ID, name, v);
        //} // TODO
        SR_FORCE_INLINE void SetVec3(const char* name, const glm::vec3& v)    const noexcept {
            //m_env->SetVec3OfLocation(this->m_fields.find(name)->second, v);
           // m_env->SetVec3(m_ID, name, v);
            m_env->SetVec3(this->m_shaderProgram, name, v);
        }
        //SR_FORCE_INLINE void SetVec2(const char* name, const glm::vec2& v)    const noexcept { m_env->SetVec2(m_ID, name, v); }
        SR_FORCE_INLINE void SetIVec2(const char* name, const glm::ivec2& v)  const noexcept {
            //m_env->SetIVec2OfLocation(this->m_fields.find(name)->second, v);
            //m_env->SetIVec2(m_ID, name, v);
            m_env->SetIVec2(this->m_shaderProgram, name, v);
        }
    };

    static std::string ShaderFlagsToString(Shader::Flags flags) {
        switch (flags) {
            case Shader::Flags::None:         return "None";
            case Shader::Flags::Diffuse:      return "Diffuse";
            case Shader::Flags::Normal:       return "Normal";
            case Shader::Flags::Specular:     return "Specular";
            case Shader::Flags::Glossiness:   return "Glossiness";
            case Shader::Flags::Alpha:        return "Alpha";
            case Shader::Flags::ForwardLight: return "ForwardLight";
            case Shader::Flags::GBuffer:      return "GBuffer";
            case Shader::Flags::MAX:          return "Max";
            default:
                Helper::Debug::Error("Graphics::ShaderFlagsToString() : unknown flag!");
                return std::string();
        }
    }
}

#endif //GAMEENGINE_SHADER_H
