//
// Created by Monika on 02.04.2025.
//

#include <Scripting/Cpp/ScriptSystem.h>

#include <Utils/Common/Features.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Types/Time.h>

namespace SR_SCRIPTING_NS {
    ScriptSystem::~ScriptSystem() {
        ResetSubscriptions();

        m_threadRunning = false;

        if (m_thread) {
            if (m_thread->Joinable()) {
                m_thread->Join();
            }
            m_thread->Free();
            m_thread = nullptr;
        }

        m_compiler.AutoFree();
        m_codeGenerator.AutoFree();
        m_moduleManager.AutoFree();
    }

    bool ScriptSystem::Init() {
        if (m_isInit) {
            SRHalt("ScriptSystem::Init() : script system already initialized!");
            return false;
        }

        SR_LOG("ScriptSystem::Init() : initializing script system...");

        m_resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        m_engineResourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetEngineResPath();
        m_cacheFolder = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();

        m_isCompilationEnabled = SR_UTILS_NS::Features::Instance().Enabled("ScriptCompilation", true);
        m_isCompilationEnabled &= !SR_PLATFORM_NS::IsMobilePlatform();
        m_apiFolder = m_engineResourcesFolder.Concat("API");

        if (m_isCompilationEnabled && !InitEngineSources()) {
            SR_ERROR("ScriptSystem::Init() : failed to initialize engine sources!");
            return false;
        }

        m_moduleManager = ModuleManager::MakeShared(this);

        if (!m_moduleManager->Init()) {
            SR_ERROR("ScriptSystem::Init() : failed to initialize module manager!");
            return false;
        }

        if (m_isCompilationEnabled) {
            SR_LOG("ScriptSystem::Init() : script compilation is enabled!");

            m_compiler = CppCompiler::MakeShared(this);
            m_codeGenerator = CppCodeGenerator::MakeShared(this);

            m_codeGenerator->SetCompiler(m_compiler.Get());

            if (!m_compiler->Init()) {
                SR_ERROR("ScriptSystem::Init() : failed to initialize c++ compiler!");
                return false;
            }

            if (!m_codeGenerator->Init()) {
                SR_ERROR("ScriptSystem::Init() : failed to initialize code generator!");
                return false;
            }

            auto&& pFileSystemWatcher = SR_UTILS_NS::ResourceManager::Instance().GetFileSystemWatcher();

            m_fileChangedSubscription = pFileSystemWatcher->Subscribe(SR_UTILS_NS::FileSystemWatcher::MODIFIED_EVENT_ID,
                std::bind(&ScriptSystem::HandleFileSystemEvent, this, std::placeholders::_1, SR_UTILS_NS::FileSystemWatcher::EventType::Modified));

            m_fileCreatedSubscription = pFileSystemWatcher->Subscribe(SR_UTILS_NS::FileSystemWatcher::ADDED_EVENT_ID,
                std::bind(&ScriptSystem::HandleFileSystemEvent, this, std::placeholders::_1, SR_UTILS_NS::FileSystemWatcher::EventType::Add));

            m_fileDeletedSubscription = pFileSystemWatcher->Subscribe(SR_UTILS_NS::FileSystemWatcher::DELETED_EVENT_ID,
                std::bind(&ScriptSystem::HandleFileSystemEvent, this, std::placeholders::_1, SR_UTILS_NS::FileSystemWatcher::EventType::Delete));

            SR_LOG("ScriptSystem::Init() : creating script system thread...");

            m_threadRunning = true;

            SR_HTYPES_NS::Thread::Factory::Instance().Create(m_thread, &ScriptSystem::ThreadFunc, this);

            m_thread->SetName("Script system");
        }
        else {
            SR_LOG("ScriptSystem::Init() : script compilation is disabled!");
            return true;
        }

        SR_LOG("ScriptSystem::Init() : script system initialized successfully!");

        m_isInit = true;

        return true;
    }

