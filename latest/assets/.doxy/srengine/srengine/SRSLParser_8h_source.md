

# File SRSLParser.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Loaders**](dir_3c21463f64aae35806a3291732eddb38.md) **>** [**SRSLParser.h**](SRSLParser_8h.md)

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


