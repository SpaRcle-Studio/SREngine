

# File Application.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Application.h**](Application_8h.md)

[Go to the documentation of this file](Application_8h.md)


```C++
//
// Created by Monika on 14.09.2023.
//

#ifndef SR_ENGINE_CORE_APPLICATION_H
#define SR_ENGINE_CORE_APPLICATION_H

#include <Utils/Types/SharedPtr.h>
#include <Utils/FileSystem/Path.h>

namespace SR_CORE_NS {
    class Engine;

    class Application : public SR_HTYPES_NS::SharedPtr<Application> {
        using Super = SR_HTYPES_NS::SharedPtr<Application>;
    public:
        Application();
        ~Application();

    public:
        bool PreInit();
        bool EarlyInit();
        bool Init();
        bool Execute();
        void Close();

        void SwitchResourcesFolder(const SR_UTILS_NS::Path& path);
        void Reload();

        virtual bool InitializeResourcesFolder();

        SR_NODISCARD const SR_UTILS_NS::Path& GetResourcesPath() const { return m_resourcesPath; }

    private:
        bool InitResourceTypes();
        bool InitLogger(const SR_UTILS_NS::Path& logDir);
        bool FindResourcesFolder();
        //void TryPlayStartSound()

    private:
        SR_UTILS_NS::Path m_applicationPath;
        SR_UTILS_NS::Path m_resourcesPath;

        std::atomic<bool> m_isNeedReload = false;

        SR_HTYPES_NS::SharedPtr<Engine> m_engine;

    };
}

#endif //SR_ENGINE_CORE_APPLICATION_H
```


