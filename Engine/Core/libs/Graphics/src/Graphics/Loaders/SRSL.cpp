//
// Created by Monika on 09.04.2022.
//

#include <Graphics/Loaders/SRSL.h>

const std::unordered_map<std::string, Framework::Graphics::ShaderVarType> SR_GRAPH_NS::SRSL::SRSLLoader::STANDARD_VARIABLES = {
        { "HALF_SIZE_NEAR_PLANE", ShaderVarType::Vec2 },
        { "MODEL_MATRIX", ShaderVarType::Mat4 },
        { "VIEW_MATRIX", ShaderVarType::Mat4 },
        { "PROJECTION_MATRIX", ShaderVarType::Mat4 },
        { "ORTHOGONAL_MATRIX", ShaderVarType::Mat4 },
        { "VIEW_NO_TRANSLATE_MATRIX", ShaderVarType::Mat4 },
        { "SKELETON_MATRICES_128", ShaderVarType::Skeleton128 },
        { "SKYBOX_DIFFUSE", ShaderVarType::SamplerCube },
        { "TEXT_ATLAS_TEXTURE", ShaderVarType::Sampler2D },
        { "TIME", ShaderVarType::Float },
        { "TEXT_RECT_X", ShaderVarType::Float },
        { "TEXT_RECT_Y", ShaderVarType::Float },
        { "TEXT_RECT_WIDTH", ShaderVarType::Float },
        { "TEXT_RECT_HEIGHT", ShaderVarType::Float },
        { "VIEW_DIRECTION", ShaderVarType::Vec3 },
        { "LINE_START_POINT", ShaderVarType::Vec3 },
        { "LINE_END_POINT", ShaderVarType::Vec3 },
        { "LINE_COLOR", ShaderVarType::Vec4 },
};

const std::unordered_map<std::string, Framework::Graphics::ShaderVarType> SR_GRAPH_NS::SRSL::SRSLLoader::COLOR_INDICES = {
        { "COLOR_INDEX_0", ShaderVarType::Vec4 },
        { "COLOR_INDEX_1", ShaderVarType::Vec4 },
        { "COLOR_INDEX_2", ShaderVarType::Vec4 },
        { "COLOR_INDEX_3", ShaderVarType::Vec4 },
        { "COLOR_INDEX_4", ShaderVarType::Vec4 },
        { "COLOR_INDEX_5", ShaderVarType::Vec4 },
        { "COLOR_INDEX_6", ShaderVarType::Vec4 },
        { "COLOR_INDEX_7", ShaderVarType::Vec4 },
};

const std::unordered_map<std::string, Framework::Graphics::ShaderVarType> SR_GRAPH_NS::SRSL::SRSLLoader::ATTACHMENTS = {
        { "COLOR_ATTACHMENT_0", ShaderVarType::Sampler2D },
        { "COLOR_ATTACHMENT_1", ShaderVarType::Sampler2D },
        { "COLOR_ATTACHMENT_2", ShaderVarType::Sampler2D },
        { "COLOR_ATTACHMENT_3", ShaderVarType::Sampler2D },
        { "COLOR_ATTACHMENT_4", ShaderVarType::Sampler2D },
        { "COLOR_ATTACHMENT_5", ShaderVarType::Sampler2D },
        { "COLOR_ATTACHMENT_6", ShaderVarType::Sampler2D },
        { "COLOR_ATTACHMENT_7", ShaderVarType::Sampler2D },
        { "DEPTH_ATTACHMENT", ShaderVarType::Sampler2D },
};

