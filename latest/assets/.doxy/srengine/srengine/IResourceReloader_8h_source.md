

# File IResourceReloader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**IResourceReloader.h**](IResourceReloader_8h.md)

[Go to the documentation of this file](IResourceReloader_8h.md)


```C++
//
// Created by Monika on 11.03.2023.
//

#ifndef SR_ENGINE_IRESOURCERELOADER_H
#define SR_ENGINE_IRESOURCERELOADER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/FileSystem/Path.h>

namespace SR_UTILS_NS {
    class ResourceInfo;
    class IResource;

    class SR_DLL_EXPORT IResourceReloader : public SR_UTILS_NS::NonCopyable {
    public:
        SR_NODISCARD virtual bool IsResourceSuitableForReload(IResource* pResource) const;
        SR_NODISCARD virtual bool Reload(const SR_UTILS_NS::Path& path, ResourceInfo* pResourceInfo) = 0;

    protected:
        std::recursive_mutex m_mutex;

    };

    class SR_DLL_EXPORT DefaultResourceReloader final : public IResourceReloader {
    public:
        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, ResourceInfo* pResourceInfo) override;

    };
}

#endif //SR_ENGINE_IRESOURCERELOADER_H
```


