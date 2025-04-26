//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_COMPILER_H
#define SR_ENGINE_SCRIPTING_CPP_COMPILER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    class ScriptSystem;

    struct CppCompilerContext {
        SR_UTILS_NS::StringAtom moduleName;
        SR_UTILS_NS::Path outFolder;
        std::vector<SR_UTILS_NS::Path> includePaths;
        std::vector<SR_UTILS_NS::Path> sourceFiles;
        bool isDebug = false;
        bool isShared = false;
    };

    enum class CppCompilerType {
        Unknown, MinGW, GCC, Clang, MSVC
    };

    class CppCompiler : public SR_HTYPES_NS::SharedPtr<CppCompiler> {
        using Super = SR_HTYPES_NS::SharedPtr<CppCompiler>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<CppCompiler>;

    public:
        CppCompiler(ScriptSystem* pScriptSystem)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
            , m_pScriptSystem(pScriptSystem)
        { }

    public:
        SR_NODISCARD bool Init();
        SR_NODISCARD bool IsCompilerAvailable() const;
        SR_NODISCARD std::string GetCompilerVersion() const;
        SR_NODISCARD bool Compile(const CppCompilerContext& context);

    private:
        bool InstallMinGW();
        bool FindEngineLibs();

        SR_NODISCARD SR_UTILS_NS::Path FindMSVCCompilerPath() const;

    private:
        std::vector<SR_UTILS_NS::Path> m_engineLibs;
        CppCompilerType m_compilerType = CppCompilerType::Unknown;
        SR_UTILS_NS::Path m_cachePath;
        SR_UTILS_NS::Path m_compilerPath;
        bool m_isInitialized = false;
        ScriptSystem* m_pScriptSystem = nullptr;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_COMPILER_H
