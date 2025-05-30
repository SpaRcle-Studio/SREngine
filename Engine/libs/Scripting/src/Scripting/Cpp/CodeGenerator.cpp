//
// Created by Monika on 03.04.2025.
//

#include <Scripting/Cpp/CodeGenerator.h>
#include <Scripting/Cpp/ScriptSystem.h>

#include <tree_sitter/api.h>

namespace SR_SCRIPTING_NS {
    void CppCodeGenerator::ProcessChangedCodeFiles(const std::set<SR_UTILS_NS::Path>& changedFiles) {
        SR_TRACY_ZONE;

        std::set<SR_UTILS_NS::Path> deletedFiles;
        std::set<SR_UTILS_NS::Path> updatedCppFiles;

        for (auto&& file : changedFiles) {
            if (file.IsFile()) {
                if (ScriptSystem::ALLOWED_CPP_EXTENSIONS.find(file.GetExtensionView()) ==
                    ScriptSystem::ALLOWED_CPP_EXTENSIONS.end()) {
                    SRHalt(
                        "CppCodeGenerator::ProcessChangedCodeFiles() : file is "
                        "not a C++ file!\n\tPath: {}",
                        file
                    );
                    continue;
                }
                updatedCppFiles.insert(file);
            } else {
                deletedFiles.insert(file);
            }
        }

        for (auto&& filePath : updatedCppFiles) {
            auto&& pModuleIt = std::ranges::find_if(m_modules, [&filePath](const CppCodegenModule& module) {
                return filePath.IsSubPath(module.path.GetFolder());
            });

            if (pModuleIt != m_modules.end()) {
                pModuleIt->codeFiles.insert(filePath);
                OnModuleChanged(pModuleIt->moduleInfo.moduleName);
            }
        }

        for (auto&& filePath : deletedFiles) {
            auto&& pModuleIt = std::ranges::find_if(m_modules, [&filePath](const CppCodegenModule& module) {
                return filePath.IsSubPath(module.path.GetFolder());
            });

            if (pModuleIt != m_modules.end()) {
                if (auto&& pFileIt = pModuleIt->codeFiles.find(filePath); pFileIt != pModuleIt->codeFiles.end()) {
                    pModuleIt->codeFiles.erase(pFileIt);
                    OnModuleChanged(pModuleIt->moduleInfo.moduleName);
                }
            }
        }
    }

    void CppCodeGenerator::OnModuleCompiled(SR_UTILS_NS::StringAtom moduleName) {
        for (auto&& module : m_modules) {
            if (module.moduleInfo.moduleName == moduleName) {
                module.isCompiled = true;
                return;
            }
        }
        SRHalt(
            "CppCodeGenerator::OnModuleCompiled() : module not "
            "found!\n\tModule: {}",
            moduleName
        );
    }

    bool CppCodeGenerator::IsNeedRecompile() const {
        return std::ranges::any_of(m_modules, [](const CppCodegenModule& module) { return !module.isCompiled; });
    }

    void CppCodeGenerator::ProcessChangedModules(const std::set<SR_UTILS_NS::Path>& changedModules) {
        std::set<SR_UTILS_NS::Path> deletedModules;
        std::set<SR_UTILS_NS::Path> updatedModules;

        for (auto&& module : changedModules) {
            if (module.IsFile()) {
                if (ScriptSystem::ENGINE_MODULE_FILE_NAME != module.GetBaseNameAndExt()) {
                    SRHalt(
                        "CppCodeGenerator::ProcessChangedModules() : file is "
                        "not a engine module!\n\tPath: {}",
                        module
                    );
                    continue;
                }
                updatedModules.insert(module);
            } else {
                deletedModules.insert(module);
            }
        }

        for (auto&& modulePath : updatedModules) {
            SR_UTILS_NS::SRADeserializer deserializer;
            if (!deserializer.LoadFromFile(modulePath)) {
                SR_ERROR(
                    "CppCodeGenerator::ProcessChangedModules() : failed to "
                    "load file!\n\tPath: {}",
                    modulePath
                );
                continue;
            }

            CppScriptModuleInfo moduleInfo;
            if (!moduleInfo.Load(deserializer)) {
                SR_ERROR(
                    "CppCodeGenerator::ProcessChangedModules() : failed to "
                    "load module info!\n\tPath: {}",
                    modulePath
                );
                continue;
            }

            auto&& pModuleIt = std::ranges::find_if(m_modules, [&modulePath](const CppCodegenModule& module) {
                return module.path == modulePath;
            });

            if (pModuleIt == m_modules.end()) {
                CppCodegenModule module;
                module.path = modulePath;
                module.moduleInfo = moduleInfo;
                m_modules.emplace_back(module);
                pModuleIt = std::prev(m_modules.end());
            } else {
                pModuleIt->moduleInfo = moduleInfo;
            }

            InitModuleSources(*pModuleIt);
            OnModuleChanged(moduleInfo.moduleName);
        }

        for (auto&& modulePath : deletedModules) {
            auto&& pModuleIt = std::ranges::find_if(m_modules, [&modulePath](const CppCodegenModule& module) {
                return module.path == modulePath;
            });

            if (pModuleIt != m_modules.end()) {
                OnModuleChanged(pModuleIt->moduleInfo.moduleName);
                m_modules.erase(pModuleIt);
            } else {
                SR_ERROR(
                    "CppCodeGenerator::ProcessChangedModules() : module for "
                    "deletion not found!\n\tPath: {}",
                    modulePath
                );
            }
        }
    }

