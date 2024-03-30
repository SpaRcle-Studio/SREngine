//
// Created by innerviewer on 2024-03-20.
//

#ifndef SR_ENGINE_CORE_LAUNCHER_H
#define SR_ENGINE_CORE_LAUNCHER_H

#include <Utils/Types/SharedPtr.h>
#include <Core/Application.h>

namespace SR_CORE_NS {
    class Launcher : public SR_CORE_NS::Application {
    public:
        void Init(int argc, char** argv);

    protected:
        bool InitializeResourcesFolder(int argc, char** argv) override { return true; }

    private:
        void ExportResources();
    };
}

#endif //SR_ENGINE_CORE_LAUNCHER_H
