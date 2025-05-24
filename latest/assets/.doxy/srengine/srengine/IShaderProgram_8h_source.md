

# File IShaderProgram.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Pipeline**](dir_b95270d167403b29f5d572cffd5b214a.md) **>** [**IShaderProgram.h**](IShaderProgram_8h.md)

[Go to the documentation of this file](IShaderProgram_8h.md)


```C++
//
// Created by Nikita on 29.03.2021.
//

#ifndef SR_ENGINE_GRAPHICS_I_SHADER_PROGRAM_H
#define SR_ENGINE_GRAPHICS_I_SHADER_PROGRAM_H

#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>

#include <Graphics/Types/Uniforms.h>
#include <Graphics/Types/Vertices.h>

namespace SR_GTYPES_NS {
    class Texture;
    class Shader;
}

namespace SR_GRAPH_NS {
    struct ShaderUseInfo {
        ShaderUseInfo() = default;
        explicit SR_CONSTEXPR ShaderUseInfo(SR_GTYPES_NS::Shader* pShader)
            : pShader(pShader)
            , ignoreReplace(false)
            , useMaterialUniforms(true)
            , useMaterialSamplers(true)
        { }

        SR_GTYPES_NS::Shader* pShader;
        bool ignoreReplace       : 4;
        bool useMaterialUniforms : 2;
        bool useMaterialSamplers : 2;
    };

    SR_ENUM_NS_CLASS_T(ShaderBindResult, uint8_t,
        Failed = 0,  
        Success = 1, 
        Duplicated,
        ReAllocated
    );

    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_LINE_START_POINT = "LINE_START_POINT";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_LINE_END_POINT = "LINE_END_POINT";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_LINE_COLOR = "LINE_COLOR";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_MODEL_MATRIX = "MODEL_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SLICED_TEXTURE_BORDER = "SLICED_TEXTURE_BORDER";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SLICED_WINDOW_BORDER = "SLICED_WINDOW_BORDER";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_MODEL_NO_SCALE_MATRIX = "MODEL_NO_SCALE_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SKELETON_MATRICES_128 = "SKELETON_MATRICES_128";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SKELETON_MATRIX_OFFSETS_128 = "SKELETON_MATRIX_OFFSETS_128";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SKELETON_MATRICES_256 = "SKELETON_MATRICES_256";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SKELETON_MATRIX_OFFSETS_256 = "SKELETON_MATRIX_OFFSETS_256";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SKELETON_MATRICES_384 = "SKELETON_MATRICES_384";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SKELETON_MATRIX_OFFSETS_384 = "SKELETON_MATRIX_OFFSETS_384";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_VIEW_MATRIX = "VIEW_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SSAO_SAMPLES = "SSAO_SAMPLES";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_LIGHT_SPACE_MATRIX = "LIGHT_SPACE_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_VIEW_NO_TRANSLATE_MATRIX = "VIEW_NO_TRANSLATE_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_PROJECTION_MATRIX = "PROJECTION_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_PROJECTION_NO_FOV_MATRIX = "PROJECTION_NO_FOV_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_ORTHOGONAL_MATRIX = "ORTHOGONAL_MATRIX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_VIEW_DIRECTION = "VIEW_DIRECTION";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_VIEW_POSITION = "VIEW_POSITION";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_TIME = "TIME";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_ASPECT = "ASPECT";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_RESOLUTION = "RESOLUTION";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SKYBOX_DIFFUSE = "SKYBOX_DIFFUSE";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_DEPTH_ATTACHMENT = "DEPTH_ATTACHMENT";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_TEXT_RECT_X = "TEXT_RECT_X";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_TEXT_RECT_Y = "TEXT_RECT_Y";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_TEXT_RECT_WIDTH = "TEXT_RECT_WIDTH";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_TEXT_RECT_HEIGHT = "TEXT_RECT_HEIGHT";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_DIRECTIONAL_LIGHT_POSITION = "DIRECTIONAL_LIGHT_POSITION";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_PC_SHADOW_CASCADE_INDEX = "PC_SHADOW_CASCADE_INDEX";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_CASCADE_LIGHT_SPACE_MATRICES = "CASCADE_LIGHT_SPACE_MATRICES";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_CASCADE_SPLITS = "CASCADE_SPLITS";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_PC_COLOR_BUFFER_MODE = "PC_COLOR_BUFFER_MODE";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_PC_COLOR_BUFFER_VALUE = "PC_COLOR_BUFFER_VALUE";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_SSAO_NOISE = "SSAO_NOISE";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_RGBA_VALUE = "RGBA_VALUE";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_TEXT_ATLAS_TEXTURE = "TEXT_ATLAS_TEXTURE";
    SR_INLINE_STATIC SR_UTILS_NS::StringAtom SHADER_NDC_RECT = "NDC_RECT";

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

    SR_ENUM_NS_CLASS(LayoutBinding, Unknown = 0, Uniform, Sampler2D, Attachhment, SSBO)
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

    struct SR_RENDERER_DLL_API Uniform {
        LayoutBinding type = LayoutBinding::Unknown;
        ShaderStage stage = ShaderStage::Unknown;
        uint64_t binding = 0;
        uint64_t size = 0;
    };

    typedef std::vector<Uniform> UBOInfo;

    struct SR_RENDERER_DLL_API SRShaderPushConstant {
        uint64_t size = 0;
        uint64_t offset = 0;
    };

    struct SR_RENDERER_DLL_API SRShaderStageInfo {
    public:
        SR_UTILS_NS::Path path;
        std::vector<SRShaderPushConstant> pushConstants;

    };

    struct SR_RENDERER_DLL_API SRShaderCreateInfo {
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

        if (SR_UTILS_NS::StringUtils::Contains(line, "ssbo"))
            return LayoutBinding::SSBO;

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
}

#endif //SR_ENGINE_GRAPHICS_I_SHADER_PROGRAM_H
```


