//
// Created by Monika on 09.04.2022.
//

#ifndef SR_ENGINE_SRSL_H
#define SR_ENGINE_SRSL_H

#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Loaders/ShaderProperties.h>
#include <Graphics/Loaders/SRSLParser.h>
#include <Graphics/SRSL/ShaderType.h>

namespace SR_GRAPH_NS::SRSL {
    typedef uint32_t RequireBits;
    typedef uint32_t VertexAttributeBits;
    typedef std::vector<std::string>::const_iterator CodeIter;

    struct SRSLVariable {
        bool used;
        bool show;
        ShaderVarType type;
        int32_t binding;
    };
    typedef std::map<std::string, SRSLVariable> SRSLVariables;

    struct SRSLStage {
        SR_UTILS_NS::Path path;
    };

    typedef std::map<ShaderStage, SRSLStage> SRSLStages;

    struct SRSLUnit {
        std::string path;
        SR_SRSL_NS::ShaderType type = SR_SRSL_NS::ShaderType::Unknown;
        SRSLStages stages;
        SRShaderCreateInfo createInfo = {};
        std::map<std::string, SRSLVariable> bindings;

        SR_NODISCARD std::list<std::pair<std::string, SRSLVariable>> GetUniformBlock() const;
        SR_NODISCARD std::map<uint32_t, uint32_t> GetUniformSizes() const;
        SR_NODISCARD std::map<std::string, SRSLVariable> GetSamplers() const;

    };

    class SRSLLoader : public SR_UTILS_NS::Singleton<SRSLLoader> {
        friend class SR_UTILS_NS::Singleton<SRSLLoader>;
        using Stream = std::ifstream;

        static const std::unordered_map<std::string, ShaderVarType> STANDARD_VARIABLES;
        static const std::unordered_map<std::string, ShaderVarType> COLOR_INDICES;
        static const std::unordered_map<std::string, ShaderVarType> ATTACHMENTS;

    public:
        std::optional<SRSLUnit> Load(std::string path);

    private:
        SRSLVariables RefAnalyzer(const std::string& code, const SRSLVars& allVars);
        SRSLVariables GetColorIndices(const std::string& code);
        bool PrepareUnit(SRSLUnit& unit, const SRSLVars& vars);

        bool AnalyzeUniforms(SRSLUnit& unit, SRSLParseData& parseData, const std::string& fullCode);

        std::string MakeUniformsCode(SRSLUnit& unit, const std::string& code, SRSLParseData& parseData);

        bool CreateFragment(SRSLUnit& unit, SRSLParseData& parseData, const std::string& code, SR_UTILS_NS::Path&& path);
        std::string MakeFragmentCode(const SRSLUnit &unit, const SRSLParseData& parseData);

        bool CreateVertex(SRSLUnit& unit, SRSLParseData& parseData, const std::string& code, SR_UTILS_NS::Path&& path);
        std::string MakeVertexCode(const SRSLUnit &unit, const SRSLParseData& parseData);

    };
}

#endif //SR_ENGINE_SRSL_H
