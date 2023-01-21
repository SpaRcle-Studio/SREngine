//
// Created by Monika on 09.04.2022.
//

#ifndef SRENGINE_SRSL_H
#define SRENGINE_SRSL_H

#include <Graphics/Pipeline/IShaderProgram.h>
#include <Graphics/Loaders/ShaderProperties.h>
#include <Graphics/Loaders/SRSLParser.h>

namespace SR_GRAPH_NS::SRSL {
    SR_ENUM_NS_CLASS(ShaderType,
        Unknown,
        Spatial,            /// пространственный шейдер, все статические меши
        SpatialCustom,      /// пространственный шейдер (только вершины), все статические меши
        Skinned,            /// пространтсвенный шейдер, геометрия со скелетом
        PostProcessing,     /// шейдер пост-обработки
        Skybox,             /// шейдер скайбокса
        Simple,             ///
        Canvas,             /// шейдер 2д пользовательского интерфейса
        Particles,          /// шейдер для частиц
        Compute,            ///
        Line,               /// просто линия, имеет начало и конец
        Text,               /// специальный шейдер для рендера 3d текста
        TextUI,             /// специальный шейдер для рендера 2d текста
        Custom,             /// полностью чистый шейдер, все настраивается вручную
        Raygen,             /// трасировка лучей. генерация лучей и вызов трассировки
        AnyHit,             /// трасировка лучей. проверка на пересечение с примитивом (необязательный)
        ClosestHit,         /// трасировка лучей. проверка на пересечение с примитивом (обязательный)
        Miss,               /// трасировка лучей. пересечение не было найдено (в пределах [tmin; tmax])
        Intersection        /// трасировка лучей. проверка пересечения луча и геометрии
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
        ShaderType type = ShaderType::Unknown;
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

#endif //SRENGINE_SRSL_H
