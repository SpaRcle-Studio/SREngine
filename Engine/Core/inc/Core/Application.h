//
// Created by Monika on 14.09.2023.
//

#ifndef SR_ENGINE_CORE_APPLICATION_H
#define SR_ENGINE_CORE_APPLICATION_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/FileSystem/Path.h>

namespace SR_CORE_NS {
    class Engine;

    class Application : public SR_HTYPES_NS::SharedPtr<Application> {
        using Super = SR_HTYPES_NS::SharedPtr<Application>;
    public:
        Application();
        ~Application();

    public:
        bool PreInit(int argc, char** argv);
        bool Init();
        bool Execute();

        void SwitchResourcesFolder(const SR_UTILS_NS::Path& path);
        void Reload();

    private:
        bool InitResourceTypes();
        bool InitLogger();
        bool FindResourcesFolder();
        void TryPlayStartSound();
        void Close();

    private:
        SR_UTILS_NS::Path m_applicationPath;
        SR_UTILS_NS::Path m_resourcesPath;

        std::atomic<bool> m_isNeedReload = false;
        std::atomic<bool> m_isNeedPlaySound = true;

        SR_HTYPES_NS::SharedPtr<Engine> m_engine;

    };
}

#endif //SR_ENGINE_CORE_APPLICATION_H
