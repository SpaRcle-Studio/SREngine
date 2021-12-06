//
// Created by Nikita on 17.11.2020.
//

#include "ResourceManager/IResource.h"
#include "ResourceManager/ResourceManager.h"

using namespace Framework::Helper;

IResource::IResource(const char *res_name) : m_resource_name(res_name) {
    m_lifetime = ResourceManager::ResourceLifeTime;
    ResourceManager::Instance().RegisterResource(this);
}

bool IResource::ForceDestroy() {
    if (m_force || m_isDestroy) {
        Helper::Debug::Error("IResource::ForceDestroy() : resource is already destroyed!");
        return false;
    }

    m_force = true;

    return this->Destroy();
}