std::optional<SR_GRAPH_NS::SRSL::SRSLUnit> SR_GRAPH_NS::SRSL::SRSLLoader::Load(std::string path) {
    SR_SHADER_LOG("SRSLLoader::Load() : loading SpaRcle shader... \n\tPath: " + path);

    if (const auto& pos = path.find(".srsl"); pos != std::string::npos) {
        path.resize(path.size() - (path.size() - pos));
    }

    auto&& resManager = SR_UTILS_NS::ResourceManager::Instance();
    auto&& cache = resManager.GetCachePath().Concat("Shaders/SRSL");
    auto&& shader = resManager.GetResPath().Concat(path).ConcatExt(".srsl");

    if (!shader.Exists()) {
        SR_ERROR("SRSLLoader::Load() : file not exists! Path: " + shader.ToString());
        return {};
    }

    SRSLUnit unit;
    unit.path = path;

    SRSLCode code = SR_UTILS_NS::FileSystem::ReadAllLines(shader);

    if (!RemoveComments(code)) {
        SR_ERROR("SRSLLoader::Load() : failed to remove comments! Path: " + shader.ToString());
        return {};
    }

    auto parseData = SRSL::Parse(code);
    if (!parseData) {
        SR_ERROR("SRSLLoader::Load() : failed to parse! \n\tPath: " + shader.ToString());
        return {};
    }

    if (!PrepareUnit(unit, parseData->vars)) {
        SR_ERROR("SRSLLoader::Load() : failed to prepare unit! \n\tPath: " + shader.ToString());
        return {};
    }

    const auto&& vertex = MakeVertexCode(unit, parseData.value());
    const auto&& fragment = MakeFragmentCode(unit, parseData.value());

    if (!AnalyzeUniforms(unit, parseData.value(), vertex + fragment)) {
        SR_ERROR("SRSLLoader::Load() : failed to analyze uniforms! \n\tPath: " + shader.ToString());
        return {};
    }

    if (!CreateVertex(unit, parseData.value(), vertex, cache.Concat(path).Concat("shader.vert"))) {
        SR_ERROR("SRSLLoader::Load() : failed to create vertex shader! \n\tPath: " + shader.ToString());
        return {};
    }

    if (!CreateFragment(unit, parseData.value(), fragment, cache.Concat(path).Concat("shader.frag"))) {
        SR_ERROR("SRSLLoader::Load() : failed to create fragment shader! \n\tPath: " + shader.ToString());
        return {};
    }

    return unit;
}

SR_GRAPH_NS::SRSL::SRSLVariables SR_GRAPH_NS::SRSL::SRSLLoader::RefAnalyzer(const std::string& code, const SRSLVars& allVars) {
    SRSLVariables used;

    const auto&& isUsed = [&code](const std::string& var) -> bool {
        size_t offset = 0;
    retry:
        if (auto&& pos = code.find(var, offset); pos != std::string::npos) {
            const std::string operators = "!~`@#$%^&*()-=+:'\"|\\/.,?^;<>[] \t\n";

            /// check left side
            if (pos > 0 && operators.find(code[pos - 1]) == std::string::npos) {
                offset = pos + var.size();
                goto retry;
            }

            /// check right side
            if ((pos + var.size() < code.size()) && operators.find(code[pos + var.size()]) == std::string::npos) {
                offset = pos + var.size();
                goto retry;
            }
        }
        else
            return false;

        return true;
    };

    for (const auto& var : allVars) {
        auto&& args = SR_UTILS_NS::StringUtils::Split(var, " ");

        /// { uniform, type, name }
        if (args.size() != 3) {
            continue;
        }

        if (args[0] != "uniform") {
            continue;
        }

        used[args[2]] = SRSLVariable { isUsed(args[2]), true, GetShaderVarTypeFromString(args[1]), -1 };
    }

    for (const auto& [name, type] : STANDARD_VARIABLES) {
        used[name] = SRSLVariable { isUsed(name), false, type, -1 };
    }

    for (const auto& [name, type] : COLOR_INDICES) {
        used[name] = SRSLVariable { isUsed(name), false, type, -1 };
    }

    for (const auto& [name, type] : ATTACHMENTS) {
        used[name] = SRSLVariable { isUsed(name), false, type, -1 };
    }

    return used;
}

