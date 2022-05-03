//
// Created by Monika on 02.05.2022.
//

#ifndef SRENGINE_RESOURCEINFO_H
#define SRENGINE_RESOURCEINFO_H

#include <Debug.h>
#include <ResourceManager/IResource.h>
#include <FileSystem/Path.h>

namespace SR_UTILS_NS {
    typedef std::list<IResource*> ResourcesList;
    typedef std::unordered_set<IResource*> ResourcesSet;

    class ResourceManager;

    struct ResourceInfo {
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

    class ResourceType {
        friend class ResourceManager;
        using ResourceId = std::string;
        using ResourcePath = std::string;
        using CopiesMap = std::unordered_map<ResourceId, std::unordered_set<IResource*>>;
        using Info = std::unordered_map<ResourcePath, ResourceInfo>;
    public:
        SR_NODISCARD IResource* Find(const std::string& id);
        SR_NODISCARD bool IsLast(const std::string& id);
        SR_NODISCARD const CopiesMap& GetCopiesRef() const;
        SR_NODISCARD Info& GetInfo();

        void Remove(IResource* resource);
        void Add(IResource* resource);

    private:
        ResourcesSet m_resources;
        CopiesMap m_copies;
        Info m_info;

    };

    typedef std::unordered_map<std::string, ResourceType> ResourcesTypes;
}

#endif //SRENGINE_RESOURCEINFO_H
