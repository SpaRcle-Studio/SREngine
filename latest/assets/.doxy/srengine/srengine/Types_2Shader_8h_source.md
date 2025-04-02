

# File Shader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Shader.h**](Types_2Shader_8h.md)

[Go to the documentation of this file](Types_2Shader_8h.md)


```C++
//
// Created by Nikita on 17.11.2020.
//

#ifndef SR_ENGINE_GRAPHICS_SHADER_H
#define SR_ENGINE_GRAPHICS_SHADER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Resources/IResource.h>
#include <Utils/Math/Rect.h>

#include <Graphics/Types/Vertices.h>
#include <Graphics/Types/Uniforms.h>
#include <Graphics/Memory/ShaderUBOBlock.h>
#include <Graphics/Loaders/SRSL.h>
#include <Graphics/Memory/ShaderProgramManager.h>
#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Memory/UBOManager.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class Render;
    class RenderContext;
}

namespace SR_GTYPES_NS {
    class Shader;

    class Shader : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
        using ShaderProgram = int32_t;
    public:
        using Ptr = Shader*;

    private:
        Shader();
        ~Shader() override;

    public:
        static Shader* Load(const SR_UTILS_NS::Path& rawPath);

        ShaderBindResult Use() noexcept;

        bool Init();
        void UnUse() noexcept;
        //bool InitUBOBlock();
        bool Flush() const;
        void FlushSamplers();
        void FlushConstants();
        void FreeVideoMemory() override;
        void StartWatch() override;

        void AttachDescriptorSets();

        bool BeginSharedUBO();
        void EndSharedUBO();

    public:
        SR_NODISCARD SR_UTILS_NS::Path GetAssociatedPath() const override;
        SR_DEPRECATED SR_NODISCARD int32_t GetID();
        SR_NODISCARD int32_t GetId() noexcept;
        SR_NODISCARD ShaderProgram GetVirtualProgram() const noexcept { return m_shaderProgram; }
        SR_NODISCARD bool Ready() const;
        SR_NODISCARD uint64_t GetUBOBlockSize() const;
        SR_NODISCARD uint32_t GetSamplersCount() const;
        SR_NODISCARD ShaderProperties GetProperties();
        SR_NODISCARD const ShaderSamplers& GetSamplers() const noexcept { return m_samplers; };
        SR_NODISCARD bool IsBlendEnabled() const;
        SR_NODISCARD bool IsAvailable() const;
        SR_NODISCARD bool IsSamplersValid() const;
        SR_NODISCARD bool HasSharedUBO() const noexcept { return m_uniformSharedBlock.Valid(); }
        SR_NODISCARD SR_SRSL_NS::ShaderType GetType() const noexcept;

    public:
        template<bool constant, typename T> void SetValue(uint64_t hashId, const T* v) noexcept {
            if constexpr (constant) {
                m_constBlock.SetField(hashId, v);
            }
            else {
                if (m_sharedUBOMode) SR_UNLIKELY_ATTRIBUTE {
                    m_uniformSharedBlock.SetField(hashId, v);
                }
                else {
                    m_uniformBlock.SetField(hashId, v);
                }
            }
        }

        void SR_FASTCALL SetBool(uint64_t hashId, bool v) noexcept;
        void SR_FASTCALL SetFloat(uint64_t hashId, float_t v) noexcept;
        void SR_FASTCALL SetInt(uint64_t hashId, int32_t v) noexcept;
        void SR_FASTCALL SetMat4(uint64_t hashId, const SR_MATH_NS::Matrix4x4& v) noexcept;
        void SR_FASTCALL SetVec3(uint64_t hashId, const SR_MATH_NS::FVector3& v) noexcept;
        void SR_FASTCALL SetVec4(uint64_t hashId, const SR_MATH_NS::FVector4& v) noexcept;
        void SR_FASTCALL SetRect(uint64_t hashId, const SR_MATH_NS::FRect& v) noexcept;
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

        void SR_FASTCALL SetSampler2D(SR_UTILS_NS::StringAtom name, Texture* sampler) noexcept;
        void SR_FASTCALL SetSampler2D(SR_UTILS_NS::StringAtom name, int32_t sampler) noexcept;
        void SR_FASTCALL SetSamplerCube(SR_UTILS_NS::StringAtom name, int32_t sampler) noexcept;

        void BindSSBO(SR_UTILS_NS::StringAtom name, uint32_t ssbo) noexcept;

        SR_NODISCARD bool HasErrors() const noexcept { return m_hasErrors; }

    protected:
        bool IsAllowedToRevive() const override;
        void ReviveResource() override;

        bool Load() override;
        bool Unload() override;

        void OnReloadDone() override;

        void LoadDefaultSampler(SR_UTILS_NS::StringAtom name);
        void UnloadDefaultSamplers();

    private:
        void SetSampler(SR_UTILS_NS::StringAtom name, int32_t sampler) noexcept;

    private:
        Memory::UBOManager& m_uboManager;
        Memory::ShaderProgramManager& m_manager;

        ShaderProgram m_shaderProgram = SR_ID_INVALID;

        bool m_hasErrors = false;
        bool m_isRegistered = false;
        bool m_sharedUBOMode = false;

        SRShaderCreateInfo m_shaderCreateInfo = { };

        std::pair<int32_t, bool> m_virtualUBO = { SR_ID_INVALID, true };

        std::vector<SR_UTILS_NS::StringAtom> m_includes;
        Memory::ShaderUBOBlock m_uniformBlock;
        Memory::ShaderUBOBlock m_uniformSharedBlock;
        Memory::ShaderUBOBlock m_constBlock;
        ShaderSamplers m_samplers;
        ShaderProperties m_properties;
        SSBOBindings m_ssboBindings;
        std::map<SR_UTILS_NS::StringAtom, Texture*> m_defaultSamplers;

        SR_SRSL_NS::ShaderType m_type = SR_SRSL_NS::ShaderType::Unknown;

    };
}

#endif //SR_ENGINE_GRAPHICS_SHADER_H
```