bool SR_GRAPH_NS::SRSL::SRSLLoader::PrepareUnit(SRSLUnit& unit, const SRSLVars& vars) {
    /// prepare settings
    for (const auto& var : vars) {
        auto&& args = SR_UTILS_NS::StringUtils::Split(var, " ");

        if (args.size() != 2) {
            continue;
        }

        if (args[0] == "ShaderType") {
            unit.type = SR_UTILS_NS::EnumReflector::FromString<ShaderType>(args[1]);
        }
        else if (args[0] == "PolygonMode") {
            unit.createInfo.polygonMode = SR_UTILS_NS::EnumReflector::FromString<PolygonMode>(args[1]);
        }
        else if (args[0] == "CullMode") {
            unit.createInfo.cullMode = SR_UTILS_NS::EnumReflector::FromString<CullMode>(args[1]);
        }
        else if (args[0] == "DepthCompare") {
            unit.createInfo.depthCompare = SR_UTILS_NS::EnumReflector::FromString<DepthCompare>(args[1]);
        }
        else if (args[0] == "PrimitiveTopology") {
            unit.createInfo.primitiveTopology = SR_UTILS_NS::EnumReflector::FromString<PrimitiveTopology>(args[1]);
        }
        else if (args[0] == "BlendEnabled") {
            unit.createInfo.blendEnabled = SR_UTILS_NS::LexicalCast<bool>(args[1]);
        }
        else if (args[0] == "DepthWrite") {
            unit.createInfo.depthWrite = SR_UTILS_NS::LexicalCast<bool>(args[1]);
        }
        else if (args[0] == "DepthTest") {
            unit.createInfo.depthTest = SR_UTILS_NS::LexicalCast<bool>(args[1]);
        }
    }

    if (unit.type == ShaderType::Unknown) {
        SR_ERROR("SRSLLoader::PrepareUnit() : shader type not defined!");
        return false;
    }

    return true;
}

bool Framework::Graphics::SRSL::SRSLLoader::AnalyzeUniforms(SRSLUnit &unit, SRSLParseData &parseData, const std::string &fullCode) {
    SRSLVariables uniforms;

    for (auto&& [name, var] : RefAnalyzer(fullCode, parseData.vars)) {
        if (!IsSamplerType(var.type) && COLOR_INDICES.count(name) == 0) {
            uniforms[name] = var;
        }
    }

    if (!uniforms.empty()) {
        bool used = false;

        for (auto&& [name, var] : uniforms) {
            var.binding = parseData.lastBinding;
            unit.bindings[name] = var;
            used |= var.used;
        }

        if (used) {
            ++parseData.lastBinding;
        }
    }

    return true;
}

Framework::Graphics::SRSL::SRSLVariables Framework::Graphics::SRSL::SRSLLoader::GetColorIndices(const std::string &code) {
    SRSLVariables indices;

    const std::string prefix = "COLOR_INDEX_";

    for (auto&& [name, var] : RefAnalyzer(code, {})) {
        if (auto&& pos = name.find(prefix); pos != std::string::npos) {
            var.binding = SR_UTILS_NS::LexicalCast<int32_t>(SR_UTILS_NS::StringUtils::Remove(name, prefix.size()));
            indices[name] = var;
        }
    }

    return indices;
}

