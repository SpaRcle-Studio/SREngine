

# File ResourcesHolder.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**ResourcesHolder.h**](ResourcesHolder_8h.md)

[Go to the documentation of this file](ResourcesHolder_8h.md)


```C++
//
// Created by Monika on 18.03.2022.
//

#ifndef SR_ENGINE_RESOURCESHOLDER_H
#define SR_ENGINE_RESOURCESHOLDER_H

#include <Utils/Resources/IResource.h>

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
```


