//
// Created by Monika on 09.04.2022.
//

#include <Loaders/SRSL.h>

const std::unordered_set<std::string> SR_GRAPH_NS::SRSL::SRSLLoader::STANDARD_VARIABLES = {
    "float TIME", "mat4 MODEL_MATRIX", "mat4 VIEW_MATRIX", "mat4 PROJECTION_MATRIX"
};

std::optional<SR_GRAPH_NS::SRSL::SRSLUnit> SR_GRAPH_NS::SRSL::SRSLLoader::Load(std::string path) {
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

    if (!CreateVertex(unit, parseData.value(), cache.Concat(path).Concat("shader.vert"))) {
        SR_ERROR("SRSLLoader::Load() : failed to create vertex shader! \n\tPath: " + shader.ToString());
        return {};
    }

    if (!CreateFragment(unit, parseData.value(), cache.Concat(path).Concat("shader.frag"))) {
        SR_ERROR("SRSLLoader::Load() : failed to create fragment shader! \n\tPath: " + shader.ToString());
        return {};
    }

    return unit;
}

SR_GRAPH_NS::SRSL::SRSLVariables SR_GRAPH_NS::SRSL::SRSLLoader::RefAnalyzer(const std::string& code, const SRSLVars& allVars) {
    SRSLVariables used;

    const auto&& isUsed = [&code](const std::string& var) -> bool {
        if (auto&& pos = code.find(var); pos != std::string::npos) {
            const std::string operators = "!~`@#$%^&*()-=+:'\"|\\/.,?^;<> \t\n";

            /// check left side
            if (pos > 0 && operators.find(code[pos - 1]) == std::string::npos) {
                return false;
            }

            /// check right side
            if ((pos + var.size() < code.size()) && operators.find(code[pos + var.size()]) == std::string::npos) {
                return false;
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

        used[args[2]] = SRSLVariable { isUsed(args[2]), true, args[1] };
    }

    for (const auto& var : STANDARD_VARIABLES) {
        auto&& args = SR_UTILS_NS::StringUtils::Split(var, " ");

        /// { type, name }
        if (args.size() != 2) {
            continue;
        }

        used[args[1]] = SRSLVariable { isUsed(args[1]), false, args[0] };
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

    switch (unit.type) {
        case ShaderType::TransparentSpatial:
        case ShaderType::Spatial:
            unit.attributes = SRSL_VERTEX_ATTRIBUTE_POSITION
                | SRSL_VERTEX_ATTRIBUTE_UV
                | SRSL_VERTEX_ATTRIBUTE_NORMAL
                | SRSL_VERTEX_ATTRIBUTE_TANGENT
                | SRSL_VERTEX_ATTRIBUTE_BITANGENT;

            break;
        case ShaderType::Animation:
        case ShaderType::PostProcess:
        case ShaderType::Skybox:
        case ShaderType::Canvas:
        case ShaderType::Particles:
        case ShaderType::Unknown:
            SRAssert(false);
            break;
    }

    return true;
}

std::string SR_GRAPH_NS::SRSL::SRSLLoader::MakeUniformsCode(SRSLUnit& unit, const std::string &code, SRSLParseData &parseData) {
    SRSLVariables uniforms;
    SRSLVariables samplers;

    for (auto&& [name, var] : RefAnalyzer(code, parseData.vars)) {
        if (var.type == "sampler2D") {
            samplers[name] = var;
        }
        else
            uniforms[name] = var;
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

        source += SR_UTILS_NS::Format("layout (binding = %i) uniform %s %s;", unit.bindings[name].binding, var.type.c_str(), name.c_str());

        if (var.show) {
            source += " // public\n";
        }
        else
            source += " // hidden\n";
    }

    const bool haveUsed = [=]() -> bool {
        for (auto&& [name, var] : uniforms) {
            if (var.used)
                return true;
        }
        return false;
    }();

    if (haveUsed && !uniforms.empty()) {
        if (unit.bindings.count(uniforms.begin()->first) == 0) {
            for (auto&& [name, var] : uniforms) {
                var.binding = parseData.lastBinding;
                unit.bindings[name] = var;
            }

            parseData.lastBinding++;
        }

        auto&& binding = unit.bindings.at(uniforms.begin()->first).binding;

        source += SR_UTILS_NS::Format("layout (binding = %i) uniform BLOCK {\n", binding);

        for (auto&& [name, var] : uniforms) {
            source += SR_UTILS_NS::Format("\t%s %s;", var.type.c_str(), name.c_str());

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

bool SR_GRAPH_NS::SRSL::SRSLLoader::CreateFragment(SRSLUnit &unit, SRSLParseData &parseData, Path &&path) {
    auto& stage = unit.stages[ShaderStage::Fragment];
    stage.path = std::move(path);

    if (!stage.path.Make(Helper::Path::Type::File)) {
        SR_ERROR("SRSLLoader::CreateFragment() : failed to create fragment path! Path: " + stage.path.ToString());
        unit.stages.erase(ShaderStage::Fragment);
        return false;
    }

    const std::string fragCode = MakeFragmentCode(unit, parseData);

    /// ----------------------------------------------------------------------------------------------------------------

    std::string source;

    source += "// [WARNING: THIS FILE WAS CREATED BY CODE GENERATION]\n\n";

    source += "#version 450\n";
    source += "#extension GL_ARB_separate_shader_objects : enable\n\n";

    source += "layout (location = 0) out vec4 OUT_COLOR;\n\n";

    source += MakeUniformsCode(unit, fragCode, parseData);

    source += fragCode;

    /// ----------------------------------------------------------------------------------------------------------------

    return SR_UTILS_NS::FileSystem::WriteToFile(stage.path.ToString(), source);
}

std::string SR_GRAPH_NS::SRSL::SRSLLoader::MakeFragmentCode(const SRSLUnit &unit, const SRSLParseData &parseData) {
    std::string source;

    source += "// -- codegen -- | begin declaration default vars\n";
    uint32_t location = 0;
    switch (unit.type) {
        case ShaderType::Spatial:
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 NORMAL;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 TANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANBENT;\n", location++);
            source += "vec4 COLOR;\n";
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
        case ShaderType::Spatial:
            source += "\tOUT_COLOR = COLOR;\n";
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
        case ShaderType::Spatial:
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 VERTEX;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec2 UV;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 NORMAL;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 TANGENT;\n", location++);
            source += SR_UTILS_NS::Format("layout (location = %i) out vec3 BITANBENT;\n", location++);
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
        case ShaderType::Spatial:
            source += "\tVERTEX = VERTEX_INPUT;\n";
            source += "\tUV = UV_INPUT;\n";
            source += "\tNORMAL = NORMAL_INPUT;\n";
            source += "\tTANGENT = TANGENT_INPUT;\n";
            source += "\tBITANBENT = BITANBENT_INPUT;\n";
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
        case ShaderType::Spatial:
            source += "\tgl_Position = PROJECTION_MATRIX * VIEW_MATRIX * MODEL_MATRIX * vec4(VERTEX, 1.0);\n";
            break;
        default:
            SRAssert(false);
            break;
    }
    source += "\t// -- codegen -- | end shader code\n";

    source += "}\n";

    return source;
}

bool SR_GRAPH_NS::SRSL::SRSLLoader::CreateVertex(SRSLUnit &unit, SRSLParseData& parseData, SR_UTILS_NS::Path&& path) {
    auto& stage = unit.stages[ShaderStage::Vertex];
    stage.path = std::move(path);

    if (!stage.path.Make(Helper::Path::Type::File)) {
        SR_ERROR("SRSLLoader::CreateVertex() : failed to create vertex path! Path: " + stage.path.ToString());
        unit.stages.erase(ShaderStage::Vertex);
        return false;
    }

    const auto&& vertexCode = MakeVertexCode(unit, parseData);

    /// ----------------------------------------------------------------------------------------------------------------

    std::string source;

    source += "// [WARNING: THIS FILE WAS CREATED BY CODE GENERATION]\n\n";

    source += "#version 450\n";
    source += "#extension GL_ARB_separate_shader_objects : enable\n\n";

    /// ----------------------------------------------------------------------------------------------------------------

    source += "// -- codegen -- | begin vertex locations\n";

    uint32_t location = 0;
    if (unit.attributes & SRSL_VERTEX_ATTRIBUTE_POSITION)
        source += SR_UTILS_NS::Format("layout (location = %i) in vec3 VERTEX_INPUT;\n", location++);

    if (unit.attributes & SRSL_VERTEX_ATTRIBUTE_UV)
        source += SR_UTILS_NS::Format("layout (location = %i) in vec2 UV_INPUT;\n", location++);

    if (unit.attributes & SRSL_VERTEX_ATTRIBUTE_NORMAL)
        source += SR_UTILS_NS::Format("layout (location = %i) in vec3 NORMAL_INPUT;\n", location++);

    if (unit.attributes & SRSL_VERTEX_ATTRIBUTE_TANGENT)
        source += SR_UTILS_NS::Format("layout (location = %i) in vec3 TANGENT_INPUT;\n", location++);

    if (unit.attributes & SRSL_VERTEX_ATTRIBUTE_BITANGENT)
        source += SR_UTILS_NS::Format("layout (location = %i) in vec3 BITANBENT_INPUT;\n", location++);

    source += "// -- codegen -- | end vertex locations\n\n";

    source += MakeUniformsCode(unit, vertexCode, parseData);

    source += vertexCode;

    /// ----------------------------------------------------------------------------------------------------------------

    return SR_UTILS_NS::FileSystem::WriteToFile(stage.path.ToString(), source);
}

std::map<uint32_t, uint32_t> Framework::Graphics::SRSL::SRSLUnit::GetUniformSizes() const {
    std::map<uint32_t, uint32_t> uniforms;

    const std::unordered_set<std::string> sampler = {
            "sampler1D",
            "sampler2D",
            "sampler3D",
            "samplerCube",
            "sampler1DShadow",
            "sampler2DShadow",
    };

    const std::unordered_map<std::string, uint32_t> sizes = {
            { "float", 4         },
            { "int",   4         },
            { "bool",  4         },
            { "vec2",  4 * 2     },
            { "ivec2", 4 * 2     },
            { "vec3",  4 * 3     },
            { "ivec3", 4 * 3     },
            { "vec4",  4 * 4     },
            { "ivec4", 4 * 4     },
            { "mat2",  4 * 2 * 2 },
            { "mat3",  4 * 3 * 3 },
            { "mat4",  4 * 4 * 4 },
    };

    for (const auto& [name, var] : bindings) {
        if (sampler.count(var.type) == 1) {
            continue;
        }

        if (sizes.count(var.type) == 0) {
            SRAssert2(false, "Unknown uniform type!");
            return {};
        }

        uniforms[var.binding] += sizes.at(var.type);
    }

    return uniforms;
}
