//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <mutex>
#include <ResourceManager/IResource.h>
#include <Environment/Environment.h>
#include <Environment/TextureFilters.h>

namespace Framework::Graphics{
    class TextureLoader;
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

        std::mutex                      m_mutex         = std::mutex();
        TextureType                     m_type          = TextureType::Unknown;
        TextureFilter                   m_filter        = TextureFilter::Unknown;
    private:
        bool Calculate();
    public:
        unsigned int GetID() noexcept;
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