std::string SR_GRAPH_NS::SRSL::SRSLLoader::MakeUniformsCode(SRSLUnit& unit, const std::string &code, SRSLParseData &parseData) {
    SRSLVariables samplers;

    for (auto&& [name, var] : RefAnalyzer(code, parseData.vars)) {
        if (IsSamplerType(var.type)) {
            samplers[name] = var;
        }
    }

    std::string source = "// -- codegen -- | begin default bindings\n";

    for (auto&& [name, var] : samplers) {
        if (!var.used) {
            continue;
        }

        if (unit.bindings.count(name) == 0) {
            samplers[name].binding = parseData.lastBinding++;
            unit.bindings[name] = samplers[name];
        }

        source += SR_UTILS_NS::Format("layout (binding = %i) uniform %s;",
                unit.bindings[name].binding,
                MakeShaderVariable(var.type, name).c_str()
        );

        if (var.show) {
            source += " // public\n";
        }
        else
            source += " // hidden\n";
    }

    /// ----------------------------------------------------------------------------------------------------------------

    auto&& uniforms = unit.GetUniformBlock();

    if (!uniforms.empty()) {
        source += SR_UTILS_NS::Format("layout (std140, binding = %i) uniform BLOCK {\n", uniforms.begin()->second.binding);

        for (auto&& [name, var] : uniforms) {
            source += SR_UTILS_NS::Format("\t%s;", MakeShaderVariable(var.type, name).c_str());

            if (var.show) {
                source += " // public\n";
            }
            else
                source += " // hidden\n";
        }

        source += "};\n";
    }

    source += "// -- codegen -- | end default bindings\n\n";

    return source;
}

bool SR_GRAPH_NS::SRSL::SRSLLoader::CreateFragment(SRSLUnit &unit, SRSLParseData &parseData, const std::string& code, SR_UTILS_NS::Path &&path) {
    auto& stage = unit.stages[ShaderStage::Fragment];
    stage.path = std::move(path);

    if (!stage.path.Make(Helper::Path::Type::File)) {
        SR_ERROR("SRSLLoader::CreateFragment() : failed to create fragment path! Path: " + stage.path.ToString());
        unit.stages.erase(ShaderStage::Fragment);
        return false;
    }

    /// ----------------------------------------------------------------------------------------------------------------

    std::string source;

    source += "// [WARNING: THIS FILE WAS CREATED BY CODE GENERATION]\n\n";

    source += "#version 450\n\n";
    source += "#extension GL_ARB_separate_shader_objects : enable\n";
    source += "#extension GL_EXT_shader_atomic_float : enable\n\n";

    switch (unit.type) {
        case ShaderType::Custom:
            break;
        case ShaderType::Spatial:
        case ShaderType::SpatialCustom:
        case ShaderType::Skinned:
        case ShaderType::Simple:
        case ShaderType::Skybox:
        case ShaderType::Canvas:
        case ShaderType::Line:
        case ShaderType::Text:
        case ShaderType::TextUI:
        case ShaderType::PostProcessing: {
            for (auto&& [name, var] : GetColorIndices(code)) {
                if (!var.used) {
                    continue;
                }

                source += SR_UTILS_NS::Format("layout (location = %i) out %s;\n",
                        var.binding, MakeShaderVariable(var.type, name).c_str()
                );
            }

            source += "\n";
            break;
        }
        default:
            SRAssert(false);
            return false;
    }

    source += MakeUniformsCode(unit, code, parseData);

    source += code;

    /// ----------------------------------------------------------------------------------------------------------------

    return SR_UTILS_NS::FileSystem::WriteToFile(stage.path.ToString(), source);
}