    void ScriptSystem::HandleFileSystemEvent(const SR_UTILS_NS::SubscriptionMessage& message, SR_UTILS_NS::FileSystemWatcher::EventType eventType) {
        auto&& path = message.GetPathRef(SR_UTILS_NS::FileSystemWatcher::FILE_MSG_ID);
        if (path.IsSubPath(m_cacheFolder) || path.IsSubPath(m_apiFolder)) {
            return;
        }

        /// Ignore folders modifications and creations
        if (eventType != SR_UTILS_NS::FileSystemWatcher::EventType::Delete && !path.IsFile()) {
            return;
        }

        if (path.GetBaseNameView() == "libclang") {
            return;
        }

        SR_LOCK_GUARD;

        if (m_changedCppFiles.count(path) > 0 || m_changedModules.count(path) > 0 || m_changedCppModules.count(path) > 0) {
            m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
            return;
        }

        if (m_isCompilationEnabled) {
            if (path.GetBaseNameAndExt() == ENGINE_MODULE_FILE_NAME) {
                if (m_state != State::InitialAnalyse) {
                    SR_DEBUG_LOG("ScriptSystem::HandleFileSystemEvent() : engine module change detected!\n\tPath: {}", path);
                }
                m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
                m_changedModules.insert(path);
            }
            else if (ALLOWED_CPP_EXTENSIONS.find(path.GetExtensionView()) != ALLOWED_CPP_EXTENSIONS.end()) {
                if (m_state != State::InitialAnalyse) {
                    SR_DEBUG_LOG("ScriptSystem::HandleFileSystemEvent() : c++ file change detected!\n\tPath: {}", path);
                }
                m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
                m_changedCppFiles.insert(path);
            }
        }

        if (ALLOWED_CPP_MODULE_EXTENSIONS.find(path.GetExtensionView()) != ALLOWED_CPP_MODULE_EXTENSIONS.end()) {
            if (m_state != State::InitialAnalyse) {
                SR_DEBUG_LOG("ScriptSystem::HandleFileSystemEvent() : c++ module change detected!\n\tPath: {}", path);
            }
            m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
            m_changedCppModules.insert(path);
        }
    }

    void ScriptSystem::ThreadFunc() {
        SR_INFO("ScriptSystem::ThreadFunc() : script system thread started!");

        while (m_threadRunning) {
            SR_TRACY_ZONE_N("ScriptSystem");
            SR_PLATFORM_NS::Sleep(50);

            m_thread->Synchronize();

            {
                SR_LOCK_GUARD;
                if (m_lastFileSystemEvent + std::chrono::milliseconds(200) > SR_HTYPES_NS::Time::Instance().Now()) {
                    m_hasModuleReloadRequest = false;
                    continue;
                }
            }

            switch (m_state) {
                case State::InitialAnalyse:
                    InitialAnalyse();
                    m_state = State::Idle;
                    break;
                case State::Idle:
                    ThreadIdle();
                    break;
                case State::CheckModules: {
                    std::set<SR_UTILS_NS::Path> changedModules;
                    {
                        SR_LOCK_GUARD;
                        changedModules = SR_EXCHANGE(m_changedModules, {});
                    }
                    m_codeGenerator->ProcessChangedModules(changedModules);
                    m_state = State::Codegen;
                    break;
                }
                case State::Codegen: {
                    std::set<SR_UTILS_NS::Path> changedCppFiles;
                    {
                        SR_LOCK_GUARD;
                        changedCppFiles = SR_EXCHANGE(m_changedCppFiles, {});
                    }
                    m_codeGenerator->ProcessChangedCodeFiles(changedCppFiles);
                    if (m_codeGenerator->IsNeedRecompile()) {
                        m_codeGenerator->RegenerateChangedModules();
                        m_isCompiled = false;
                    }
                    m_state = State::Idle;
                    break;
                }
                case State::Compiling:
                    CompileModules();
                    if (!m_hasCompileErrors) {
                        CopyModules();
                    }
                    m_state = State::Idle;
                    m_isCompiled = true;
                    break;
                case State::Reloading:
                    ReloadModules();
                    m_state = State::Idle;
                    m_hasModuleReloadRequest = false;
                    break;
            }
        }

        SR_INFO("ScriptSystem::ThreadFunc() : script system thread stopped!");
    }

    void ScriptSystem::InitialAnalyse() {
        SR_UTILS_NS::FileSystem::ForEachFileInFolder(m_resourcesFolder, true, [this](const SR_UTILS_NS::Path& path) {
            SR_UTILS_NS::SubscriptionMessage message;
            message.SetPath(SR_UTILS_NS::FileSystemWatcher::FILE_MSG_ID, path);
            HandleFileSystemEvent(message, SR_UTILS_NS::FileSystemWatcher::EventType::Add);
        });
    }

