//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <Types/Vertices.h>
#include <Types/Uniforms.h>

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/ResourceManager/IResource.h>

#include <Memory/ShaderUBOBlock.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class Render;
    class Shader;
    class Environment;

    class Shader : public SR_UTILS_NS::IResource {
    public:
        Shader();

    private:
        ~Shader() override;

    public:
        static constexpr uint64_t MODEL_MATRIX = SR_COMPILE_TIME_CRC32_STR("MODEL_MATRIX");
        static constexpr uint64_t VIEW_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_MATRIX");
        static constexpr uint64_t VIEW_NO_TRANSLATE_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_NO_TRANSLATE_MATRIX");
        static constexpr uint64_t PROJECTION_MATRIX = SR_COMPILE_TIME_CRC32_STR("PROJECTION_MATRIX");
        static constexpr uint64_t TIME = SR_COMPILE_TIME_CRC32_STR("TIME");
        static constexpr uint64_t SKYBOX_DIFFUSE = SR_COMPILE_TIME_CRC32_STR("SKYBOX_DIFFUSE");
        static constexpr uint64_t DEPTH_ATTACHMENT = SR_COMPILE_TIME_CRC32_STR("DEPTH_ATTACHMENT");

        static constexpr std::array<uint64_t, 8> COLOR_ATTACHMENTS = {
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_0"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_1"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_2"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_3"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_4"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_5"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_6"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_7")
        };

    private:
        bool Link();
        bool Compile();

    public:
        bool Init();

        static Shader* Load(const SR_UTILS_NS::Path& rawPath);

    public:
        //SR_NODISCARD SR_FORCE_INLINE std::string GetPath() const { return m_path; }
        SR_NODISCARD SR_FORCE_INLINE Render* GetRender() const { return m_render; }
        //SR_NODISCARD SR_FORCE_INLINE std::string GetName() const { return m_name; }
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        //SR_NODISCARD int32_t GetUBO(const uint32_t& index) const;
        SR_NODISCARD int32_t GetID();
        SR_NODISCARD bool Ready() const;
        SR_NODISCARD uint64_t GetUBOBlockSize() const;
        SR_NODISCARD uint32_t GetSamplersCount() const;
        SR_NODISCARD ShaderProperties GetProperties();

    public:
        SR_NODISCARD SR_FORCE_INLINE bool Complete() const { return m_isInit; }

        bool Use() noexcept;
        void UnUse() noexcept;
        bool InitUBOBlock();
        bool Flush() const;
        void FreeVideoMemory();
        bool Reload() override;

        //bool SetVertex(const VertexDescriptions& descriptions, const VertexAttributes& attributes);

        /**
         * 0 - binding
         * 1 - type
         * 2 - ubo size
         */
        //bool SetUniforms(const UBOInfo& uniforms);
        //bool SetCreateInfo(SRShaderCreateInfo shaderCreateInfo);

    public:
        template<typename T, bool shared = false> void SetValue(uint64_t hashId, const T& v) noexcept {
            if (!IsLoaded()) {
                return;
            }

            if constexpr (shared) {
                //m_uniformSharedBlock.SetField(hashId, &v);
            }
            else {
                m_uniformBlock.SetField(hashId, &v);
            }
        }

        void SetBool(uint64_t hashId, const bool& v) noexcept;
        void SetFloat(uint64_t hashId, const float& v) noexcept;
        void SetInt(uint64_t hashId, const int& v) noexcept;
        void SetMat4(uint64_t hashId, const glm::mat4& v) noexcept;
        void SetVec4(uint64_t hashId, const glm::vec4& v) noexcept;
        void SetVec3(uint64_t hashId, const glm::vec3& v) noexcept;
        void SetVec2(uint64_t hashId, const glm::vec2& v) noexcept;
        void SetIVec2(uint64_t hashId, const glm::ivec2& v) noexcept;
        void SetSampler2D(const std::string& name, Types::Texture* sampler) noexcept;
        void SetSamplerCube(uint64_t hashId, int32_t sampler) noexcept;
        void SetSampler2D(uint64_t hashId, Types::Texture* sampler) noexcept;
        void SetSampler2D(uint64_t hashId, int32_t sampler) noexcept;

    private:
        void SetSampler(uint64_t hashId, int32_t sampler) noexcept;

    protected:
        bool Load() override;
        bool Unload() override;

    private:
        SR_SHADER_PROGRAM      m_shaderProgram        = SR_NULL_SHADER;
        void*                  m_shaderTempData       = nullptr;

        std::atomic<bool>      m_isLink               = false;
        std::atomic<bool>      m_isCompile            = false;
        std::atomic<bool>      m_hasErrors            = false;
        std::atomic<bool>      m_isInit               = false;

    private: // For vulkan
        SRShaderCreateInfo     m_shaderCreateInfo     = {};

        int32_t                m_fbo                  = SR_ID_INVALID;

        Memory::ShaderUBOBlock m_uniformBlock         = Memory::ShaderUBOBlock();
        ShaderSamplers         m_samplers             = ShaderSamplers();
        ShaderProperties       m_properties           = ShaderProperties();

    private:
        Render*                m_render               = nullptr;

    };
}

#endif //GAMEENGINE_SHADER_H
