

# File IState.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**IState.h**](IState_8h.md)

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


