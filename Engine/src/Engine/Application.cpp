//
// Created by Monika on 14.09.2023.
//

#include <Engine/Application.h>

#include <Utils/Debug.h>
#include <Utils/Common/CmdOptions.h>
#include <Utils/TaskManager/TaskManager.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/SRLM/DataTypeManager.h>
#include <Utils/Localization/Encoding.h>
#include <Utils/Platform/Platform.h>
#include <Utils/ECS/LayerManager.h>
#include <Utils/Tests/SharedPtrAutotests.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/SRLM/LogicalMachine.h>
#include <Utils/TaskManager/ThreadWorker.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/Common/CLIManager.h>

#include <Graphics/GUI/NodeManager.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Font/Font.h>
#include <Graphics/Types/Skybox.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Animations/AnimationClip.h>

#include <Audio/Sound.h>
#include <Audio/SoundManager.h>
#include <Audio/RawSound.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/PhysicsMaterial.h>

namespace SR_CORE_NS {
    Application::Application()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    Application::~Application() {
        Close();
        SR_UTILS_NS::Debug::DestroySingleton();
    }

    bool Application::PreInit() {
        SR_UTILS_NS::Localization::SetLocale();
        SR_UTILS_NS::Random::Initialize();

        m_applicationPath = SR_PLATFORM_NS::GetApplicationPath().GetFolder();

        auto&& defaultLogDir = SR_UTILS_NS::Path(m_applicationPath);
        SR_UTILS_NS::Path logDir = SR_UTILS_NS::CLIManager::Instance().GetOptionValue(SR_UTILS_NS::CLIOptions::LogDir).value_or(defaultLogDir);

        return InitLogger(logDir);
    }

    bool Application::EarlyInit() {
        if (!SR_UTILS_NS::Debug::Instance().IsInitialized()) {
            SR_PLATFORM_NS::WriteConsoleError("Logger is not initialized!\n");
            return false;
        }

        SR_SYSTEM_LOG("Application::EarlyInit() : early initializing application...");

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

    bool Application::InitializeResourcesFolder() {
        m_resourcesPath = SR_PLATFORM_NS::GetApplicationResourcesPath();
        return m_resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder);
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

    bool Application::Execute() {
        SR_INFO("Application::Execute() : waiting for the application to close...");

        volatile bool hasErrors = false;

        while (!hasErrors) {
            SR_TRACY_ZONE;
            SR_PLATFORM_NS::Sleep(50);

            if (m_isNeedReload) {
                Close();
                hasErrors |= !Init();
                m_isNeedReload = false;
            }

            if (!m_engine) {
                SR_ERROR("Application::Execute() : engine lost!");
                hasErrors = true;
            }

            if (!m_engine->Execute()) {
                SR_SYSTEM_LOG("Application::Execute() : engine is not alive!");
                break;
            }
        }

        return !hasErrors;
    }

    void Application::Close() {
        SR_TRACY_ZONE;

        if (m_engine) {
            m_engine->Close();
        }

        m_engine.AutoFree([](auto&& pEngine) {
            delete pEngine;
        });

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

    void Application::SwitchResourcesFolder(const SR_UTILS_NS::Path& path) {
        // SR_STATIC_ASSERT("Not yet implemented.");
    }

    void Application::Reload() {
        m_isNeedReload = true;
    }
}
