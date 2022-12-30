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

    struct SR_DLL_EXPORT ResourceInfo {
        ResourceInfo(uint64_t fileHash, uint64_t resourceHash)
            : m_fileHash(fileHash)
            , m_resourceHash(resourceHash)
        { }

        ResourceInfo()
            : ResourceInfo(0, 0)
        { }

        uint64_t m_fileHash = 0;
        uint64_t m_resourceHash = 0;
        ResourcesSet m_loaded;
    };

    class SR_DLL_EXPORT ResourceType {
        friend class ResourceManager;
        using ResourceId = uint64_t;
        using ResourcePath = uint64_t;
        using CopiesMap = std::unordered_map<ResourceId, std::unordered_set<IResource*>>;
        using Info = std::unordered_map<ResourcePath, ResourceInfo>;
    public:
        ResourceType()
            : m_name(std::string())
        { }

        explicit ResourceType(std::string name)
            : m_name(std::move(name))
        { }

        ResourceType(const ResourceType& other) noexcept {
            m_resources = other.m_resources;
            m_copies = other.m_copies;
            m_info = other.m_info;
            m_name = other.m_name;
        }

        ResourceType(ResourceType&& other) noexcept
            : m_resources(std::exchange(other.m_resources, { }))
            , m_copies(std::exchange(other.m_copies, { }))
            , m_info(std::exchange(other.m_info, { }))
            , m_name(std::exchange(other.m_name, { }))
        { }

        ResourceType& operator=(ResourceType&& other) noexcept {
            m_resources = std::exchange(other.m_resources, { });
            m_copies = std::exchange(other.m_copies, { });
            m_info = std::exchange(other.m_info, { });
            m_name = std::exchange(other.m_name, { });
            return *this;
        }

    public:
        SR_NODISCARD IResource* Find(const ResourceId& id);
        SR_NODISCARD bool IsLast(const ResourceId& id);
        SR_NODISCARD const CopiesMap& GetCopiesRef() const;
        SR_NODISCARD Info& GetInfo();
        SR_NODISCARD std::string_view GetName() const { return m_name; }

        void Remove(IResource* pResource);
        void Add(IResource* pResource);

    private:
        ResourcesSet m_resources;
        CopiesMap m_copies;
        Info m_info;
        std::string m_name;

    };

    typedef ska::flat_hash_map<uint64_t, ResourceType> ResourcesTypes;
}

#endif //SRENGINE_RESOURCEINFO_H
