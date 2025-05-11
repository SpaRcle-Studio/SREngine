

# File SRSLParser.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Loaders**](dir_d0a1daf921f47a1ee4283e6d14a9506b.md) **>** [**SRSLParser.h**](SRSLParser_8h.md)

[Go to the documentation of this file](SRSLParser_8h.md)


```C++
//
// Created by Monika on 12.04.2022.
//

#ifndef SR_ENGINE_SRSLPARSER_H
#define SR_ENGINE_SRSLPARSER_H

#include <Utils/Common/Singleton.h>

#include <Graphics/Types/Vertices.h>
#include <Graphics/Pipeline/IShaderProgram.h>

namespace SR_GRAPH_NS::SRSL {
    struct SRSLFunc {
        std::string name;
        std::string retType;
        std::string args;
        std::string code;

        std::set<std::string> calls;
    };

    struct SRSLStruct {
        std::string name;
        std::string code;
    };

    typedef std::list<SRSLStruct> SRSLStructs;
    typedef std::list<SRSLFunc> SRSLFunctions;
    typedef std::list<std::string> SRSLVars;
    typedef std::vector<std::string> SRSLCode;

    struct SRSLParseData {
        SRSLStructs structs;
        SRSLFunctions functions;
        SRSLVars vars;
        uint32_t lastBinding = 0;

    };

    bool RemoveComments(SRSLCode& code);
    bool PreProcess(SRSLCode& code, std::map<std::string, std::string> defines /* copy */);
    std::optional<SRSLParseData> Parse(SRSLCode& code);
    std::string GenerateFunctions(const SRSLFunctions& functions, const std::string& callFrom);
}

#endif //SR_ENGINE_SRSLPARSER_H
```


