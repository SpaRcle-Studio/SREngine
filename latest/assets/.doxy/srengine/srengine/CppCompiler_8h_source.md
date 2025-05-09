

# File CppCompiler.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Cpp**](dir_5b4c9295b84b252e440361db0d67cd77.md) **>** [**CppCompiler.h**](CppCompiler_8h.md)

[Go to the documentation of this file](CppCompiler_8h.md)


```C++
//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_COMPILER_H
#define SR_ENGINE_SCRIPTING_CPP_COMPILER_H

#include <Scripting/macros.h>

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

    SR_ENUM_NS_CLASS_T(CppCompilerType, uint8_t,
        Unknown, MinGW, GCC, Clang, MSVC
    )

    struct CppCompilerSettings : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        
        CppCompilerType compilerType = CppCompilerType::Unknown;
        bool useBuiltInCompiler = false;
        bool ignoreCompilerVersion = false;
        bool ignoreOSVersion = false;
        SR_UTILS_NS::Path compilerPath;
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

        ~CppCompiler() override;

    public:
        SR_NODISCARD bool Init();
        SR_NODISCARD bool IsCompilerAvailable() const;
        SR_NODISCARD std::string GetCompilerVersion() const;
        SR_NODISCARD bool Compile(const CppCompilerContext& context);

    private:
        bool InstallMinGW();
        bool FindEngineLibs();
        bool FindWindowsCompiler();

        bool ValidateCompilerAndOS();
        void SaveSettings();

        SR_NODISCARD SR_UTILS_NS::Path GetBuiltInMSVCCompilerPath() const;

    private:
        CppCompilerSettings m_settings;
        std::vector<SR_UTILS_NS::Path> m_engineLibs;
        SR_UTILS_NS::Path m_cachePath;
        SR_UTILS_NS::Path m_resourcesPath;
        bool m_isInitialized = false;
        ScriptSystem* m_pScriptSystem = nullptr;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_COMPILER_H
```


