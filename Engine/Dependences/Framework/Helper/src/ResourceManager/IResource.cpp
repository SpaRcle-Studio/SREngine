//
// Created by Nikita on 17.11.2020.
//

#include "ResourceManager/IResource.h"
#include "ResourceManager/ResourceManager.h"

using namespace Framework::Helper;

IResource::IResource(const char *res_name) : m_resource_name(res_name) {
    ResourceManager::Instance().RegisterResource(this);
}
