

# File TestManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**Tests**](dir_b306193d88a6a4b0067721036c79fdf5.md) **>** [**TestManager.h**](TestManager_8h.md)

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

        void RunAll();

        bool IsSingletonCanBeDestroyed() const override { return false; }

    private:
        bool RunTest(const Test& test);
        bool RunEngineTest(const Test& test);

    private:
        std::map<std::string, TestFn> m_engineTests;
        std::map<std::string, TestFn> m_tests;
    };
}

#endif //SR_ENGINE_TESTMANAGER_H
```


