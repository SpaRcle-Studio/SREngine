//
// Created by Monika on 28.03.2023.
//

#ifndef SRENGINE_GRAPHICSRESOURCERELOADER_H
#define SRENGINE_GRAPHICSRESOURCERELOADER_H

#include <Utils/ResourceManager/IResourceReloader.h>

namespace SR_CORE_NS {
    class SR_DLL_EXPORT GraphicsResourceReloader final : public SR_UTILS_NS::IResourceReloader {
        using Super = SR_UTILS_NS::IResourceReloader;
    public:
        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) override;

    private:
        void OnResourceReloaded(SR_UTILS_NS::IResource* pResource);

    };
}

#endif //SRENGINE_GRAPHICSRESOURCERELOADER_H
