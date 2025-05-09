

# File FileSystemWatcher.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Resources**](dir_324d400546bb3f221a744d7d2624d5c6.md) **>** [**FileSystemWatcher.h**](FileSystemWatcher_8h.md)

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


