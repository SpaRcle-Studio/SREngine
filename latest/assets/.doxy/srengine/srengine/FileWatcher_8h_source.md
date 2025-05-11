

# File FileWatcher.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**FileWatcher.h**](FileWatcher_8h.md)

[Go to the documentation of this file](FileWatcher_8h.md)


```C++
//
// Created by Monika on 05.08.2023.
//

#ifndef SR_ENGINE_FILEWATCHER_H
#define SR_ENGINE_FILEWATCHER_H

#include <Utils/Debug.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/SubscriptionHolder.h>
#include <Utils/Types/Function.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_UTILS_NS {
    class ResourceManager;

    class FileWatcher final : public SR_HTYPES_NS::SharedPtr<FileWatcher>, SR_UTILS_NS::NonCopyable {
        using CallBack = SR_HTYPES_NS::Function<void(FileWatcher* pWatcher)>;
        friend class ResourceManager;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<FileWatcher>;

    public:
        explicit FileWatcher(SR_UTILS_NS::Path path);
        ~FileWatcher() override;

    public:
        void SetCallBack(CallBack callBack);
        void SetName(std::string name);

        void Pause();
        void Resume();

        SR_NODISCARD std::string GetName() const noexcept;
        SR_NODISCARD const SR_UTILS_NS::Path& GetPath() const noexcept;

    private:
        void Subscribe();
        void Unsubscribe();

        void Signal(const SR_UTILS_NS::SubscriptionMessage& message);

    private:
        std::optional<Subscription> m_subscription;
        SR_UTILS_NS::Path m_path;
        CallBack m_callBack;
        std::string m_name;

    };
}

#endif //SR_ENGINE_FILEWATCHER_H
```