std::string SR_GRAPH_NS::SRSL::SRSLLoader::MakeFragmentCode(const SRSLUnit &unit, const SRSLParseData &parseData) {
    std::string source;

    source += "// -- codegen -- | begin declaration default vars\n";
    uint32_t location = 0;
    switch (unit.type) {
        case ShaderType::SpatialCustom:
        case ShaderType::Spatial:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 NORMAL;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 TANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in float VERTEX_INDEX;\n", location++);
            source += "vec4 COLOR;";
            break;
        case ShaderType::Skinned:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 NORMAL;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 TANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in float VERTEX_INDEX;\n", location++);

            for (uint8_t i = 0; i < SR_MAX_BONES_ON_VERTEX; i++) {
                source += SR_UTILS_NS::Format("layout (location = %i) in vec2 WEIGHT%i;\n", location++, i);
            }

            source += "vec4 COLOR;";
            break;
        case ShaderType::Simple:
        case ShaderType::Canvas:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV;\n", location++);
            source += "vec4 COLOR;";
            break;
        case ShaderType::Skybox:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 UV;\n", location++);
            source += "vec4 COLOR;";
            break;
        case ShaderType::TextUI:
        case ShaderType::Text:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV;\n", location++);
            source += "vec4 COLOR;";
            break;
        case ShaderType::Line:
        case ShaderType::Custom:
            break;
        case ShaderType::PostProcessing:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV;\n", location++);
            break;
        default:
            SRAssert(false);
            break;
    }
    source += "// -- codegen -- | end declaration default vars\n\n";

    source += SRSL::GenerateFunctions(parseData.functions, "fragment");

    source += "void main() {\n";

    /// вставляем код отвечающий за данный тип шейдера
    source += "\t// -- codegen -- | begin shader pre code\n";
    switch (unit.type) {
        case ShaderType::TextUI:
        case ShaderType::Text:
            source += "\tCOLOR = texture(TEXT_ATLAS_TEXTURE, UV);";
            break;
        default:
            break;
    }
    source += "\t// -- codegen -- | end shader pre code\n";

    /// опционально вставляем пользовательский код
    auto&& functionIt = std::find_if(parseData.functions.begin(), parseData.functions.end(), [](const SRSLFunc& func) -> bool {
        return func.name == "fragment";
    });
    if (functionIt != parseData.functions.end()) {
        source += "\t// -- codegen -- | begin user code\n\t{\n";
        source += SR_UTILS_NS::StringUtils::Tab(functionIt->code);
        source += "\t}\n\t// -- codegen -- | end user code\n\n";
    }

    /// вставляем код отвечающий за данный тип шейдера
    source += "\t// -- codegen -- | begin shader code\n";
    switch (unit.type) {
        case ShaderType::Custom:
            break;
        case ShaderType::Spatial:
        case ShaderType::SpatialCustom:
        case ShaderType::Skinned:
        case ShaderType::Simple:
        case ShaderType::TextUI:
        case ShaderType::Text:
        case ShaderType::Skybox:
        case ShaderType::Canvas:
            source += "\tCOLOR_INDEX_0 = COLOR;\n";
            break;
        case ShaderType::Line:
            source += "\tCOLOR_INDEX_0 = LINE_COLOR;\n";
            break;
        case ShaderType::PostProcessing:
            break;
        default:
            SRAssert(false);
            break;
    }
    source += "\t// -- codegen -- | end shader code\n";

    source += "}\n";

    return source;
}

