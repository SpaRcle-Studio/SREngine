#include <vector>
#include <optional>
#include <iostream>
#include <cstdint>
#include <cfloat>
#include <cmath>
#include <cstdio>

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
        void SetScriptContextHandle(ScriptHandle handle) { m_scriptContextHandle = handle; }

        ScriptModuleInfo& AddModule(const char* moduleName) {
            auto& module = m_scriptModules.emplace_back();
            module.name = moduleName;
            return module;
        }

        CoreAPI& SetCompilerVersion(const char* version) {
            m_compilerVersion = version;
            return *this;
        }

        SR_NODISCARD const char* GetCompilerVersion() const { return m_compilerVersion; }
        SR_NODISCARD uint32_t GetCountModules() const { return static_cast<uint32_t>(m_scriptModules.size()); }
        SR_NODISCARD ScriptModuleInfo& GetScriptModule(uint32_t index) { return m_scriptModules[index]; }
        SR_NODISCARD ScriptHandle GetScriptContextHandle() const { return m_scriptContextHandle; }
        SR_NODISCARD FunctionHandle GetFunction(uint64_t index) const { return m_functionTable[index]; }

        SR_NODISCARD CppBehaviour* AllocateBehaviour(const char* behaviourName) {
            for (auto& module : m_scriptModules) {
                for (auto& behaviour : module.behaviours) {
                    if (strcmp(behaviour.name, behaviourName) == 0) {
                        return reinterpret_cast<CppBehaviour*>(behaviour.allocateFunc());
                    }
                }
            }
            return nullptr;
        }

    private:
        const char* m_compilerVersion = nullptr;
        std::vector<ScriptModuleInfo> m_scriptModules;
        std::vector<FunctionHandle> m_functionTable;
        ScriptHandle m_scriptContextHandle;

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

    class CppBehaviour {
    public:
        CppBehaviour() = default;
        virtual ~CppBehaviour() = default;

        CppBehaviour(const CppBehaviour&) = delete;
        CppBehaviour(CppBehaviour&&) = delete;

        CppBehaviour& operator=(const CppBehaviour&) = delete;
        CppBehaviour& operator=(CppBehaviour&&) = delete;

    public:
        virtual void Awake() { }
        virtual void OnEnable() { }
        virtual void OnDisable() { }
        virtual void OnAttached() { }
        virtual void OnDetached() { }
        virtual void OnDestroy() { }
        virtual void Start() { }
        virtual void Update(float_t dt) { }
        virtual void FixedUpdate() { }

    private:

    };
}

#define SR_SCRIPT_BEHAVIOUR_CLASS()

using namespace SpaRcleAPI;

SR_SCRIPT_EXTERN_DLL void InitScriptCoreAPI(uint64_t countFunctions) { CoreAPI::Instance().Init(countFunctions); }
SR_SCRIPT_EXTERN_DLL void SetScriptFunction(uint64_t index, void* pFunction) { CoreAPI::Instance().SetFunction(index, pFunction); }
SR_SCRIPT_EXTERN_DLL void SetScriptContextHandle(ScriptHandle handle) { CoreAPI::Instance().SetScriptContextHandle(handle); }
SR_SCRIPT_EXTERN_DLL void DestroyScriptCoreAPI() { CoreAPI::Destroy(); }
SR_SCRIPT_EXTERN_DLL uint32_t GetScriptModulesCount() { return CoreAPI::Instance().GetCountModules(); }
SR_SCRIPT_EXTERN_DLL const char* GetScriptModuleName(uint32_t index) { return CoreAPI::Instance().GetScriptModule(index).name; }
SR_SCRIPT_EXTERN_DLL const char* GetScriptModuleCompilerVersion() { return CoreAPI::Instance().GetCompilerVersion(); }
SR_SCRIPT_EXTERN_DLL void* AllocateScriptBehaviour(const char* behaviourName) { return CoreAPI::Instance().AllocateBehaviour(behaviourName); }
SR_SCRIPT_EXTERN_DLL void FreeScriptBehaviour(void* pBehaviour) { delete reinterpret_cast<CppBehaviour*>(pBehaviour); }