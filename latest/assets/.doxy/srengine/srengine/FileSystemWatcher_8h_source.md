

# File FileSystemWatcher.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Resources**](dir_97f93f5c84d133c6e09e46b256597939.md) **>** [**FileSystemWatcher.h**](FileSystemWatcher_8h.md)

[Go to the documentation of this file](FileSystemWatcher_8h.md)


```C++
//
// Created by Monika on 03.04.2025.
//

#ifndef SR_ENGINE_UTILS_DIRECTORY_WATCHER_H
#define SR_ENGINE_UTILS_DIRECTORY_WATCHER_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/Common/SubscriptionHolder.h>

namespace SR_UTILS_NS {
    class FileSystemWatcher final : public SR_HTYPES_NS::SharedPtr<FileSystemWatcher>, public SubscriptionHolder {
        using Super = SR_HTYPES_NS::SharedPtr<FileSystemWatcher>;
    public:
        static const inline StringAtom MODIFIED_EVENT_ID = "Modified";
        static const inline StringAtom ADDED_EVENT_ID = "Added";
        static const inline StringAtom DELETED_EVENT_ID = "Deleted";
        static const inline StringAtom MOVED_EVENT_ID = "Moved";

        static const inline StringAtom DIR_MSG_ID = "Directory";
        static const inline StringAtom FILE_MSG_ID = "File";
        static const inline StringAtom OLD_FILE_MSG_ID = "OldFile";

        enum class EventType : uint8_t {
            None, Add, Delete, Move, Modified
        };
        struct Event {
            EventType type = EventType::None;
            std::string dir;
            std::string filename;
            std::string oldFilename;
        };

    public:
        FileSystemWatcher();
        ~FileSystemWatcher() override;

    public:
        void StartAsyncWatch();
        void WatchPull();

        void AddListener(const std::string& path);

        void OnEvent(Event&& event);

    private:
        void* m_pImpl = nullptr;
        std::map<uint64_t, void*> m_listeners;
        bool m_isAsyncWatchingActive = false;
        std::recursive_mutex m_mutex;
        std::vector<Event> m_events;

    };
}

#endif //SR_ENGINE_UTILS_DIRECTORY_WATCHER_H
```


