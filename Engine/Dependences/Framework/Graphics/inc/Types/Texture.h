//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <mutex>
#include <ResourceManager/IResource.h>
#include <Environment/Environment.h>
#include <Environment/TextureFilters.h>
#include <macros.h>

namespace Framework::Graphics{
    class TextureLoader;
    class Render;
}

namespace Framework::Graphics::Types {
    using namespace Helper;
    class Texture : public IResource {
        friend class ::Framework::Graphics::TextureLoader;
    private:
        Texture();
        ~Texture();
    private:
        inline static Environment*      m_env           = nullptr;

        unsigned int                    m_ID            = 0;

        unsigned int                    m_width         = 0;
        unsigned int                    m_height        = 0;

        int                             m_format        = 0;

        unsigned char*                  m_data          = nullptr;

        volatile bool                   m_isCalculate   = false;

        Render*                         m_render        = nullptr;

        std::mutex                      m_mutex         = std::mutex();
        TextureType                     m_type          = TextureType::Unknown;
        TextureFilter                   m_filter        = TextureFilter::Unknown;
    private:
        bool Calculate();
    public:
        void OnDestroyGameObject() noexcept;

        void SetRender(Render* render);

        [[nodiscard]] SR_FORCE_INLINE bool IsCalculated() const noexcept { return m_isCalculate; }
        [[nodiscard]] SR_FORCE_INLINE unsigned int GetID() noexcept {
            if (m_isDestroy) {
                Debug::Error("Texture::GetID() : texture \""+m_resource_id+"\" is destroyed!");
                return 0;
            }

            if (!m_isCalculate)
                if (!Calculate()) {
                    Debug::Error("Texture::GetID() : failed calculating texture!");
                    return 0;
                }

            return m_ID;
        }

        /* Call only from render pool events */
        SR_FORCE_INLINE bool FreeVideoMemory() noexcept {
            if (Debug::GetLevel() >= Debug::Level::High)
                Debug::Log("Texture::FreeVideoMemory() : free texture video memory...");

            if (!m_isCalculate){
                Debug::Error("Texture::FreeVideoMemory() : texture is not calculated!");
                return false;
            }
            else {
                this->m_env->DeleteTexture(m_ID);
                return true;
            }
        }
        //Texture* Copy();
    public:
        static Texture* Load(std::string path, bool autoRemove = false, TextureType type = TextureType::Diffuse, TextureFilter filter = TextureFilter::NEAREST);
    public:
        bool Free() override {
            delete this;
            return true;
        }
    public:
        bool Destroy() override;
    };
}

#endif //GAMEENGINE_TEXTURE_H
