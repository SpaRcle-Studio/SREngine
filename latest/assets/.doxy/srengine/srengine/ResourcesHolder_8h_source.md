

# File ResourcesHolder.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**ResourcesHolder.h**](ResourcesHolder_8h.md)

[Go to the documentation of this file](ResourcesHolder_8h.md)


```C++
//
// Created by Monika on 18.03.2022.
//

#ifndef SR_ENGINE_RESOURCESHOLDER_H
#define SR_ENGINE_RESOURCESHOLDER_H

#include <Utils/Resources/IResource.h>

namespace SR_UTILS_NS {
    class SR_COMMON_DLL_API ResourcesHolder : public NonCopyable {
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
```


