//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_SHADER_H
#define GAMEENGINE_SHADER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/ResourceManager/IResource.h>

#include <Graphics/Types/Vertices.h>
#include <Graphics/Types/Uniforms.h>
#include <Graphics/Memory/ShaderUBOBlock.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class Render;
    class RenderContext;
    class Environment;
}

namespace SR_GRAPH_NS::Types {
    class Shader;

    class Shader : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
        using ShaderProgram = int32_t;
        using RenderContextPtr = SR_HTYPES_NS::SafePtr<RenderContext>;
    private:
        Shader();
        ~Shader() override;

    public:
        static Shader* Load(const SR_UTILS_NS::Path& rawPath);

        bool Init();
        bool Use() noexcept;
        void UnUse() noexcept;
        bool InitUBOBlock();
        bool Flush() const;
        void FreeVideoMemory() override;

    public:
        SR_NODISCARD SR_FORCE_INLINE RenderContextPtr GetContext() const { return m_context; }
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_DEPRECATED SR_NODISCARD int32_t GetID();
        SR_NODISCARD int32_t GetId() noexcept;
        SR_NODISCARD bool Ready() const;
        SR_NODISCARD uint64_t GetUBOBlockSize() const;
        SR_NODISCARD uint32_t GetSamplersCount() const;
        SR_NODISCARD ShaderProperties GetProperties();
        SR_NODISCARD bool IsBlendEnabled() const;
        SR_NODISCARD SRSL::ShaderType GetType() const noexcept { return m_type; }

    public:
        template<typename T, bool shared = false> void SetValue(uint64_t hashId, const T& v) noexcept {
            if (!IsLoaded()) {
                return;
            }

            m_uniformBlock.SetField(hashId, &v);
        }

        void SR_FASTCALL SetBool(uint64_t hashId, const bool& v) noexcept;
        void SR_FASTCALL SetFloat(uint64_t hashId, const float& v) noexcept;
        void SR_FASTCALL SetInt(uint64_t hashId, const int& v) noexcept;
        void SR_FASTCALL SetMat4(uint64_t hashId, const glm::mat4& v) noexcept;
        void SR_FASTCALL SetMat4(uint64_t hashId, const SR_MATH_NS::Matrix4x4& v) noexcept;
        void SR_FASTCALL SetVec4(uint64_t hashId, const glm::vec4& v) noexcept;
        void SR_FASTCALL SetVec3(uint64_t hashId, const glm::vec3& v) noexcept;
        void SR_FASTCALL SetVec2(uint64_t hashId, const glm::vec2& v) noexcept;
        void SR_FASTCALL SetIVec2(uint64_t hashId, const glm::ivec2& v) noexcept;
        void SR_FASTCALL SetSampler2D(const std::string& name, Types::Texture* sampler) noexcept;
        void SR_FASTCALL SetSamplerCube(uint64_t hashId, int32_t sampler) noexcept;
        void SR_FASTCALL SetSampler2D(uint64_t hashId, Types::Texture* sampler) noexcept;
        void SR_FASTCALL SetSampler2D(uint64_t hashId, int32_t sampler) noexcept;

    protected:
        bool Load() override;
        bool Unload() override;

        void OnReloadDone() override;

    private:
        void SetSampler(uint64_t hashId, int32_t sampler) noexcept;

    private:
        ShaderProgram          m_shaderProgram        = SR_ID_INVALID;

        std::atomic<bool>      m_hasErrors            = false;
        std::atomic<bool>      m_isInit               = false;

        bool                   m_isRegistered         = false;

        SRShaderCreateInfo     m_shaderCreateInfo     = { };

        Memory::ShaderUBOBlock m_uniformBlock         = Memory::ShaderUBOBlock();
        ShaderSamplers         m_samplers             = ShaderSamplers();
        ShaderProperties       m_properties           = ShaderProperties();

        RenderContextPtr       m_context              = { };

        SRSL::ShaderType       m_type                 = SRSL::ShaderType::Unknown;

    };
}

#endif //GAMEENGINE_SHADER_H
