//
// Created by Monika on 14.09.2023.
//

#include <Engine/Application.h>
#include <Engine/World/World.h>
#include <Engine/Engine.h>

#include <Graphics/Types/Shader.h>
#include <Graphics/Memory/CameraManager.h>
#include <Graphics/Memory/MeshManager.h>

#include <Audio/Sound.h>
#include <Audio/SoundManager.h>
#include <Audio/RawSound.h>

#include <Scripting/Base/Behaviour.h>
#include <Scripting/Cpp/ScriptSystem.h>

#include <Physics/PhysicsMaterial.h>
#include <Physics/PhysicsLib.h>

#include <Utils/Common/Numeric.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/TaskManager/TaskManager.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Localization/Encoding.h>
#include <Utils/Platform/Platform.h>
#include <Utils/ECS/LayerManager.h>
#include <Utils/Common/CLIManager.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Types/Time.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Platform/Stacktrace.h>
#include <Utils/Network/GitHubDownloader.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/DirectoryVFSBackend.h>
#include <Utils/FileSystem/AndroidVFSBackend.h>
#include <Utils/FileSystem/GitHubVFSBackend.h>

namespace SR_CORE_NS {
    Application::Application()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    Application::~Application() {
        Close();
        SR_UTILS_NS::Debug::DestroySingleton();
    }

    bool Application::PreInit() {
        SR_TRACY_ZONE;

        SR_UTILS_NS::Localization::SetLocale();
        SR_UTILS_NS::Random::Initialize();

        if (SR_UTILS_NS::CLIManager::Instance().IsHeadlessMode()) {
            /// Эмулируем пустые состояния устройств ввода, так как нет возможности получать реальные данные от устройств в headless режиме.
            SR_PLATFORM_NS::SetOverriddenMouseState(SR_PLATFORM_NS::MouseState());
            SR_PLATFORM_NS::SetOverriddenKeyboardState(SR_PLATFORM_NS::KeyboardState());
        }

        SR_UTILS_NS::Path path;
        if (auto&& logPath = SR_PLATFORM_NS::GetApplicationLogPath()) {
            path = logPath.value();
        }
        else {
            auto&& appPath = SR_PLATFORM_NS::GetApplicationPath();
            path = SR_UTILS_NS::StringUtils::GetDirToFileFromFullPath(appPath);
        }

        SR_UTILS_NS::Path logDir = SR_UTILS_NS::CLIManager::Instance().GetOptionValue(SR_UTILS_NS::CLIOptions::LogDir).value_or(path.ToString());

        return InitLogger(logDir);
    }

    bool Application::EarlyInit() {
        SR_TRACY_ZONE;

        if (!SR_UTILS_NS::Debug::Instance().IsInitialized()) {
            SR_PLATFORM_NS::WriteConsoleError("Logger is not initialized!\n");
            return false;
        }

        SR_SYSTEM_LOG("Application::EarlyInit() : early initializing application...");

        if (SR_MATH_NS::HasSSE41()) {
            SR_SYSTEM_LOG("Application::EarlyInit() : SSE4.1 is supported.");
        }
        else {
            SR_SYSTEM_LOG("Application::EarlyInit() : SSE4.1 is NOT supported.");
        }

        SR_HTYPES_NS::Thread::Factory::Instance().SetMainThread();
        SR_HTYPES_NS::Time::Instance().Update();

        SR_UTILS_NS::Features::Instance().SetPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Engine/Configs/Features.xml"));
        SR_UTILS_NS::Features::Instance().Reload();

        if (SR_UTILS_NS::Features::Instance().Enabled("SegmentationHandler", false)) {
            SR_PLATFORM_NS::InitSegmentationHandler();
        }

        if (SR_UTILS_NS::Features::Instance().Enabled("DisableStackTrace", false)) {
            SR_UTILS_NS::DisableStacktrace();
        }

        if (SR_UTILS_NS::Features::Instance().Enabled("ResourceUsePointStackTraceProfiling", false)) {
            SR_UTILS_NS::ResourceManager::Instance().EnableStackTraceProfiling();
        }

        SR_UTILS_NS::StoreUtils::Storage::Instance().Load();

        return true;
    }

