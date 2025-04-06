//
// Created by Monika on 02.04.2025.
//

#include <Scripting/Cpp/ScriptSystem.h>
#include <Utils/Common/Features.h>
#include <Utils/FileSystem/FileSystem.h>

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
    }

    bool ScriptSystem::Init() {
        if (m_isInit) {
            SRHalt("ScriptSystem::Init() : script system already initialized!");
            return false;
        }

        m_isInit = true;

        SR_LOG("ScriptSystem::Init() : initializing script system...");

        m_resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        m_cacheFolder = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
        m_apiFolder = m_resourcesFolder.Concat("SpaRcleAPI");

        m_isCompilationEnabled = SR_UTILS_NS::Features::Instance().Enabled("ScriptCompilation", true);

        if (m_isCompilationEnabled) {
            SR_LOG("ScriptSystem::Init() : script compilation is enabled!");

            m_compiler = CppCompiler::MakeShared();
            m_codeGenerator = CppCodeGenerator::MakeShared();

            if (!m_compiler->Init()) {
                SR_ERROR("ScriptSystem::Init() : failed to initialize c++ compiler!");
                return false;
            }

            if (!m_codeGenerator->Init()) {
                SR_ERROR("ScriptSystem::Init() : failed to initialize code generator!");
                return false;
            }
        }
        else {
            SR_LOG("ScriptSystem::Init() : script compilation is disabled!");
            return true;
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

        SR_LOG("ScriptSystem::Init() : script system initialized successfully!");

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

        if (m_isCompilationEnabled) {
            if (path.GetBaseNameAndExt() == ENGINE_MODULE_FILE_NAME) {
                SR_WRITE_LOCK;
                if (m_state != State::InitialAnalyse) {
                    SR_LOG("ScriptSystem::HandleFileSystemEvent() : engine module change detected!\n\tPath: {}", path);
                }
                m_changedModules.insert(path);
            }
            else if (ALLOWED_CPP_EXTENSIONS.find(path.GetExtensionView()) != ALLOWED_CPP_EXTENSIONS.end()) {
                SR_WRITE_LOCK;
                if (m_state != State::InitialAnalyse) {
                    SR_LOG("ScriptSystem::HandleFileSystemEvent() : c++ file change detected!\n\tPath: {}", path);
                }
                m_changedCppFiles.insert(path);
            }
        }

        if (ALLOWED_CPP_MODULE_EXTENSIONS.find(path.GetExtensionView()) != ALLOWED_CPP_MODULE_EXTENSIONS.end()) {
            SR_WRITE_LOCK;
            if (m_state != State::InitialAnalyse) {
                SR_LOG("ScriptSystem::HandleFileSystemEvent() : c++ module change detected!\n\tPath: {}", path);
            }
            m_changedCppModules.insert(path);
        }
    }

    void ScriptSystem::ThreadFunc() {
        SR_INFO("ScriptSystem::ThreadFunc() : script system thread started!");

        while (m_threadRunning) {
            SR_TRACY_ZONE_N("ScriptSystem");

            m_thread->Synchronize();

            switch (m_state) {
                case State::InitialAnalyse:
                    InitialAnalyse();
                    m_state = State::Idle;
                    break;
                case State::Idle:
                    ThreadIdle();
                    break;
                case State::CheckModules: {
                    std::set<SR_UTILS_NS::Path> changedModules; {
                        SR_WRITE_LOCK;
                        changedModules = SR_EXCHANGE(m_changedModules, {});
                    }
                    m_codeGenerator->ProcessChangedModules(changedModules);
                    m_state = State::Codegen;
                    break;
                }
                case State::Codegen: {
                    std::set<SR_UTILS_NS::Path> changedCppFiles; {
                        SR_WRITE_LOCK;
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
                    m_state = State::Idle;
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
        /// first, check if we have any changes in the modules
        {
            SR_READ_LOCK;
            if (!m_changedModules.empty()) {
                m_state = State::CheckModules;
                return;
            }
        }

        /// next, check if we have any changes in the cpp files
        {
            SR_READ_LOCK;
            if (!m_changedCppFiles.empty()) {
                if (SRVerify2(m_isCompilationEnabled, "Script system thread detected file changes but compilation is disabled!")) {
                    SR_LOG("ScriptSystem::ThreadIdle() : script system thread detected file changes!");
                    m_state = State::Codegen;
                }
                return;
            }
        }

        /// after codegen we need to compile the code
        if (!m_isCompiled && m_isCompilationEnabled) {
            m_state = State::Compiling;
            return;
        }

        if (m_hasModuleCopyErrors || m_hasCompileErrors) {
            return;
        }

        /// if all files are compiled we need to check if we have any changes in the c++ modules
        {
            SR_READ_LOCK;
            if (!m_changedCppModules.empty()) {
                SR_LOG("ScriptSystem::ThreadIdle() : script system thread detected cpp module changes!");
                m_state = State::Reloading;
                return;
            }
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

        m_hasCompileErrors = false;

        for (auto&& module : m_codeGenerator->GetModules()) {
            if (module.isCompiled) {
                continue;
            }

            CppCompilerContext context;
            context.moduleName = module.moduleInfo.moduleName;
            context.outFolder = m_cacheFolder.Concat("Scripts/Modules/{}"_format(module.moduleInfo.moduleName));
            context.isDebug = true;
            context.isShared = true;

            for (auto&& [filePath, metadata] : module.codeFiles) {
                context.sourceFiles.emplace_back(filePath);
            }

            context.includePaths.emplace_back(m_resourcesFolder.Concat("SpaRcleAPI"));
            context.includePaths.emplace_back(module.path.GetFolder());

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
            auto&& sourceModulePath = m_cacheFolder.Concat("Scripts/Modules/{}"_format(moduleName));

            if (auto&& pModule = m_codeGenerator->GetModule(moduleName)) {
                auto&& destinationModulePath = pModule->path.GetFolder().Concat("{}.{}"_format(moduleName, m_compiler->GetDynamicModuleExtension()));

                if (destinationModulePath.IsFile()) {
                    SR_PLATFORM_NS::Delete(destinationModulePath);
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
    }

    void ScriptSystem::ReloadModules() {

    }
}