std::string SR_GRAPH_NS::SRSL::SRSLLoader::MakeVertexCode(const SRSLUnit &unit, const SRSLParseData &parseData) {
    std::string source;

    source += "// -- codegen -- | begin declaration default vars\n";
    uint32_t location = 0;
    switch (unit.type) {
        case ShaderType::TextUI:
        case ShaderType::Text:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            break;
        case ShaderType::Custom:
        case ShaderType::Line:
            break;
        case ShaderType::SpatialCustom:
        case ShaderType::Spatial:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 NORMAL;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 TANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 BITANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out float VERTEX_INDEX;\n", location++);
            break;
        case ShaderType::Skinned:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 NORMAL;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 TANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 BITANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out float VERTEX_INDEX;\n", location++);

            for (uint8_t i = 0; i < SR_MAX_BONES_ON_VERTEX; i++) {
                source += SR_UTILS_NS::Format("layout (location = %i) out vec2 WEIGHT%i;\n", location++, i);
            }
            break;
        case ShaderType::PostProcessing:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out float VERTEX_INDEX;\n", location++);
            break;
        case ShaderType::Simple:
        case ShaderType::Canvas:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            break;
        case ShaderType::Skybox:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out float VERTEX_INDEX;\n", location++);
            break;
        default:
            SRHalt("SRSLLoader::MakeVertexCode() : unknown shader type!");
            break;
    }
    source += "// -- codegen -- | end declaration default vars\n\n";

    source += SRSL::GenerateFunctions(parseData.functions, "vertex");

    source += "void main() {\n";

    /// объявляем все переменные по умолчанию
    source += "\t// -- codegen -- | begin default vars\n";
    switch (unit.type) {
        case ShaderType::Custom:
        case ShaderType::TextUI:
        case ShaderType::Text:
        case ShaderType::Line:
            break;
        case ShaderType::PostProcessing:
            source += "\tVERTEX_INDEX = float(gl_VertexIndex);\n";
            break;
        case ShaderType::SpatialCustom:
        case ShaderType::Spatial:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            source += "\tUV = UV_INPUT;\n";
            source += "\tNORMAL = NORMAL_INPUT;\n";
            source += "\tTANGENT = TANGENT_INPUT;\n";
            source += "\tBITANGENT = BITANGENT_INPUT;\n";
            source += "\tVERTEX_INDEX = float(gl_VertexIndex);\n";
            break;
        case ShaderType::Skinned:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            source += "\tUV = UV_INPUT;\n";
            source += "\tNORMAL = NORMAL_INPUT;\n";
            source += "\tTANGENT = TANGENT_INPUT;\n";
            source += "\tBITANGENT = BITANGENT_INPUT;\n";
            source += "\tVERTEX_INDEX = float(gl_VertexIndex);\n";

            for (uint8_t i = 0; i < SR_MAX_BONES_ON_VERTEX; i++) {
                source += SR_FORMAT("\tWEIGHT%i = WEIGHT%i_INPUT;\n", i, i);
            }

            break;
        case ShaderType::Canvas:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            source += "\tUV = UV_INPUT;\n";
            break;
        case ShaderType::Simple:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            break;
        case ShaderType::Skybox:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            source += "\tUV = VERTEX;\n";
            source += "\tVERTEX_INDEX = float(gl_VertexIndex);\n";
            break;
        case ShaderType::Compute:
            source += "\tGLOBAL_INVOCATION_ID = gl_GlobalInvocationID;\n";
            break;
        default:
            SRAssert(false);
            break;
    }
    source += "\t// -- codegen -- | end default var\n\n";

    /// опционально вставляем пользовательский код
    auto&& functionIt = std::find_if(parseData.functions.begin(), parseData.functions.end(), [](const SRSLFunc& func) -> bool {
        return func.name == "vertex";
    });
    if (functionIt != parseData.functions.end()) {
        source += "\t// -- codegen -- | begin user code\n\t{\n";
        source += SR_UTILS_NS::StringUtils::Tab(functionIt->code);
        source += "\t}\n\t// -- codegen -- | end user code\n\n";
    }

    /// вставляем код отвечающий за данный тип шейдера
    source += "\t// -- codegen -- | begin shader code\n";
    switch (unit.type) {
        case ShaderType::Custom:
        case ShaderType::SpatialCustom:
            break;
        case ShaderType::Simple:
        case ShaderType::Spatial:
            source += "\tgl_Position = PROJECTION_MATRIX * VIEW_MATRIX * MODEL_MATRIX * vec4(VERTEX, 1.0);\n";
            break;
        case ShaderType::Skinned:
            source += "\tgl_Position = PROJECTION_MATRIX * VIEW_MATRIX * MODEL_MATRIX * vec4(VERTEX, 1.0);\n";
            break;
        case ShaderType::Canvas:
            source += "\tgl_Position = ORTHOGONAL_MATRIX * MODEL_MATRIX * vec4(VERTEX, 1.0);\n";
            break;
        case ShaderType::Skybox:
            source += "\tgl_Position = (PROJECTION_MATRIX * VIEW_NO_TRANSLATE_MATRIX * vec4(VERTEX, 1.0)).xyww;\n";
            break;
        case ShaderType::PostProcessing:
            source += "\tgl_Position = vec4(VERTEX, 1.0);\n";
            break;
        case ShaderType::Text:
            source += "\tvec3 text_points[6] = {\n"
                      "\t\tvec3(TEXT_RECT_X, TEXT_RECT_Y, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X + TEXT_RECT_WIDTH, TEXT_RECT_Y, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X + TEXT_RECT_WIDTH, TEXT_RECT_Y + TEXT_RECT_HEIGHT, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X, TEXT_RECT_Y + TEXT_RECT_HEIGHT, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X + TEXT_RECT_WIDTH, TEXT_RECT_Y + TEXT_RECT_HEIGHT, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X, TEXT_RECT_Y, 0.0),\n"
                      "\t};\n\n";

            source += "\tvec2 text_uv[6] = {\n"
                      "\t\tvec2(0.0, 0.0),\n"
                      "\t\tvec2(1.0, 0.0),\n"
                      "\t\tvec2(1.0, 1.0),\n"
                      "\t\tvec2(0.0, 1.0),\n"
                      "\t\tvec2(1.0, 1.0),\n"
                      "\t\tvec2(0.0, 0.0),\n"
                      "\t};\n\n";

            source += "\tUV = text_uv[gl_VertexIndex];\n";
            source += "\tUV = vec2(UV.x, 1.0 - UV.y);\n";
            source += "\tgl_Position = PROJECTION_MATRIX * VIEW_MATRIX * MODEL_MATRIX * vec4(text_points[gl_VertexIndex], 1.0);\n";
            break;
        case ShaderType::TextUI:
            source += "\tvec3 text_points[6] = {\n"
                      "\t\tvec3(TEXT_RECT_X, TEXT_RECT_Y, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X + TEXT_RECT_WIDTH, TEXT_RECT_Y, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X + TEXT_RECT_WIDTH, TEXT_RECT_Y + TEXT_RECT_HEIGHT, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X, TEXT_RECT_Y + TEXT_RECT_HEIGHT, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X + TEXT_RECT_WIDTH, TEXT_RECT_Y + TEXT_RECT_HEIGHT, 0.0),\n"
                      "\t\tvec3(TEXT_RECT_X, TEXT_RECT_Y, 0.0),\n"
                      "\t};\n\n";

            source += "\tvec2 text_uv[6] = {\n"
                      "\t\tvec2(0.0, 0.0),\n"
                      "\t\tvec2(1.0, 0.0),\n"
                      "\t\tvec2(1.0, 1.0),\n"
                      "\t\tvec2(0.0, 1.0),\n"
                      "\t\tvec2(1.0, 1.0),\n"
                      "\t\tvec2(0.0, 0.0),\n"
                      "\t};\n\n";

            source += "\tUV = text_uv[gl_VertexIndex];\n";
            source += "\tUV = vec2(UV.x, UV.y);\n";
            source += "\tgl_Position = ORTHOGONAL_MATRIX * MODEL_MATRIX * vec4(text_points[gl_VertexIndex], 1.0);\n";
            break;
        case ShaderType::Line:
            source += "\tif (gl_VertexIndex == 0) { gl_Position = PROJECTION_MATRIX * VIEW_MATRIX * vec4(LINE_START_POINT, 1.0); } \n";
            source += "\tif (gl_VertexIndex == 1) { gl_Position = PROJECTION_MATRIX * VIEW_MATRIX * vec4(LINE_END_POINT, 1.0); } \n";
            break;
        default:
            SRAssert(false);
            break;
    }
    source += "\t// -- codegen -- | end shader code\n";

    source += "}\n";

    return source;
}

