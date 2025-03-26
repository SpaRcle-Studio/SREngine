#include <vector>
#include <iostream>

namespace SpaRcleAPI {
    #include "ScriptHandle.h"

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

    private:
        std::vector<FunctionHandle> m_functionTable;

    };
}

using namespace SpaRcleAPI;