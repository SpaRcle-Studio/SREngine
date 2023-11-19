//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_ISHADERPROGRAM_H
#define GAMEENGINE_ISHADERPROGRAM_H

#include <Utils/FileSystem/FileSystem.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>

#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Vertices.h>

#define SR_SHADER_MAKE_HASH_NAME(name) \
    SR_UTILS_NS::StringAtom(name).GetHash()

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS {
    SR_ENUM_NS_CLASS_T(ShaderBindResult, uint8_t,
        Failed = 0,  /// false
        Success = 1, /// true
        Duplicated,
        ReAllocated
    );

    SR_INLINE_STATIC uint64_t SHADER_LINE_START_POINT = SR_SHADER_MAKE_HASH_NAME("LINE_START_POINT");
    SR_INLINE_STATIC uint64_t SHADER_LINE_END_POINT = SR_SHADER_MAKE_HASH_NAME("LINE_END_POINT");
    SR_INLINE_STATIC uint64_t SHADER_LINE_COLOR = SR_SHADER_MAKE_HASH_NAME("LINE_COLOR");
    SR_INLINE_STATIC uint64_t SHADER_MODEL_MATRIX = SR_SHADER_MAKE_HASH_NAME("MODEL_MATRIX");
    SR_INLINE_STATIC uint64_t SHADER_SLICED_TEXTURE_BORDER = SR_SHADER_MAKE_HASH_NAME("SLICED_TEXTURE_BORDER");
    SR_INLINE_STATIC uint64_t SHADER_SLICED_WINDOW_BORDER = SR_SHADER_MAKE_HASH_NAME("SLICED_WINDOW_BORDER");
    SR_INLINE_STATIC uint64_t SHADER_MODEL_NO_SCALE_MATRIX = SR_SHADER_MAKE_HASH_NAME("MODEL_NO_SCALE_MATRIX");
    SR_INLINE_STATIC uint64_t SHADER_SKELETON_MATRICES_128 = SR_SHADER_MAKE_HASH_NAME("SKELETON_MATRICES_128");
    SR_INLINE_STATIC uint64_t SHADER_SKELETON_MATRIX_OFFSETS_128 = SR_SHADER_MAKE_HASH_NAME("SKELETON_MATRIX_OFFSETS_128");
    SR_INLINE_STATIC uint64_t SHADER_SKELETON_MATRICES_256 = SR_SHADER_MAKE_HASH_NAME("SKELETON_MATRICES_256");
    SR_INLINE_STATIC uint64_t SHADER_SKELETON_MATRIX_OFFSETS_256 = SR_SHADER_MAKE_HASH_NAME("SKELETON_MATRIX_OFFSETS_256");
    SR_INLINE_STATIC uint64_t SHADER_SKELETON_MATRICES_384 = SR_SHADER_MAKE_HASH_NAME("SKELETON_MATRICES_384");
    SR_INLINE_STATIC uint64_t SHADER_SKELETON_MATRIX_OFFSETS_384 = SR_SHADER_MAKE_HASH_NAME("SKELETON_MATRIX_OFFSETS_384");
    SR_INLINE_STATIC uint64_t SHADER_VIEW_MATRIX = SR_SHADER_MAKE_HASH_NAME("VIEW_MATRIX");
    SR_INLINE_STATIC uint64_t SHADER_SSAO_NOISE = SR_SHADER_MAKE_HASH_NAME("SSAO_NOISE");
    SR_INLINE_STATIC uint64_t SHADER_SSAO_SAMPLES = SR_SHADER_MAKE_HASH_NAME("SSAO_SAMPLES");
    SR_INLINE_STATIC uint64_t SHADER_LIGHT_SPACE_MATRIX = SR_SHADER_MAKE_HASH_NAME("LIGHT_SPACE_MATRIX");
    SR_INLINE_STATIC uint64_t SHADER_VIEW_NO_TRANSLATE_MATRIX = SR_SHADER_MAKE_HASH_NAME("VIEW_NO_TRANSLATE_MATRIX");
    SR_INLINE_STATIC uint64_t SHADER_PROJECTION_MATRIX = SR_SHADER_MAKE_HASH_NAME("PROJECTION_MATRIX");
    SR_INLINE_STATIC uint64_t SHADER_ORTHOGONAL_MATRIX = SR_SHADER_MAKE_HASH_NAME("ORTHOGONAL_MATRIX");
    SR_INLINE_STATIC uint64_t SHADER_VIEW_DIRECTION = SR_SHADER_MAKE_HASH_NAME("VIEW_DIRECTION");
    SR_INLINE_STATIC uint64_t SHADER_VIEW_POSITION = SR_SHADER_MAKE_HASH_NAME("VIEW_POSITION");
    SR_INLINE_STATIC uint64_t SHADER_TIME = SR_SHADER_MAKE_HASH_NAME("TIME");
    SR_INLINE_STATIC uint64_t SHADER_RESOLUTION = SR_SHADER_MAKE_HASH_NAME("RESOLUTION");
    SR_INLINE_STATIC uint64_t SHADER_SKYBOX_DIFFUSE = SR_SHADER_MAKE_HASH_NAME("SKYBOX_DIFFUSE");
    SR_INLINE_STATIC uint64_t SHADER_DEPTH_ATTACHMENT = SR_SHADER_MAKE_HASH_NAME("DEPTH_ATTACHMENT");
    SR_INLINE_STATIC uint64_t SHADER_TEXT_ATLAS_TEXTURE = SR_SHADER_MAKE_HASH_NAME("TEXT_ATLAS_TEXTURE");
    SR_INLINE_STATIC uint64_t SHADER_TEXT_RECT_X = SR_SHADER_MAKE_HASH_NAME("TEXT_RECT_X");
    SR_INLINE_STATIC uint64_t SHADER_TEXT_RECT_Y = SR_SHADER_MAKE_HASH_NAME("TEXT_RECT_Y");
    SR_INLINE_STATIC uint64_t SHADER_TEXT_RECT_WIDTH = SR_SHADER_MAKE_HASH_NAME("TEXT_RECT_WIDTH");
    SR_INLINE_STATIC uint64_t SHADER_TEXT_RECT_HEIGHT = SR_SHADER_MAKE_HASH_NAME("TEXT_RECT_HEIGHT");
    SR_INLINE_STATIC uint64_t SHADER_DIRECTIONAL_LIGHT_POSITION = SR_SHADER_MAKE_HASH_NAME("DIRECTIONAL_LIGHT_POSITION");
    SR_INLINE_STATIC uint64_t SHADER_SHADOW_CASCADE_INDEX = SR_SHADER_MAKE_HASH_NAME("SHADOW_CASCADE_INDEX");
    SR_INLINE_STATIC uint64_t SHADER_CASCADE_LIGHT_SPACE_MATRICES = SR_SHADER_MAKE_HASH_NAME("CASCADE_LIGHT_SPACE_MATRICES");
    SR_INLINE_STATIC uint64_t SHADER_CASCADE_SPLITS = SR_SHADER_MAKE_HASH_NAME("CASCADE_SPLITS");
    SR_INLINE_STATIC uint64_t SHADER_COLOR_BUFFER_MODE = SR_SHADER_MAKE_HASH_NAME("COLOR_BUFFER_MODE");
    SR_INLINE_STATIC uint64_t SHADER_COLOR_BUFFER_VALUE = SR_SHADER_MAKE_HASH_NAME("COLOR_BUFFER_VALUE");

    typedef std::vector<std::pair<Vertices::Attribute, size_t>> VertexAttributes;
    typedef std::vector<SR_VERTEX_DESCRIPTION> VertexDescriptions;

    SR_DEPRECATED
    typedef std::variant<glm::mat4, glm::mat3, glm::mat2, float, int, glm::vec2, glm::vec3, glm::vec4, glm::ivec2, glm::ivec3, glm::ivec4> ShaderVariable;

    SR_ENUM_NS_CLASS_T(ShaderStage, uint8_t,
        Unknown,
        Vertex,
        Fragment,
        Geometry,
        Tesselation,
        Compute,
        Raygen,
        Intersection,
        HitClosest,
        HitAny,
        MissPrimary,
        MissSecondary
    );

    SR_ENUM_NS_CLASS(LayoutBinding, Unknown = 0, Uniform = 1, Sampler2D = 2, Attachhment=3)
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

    struct SR_DLL_EXPORT Uniform {
        LayoutBinding type = LayoutBinding::Unknown;
        ShaderStage stage = ShaderStage::Unknown;
        uint64_t binding = 0;
        uint64_t size = 0;
    };

    typedef std::vector<Uniform> UBOInfo;

    struct SR_DLL_EXPORT SRShaderPushConstant {
        uint64_t size = 0;
        uint64_t offset = 0;
    };

    struct SR_DLL_EXPORT SRShaderStageInfo {
    public:
        SR_UTILS_NS::Path path;
        std::vector<SRShaderPushConstant> pushConstants;

    };

    struct SR_DLL_EXPORT SRShaderCreateInfo {
    public:
        SR_NODISCARD bool Validate() const noexcept {
            return polygonMode       != PolygonMode::Unknown
                   && cullMode          != CullMode::Unknown
                   && depthCompare      != DepthCompare::Unknown
                   && primitiveTopology != PrimitiveTopology::Unknown;
        }

    public:
        std::map<ShaderStage, SRShaderStageInfo> stages;

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

    SR_MAYBE_UNUSED static CullMode InverseCullMode(CullMode cullMode) {
        switch (cullMode) {
            case CullMode::Back:
                return CullMode::Front;
            case CullMode::Front:
                return CullMode::Back;
            default:
                return cullMode;
        }
    }

    SR_MAYBE_UNUSED static LayoutBinding GetBindingType(const std::string& line) {
        //! first check sampler, after that check uniform

        if (SR_UTILS_NS::StringUtils::Contains(line, "sampler2DArray"))
            return LayoutBinding::Sampler2D;

        if (SR_UTILS_NS::StringUtils::Contains(line, "sampler2D"))
            return LayoutBinding::Sampler2D;

        if (SR_UTILS_NS::StringUtils::Contains(line, "samplerCube"))
            return LayoutBinding::Sampler2D;

        if (SR_UTILS_NS::StringUtils::Contains(line, "subpassInputMS"))
            return LayoutBinding::Attachhment;

        if (SR_UTILS_NS::StringUtils::Contains(line, "subpassInput"))
            return LayoutBinding::Attachhment;

        if (SR_UTILS_NS::StringUtils::Contains(line, "uniform"))
            return LayoutBinding::Uniform;

        return LayoutBinding::Unknown;
    }

    struct SourceShader {
        std::string m_path;
        ShaderStage m_stage;

        SourceShader(const std::string& path, ShaderStage stage) {
            m_path  = path;
            m_stage = stage;
        }
    };

    SR_MAYBE_UNUSED static std::optional<std::vector<Uniform>> AnalyseShader(const std::vector<SourceShader>& modules) {
        uint32_t count = 0;

        auto uniforms = std::vector<Uniform>();

        std::vector<std::string> lines = { };
        for (auto&& module : modules) {
            auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Shaders").Concat(module.m_path);
            lines = SR_UTILS_NS::FileSystem::ReadAllLines(path);
            if (lines.empty()) {
                SR_ERROR("Graphics::AnalyseShader() : failed to read module! \n\tPath: " + path.ToString());
                return std::optional<std::vector<Uniform>>();
            }

            for (std::string line : lines) {
                if (const auto&& pos = line.find("//"); pos != std::string::npos) {
                    line.resize(pos);
                }

                int32_t bindingIndex = SR_UTILS_NS::StringUtils::IndexOf(line, "binding");
                if (bindingIndex >= 0) {
                    int32_t index = SR_UTILS_NS::StringUtils::IndexOf(line, '=', bindingIndex);

                    int32_t comment = SR_UTILS_NS::StringUtils::IndexOf(line, '/');
                    if (comment >= 0 && comment < index)
                        continue;

                    if (index <= 0) {
                        SRHalt("Graphics::AnalyseShader() : incorrect binding location!");
                        return std::optional<std::vector<Uniform>>();
                    }

                    const auto&& location = SR_UTILS_NS::StringUtils::ReadNumber(line, index + 2 /** space and assign */);
                    if (location.empty()) {
                        SR_ERROR("Graphics::AnalyseShader() : failed match location!");
                        return std::optional<std::vector<Uniform>>();
                    }

                    Uniform uniform {
                        .type = GetBindingType(line),
                        .stage = module.m_stage,
                        .binding = static_cast<uint32_t>(SR_UTILS_NS::LexicalCast<uint32_t>(location))
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
                return std::optional<std::vector<Uniform>>();
            }
        }

        return uniforms;
    }
}

#endif //GAMEENGINE_ISHADERPROGRAM_H
