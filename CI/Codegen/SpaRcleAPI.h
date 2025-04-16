#include <vector>
#include <optional>
#include <iostream>
#include <cstdint>
#include <cfloat>
#include <cmath>
#include <cstdio>
#include <memory>

#ifdef SR_SCRIPT_AOT_ENABLED
    #define SR_SCRIPT_EXTERN_DLL
#else
    #define SR_SCRIPT_EXTERN_DLL extern "C" __declspec(dllexport)
#endif

#ifndef SR_NODISCARD
    #define SR_NODISCARD [[nodiscard]]
#endif

namespace SpaRcleAPI {
    class CoreAPI;

    CoreAPI* g_pCoreAPI = nullptr;

    #include "ScriptHandle.h"

    template <typename T, bool AllowSuccessor = false, typename ... Others>
    class ScriptablePassKey : private ScriptablePassKey<Others, false> ... {
    public:
        template <typename U, typename = typename std::enable_if<AllowSuccessor && std::is_base_of<T, U>::value && !std::is_same<U, T>::value, T>::type>
        ScriptablePassKey(ScriptablePassKey<U>&&) { }

        template <typename U, typename = U, typename = typename std::enable_if<std::is_base_of<ScriptablePassKey<U>, ScriptablePassKey<T, AllowSuccessor, Others...>>::value, U>::type>
        ScriptablePassKey(ScriptablePassKey<U>&&) { }

        template <typename U, typename = U, typename = U, typename = typename std::enable_if<(AllowSuccessor || (sizeof...(Others) > 0)) && std::is_same<U, T>::value, T>::type>
        ScriptablePassKey(ScriptablePassKey<U, AllowSuccessor, Others...>&&) { }

    protected:
        ScriptablePassKey() noexcept = default;
        explicit ScriptablePassKey(const T *) noexcept { }

    private:
        friend T;

        ScriptablePassKey(ScriptablePassKey<T, false>&&) { }

        ScriptablePassKey(const ScriptablePassKey&) = delete;
        ScriptablePassKey& operator=(const ScriptablePassKey&) = delete;
        ScriptablePassKey& operator=(ScriptablePassKey&&) = delete;

    };

    template<typename T> ScriptablePassKey(const T*) -> ScriptablePassKey<T>;

    using AllocateScriptBehaviourFunc = void* (*)();

    struct ScriptModuleBehaviourInfo {
    public:
        const char* name = nullptr;
        AllocateScriptBehaviourFunc allocateFunc = nullptr;

    };

    struct ScriptModuleInfo {
    public:
        ScriptModuleBehaviourInfo& AddBehaviour(const char* behaviourName, AllocateScriptBehaviourFunc allocateFunc) {
            auto& behaviour = behaviours.emplace_back();
            behaviour.name = behaviourName;
            behaviour.allocateFunc = allocateFunc;
            return behaviour;
        }

    public:
        const char* name = nullptr;
        std::vector<ScriptModuleBehaviourInfo> behaviours;

    };

    class CppBehaviour;

    class CoreAPI {
        using FunctionHandle = void*;
    private:
        CoreAPI() = default;
        ~CoreAPI() = default;

    public:
        CoreAPI(const CoreAPI&) = delete;
        CoreAPI(CoreAPI&&) = delete;

        CoreAPI& operator=(const CoreAPI&) = delete;
        CoreAPI& operator=(CoreAPI&&) = delete;

    public:
        static CoreAPI& Instance() {
            if (!g_pCoreAPI) {
                g_pCoreAPI = new SpaRcleAPI::CoreAPI();
            }
            return *g_pCoreAPI;
        }

        static void Destroy() {
            if (g_pCoreAPI) {
                delete g_pCoreAPI;
                g_pCoreAPI = nullptr;
            }
        }

        void Init(uint64_t countFunctions) { m_functionTable.resize(countFunctions); }
        void SetFunction(uint64_t index, FunctionHandle function) { m_functionTable[index] = function; }

        ScriptModuleInfo& AddModule(const char* moduleName) {
            auto& module = m_scriptModules.emplace_back();
            module.name = moduleName;
            return module;
        }

        ScriptModuleInfo& GetLastModule() {
            return m_scriptModules.back();
        }

        CoreAPI& SetCompilerVersion(const char* version) {
            m_compilerVersion = version;
            return *this;
        }

        SR_NODISCARD const char* GetCompilerVersion() const { return m_compilerVersion; }
        SR_NODISCARD uint32_t GetCountModules() const { return static_cast<uint32_t>(m_scriptModules.size()); }
        SR_NODISCARD ScriptModuleInfo& GetScriptModule(uint32_t index) { return m_scriptModules[index]; }
        SR_NODISCARD FunctionHandle GetFunction(uint64_t index) const { return m_functionTable[index]; }
        SR_NODISCARD CppBehaviour* AllocateBehaviour(const char* behaviourName);

    private:
        const char* m_compilerVersion = nullptr;
        std::vector<ScriptModuleInfo> m_scriptModules;
        std::vector<FunctionHandle> m_functionTable;

    };

    struct SharedPtrUnmanagedPassKey { };

