//
// Created by Monika on 05.08.2023.
//

#include <Utils/ResourceManager/FileWatcher.h>

namespace SR_UTILS_NS {
    FileWatcher::FileWatcher(const SR_UTILS_NS::Path& path)
        : SR_HTYPES_NS::SharedPtr<FileWatcher>(this, SharedPtrPolicy::Automatic)
        , m_path(path)
        , m_name("Unnamed")
    { }

    void FileWatcher::Stop() {
        SR_LOCK_GUARD;
        m_isActive = false;
    }

    bool FileWatcher::IsActive() const noexcept {
        SR_LOCK_GUARD;
        return m_isActive;
    }

    void FileWatcher::SetCallBack(FileWatcher::CallBack callBack) {
        SR_LOCK_GUARD;
        SRAssert(m_isActive);
        m_callBack = std::move(callBack);
    }

    const SR_UTILS_NS::Path& FileWatcher::GetPath() const noexcept {
        SR_LOCK_GUARD;
        return m_path;
    }

    bool FileWatcher::Update() {
        SR_LOCK_GUARD;

        SRAssert(m_isActive);
        SRAssert(!m_isDirty);

        auto&& hash = m_path.GetFileHash();

        if (!m_isInit) {
            m_hash = hash;
            m_isInit = true;
            return false;
        }

        if (m_hash != hash) {
            m_isDirty = true;
            m_hash = hash;
            return true;
        }

        return false;
    }

    void FileWatcher::SetName(std::string name) {
        SR_LOCK_GUARD;
        m_name = std::move(name);
    }

    std::string FileWatcher::GetName() const noexcept {
        SR_LOCK_GUARD;
        return m_name;
    }

    void FileWatcher::Signal() {
        SR_LOCK_GUARD;

        if (!m_isDirty) {
            return;
        }

        m_isDirty = false;

        if (m_callBack) {
            m_callBack(this);
        }
    }

    void FileWatcher::Pause() {
        SR_LOCK_GUARD;
        m_isPaused = true;
    }

    void FileWatcher::Resume() {
        SR_LOCK_GUARD;
        m_isPaused = false;
    }

    bool FileWatcher::IsPaused() const noexcept {
        SR_LOCK_GUARD;
        return m_isPaused;
    }

    bool FileWatcher::IsDirty() const noexcept {
        SR_LOCK_GUARD;
        return m_isDirty;
    }

    void FileWatcher::Init() {
        SR_LOCK_GUARD;

        if (!m_isInit) {
            m_hash = m_path.GetFileHash();
            m_isInit = true;
        }
    }
}