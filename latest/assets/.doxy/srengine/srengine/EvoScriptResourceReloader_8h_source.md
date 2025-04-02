

# File EvoScriptResourceReloader.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Impl**](dir_24f2b9252cbd3f2e0c4afbfdbb5b103e.md) **>** [**EvoScriptResourceReloader.h**](EvoScriptResourceReloader_8h.md)

[Go to the documentation of this file](EvoScriptResourceReloader_8h.md)


```C++
//
// Created by Monika on 11.03.2023.
//

#ifndef SR_ENGINE_EVOSCRIPTRESOURCERELOADER_H
#define SR_ENGINE_EVOSCRIPTRESOURCERELOADER_H

#include <Utils/Resources/IResourceReloader.h>

namespace SR_SCRIPTING_NS {
    class SR_DLL_EXPORT EvoScriptResourceReloader final : public SR_UTILS_NS::IResourceReloader {
        using StashedProperties = std::vector<std::pair<IRawBehaviour*, SR_HTYPES_NS::Marshal::Ptr>>;
    public:
        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) override;

    private:
        void FreeStashedProperties(const StashedProperties& properties);

    };
}

#endif //SR_ENGINE_EVOSCRIPTRESOURCERELOADER_H
```


