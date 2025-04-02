

# File ISamplersPass.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Pass**](dir_35fe2922dafa05ba0688834fb0253db8.md) **>** [**ISamplersPass.h**](ISamplersPass_8h.md)

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
            SR_GTYPES_NS::Texture* pTexture = nullptr;
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


