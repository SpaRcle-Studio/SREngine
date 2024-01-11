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
