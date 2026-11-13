//
// Created by Monika on 31.03.2025.
//

#ifndef SR_ENGINE_SCRIPTING_CPP_COMPILER_H
#define SR_ENGINE_SCRIPTING_CPP_COMPILER_H

#include <Scripting/macros.h>

#include <Utils/Serialization/Serializable.h>
#include <Utils/Types/SharedPtr.h>
#include <Utils/FileSystem/Path.h>

namespace SR_SCRIPTING_NS {
    class CppScriptSystem;

    struct CppCompilerContext {
        SR_UTILS_NS::StringAtom moduleName;
        SR_UTILS_NS::Path outFolder;
        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> includePaths;
        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> sourceFiles;
        bool isDebug = false;
        bool isShared = false;
    };

    SR_ENUM_NS_CLASS_T(CppCompilerType, uint8_t,
        Unknown, MinGW, GCC, Clang, MSVC
    )

    struct SR_SCRIPTING_DLL_API CppCompilerSettings : public SR_UTILS_NS::Serializable {
        SR_STRUCT()

        /// @property
        CppCompilerType compilerType = CppCompilerType::Unknown;
        /// @property
        bool useBuiltInCompiler = false;
        /// @property
        bool ignoreCompilerVersion = false;
        /// @property
        bool ignoreOSVersion = false;
        /// @property
        SR_UTILS_NS::Path compilerPath;
    };

    class SR_SCRIPTING_DLL_API CppCompiler : public SR_HTYPES_NS::SharedPtr<CppCompiler> {
        using Super = SR_HTYPES_NS::SharedPtr<CppCompiler>;
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<CppCompiler>;

    public:
        CppCompiler(CppScriptSystem* pCppScriptSystem)
            : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
            , m_pCppScriptSystem(pCppScriptSystem)
        { }

        ~CppCompiler() override;

    public:
        SR_NODISCARD bool Init();
        SR_NODISCARD bool IsCompilerAvailable() const;
        SR_NODISCARD SR_UTILS_NS::String GetCompilerVersion() const;
        SR_NODISCARD bool Compile(const CppCompilerContext& context);

    private:
        bool InstallMinGW();
        bool FindEngineLibs();
        bool FindWindowsCompiler();
        bool FindWindowsSDK();

        bool ValidateCompilerAndOS();
        void SaveSettings();

        SR_NODISCARD SR_UTILS_NS::Path GetBuiltInMSVCCompilerPath() const;

    private:
        SR_UTILS_NS::Path m_windowsSDKPath;
        SR_UTILS_NS::Path m_windowsSDKLibPath;
        SR_UTILS_NS::String m_windowsSDKVersion;
        CppCompilerSettings m_settings;
        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> m_engineLibs;
        SR_UTILS_NS::Path m_cachePath;
        SR_UTILS_NS::Path m_resourcesPath;
        bool m_isInitialized = false;
        CppScriptSystem* m_pCppScriptSystem = nullptr;

    };
}

#endif //SR_ENGINE_SCRIPTING_CPP_COMPILER_H
