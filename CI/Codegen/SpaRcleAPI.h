#include <vector>
#include <optional>
#include <iostream>
#include <cstdint>

namespace SpaRcleAPI {
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
            static CoreAPI instance;
            return instance;
        }

        FunctionHandle GetFunction(uint64_t index) const {
            return m_functionTable[index];
        }

        void Init(uint64_t countFunctions) {
            m_functionTable.resize(countFunctions);
        }

        void SetFunction(uint64_t index, FunctionHandle function) {
            m_functionTable[index] = function;
        }

        ScriptHandle GetScriptContextHandle() const {
            return m_scriptContextHandle;
        }

        void SetScriptContextHandle(ScriptHandle handle) {
            m_scriptContextHandle = handle;
        }

    private:
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
}

using namespace SpaRcleAPI;