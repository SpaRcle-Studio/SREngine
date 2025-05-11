

# File IResourceReloader.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**IResourceReloader.h**](IResourceReloader_8h.md)

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

    class SR_COMMON_DLL_API IResourceReloader : public SR_UTILS_NS::NonCopyable {
    public:
        SR_NODISCARD virtual bool IsResourceSuitableForReload(IResource* pResource) const;
        SR_NODISCARD virtual bool Reload(const SR_UTILS_NS::Path& path, ResourceInfo* pResourceInfo) = 0;

    protected:
        std::recursive_mutex m_mutex;

    };

    class SR_COMMON_DLL_API DefaultResourceReloader final : public IResourceReloader {
    public:
        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, ResourceInfo* pResourceInfo) override;

    };
}

#endif //SR_ENGINE_IRESOURCERELOADER_H
```


