

# File Script.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Script.h**](Script_8h.md)

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


