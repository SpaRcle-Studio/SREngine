//
// Created by Monika on 31.08.2021.
//

#include <Render/ShaderGenerator.h>
#include <ResourceManager/ResourceManager.h>
#include <Utils/VectorUtils.h>
#include <Xml.h>

bool Framework::Graphics::Codegen::ShaderGenerator::Generate(
        const std::string &name,
        const std::string &dist,
        Framework::Graphics::ShaderFlags flags)
{
    std::string modulesFolder = Framework::Helper::ResourceManager::GetResourcesFolder() + "/Shaders/Modules/" + name + "/";

    bool lighting = false;
    auto defines  = std::vector<std::string>();
    auto modules  = std::vector<Module>();

    if ((flags & Shader::Flags::GBuffer) && (flags & Shader::Flags::ForwardLight)) {
        Helper::Debug::Error("ShaderGenerator::Generate() : incorrect lighting flags!");
        return false;
    } else if ((flags & Shader::Flags::GBuffer) || (flags & Shader::Flags::ForwardLight)) {
        lighting = true;
        if (flags & Shader::Flags::GBuffer)
            defines.emplace_back("GBuffer");
        else
            defines.emplace_back("ForwardLight");
    }

    if (flags & Shader::Flags::Diffuse)
        modules = Helper::VectorUtils::Combine(modules, LoadModules(modulesFolder + "diffuse"));
    if (flags & Shader::Flags::Normal)
        modules = Helper::VectorUtils::Combine(modules, LoadModules(modulesFolder + "normal"));
    if (flags & Shader::Flags::Specular)
        modules = Helper::VectorUtils::Combine(modules, LoadModules(modulesFolder + "specular"));
    if (flags & Shader::Flags::Glossiness)
        modules = Helper::VectorUtils::Combine(modules, LoadModules(modulesFolder + "glossiness"));

    if (auto fragment_module = LinkModules(modules, "fragment", defines); fragment_module.has_value()) {
        std::cout << fragment_module.value().ToCode() << std::endl;
    }

    return true;
}

std::optional<Framework::Graphics::Codegen::Module> Framework::Graphics::Codegen::ShaderGenerator::Parse(const std::string &path) {
    auto module = Codegen::Module();

    if (auto xml = Helper::Xml::Document::Load(path); xml.Valid()) {
        if (auto moduleXml = xml.Root().GetNode("module"); moduleXml.Valid()) {
            module.m_name = moduleXml.GetAttribute("name").ToString();
            module.m_type = moduleXml.GetAttribute("type").ToString();

            if (auto extensions = moduleXml.GetNode("extensions"); extensions.Valid()) {
                for (const auto& ext : extensions.GetNodes()) {
                    module.m_extensions.emplace_back(ext.Name());
                }
            }
            if (auto attributes = moduleXml.GetNode("attributes"); attributes.Valid()) {
                for (const auto& attrib : attributes.GetNodes("attribute")) {
                    module.m_attributes.emplace_back(Attribute {
                        .m_layout = (uint32_t)attrib.GetAttribute("layout").ToInt(),
                        .m_type   = attrib.GetAttribute("type").ToString(),
                        .m_name   = attrib.GetAttribute("name").ToString()
                    });
                }
            }
            if (auto uniforms = moduleXml.GetNode("uniforms"); uniforms.Valid()) {
                for (const auto& uniform : uniforms.GetNodes("uniform")) {
                    auto types = std::map<std::string, std::string>();
                    for (const auto& type : uniform.GetNodes("type"))
                        types.insert(std::pair(
                                type.GetAttribute("name").ToString(),
                                type.GetAttribute("var").ToString()));

                    module.m_uniforms.emplace_back(Uniform {
                            .m_binding = (uint32_t)uniform.GetAttribute("binding").ToInt(),
                            .m_name    = uniform.GetAttribute("name").ToString(),
                            .m_types   = types
                    });
                }
            }
            if (auto layouts = moduleXml.GetNode("layouts"); layouts.Valid()) {
                for (const auto& layout : layouts.GetNodes()) {
                    module.m_layouts.emplace_back(Layout {
                            .m_location = (uint32_t)layout.GetAttribute("location").ToInt(),
                            .m_name = layout.Name(),
                            .m_type = layout.GetAttribute("type").ToString(),
                            .m_IO   = layout.GetAttribute("IO").ToString()
                    });
                }
            }
        }
    }

    return module;
}

