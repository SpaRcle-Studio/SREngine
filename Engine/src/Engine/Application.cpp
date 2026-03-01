//
// Created by Monika on 14.09.2023.
//

#include <Engine/Application.h>
#include <Engine/World/World.h>

#include <Graphics/GUI/NodeManager.h>
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
#include <Utils/TaskManager/TaskManager.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/SRLM/DataTypeManager.h>
#include <Utils/Localization/Encoding.h>
#include <Utils/Platform/Platform.h>
#include <Utils/ECS/LayerManager.h>
#include <Utils/SRLM/LogicalMachine.h>
#include <Utils/Common/CLIManager.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Types/Time.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/Platform/Stacktrace.h>

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

        SR_UTILS_NS::Path path;
        if (auto&& logPath = SR_PLATFORM_NS::GetApplicationLogPath()) {
            path = logPath.value();
        }
        else {
            path = SR_PLATFORM_NS::GetApplicationPath().GetFolder();
        }

        SR_UTILS_NS::Path logDir = SR_UTILS_NS::CLIManager::Instance().GetOptionValue(SR_UTILS_NS::CLIOptions::LogDir).value_or(path);

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

        if (m_resourcesPath.IsEmpty()) {
            SR_ERROR("Application::EarlyInit() : resources path is empty!");
            return false;
        }

        SR_HTYPES_NS::Thread::Factory::Instance().SetMainThread();
        SR_HTYPES_NS::Time::Instance().Update();

        SR_UTILS_NS::Features::Instance().SetPath(m_resourcesPath.Concat("Engine/Configs/Features.xml"));
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

    /*void Application::TryPlayStartSound() {
        auto&& pEditor = m_engine->GetEditor();
        if (!pEditor || !pEditor->Enabled()) {
            m_isNeedPlaySound = false;
            return;
        }

        if (auto&& pRenderScene = m_engine->GetRenderScene()) {
            if (!pRenderScene->GetPipeline()) {
                return;
            }

            if (pRenderScene->GetPipeline()->IsDirty()) {
                return;
            }

            if (auto&& pSound = SR_AUDIO_NS::Sound::Load("Editor/Audio/Success.mp3")) {
                pSound->Play();
            }

            m_isNeedPlaySound = false;
        }
    }*/

    static std::string_view ResolvePath(const std::string_view& original, const std::string_view& engineRoot, decltype(&SR_PLATFORM_NS::GetPathType) getFileType) {
        SR_TRACY_ZONE;

        if (getFileType(original) != SR_UTILS_NS::Path::Type::Undefined) {
            return original;
        }

        constexpr const char* anchor = "Resources/";
        constexpr size_t anchorLen = 10;
        const char* pos = std::strstr(original.data(), anchor);
        if (!pos) {
            return original;
        }

        /// если файл в Resources/Cache, то не трогаем
        if (std::strncmp(pos + anchorLen, "Cache/", 6) == 0) {
            return original;
        }

        const char* tail = pos + anchorLen;

        thread_local char buf[4096];
        char* p = buf;

        size_t lenRoot = engineRoot.size();
        size_t lenTail = std::strlen(tail);
        size_t need = lenRoot + 1 + lenTail + 1;

        if (need > sizeof(buf)) SR_UNLIKELY_ATTRIBUTE {
            SR_PLATFORM_NS::WriteConsoleError(SR_FORMAT("Resolved path is too long! Path: {}\n", original));
            return original;
        }

        std::memcpy(p, engineRoot.data(), lenRoot);
        p += lenRoot;
        *p++ = '/';

        std::memcpy(p, tail, lenTail);
        p += lenTail;
        *p = '\0';

        if (getFileType(buf) != SR_UTILS_NS::Path::Type::Undefined) {
            return std::string_view(buf, need - 1); // минус '\0'
        }

        return original;
    }

    bool Application::InitializeResourcesFolder() {
        m_engineResourcesPath = SR_PLATFORM_NS::GetApplicationResourcesPath();
        if (!m_engineResourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            return false;
        }

        m_resourcesPath = m_engineResourcesPath;

        if (auto&& projectPath = SR_UTILS_NS::CLIManager::Instance().GetProjectPath()) {
            auto&& resourcesPath = projectPath->GetFolder().Concat("Resources");
            if (resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
                m_resourcesPath = resourcesPath;

                SR_PLATFORM_NS::InitializeHooks([applicationResources = m_engineResourcesPath](SR_PLATFORM_NS::PlatformHooks& hooks) {
                    if (hooks.originalReadFile && hooks.originalGetPathType) {
                        hooks.getFileTypeHook = [applicationResources, hooks](auto&& path) {
                            return hooks.originalGetPathType(ResolvePath(path, applicationResources.ToStringView(), hooks.originalGetPathType));
                        };
                        hooks.readFileHook = [applicationResources, hooks](auto&& path, auto&& buffer) {
                            return hooks.originalReadFile(ResolvePath(path.ToStringView(), applicationResources.ToStringView(), hooks.originalGetPathType), buffer);
                        };
                        hooks.pathResolver = [applicationResources, hooks](std::string_view path) {
                            return ResolvePath(path, applicationResources.ToStringView(), hooks.originalGetPathType);
                        };
                    }
                });
            }
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

        SR_SRLM_NS::LogicalNodeManager::Instance().InitializeTypes();

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

        if (m_isNeedReload) {
            Close();
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
        SR_INFO("Application::Execute() : waiting for the application to close...");

        m_hasErrors = false;

        auto&& optionPath =  SR_UTILS_NS::CLIManager::Instance().GetOptionValue(SR_UTILS_NS::CLIOptions::RunScene);
        if (m_engine && optionPath.has_value()) {
            SR_LOG("Application::Execute() : command line option to run scene detected: {}", optionPath.value());

            auto&& path = optionPath.value();
            m_engine->RunSceneGameMode(path);
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

        SR_SCRIPTING_NS::ScriptSystem::DestroySingleton();

        SR_SRLM_NS::DataTypeManager::DestroySingleton();

        SR_UTILS_NS::TagManager::DestroySettings();
        SR_UTILS_NS::LayerManager::DestroySettings();

        SR_AUDIO_NS::SoundManager::DestroySingleton();
        SR_PHYSICS_NS::PhysicsLibrary::DestroySingleton();
        SR_GRAPH_NS::Memory::CameraManager::DestroySingleton();
        SR_GRAPH_GUI_NS::NodeManager::DestroySingleton();
        SR_UTILS_NS::TaskManager::DestroySingleton();
        SR_GRAPH_NS::Memory::MeshManager::DestroySingleton();

        SR_UTILS_NS::Debug::Instance().System("Application::Close() : all systems were successfully closed!");
    }

    void Application::Reload() {
        m_isNeedReload = true;
    }
}