    template<typename T> class SharedPtr {
    public:
        SharedPtr() = default;

        ~SharedPtr() {
            auto&& pDeleteFunction = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(T::API_DELETE_FUNCTION_INDEX);
            pDeleteFunction(m_handle);
        }

        SharedPtr(const ScriptHandle& handle)
            : m_handle(handle)
        {
            auto&& pIncrementFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(T::API_INCREMENT_FUNCTION_INDEX);
            pIncrementFunc(m_handle);
        }

        SharedPtr(const SharedPtr& other)
            : m_handle(other.m_handle)
            , m_initialized(other.m_initialized)
        {
            auto&& pIncrementFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(T::API_INCREMENT_FUNCTION_INDEX);
            pIncrementFunc(m_handle);

            memcpy(m_storage, other.m_storage, sizeof(T));
        }

        SharedPtr(SharedPtr&& other) noexcept
            : m_handle(std::exchange(other.m_handle, {}))
            , m_initialized(std::exchange(other.m_initialized, false))
        {
            memcpy(m_storage, other.m_storage, sizeof(T));
        }

        SharedPtr& operator=(const SharedPtr& other) {
            if (this != &other) {
                auto&& pIncrementFunc = (void (*)(ScriptHandle))CoreAPI::Instance().GetFunction(T::API_INCREMENT_FUNCTION_INDEX);
                pIncrementFunc(other.m_handle);
                m_handle = other.m_handle;
                m_initialized = other.m_initialized;
                memcpy(m_storage, other.m_storage, sizeof(T));
            }
            return *this;
        }

        SharedPtr& operator=(SharedPtr&& other) noexcept {
            if (this != &other) {
                m_handle = std::exchange(other.m_handle, {});
                m_initialized = std::exchange(other.m_initialized, false);
                memcpy(m_storage, other.m_storage, sizeof(T));
            }
            return *this;
        }

        T* operator->() { EnsureInitialized(); return Get(); }
        T& operator*() { EnsureInitialized(); return *Get(); }

    private:
        T* Get() { return reinterpret_cast<T*>(&m_storage); }

        void EnsureInitialized() {
            if (!m_initialized) {
                new (static_cast<void*>(Get())) T(m_handle, SharedPtrUnmanagedPassKey());
                m_initialized = true;
            }
        }

    private:
        ScriptHandle m_handle;
        alignas(T) std::byte m_storage[sizeof(T)];
        bool m_initialized = false;

    };

    template<typename T> class UnsafeRef {
    public:
        UnsafeRef() = default;
        ~UnsafeRef() = default;
        UnsafeRef(const UnsafeRef&) = delete;
        UnsafeRef(UnsafeRef&&) = delete;
        UnsafeRef& operator=(const UnsafeRef&) = delete;
        UnsafeRef& operator=(UnsafeRef&&) = delete;

        UnsafeRef(const ScriptHandle& handle)
            : m_handle(handle)
        { }

    public:
        T* operator->() const {
            if (!m_instance) {
                m_instance = T(m_handle);
            }
            return &m_instance.value();
        }

    private:
        mutable std::optional<T> m_instance;
        ScriptHandle m_handle;

    };
}

#define SR_SCRIPT_BEHAVIOUR_CLASS()

using namespace SpaRcleAPI;

SR_SCRIPT_EXTERN_DLL void InitScriptCoreAPI(uint64_t countFunctions) { CoreAPI::Instance().Init(countFunctions); }
SR_SCRIPT_EXTERN_DLL void SetScriptFunction(uint64_t index, void* pFunction) { CoreAPI::Instance().SetFunction(index, pFunction); }
SR_SCRIPT_EXTERN_DLL void DestroyScriptCoreAPI() { CoreAPI::Destroy(); }
SR_SCRIPT_EXTERN_DLL uint32_t GetScriptModulesCount() { return CoreAPI::Instance().GetCountModules(); }
SR_SCRIPT_EXTERN_DLL uint32_t GetScriptModuleBehavioursCount(uint32_t index) { return CoreAPI::Instance().GetScriptModule(index).behaviours.size(); }
SR_SCRIPT_EXTERN_DLL const char* GetScriptModuleBehaviourName(uint32_t moduleIndex, uint32_t behaviourIndex) { return CoreAPI::Instance().GetScriptModule(moduleIndex).behaviours[behaviourIndex].name; }
SR_SCRIPT_EXTERN_DLL const char* GetScriptModuleName(uint32_t index) { return CoreAPI::Instance().GetScriptModule(index).name; }
SR_SCRIPT_EXTERN_DLL const char* GetScriptModuleCompilerVersion() { return CoreAPI::Instance().GetCompilerVersion(); }

SR_SCRIPT_EXTERN_DLL void* AllocateScriptBehaviour(const char* behaviourName) { return CoreAPI::Instance().AllocateBehaviour(behaviourName); }
SR_SCRIPT_EXTERN_DLL void FreeScriptBehaviour(void* pBehaviour);
SR_SCRIPT_EXTERN_DLL void ScriptModuleSetBehaviourSceneObject(void* pInstance, ScriptHandle handle);

SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourAwake(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourOnEnable(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourOnDisable(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourOnAttached(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourOnDetached(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourOnDestroy(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourStart(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourFixedUpdate(void* pInstance);
SR_SCRIPT_EXTERN_DLL void ScriptModuleBehaviourUpdate(void* pInstance, float_t dt);