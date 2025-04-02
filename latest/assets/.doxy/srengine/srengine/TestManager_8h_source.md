

# File TestManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**Tests**](dir_a438f77ea296cf9ed84cc5f25e2e6a4d.md) **>** [**TestManager.h**](TestManager_8h.md)

[Go to the documentation of this file](TestManager_8h.md)


```C++
//
// Created by innerviewer on 2024-03-18.
//

#ifndef SR_ENGINE_TESTMANAGER_H
#define SR_ENGINE_TESTMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Coroutine.h>
#include <Utils/Types/Function.h>

namespace SR_CORE_NS {
    class TestManager : public SR_UTILS_NS::Singleton<TestManager> {
        SR_REGISTER_SINGLETON(TestManager)
        using TestFn = SR_HTYPES_NS::Function<bool()>;
        using Test = std::pair<std::string, TestFn>;
    public:
        void AddTest(const TestFn& test, const std::string& name) { m_tests.insert(std::make_pair(name, test)); }
        void AddEngineTest(const TestFn& test, const std::string& name) { m_engineTests.insert(std::make_pair(name, test)); }

        void RunAll(int argc, char** argv);

        bool IsSingletonCanBeDestroyed() const override { return false; }

    private:
        bool RunTest(const Test& test);
        bool RunEngineTest(const Test& test);

    private:
        std::map<std::string, TestFn> m_engineTests;
        std::map<std::string, TestFn> m_tests;

        int m_argc = 0;
        char** m_argv = nullptr;
    };
}

#endif //SR_ENGINE_TESTMANAGER_H
```