    void CppCodeGenerator::OnModuleChanged(SR_UTILS_NS::StringAtom moduleName) {
        for (auto&& module : m_modules) {
            if (module.moduleInfo.dependencies.count(moduleName) != 0) {
                module.isCompiled = false;
                module.isNeedCodegen = true;
            }
            if (module.moduleInfo.moduleName == moduleName) {
                module.isCompiled = false;
                module.isNeedCodegen = true;
            }
        }
    }

    void CppCodeGenerator::RegenerateChangedModules() {
        SR_TRACY_ZONE;

        RegenerateCmake();

        for (auto&& module : m_modules) {
            if (module.codeFiles.empty() || !module.isNeedCodegen) {
                continue;
            }

            const SR_UTILS_NS::Path buildDir =
                m_cacheFolder.Concat("Scripts/Modules/{}"_format(module.moduleInfo.moduleName));
            const SR_UTILS_NS::Path configFolder = m_resourcesFolder.Concat("Engine/Utilities");

            const std::string command =
                "{} --codegen_dir \"{}\" --root_build_dir \"{}\" --repo_dir \"{}\" --config_dir \"{}\" --module_name \"{}\" --is_script --help_sources_dir \"{}\""_format(
                    m_codegenExecutablePath, buildDir, buildDir, module.path.GetFolder(), configFolder,
                    module.moduleInfo.moduleName, m_pScriptSystem->GetEngineSourcesPath().Concat("Engine")
                );

            SR_LOG(
                "CppCodeGenerator::RegenerateChangedModules() : generating "
                "module...\n\tModule: {}\n\tCommand: {}",
                module.moduleInfo.moduleName, command
            );
            const SR_UTILS_NS::TimePointType startTime = SR_HTYPES_NS::Time::Instance().Now();
            std::string result = SR_PLATFORM_NS::ExecuteCommand(command);

            const SR_UTILS_NS::TimePointType endTime = SR_HTYPES_NS::Time::Instance().Now();
            const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

            SR_LOG(
                "CppCodeGenerator::RegenerateChangedModules() : codegen "
                "result:\n{}",
                result
            );
            SR_LOG(
                "CppCodeGenerator::RegenerateChangedModules() : codegen "
                "duration: {} ms",
                duration
            );

            GenerateModule(module);

            module.isNeedCodegen = false;
        }
    }

