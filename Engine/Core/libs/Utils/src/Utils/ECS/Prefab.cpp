//
// Created by Monika on 23.12.2022.
//

#include <Utils/ECS/Prefab.h>
#include <Utils/ResourceManager/ResourceManager.h>

namespace SR_UTILS_NS {
    Prefab::Prefab()
        : IResource(SR_COMPILE_TIME_CRC32_TYPE_NAME(Prefab), true /** auto remove */)
    { }

    Prefab::~Prefab() {
        SRAssert(!m_data);
    }

    Prefab* Prefab::Load(const Path& rawPath) {
        SR_GLOBAL_LOCK

        Path&& path = Path(rawPath).RemoveSubPath(ResourceManager::Instance().GetResPath());

        if (auto&& pResource = ResourceManager::Instance().Find<Prefab>(path)) {
            return pResource;
        }

        auto pResource = new Prefab();

        pResource->SetId(path, false /** auto register */);

        if (!pResource->Reload()) {
            SR_ERROR("RawMesh::Load() : failed to load prefab! \n\tPath: " + path.ToString());
            delete pResource;
            return nullptr;
        }

        /// отложенная ручная регистрация
        ResourceManager::Instance().RegisterResource(pResource);

        return pResource;
    }

    bool Prefab::Unload() {
        SR_LOCK_GUARD

        m_data->Destroy();

        return IResource::Unload();
    }

    bool Prefab::Load() {
        SR_LOCK_GUARD

        Path&& path = Path(GetResourceId());
        if (!path.IsAbs()) {
            path = ResourceManager::Instance().GetResPath().Concat(path);
        }

        auto&& marshal = SR_HTYPES_NS::Marshal::Load(path);
        if (!marshal.Valid()) {
            SR_ERROR("Prefab::Load() : failed to load marshal data!");
            return false;
        }



        return IResource::Load();
    }
}
