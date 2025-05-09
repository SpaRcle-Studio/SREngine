

# File ResourceInfo.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**ResourceInfo.h**](ResourceInfo_8h.md)

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
    typedef std::list<IResource*> ResourcesList;
    typedef std::unordered_set<IResource*> ResourcesSet;

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

        SR_NODISCARD IResource* GetResource() const;
        SR_NODISCARD IResource* GetFirstResource() const;
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
        using CopiesMap = std::unordered_map<ResourceId, std::unordered_set<IResource*>>;
        using Info = std::unordered_map<ResourcePath, ResourceInfo::HardPtr>;
    public:
        explicit ResourceType(std::string name)
            : m_name(std::move(name))
        { }

        ~ResourceType() override;

    public:
        SR_NODISCARD IResource* Find(const ResourceId& id);
        SR_NODISCARD bool IsLast(const ResourceId& id);
        SR_NODISCARD const CopiesMap& GetCopiesRef() const;
        SR_NODISCARD Info& GetInfo();
        SR_NODISCARD std::pair<ResourcePath, ResourceInfo::HardPtr> GetInfoByIndex(uint64_t index);
        SR_NODISCARD IResourceReloader* GetReloader() const noexcept { return m_reloader; }
        SR_NODISCARD const std::string& GetName() const { return m_name; }

        void Remove(IResource* pResource);
        void Add(IResource* pResource);

        void SetReloader(IResourceReloader* pReloader);

        void CollectUnused();

    private:
        IResourceReloader* m_reloader = nullptr;
        ResourcesSet m_resources;
        CopiesMap m_copies;
        Info m_info;
        std::string m_name;

    };

    typedef ska::flat_hash_map<uint64_t, ResourceType*> ResourcesTypes;
}

#endif //SR_ENGINE_RESOURCEINFO_H
```


