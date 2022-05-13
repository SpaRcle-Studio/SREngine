//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <ResourceManager/IResource.h>
#include <Environment/TextureHelper.h>
#include <Memory/TextureConfigs.h>

namespace Framework::Graphics {
    class Environment;
    class TextureLoader;
    class Render;
}

namespace Framework::Graphics::Types {
    class Texture : public Helper::IResource {
        friend class ::Framework::Graphics::TextureLoader;
    private:
        Texture();
        ~Texture() override;

    public:
        static Texture* Load(const std::string& path);
        static Texture* Load(const std::string& path, const Memory::TextureConfig& config);
        static Texture* LoadFromMemory(const std::string& data, const Memory::TextureConfig& config);
        static Texture* GetNone();
        static void FreeNoneTexture();

    public:
        void SetRender(Render* render);

        [[nodiscard]] SR_FORCE_INLINE Render* GetRender() const noexcept { return m_render; }
        [[nodiscard]] SR_FORCE_INLINE std::string GetName() const { return m_name; }
        [[nodiscard]] SR_FORCE_INLINE bool IsCalculated() const noexcept { return m_isCalculate; }
        [[nodiscard]] SR_FORCE_INLINE bool HasRender() const noexcept { return GetRender(); }
        [[nodiscard]] SR_FORCE_INLINE int32_t GetID() noexcept;

        /* Call only from render pool events */
        bool FreeVideoMemory();

    public:
        bool Destroy() override;

    private:
        bool Calculate();
        void SetConfig(const Memory::TextureConfig& config);

    private:
        inline static Texture*     m_none        = nullptr;

        Environment* m_env                       = nullptr;
        Render*                    m_render      = nullptr;
        uint8_t*                   m_data        = nullptr;

        int32_t                    m_ID          = 0;
        uint32_t                   m_width       = 0;
        uint32_t                   m_height      = 0;

        std::string                m_name        = std::string();

        std::atomic<bool>          m_isCalculate = false;
        std::atomic<bool>          m_hasErrors   = false;

        Memory::TextureConfig      m_config      = Memory::TextureConfig();

    };
}

#endif //GAMEENGINE_TEXTURE_H
