

# File ResourceContainer.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**ResourceContainer.h**](ResourceContainer_8h.md)

[Go to the documentation of this file](ResourceContainer_8h.md)


```C++
//
// Created by Monika on 20.01.2023.
//

#ifndef SR_ENGINE_RESOURCECONTAINER_H
#define SR_ENGINE_RESOURCECONTAINER_H

#include <Utils/Types/SharedPtr.h>

namespace SR_UTILS_NS {
    class ResourceContainer : public SR_HTYPES_NS::SharedPtr<ResourceContainer> {
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ResourceContainer>;

    public:
        ResourceContainer();
        ~ResourceContainer() override;

    public:
        void AddDependency(const ResourceContainer::Ptr& pContainer);
        void RemoveDependency(const ResourceContainer::Ptr& pContainer);

        SR_NODISCARD const std::unordered_set<ResourceContainer::Ptr>& GetContainerParents() const { return m_parents; }

    protected:
        void UpdateResources(int32_t depth = 0);
        virtual void OnResourceUpdated(ResourceContainer* pContainer, int32_t depth);

    private:
        std::unordered_set<ResourceContainer::Ptr> m_parents;
        std::unordered_set<ResourceContainer::Ptr> m_dependencies;

    };
}

#endif //SR_ENGINE_RESOURCECONTAINER_H
```


