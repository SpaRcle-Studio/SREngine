

# File ResourceContainer.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**ResourceContainer.h**](ResourceContainer_8h.md)

[Go to the documentation of this file](ResourceContainer_8h.md)


```C++
//
// Created by Monika on 20.01.2023.
//

#ifndef SR_ENGINE_RESOURCECONTAINER_H
#define SR_ENGINE_RESOURCECONTAINER_H

#include <Utils/Common/NonCopyable.h>

namespace SR_UTILS_NS {
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

    private:
        std::unordered_set<ResourceContainer*> m_parents;
        std::unordered_set<ResourceContainer*> m_dependencies;

    };
}

#endif //SR_ENGINE_RESOURCECONTAINER_H
```


