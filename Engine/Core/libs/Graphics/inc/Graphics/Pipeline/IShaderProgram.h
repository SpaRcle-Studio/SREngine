//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_ISHADERPROGRAM_H
#define GAMEENGINE_ISHADERPROGRAM_H

#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>

#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Vertices.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    static constexpr uint64_t SHADER_LINE_START_POINT = SR_COMPILE_TIME_CRC32_STR("LINE_START_POINT");
    static constexpr uint64_t SHADER_LINE_END_POINT = SR_COMPILE_TIME_CRC32_STR("LINE_END_POINT");
    static constexpr uint64_t SHADER_LINE_COLOR = SR_COMPILE_TIME_CRC32_STR("LINE_COLOR");
    static constexpr uint64_t SHADER_MODEL_MATRIX = SR_COMPILE_TIME_CRC32_STR("MODEL_MATRIX");
    static constexpr uint64_t SHADER_SKELETON_MATRICES_128 = SR_COMPILE_TIME_CRC32_STR("SKELETON_MATRICES_128");
    static constexpr uint64_t SHADER_SKELETON_MATRIX_OFFSETS_128 = SR_COMPILE_TIME_CRC32_STR("SKELETON_MATRIX_OFFSETS_128");
    static constexpr uint64_t SHADER_VIEW_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_MATRIX");
    static constexpr uint64_t SHADER_VIEW_NO_TRANSLATE_MATRIX = SR_COMPILE_TIME_CRC32_STR("VIEW_NO_TRANSLATE_MATRIX");
    static constexpr uint64_t SHADER_PROJECTION_MATRIX = SR_COMPILE_TIME_CRC32_STR("PROJECTION_MATRIX");
    static constexpr uint64_t SHADER_ORTHOGONAL_MATRIX = SR_COMPILE_TIME_CRC32_STR("ORTHOGONAL_MATRIX");
    static constexpr uint64_t SHADER_VIEW_DIRECTION = SR_COMPILE_TIME_CRC32_STR("VIEW_DIRECTION");
    static constexpr uint64_t SHADER_TIME = SR_COMPILE_TIME_CRC32_STR("TIME");
    static constexpr uint64_t SHADER_SKYBOX_DIFFUSE = SR_COMPILE_TIME_CRC32_STR("SKYBOX_DIFFUSE");
    static constexpr uint64_t SHADER_DEPTH_ATTACHMENT = SR_COMPILE_TIME_CRC32_STR("DEPTH_ATTACHMENT");
    static constexpr uint64_t SHADER_TEXT_ATLAS_TEXTURE = SR_COMPILE_TIME_CRC32_STR("TEXT_ATLAS_TEXTURE");
    static constexpr uint64_t SHADER_TEXT_RECT_X = SR_COMPILE_TIME_CRC32_STR("TEXT_RECT_X");
    static constexpr uint64_t SHADER_TEXT_RECT_Y = SR_COMPILE_TIME_CRC32_STR("TEXT_RECT_Y");
    static constexpr uint64_t SHADER_TEXT_RECT_WIDTH = SR_COMPILE_TIME_CRC32_STR("TEXT_RECT_WIDTH");
    static constexpr uint64_t SHADER_TEXT_RECT_HEIGHT = SR_COMPILE_TIME_CRC32_STR("TEXT_RECT_HEIGHT");

    /**
       0 - binding
       1 - ubo size
    */
    typedef std::vector<std::pair<uint32_t, uint64_t>> UBOInfo;

    typedef std::vector<std::pair<Vertices::Attribute, size_t>> VertexAttributes;
    typedef std::vector<SR_VERTEX_DESCRIPTION> VertexDescriptions;

    SR_DEPRECATED
    typedef std::variant<glm::mat4, glm::mat3, glm::mat2, float, int, glm::vec2, glm::vec3, glm::vec4, glm::ivec2, glm::ivec3, glm::ivec4> ShaderVariable;

    SR_ENUM_NS_CLASS(ShaderStage, Unknown, Vertex, Fragment, Tesselation)
    SR_ENUM_NS_CLASS(LayoutBinding, Unknown = 0, Uniform = 1, Sampler2D = 2)
    SR_ENUM_NS_CLASS(PolygonMode, Unknown, Fill, Line, Point)
    SR_ENUM_NS_CLASS(CullMode, Unknown, None, Front, Back, FrontAndBack)
    SR_ENUM_NS_CLASS(PrimitiveTopology,
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

    SR_ENUM_NS_CLASS(DepthCompare,
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

    static CullMode InverseCullMode(CullMode cullMode) {
        switch (cullMode) {
            case CullMode::Back:
                return CullMode::Front;
            case CullMode::Front:
                return CullMode::Back;
            default:
                return cullMode;
        }
    }

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

#endif //GAMEENGINE_ISHADERPROGRAM_H
