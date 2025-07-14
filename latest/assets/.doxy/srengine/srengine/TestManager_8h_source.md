

# File TestManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Tests**](dir_c9bf2873816ed2ebb5fd18269f2ea03a.md) **>** [**TestManager.h**](TestManager_8h.md)

[Go to the documentation of this file](TestManager_8h.md)


```C++
//
// Created by innerviewer on 2024-03-18.
//

#ifndef SR_ENGINE_COMMON_TESTS_TEST_MANAGER_H
#define SR_ENGINE_COMMON_TESTS_TEST_MANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Coroutine.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Resources/Asset.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_CLASS_T(TestExecutionResult, uint8_t,
        Success,
        Error,
        Fatal,
        Skipped,
        Count
    );

    class ITestController : public SR_UTILS_NS::Serializable, public SR_HTYPES_NS::SharedPtr<ITestController> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<ITestController>;
        using OriginType = ITestController;

    public:
        ITestController();

    public:
        virtual TestExecutionResult Run() = 0;
        SR_NODISCARD virtual uint32_t GetTotalTestsCount() const { return 1; }

    };

    class TestGroupController : public ITestController {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TestGroupController>;

    public:
        TestExecutionResult Run() override;
        SR_NODISCARD uint32_t GetTotalTestsCount() const override;

    private:
        std::vector<ITestController::Ptr> m_tests;

    };

    class TestManagerAsset : public SR_UTILS_NS::Asset {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<TestManagerAsset>;

    public:
        std::vector<ITestController::Ptr> m_tests;

    };

    class TestManager : public Singleton<TestManager> {
        SR_REGISTER_SINGLETON(TestManager)
    public:
        SR_NODISCARD TestExecutionResult RunAll();
        SR_NODISCARD bool HasFatalError() const { return m_hasFatalError; }

        void OnTestResult(TestExecutionResult result);

    private:
        TestManagerAsset::Ptr m_pTestManagerAsset;
        std::array<uint32_t, static_cast<uint32_t>(TestExecutionResult::Count)> m_testResults;

        bool m_hasFatalError = false;

    };
}

#endif //SR_ENGINE_COMMON_TESTS_TEST_MANAGER_H
```


