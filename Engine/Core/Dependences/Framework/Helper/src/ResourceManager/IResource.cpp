//
// Created by Nikita on 17.11.2020.
//

#include "ResourceManager/IResource.h"
#include "ResourceManager/ResourceManager.h"

using namespace Framework::Helper;

IResource::IResource(const char* name)
    : m_resourceName(name)
    , m_lifetime(ResourceManager::ResourceLifeTime)
{ }

bool IResource::ForceDestroy() {
    if (m_force || m_isDestroy) {
        Helper::Debug::Error("IResource::ForceDestroy() : resource is already destroyed!");
        return false;
    }

    m_force = true;

    return this->Destroy();
}

void IResource::SetId(const std::string &id) {
    if (m_resourceId == "NoID") {
        m_resourceId = id;
        ResourceManager::Instance().RegisterResource(this);
    }
    else {
        SRAssert2(false, "Double set resource id!");
    }
}

IResource *IResource::Copy(IResource* destination) const {
    destination->m_autoRemove = m_autoRemove;
    destination->SetId(m_resourceId);
    destination->SetReadOnly(m_readOnly);

    return destination;
}

bool IResource::Destroy() {
    Helper::ResourceManager::Instance().Destroy(this);

    SRAssert(!m_isDestroy);
    m_isDestroy = true;
    return true;
}

bool IResource::IsValid() const {
    return m_resourceId != "NoID" && !m_resourceId.empty() && std::string(m_resourceName) != "Unnamed";
}