    void CppCodeGenerator::RegenerateCmake() {
        auto&& cmakeListsPath = m_resourcesFolder.Concat("CMakeLists.txt");
        auto&& cmakeListsCachePath = m_cacheFolder.Concat("Scripts/CMakeLists.txt");

        std::string cmakeContent;
        cmakeContent += "project(SREngineScriptModules)\n";
        cmakeContent += "cmake_minimum_required(VERSION 3.5)\n\n";
        cmakeContent += "set(CMAKE_CXX_STANDARD 20)\n\n";

        cmakeContent += "# Modules \n\n";

        for (auto&& module : m_modules) {
            cmakeContent += "if (ANDROID_NDK)\n";

            cmakeContent += "\tadd_library(SCRIPT_MODULE_{} STATIC\n"_format(module.moduleInfo.moduleName);
            cmakeContent +=
                "\t\t{}/{}.cxx\n"_format(m_cacheFolder.Concat("Scripts/Codegen"), module.moduleInfo.moduleName);
            cmakeContent += "\t)\n";

            cmakeContent += "else()\n";

            cmakeContent += "\tadd_library(SCRIPT_MODULE_{} SHARED\n"_format(module.moduleInfo.moduleName);
            cmakeContent +=
                "\t\t{}/{}.cxx\n"_format(m_cacheFolder.Concat("Scripts/Codegen"), module.moduleInfo.moduleName);
            cmakeContent += "\t)\n";

            cmakeContent += "endif()\n";

            for (auto&& engineIncludeDir : m_pScriptSystem->GetEngineSourcesIncludePaths()) {
                cmakeContent += "target_include_directories(SCRIPT_MODULE_{} PUBLIC {})\n"_format(
                    module.moduleInfo.moduleName, engineIncludeDir
                );
            }

            cmakeContent += "target_include_directories(SCRIPT_MODULE_{} PUBLIC {})\n"_format(
                module.moduleInfo.moduleName,
                m_cacheFolder.Concat("Scripts/Modules/{}/Codegen"_format(module.moduleInfo.moduleName))
            );
        }

        cmakeContent += "# Dependencies \n\n";

        for (auto&& module : m_modules) {
            for (auto&& dependency : GetDependenciesRecursive(module.moduleInfo.moduleName)) {
                if (auto&& pDependencyModule = GetModule(dependency)) {
                    cmakeContent += "target_link_libraries(SCRIPT_MODULE_{} SCRIPT_MODULE_{})\n"_format(
                        module.moduleInfo.moduleName, dependency
                    );
                    cmakeContent += "target_include_directories(SCRIPT_MODULE_{} PUBLIC {})\n"_format(
                        module.moduleInfo.moduleName, pDependencyModule->path.GetFolder()
                    );
                }
            }
        }

        if (!cmakeListsCachePath.Create()) {
            SR_ERROR(
                "CppCodeGenerator::RegenerateCmake() : failed to create script "
                "cmake folder!\n\tPath: {}",
                cmakeListsCachePath
            );
            return;
        }

        if (cmakeListsCachePath.IsFile()) {
            SR_PLATFORM_NS::Delete(cmakeListsCachePath);
        }

        std::ofstream cmakeFile(cmakeListsCachePath.ToString());
        if (cmakeFile.is_open()) {
            cmakeFile << cmakeContent;
            cmakeFile.close();
        } else {
            SR_ERROR(
                "CppCodeGenerator::RegenerateCmake() : failed to open "
                "file!\n\tPath: {}",
                cmakeListsCachePath
            );
        }

        if (cmakeListsPath.IsFile()) {
            if (cmakeListsPath.GetFileHash() == cmakeListsCachePath.GetFileHash()) {
                return;
            }

            SR_LOG(
                "CppCodeGenerator::RegenerateCmake() : CMakeLists.txt is "
                "outdated! Rewrite...\n\tPath: {}",
                cmakeListsPath
            );
            SR_PLATFORM_NS::Delete(cmakeListsPath);
        }

        if (!SR_PLATFORM_NS::Copy(cmakeListsCachePath, cmakeListsPath)) {
            SR_ERROR(
                "CppCodeGenerator::RegenerateCmake() : failed to copy "
                "file!\n\tPath: {}",
                cmakeListsCachePath
            );
        }
    }

    bool CppCodeGenerator::Init() {
        m_resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        m_cacheFolder = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();

        if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Windows) {
            m_codegenExecutablePath = m_resourcesFolder.Concat("Engine/Utilities/codegen.exe");
        } else {
            m_codegenExecutablePath = m_resourcesFolder.Concat("Engine/Utilities/codegen");
        }

