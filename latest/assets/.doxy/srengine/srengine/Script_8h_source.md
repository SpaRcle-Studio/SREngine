

# File Script.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**Script.h**](Script_8h.md)

[Go to the documentation of this file](Script_8h.md)


```C++
//
// Created by Nikita on 03.07.2021.
//

#ifndef EVOSCRIPT_SCRIPT_H
#define EVOSCRIPT_SCRIPT_H

#include <Scripting/IState.h>
#include <Scripting/Compilation/Typedefs.h>

namespace EvoScript {
    class Compiler;

    static void* ESAllocateMemory(size_t sz) {
        return new char[sz];
    }

    static void ESFreeMemory(void* ptr) {
        delete[] (char*)ptr;
    }

    class Script : private SR_UTILS_NS::NonCopyable {
        using MethodPointers = std::vector<std::function<void(EvoScript::IState *)>>;
    private:
        Script(std::string name, Compiler *pCompiler, MethodPointers &&methodPointers)
                : m_name(std::move(name)), m_methodPointers(std::move(methodPointers)), m_compiler(pCompiler) {}

    public:
        ~Script() override;

    public:
        SR_NODISCARD bool IsDirty() const;

        static Script *Allocate(const std::string &name, Compiler *pCompiler, MethodPointers methodPointers);

        template<typename Fn>
        SR_INLINE Fn GetFunction(const std::string &name) {
            return reinterpret_cast<Fn>(m_state->GetFunction<Fn>(name.c_str()));
        }

        template<typename Fn>
        SR_INLINE bool HasFunction(const std::string &name) {
            return GetFunction<Fn>(name);
        }

        template<typename Fn, typename Return, typename... Args>
        SR_INLINE Return Call(Fn fn, Args... args) {
            return fn(std::forward<Args>(args)...);
        }

        template<typename Fn, typename... Args>
        SR_INLINE void Call(Fn fn, Args... args) {
            fn(std::forward<Args>(args)...);
        }

        template<typename Fn, typename Return>
        SR_INLINE Return Call(Fn fn) {
            return fn();
        }

        template<typename Fn, typename Return, typename... Args>
        SR_INLINE Return Call(const std::string &name, Args... args) {
            return Call<Fn, Return, Args...>(GetFunction<Fn>(name), std::forward<Args>(args)...);
        }

        template<typename Fn, typename... Args>
        SR_INLINE void Call(const std::string &name, Args... args) {
            Call<Fn>(GetFunction<Fn>(name), std::forward<Args>(args)...);
        }

        template<typename Fn, typename Return>
        SR_INLINE Return Call(const std::string &name) {
            return Call<Fn, Return>(GetFunction<Fn>(name));
        }

        template<typename Fn>
        SR_INLINE void Call(const std::string &name) {
            return Call<Fn, void>(GetFunction<Fn>(name));
        }

    public:
        SR_NODISCARD bool IsDebug() const { return m_debug; }

        SR_NODISCARD IState *GetState() const { return m_state; }

        SR_NODISCARD std::string GetPath() const { return m_path; }

        SR_NODISCARD std::string GetName() const { return m_name; }

    public:
        bool Load(const std::string &path, Compiler &compiler, bool compile);

    private:
        bool HookFunctions();

    private:
        std::string m_name = "None";
        std::string m_path = "None";
        MethodPointers m_methodPointers = {};
        IState *m_state = nullptr;
        Compiler *m_compiler = nullptr;

#ifdef SR_DEBUG
        const bool m_debug = true;
#else
        const bool m_debug = false;
#endif

    };
}

#endif //EVOSCRIPT_SCRIPT_H
```


