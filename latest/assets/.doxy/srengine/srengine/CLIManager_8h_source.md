

# File CLIManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**CLIManager.h**](CLIManager_8h.md)

[Go to the documentation of this file](CLIManager_8h.md)


```C++
// 
// Created by innerviewer on 2025-04-15.
//

#ifndef SR_ENGINE_CORE_CLI_MANAGER_H
#define SR_ENGINE_CORE_CLI_MANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Enumerations.h>

namespace SR_CORE_NS {
    SR_ENUM_NS_STRUCT_T(CLIFlags, uint32_t,
        None = 0,
        UnitTests = 1 << 0,
        DeleteOldApp = 1 << 1
    );

    SR_ENUM_NS_STRUCT_T(CLIOptions, uint32_t,
        Resources,
        LogDir
    );

    class CLIManager : public SR_UTILS_NS::Singleton<CLIManager> {
        SR_REGISTER_SINGLETON(CLIManager);
    public:
        void Init(int argc, char** argv);

        std::optional<std::string> GetOptionValue(CLIOptions option);
        bool IsFlagPresent(CLIFlags flag) const { return SR_MATH_NS::IsMaskIncludedSubMask(m_flags, flag); }

        SR_NODISCARD const std::map<CLIOptions, std::optional<std::string>>& GetOptions() const { return m_options; }
        SR_NODISCARD CLIFlags GetFlags() const { return m_flags; }

    public:
        bool IsSingletonCanBeDestroyed() const override { return false; }

    private:
        std::map<CLIOptions, std::optional<std::string>> m_options;
        CLIFlags m_flags = CLIFlags::None;
    };
}

#endif //SR_ENGINE_CORE_CLI_MANAGER_H
```


