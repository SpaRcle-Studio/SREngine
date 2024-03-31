//
// Created by innerviewer on 2024-03-20.
//

#ifndef SR_ENGINE_CORE_LAUNCHER_H
#define SR_ENGINE_CORE_LAUNCHER_H

#include <Utils/Types/SharedPtr.h>
#include <Core/Application.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_CLASS_T(LauncherInitStatus, uint8_t,
        Success,
        Error,
        Unpacking
    )

    class Launcher : public SR_CORE_NS::Application {
        using Super = SR_CORE_NS::Application;
    public:
        LauncherInitStatus InitLauncher(int argc, char** argv);

    protected:
        bool InitializeResourcesFolder(int argc, char** argv) override { return true; }

    private:
        bool UnpackAndExecute();
        void DeleteOldApplication();
    };
}

#endif //SR_ENGINE_CORE_LAUNCHER_H