bool SR_GRAPH_NS::SRSL::SRSLLoader::CreateVertex(SRSLUnit &unit, SRSLParseData& parseData, const std::string& code, SR_UTILS_NS::Path&& path) {
    auto& stage = unit.stages[ShaderStage::Vertex];
    stage.path = std::move(path);

    if (!stage.path.Make(Helper::Path::Type::File)) {
        SR_ERROR("SRSLLoader::CreateVertex() : failed to create vertex path! Path: " + stage.path.ToString());
        unit.stages.erase(ShaderStage::Vertex);
        return false;
    }

    /// ----------------------------------------------------------------------------------------------------------------

    std::string source;

    source += "// [WARNING: THIS FILE WAS CREATED BY CODE GENERATION]\n\n";

    source += "#version 450\n\n";
    source += "#extension GL_ARB_separate_shader_objects : enable\n";
    source += "#extension GL_EXT_shader_atomic_float : enable\n\n";

    /// ----------------------------------------------------------------------------------------------------------------

    source += "// -- codegen -- | begin vertex locations\n";

    uint32_t location = 0;

    switch (unit.type) {

        case ShaderType::Spatial:
        case ShaderType::SpatialCustom:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 NORMAL_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 TANGENT_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANGENT_INPUT;\n", location++);
            break;
        case ShaderType::Skinned:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 NORMAL_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 TANGENT_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANGENT_INPUT;\n", location++);

            for (uint8_t i = 0; i < SR_MAX_BONES_ON_VERTEX; i++) {
                source += SR_UTILS_NS::Format("layout (location = %i) in vec2 WEIGHT%i_INPUT;\n", location++, i);
            }

            break;
        case ShaderType::Simple:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);
            break;
        case ShaderType::Canvas:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV_INPUT;\n", location++);
            break;
        case ShaderType::Custom:
        case ShaderType::PostProcessing:
        case ShaderType::Line:
        case ShaderType::Text:
        case ShaderType::TextUI:
            break;
        case ShaderType::Skybox:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);
            break;
        case ShaderType::Unknown:
        default:
            SRAssert(false);
            break;
    }

    source += "// -- codegen -- | end vertex locations\n\n";

    source += MakeUniformsCode(unit, code, parseData);

    source += code;

    /// ----------------------------------------------------------------------------------------------------------------

    return SR_UTILS_NS::FileSystem::WriteToFile(stage.path.ToString(), source);
}

