//
// Created by Monika on 03.04.2025.
//

#include <Scripting/Cpp/CodeGenerator.h>
#include <Scripting/Cpp/ScriptSystem.h>

#include <tree_sitter/api.h>

extern "C" {
    TSLanguage* tree_sitter_cpp();
}

namespace SR_SCRIPTING_NS {
    bool HasScriptMacro(TSNode class_body, const std::string_view& source_code, std::string_view macroName) {
        uint32_t child_count = ts_node_child_count(class_body);
        for (uint32_t i = 0; i < child_count; ++i) {
            TSNode child = ts_node_child(class_body, i);
            auto&& type = std::string_view(ts_node_type(child));
            if (type != "declaration") {
                continue;
            }
            std::string_view code_snippet = source_code.substr(
                ts_node_start_byte(child),
                ts_node_end_byte(child) - ts_node_start_byte(child)
            );
            if (code_snippet.find(macroName) != std::string::npos) {
                return true;
            }
        }
        return false;
    }

    void TraverseTree(TSNode node, const std::string_view& sourceCode, std::vector<std::string_view> namespaces, CppFileMetadata& fileMetadata) {
        std::string type = ts_node_type(node);

        if (type == "namespace_definition") {
            TSNode name_node = ts_node_child_by_field_name(node, "name", 4);
            if (ts_node_is_null(name_node)) {
                return;
            }

            std::string_view namespaceName = sourceCode.substr(
                ts_node_start_byte(name_node),
                ts_node_end_byte(name_node) - ts_node_start_byte(name_node)
            );

            namespaces.emplace_back(namespaceName);
        }
        else if (type == "class_specifier") {
            TSNode name_node = ts_node_child_by_field_name(node, "name", 4);
            TSNode body_node = ts_node_child_by_field_name(node, "body", 4);

            if (ts_node_is_null(name_node) || ts_node_is_null(body_node)) {
                return;
            }

            std::string_view class_name = sourceCode.substr(
                ts_node_start_byte(name_node),
                ts_node_end_byte(name_node) - ts_node_start_byte(name_node)
            );

            if (HasScriptMacro(body_node, sourceCode, "SR_SCRIPT_BEHAVIOUR_CLASS")) {
                CppCodegenBehaviour& behaviour = fileMetadata.behaviours.emplace_back();
                behaviour.name = class_name;
                for (auto&& ns : namespaces) {
                    behaviour.namespaces.emplace_back(ns);
                }
            }
        }

        uint32_t count = ts_node_named_child_count(node);
        for (uint32_t i = 0; i < count; ++i) {
            TraverseTree(ts_node_named_child(node, i), sourceCode, namespaces, fileMetadata);
        }
    }

    void parse_comment(TSNode node, const std::string& source_code) {
        /// extract comment text
        /// doesn't work:
        /// std::string comment_text = ts_node_string(node);


        uint32_t start_byte = ts_node_start_byte(node);
        uint32_t end_byte = ts_node_end_byte(node);
        std::string comment_text = source_code.substr(start_byte, end_byte - start_byte);
        std::cout << "Comment: " << comment_text << "\n" << std::flush;
    }

    void parse_field_declaration_list(TSNode node, const std::string& source_code) {
        // Получаем детей списка полей
        uint32_t child_count = ts_node_child_count(node);
        for (uint32_t i = 0; i < child_count; i++) {
            TSNode child = ts_node_child(node, i);
            if (ts_node_is_null(child)) continue;

            std::string childType = ts_node_type(child);
            if (childType == "field_declaration") {
                // Здесь можно обработать поле
                std::cout << "Found field declaration: " << ts_node_string(child) << "\n" << std::flush;
            }
            if (childType == "comment") {
                parse_comment(child, source_code);
            }
        }
    }

    void parse_class(TSNode node, const std::string& source_code) {
        // Получаем детей класса
        uint32_t child_count = ts_node_child_count(node);
        for (uint32_t i = 0; i < child_count; i++) {
            TSNode child = ts_node_child(node, i);
            if (ts_node_is_null(child)) continue;

            std::string childType = ts_node_type(child);
            if (childType == "field_declaration_list") {
                parse_field_declaration_list(child, source_code);
            }
        }
    }

    bool CppCodeGenerator::ParseScripts() {
        // Инициализируем парсер
        TSParser *parser = ts_parser_new();
        ts_parser_set_language(parser, tree_sitter_cpp());

        std::string source_code = R"(
            class Test {
            public:
                /// @property
                /// @dontSave
                int m_property = 2;

                /// @property
                std::string text = "hello";

                int ignored_var = 42; // не помечено @property
            };
        )";

        // Парсим код
        TSTree *tree = ts_parser_parse_string(parser, nullptr, source_code.c_str(), source_code.size());
        TSNode root = ts_tree_root_node(tree);

