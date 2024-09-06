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
