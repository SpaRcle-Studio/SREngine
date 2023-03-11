//
// Created by Monika on 11.03.2023.
//

#ifndef SRENGINE_EVOSCRIPTRESOURCERELOADER_H
#define SRENGINE_EVOSCRIPTRESOURCERELOADER_H

#include <Utils/ResourceManager/IResourceReloader.h>

namespace SR_SCRIPTING_NS {
    class SR_DLL_EXPORT EvoScriptResourceReloader : public SR_UTILS_NS::IResourceReloader {
    public:
        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo *pResourceInfo) override;

    };
}

#endif //SRENGINE_EVOSCRIPTRESOURCERELOADER_H
