//
// Created by Nikita on 29.03.2021.
//

#ifndef GAMEENGINE_ISHADERPROGRAM_H
#define GAMEENGINE_ISHADERPROGRAM_H

#include <FileSystem/FileSystem.h>
#include <Utils/StringUtils.h>
#include <Utils/Enumerations.h>

namespace Framework::Graphics {
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

    struct Uniform {
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

    struct SRShaderCreateInfo {
        PolygonMode       polygonMode       = PolygonMode::Unknown;
        CullMode          cullMode          = CullMode::Unknown;
        DepthCompare      depthCompare      = DepthCompare::Unknown;
        PrimitiveTopology primitiveTopology = PrimitiveTopology::Unknown;

        bool blendEnabled = false;
        bool depthWrite   = false;
        bool depthTest    = false;

        [[nodiscard]] bool Validate() const {
            return polygonMode       != PolygonMode::Unknown
                   && cullMode          != CullMode::Unknown
                   && depthCompare      != DepthCompare::Unknown
                   && primitiveTopology != PrimitiveTopology::Unknown;
        }
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
                Helper::Debug::Error("IShaderProgram::AnalyseShader() : incorrect uniforms!");
                *errors = true;
                return {};
            }
        }

        return uniforms;
    }
}

#endif //GAMEENGINE_ISHADERPROGRAM_H
