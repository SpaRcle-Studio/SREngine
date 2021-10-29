//
// Created by Monika on 31.08.2021.
//

#ifndef GAMEENGINE_SHADERGENERATOR_H
#define GAMEENGINE_SHADERGENERATOR_H

#include <Render/Shader.h>
#include <Utils/str_switch.h>
#include <optional>
#include <string>

namespace Framework::Graphics::Codegen {
    struct ShaderStruct {
        std::string m_name;
        /// 1 - type, 2 - name
        std::map<std::string, std::string> m_types;

        static ShaderStruct Parse(const std::vector<std::string>& lines) {
            return {};
        }
    };

    struct Uniform {
        uint32_t    m_binding;
        std::string m_name;
        // 1 - type, 2 - name
        std::map<std::string, std::string> m_types;
    };

    struct Attribute {
        uint32_t    m_layout;
        std::string m_type;
        std::string m_name;

        [[nodiscard]] std::string ToCode() const {
            return Vertices::format("layout (location {}) in {} {};", m_layout, m_type.c_str(), m_name.c_str());
        }
    };

    struct Layout {
        uint32_t m_location;
        std::string m_name;
        std::string m_type;
        std::string m_IO;

        [[nodiscard]] std::string ToCode() const {
            return Vertices::format("layout (location = {}) {} {} {};", m_location, m_IO.c_str(), m_type.c_str(), m_name.c_str());
        }
    };

    struct SegmentIO {
        std::string m_type;
        std::string m_name;
        std::string m_default;
    };

    struct CodeSegment {
        typedef std::pair<std::string, bool> Define;

        uint32_t m_priority;
        SegmentIO m_IO;
        std::string m_code;
        std::vector<Define> m_defines;

        [[nodiscard]] bool CheckConditions(const std::vector<std::string>& defines) const;
    };

    struct Module {
        std::string               m_name;
        std::string               m_type;
        std::vector<Attribute>    m_attributes;
        std::vector<ShaderStruct> m_structs;
        std::vector<Uniform>      m_uniforms;
        std::vector<Layout>       m_layouts; // shader I/O and textures layouts
        std::vector<std::string>  m_extensions;
        std::vector<CodeSegment>  m_segments;

        bool Link(const std::vector<std::string>& defines);

        [[nodiscard]] std::string ToCode() const {
            std::string code;
            code.append("#version 450");
            code.append("\n\n");

            for (const auto& attrib : m_attributes)
                code.append(attrib.ToCode()).append("\n");

            code.append("\n");

            for (const auto& layout : m_layouts)
                code.append(layout.ToCode()).append("\n");

            code.append("\n");
            code.append("void main() {\n");
            code.append("\n");
            code.append("}");

            return code;
        }

        bool Merge(const Module& module);
    };

    class ShaderGenerator {
    private:
        ShaderGenerator()  = default;
        ~ShaderGenerator() = default;
    public:
        static ShaderGenerator* Instance() {
            static auto instance = new ShaderGenerator();
            return instance;
        }
    private:
        std::vector<Module> LoadModules(const std::string& path);
        std::optional<Module> Parse(const std::string& path);
        std::optional<Module> LinkModules(
                const std::vector<Module>& modules,
                const std::string& shaderType,
                const std::vector<std::string>& defines);
    public:
        bool Generate(const std::string& name, const std::string& dist, ShaderFlags flags);
    };
}

#endif //GAMEENGINE_SHADERGENERATOR_H
