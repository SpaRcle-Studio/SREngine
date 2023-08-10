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

    SR_UTILS_NS::Path FileWatcher::GetPath() const noexcept {
        SR_LOCK_GUARD;
        return m_path;
    }

    void FileWatcher::Update() {
        SR_LOCK_GUARD;

        SRAssert(m_isActive);

        auto&& hash = m_path.GetFileHash();

        if (!m_isInit) {
            m_hash = hash;
            m_isInit = true;
            return;
        }

        if (m_hash != hash) {
            if (m_callBack) {
                m_callBack(this);
            }
            m_hash = hash;
        }
    }

    void FileWatcher::SetName(std::string name) {
        SR_LOCK_GUARD;
        m_name = std::move(name);
    }

    std::string FileWatcher::GetName() const noexcept {
        SR_LOCK_GUARD;
        return m_name;
    }
}