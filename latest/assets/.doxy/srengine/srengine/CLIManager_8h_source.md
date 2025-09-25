

# File CLIManager.h

[**File List**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**CLIManager.h**](CLIManager_8h.md)

[Go to the documentation of this file](CLIManager_8h.md)


```C++
// 
// Created by innerviewer on 2025-04-15.
//

#ifndef SR_ENGINE_COMMON_CLI_MANAGER_H
#define SR_ENGINE_COMMON_CLI_MANAGER_H

#include <Utils/Common/Singleton.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Math/Mathematics.h>

namespace SR_UTILS_NS {
    SR_ENUM_NS_STRUCT_T(CLIFlags, uint32_t,
        None = 0,
        UnitTests          = 1 << 0,
        ContinueAfterTests = 1 << 1,
        DeleteOldApp       = 1 << 2
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
        SR_NODISCARD const std::optional<Path>& GetProjectPath() const { return m_projectPath; }

    public:
        bool IsSingletonCanBeDestroyed() const override { return false; }

    private:
        std::map<CLIOptions, std::optional<std::string>> m_options;
        CLIFlags m_flags = CLIFlags::None;
        std::optional<Path> m_projectPath;
    };
}

#endif //SR_ENGINE_COMMON_CLI_MANAGER_H
```