std::map<uint32_t, uint32_t> Framework::Graphics::SRSL::SRSLUnit::GetUniformSizes() const {
    std::map<uint32_t, uint32_t> uniforms;

    for (const auto& [name, var] : bindings) {
        if (IsSamplerType(var.type) || !var.used) {
            continue;
        }

        uniforms[var.binding] += GetShaderVarSize(var.type);
    }

    return uniforms;
}

std::list<std::pair<std::string, SR_GRAPH_NS::SRSL::SRSLVariable>> Framework::Graphics::SRSL::SRSLUnit::GetUniformBlock() const {
    auto&& variables = std::list<std::pair<std::string, SRSLVariable>>();

    for (auto&& [name, var] : bindings) {
        if (!var.used || IsSamplerType(var.type)) {
            continue;
        }

        variables.emplace_back(std::make_pair(name, var));
    }

    std::map<ShaderVarType, uint32_t> order = {
            { ShaderVarType::Skeleton128,1 },
            { ShaderVarType::Mat4,       2 },
            { ShaderVarType::Mat3,       3 },
            { ShaderVarType::Mat2,       4 },
            { ShaderVarType::Vec4,       5 },
            { ShaderVarType::Vec3,       6 },
            { ShaderVarType::Vec2,       7 },
            { ShaderVarType::Float,      8 },
            { ShaderVarType::Int,        9 },
    };

    variables.sort([&order](const std::pair<std::string, SRSLVariable> &a, const std::pair<std::string, SRSLVariable> &b) {
        return order[a.second.type] < order[b.second.type];
        //return GetShaderVarSize(a.second.type) > GetShaderVarSize(b.second.type);
        //return GetShaderVarSize(a.second.type) < GetShaderVarSize(b.second.type);
    });

    return variables;
}

std::map<std::string, SR_GRAPH_NS::SRSL::SRSLVariable> Framework::Graphics::SRSL::SRSLUnit::GetSamplers() const {
    auto&& samplers = std::map<std::string, SR_GRAPH_NS::SRSL::SRSLVariable>();

    for (auto&& [name, var] : bindings) {
        if (!var.used || !IsSamplerType(var.type)) {
            continue;
        }

        samplers[name] = var;
    }

    return samplers;
}
