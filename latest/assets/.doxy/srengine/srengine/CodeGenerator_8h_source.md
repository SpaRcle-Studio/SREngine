

# File CodeGenerator.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Cpp**](dir_5b4c9295b84b252e440361db0d67cd77.md) **>** [**CodeGenerator.h**](CodeGenerator_8h.md)

[Go to the documentation of this file](CodeGenerator_8h.md)


```C++
//
// Created by Monika on 03.04.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CODE_GENERATOR_H
#define SR_ENGINE_SCRIPTING_CODE_GENERATOR_H

#include <Scripting/Cpp/ScriptModuleInfo.h>

#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    class CppCompiler;
    class ScriptSystem;

    struct CppCodegenBehaviour {
        SR_UTILS_NS::StringAtom name;
        std::vector<SR_UTILS_NS::StringAtom> namespaces;

        std::string MakeNameWithNamespace() const {
            std::string result;
            for (const auto& ns : namespaces) {
                result += ns.ToString() + "::";
            }
            result += name.ToString();
            return result;
        }
    };

    struct CppFileMetadata {
        std::vector<CppCodegenBehaviour> behaviours;
    };

    struct CppCodegenModule {
        bool isCompiled = false;
        bool isNeedCodegen = true;
        SR_UTILS_NS::Path path;
        CppScriptModuleInfo moduleInfo;
        std::set<SR_UTILS_NS::Path> codeFiles;
    };

    class CppCodeGenerator : public SR_HTYPES_NS::SharedPtr<CppCodeGenerator> {
        using Super = SR_HTYPES_NS::SharedPtr<CppCodeGenerator>;
        constexpr static uint32_t MAX_INCLUDE_DEPTH = 64;
    public:
        explicit CppCodeGenerator(ScriptSystem* pScriptSystem)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
            , m_pScriptSystem(pScriptSystem)
        { }

    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<CppCodeGenerator>;

    public:
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

        void OnModuleChanged(SR_UTILS_NS::StringAtom moduleName);
        void InitModuleSources(CppCodegenModule& module);

        SR_NODISCARD std::vector<SR_UTILS_NS::StringAtom> GetDependenciesRecursive(SR_UTILS_NS::StringAtom moduleName) const;

    private:
        ScriptSystem* m_pScriptSystem = nullptr;
        CppCompiler* m_compiler = nullptr;
        std::vector<CppCodegenModule> m_modules;
        SR_UTILS_NS::Path m_resourcesFolder;
        SR_UTILS_NS::Path m_cacheFolder;
        SR_UTILS_NS::Path m_codegenExecutablePath;

    };
}

#endif //SR_ENGINE_SCRIPTING_CODE_GENERATOR_H
```