        // Проход по AST
        TSNode comment, field, type, name, value;
        uint32_t field_count = ts_node_child_count(root);

        for (uint32_t i = 0; i < field_count; i++) {
            TSNode node = ts_node_child(root, i);
            if (ts_node_is_null(node)) continue;

            // Проверяем, что это комментарий
            std::string nodeType = ts_node_type(node);
            if (nodeType == "class_specifier") {
                parse_class(node, source_code);
            }

            /*if (std::string(nodeType) == "comment") {
                std::string comment_text = ts_node_string(node);
                if (comment_text.find("@property") != std::string::npos) {
                    // Следующий узел должен быть полем
                    field = ts_node_next_sibling(node);
                    if (!ts_node_is_null(field) && std::string(ts_node_type(field)) == "field_declaration") {
                        // Достаём детей (тип, имя, значение)
                        type = ts_node_child(field, 0);
                        name = ts_node_child(field, 1);
                        value = ts_node_child_count(field) > 3 ? ts_node_child(field, 3) : TSNode{};

                        std::cout << "Found property:\n";
                        std::cout << "Type: " << ts_node_string(type) << "\n";
                        std::cout << "Name: " << ts_node_string(name) << "\n";
                        if (!ts_node_is_null(value))
                            std::cout << "Value: " << ts_node_string(value) << "\n";
                        std::cout << "----------------------\n";
                    }
                }
            }*/
        }

        // Освобождаем память
        ts_tree_delete(tree);
        ts_parser_delete(parser);

