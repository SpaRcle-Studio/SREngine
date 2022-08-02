//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_ISHADERPROGRAM_H
#define GAMEENGINE_ISHADERPROGRAM_H

#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>

#include <Types/Uniforms.h>
#include <Types/Vertices.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    static constexpr uint64_t SHADER_MODEL_MATRIX = SR_COMPILE_TIME_CRC32_STR("MODEL_MATRIX");
    static constexpr uint64_t SHADER_VIEW_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_MATRIX");
    static constexpr uint64_t SHADER_VIEW_NO_TRANSLATE_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_NO_TRANSLATE_MATRIX");
    static constexpr uint64_t SHADER_PROJECTION_MATRIX = SR_COMPILE_TIME_CRC32_STR("PROJECTION_MATRIX");
    static constexpr uint64_t SHADER_ORTHOGONAL_MATRIX = SR_COMPILE_TIME_CRC32_STR("ORTHOGONAL_MATRIX");
    static constexpr uint64_t SHADER_TIME = SR_COMPILE_TIME_CRC32_STR("TIME");
    static constexpr uint64_t SHADER_SKYBOX_DIFFUSE = SR_COMPILE_TIME_CRC32_STR("SKYBOX_DIFFUSE");
    static constexpr uint64_t SHADER_DEPTH_ATTACHMENT = SR_COMPILE_TIME_CRC32_STR("DEPTH_ATTACHMENT");

    static constexpr std::array<uint64_t, 8> SHADER_COLOR_ATTACHMENTS = {
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_0"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_1"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_2"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_3"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_4"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_5"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_6"),
            SR_COMPILE_TIME_CRC32_STR("COLOR_ATTACHMENT_7")
    };

    /**
       0 - binding
       1 - ubo size
    */
    typedef std::vector<std::pair<uint32_t, uint64_t>> UBOInfo;

    typedef std::variant<SR_GTYPES_NS::Texture*, float_t, int32_t, SR_MATH_NS::FVector2, SR_MATH_NS::FVector3, SR_MATH_NS::FVector4> ShaderPropertyVariant;

    SR_ENUM_CLASS(ShaderVarType,
              Unknown,
              Int,
              Float,
              Vec2,
              Vec3,
              Vec4,
              Mat2,
              Mat3,
              Mat4,
              Sampler1D,
              Sampler2D,
              Sampler3D,
              SamplerCube,
              Sampler1DShadow,
              Sampler2DShadow,
    )

    static bool IsSamplerType(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Sampler1D:
            case ShaderVarType::Sampler2D:
            case ShaderVarType::Sampler3D:
            case ShaderVarType::SamplerCube:
            case ShaderVarType::Sampler1DShadow:
            case ShaderVarType::Sampler2DShadow:
                return true;
            default:
                return false;
        }
    }

    static bool IsMatrixType(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Mat2:
            case ShaderVarType::Mat3:
            case ShaderVarType::Mat4:
                return true;
            default:
                return false;
        }
    }

    static std::string ShaderVarTypeToString(ShaderVarType type) {
        std::string str = EnumShaderVarTypeToString(type);

        if (!str.empty()) {
            str[0] = tolower(str[0]);
        }

        return str;
    }

    static uint32_t GetShaderVarSize(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Int:
            case ShaderVarType::Float:
                return 4;
            case ShaderVarType::Vec2:
                return 4 * 2;
            case ShaderVarType::Vec3:
                return 4 * 3;
            case ShaderVarType::Vec4:
                return 4 * 4;
            case ShaderVarType::Mat2:
                return 4 * 2 * 2;
            case ShaderVarType::Mat3:
                return 4 * 3 * 3;
            case ShaderVarType::Mat4:
                return 4 * 4 * 4;
            case ShaderVarType::Unknown:
            default:
                SRAssert2(false, "unknown type!");
                return 0;
        }
    }

    static ShaderPropertyVariant GetVariantFromShaderVarType(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Int:
                return static_cast<int32_t>(0);
            case ShaderVarType::Float:
                return static_cast<float_t>(0.f);
            case ShaderVarType::Vec2:
                return SR_MATH_NS::FVector2(SR_MATH_NS::Unit(0));
            case ShaderVarType::Vec3:
                return SR_MATH_NS::FVector3(SR_MATH_NS::Unit(0));
            case ShaderVarType::Vec4:
                return SR_MATH_NS::FVector4(SR_MATH_NS::Unit(0));
            case ShaderVarType::Sampler1D:
            case ShaderVarType::Sampler2D:
            case ShaderVarType::Sampler3D:
            case ShaderVarType::SamplerCube:
            case ShaderVarType::Sampler1DShadow:
            case ShaderVarType::Sampler2DShadow:
                return static_cast<Types::Texture*>(nullptr);
            default:
                SRAssert(false);
                return ShaderPropertyVariant();
        }
    }

    static ShaderVarType GetShaderVarTypeFromString(std::string str) {
        if (!str.empty()) {
            str[0] = toupper(str[0]);
        }

        return StringToEnumShaderVarType(str);
    }

    typedef std::vector<std::pair<Vertices::Attribute, size_t>> VertexAttributes;
    typedef std::vector<SR_VERTEX_DESCRIPTION> VertexDescriptions;
    typedef std::list<std::pair<std::string, ShaderVarType>> ShaderProperties;
    typedef std::map<uint64_t, std::pair<ShaderVarType, uint32_t>> ShaderSamplers;
    typedef std::variant<glm::mat4, glm::mat3, glm::mat2, float, int, glm::vec2, glm::vec3, glm::vec4, glm::ivec2, glm::ivec3, glm::ivec4> ShaderVariable;

    SR_ENUM_CLASS(ShaderStage, Unknown, Vertex, Fragment, Tesselation)
    SR_ENUM_CLASS(LayoutBinding, Unknown = 0, Uniform = 1, Sampler2D = 2)
    SR_ENUM_CLASS(PolygonMode, Unknown, Fill, Line, Point)
    SR_ENUM_CLASS(CullMode, Unknown, None, Front, Back, FrontAndBack)
    SR_ENUM_CLASS(PrimitiveTopology,
            Unknown,
            PointList,
            LineList,
            LineStrip,
            TriangleList,
            TriangleStrip,
            TriangleFan,
            LineListWithAdjacency,
            LineStripWithAdjacency,
            TriangleListWithAdjacency,
            TriangleStripWithAdjacency,
            PathList)

    struct SR_DLL_EXPORT Uniform {
        LayoutBinding type;
        ShaderStage stage;
        uint32_t binding;
    };

    SR_ENUM_CLASS(DepthCompare,
        Unknown,
        Never,
        Less,
        Equal,
        LessOrEqual,
        Greater,
        NotEqual,
        GreaterOrEqual,
        Always)

    struct SR_DLL_EXPORT SRShaderCreateInfo {
        SRShaderCreateInfo() = default;

        SRShaderCreateInfo(const SRShaderCreateInfo& ref)
            : path(ref.path)
            , polygonMode(ref.polygonMode)
            , cullMode(ref.cullMode)
            , depthCompare(ref.depthCompare)
            , primitiveTopology(ref.primitiveTopology)
            , vertexAttributes(ref.vertexAttributes)
            , vertexDescriptions(ref.vertexDescriptions)
            , uniforms(ref.uniforms)
            , blendEnabled(ref.blendEnabled)
            , depthWrite(ref.depthWrite)
            , depthTest(ref.depthTest)
        { }

        SRShaderCreateInfo(SRShaderCreateInfo&& ref) noexcept {
            path = std::exchange(ref.path, {});
            polygonMode = std::exchange(ref.polygonMode, {});
            cullMode = std::exchange(ref.cullMode, {});
            depthCompare = std::exchange(ref.depthCompare, {});
            primitiveTopology = std::exchange(ref.primitiveTopology, {});
            vertexAttributes = std::exchange(ref.vertexAttributes, {});
            vertexDescriptions = std::exchange(ref.vertexDescriptions, {});
            uniforms = std::exchange(ref.uniforms, {});
            blendEnabled = std::exchange(ref.blendEnabled, {});
            depthWrite = std::exchange(ref.depthWrite, {});
            depthTest = std::exchange(ref.depthTest, {});
        }

        SRShaderCreateInfo& operator=(const SRShaderCreateInfo& ref) noexcept {
            path = ref.path;
            polygonMode = ref.polygonMode;
            cullMode = ref.cullMode;
            depthCompare = ref.depthCompare;
            primitiveTopology = ref.primitiveTopology;
            vertexAttributes = ref.vertexAttributes;
            vertexDescriptions = ref.vertexDescriptions;
            uniforms = ref.uniforms;
            blendEnabled = ref.blendEnabled;
            depthWrite = ref.depthWrite;
            depthTest = ref.depthTest;
            return *this;
        }

        SRShaderCreateInfo& operator=(SRShaderCreateInfo&& ref) noexcept {
            path = std::exchange(ref.path, {});
            polygonMode = std::exchange(ref.polygonMode, {});
            cullMode = std::exchange(ref.cullMode, {});
            depthCompare = std::exchange(ref.depthCompare, {});
            primitiveTopology = std::exchange(ref.primitiveTopology, {});
            vertexAttributes = std::exchange(ref.vertexAttributes, {});
            vertexDescriptions = std::exchange(ref.vertexDescriptions, {});
            uniforms = std::exchange(ref.uniforms, {});
            blendEnabled = std::exchange(ref.blendEnabled, {});
            depthWrite = std::exchange(ref.depthWrite, {});
            depthTest = std::exchange(ref.depthTest, {});
            return *this;
        }

    public:
        SR_NODISCARD bool Validate() const noexcept {
            return polygonMode       != PolygonMode::Unknown
                   && cullMode          != CullMode::Unknown
                   && depthCompare      != DepthCompare::Unknown
                   && primitiveTopology != PrimitiveTopology::Unknown;
        }

    public:
        SR_UTILS_NS::Path path;

        PolygonMode       polygonMode       = PolygonMode::Unknown;
        CullMode          cullMode          = CullMode::Unknown;
        DepthCompare      depthCompare      = DepthCompare::Unknown;
        PrimitiveTopology primitiveTopology = PrimitiveTopology::Unknown;

        VertexAttributes vertexAttributes;
        VertexDescriptions vertexDescriptions;
        UBOInfo uniforms;

        bool blendEnabled = false;
        bool depthWrite   = false;
        bool depthTest    = false;

    };

    static LayoutBinding GetBindingType(const std::string& line) {
        //! first check sampler, after that check uniform

        if (Helper::StringUtils::Contains(line, "sampler2D"))
            return LayoutBinding::Sampler2D;

        if (Helper::StringUtils::Contains(line, "samplerCube"))
            return LayoutBinding::Sampler2D;

        if (Helper::StringUtils::Contains(line, "uniform"))
            return LayoutBinding::Uniform;

        return LayoutBinding::Unknown;
    }

    struct SourceShader {
        std::string m_name;
        std::string m_path;
        ShaderStage m_stage;

        SourceShader(const std::string& name, const std::string& path, ShaderStage stage) {
            m_name  = name;
            m_path  = path;
            m_stage = stage;
        }
    };

    static std::vector<Uniform> AnalyseShader(const std::vector<SourceShader>& modules, bool* errors) {
        if (!errors) {
            SR_ERROR("Graphics::AnalyseShader() : errors flag pointer is nullptr! You are stupid!");
            return { };
        }
        else
            *errors = false;

        uint32_t count = 0;

        auto uniforms = std::vector<Uniform>();

        std::vector<std::string> lines = { };
        for (const auto& module : modules) {
            lines = Helper::FileSystem::ReadAllLines(module.m_path);
            if (lines.empty()) {
                SR_ERROR("Graphics::AnalyseShader() : failed to read module! \n\tPath: " + module.m_path);
                *errors = true;
                return { };
            }

            for (std::string line : lines) {
                if (const auto&& pos = line.find("//"); pos != std::string::npos) {
                    line.resize(pos);
                }

                if (Helper::StringUtils::Contains(line, "binding")) {
                    int32_t index = Helper::StringUtils::IndexOf(line, '=');

                    int32_t comment = Helper::StringUtils::IndexOf(line, '/');
                    if (comment >= 0 && comment < index)
                        continue;

                    if (index <= 0) {
                        SRAssert2(false, "Graphics::AnalyseShader() : incorrect binding location!");
                        *errors = true;
                        return { };
                    }

                    const auto&& location = Helper::StringUtils::ReadFrom(line, ')', index + 2);
                    if (location.empty()) {
                        SR_ERROR("Graphics::AnalyseShader() : failed match location!");
                        *errors = true;
                        return { };
                    }

                    Uniform uniform {
                        .type = GetBindingType(line),
                        .stage = module.m_stage,
                        .binding = static_cast<uint32_t>(std::atoll(location.c_str()))
                    };

                    uniforms.emplace_back(uniform);

                    count++;
                }
            }
        }

        /// error correction
        for (auto&& uniform : uniforms) {
            if (uniform.stage == ShaderStage::Unknown || uniform.type == LayoutBinding::Unknown) {
                SR_ERROR("IShaderProgram::AnalyseShader() : incorrect uniforms!");
                *errors = true;
                return {};
            }
        }

        return uniforms;
    }
}

namespace std {
    template<> struct hash<Framework::Graphics::ShaderSamplers> {
        size_t operator()(Framework::Graphics::ShaderSamplers const& value) const {
            std::size_t res = 0;

            for (auto&& [key, val] : value) {
                res = SR_UTILS_NS::HashCombine(key, res);
                res = SR_UTILS_NS::HashCombine(val.first, res);
                res = SR_UTILS_NS::HashCombine(val.second, res);
            }

            return res;
        }
    };

    template<> struct hash<Framework::Graphics::ShaderProperties> {
        size_t operator()(Framework::Graphics::ShaderProperties const& value) const {
            std::size_t res = 0;

            for (auto&& [key, val] : value) {
                res = SR_UTILS_NS::HashCombine(key, res);
                res = SR_UTILS_NS::HashCombine(val, res);
            }

            return res;
        }
    };
}

#endif //GAMEENGINE_ISHADERPROGRAM_H
