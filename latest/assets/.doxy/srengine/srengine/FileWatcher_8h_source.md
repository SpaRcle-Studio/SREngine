

# File FileWatcher.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**FileWatcher.h**](FileWatcher_8h.md)

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