        return false;
    }

    void CppCodeGenerator::ProcessChangedCodeFiles(const std::set<SR_UTILS_NS::Path>& changedFiles) {
        SR_TRACY_ZONE;

        std::set<SR_UTILS_NS::Path> deletedFiles;
        std::set<SR_UTILS_NS::Path> updatedCppFiles;

        for (auto&& file : changedFiles) {
            if (file.IsFile()) {
                if (ScriptSystem::ALLOWED_CPP_EXTENSIONS.find(file.GetExtensionView()) == ScriptSystem::ALLOWED_CPP_EXTENSIONS.end()) {
                    SRHalt("CppCodeGenerator::ProcessChangedCodeFiles() : file is not a C++ file!\n\tPath: {}", file);
                    continue;
                }
                updatedCppFiles.insert(file);
            }
            else {
                deletedFiles.insert(file);
            }
        }

        for (auto&& filePath : updatedCppFiles) {
            auto&& pModuleIt = std::ranges::find_if(m_modules, [&filePath](const CppCodegenModule& module) {
                return filePath.IsSubPath(module.path.GetFolder());
            });

            if (pModuleIt != m_modules.end()) {
                pModuleIt->codeFiles[filePath] = CppFileMetadata();
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

    CppFileMetadata CppCodeGenerator::ParseFile(const SR_UTILS_NS::Path& path) const {
        SR_TRACY_ZONE;

        CppFileMetadata fileMetadata;

        std::string code = SR_UTILS_NS::FileSystem::ReadBinaryAsString(path);

        TSParser *parser = ts_parser_new();
        ts_parser_set_language(parser, tree_sitter_cpp());

        TSTree *tree = ts_parser_parse_string(parser, nullptr, code.c_str(), code.size());
        TSNode root = ts_tree_root_node(tree);

        TraverseTree(root, code, {}, fileMetadata);

        ts_tree_delete(tree);
        ts_parser_delete(parser);

        return fileMetadata;
    }

    void CppCodeGenerator::OnModuleCompiled(SR_UTILS_NS::StringAtom moduleName) {
        for (auto&& module : m_modules) {
            if (module.moduleInfo.moduleName == moduleName) {
                module.isCompiled = true;
                return;
            }
        }
        SRHalt("CppCodeGenerator::OnModuleCompiled() : module not found!\n\tModule: {}", moduleName);
    }

    bool CppCodeGenerator::IsNeedRecompile() const {
        return std::ranges::any_of(m_modules, [](const CppCodegenModule& module) {
            return !module.isCompiled;
        });
    }

    void CppCodeGenerator::ProcessChangedModules(const std::set<SR_UTILS_NS::Path>& changedModules) {
        std::set<SR_UTILS_NS::Path> deletedModules;
        std::set<SR_UTILS_NS::Path> updatedModules;

        for (auto&& module : changedModules) {
            if (module.IsFile()) {
                if (ScriptSystem::ENGINE_MODULE_FILE_NAME != module.GetBaseNameAndExt()) {
                    SRHalt("CppCodeGenerator::ProcessChangedModules() : file is not a engine module!\n\tPath: {}", module);
                    continue;
                }
                updatedModules.insert(module);
            }
            else {
                deletedModules.insert(module);
            }
        }

        for (auto&& modulePath : updatedModules) {
            SR_UTILS_NS::SRADeserializer deserializer;
            if (!deserializer.LoadFromFile(modulePath)) {
                SR_ERROR("CppCodeGenerator::ProcessChangedModules() : failed to load file!\n\tPath: {}", modulePath);
                continue;
            }

            CppScriptModuleInfo moduleInfo;
            if (!moduleInfo.Load(deserializer)) {
                SR_ERROR("CppCodeGenerator::ProcessChangedModules() : failed to load module info!\n\tPath: {}", modulePath);
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
            }
            else {
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
            }
            else {
                SR_ERROR("CppCodeGenerator::ProcessChangedModules() : module for deletion not found!\n\tPath: {}", modulePath);
            }
        }
    }

    void CppCodeGenerator::OnModuleChanged(SR_UTILS_NS::StringAtom moduleName) {
        for (auto&& module : m_modules) {
            if (module.moduleInfo.dependencies.count(moduleName) != 0) {
                module.isCompiled = false;
            }
            if (module.moduleInfo.moduleName == moduleName) {
                module.isCompiled = false;
            }
        }
    }

    void CppCodeGenerator::RegenerateChangedModules() {
        SR_TRACY_ZONE;

        RegenerateCmake();

        for (auto&& module : m_modules) {
            if (module.codeFiles.empty()) {
                continue;
            }

            for (auto&& [filePath, fileMetadata] : module.codeFiles) {
                fileMetadata = ParseFile(filePath);
            }

            GenerateModule(module);
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
            cmakeContent += "add_library(SCRIPT_MODULE_{} SHARED\n"_format(module.moduleInfo.moduleName);

            cmakeContent += "\t{}/{}.cxx\n"_format(m_cacheFolder.Concat("Scripts/Codegen"), module.moduleInfo.moduleName);

            cmakeContent += ")\n";

            if (m_scriptSystem->IsUseEngineSourcesAPI()) {
                for (auto&& engineIncludeDir : m_scriptSystem->GetEngineSourcesIncludePaths()) {
                    cmakeContent += "target_include_directories(SCRIPT_MODULE_{} PUBLIC {})\n"_format(module.moduleInfo.moduleName, engineIncludeDir);
                }

                cmakeContent += "target_include_directories(SCRIPT_MODULE_{} PUBLIC {})\n"_format(module.moduleInfo.moduleName, m_scriptSystem->GetBuildFolderPath().Concat("Codegen"));
            }
            else {
                cmakeContent += "target_include_directories(SCRIPT_MODULE_{} PUBLIC SpaRcleAPI)\n\n"_format(module.moduleInfo.moduleName);
            }
        }

        cmakeContent += "# Dependencies \n\n";

        for (auto&& module : m_modules) {
            for (auto&& dependency : GetDependenciesRecursive(module.moduleInfo.moduleName)) {
                if (auto&& pDependencyModule = GetModule(dependency)) {
                    cmakeContent += "target_link_libraries(SCRIPT_MODULE_{} SCRIPT_MODULE_{})\n"_format(module.moduleInfo.moduleName, dependency);
                    cmakeContent += "target_include_directories(SCRIPT_MODULE_{} PUBLIC {})\n"_format(module.moduleInfo.moduleName, pDependencyModule->path.GetFolder());
                }
            }
        }

        if (!cmakeListsCachePath.Create()) {
            SR_ERROR("CppCodeGenerator::RegenerateCmake() : failed to create script cmake folder!\n\tPath: {}", cmakeListsCachePath);
            return;
        }

        if (cmakeListsCachePath.IsFile()) {
            SR_PLATFORM_NS::Delete(cmakeListsCachePath);
        }

        std::ofstream cmakeFile(cmakeListsCachePath.ToString());
        if (cmakeFile.is_open()) {
            cmakeFile << cmakeContent;
            cmakeFile.close();
        }
        else {
            SR_ERROR("CppCodeGenerator::RegenerateCmake() : failed to open file!\n\tPath: {}", cmakeListsCachePath);
        }

        if (cmakeListsPath.IsFile()) {
            if (cmakeListsPath.GetFileHash() == cmakeListsCachePath.GetFileHash()) {
                return;
            }

            SR_LOG("CppCodeGenerator::RegenerateCmake() : CMakeLists.txt is outdated! Rewrite...\n\tPath: {}", cmakeListsPath);
            SR_PLATFORM_NS::Delete(cmakeListsPath);
        }

        if (!SR_PLATFORM_NS::Copy(cmakeListsCachePath, cmakeListsPath)) {
            SR_ERROR("CppCodeGenerator::RegenerateCmake() : failed to copy file!\n\tPath: {}", cmakeListsCachePath);
        }
    }

    bool CppCodeGenerator::Init() {
        m_resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        m_cacheFolder = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
        return true;
    }

    std::vector<SR_UTILS_NS::StringAtom> CppCodeGenerator::GetDependenciesRecursive(SR_UTILS_NS::StringAtom moduleName) const {
        std::vector<SR_UTILS_NS::StringAtom> dependencies;
        for (auto&& module : m_modules) {
            if (module.moduleInfo.moduleName == moduleName) {
                dependencies.insert(dependencies.end(), module.moduleInfo.dependencies.begin(), module.moduleInfo.dependencies.end());
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
        SR_UTILS_NS::FileSystem::ForEachFileInFolder(module.path.GetFolder(), true, [&module](const SR_UTILS_NS::Path& filePath) {
            if (filePath.IsFile()) {
                if (ScriptSystem::ALLOWED_CPP_EXTENSIONS.find(filePath.GetExtensionView()) != ScriptSystem::ALLOWED_CPP_EXTENSIONS.end()) {
                    module.codeFiles[filePath] = CppFileMetadata();
                }
            }
        });
    }

    void CppCodeGenerator::GenerateModule(const CppCodegenModule& module) {
        auto&& codegenFile = m_cacheFolder.Concat("Scripts/Codegen/{}.cxx"_format(module.moduleInfo.moduleName));
        if (!codegenFile.Create()) {
            SR_ERROR("CppCodeGenerator::GenerateModule() : failed to create codegen path!\n\tPath: {}", codegenFile);
            return;
        }

        if (codegenFile.IsFile()) {
            SR_PLATFORM_NS::Delete(codegenFile);
        }

        std::ofstream codegenFileStream(codegenFile.ToString());
        if (codegenFileStream.is_open()) {
            codegenFileStream << "/// " << SR_CODEGEN_HEADER_COMMENT << "\n\n";

            if (!m_scriptSystem->IsUseEngineSourcesAPI()) {
                codegenFileStream << "#include \"{}\"\n\n"_format(m_resourcesFolder.Concat("SpaRcleAPI/CoreAPIImpl.cpp"));
            }

            for (auto&& file : module.codeFiles) {
                if (file.first.GetExtensionView() == "cxx" || file.first.GetExtensionView() == "cpp") {
                    codegenFileStream << "#include \"" << file.first.ToStringRef() << "\"\n";
                }
            }

            if (!module.codeFiles.empty()) {
                codegenFileStream << "\n";
            }

            bool hasBehaviours = false;
            for (auto&& [filePath, fileMetadata] : module.codeFiles) {
                for (auto&& behaviour : fileMetadata.behaviours) {
                    codegenFileStream << "void* CodegenAllocateScriptBehaviour_{}() "_format(behaviour.name);
                    codegenFileStream << "{ "<< "return new {}(); "_format(behaviour.MakeNameWithNamespace()) << "}\n";
                }
                hasBehaviours = !fileMetadata.behaviours.empty();
            }

            if (hasBehaviours) {
                codegenFileStream << "\n";
            }

            if (!m_scriptSystem->IsUseEngineSourcesAPI()) {
                std::string compilerVersion = m_compiler->GetCompilerVersion();
                compilerVersion = SR_UTILS_NS::StringUtils::ReplaceAll<std::string>(compilerVersion, "\r", "");
                compilerVersion = SR_UTILS_NS::StringUtils::ReplaceAll<std::string>(compilerVersion, "\n", "\\n");

                codegenFileStream << "bool CodegenRegisterModule_{}_Module() "_format(module.moduleInfo.moduleName) << "{\n";
                codegenFileStream << "\tSpaRcleAPI::CoreAPI::Instance()";
                codegenFileStream << "\n\t\t.SetCompilerVersion(\"{}\")"_format(compilerVersion);
                codegenFileStream << "\n\t\t.AddModule(\"{}\")"_format(module.moduleInfo.moduleName);
                codegenFileStream << ";\n";

                for (auto&& [filePath, fileMetadata] : module.codeFiles) {
                    for (auto&& behaviour : fileMetadata.behaviours) {
                        codegenFileStream << "\tSpaRcleAPI::CoreAPI::Instance().GetLastModule()\n";
                        codegenFileStream << "\t\t.AddBehaviour(\"{}\", &CodegenAllocateScriptBehaviour_{})"_format(behaviour.name, behaviour.name);
                        codegenFileStream << ";\n";
                    }
                }

                codegenFileStream << "\treturn true;\n";
                codegenFileStream << "}\n\n";

                codegenFileStream << "const bool CodegenRegisterModule_{}_Result = CodegenRegisterModule_{}_Module();"_format(module.moduleInfo.moduleName, module.moduleInfo.moduleName);
            }

            codegenFileStream.close();
        }
        else {
            SR_ERROR("CppCodeGenerator::GenerateModule() : failed to open file!\n\tPath: {}", codegenFile);
        }
    }
}