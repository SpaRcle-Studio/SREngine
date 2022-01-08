//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <mutex>
#include <ResourceManager/IResource.h>
#include <Environment/Environment.h>
#include <Environment/TextureHelper.h>
#include <macros.h>

namespace Framework::Graphics{
    class TextureLoader;
    class Render;
}

namespace Framework {
    class API;
}

namespace Framework::Graphics::Types {
    using namespace Helper;
    class Texture : public IResource {
        friend class ::Framework::Graphics::TextureLoader;
        friend class ::Framework::API;
    private:
        Texture();
        ~Texture() override;
    private:
        inline static Environment* m_env         = nullptr;

        int32_t                    m_ID          = 0;

        uint32_t                   m_width       = 0;
        uint32_t                   m_height      = 0;

        TextureFormat              m_format      = TextureFormat::Unknown;
        TextureCompression         m_compression = TextureCompression::None;

        uint8_t                    m_mipLevels   = 0;

        bool                       m_alpha       = false;

        uint8_t*                   m_data        = nullptr;

        volatile bool              m_isCalculate = false;
        bool                       m_hasErrors   = false;

        Render*                    m_render      = nullptr;

        std::mutex                 m_mutex       = std::mutex();
        TextureType                m_type        = TextureType::Unknown;
        TextureFilter              m_filter      = TextureFilter::Unknown;
    private:
        bool Calculate();
    public:
        void OnDestroyGameObject();

        void SetRender(Render* render);

        [[nodiscard]] SR_FORCE_INLINE bool IsCalculated() const noexcept { return m_isCalculate; }
        [[nodiscard]] SR_FORCE_INLINE int32_t GetID() noexcept {
            if (IsDestroy()) {
                Debug::Error("Texture::GetID() : texture \"" + GetResourceId() + "\" is destroyed!");
                return -1;
            }

            if (!m_isCalculate)
                if (!Calculate()) {
                    Debug::Error("Texture::GetID() : failed calculating texture!");
                    return -1;
                }

            return m_ID;
        }

        /* Call only from render pool events */
        bool FreeVideoMemory();
    public:
        static Texture* Load(
                const std::string& path,
                TextureFormat format,
                bool autoRemove = false,
                TextureType type = TextureType::Diffuse,
                TextureFilter filter = TextureFilter::NEAREST,
                TextureCompression compression = TextureCompression::None,
                uint8_t mipLevels = 1);
    public:
        bool Destroy() override;
    };
}

#endif //GAMEENGINE_TEXTURE_H
