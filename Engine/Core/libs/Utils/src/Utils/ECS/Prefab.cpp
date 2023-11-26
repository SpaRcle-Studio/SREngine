//
// Created by Monika on 23.12.2022.
//

#include <Utils/ECS/Prefab.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_UTILS_NS {
    Prefab::Prefab()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(Prefab))
    { }

    Prefab::~Prefab() {
        m_data.AutoFree([](auto&& pData) {
            pData->Destroy();
        });
    }

    Prefab* Prefab::Load(const Path& rawPath) {
        Prefab* pResource = nullptr;

        ResourceManager::Instance().Execute([&pResource, &rawPath]() {
            Path&& path = Path(rawPath).RemoveSubPath(ResourceManager::Instance().GetResPath());

            if ((pResource = ResourceManager::Instance().Find<Prefab>(path))) {
                return;
            }

            pResource = new Prefab();

            pResource->SetId(path.ToStringRef(), false /** auto register */);

            if (!pResource->Reload()) {
                SR_ERROR("RawMesh::Load() : failed to load prefab! \n\tPath: " + path.ToString());
                pResource->DeleteResource();
                pResource = nullptr;
                return;
            }

            /// отложенная ручная регистрация
            ResourceManager::Instance().RegisterResource(pResource);
        });

        return pResource;
    }

    bool Prefab::Unload() {
        m_data.AutoFree([](auto&& pData) {
            pData->Destroy();
        });

        return IResource::Unload();
    }

    bool Prefab::Load() {
        Path&& path = Path(GetResourceId());
        if (!path.IsAbs()) {
            path = ResourceManager::Instance().GetResPath().Concat(path);
        }

        auto&& marshal = SR_HTYPES_NS::Marshal::Load(path);
        if (!marshal.Valid()) {
            SR_ERROR("Prefab::Load() : failed to load marshal data!");
            return false;
        }

        m_data = SR_UTILS_NS::GameObject::Load(marshal, nullptr);

        if (!m_data.Valid()) {
            m_loadState = LoadState::Error;
            SR_ERROR("Prefab::Load() : failed to load game object from marshal data!");
            return false;
        }


        return IResource::Load();
    }

    Prefab::GameObjectPtr Prefab::Instance(const Prefab::ScenePtr& scene) const {
        if (m_data) {
            auto&& instanced = m_data->Copy(scene);
            instanced->SetPrefab(const_cast<Prefab*>(this), true);
            return instanced;
        }

        return Prefab::GameObjectPtr();
    }
}
