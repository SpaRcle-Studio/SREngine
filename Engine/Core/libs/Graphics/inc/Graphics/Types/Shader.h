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
#include <Graphics/Loaders/SRSL.h>
#include <Graphics/Memory/ShaderProgramManager.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class Render;
    class RenderContext;
    class Environment;
}

namespace SR_GTYPES_NS {
    class Shader;

    class Shader : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
        using ShaderProgram = int32_t;
    private:
        Shader();
        ~Shader() override;

    public:
        static Shader* Load(const SR_UTILS_NS::Path& rawPath);

        ShaderBindResult Use() noexcept;

        bool Init();
        void UnUse() noexcept;
        bool InitUBOBlock();
        bool Flush() const;
        void FlushSamplers();
        void FlushConstants();
        void FreeVideoMemory() override;

    public:
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_DEPRECATED SR_NODISCARD int32_t GetID();
        SR_NODISCARD int32_t GetId() noexcept;
        SR_NODISCARD ShaderProgram GetVirtualProgram() const noexcept { return m_shaderProgram; }
        SR_NODISCARD bool Ready() const;
        SR_NODISCARD uint64_t GetUBOBlockSize() const;
        SR_NODISCARD uint32_t GetSamplersCount() const;
        SR_NODISCARD ShaderProperties GetProperties();
        SR_NODISCARD bool IsBlendEnabled() const;
        SR_NODISCARD bool IsAvailable() const;
        SR_NODISCARD SR_SRSL_NS::ShaderType GetType() const noexcept;

    public:
        template<bool constant, typename T> void SetValue(uint64_t hashId, const T* v) noexcept {
            if (!IsLoaded()) {
                return;
            }

            if constexpr (constant) {
                m_constBlock.SetField(hashId, v);
            }
            else {
                m_uniformBlock.SetField(hashId, v);
            }
        }

        void SR_FASTCALL SetBool(uint64_t hashId, bool v) noexcept;
        void SR_FASTCALL SetFloat(uint64_t hashId, float_t v) noexcept;
        void SR_FASTCALL SetInt(uint64_t hashId, int32_t v) noexcept;
        void SR_FASTCALL SetMat4(uint64_t hashId, const SR_MATH_NS::Matrix4x4& v) noexcept;
        void SR_FASTCALL SetVec4(uint64_t hashId, const SR_MATH_NS::FVector4& v) noexcept;
        void SR_FASTCALL SetVec3(uint64_t hashId, const SR_MATH_NS::FVector3& v) noexcept;
        void SR_FASTCALL SetVec2(uint64_t hashId, const SR_MATH_NS::FVector2& v) noexcept;
        void SR_FASTCALL SetIVec2(uint64_t hashId, const SR_MATH_NS::IVector2& v) noexcept;

        void SR_FASTCALL SetConstBool(uint64_t hashId, bool v) noexcept;
        void SR_FASTCALL SetConstFloat(uint64_t hashId, float_t v) noexcept;
        void SR_FASTCALL SetConstInt(uint64_t hashId, int32_t v) noexcept;
        void SR_FASTCALL SetConstMat4(uint64_t hashId, const SR_MATH_NS::Matrix4x4& v) noexcept;
        void SR_FASTCALL SetConstVec4(uint64_t hashId, const SR_MATH_NS::FVector4& v) noexcept;
        void SR_FASTCALL SetConstVec3(uint64_t hashId, const SR_MATH_NS::FVector3& v) noexcept;
        void SR_FASTCALL SetConstVec2(uint64_t hashId, const SR_MATH_NS::FVector2& v) noexcept;
        void SR_FASTCALL SetConstIVec2(uint64_t hashId, const SR_MATH_NS::IVector2& v) noexcept;

        void SR_FASTCALL SetSampler2D(const std::string& name, Texture* sampler) noexcept;
        void SR_FASTCALL SetSamplerCube(uint64_t hashId, int32_t sampler) noexcept;
        void SR_FASTCALL SetSampler2D(uint64_t hashId, Texture* sampler) noexcept;
        void SR_FASTCALL SetSampler2D(uint64_t hashId, int32_t sampler) noexcept;

    protected:
        bool IsAllowedToRevive() const override;
        void ReviveResource() override;

        bool Load() override;
        bool Unload() override;

        void OnReloadDone() override;

    private:
        void SetSampler(uint64_t hashId, int32_t sampler) noexcept;

    private:
        Memory::ShaderProgramManager& m_manager;

        ShaderProgram m_shaderProgram = SR_ID_INVALID;

        std::atomic<bool> m_hasErrors = false;

        bool m_isRegistered = false;

        SRShaderCreateInfo m_shaderCreateInfo = {};

        Memory::ShaderUBOBlock m_uniformBlock;
        Memory::ShaderUBOBlock m_constBlock;
        ShaderSamplers m_samplers;
        ShaderProperties m_properties;

        SR_SRSL_NS::ShaderType m_type = SR_SRSL_NS::ShaderType::Unknown;

    };
}

#endif //GAMEENGINE_SHADER_H
