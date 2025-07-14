

# File ISamplersPass.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pass**](dir_f60d182ad98ca085ac1e9e7ce07e0a4d.md) **>** [**ISamplersPass.h**](ISamplersPass_8h.md)

[Go to the documentation of this file](ISamplersPass_8h.md)


```C++
//
// Created by Monika on 07.05.2024.
//

#ifndef SR_ENGINE_GRAPHICS_I_SAMPLERS_PASS_H
#define SR_ENGINE_GRAPHICS_I_SAMPLERS_PASS_H

#include <Utils/Types/StringAtom.h>

#include <Graphics/Types/Texture.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS {
    class IRenderTechnique;

    class ISamplersPass {
    private:
        struct Sampler : public SR_UTILS_NS::NonCopyable {
            Sampler() = default;
            ~Sampler() override;

            Sampler(Sampler&& other) noexcept;
            Sampler& operator=(Sampler&& other) noexcept;

            uint32_t textureId = SR_ID_INVALID;
            uint32_t fboId = SR_ID_INVALID;
            SR_UTILS_NS::StringAtom id;
            SR_UTILS_NS::StringAtom fboName;
            SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Texture> pTexture;
            uint64_t index = 0;
            bool depth = false;
        };
        using Samplers = std::vector<Sampler>;

    public:
        virtual ~ISamplersPass();

    public:
        void LoadSamplersPass(const SR_XML_NS::Node& passNode);

        virtual void UseSamplers(ShaderUseInfo info);

        SR_NODISCARD bool HasSamplers() const noexcept { return !m_samplers.empty(); }
        SR_NODISCARD bool IsSamplersDirty() const noexcept { return m_dirtySamplers; }

    protected:
        virtual void OnSamplersChanged() { }
        void MarkSamplersDirty() { m_dirtySamplers = true; }
        void PrepareSamplers();
        void SetISamplerRenderTechnique(IRenderTechnique* pTechnique) { m_pTechnique = pTechnique; }

    private:
        bool m_dirtySamplers = true;
        Samplers m_samplers;

        IRenderTechnique* m_pTechnique = nullptr;

    };
}

#endif //SR_ENGINE_GRAPHICS_I_SAMPLERS_PASS_H
```


