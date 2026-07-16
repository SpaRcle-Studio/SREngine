//
// Created by Monika on 02.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_SCRIPT_SYSTEM_H
#define SR_ENGINE_SCRIPTING_CPP_SCRIPT_SYSTEM_H

#include <Scripting/Cpp/CodeGenerator.h>
#include <Scripting/Cpp/CppCompiler.h>
#include <Scripting/Cpp/ModuleManager.h>

#include <Utils/Common/Singleton.h>
#include <Utils/Common/NonCopyable.h>
#include <Utils/Resources/FileSystemWatcher.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    SR_ENUM_NS_CLASS_T(ScriptSystemState, uint8_t,
        InitialAnalyse, Idle, CheckModules, Codegen, Compiling, Reloading
    );

    class ScriptSystem : public SR_UTILS_NS::Singleton<ScriptSystem> {
        SR_REGISTER_SINGLETON(ScriptSystem)
        using Super = SR_HTYPES_NS::SharedPtr<ScriptSystem>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ScriptSystem>;

        const static inline std::set<std::string_view> ALLOWED_CPP_EXTENSIONS = { "cpp", "h", "hpp", "cxx" };
        const static inline std::set<std::string_view> ALLOWED_CPP_MODULE_EXTENSIONS = { "dll", "so" };
        const static inline SR_UTILS_NS::StringAtom ENGINE_MODULE_FILE_NAME = ".module";

    private:
        ScriptSystem() = default;
        ~ScriptSystem() override;

    public:
        SR_NODISCARD bool IsInitialized() const { return m_isInit; }
        SR_NODISCARD bool Init();

        SR_NODISCARD const ModuleManager* GetModuleManager() const { return m_moduleManager.Get(); }
        SR_NODISCARD ModuleManager* GetModuleManager() { return m_moduleManager.Get(); }
        SR_NODISCARD const std::vector<SR_UTILS_NS::Path>& GetEngineSourcesIncludePaths() const { return m_engineSourcesIncludePaths; }
        SR_NODISCARD const SR_UTILS_NS::Path& GetEngineSourcesPath() const { return m_pathToEngineSourcesRoot; }
        SR_NODISCARD ScriptSystemState GetState() const { return m_state; }
        SR_NODISCARD bool HasErrors() const { return m_hasCompileErrors || m_hasModuleCopyErrors; }

        void WaitForIdle();
        void ReloadModulesIfNeeded();
        void SetReloadRequest();

        static std::string_view GetDynamicLibraryExtension();

    private:
        void HandleFileSystemEvent(const SR_UTILS_NS::SubscriptionMessage& message, SR_UTILS_NS::FileSystemWatcher::EventType eventType);
        bool ThreadFunc();
        bool InitEngineSources();

        void InitialAnalyse();
        void ThreadIdle();
        void CompileModules();
        void CopyModules();
        void ReloadModules();

        void ResetSubscriptions();

    private:
        bool m_isInit = false;
        bool m_isCompilationEnabled = false;

        std::recursive_mutex m_mutex;
        SR_HTYPES_NS::Thread::Ptr m_thread = nullptr;

        SR_UTILS_NS::Subscription m_fileChangedSubscription;
        SR_UTILS_NS::Subscription m_fileCreatedSubscription;
        SR_UTILS_NS::Subscription m_fileDeletedSubscription;

        /// shared parameters (read only)

        SR_UTILS_NS::Path m_pathToEngineSourcesRoot;
        SR_UTILS_NS::Path m_engineResourcesFolder;
        SR_UTILS_NS::Path m_resourcesFolder;
        SR_UTILS_NS::Path m_cacheFolder;
        SR_UTILS_NS::Path m_apiFolder;

        /// thread owned parameters

        std::vector<SR_UTILS_NS::Path> m_engineSourcesIncludePaths;
        SR_UTILS_NS::TimePointType m_lastFileSystemEvent;

        CppCompiler::Ptr m_compiler;
        CppCodeGenerator::Ptr m_codeGenerator;
        ModuleManager::Ptr m_moduleManager;

        std::atomic<bool> m_threadRunning = false;
        std::atomic<bool> m_isCompiled = false;
        std::atomic<bool> m_hasCompileErrors = false;
        std::atomic<bool> m_hasModuleCopyErrors = false;
        std::atomic<bool> m_hasModuleReloadRequest = false;
        std::atomic<bool> m_forceReloadModules = false;
        std::atomic<ScriptSystemState> m_state = ScriptSystemState::InitialAnalyse;

        std::set<SR_UTILS_NS::Path> m_changedCppFiles;
        std::set<SR_UTILS_NS::Path> m_changedCppModules;
        std::set<SR_UTILS_NS::Path> m_changedModules;

        std::set<SR_UTILS_NS::StringAtom> m_modulesToCopy;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_SCRIPT_SYSTEM_H
