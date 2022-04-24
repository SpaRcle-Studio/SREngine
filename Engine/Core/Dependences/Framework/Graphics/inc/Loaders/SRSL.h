//
// Created by Monika on 09.04.2022.
//

#ifndef SRENGINE_SRSL_H
#define SRENGINE_SRSL_H

#include <Loaders/SRSLParser.h>

namespace SR_GRAPH_NS::SRSL {
    SR_ENUM_CLASS(ShaderType,
        Unknown,
        Spatial,            /// пространственный шейдер, все статические меши
        TransparentSpatial, /// пространственный шейдер, все статические меши
        Animation,          /// пространтсвенный шейдер, геометрия со скелетом
        PostProcess,        /// шейдер пост-обработки
        Skybox,             /// шейдер скайбокса
        Canvas,             /// шейдер 2д пользовательского интерфейса
        Particles           /// шейдер для частиц
    );

    enum VertexAttribute {
        SRSL_VERTEX_ATTRIBUTE_AUTO      = 0,
        SRSL_VERTEX_ATTRIBUTE_POSITION  = 1 << 0,
        SRSL_VERTEX_ATTRIBUTE_UV        = 1 << 1,
        SRSL_VERTEX_ATTRIBUTE_NORMAL    = 1 << 2,
        SRSL_VERTEX_ATTRIBUTE_TANGENT   = 1 << 3,
        SRSL_VERTEX_ATTRIBUTE_BITANGENT = 1 << 4,
    };

    typedef uint32_t RequireBits;
    typedef uint32_t VertexAttributeBits;
    typedef std::vector<std::string>::const_iterator CodeIter;

    struct SRSLVariable {
        bool used;
        bool show;
        std::string type;
        int32_t binding;
    };
    typedef std::map<std::string, SRSLVariable> SRSLVariables;

    struct SRSLStage {
        SR_UTILS_NS::Path path;
    };

    typedef std::map<ShaderStage, SRSLStage> SRSLStages;

    struct SRSLUnit {
        std::string path;
        ShaderType type = ShaderType::Unknown;
        SRSLStages stages;
        SRShaderCreateInfo createInfo = {};
        VertexAttributeBits attributes = SRSL_VERTEX_ATTRIBUTE_AUTO;
        std::map<std::string, SRSLVariable> bindings;

        std::map<uint32_t, uint32_t> GetUniformSizes() const;

    };

    class SRSLLoader : public SR_UTILS_NS::Singleton<SRSLLoader> {
        friend class SR_UTILS_NS::Singleton<SRSLLoader>;
        using Stream = std::ifstream;

        static const std::unordered_set<std::string> STANDARD_VARIABLES;

    public:
        std::optional<SRSLUnit> Load(std::string path);

    private:
        SRSLVariables RefAnalyzer(const std::string& code, const SRSLVars& allVars);
        bool PrepareUnit(SRSLUnit& unit, const SRSLVars& vars);

        std::string MakeUniformsCode(SRSLUnit& unit, const std::string& code, SRSLParseData& parseData);

        bool CreateFragment(SRSLUnit& unit, SRSLParseData& parseData, SR_UTILS_NS::Path&& path);
        std::string MakeFragmentCode(const SRSLUnit &unit, const SRSLParseData& parseData);

        bool CreateVertex(SRSLUnit& unit, SRSLParseData& parseData, SR_UTILS_NS::Path&& path);
        std::string MakeVertexCode(const SRSLUnit &unit, const SRSLParseData& parseData);

    };
}

#endif //SRENGINE_SRSL_H
