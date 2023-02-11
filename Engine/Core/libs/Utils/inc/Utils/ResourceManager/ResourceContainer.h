//
// Created by Monika on 20.01.2023.
//

#ifndef SRENGINE_RESOURCECONTAINER_H
#define SRENGINE_RESOURCECONTAINER_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
    class IResource;

    class ResourceContainer : public SR_UTILS_NS::NonCopyable {
    protected:
        ~ResourceContainer() override;

    public:
        void AddDependency(ResourceContainer* pContainer);
        void RemoveDependency(ResourceContainer* pContainer);

        SR_NODISCARD const std::unordered_set<ResourceContainer*>& GetContainerParents() const { return m_parents; }

    protected:
        void UpdateResources(int32_t depth = 0);
        virtual void OnResourceUpdated(ResourceContainer* pContainer, int32_t depth);

    protected:
        mutable std::recursive_mutex m_mutex;

    private:
        std::unordered_set<ResourceContainer*> m_parents;
        std::unordered_set<ResourceContainer*> m_dependencies;

    };
}

#endif //SRENGINE_RESOURCECONTAINER_H