        return true;
    }

    std::vector<SR_UTILS_NS::StringAtom> CppCodeGenerator::GetDependenciesRecursive(SR_UTILS_NS::StringAtom moduleName
    ) const {
        std::vector<SR_UTILS_NS::StringAtom> dependencies;
        for (auto&& module : m_modules) {
            if (module.moduleInfo.moduleName == moduleName) {
                dependencies.insert(
                    dependencies.end(), module.moduleInfo.dependencies.begin(), module.moduleInfo.dependencies.end()
                );
                for (auto&& dependency : module.moduleInfo.dependencies) {
                    auto&& subDependencies = GetDependenciesRecursive(dependency);
                    dependencies.insert(dependencies.end(), subDependencies.begin(), subDependencies.end());
                }
                break;
            }
        }
        return dependencies;
    }

    CppCodegenModule* CppCodeGenerator::GetModule(SR_UTILS_NS::StringAtom moduleName) {
        for (auto&& module : m_modules) {
            if (module.moduleInfo.moduleName == moduleName) {
                return &module;
            }
        }
        return nullptr;
    }

    void CppCodeGenerator::InitModuleSources(CppCodegenModule& module) {
        SR_UTILS_NS::FileSystem::ForEachFileInFolder(
            module.path.GetFolder(), true,
            [&module](const SR_UTILS_NS::Path& filePath) {
                if (filePath.IsFile()) {
                    if (ScriptSystem::ALLOWED_CPP_EXTENSIONS.find(filePath.GetExtensionView()) !=
                        ScriptSystem::ALLOWED_CPP_EXTENSIONS.end()) {
                        module.codeFiles.insert(filePath);
                    }
                }
            }
        );
    }

    void CppCodeGenerator::GenerateModule(const CppCodegenModule& module) {
        auto&& codegenFile = m_cacheFolder.Concat("Scripts/Codegen/{}.cxx"_format(module.moduleInfo.moduleName));
        if (!codegenFile.Create()) {
            SR_ERROR(
                "CppCodeGenerator::GenerateModule() : failed to create codegen "
                "path!\n\tPath: {}",
                codegenFile
            );
            return;
        }

        if (codegenFile.IsFile()) {
            SR_PLATFORM_NS::Delete(codegenFile);
        }

        std::ofstream codegenFileStream(codegenFile.ToString());
        if (codegenFileStream.is_open()) {
            codegenFileStream << "/// " << SR_CODEGEN_HEADER_COMMENT << "\n\n";

            codegenFileStream << "#include <Codegen/SpaRcleModule{}Core.generated.hpp>\n\n"_format(
                module.moduleInfo.moduleName
            );

            for (auto&& file : module.codeFiles) {
                if (file.GetExtensionView() == "cxx" || file.GetExtensionView() == "cpp") {
                    codegenFileStream << "#include \"" << file.ToStringRef() << "\"\n";
                }
            }

            if (!module.codeFiles.empty()) {
                codegenFileStream << "\n";
            }

            /*bool hasBehaviours = false;
            for (auto&& [filePath, fileMetadata] : module.codeFiles) {
                for (auto&& behaviour : fileMetadata.behaviours) {
                    codegenFileStream << "void*
            CodegenAllocateScriptBehaviour_{}() "_format(behaviour.name);
                    codegenFileStream << "{ "<< "return new {}();
            "_format(behaviour.MakeNameWithNamespace()) << "}\n";
                }
                hasBehaviours = !fileMetadata.behaviours.empty();
            }

            if (hasBehaviours) {
                codegenFileStream << "\n";
            }*/

            /*if (!m_pScriptSystem->IsUseEngineSourcesAPI()) {
                std::string compilerVersion = m_compiler->GetCompilerVersion();
                compilerVersion =
            SR_UTILS_NS::StringUtils::ReplaceAll<std::string>(compilerVersion,
            "\r", ""); compilerVersion =
            SR_UTILS_NS::StringUtils::ReplaceAll<std::string>(compilerVersion,
            "\n", "\\n");

                codegenFileStream << "bool CodegenRegisterModule_{}_Module()
            "_format(module.moduleInfo.moduleName) << "{\n"; codegenFileStream
            << "\tSpaRcleAPI::CoreAPI::Instance()"; codegenFileStream <<
            "\n\t\t.SetCompilerVersion(\"{}\")"_format(compilerVersion);
                codegenFileStream <<
            "\n\t\t.AddModule(\"{}\")"_format(module.moduleInfo.moduleName);
                codegenFileStream << ";\n";

                for (auto&& [filePath, fileMetadata] : module.codeFiles) {
                    for (auto&& behaviour : fileMetadata.behaviours) {
                        codegenFileStream <<
            "\tSpaRcleAPI::CoreAPI::Instance().GetLastModule()\n";
                        codegenFileStream << "\t\t.AddBehaviour(\"{}\",
            &CodegenAllocateScriptBehaviour_{})"_format(behaviour.name,
            behaviour.name); codegenFileStream << ";\n";
                    }
                }

                codegenFileStream << "\treturn true;\n";
                codegenFileStream << "}\n\n";

                codegenFileStream << "const bool CodegenRegisterModule_{}_Result
            =
            CodegenRegisterModule_{}_Module();"_format(module.moduleInfo.moduleName,
            module.moduleInfo.moduleName);
            }*/

            codegenFileStream.close();
        } else {
            SR_ERROR(
                "CppCodeGenerator::GenerateModule() : failed to open "
                "file!\n\tPath: {}",
                codegenFile
            );
        }
    }
} // namespace SR_SCRIPTING_NS