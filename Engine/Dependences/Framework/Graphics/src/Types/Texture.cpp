//
// Created by Nikita on 17.11.2020.
//

#include <ResourceManager/ResourceManager.h>
#include "Types/Texture.h"

Framework::Graphics::Types::Texture::Texture() : IResource("Texture") {

}

Framework::Graphics::Types::Texture::~Texture() {

}

bool Framework::Graphics::Types::Texture::Destroy() {
    if (m_isDestroy)
        return false;

    this->m_isDestroy = true;

    Helper::ResourceManager::Destroy(this);

    return true;
}
