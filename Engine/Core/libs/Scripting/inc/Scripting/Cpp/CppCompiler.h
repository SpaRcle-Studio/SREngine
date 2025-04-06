//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_COMPILER_H
#define SR_ENGINE_SCRIPTING_CPP_COMPILER_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    struct CppCompilerContext {
        SR_UTILS_NS::StringAtom moduleName;
        SR_UTILS_NS::Path outFolder;
        std::vector<SR_UTILS_NS::Path> includePaths;
        std::vector<SR_UTILS_NS::Path> sourceFiles;
        bool isDebug = false;
        bool isShared = false;
    };

    class CppCompiler : public SR_HTYPES_NS::SharedPtr<CppCompiler> {
        using Super = SR_HTYPES_NS::SharedPtr<CppCompiler>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<CppCompiler>;

    public:
        CppCompiler()
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

    public:
        SR_NODISCARD bool Init();
        SR_NODISCARD bool IsCompilerAvailable() const;
        SR_NODISCARD std::string GetCompilerVersion() const;
        SR_NODISCARD bool Compile(const CppCompilerContext& context);
        SR_NODISCARD std::string_view GetDynamicModuleExtension() const;

    private:
        bool InstallMinGW();

    private:
        SR_UTILS_NS::Path m_gccPath;
        bool m_isInitialized = false;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_COMPILER_H
