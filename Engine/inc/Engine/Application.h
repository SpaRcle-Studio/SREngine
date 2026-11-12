//
// Created by Monika on 14.09.2023.
//

#ifndef SR_ENGINE_CORE_APPLICATION_H
#define SR_ENGINE_CORE_APPLICATION_H

#include <Engine/stdInclude.h>

#include <Utils/Types/SharedPtr.h>
#include <Utils/Types/WeakPtr.h>
#include <Utils/FileSystem/Path.h>

namespace SR_CORE_NS {
    class Engine;

    /// @noCopyable @noMovable
    class Application : public SR_HTYPES_NS::SharedPtr<Application>, public SR_UTILS_NS::Serializable {
        SR_CLASS()
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

        /// @method @evaluate
        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<Engine>& GetEngine() const { return m_engine; }
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Engine>& GetEngine() { return m_engine; }

    protected:
        bool InitializeResourcesFolder();

    private:
        bool InitLogger(const SR_UTILS_NS::Path& logDir);

    private:
        bool m_hasErrors = false;
        std::atomic<bool> m_isNeedReload = false;

        SR_HTYPES_NS::SharedPtr<Engine> m_engine;

    };

    /// @noCopyable @noMovable
    class ApplicationManager : public SR_UTILS_NS::Singleton<ApplicationManager>, public SR_UTILS_NS::SRClass {
        SR_REGISTER_SINGLETON(ApplicationManager)
        SR_CLASS()
    public:
        void RegisterApplication(Application& application);
        void UnRegisterApplication(Application& application);

        /// @method @evaluate
        SR_HTYPES_NS::SharedPtr<Application> GetApplication() const;

    private:
        SR_UTILS_NS::Vector<SR_HTYPES_NS::WeakPtr<Application>> m_applications;

    };
}

#endif //SR_ENGINE_CORE_APPLICATION_H
