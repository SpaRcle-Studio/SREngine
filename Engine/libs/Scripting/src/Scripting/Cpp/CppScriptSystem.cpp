//
// Created by Monika on 02.04.2025.
//

#include <Scripting/Cpp/CppScriptSystem.h>

#include <Utils/Common/Bind.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/FileSystem/IVFSBackend.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Types/Time.h>
#include <Utils/TypeTraits/Factory.h>

#include <Enum/PlatformType.hpp>
#include <Enum/BuildType.hpp>

namespace SR_SCRIPTING_NS {
    CppScriptSystem::~CppScriptSystem() {
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

    bool CppScriptSystem::Init(bool compilationEnabled) {
        if (m_isInit) {
            SRHalt("CppScriptSystem::Init() : script system already initialized!");
            return false;
        }

        SR_LOG("CppScriptSystem::Init() : initializing script system...");

        m_cacheFolder = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
        SR_UTILS_NS::VFS::Instance().ResolvePath(m_cacheFolder, SR_UTILS_NS::FileMode::Write);

        m_isCompilationEnabled = compilationEnabled;
    #ifdef SR_ENGINE_STATIC_LIBRARY
        if (SR_UTILS_NS::StoreUtils::Temp::GetBool("ApplicationHasEmbeddedResources", false)) {
            m_isCompilationEnabled = false;
            SR_INFO("CppScriptSystem::Init() : compilation disabled by embedded resources!");
        }
    #endif
        m_apiFolder = CoreResLoader::GetResPath().Concat("API");

        if (m_isCompilationEnabled && !InitEngineSources()) {
            SR_ERROR("CppScriptSystem::Init() : failed to initialize engine sources!");
            return false;
        }

        m_moduleManager = ModuleManager::MakeShared(this);

        if (!m_moduleManager->Init()) {
            SR_ERROR("CppScriptSystem::Init() : failed to initialize module manager!");
            return false;
        }

        if (m_isCompilationEnabled) {
            SR_LOG("CppScriptSystem::Init() : script compilation is enabled!");

            m_compiler = CppCompiler::MakeShared(this);
            m_codeGenerator = CppCodeGenerator::MakeShared(this);

            m_codeGenerator->SetCompiler(m_compiler.Get());

            if (!m_compiler->Init()) {
                if (!SR_UTILS_NS::StoreUtils::User::GetBool("CompilerUserCanceled", false)) {
                    SR_ERROR("CppScriptSystem::Init() : failed to initialize c++ compiler!");
                }
                m_state = ScriptSystemState::Idle;
                m_threadRunning = false;
                return false;
            }

            if (!m_codeGenerator->Init()) {
                SR_ERROR("CppScriptSystem::Init() : failed to initialize code generator!");
                m_state = ScriptSystemState::Idle;
                m_threadRunning = false;
                return false;
            }

        }
        else {
            m_isInit = true;
            SR_LOG("CppScriptSystem::Init() : script compilation is disabled!");
            return true;
        }

        SR_LOG("CppScriptSystem::Init() : script system initialized successfully!");

        m_isInit = true;

        return true;
    }

    void CppScriptSystem::Start() {
        if (!m_isInit || m_thread) {
            SRHalt("CppScriptSystem::Start() : system must be initialized and not started!");
            return;
        }
        m_threadRunning = true;
        SR_HTYPES_NS::Thread::Factory::Instance().Create(m_thread, &CppScriptSystem::ThreadFunc, this);
        m_thread->SetName("C++ script system");
    }

    void CppScriptSystem::HandleFileEvent(const SR_UTILS_NS::Path& path) {
        SR_LOCK_GUARD;

        if (m_changedCppFiles.count(path) > 0 || m_changedModules.count(path) > 0 || m_changedCppModules.count(path) > 0) {
            m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
            return;
        }

        if (m_isCompilationEnabled) {
            if (path.GetBaseNameAndExtView() == ENGINE_MODULE_FILE_NAME) {
                if (m_state != ScriptSystemState::InitialAnalyse) {
                    SR_DEBUG_LOG("CppScriptSystem::HandleFileSystemEvent() : engine module change detected!\n\tPath: {}", path);
                }
                m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
                m_changedModules.insert(path);
            }
            else if (ALLOWED_CPP_EXTENSIONS.find(path.GetExtensionView()) != ALLOWED_CPP_EXTENSIONS.end()) {
                if (m_state != ScriptSystemState::InitialAnalyse) {
                    SR_DEBUG_LOG("CppScriptSystem::HandleFileSystemEvent() : c++ file change detected!\n\tPath: {}", path);
                }
                m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
                m_changedCppFiles.insert(path);
            }
        }

        if (ALLOWED_CPP_MODULE_EXTENSIONS.find(path.GetExtensionView()) != ALLOWED_CPP_MODULE_EXTENSIONS.end()) {
            if (m_state != ScriptSystemState::InitialAnalyse) {
                SR_DEBUG_LOG("CppScriptSystem::HandleFileSystemEvent() : c++ module change detected!\n\tPath: {}", path);
            }
            m_lastFileSystemEvent = SR_HTYPES_NS::Time::Instance().Now();
            m_changedCppModules.insert(path);
        }
    }

    bool CppScriptSystem::ThreadFunc() {
        SR_TRACY_ZONE_N("CppScriptSystem");

        if (!m_threadRunning) {
            SR_INFO("CppScriptSystem::ThreadFunc() : script system thread stopped!");
            m_state = ScriptSystemState::Idle;
            return false;
        }

    #ifdef SR_THREADS_ALLOWED
        SR_PLATFORM_NS::Sleep(5);
    #endif

        m_thread->Synchronize();

        {
            SR_LOCK_GUARD;
            if (m_lastFileSystemEvent + std::chrono::milliseconds(200) > SR_HTYPES_NS::Time::Instance().Now()) {
                m_hasModuleReloadRequest = false;
                return true;
            }
        }

        switch (m_state) {
            case ScriptSystemState::InitialAnalyse:
                ThreadIdle();
                if (m_state == ScriptSystemState::InitialAnalyse) {
                    m_state = ScriptSystemState::Idle;
                }
                break;
            case ScriptSystemState::Idle:
                ThreadIdle();
                break;
            case ScriptSystemState::CheckModules: {
                SR_UTILS_NS::Set<SR_UTILS_NS::Path> changedModules;
                {
                    SR_LOCK_GUARD;
                    changedModules = SR_EXCHANGE(m_changedModules, {});
                }
                m_codeGenerator->ProcessChangedModules(changedModules);
                m_state = ScriptSystemState::Codegen;
                break;
            }
            case ScriptSystemState::Codegen: {
                SR_UTILS_NS::Set<SR_UTILS_NS::Path> changedCppFiles;
                {
                    SR_LOCK_GUARD;
                    changedCppFiles = SR_EXCHANGE(m_changedCppFiles, {});
                }
                m_codeGenerator->ProcessChangedCodeFiles(changedCppFiles);
                if (m_codeGenerator->IsNeedRecompile()) {
                    m_codeGenerator->RegenerateChangedModules();
                    m_isCompiled = false;
                }
                ThreadIdle();
                if (m_state == ScriptSystemState::Codegen) {
                    m_state = ScriptSystemState::Idle;
                }
                break;
            }
            case ScriptSystemState::Compiling:
                CompileModules();
                if (!m_hasCompileErrors) {
                    CopyModules();
                }
                m_isCompiled = true;
                ThreadIdle();
                if (m_state == ScriptSystemState::Compiling) {
                    m_state = ScriptSystemState::Idle;
                }
                break;
            case ScriptSystemState::Reloading:
                ReloadModules();
                m_state = ScriptSystemState::Idle;
                m_hasModuleReloadRequest = false;
                break;
        }

        return true;
    }

    void CppScriptSystem::ThreadIdle() {
        SR_LOCK_GUARD;

        if (!m_threadRunning) {
            m_state = ScriptSystemState::Idle;
            return;
        }

        /// first, check if we have any changes in the modules
        if (!m_changedModules.empty()) {
            m_state = ScriptSystemState::CheckModules;
            m_hasModuleReloadRequest = false;
            return;
        }

        /// next, check if we have any changes in the cpp files
        if (!m_changedCppFiles.empty()) {
            if (SRVerify2(m_isCompilationEnabled, "Script system thread detected file changes but compilation is disabled!")) {
                SR_INFO("CppScriptSystem::ThreadIdle() : script system thread detected file changes!");
                m_state = ScriptSystemState::Codegen;
            }
            m_hasModuleReloadRequest = false;
            return;
        }

        /// after codegen we need to compile the code
        if (!m_isCompiled && m_isCompilationEnabled) {
            m_state = ScriptSystemState::Compiling;
            m_hasModuleReloadRequest = false;
            return;
        }

        if (m_hasModuleCopyErrors || m_hasCompileErrors) {
            m_hasModuleReloadRequest = false;
            return;
        }

        if (m_hasModuleReloadRequest) {
            SR_INFO("CppScriptSystem::ThreadIdle() : script system thread detected module reload request!");
            m_state = ScriptSystemState::Reloading;
            return;
        }
    }

    void CppScriptSystem::CompileModules() {
        SR_LOG("CppScriptSystem::CompileModules() : compiling modules...");
        SR_TRACY_ZONE;

        if (!m_isCompilationEnabled) {
            SRHalt("CppScriptSystem::CompileModules() : script compilation is disabled! But compilation was requested!");
            return;
        }

        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> includePaths;

        m_hasCompileErrors = false;

        SR_UTILS_NS::Path modulesPath = m_cacheFolder.Concat("Scripts/Modules-{}-{}"_format(SR_PLATFORM_NS::GetType(), SR_PLATFORM_NS::GetBuildType()));

        for (auto&& module : m_codeGenerator->GetModules()) {
            if (module.isCompiled || !module.moduleInfo.enabled) {
                continue;
            }

            CppCompilerContext context;
            context.moduleName = module.moduleInfo.moduleName;
            context.outFolder = modulesPath.Concat(module.moduleInfo.moduleName);

        #ifdef SR_RELEASE
            context.isDebug = false;
        #else
            context.isDebug = true;
        #endif

            context.isShared = true;

            for (auto&& filePath : module.codeFiles) {
                context.sourceFiles.emplace_back(filePath);
            }

            for (auto&& path : m_engineSourcesIncludePaths) {
                context.includePaths.emplace_back(path);
            }

            auto&& codegenFolder = context.outFolder.Concat("Codegen");
            if (!codegenFolder.CreateDirectories()) {
                SR_ERROR("CppScriptSystem::CompileModules() : failed to create codegen folder! \n\tPath: {}", codegenFolder);
                m_hasCompileErrors = true;
                return;
            }

            context.includePaths.emplace_back(codegenFolder);

            for (auto&& path : context.includePaths) {
                SR_UTILS_NS::VFS::Instance().ResolvePath(path, SR_UTILS_NS::FileMode::Read);
            }

            SR_UTILS_NS::Path moduleFolder = module.path;
            SR_UTILS_NS::VFS::Instance().ResolvePath(moduleFolder, SR_UTILS_NS::FileMode::Read);
            context.includePaths.emplace_back(moduleFolder.GetFolder());

            if (!m_compiler->Compile(context)) {
                SR_ERROR("CppScriptSystem::CompileModules() : failed to compile modules!");
                m_hasCompileErrors = true;
                return;
            }

            m_modulesToCopy.insert(module.moduleInfo.moduleName);
            m_codeGenerator->OnModuleCompiled(module.moduleInfo.moduleName);
        }

        SR_LOG("CppScriptSystem::CompileModules() : modules compiled!");
    }

    void CppScriptSystem::CopyModules() {
        if (!m_isCompilationEnabled) {
            SRHalt("CppScriptSystem::CopyModules() : script compilation is disabled! But copy was requested!");
            return;
        }

        if (m_hasCompileErrors) {
            SRHalt("CppScriptSystem::CopyModules() : cannot copy modules! Compilation errors detected!");
            return;
        }

        if (m_modulesToCopy.empty()) {
            return;
        }

        SR_LOG("CppScriptSystem::CopyModules() : copying recompiled modules...");

        m_hasModuleCopyErrors = false;

        SR_UTILS_NS::Path modulesPath = m_cacheFolder.Concat("Scripts/Modules-{}-{}"_format(SR_PLATFORM_NS::GetType(), SR_PLATFORM_NS::GetBuildType()));

        for (auto&& moduleName : m_modulesToCopy) {
            const SR_UTILS_NS::StringView extension = CppScriptSystem::GetDynamicLibraryExtension();
            auto&& sourceModulePath = modulesPath.Concat("{}/{}.{}"_format(moduleName, moduleName, extension));
            auto&& sourcePdbPath = modulesPath.Concat("{}/{}.pdb.protected"_format(moduleName, moduleName));

            if (auto&& pModule = m_codeGenerator->GetModule(moduleName)) {
                auto&& destinationModulePath = pModule->path.GetFolder().Concat("{}.{}"_format(moduleName, extension));
                auto&& destinationPdbPath = pModule->path.GetFolder().Concat("{}.pdb"_format(moduleName));

                if (destinationModulePath.IsFile()) {
                    SR_UTILS_NS::VFS::Instance().Delete(destinationModulePath);
                }

                if (destinationPdbPath.IsFile()) {
                    SR_UTILS_NS::VFS::Instance().Delete(destinationPdbPath);
                }

                if (sourcePdbPath.IsFile()) {
                    if (SR_UTILS_NS::VFS::Instance().Copy(sourcePdbPath, destinationPdbPath)) {
                        SR_LOG("CppScriptSystem::CopyModules() : pdb copied successfully!\n\tSource: {}\n\tDestination: {}", sourcePdbPath, destinationPdbPath);
                    }
                    else {
                        SR_ERROR("CppScriptSystem::CopyModules() : failed to copy pdb!\n\tSource: {}\n\tDestination: {}", sourcePdbPath, destinationPdbPath);
                        m_hasModuleCopyErrors = true;
                        return;
                    }
                }

                if (SR_UTILS_NS::VFS::Instance().Copy(sourceModulePath, destinationModulePath)) {
                    SR_LOG("CppScriptSystem::CopyModules() : module copied successfully!\n\tSource: {}\n\tDestination: {}", sourceModulePath, destinationModulePath);
                }
                else {
                    SR_ERROR("CppScriptSystem::CopyModules() : failed to copy module!\n\tSource: {}\n\tDestination: {}", sourceModulePath, destinationModulePath);
                    m_hasModuleCopyErrors = true;
                    return;
                }
            }
            else {
                SR_WARN("CppScriptSystem::CopyModules() : module not found!\n\tModule: {}", moduleName);
            }
        }

        m_modulesToCopy.clear();
    }

    void CppScriptSystem::ReloadModules() {
        SR_TRACY_ZONE;
        SR_LOG("CppScriptSystem::ReloadModules() : reloading modules...");

        SR_UTILS_NS::Set<SR_UTILS_NS::Path> changedCppModules;
        {
            SR_LOCK_GUARD;
            if (m_forceReloadModules.exchange(false) && m_codeGenerator) {
                for (auto&& module : m_codeGenerator->GetModules()) {
                    if (!module.moduleInfo.enabled) {
                        continue;
                    }
                    const auto modulePath = module.path.GetFolder().Concat(module.moduleInfo.moduleName).ConcatExt(GetDynamicLibraryExtension());
                    m_changedCppModules.insert(modulePath);
                }
            }
            changedCppModules = SR_EXCHANGE(m_changedCppModules, {});
        }

        for (auto&& modulePath : changedCppModules) {
            if (m_moduleManager->ReloadModule(modulePath)) {
                SR_LOG("CppScriptSystem::ReloadModules() : module reloaded successfully!\n\tPath: {}", modulePath);
            }
        }

        SR_LOG("CppScriptSystem::ReloadModules() : reloading completed!");
    }

    SR_UTILS_NS::StringView CppScriptSystem::GetDynamicLibraryExtension() {
        const SR_UTILS_NS::PlatformType platform = SR_PLATFORM_NS::GetType();

        switch (platform) {
            case SR_UTILS_NS::PlatformType::Windows:
                return "dll";
            case SR_UTILS_NS::PlatformType::Linux:
            case SR_UTILS_NS::PlatformType::Android:
            case SR_UTILS_NS::PlatformType::Emscripten:
                return "so";
            default:
                SRHalt("CppScriptSystem::Compile() : unknown platform!");
                return "";
        }
    }

    SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> CppScriptSystem::GetBehaviourNames() const {
        auto&& factory = SR_UTILS_NS::Factory::Instance();
        auto names = factory.GetInheritances(CppBehaviour::GetClassStaticName());
        names.erase_if([&factory](const auto& name) { return factory.IsAbstract(name); });
        return names;
    }

    void CppScriptSystem::WaitForIdle() {
        if (GetState() == ScriptSystemState::Idle || !m_threadRunning) {
            return;
        }

        SR_INFO("CppScriptSystem::WaitForIdle() : waiting for script system idle...");

        while (m_state != ScriptSystemState::Idle) {
            SR_HTYPES_NS::Time::Instance().Update();
            SR_PLATFORM_NS::Sleep(10);
        }
    }

    void CppScriptSystem::ReloadModulesIfNeeded() {
        {
            SR_TRACY_ZONE;
            SR_LOCK_GUARD;

            if (m_hasModuleReloadRequest || m_state != ScriptSystemState::Idle) {
                return;
            }

            if (m_hasModuleCopyErrors || m_hasCompileErrors) {
                return;
            }

            if (m_changedCppModules.empty() && !m_forceReloadModules) {
                return;
            }

            m_hasModuleReloadRequest = true;
        }

        SR_TRACY_ZONE_N("Wait for module reload");

        while (m_hasModuleReloadRequest);
    }

    void CppScriptSystem::SetReloadRequest() {
        SR_LOCK_GUARD;
        m_forceReloadModules = true;
    }

    bool CppScriptSystem::InitEngineSources() {
        if (!m_apiFolder.IsDir()) {
            SR_ERROR("CppScriptSystem::InitEngineSources() : engine sources folder not found!\n\tPath: {}", m_apiFolder);
            m_hasCompileErrors = true;
            return false;
        }

        SR_LOG("CppScriptSystem::InitEngineSources() : engine sources root: {}", m_apiFolder);

        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Codegen"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Audio/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Graphics/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Physics/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Utils/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Utils/libs"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Utils/libs/fmt/include"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Utils/libs/tracy/public"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/Scripting/inc"));
        m_engineSourcesIncludePaths.emplace_back(m_apiFolder.Concat("Engine/libs/ImmediateGUI/inc"));

        for (auto&& path : m_engineSourcesIncludePaths) {
            if (!path.IsDir()) {
                SR_ERROR("CppScriptSystem::InitEngineSources() : engine sources folder not found!\n\tPath: {}", path);
                return false;
            }
        }

        return true;
    }
}
