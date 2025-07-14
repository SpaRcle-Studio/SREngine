

# File ResourceInfo.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**ResourceInfo.h**](ResourceInfo_8h.md)

[Go to the documentation of this file](ResourceInfo_8h.md)


```C++
//
// Created by Monika on 02.05.2022.
//

#ifndef SR_ENGINE_RESOURCEINFO_H
#define SR_ENGINE_RESOURCEINFO_H

#include <Utils/Debug.h>
#include <Utils/Resources/IResource.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    typedef std::list<IResource::Ptr> ResourcesList;
    typedef std::unordered_set<IResource::Ptr> ResourcesSet;

    class ResourceManager;
    class IResourceReloader;
    class ResourceType;

    struct SR_COMMON_DLL_API ResourceInfo {
        using HardPtr = std::shared_ptr<ResourceInfo>;
        using WeakPtr = std::weak_ptr<ResourceInfo>;

        ResourceInfo(uint64_t resourceHash, SR_UTILS_NS::StringAtom path, ResourceType* pResourceType)
            : m_resourceType(pResourceType)
            , m_resourceHash(resourceHash)
            , m_path(path)
        { }

        SR_NODISCARD IResource::Ptr GetResource() const;
        SR_NODISCARD IResource::Ptr GetFirstResource() const;
        SR_NODISCARD IResourceReloader* GetReloader() const;

        ResourceType* m_resourceType = nullptr;

        uint64_t m_resourceHash = 0;
        SR_UTILS_NS::StringAtom m_path;

        ResourcesSet m_loaded;
    };

    class SR_COMMON_DLL_API ResourceType : public NonCopyable {
        friend class ResourceManager;
        using ResourceId = SR_UTILS_NS::StringAtom;
        using ResourcePath = SR_UTILS_NS::StringAtom;
    public:
        using CopiesMap = std::unordered_map<ResourceId, std::unordered_set<IResource::Ptr>>;
        using Info = std::unordered_map<ResourcePath, ResourceInfo::HardPtr>;

    public:
        explicit ResourceType(std::string name)
            : m_name(std::move(name))
        { }

        ~ResourceType() override;

    public:
        SR_NODISCARD IResource::Ptr Find(const ResourceId& id);
        SR_NODISCARD bool IsLast(const ResourceId& id);
        SR_NODISCARD CopiesMap& GetCopiesRef();
        SR_NODISCARD const CopiesMap& GetCopiesRef() const;
        SR_NODISCARD Info& GetInfo();
        SR_NODISCARD std::pair<ResourcePath, ResourceInfo::HardPtr> GetInfoByIndex(uint64_t index);
        SR_NODISCARD IResourceReloader* GetReloader() const noexcept { return m_reloader; }
        SR_NODISCARD const std::string& GetName() const { return m_name; }

        void Remove(const IResource::Ptr& pResource);
        void Add(const IResource::Ptr& pResource);

        void SetReloader(IResourceReloader* pReloader);

        void CollectUnused();

    private:
        IResourceReloader* m_reloader = nullptr;
        ResourcesSet m_resources;
        CopiesMap m_copies;
        Info m_info;
        std::string m_name;

    };

    typedef ska::flat_hash_map<SR_UTILS_NS::StringAtom, ResourceType*> ResourcesTypes;
}

#endif //SR_ENGINE_RESOURCEINFO_H
```


