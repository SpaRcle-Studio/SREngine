//
// Created by Nikita on 17.11.2020.
//

#ifndef GAMEENGINE_TEXTURE_H
#define GAMEENGINE_TEXTURE_H

#include <ResourceManager/IResource.h>

namespace Framework::Graphics::Types {
    using namespace Helper;
    class Texture : public IResource {
    public:
        Texture();
    private:
        ~Texture();
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