    void ScriptSystem::ThreadIdle() {
        SR_LOCK_GUARD;

        /// first, check if we have any changes in the modules
        if (!m_changedModules.empty()) {
            m_state = State::CheckModules;
            m_hasModuleReloadRequest = false;
            return;
        }

        /// next, check if we have any changes in the cpp files
        if (!m_changedCppFiles.empty()) {
            if (SRVerify2(m_isCompilationEnabled, "Script system thread detected file changes but compilation is disabled!")) {
                SR_INFO("ScriptSystem::ThreadIdle() : script system thread detected file changes!");
                m_state = State::Codegen;
            }
            m_hasModuleReloadRequest = false;
            return;
        }

        /// after codegen we need to compile the code
        if (!m_isCompiled && m_isCompilationEnabled) {
            m_state = State::Compiling;
            m_hasModuleReloadRequest = false;
            return;
        }

        if (m_hasModuleCopyErrors || m_hasCompileErrors) {
            m_hasModuleReloadRequest = false;
            return;
        }

        if (m_hasModuleReloadRequest) {
            SR_INFO("ScriptSystem::ThreadIdle() : script system thread detected module reload request!");
            m_state = State::Reloading;
            return;
        }
    }

    void ScriptSystem::ResetSubscriptions() {
        m_fileChangedSubscription.Reset();
        m_fileCreatedSubscription.Reset();
        m_fileDeletedSubscription.Reset();
    }

    void ScriptSystem::CompileModules() {
        SR_LOG("ScriptSystem::CompileModules() : compiling modules...");
        SR_TRACY_ZONE;

        if (!m_isCompilationEnabled) {
            SRHalt("ScriptSystem::CompileModules() : script compilation is disabled! But compilation was requested!");
            return;
        }

        std::vector<SR_UTILS_NS::Path> includePaths;

        m_hasCompileErrors = false;

        for (auto&& module : m_codeGenerator->GetModules()) {
            if (module.isCompiled || !module.moduleInfo.enabled) {
                continue;
            }

            CppCompilerContext context;
            context.moduleName = module.moduleInfo.moduleName;
            context.outFolder = m_cacheFolder.Concat("Scripts/Modules/{}"_format(module.moduleInfo.moduleName));
            context.isDebug = true;
            context.isShared = true;

            for (auto&& filePath : module.codeFiles) {
                context.sourceFiles.emplace_back(filePath);
            }

            for (auto&& path : m_engineSourcesIncludePaths) {
                context.includePaths.emplace_back(path);
            }

            context.includePaths.emplace_back(module.path.GetFolder());
            context.includePaths.emplace_back(context.outFolder.Concat("Codegen"));

            if (!m_compiler->Compile(context)) {
                SR_ERROR("ScriptSystem::CompileModules() : failed to compile modules!");
                m_hasCompileErrors = true;
                return;
            }

            m_modulesToCopy.insert(module.moduleInfo.moduleName);
            m_codeGenerator->OnModuleCompiled(module.moduleInfo.moduleName);
        }
    }

    void ScriptSystem::CopyModules() {
        if (!m_isCompilationEnabled) {
            SRHalt("ScriptSystem::CopyModules() : script compilation is disabled! But copy was requested!");
            return;
        }

        if (m_hasCompileErrors) {
            SRHalt("ScriptSystem::CopyModules() : cannot copy modules! Compilation errors detected!");
            return;
        }

        if (m_modulesToCopy.empty()) {
            return;
        }

        SR_LOG("ScriptSystem::CopyModules() : copying recompiled modules...");

        m_hasModuleCopyErrors = false;

        for (auto&& moduleName : m_modulesToCopy) {
            const std::string_view extension = ScriptSystem::GetDynamicLibraryExtension();
            auto&& sourceModulePath = m_cacheFolder.Concat("Scripts/Modules/{}/{}.{}"_format(moduleName, moduleName, extension));
            auto&& sourcePdbPath = m_cacheFolder.Concat("Scripts/Modules/{}/{}.pdb.protected"_format(moduleName, moduleName));

            if (auto&& pModule = m_codeGenerator->GetModule(moduleName)) {
                auto&& destinationModulePath = pModule->path.GetFolder().Concat("{}.{}"_format(moduleName, extension));
                auto&& destinationPdbPath = pModule->path.GetFolder().Concat("{}.pdb"_format(moduleName));

                if (destinationModulePath.IsFile()) {
                    SR_PLATFORM_NS::Delete(destinationModulePath);
                }

                if (destinationPdbPath.IsFile()) {
                    SR_PLATFORM_NS::Delete(destinationPdbPath);
                }

                if (sourcePdbPath.IsFile()) {
                    if (SR_PLATFORM_NS::Copy(sourcePdbPath, destinationPdbPath)) {
                        SR_LOG("ScriptSystem::CopyModules() : pdb copied successfully!\n\tSource: {}\n\tDestination: {}", sourcePdbPath, destinationPdbPath);
                    }
                    else {
                        SR_ERROR("ScriptSystem::CopyModules() : failed to copy pdb!\n\tSource: {}\n\tDestination: {}", sourcePdbPath, destinationPdbPath);
                        m_hasModuleCopyErrors = true;
                        return;
                    }
                }

                if (SR_PLATFORM_NS::Copy(sourceModulePath, destinationModulePath)) {
                    SR_LOG("ScriptSystem::CopyModules() : module copied successfully!\n\tSource: {}\n\tDestination: {}", sourceModulePath, destinationModulePath);
                }
                else {
                    SR_ERROR("ScriptSystem::CopyModules() : failed to copy module!\n\tSource: {}\n\tDestination: {}", sourceModulePath, destinationModulePath);
                    m_hasModuleCopyErrors = true;
                    return;
                }
            }
            else {
                SR_WARN("ScriptSystem::CopyModules() : module not found!\n\tModule: {}", moduleName);
            }
        }

        m_modulesToCopy.clear();
    }

