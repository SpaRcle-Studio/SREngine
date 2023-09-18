//
// Created by Monika on 14.09.2023.
//

#include <Core/Application.h>

#include <Utils/Debug.h>
#include <Utils/Common/CmdOptions.h>
#include <Utils/World/SceneAllocator.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/SRLM/LogicalNodeManager.h>
#include <Utils/SRLM/DataTypeManager.h>

#include <Audio/Sound.h>

namespace SR_CORE_NS {
    Application::Application()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    Application::~Application() {
        Close();
        SR_UTILS_NS::Debug::DestroySingleton();
    }

    bool Application::PreInit(int argc, char** argv) {
        SR_UTILS_NS::Locale::SetLocale();
        SR_UTILS_NS::Random::Initialize();
        SR_PLATFORM_NS::InitSegmentationHandler();

        m_applicationPath = SR_PLATFORM_NS::GetApplicationPath().GetFolder();

        if (!InitLogger()) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to initialize logger!\n");
            return false;
        }

        if (auto&& folder = SR_UTILS_NS::GetCmdOption(argv, argv + argc, "-resources"); !folder.empty()) {
            m_resourcesPath = folder;
        }

        if (!m_resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder) && !FindResourcesFolder()) {
            SR_ERROR("Application::PreInit() : failed to find resources folder!");
            return false;
        }

        return true;
    }

    void Application::TryPlayStartSound() {
        auto&& pEditor = m_engine->GetEditor();
        if (!pEditor || !pEditor->Enabled()) {
            m_isNeedPlaySound = false;
            return;
        }

        if (auto&& pRenderScene = m_engine->GetRenderScene()) {
            if (pRenderScene->GetPipeline()->IsDirty()) {
                return;
            }

            if (auto&& pSound = SR_AUDIO_NS::Sound::Load("Editor/Audio/Success.mp3")) {
                pSound->Play();
            }

            m_isNeedPlaySound = false;
        }
    }

    bool Application::FindResourcesFolder() {
        m_resourcesPath = m_applicationPath.Concat("Resources");
        if (m_resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            return true;
        }

        m_resourcesPath = m_applicationPath.Concat("../Resources");
        if (m_resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            return true;
        }

        m_resourcesPath = m_applicationPath.Concat("../../Resources");
        if (m_resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            return true;
        }

        m_resourcesPath = m_applicationPath.Concat("../../../Resources");
        if (m_resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            return true;
        }

        m_resourcesPath = m_applicationPath.Concat("../../../../Resources");
        if (m_resourcesPath.Exists(SR_UTILS_NS::Path::Type::Folder)) {
            return true;
        }

        return false;
    }

    bool Application::InitLogger() {
        if (SR_UTILS_NS::Debug::Instance().IsInitialized()) {
            return true;
        }

        SR_UTILS_NS::Debug::Instance().Init(m_applicationPath, true, SR_UTILS_NS::Debug::Theme::Dark);
        SR_UTILS_NS::Debug::Instance().SetLevel(SR_UTILS_NS::Debug::Level::Low);
        return true;
    }

    bool Application::Init() {
        if (!InitLogger()) {
            SR_PLATFORM_NS::WriteConsoleError("Failed to initialize logger!\n");
            return false;
        }

        SR_SYSTEM_LOG("Application::Init() : initializing application...");

        if (m_resourcesPath.Empty()) {
            SR_ERROR("Application::Init() : resources path is empty!");
            return false;
        }

        SR_HTYPES_NS::Thread::Factory::Instance().SetMainThread();
        SR_HTYPES_NS::Time::Instance().Update();

        SR_UTILS_NS::Features::Instance().SetPath(m_resourcesPath.Concat("Engine/Configs/Features.xml"));
        SR_UTILS_NS::Features::Instance().Reload();

        SR_UTILS_NS::ResourceManager::Instance().Init(m_resourcesPath);

        if (!SR_UTILS_NS::ResourceManager::Instance().Run()) {
            SR_ERROR("Application::Init() : failed to initialize resources manager!");
            return false;
        }

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
            if (m_isNeedReload) {
                Close();
                hasErrors |= !Init();
                m_isNeedReload = false;
            }

            if (!m_engine) {
                SR_ERROR("Application::Execute() : engine lost!");
                hasErrors = true;
            }

            if (!m_engine->IsRun()) {
                break;
            }

            if (m_engine->GetWindow() && !m_engine->GetWindow()->IsValid()) {
                SR_SYSTEM_LOG("Application::Execute() : window has been closed!");
                break;
            }

            m_engine->FlushScene();

            if (m_isNeedPlaySound) {
                TryPlayStartSound();
            }

            SR_HTYPES_NS::Thread::Sleep(50);
        }

        return !hasErrors;
    }

    void Application::Close() {
        m_engine->AutoFree([](auto&& pEngine) {
            pEngine->Close();
            delete pEngine;
        });

        SR_SRLM_NS::DataTypeManager::DestroySingleton();

        SR_CORE_NS::EditorSettings::DestroySettings();
        SR_UTILS_NS::TagManager::DestroySettings();

        SR_AUDIO_NS::SoundManager::DestroySingleton();
        SR_PHYSICS_NS::PhysicsLibrary::DestroySingleton();
        SR_GRAPH_NS::Memory::CameraManager::DestroySingleton();
        SR_SCRIPTING_NS::GlobalEvoCompiler::DestroySingleton();
        SR_SCRIPTING_NS::EvoScriptManager::DestroySingleton();
        SR_UTILS_NS::EntityManager::DestroySingleton();
        SR_GRAPH_NS::GUI::NodeManager::DestroySingleton();
        SR_UTILS_NS::TaskManager::DestroySingleton();
        SR_GRAPH_NS::Memory::MeshManager::DestroySingleton();

        SR_UTILS_NS::Debug::Instance().System("Application::Close() : all systems were successfully closed!");

        SR_UTILS_NS::ResourceManager::DestroySingleton();

        SR_HTYPES_NS::Thread::Factory::Instance().PrintThreads();

        SR_UTILS_NS::GetSingletonManager()->DestroyAll();
    }

    void Application::SwitchResourcesFolder(const SR_UTILS_NS::Path& path) {

    }

    void Application::Reload() {
        m_isNeedReload = true;
        m_isNeedPlaySound = true;
    }
}