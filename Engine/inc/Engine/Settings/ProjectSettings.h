//
// Created by Monika on 17.06.2022.
//

#ifndef SR_ENGINE_PROJECT_SETTINGS_H
#define SR_ENGINE_PROJECT_SETTINGS_H

#include <Engine/macros.h>

#include <Utils/Resources/Asset.h>

namespace SR_CORE_NS {
    /// @extension(srproject)
    class ProjectSettings : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ProjectSettings>;

    public:
        /// @property
        SR_UTILS_NS::StringAtom projectName = "New Project";

    };
}

#endif //SR_ENGINE_PROJECT_SETTINGS_H
