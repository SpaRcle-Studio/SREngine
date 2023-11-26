//
// Created by Monika on 02.05.2022.
//

#ifndef SRENGINE_RESOURCEINFO_H
#define SRENGINE_RESOURCEINFO_H

#include <Utils/Debug.h>
#include <Utils/ResourceManager/IResource.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Types/Map.h>

namespace SR_UTILS_NS {
    typedef std::list<IResource*> ResourcesList;
    typedef std::unordered_set<IResource*> ResourcesSet;

    class ResourceManager;
    class IResourceReloader;
    class ResourceType;

    struct SR_DLL_EXPORT ResourceInfo {
        using HardPtr = std::shared_ptr<ResourceInfo>;
        using WeakPtr = std::weak_ptr<ResourceInfo>;

        ResourceInfo(uint64_t resourceHash, uint64_t pathHash, ResourceType* pResourceType)
            : m_resourceType(pResourceType)
            , m_resourceHash(resourceHash)
            , m_pathHash(pathHash)
        { }

        SR_NODISCARD IResource* GetResource() const;
        SR_NODISCARD IResource* GetFirstResource() const;
        SR_NODISCARD IResourceReloader* GetReloader() const;

        ResourceType* m_resourceType = nullptr;

        /// текущий хэш самого ресурса (параметры и тд, не файл!)
        uint64_t m_resourceHash = 0;
        /// хеш пути ресурса
        uint64_t m_pathHash = 0;

        ResourcesSet m_loaded;
    };

    class SR_DLL_EXPORT ResourceType : public NonCopyable {
        friend class ResourceManager;
        using ResourceId = SR_UTILS_NS::StringAtom;
        using ResourcePath = uint64_t;
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

        /// ставит все неиспользуемые ресурсы на очередь уничтожения
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

#endif //SRENGINE_RESOURCEINFO_H
