

# File CMakeCodeGen.h

[**File List**](files.md) **>** [**Compilation**](dir_851141f4261c6b16b58da121ff8aacd8.md) **>** [**CMakeCodeGen.h**](CMakeCodeGen_8h.md)

[Go to the documentation of this file](CMakeCodeGen_8h.md)


```C++
//
// Created by innerviewer on 10/10/2023.
//

#ifndef SR_ENGINE_CMAKE_CODEGEN_H
#define SR_ENGINE_CMAKE_CODEGEN_H

#include <Utils/Common/NonCopyable.h>

namespace EvoScript {
    class CMakeCodeGen {
    public:
        CMakeCodeGen() = delete;
        ~CMakeCodeGen() = delete;

    public:
        static bool Generate(const std::string& resourcesPath);

    private:
        static bool GenerateCMakeLists(const std::string& resourcesPath);
        static bool GenerateCxxFile(const std::string& resourcesPath);
    };
}

#endif //SR_ENGINE_CMAKE_CODEGEN_H
```