    void ScriptSystem::ReloadModules() {
        SR_TRACY_ZONE;
        SR_LOG("ScriptSystem::ReloadModules() : reloading modules...");

        std::set<SR_UTILS_NS::Path> changedCppModules = SR_EXCHANGE(m_changedCppModules, {});

        for (auto&& modulePath : changedCppModules) {
            if (m_moduleManager->ReloadModule(modulePath)) {
                SR_LOG("ScriptSystem::ReloadModules() : module reloaded successfully!\n\tPath: {}", modulePath);
            }
        }

        SR_LOG("ScriptSystem::ReloadModules() : reloading completed!");
    }

    std::string_view ScriptSystem::GetDynamicLibraryExtension() {
        const SR_UTILS_NS::PlatformType platform = SR_PLATFORM_NS::GetType();

        switch (platform) {
            case SR_UTILS_NS::PlatformType::Windows:
                return "dll";
            case SR_UTILS_NS::PlatformType::Linux:
            case SR_UTILS_NS::PlatformType::Android:
                return "so";
            default:
                SRHalt("CppCompiler::Compile() : unknown platform!");
                return "";
        }
    }

    void ScriptSystem::WaitForIdle() {
        if (GetState() == State::Idle || !m_threadRunning) {
            return;
        }

        SR_INFO("ScriptSystem::WaitForIdle() : waiting for script system idle...");

        while (m_state != State::Idle) {
            SR_PLATFORM_NS::Sleep(10);
        }
    }

    void ScriptSystem::ReloadModulesIfNeeded() {
        {
            SR_TRACY_ZONE;
            SR_LOCK_GUARD;

            if (m_hasModuleReloadRequest || m_state != State::Idle) {
                return;
            }

            if (m_hasModuleCopyErrors || m_hasCompileErrors) {
                return;
            }

            if (m_changedCppModules.empty()) {
                return;
            }

            m_hasModuleReloadRequest = true;
        }

        SR_TRACY_ZONE_N("Wait for module reload");

        while (m_hasModuleReloadRequest);
    }

    bool ScriptSystem::InitEngineSources() {
        m_pathToEngineSourcesRoot = m_engineResourcesFolder.Concat("API");
        if (!m_pathToEngineSourcesRoot.IsDir()) {
            SR_ERROR("ScriptSystem::InitEngineSources() : engine sources folder not found!\n\tPath: {}", m_pathToEngineSourcesRoot);
            return false;
        }

        SR_LOG("ScriptSystem::InitEngineSources() : engine sources root: {}", m_pathToEngineSourcesRoot);

        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Codegen"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Audio/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Graphics/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Physics/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Utils/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Utils/libs"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Utils/libs/entt/src"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Utils/libs/icu"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Utils/libs/fmt/include"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Utils/libs/tracy/tracy"));
        m_engineSourcesIncludePaths.emplace_back(m_pathToEngineSourcesRoot.Concat("Engine/libs/Scripting/inc"));

        for (auto&& path : m_engineSourcesIncludePaths) {
            if (!path.IsDir()) {
                SR_ERROR("ScriptSystem::InitEngineSources() : engine sources folder not found!\n\tPath: {}", path);
                return false;
            }
        }

        return true;
    }
}
