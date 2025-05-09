

# File Finder.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**Tools**](dir_04907cd073aeacf0a44a00b3a87fc81c.md) **>** [**Finder.h**](Finder_8h.md)

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


