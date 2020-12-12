//
// Created by Nikita on 03.12.2020.
//

#ifndef GAMEENGINE_TEXTURELOADER_H
#define GAMEENGINE_TEXTURELOADER_H

#include <string>

namespace Framework::Graphics::Types{
    class Texture;
}

namespace Framework::Graphics {
    class TextureLoader {
    private:
        TextureLoader() { }
        ~TextureLoader() { }
    public:
        static Types::Texture* Load(std::string path);
        static bool Free(unsigned char* data);
    };
}

#endif //GAMEENGINE_TEXTURELOADER_H