    bool Application::InitializeResourcesFolder() {
        SR_LOG("Application::InitializeResourcesFolder() : initializing resources folder...");

        auto&& engineResourcesPath = SR_PLATFORM_NS::GetApplicationResourcesPath();
        auto&& resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

        SR_UTILS_NS::VFS::Instance().UnmountAll();

        bool projectPathMounted = false;

        if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Android) {
            /// ресурсы упакованы в assets вместе с папкой "Resources", поэтому бекенд монтируется
            /// в корень и виртуальные пути совпадают с путями внутри apk
            SR_UTILS_NS::VFS::Instance().Mount("", new SR_UTILS_NS::AndroidVFSBackend(), -100);
            projectPathMounted = true;
        }

        /// в assets писать нельзя, поэтому всё изменяемое (кеш, конфиги) уходит в папку данных
        /// приложения. Она монтируется поверх ресурсов, чтобы изменённые файлы имели приоритет
        if (auto&& dataPath = SR_PLATFORM_NS::GetApplicationDataPath(); dataPath && !dataPath->empty()) {
            SR_UTILS_NS::VFS::Instance().Mount("", new SR_UTILS_NS::DirectoryVFSBackend(*dataPath), -75);
        }

        if (auto&& appFolder = SR_PLATFORM_NS::GetApplicationDirectory(); !appFolder.empty()) {
            SR_UTILS_NS::VFS::Instance().Mount("", new SR_UTILS_NS::ReadOnlyDirectoryVFSBackend(appFolder), -50);
        }

        if (auto&& projectPath = SR_UTILS_NS::CLIManager::Instance().GetProjectPath()) {
            auto&& projectResourcesPath = SR_PLATFORM_NS::GetPathType(*projectPath) == SR_UTILS_NS::FSItemType::File
                ? projectPath->GetFolder().Concat("Resources")
                : projectPath->Concat("Resources");

            if (SR_PLATFORM_NS::IsDirectoryExists(projectResourcesPath) && projectResourcesPath != engineResourcesPath) {
                auto&& pEngineReadOnlyBackend = new SR_UTILS_NS::ReadOnlyDirectoryVFSBackend(engineResourcesPath);

                pEngineReadOnlyBackend->AddIgnoredExtension("so");
                pEngineReadOnlyBackend->AddIgnoredExtension("pdb");
                pEngineReadOnlyBackend->AddIgnoredExtension("dll");

                SR_UTILS_NS::VFS::Instance().Mount(resourcesPath, pEngineReadOnlyBackend, 0);
                SR_UTILS_NS::VFS::Instance().Mount(resourcesPath, new SR_UTILS_NS::DirectoryVFSBackend(projectResourcesPath), 100);
                projectPathMounted = true;
            }
        }

        if (auto&& gameLink = SR_UTILS_NS::CLIManager::Instance().GetOptionValue(SR_UTILS_NS::CLIOptions::GameLink)) {
            SR_INFO("Application::InitializeResourcesFolder() : game link detected: \"{}\".", gameLink.value());
            SR_UTILS_NS::VFS::Instance().Mount(resourcesPath, new SR_UTILS_NS::DirectoryVFSBackend(engineResourcesPath), 0);
            SR_UTILS_NS::VFS::Instance().Mount("", new SR_UTILS_NS::GitHubVFSBackend(gameLink.value()), 50);
            projectPathMounted = true;
        }

        if (!projectPathMounted) {
            SR_UTILS_NS::VFS::Instance().Mount(resourcesPath, new SR_UTILS_NS::DirectoryVFSBackend(engineResourcesPath), 0);
        }

        if (!SR_UTILS_NS::VFS::Instance().CreateDirectories(CoreResLoader::GetCachePath())) {
            SR_ERROR("Application::InitializeResourcesFolder() : failed to create cache folder!");
            return false;
        }

