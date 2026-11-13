//
// Created by Codex on 13.11.2026.
//

#include <Scripting/Base/ScriptSystem.h>
#include <Scripting/Base/BehaviourInstance.h>

#include <Utils/Common/Bind.h>
#include <Utils/Common/SubscriptionMessage.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/FileSystem/IVFSBackend.h>

namespace SR_SCRIPTING_NS {
    namespace ScriptSystemHelpers {
        bool IsWithin(const SR_UTILS_NS::Path& path, const SR_UTILS_NS::Path& folder) {
            auto&& value = path.ToStringView();
            auto&& root = folder.ToStringView();

            return value == root ||
                (!root.empty() && value.size() > root.size() && value.starts_with(root) && (root.back() == '/' || value[root.size()] == '/'));
        }
    }

    ScriptSystem::~ScriptSystem() {
        ResetSubscriptions();
        m_angelScriptSystem.AutoFree();
        m_cppSystem.AutoFree();
    }

    bool ScriptSystem::Init(bool compilationEnabled) {
        if (m_isInit) {
            SRHalt("ScriptSystem::Init() : already initialized!");

            return false;
        }

        m_angelScriptSystem = AngelScriptSystem::MakeShared();
        m_cppSystem = CppScriptSystem::MakeShared();

        if (!m_cppSystem->Init(compilationEnabled)) {
            m_cppSystem.AutoFree();

            return false;
        }

        auto&& watcher = SR_UTILS_NS::ResourceManager::Instance().GetFileSystemWatcher();

        m_fileChangedSubscription = watcher->Subscribe(SR_UTILS_NS::FileSystemWatcher::MODIFIED_EVENT_ID,
        SR_UTILS_NS::Bind(&ScriptSystem::HandleFileSystemEvent, this, SR_UTILS_NS::Placeholders::_1, SR_UTILS_NS::FileSystemWatcher::EventType::Modified));
        m_fileCreatedSubscription = watcher->Subscribe(SR_UTILS_NS::FileSystemWatcher::ADDED_EVENT_ID,
        SR_UTILS_NS::Bind(&ScriptSystem::HandleFileSystemEvent, this, SR_UTILS_NS::Placeholders::_1, SR_UTILS_NS::FileSystemWatcher::EventType::Add));
        m_fileDeletedSubscription = watcher->Subscribe(SR_UTILS_NS::FileSystemWatcher::DELETED_EVENT_ID,
        SR_UTILS_NS::Bind(&ScriptSystem::HandleFileSystemEvent, this, SR_UTILS_NS::Placeholders::_1, SR_UTILS_NS::FileSystemWatcher::EventType::Delete));
        m_fileMovedSubscription = watcher->Subscribe(SR_UTILS_NS::FileSystemWatcher::MOVED_EVENT_ID,
        SR_UTILS_NS::Bind(&ScriptSystem::HandleFileSystemEvent, this, SR_UTILS_NS::Placeholders::_1, SR_UTILS_NS::FileSystemWatcher::EventType::Move));

        InitialAnalyse();

        m_isInit = true;
        m_cppSystem->Start();

        return true;
    }

    void ScriptSystem::ResetSubscriptions() {
        m_fileChangedSubscription.Reset();
        m_fileCreatedSubscription.Reset();
        m_fileDeletedSubscription.Reset();
        m_fileMovedSubscription.Reset();
    }

    void ScriptSystem::InitialAnalyse() {
        SR_TRACY_ZONE;
        SR_UTILS_NS::VFS::Instance().Enumerate(CoreResLoader::GetResPath(), [this](const SR_UTILS_NS::VFSEntry& entry) {
            if (entry.type == SR_UTILS_NS::FSItemType::File) {
                HandleFileEvent(entry.fullPath);
            }
        }, true);
    }

    void ScriptSystem::HandleFileSystemEvent(const SR_UTILS_NS::SubscriptionMessage& message, SR_UTILS_NS::FileSystemWatcher::EventType eventType) {
        SR_LOCK_GUARD;
        auto path = message.GetPathRef(SR_UTILS_NS::FileSystemWatcher::FILE_MSG_ID);
        SR_UTILS_NS::VFS::Instance().UnResolvePath(path);
        path.Normalize();

        if (eventType == SR_UTILS_NS::FileSystemWatcher::EventType::Move || eventType == SR_UTILS_NS::FileSystemWatcher::EventType::Delete) {
            auto oldPath = eventType == SR_UTILS_NS::FileSystemWatcher::EventType::Move ? message.GetPathRef(SR_UTILS_NS::FileSystemWatcher::OLD_FILE_MSG_ID) : path;
            SR_UTILS_NS::VFS::Instance().UnResolvePath(oldPath);
            oldPath.Normalize();
            SR_UTILS_NS::Vector<SR_UTILS_NS::Path> removed;

            for (auto&& knownPath : m_knownFiles) {
                if (ScriptSystemHelpers::IsWithin(knownPath, oldPath)) {
                    removed.emplace_back(knownPath);
                }
            }

            for (auto&& removedPath : removed) {
                HandleFileEvent(removedPath);
            }

            if (eventType == SR_UTILS_NS::FileSystemWatcher::EventType::Move) {
                HandleFileEvent(oldPath);
            }
        }

        if (path.IsDir()) {
            if (eventType == SR_UTILS_NS::FileSystemWatcher::EventType::Modified) {
                return;
            }

            SR_UTILS_NS::VFS::Instance().Enumerate(path, [this](const SR_UTILS_NS::VFSEntry& entry) {
                if (entry.type == SR_UTILS_NS::FSItemType::File) {
                    HandleFileEvent(entry.fullPath);
                }
            }, true);
        }
        else {
            HandleFileEvent(path);
        }
    }

