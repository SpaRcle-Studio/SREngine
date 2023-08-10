//
// Created by Monika on 05.08.2023.
//

#ifndef SRENGINE_FILEWATCHER_H
#define SRENGINE_FILEWATCHER_H

#include <Utils/Debug.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_UTILS_NS {
    class ResourceManager;

    class SR_DLL_EXPORT FileWatcher : public SR_HTYPES_NS::SharedPtr<FileWatcher>, SR_UTILS_NS::NonCopyable {
        using Ptr = SR_HTYPES_NS::SharedPtr<FileWatcher>;
        using CallBack = SR_HTYPES_NS::Function<void(FileWatcher* pWatcher)>;
        using Hash = uint64_t;
        using Mutex = std::recursive_mutex;
        friend class ResourceManager;
    private:
        explicit FileWatcher(const SR_UTILS_NS::Path& path);

    public:
        void Stop();

        void SetCallBack(CallBack callBack);
        void SetName(std::string name);

        SR_NODISCARD bool IsActive() const noexcept;
        SR_NODISCARD std::string GetName() const noexcept;
        SR_NODISCARD SR_UTILS_NS::Path GetPath() const noexcept;
        SR_NODISCARD Mutex& GetMutex() { return m_mutex; };

    private:
        void Update();

    private:
        SR_UTILS_NS::Path m_path;
        bool m_isActive = true;
        bool m_isInit = false;
        CallBack m_callBack;
        Hash m_hash = SR_UINT64_MAX;
        std::string m_name;
        mutable Mutex m_mutex;

    };
}

#endif //SRENGINE_FILEWATCHER_H
