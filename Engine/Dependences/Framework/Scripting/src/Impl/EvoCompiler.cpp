//
// Created by Nikita on 11.07.2021.
//

#include "Impl/EvoCompiler.h"
#include <ResourceManager/ResourceManager.h>

bool Framework::Scripting::EvoCompiler::Init() {
    Helper::Debug::Info("EvoCompiler::Init() : initialization of the compiler...");

    EvoScript::Tools::ESDebug::Error = [](const std::string& msg) { Helper::Debug::Error(msg); };
    EvoScript::Tools::ESDebug::Log   = [](const std::string& msg) { Helper::Debug::Log(msg);   };
    EvoScript::Tools::ESDebug::Warn  = [](const std::string& msg) { Helper::Debug::Warn(msg);  };
    EvoScript::Tools::ESDebug::Info  = [](const std::string& msg) { Helper::Debug::Info(msg);  };

    this->m_pathToScripts = Framework::Helper::ResourceManager::GetResourcesFolder() + "/Scripts/";

    std::string config = Helper::ResourceManager::GetResourcesFolder() + "/Configs/EvoScriptGenerator.config";
    std::ifstream ifs(config);
    if (!ifs.is_open()) {
        Helper::Debug::Error("EvoCompiler::Init() : failed to read config file! \n\tPath: " + config);
        return false;
    } else {
        std::string generator((std::istreambuf_iterator<char>(ifs)), (std::istreambuf_iterator<char>()));
        this->m_compiler  = EvoScript::Compiler::Create(generator, Helper::ResourceManager::GetResourcesFolder() + "/Cache");
        this->m_generator = new EvoScript::AddressTableGen();
    }

    return true;
}
