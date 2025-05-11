

# File IState.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**IState.h**](IState_8h.md)

[Go to the documentation of this file](IState_8h.md)


```C++
//
// Created by Nikita on 03.07.2021.
//

#ifndef SR_ENGINE_SCRIPTING_I_STATE_H
#define SR_ENGINE_SCRIPTING_I_STATE_H

#include <Utils/Common/NonCopyable.h>

namespace EvoScript {
    class IState : private SR_UTILS_NS::NonCopyable {
    public:
        ~IState() override = default;

    protected:
        explicit IState(std::string path)
            : m_path(std::move(path))
        { }

    public:
        static IState* Allocate(const std::string& path);

        template<typename Fn> inline Fn GetFunction(const char* name) {
            return reinterpret_cast<Fn>(GetFunctionImpl(name));
        }

    public:
        SR_NODISCARD std::string GetPath() const { return m_path; }

        virtual bool Exists()  = 0;
        virtual bool Load()    = 0;
        virtual bool Unload()  = 0;

    protected:
        virtual void* GetFunctionImpl(const char* name) = 0;

    public:

#ifdef SR_WIN32
        static const inline std::string Extension = ".dll";
#elif defined(SR_LINUX)
        static const inline std::string Extension = ".so";
#else
        static const inline std::string Extension = ".UNKNOWN";
#endif

    protected:
        std::string m_path;

    };
}

#endif //SR_ENGINE_SCRIPTING_I_STATE_H
```


