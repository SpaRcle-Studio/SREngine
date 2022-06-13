//
// Created by Monika on 09.04.2022.
//

#include <Loaders/SRSL.h>

const std::unordered_map<std::string, Framework::Graphics::ShaderVarType> SR_GRAPH_NS::SRSL::SRSLLoader::STANDARD_VARIABLES = {
        { "TIME", ShaderVarType::Float },
        { "MODEL_MATRIX", ShaderVarType::Mat4 },
        { "VIEW_MATRIX", ShaderVarType::Mat4 },
        { "PROJECTION_MATRIX", ShaderVarType::Mat4 },
        { "VIEW_NO_TRANSLATE_MATRIX", ShaderVarType::Mat4 },
        { "SKYBOX_DIFFUSE", ShaderVarType::SamplerCube },
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

std::optional<SR_GRAPH_NS::SRSL::SRSLUnit> SR_GRAPH_NS::SRSL::SRSLLoader::Load(std::string path) {
    SR_SHADER_LOG("SRSLLoader::Load() : loading SpaRcle shader... \n\tPath: " + path);

    if (const auto& pos = path.find(".srsl"); pos != std::string::npos) {
        path.resize(path.size() - (path.size() - pos));
    }

    auto&& resManager = SR_UTILS_NS::ResourceManager::Instance();
    auto&& cache = resManager.GetCachePath().Concat("Shaders/SRSL");
    auto&& shader = resManager.GetShadersPath().Concat(path).ConcatExt(".srsl");

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
            const std::string operators = "!~`@#$%^&*()-=+:'\"|\\/.,?^;<> \t\n";

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
            unit.type = StringToEnumShaderType(args[1]);
        }
        else if (args[0] == "PolygonMode") {
            unit.createInfo.polygonMode = StringToEnumPolygonMode(args[1]);
        }
        else if (args[0] == "CullMode") {
            unit.createInfo.cullMode = StringToEnumCullMode(args[1]);
        }
        else if (args[0] == "DepthCompare") {
            unit.createInfo.depthCompare = StringToEnumDepthCompare(args[1]);
        }
        else if (args[0] == "PrimitiveTopology") {
            unit.createInfo.primitiveTopology = StringToEnumPrimitiveTopology(args[1]);
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
        for (auto&& [name, var] : uniforms) {
            var.binding = +parseData.lastBinding;
            unit.bindings[name] = var;
        }

        ++parseData.lastBinding;
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

        source += SR_UTILS_NS::Format("layout (binding = %i) uniform %s %s;",
                unit.bindings[name].binding,
                ShaderVarTypeToString(var.type).c_str(),
                name.c_str()
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
        source += SR_UTILS_NS::Format("layout (binding = %i) uniform BLOCK {\n", uniforms.begin()->second.binding);

        for (auto&& [name, var] : uniforms) {
            source += SR_UTILS_NS::Format("\t%s %s;", ShaderVarTypeToString(var.type).c_str(), name.c_str());

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

bool SR_GRAPH_NS::SRSL::SRSLLoader::CreateFragment(SRSLUnit &unit, SRSLParseData &parseData, const std::string& code, Path &&path) {
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
        case ShaderType::Simple:
        case ShaderType::Skybox:
        case ShaderType::PostProcessing: {
            for (auto&& [name, var] : GetColorIndices(code)) {
                if (!var.used) {
                    continue;
                }

                source += SR_UTILS_NS::Format("layout (location = %i) out %s %s;\n",
                        var.binding, ShaderVarTypeToString(var.type).c_str(), name.c_str()
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
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANBENT;\n", location++);
            source += "vec4 COLOR;";
            break;
        case ShaderType::Simple:
        case ShaderType::Skybox:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 UV;\n", location++);
            source += "vec4 COLOR;";
            break;
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
        case ShaderType::Simple:
        case ShaderType::Skybox:
            source += "\tCOLOR_INDEX_0 = COLOR;\n";
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
        case ShaderType::Custom:
            break;
        case ShaderType::SpatialCustom:
        case ShaderType::Spatial:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 NORMAL;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 TANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 BITANBENT;\n", location++);
            source += "int VERTEX_INDEX;";
            break;
        case ShaderType::PostProcessing:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            source += "int VERTEX_INDEX;";
            break;
        case ShaderType::Simple:
        case ShaderType::Skybox:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 UV;\n", location++);
            source += "int VERTEX_INDEX;";
            break;
        default:
            SRAssert(false);
            break;
    }
    source += "// -- codegen -- | end declaration default vars\n\n";

    source += SRSL::GenerateFunctions(parseData.functions, "vertex");

    source += "void main() {\n";

    /// объявляем все дефолтные переменные
    source += "\t// -- codegen -- | begin default vars\n";
    switch (unit.type) {
        case ShaderType::Custom:
        case ShaderType::PostProcessing:
            source += "\tVERTEX_INDEX = gl_VertexIndex;\n";
            break;
        case ShaderType::SpatialCustom:
        case ShaderType::Spatial:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            source += "\tUV = UV_INPUT;\n";
            source += "\tNORMAL = NORMAL_INPUT;\n";
            source += "\tTANGENT = TANGENT_INPUT;\n";
            source += "\tBITANBENT = BITANBENT_INPUT;\n";
            source += "\tVERTEX_INDEX = gl_VertexIndex;\n";
            break;
        case ShaderType::Simple:
        case ShaderType::Skybox:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            source += "\tUV = VERTEX;\n";
            source += "\tVERTEX_INDEX = gl_VertexIndex;\n";
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
        case ShaderType::Skybox:
            source += "\tgl_Position = (PROJECTION_MATRIX * VIEW_NO_TRANSLATE_MATRIX * vec4(VERTEX, 1.0)).xyww;\n";
            break;
        case ShaderType::PostProcessing:
            source += "\tgl_Position = vec4(VERTEX, 1.0);\n";
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
        case ShaderType::TransparentSpatial:
        case ShaderType::Spatial:
        case ShaderType::SpatialCustom:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 NORMAL_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 TANGENT_INPUT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANBENT_INPUT;\n", location++);
            break;
        case ShaderType::Custom:
        case ShaderType::PostProcessing:
            break;
        case ShaderType::Simple:
        case ShaderType::Skybox:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);
            break;
        case ShaderType::Animation:
        case ShaderType::Canvas:
        case ShaderType::Particles:
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

    variables.sort([](const std::pair<std::string, SRSLVariable> &a, const std::pair<std::string, SRSLVariable> &b) {
        return GetShaderVarSize(a.second.type) > GetShaderVarSize(b.second.type);
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
