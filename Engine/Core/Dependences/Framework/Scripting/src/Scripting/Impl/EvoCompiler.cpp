//
// Created by Nikita on 11.07.2021.
//

#include <Scripting/Impl/EvoCompiler.h>

#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>
#include <FileSystem/Path.h>
#include <Xml.h>
#include <Utils/Features.h>

namespace SR_SCRIPTING_NS {
    bool EvoCompiler::Init() {
        SR_INFO("EvoCompiler::Init() : initialization of the compiler...");

        EvoScript::Tools::ESDebug::Error = [](const std::string& msg) { SR_ERROR(msg); };
        EvoScript::Tools::ESDebug::Log   = [](const std::string& msg) { SR_LOG(msg);   };
        EvoScript::Tools::ESDebug::Warn  = [](const std::string& msg) { SR_WARN(msg);  };
        EvoScript::Tools::ESDebug::Info  = [](const std::string& msg) { SR_INFO(msg);  };

        auto&& configPath = Helper::ResourceManager::Instance().GetResPath().Concat("/Configs/EvoScript.xml");

        if (configPath.Exists()) {
            auto xml = SR_XML_NS::Document::Load(configPath);
            const auto& configs = xml.Root().GetNode("Configs");
            const auto generator = GetGenerator(configs);

            if (generator.empty()) {
                SR_ERROR("EvoCompiler::Init() : failed to get cmake generator!");
                return false;
            }

            m_generator = new EvoScript::AddressTableGen();
            m_casting = new EvoScript::CastingGen(m_generator);

            m_compiler  = EvoScript::Compiler::Create(
                    generator,
                    Helper::ResourceManager::Instance().GetCachePath().Concat("Scripting")
            );

            return true;
        }
        else {
            SR_ERROR("EvoCompiler::Init() : config file not found! \n\tPath: " + configPath.ToString());
        }

        return false;
    }

    bool Framework::Scripting::EvoCompiler::Destroy()  {
        if (m_compiler) {
            m_compiler->Destroy();
            m_compiler->Free();
            m_compiler = nullptr;
        }

        if (m_generator) {
            delete m_generator;
            m_generator = nullptr;
        }

        return true;
    }

    std::string Framework::Scripting::EvoCompiler::GetGenerator(const Framework::Helper::Xml::Node &config) const {
        if (!Helper::Features::Instance().Enabled("EvoCompiler", true)) {
            SR_INFO("EvoCompiler::GetGenerator() : cmake generator is disabled.");
            return "Disabled";
        }

        auto generator = config.GetNode("Generator").GetAttribute("Value").ToString();

        if (generator.empty()) {
            SR_ERROR("EvoCompiler::Init() : invalid generator!");
            return std::string();
        }

    #ifdef SR_MINGW
        const auto warnMsg = "EvoCompiler::Init() : The script compiler and the engine are different! This can lead to unpredictable consequences!";

        if (generator.find("Visual Studio") != std::string::npos) {
            SR_WARN(warnMsg);
        }
    #endif

        SR_INFO("EvoCompiler::GetGenerator() : use \"" + generator + "\" generator...");

        return std::move(generator);
    }
}
