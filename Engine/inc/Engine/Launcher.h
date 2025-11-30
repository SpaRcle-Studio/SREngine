//
// Created by innerviewer on 2024-03-20.
//

#ifndef SR_ENGINE_CORE_LAUNCHER_H
#define SR_ENGINE_CORE_LAUNCHER_H

#include <Utils/Types/SharedPtr.h>
#include <Engine/Application.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(LauncherInitStatus, uint8_t,
        Success,
        Error
    )

    class Launcher : public SR_CORE_NS::Application {
        using Super = SR_CORE_NS::Application;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<Launcher>;

    public:
        LauncherInitStatus InitLauncher();

    private:
        static bool UnpackEmbedded();
        bool CloneResources();

    };
}

#endif //SR_ENGINE_CORE_LAUNCHER_H
