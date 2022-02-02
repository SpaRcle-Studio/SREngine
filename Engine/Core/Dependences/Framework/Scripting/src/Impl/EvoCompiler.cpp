//
// Created by Nikita on 11.07.2021.
//

#include "Impl/EvoCompiler.h"

#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>
#include <FileSystem/Path.h>
#include <Xml.h>
#include <Utils/Features.h>

bool Framework::Scripting::EvoCompiler::Init() {
    Helper::Debug::Info("EvoCompiler::Init() : initialization of the compiler...");

    EvoScript::Tools::ESDebug::Error = [](const std::string& msg) { Helper::Debug::Error(msg); };
    EvoScript::Tools::ESDebug::Log   = [](const std::string& msg) { Helper::Debug::Log(msg);   };
    EvoScript::Tools::ESDebug::Warn  = [](const std::string& msg) { Helper::Debug::Warn(msg);  };
    EvoScript::Tools::ESDebug::Info  = [](const std::string& msg) { Helper::Debug::Info(msg);  };

    const auto configPath = Helper::ResourceManager::Instance().GetResPath().Concat("/Configs/EvoScript.xml");

    if (configPath.Exists()) {
        auto xml = SR_XML_NS::Document::Load(configPath);
        const auto& configs = xml.Root().GetNode("Configs");
        const auto generator = GetGenerator(configs);

        if (generator.empty()) {
            Helper::Debug::Error("EvoCompiler::Init() : failed to get cmake generator!");
            return false;
        }

        this->m_generator = new EvoScript::AddressTableGen();
        this->m_casting = new EvoScript::CastingGen(m_generator);

        this->m_compiler  = EvoScript::Compiler::Create(
                generator,
                Helper::ResourceManager::Instance().GetCachePath().Concat("Scripting")
        );

        return true;
    }
    else
        Helper::Debug::Error("EvoCompiler::Init() : config file not found! \n\tPath: " + configPath.ToString());

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
        Helper::Debug::Info("EvoCompiler::GetGenerator() : cmake generator is disabled.");
        return "Disabled";
    }

    const auto warnMsg = "EvoCompiler::Init() : The script compiler and the engine are different! This can lead to unpredictable consequences!";
    auto generator = config.GetNode("Generator").GetAttribute("Value").ToString();

    if (generator.empty()) {
        Helper::Debug::Error("EvoCompiler::Init() : invalid generator!");
        return std::string();
    }

#ifdef __MINGW64__
    if (generator.find("Visual Studio") != std::string::npos)
            Helper::Debug::Warn(warnMsg);
#endif

    Helper::Debug::Info("EvoCompiler::GetGenerator() : use \"" + generator + "\" generator...");

    return std::move(generator);
}
