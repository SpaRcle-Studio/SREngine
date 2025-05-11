

# File Finder.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Tools**](dir_34b1643912c4d8f0022f3f30c24098db.md) **>** [**Finder.h**](Finder_8h.md)

[Go to the documentation of this file](Finder_8h.md)


```C++
//
// Created by Monika on 31.12.2022.
//

#ifndef SR_ENGINE_SCRIPTING_FINDER_H
#define SR_ENGINE_SCRIPTING_FINDER_H

#include <Scripting/Tools/StringUtils.h>

namespace EvoScript::Tools {
    static const std::vector<std::string> VS_PATHS = {
        "C:/Program Files (x86)/Microsoft Visual Studio",
        "C:/Program Files/Microsoft Visual Studio",

        "D:/Program Files (x86)/Microsoft Visual Studio",
        "D:/Program Files/Microsoft Visual Studio",

        "E:/Program Files (x86)/Microsoft Visual Studio",
        "E:/Program Files/Microsoft Visual Studio",
    };

    static const std::vector<std::string> VS_YEARS = {
            "2015", "2016", "2017", "2018",
            "2019", "2020", "2021", "2022",
            "2023", "2024", "2025", "2026",
            "2027", "2028", "2029", "2030",
    };

    static const std::vector<std::string> VS_TYPES = {
            "Professional", "Community", "Enterprise", "BuildTools"
    };

    static std::string FindMSVCVars64(const std::string& compilerPath) {
        std::string finalPath;
        size_t pos = 0;
        size_t next;

        while ((next = compilerPath.find('\'', pos)) != std::string::npos || (next = compilerPath.find('/', pos)) != std::string::npos) {
            finalPath += compilerPath.substr(pos, next - pos) + "/";
            if (compilerPath.substr(pos, next - pos) == "VC") {
                return finalPath + "Auxiliary/Build/vcvars64.bat";
            }
            pos = next + 1;
        }

        return std::string();
    }

    static std::string FindMSVCVars64() {
        for (auto&& vsPath : VS_PATHS) {
            for (auto&& yearFolder : SR_UTILS_NS::Path(vsPath).GetFolders()) {
                auto&& pIt = std::find_if(VS_YEARS.begin(), VS_YEARS.end(), [&yearFolder](auto &&element) -> bool {
                    return yearFolder.ToStringView().find(element) != std::string::npos;
                });

                if (pIt == VS_YEARS.end()) {
                    continue;
                }

                for (auto&& typeFolder : SR_UTILS_NS::Path(yearFolder).GetFolders()) {
                    pIt = std::find_if(VS_TYPES.begin(), VS_TYPES.end(), [&typeFolder](auto &&element) -> bool {
                        return typeFolder.ToStringView().find(element) != std::string::npos;
                    });

                    if (pIt == VS_TYPES.end()) {
                        continue;
                    }

                    return typeFolder.ToStringRef() + "/VC/Auxiliary/Build/vcvars64.bat";
                }
            }
        }

        return std::string();
    }

    static std::string FindMSVC() {
        for (auto&& vsPath : VS_PATHS) {
            for (auto&& yearFolder : SR_UTILS_NS::Path(vsPath).GetFolders()) {
                auto&& pIt = std::find_if(VS_YEARS.begin(), VS_YEARS.end(), [&yearFolder](auto &&element) -> bool {
                    return yearFolder.ToStringView().find(element) != std::string::npos;
                });

                if (pIt == VS_YEARS.end()) {
                    continue;
                }

                for (auto&& typeFolder : SR_UTILS_NS::Path(yearFolder).GetFolders()) {
                    pIt = std::find_if(VS_TYPES.begin(), VS_TYPES.end(), [&typeFolder](auto &&element) -> bool {
                        return typeFolder.ToStringView().find(element) != std::string::npos;
                    });

                    if (pIt == VS_TYPES.end()) {
                        continue;
                    }

                    for (auto&& versionFolder : SR_UTILS_NS::Path(typeFolder.ToStringRef() + "/VC/Tools/MSVC").GetFolders()) {
                        return versionFolder.ToStringRef();
                    }
                }
            }
        }

        return std::string();
    }

    static std::string FindMSVCCompiler() {
        if (auto&& msvc = FindMSVC(); !msvc.empty()) {
            return msvc.append("/bin/Hostx64/x64/cl.exe");
        }

        return std::string();
    }

    static std::string FindMSVCInclude() {
        if (auto&& msvc = FindMSVC(); !msvc.empty()) {
            msvc += "/include";
            return msvc;
        }

        return std::string();
    }
}

#endif //SR_ENGINE_SCRIPTING_FINDER_H
```


