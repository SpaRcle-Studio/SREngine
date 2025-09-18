

# File Application.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Application.h**](Application_8h.md)

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
        ~Application() override;

    public:
        bool PreInit();
        bool EarlyInit();
        bool Init();
        bool Execute();
        void Close();

        void SwitchResourcesFolder(const SR_UTILS_NS::Path& path);
        void Reload();

        SR_NODISCARD const SR_UTILS_NS::Path& GetResourcesPath() const { return m_resourcesPath; }
        SR_NODISCARD const SR_HTYPES_NS::SharedPtr<Engine>& GetEngine() const { return m_engine; }
        SR_NODISCARD SR_HTYPES_NS::SharedPtr<Engine>& GetEngine() { return m_engine; }

    protected:
        bool InitializeResourcesFolder();

    private:
        bool InitLogger(const SR_UTILS_NS::Path& logDir);

    private:
        SR_UTILS_NS::Path m_resourcesPath;

        std::atomic<bool> m_isNeedReload = false;

        SR_HTYPES_NS::SharedPtr<Engine> m_engine;

    };
}

#endif //SR_ENGINE_CORE_APPLICATION_H
```