    void ScriptSystem::HandleFileEvent(SR_UTILS_NS::Path path) {
        SR_LOCK_GUARD;
        SR_UTILS_NS::VFS::Instance().UnResolvePath(path);
        path.Normalize();

        if (!ScriptSystemHelpers::IsWithin(path, CoreResLoader::GetResPath()) ||
            ScriptSystemHelpers::IsWithin(path, CoreResLoader::GetCachePath()) ||
            ScriptSystemHelpers::IsWithin(path, m_cppSystem->GetAPIFolder()) || path.GetBaseNameView() == "libclang") {
            return;
        }

        const auto extension = path.GetExtensionView();
        const bool isAS = extension == "as";
        const bool isCpp = CppScriptSystem::ALLOWED_CPP_EXTENSIONS.count(extension) > 0 ||
            CppScriptSystem::ALLOWED_CPP_MODULE_EXTENSIONS.count(extension) > 0 ||
            path.GetBaseNameAndExtView() == CppScriptSystem::ENGINE_MODULE_FILE_NAME;

        if (!isAS && !isCpp) {
            return;
        }

        if (path.IsFile()) {
            m_knownFiles.insert(path);
        }
        else {
            m_knownFiles.erase(path);
        }

        if (isAS && m_angelScriptSystem) {
            m_angelScriptSystem->HandleFileEvent(path);
        }

        if (isCpp && m_cppSystem) {
            m_cppSystem->HandleFileEvent(path);
        }
    }

    ScriptSystemState ScriptSystem::GetState() const {
        return m_cppSystem ? m_cppSystem->GetState() : ScriptSystemState::InitialAnalyse;
    }

    bool ScriptSystem::HasErrors() const {
        bool hasErrors = m_cppSystem && m_cppSystem->HasErrors();
        hasErrors |= m_angelScriptSystem && m_angelScriptSystem->HasErrors();

        return hasErrors;
    }

    void ScriptSystem::WaitForIdle() {
        if (m_cppSystem) {
            m_cppSystem->WaitForIdle();
        }
    }

    void ScriptSystem::ReloadModulesIfNeeded() {
        if (m_cppSystem) {
            m_cppSystem->ReloadModulesIfNeeded();
        }

        if (m_angelScriptSystem) {
            m_angelScriptSystem->ReloadModuleIfNeeded();
        }
    }

    void ScriptSystem::SetReloadRequest() {
        if (m_angelScriptSystem) {
            m_angelScriptSystem->SetReloadRequest();
        }

        if (m_cppSystem) {
            m_cppSystem->SetReloadRequest();
        }
    }

    BehaviourInstance* ScriptSystem::AllocateBehaviourInstance(SR_UTILS_NS::StringAtom name) {
        if (!m_isInit) {
            return nullptr;
        }

        if (m_angelScriptSystem) {
            const auto asNames = m_angelScriptSystem->GetBehaviourNames();

            if (std::find(asNames.begin(), asNames.end(), name) != asNames.end()) {
                const auto cppNames = m_cppSystem->GetBehaviourNames();

                if (std::find(cppNames.begin(), cppNames.end(), name) != cppNames.end()) {
                    SR_ERROR("ScriptSystem::AllocateBehaviourInstance() : behaviour name must be globally unique: {}", name);

                    return nullptr;
                }

                return m_angelScriptSystem->AllocateBehaviourInstance(name);
            }
        }

        return m_cppSystem->GetModuleManager()->AllocateBehaviourInstance(name);
    }

    void ScriptSystem::FreeBehaviourInstance(BehaviourInstance* pInstance) {
        auto&& pCppInstance = dynamic_cast<CppBehaviourInstance*>(pInstance);

        if (pCppInstance && m_cppSystem) {
            m_cppSystem->GetModuleManager()->FreeBehaviourInstance(pCppInstance);
        }
        else if (m_angelScriptSystem) {
            m_angelScriptSystem->FreeBehaviourInstance(pInstance);
        }
    }

    SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom> ScriptSystem::GetBehaviourNames() const {
        auto names = m_cppSystem ? m_cppSystem->GetBehaviourNames() : SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>();

        if (m_angelScriptSystem) {
            for (auto&& name : m_angelScriptSystem->GetBehaviourNames()) {
                if (std::find(names.begin(), names.end(), name) != names.end()) {
                    SR_ERROR("ScriptSystem::GetBehaviourNames() : behaviour name must be globally unique: {}", name);
                    continue;
                }

                names.emplace_back(name);
            }
        }

        return names;
    }
}
