//
// Created by Nikita on 03.12.2020.
//

#ifndef GAMEENGINE_TEXTURELOADER_H
#define GAMEENGINE_TEXTURELOADER_H

#include <Utils/stdInclude.h>

namespace SR_HTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    class TextureLoader {
    public:
        TextureLoader()  = delete;
        ~TextureLoader() = delete;
    private:
        Types::Texture* g_default = nullptr;
    public:
        static Types::Texture* GetDefaultTexture() noexcept;
    public:
        static bool Load(Types::Texture* texture, std::string path);
        static bool LoadFromMemory(Types::Texture* texture, const std::string& data);
        static bool Free(unsigned char* data);
    };
}

#endif //GAMEENGINE_TEXTURELOADER_H