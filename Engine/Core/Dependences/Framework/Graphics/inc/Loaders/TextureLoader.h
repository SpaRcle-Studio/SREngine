//
// Created by Nikita on 03.12.2020.
//

#ifndef GAMEENGINE_TEXTURELOADER_H
#define GAMEENGINE_TEXTURELOADER_H

#include <stdInclude.h>

namespace Framework::Graphics::Types{
    class Texture;
}

namespace Framework::Graphics {
    class TextureLoader {
    public:
        TextureLoader()  = delete;
        ~TextureLoader() = delete;
    private:
        Types::Texture* g_default = nullptr;
    public:
        static Types::Texture* GetDefaultTexture()             noexcept;
        static bool SetDefaultTexture(Types::Texture* texture) noexcept;
    public:
        static Types::Texture* Load(std::string path);
        static bool Free(unsigned char* data);
    };
}

#endif //GAMEENGINE_TEXTURELOADER_H