std::vector<Framework::Graphics::Codegen::Module> Framework::Graphics::Codegen::ShaderGenerator::LoadModules(const std::string &path) {
    std::string fixedPath = Helper::StringUtils::MakePath(path, false);

    auto modules = std::vector<Module>();

    auto add_module = [&modules, this](const std::string& fullPath) -> bool {
        if (auto module = Parse(fullPath); (module.has_value() && Helper::Xml::Document::GetLastError() == 0)) {
            modules.emplace_back(module.value());
            return true;
        }
        else {
            Helper::Debug::Error("ShaderGenerator::LoadModules() : failed to parse module! \n\tPath: " + fullPath);
            return false;
        }
    };

    if (auto fullPath = fixedPath + ".vert.xml"; Helper::FileSystem::FileExists(fullPath))
        if (!add_module(fullPath))
            return {};

    if (auto fullPath = fixedPath + ".frag.xml"; Helper::FileSystem::FileExists(fullPath))
        if (!add_module(fullPath))
            return {};

    return modules;
}

std::optional<Framework::Graphics::Codegen::Module> Framework::Graphics::Codegen::ShaderGenerator::LinkModules(
        const std::vector<Module> &modules,
        const std::string& shaderType,
        const std::vector<std::string>& defines)
{
    if (modules.empty()) {
        Helper::Debug::Error("ShaderGenerator::LinkModules() : empty modules!");
        return std::optional<Module>();
    }

    Module merged = {};

    for (const Module& module : modules) {
        if (module.m_type != shaderType)
            continue;

        if (!merged.Merge(module)) {
            Helper::Debug::Error("ShaderGenerator::LinkModules() : failed to merge two modules!");
            return std::optional<Module>();
        }
    }

    if (!merged.Link(defines)) {
        Helper::Debug::Error("ShaderGenerator::LinkModules() : failed to link modules!");
        return std::optional<Module>();
    }

    return merged;
}

bool Framework::Graphics::Codegen::Module::Merge(const Framework::Graphics::Codegen::Module &module) {
    for (const auto& ext1 : module.m_extensions) {
        for (const auto &ext2 : m_extensions) {
            if (ext1 == ext2)
                goto exit;
        }
        m_extensions.emplace_back(ext1);
        exit:
        continue;
    }

    for (const auto& attrib1 : module.m_attributes) {
        for (const auto& attrib2 : m_attributes) {
            if (attrib1.m_name == attrib2.m_name || attrib1.m_layout == attrib2.m_layout) {
                Helper::Debug::Error("Codegen::Module::Merge() : conflict attributes!");
                return false;
            }
        }
        m_attributes.emplace_back(attrib1);
    }

    for (const auto& layout1 : module.m_layouts) {
        for (const auto& layout2 : m_layouts) {
            if (layout1.m_name == layout2.m_name || layout1.m_location == layout2.m_location) {
                Helper::Debug::Error("Codegen::Module::Merge() : conflict layouts!");
                return false;
            }
        }
        m_layouts.emplace_back(layout1);
    }

    for (const auto& segment1 : module.m_segments) {
        for (const auto& segment2 : m_segments) {
            if (segment1.m_priority == segment2.m_priority) {
                Helper::Debug::Error("Codegen::Module::Merge() : conflict segments priority!");
                return false;
            }
        }
        m_segments.emplace_back(segment1);
    }

    return true;
}

bool Framework::Graphics::Codegen::Module::Link(const std::vector<std::string>& defines) {
    for (const auto& segment : m_segments) {
        if (segment.CheckConditions(defines)) {

        }
    }

    return true;
}

bool Framework::Graphics::Codegen::CodeSegment::CheckConditions(const std::vector<std::string>& defines) const {
    for (const auto& define1 : m_defines) {
        for (const auto& define2 : defines) {
            if (define1.first == define2) {
                if (define1.second)
                    break;
                else
                    return false;
            }
        }
        return false;
    }
    return true;
}
