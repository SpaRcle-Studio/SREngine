//
// Created by Monika on 03.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CODE_GENERATOR_H
#define SR_ENGINE_SCRIPTING_CODE_GENERATOR_H

#include <Scripting/Cpp/ScriptModuleInfo.h>

#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    class CppCompiler;

    struct CppFileMetadata {

    };

    struct CppCodegenModule {
        bool isCompiled = false;
        SR_UTILS_NS::Path path;
        CppScriptModuleInfo moduleInfo;
        std::map<SR_UTILS_NS::Path, CppFileMetadata> codeFiles;
    };

    class CppCodeGenerator : public SR_HTYPES_NS::SharedPtr<CppCodeGenerator> {
        using Super = SR_HTYPES_NS::SharedPtr<CppCodeGenerator>;
        constexpr static uint32_t MAX_INCLUDE_DEPTH = 64;
    public:
        CppCodeGenerator()
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<CppCodeGenerator>;

    public:
        bool ParseScripts();

        bool Init();

        SR_NODISCARD bool IsNeedRecompile() const;
        SR_NODISCARD const std::vector<CppCodegenModule>& GetModules() const { return m_modules; }
        SR_NODISCARD CppCodegenModule* GetModule(SR_UTILS_NS::StringAtom moduleName);

        void SetCompiler(CppCompiler* compiler) { m_compiler = compiler; }

        void ProcessChangedModules(const std::set<SR_UTILS_NS::Path>& changedModules);
        void ProcessChangedCodeFiles(const std::set<SR_UTILS_NS::Path>& changedFiles);

        void RegenerateChangedModules();

        void OnModuleCompiled(SR_UTILS_NS::StringAtom moduleName);

    private:
        void RegenerateCmake();
        void GenerateModule(const CppCodegenModule& module);

        SR_NODISCARD CppFileMetadata ParseFile(const SR_UTILS_NS::Path& path) const;

        void OnModuleChanged(SR_UTILS_NS::StringAtom moduleName);
        void InitModuleSources(CppCodegenModule& module);

        SR_NODISCARD std::vector<SR_UTILS_NS::StringAtom> GetDependenciesRecursive(SR_UTILS_NS::StringAtom moduleName) const;

    private:
        CppCompiler* m_compiler = nullptr;
        std::vector<CppCodegenModule> m_modules;
        SR_UTILS_NS::Path m_resourcesFolder;
        SR_UTILS_NS::Path m_cacheFolder;

    };
}

#endif //SR_ENGINE_SCRIPTING_CODE_GENERATOR_H
