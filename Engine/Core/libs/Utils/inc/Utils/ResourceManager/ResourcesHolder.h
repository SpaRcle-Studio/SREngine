//
// Created by Monika on 18.03.2022.
//

#ifndef SR_ENGINE_RESOURCESHOLDER_H
#define SR_ENGINE_RESOURCESHOLDER_H

#include <Utils/ResourceManager/IResource.h>

namespace SR_UTILS_NS {
    class SR_DLL_EXPORT ResourcesHolder : public NonCopyable {
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

#endif //SR_ENGINE_RESOURCESHOLDER_H
