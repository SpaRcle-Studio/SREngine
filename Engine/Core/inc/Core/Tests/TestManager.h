//
// Created by innerviewer on 2024-03-18.
//

#ifndef SRENGINE_TESTMANAGER_H
#define SRENGINE_TESTMANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Coroutine.h>
#include <Utils/Types/Function.h>

namespace SR_CORE_NS {
    class TestManager : public SR_UTILS_NS::Singleton<TestManager> {
        SR_REGISTER_SINGLETON(TestManager)
        using TestFn = SR_HTYPES_NS::Function<bool()>;
    public:
        void AddTest(const TestFn& test, const std::string& name) { m_tests.insert(std::make_pair(name, test)); }

        void RunAll(int argc, char** argv);

    private:
        bool RunTest(const TestFn& test);

    private:
        std::map<std::string, TestFn> m_tests;

        int m_argc = 0;
        char** m_argv = nullptr;
    };
}

#endif //SRENGINE_TESTMANAGER_H
