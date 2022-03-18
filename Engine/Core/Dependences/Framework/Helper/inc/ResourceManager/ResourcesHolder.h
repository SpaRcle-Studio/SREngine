//
// Created by Monika on 18.03.2022.
//

#ifndef SRENGINE_RESOURCESHOLDER_H
#define SRENGINE_RESOURCESHOLDER_H

#include <macros.h>
#include <Utils/NonCopyable.h>
#include <ResourceManager/IResource.h>
#include <unordered_set>

namespace SR_UTILS_NS {
    class ResourcesHolder : public NonCopyable {
    public:
        ~ResourcesHolder() override = default;

    public:
        bool Add(IResource* pResource);
        bool Remove(IResource* pResource);
        void Release();

    private:
        std::mutex m_mutex;
        std::unordered_set<IResource*> m_resources;

    };
}

#endif //SRENGINE_RESOURCESHOLDER_H
