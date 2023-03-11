//
// Created by Monika on 11.03.2023.
//

#ifndef SRENGINE_IRESOURCERELOADER_H
#define SRENGINE_IRESOURCERELOADER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/FileSystem/Path.h>

namespace SR_UTILS_NS {
    class ResourceInfo;
    class IResource;

    class SR_DLL_EXPORT IResourceReloader : public SR_UTILS_NS::NonCopyable {
    public:
        SR_NODISCARD virtual bool IsResourceSuitableForReload(IResource* pResource) const;
        SR_NODISCARD virtual bool Reload(const SR_UTILS_NS::Path& path, ResourceInfo* pResourceInfo) = 0;

    };

    /** Обычная перезагрузка, перебором каждого ресурса и вызова ему Reload */
    class SR_DLL_EXPORT DefaultResourceReloader final : public IResourceReloader {
    public:
        SR_NODISCARD bool Reload(const SR_UTILS_NS::Path& path, ResourceInfo* pResourceInfo) override;

    };
}

#endif //SRENGINE_IRESOURCERELOADER_H
