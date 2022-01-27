//
// Created by Nikita on 11.07.2021.
//

#include "Impl/EvoCompiler.h"

#include <ResourceManager/ResourceManager.h>
#include <FileSystem/FileSystem.h>
#include <FileSystem/Path.h>
#include <Xml.h>

bool Framework::Scripting::EvoCompiler::Init() {
    Helper::Debug::Info("EvoCompiler::Init() : initialization of the compiler...");

    EvoScript::Tools::ESDebug::Error = [](const std::string& msg) { Helper::Debug::Error(msg); };
    EvoScript::Tools::ESDebug::Log   = [](const std::string& msg) { Helper::Debug::Log(msg);   };
    EvoScript::Tools::ESDebug::Warn  = [](const std::string& msg) { Helper::Debug::Warn(msg);  };
    EvoScript::Tools::ESDebug::Info  = [](const std::string& msg) { Helper::Debug::Info(msg);  };

    const auto configPath = Helper::ResourceManager::Instance().GetResPath().Concat("/Configs/EvoScript.xml");
    const auto warnMsg = "EvoCompiler::Init() : The script compiler and the engine are different! This can lead to unpredictable consequences!";

    if (configPath.Exists()) {
        auto xml = SR_XML_NS::Document::Load(configPath);
        const auto generator = xml.Root().GetNode("Configs").GetNode("Generator").GetAttribute("Value").ToString();

        if (generator.empty()) {
            Helper::Debug::Error("EvoCompiler::Init() : invalid generator!");
            return false;
        }

    #ifdef __MINGW64__
        if (generator.find("Visual Studio") != std::string::npos)
            Helper::Debug::Warn(warnMsg);
    #endif

        Helper::Debug::Info("EvoCompiler::Init() : use \"" + generator + "\" generator...");

        this->m_generator = new EvoScript::AddressTableGen();
        this->m_casting = new EvoScript::CastingGen(m_generator);

        this->m_compiler  = EvoScript::Compiler::Create(
                generator,
                Helper::ResourceManager::Instance().GetResPath().Concat("Cache/Scripting")
        );

        return true;
    }
    else
        Helper::Debug::Error("EvoCompiler::Init() : config file not found! \n\tPath: " + configPath.ToString());

    return false;
}
