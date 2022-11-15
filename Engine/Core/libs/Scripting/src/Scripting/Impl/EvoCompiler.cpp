//
// Created by Nikita on 11.07.2021.
//

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Platform/Platform.h>
#include <Utils/Xml.h>
#include <Utils/Common/Features.h>

#include <Scripting/Impl/EvoCompiler.h>

namespace SR_SCRIPTING_NS {
    EvoCompiler::EvoCompiler(std::string cachePath)
        : EvoScript::Compiler(std::move(cachePath))
    { }

    EvoCompiler::~EvoCompiler() {
        if (m_generator) {
            delete m_generator;
            m_generator = nullptr;
        }

        if (m_casting) {
            delete m_casting;
            m_casting = nullptr;
        }
    }

    bool EvoCompiler::Init() {
        SR_INFO("EvoCompiler::Init() : initialization of the compiler...");

        auto&& configPath = Helper::ResourceManager::Instance().GetResPath().Concat("Engine/Configs/EvoScript.xml");

        if (configPath.Exists()) {
            auto xml = SR_XML_NS::Document::Load(configPath);
            const auto& configs = xml.Root().GetNode("Configs");
            const auto generator = GetGeneratorName(configs);

            if (generator.empty()) {
                SR_ERROR("EvoCompiler::Init() : failed to get cmake generator!");
                return false;
            }

            SetGenerator(generator);

            m_generator = new EvoScript::AddressTableGen();
            m_casting = new EvoScript::CastingGen(m_generator);

            return true;
        }
        else {
            SR_ERROR("EvoCompiler::Init() : config file not found! \n\tPath: " + configPath.ToString());
        }

        return false;
    }

    std::string Framework::Scripting::EvoCompiler::GetGeneratorName(const Framework::Helper::Xml::Node &config) const {
        if (!Helper::Features::Instance().Enabled("EvoCompiler", true)) {
            SR_INFO("EvoCompiler::GetGenerator() : cmake generator is disabled.");
            return "Disabled";
        }

        auto&& generator = config.GetNode("Generator").GetAttribute("Value").ToString();

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

    GlobalEvoCompiler::GlobalEvoCompiler()
        : SR_SCRIPTING_NS::EvoCompiler(SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Scripts"))
    {
        Init();
    }
}