        return true;
    }

    bool Application::InitLogger(const SR_UTILS_NS::Path& logDir) {
        if (SR_UTILS_NS::Debug::Instance().IsInitialized()) {
            return true;
        }

        SR_UTILS_NS::Debug::Instance().Initialize(logDir.Concat("srengine.log"), true, SR_UTILS_NS::Debug::Theme::Dark);
        SR_UTILS_NS::Debug::Instance().SetLevel(SR_UTILS_NS::Debug::Level::Low);
        return true;
    }

    bool Application::Init() {
        SR_TRACY_ZONE;

        SR_SYSTEM_LOG("Application::Init() : initializing application...");

        SR_LOG("Application::Init() : loaded {} tags.", SR_UTILS_NS::TagManager::Instance().GetTags().size());

        SR_WORLD_NS::SceneAllocator::Instance().Init([]() -> SR_WORLD_NS::Scene* {
            return new SR_CORE_NS::World();
        });

        m_engine = SR_CORE_NS::Engine::MakeShared(this);

        if (!m_engine->Create()) {
            SR_ERROR("Application::Init() : failed to create game engine!");
            return false;
        }

        if (!m_engine->Init()) {
            SR_ERROR("Application::Init() : failed to initialize game engine!");
            return false;
        }

        if (!m_engine->Run()) {
            SR_ERROR("Application::Init() : failed to run game engine!");
            return false;
        }

        SR_SYSTEM_LOG("Application::Init() : all systems started successfully!");

        return true;
    }

    bool AppMainLoop(void* pApplication) {
        return static_cast<Application*>(pApplication)->MainLoop();
    }

    bool Application::MainLoop() {
        SR_TRACY_ZONE;

        if (!SR_PLATFORM_NS::IsSupportThreads()) {
            SR_HTYPES_NS::Thread::Factory::Instance().ManuallyUpdateThreads();
        }

        if (m_isNeedReload) {
            Close();
            if (!InitializeResourcesFolder()) {
                SR_ERROR("Application::MainLoop() : failed to initialize resources folder!");
                m_hasErrors = true;
                return false;
            }

            m_hasErrors |= !Init();
            m_isNeedReload = false;
            if (m_hasErrors) {
                SR_ERROR("Application::MainLoop() : failed to reload application!");
                return false;
            }
        }

        if (!m_engine) {
            SR_ERROR("Application::MainLoop() : engine lost!");
            m_hasErrors = true;
            return false;
        }

        if (!m_engine->Execute()) {
            SR_SYSTEM_LOG("Application::MainLoop() : engine is not alive!");
            return false;
        }

        return true;
    }

    bool Application::Execute() {
        SR_TRACY_ZONE;

        SR_INFO("Application::Execute() : waiting for the application to close...");

        m_hasErrors = false;

        if (m_engine) {
            auto&& optionPath =  SR_UTILS_NS::CLIManager::Instance().GetOptionValue(SR_UTILS_NS::CLIOptions::RunScene);
            if (optionPath.has_value()) {
                SR_LOG("Application::Execute() : command line option to run scene detected: {}", optionPath.value());

                auto&& path = optionPath.value();
                m_engine->RunSceneGameMode(path);
            }
            else if (SR_UTILS_NS::Features::Instance().Enabled("RunGameModeOnStart", false)) {
                SR_UTILS_NS::Path startSceneConfigPath = CoreResLoader::GetResPath().Concat("Engine/Configs/StartupScene.xml");
                if (SR_XML_NS::Document document = document.Load(startSceneConfigPath)) {
                    auto&& path = document.Root().GetNode("Configs").GetNode("StartupScene").GetAttribute<SR_UTILS_NS::Path>();
                    if (!path.IsEmpty()) {
                        SR_LOG("Application::Execute() : startup scene config file detected, running scene at path \"{}\"...", path);
                        m_engine->RunSceneGameMode(path);
                    }
                    else {
                        SR_ERROR("Application::Execute() : startup scene config file is invalid! Path: \"{}\"", path);
                    }
                }
                else {
                    SR_LOG("Application::Execute() : startup scene config file not found at path \"{}\"!", startSceneConfigPath);
                }
            }
        }

        SR_PLATFORM_NS::SetApplicationMainLoop(AppMainLoop, this);

        return !m_hasErrors;
    }

    void Application::Close() {
        SR_TRACY_ZONE;

        if (m_engine) {
            m_engine->Close();
        }

        m_engine.AutoFree();

        SR_UTILS_NS::TagManager::DestroySettings();
        SR_UTILS_NS::LayerManager::DestroySingleton();

        SR_AUDIO_NS::SoundManager::DestroySingleton();
        SR_PHYSICS_NS::PhysicsLibrary::DestroySingleton();
        SR_GRAPH_NS::Memory::CameraManager::DestroySingleton();
        SR_UTILS_NS::TaskManager::DestroySingleton();
        SR_GRAPH_NS::MeshManager::DestroySingleton();

        SR_UTILS_NS::Debug::Instance().System("Application::Close() : all systems were successfully closed!");
    }

    void Application::Reload() {
        m_isNeedReload = true;
    }
}
