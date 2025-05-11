

# File EvoScriptResourceReloader.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Impl**](dir_4eaf059bf86cb1a50633501e0fe5274e.md) **>** [**EvoScriptResourceReloader.h**](EvoScriptResourceReloader_8h.md)

[Go to the documentation of this file](EvoScriptResourceReloader_8h.md)


```C++
//
// Created by Monika on 11.03.2023.
//

#ifndef SR_ENGINE_EVOSCRIPTRESOURCERELOADER_H
#define SR_ENGINE_EVOSCRIPTRESOURCERELOADER_H

#include <Utils/Resources/IResourceReloader.h>

namespace SR_SCRIPTING_NS {
    class SR_SCRIPTING_DLL_API EvoScriptResourceReloader final : public SR_UTILS_NS::IResourceReloader {
        using StashedProperties = std::vector<std::pair<IRawBehaviour*, SR_HTYPES_NS::Marshal::Ptr>>;
    public:
        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) override;

    private:
        void FreeStashedProperties(const StashedProperties& properties);

    };
}

#endif //SR_ENGINE_EVOSCRIPTRESOURCERELOADER_H
```


