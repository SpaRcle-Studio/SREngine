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
        ~Application() override;

    public:
        bool PreInit();
        bool EarlyInit();
        bool Init();
        bool Execute();
        bool MainLoop();
        void Close();

        void Reload();

        SR_NODISCARD const SR_UTILS_NS::Path& GetResourcesPath() const { return m_resourcesPath; }
        SR_NODISCARD const SR_UTILS_NS::Path& GetEngineResourcesPath() const { return m_engineResourcesPath; }
        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<Engine>& GetEngine() const { return m_engine; }
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Engine>& GetEngine() { return m_engine; }

    protected:
        bool InitializeResourcesFolder();

    private:
        bool InitLogger(const SR_UTILS_NS::Path& logDir);

    private:
        SR_UTILS_NS::Path m_engineResourcesPath;
        SR_UTILS_NS::Path m_resourcesPath;

        bool m_hasErrors = false;
        std::atomic<bool> m_isNeedReload = false;

        SR_HTYPES_NS::SharedPtr<Engine> m_engine;

    };
}

#endif //SR_ENGINE_CORE_APPLICATION_H
