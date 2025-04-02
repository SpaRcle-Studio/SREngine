

# File Skybox.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Types**](dir_360f2bb59d6258d66f77f97151cde50e.md) **>** [**Skybox.h**](Skybox_8h.md)

[Go to the documentation of this file](Skybox_8h.md)


```C++
//
// Created by Nikita on 20.11.2020.
//

#ifndef SR_ENGINE_GRAPHICS_SKYBOX_H
#define SR_ENGINE_GRAPHICS_SKYBOX_H

#include <Utils/Resources/IResource.h>

#include <Graphics/Memory/IGraphicsResource.h>
#include <Graphics/Loaders/TextureLoader.h>

namespace SR_GTYPES_NS {
    class Shader;

    class Skybox : public SR_UTILS_NS::IResource, public Memory::IGraphicsResource {
    private:
        Skybox();
        ~Skybox() override;

    public:
        static Skybox* Load(const SR_UTILS_NS::Path& path);

    public:
        SR_NODISCARD Shader* GetShader() const noexcept { return m_shader; }
        SR_NODISCARD int32_t GetVBO();
        SR_NODISCARD int32_t GetIBO();
        SR_NODISCARD int32_t GetVirtualUBO() const;

        SR_NODISCARD bool IsAllowedToRevive() const override { return true; }

        void FreeVideoMemory() override;
        void Draw();

        void SetShader(Shader *shader);

        void StartWatch() override;

    protected:
        void OnResourceUpdated(SR_UTILS_NS::ResourceContainer* pContainer, int32_t depth) override;
        uint64_t GetFileHash() const override { return 0; }

    private:
        bool Calculate();

    private:
        Shader* m_shader = nullptr;

        int32_t m_VBO = SR_ID_INVALID;
        int32_t m_IBO = SR_ID_INVALID;

        int32_t m_cubeMap = SR_ID_INVALID;

        int32_t m_virtualUBO = SR_ID_INVALID;
        int32_t m_virtualDescriptor = SR_ID_INVALID;

        uint32_t m_width = 0;
        uint32_t m_height = 0;

        bool m_hasErrors = false;
        bool m_dirtyShader = false;

        Memory::UBOManager& m_uboManager;
        DescriptorManager& m_descriptorManager;

        std::array<TextureData::Ptr, 6> m_data;

    };
}

#endif //SR_ENGINE_GRAPHICS_SKYBOX_H
```


