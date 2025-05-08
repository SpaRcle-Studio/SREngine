//
// Created by Monika on 31.03.2025.
//

#include <Scripting/Cpp/CppCompiler.h>

#include <Utils/Platform/Platform.h>
#include <Utils/Platform/MessageBox.h>
#include <Utils/FileSystem/FileDialog.h>

#include <Enum/CppCompilerType.hpp>

#include <Codegen/CppCompiler.generated.hpp>

namespace SR_SCRIPTING_NS {
    static std::string_view CPP_COMPILER_SETTINGS_PATH = "Scripts/CppCompilerSettings.sra";

    CppCompiler::~CppCompiler() = default;

    void CppCompiler::SaveSettings() {
        const SR_UTILS_NS::Path settingsPath = m_cachePath.Concat(CPP_COMPILER_SETTINGS_PATH);
        SR_LOG("CppCompiler::SaveSettings() : save settings to file: {}", settingsPath);
        SR_UTILS_NS::SRASerializer serializer;
        serializer.SetUseTabs(true);
        m_settings.Save(serializer);
        if (!serializer.SaveToFile(settingsPath)) {
            SR_WARN("CppCompiler::SaveSettings() : failed to save settings file: {}", settingsPath);
        }
    }

    bool CppCompiler::Init() {
        m_cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
        m_resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();

        auto&& settingsPath = m_cachePath.Concat(CPP_COMPILER_SETTINGS_PATH);
        if (SR_PLATFORM_NS::IsExists(settingsPath)) {
            SR_UTILS_NS::SRADeserializer deserializer;
            if (!deserializer.LoadFromFile(settingsPath)) {
                SR_WARN("CppCompiler::Init() : failed to load settings file: {}", settingsPath);
            }
            m_settings.Load(deserializer);
        }

        if (!IsCompilerAvailable()) {
            if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Windows) {
                if (!FindWindowsCompiler()) {
                    SR_ERROR("CppCompiler::Init() : failed to find windows compiler!");
                    return false;
                }
            }
            else if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Linux) {
                m_settings.compilerType = CppCompilerType::GCC;
                m_settings.compilerPath = "/usr/bin/g++";

                if (!IsCompilerAvailable()) {
                    SR_ERROR("CppCompiler::Init() : g++ compiler not found by path {}! Please install g++ by command: sudo apt install g++", m_settings.compilerPath);
                    return false;
                }
            }
        }

        if (!FindEngineLibs()) {
            SR_ERROR("CppCompiler::Init() : failed to find engine libs!");
            return false;
        }

        if (!ValidateCompilerAndOS()) {
            SR_ERROR("CppCompiler::Init() : compiler or OS are not compatible!");
            return false;
        }

        SaveSettings();

        SR_LOG("CppCompiler::Init() : compiler path: " + m_settings.compilerPath.ToString());
        SR_LOG("CppCompiler::Init() : compiler version: \n" + GetCompilerVersion());

        m_isInitialized = true;

        return true;
    }

    bool CppCompiler::IsCompilerAvailable() const {
        return SR_PLATFORM_NS::IsExists(m_settings.compilerPath);
    }

    bool CppCompiler::InstallMinGW() {
        std::string url = "https://github.com/brechtsanders/winlibs_mingw/releases/download/14.2.0posix-19.1.7-12.0.0-msvcrt-r3/winlibs-x86_64-posix-seh-gcc-14.2.0-mingw-w64msvcrt-12.0.0-r3.zip";

        auto&& cache = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
        auto&& zipFile = cache.Concat("mingw.zip");
        auto&& installDir = cache.Concat("mingw");

        if (!SR_PLATFORM_NS::IsExists(zipFile)) {
            if (!SR_PLATFORM_NS::DownloadFile(url, zipFile)) {
                SR_ERROR("CppCompiler::InstallMinGW() : failed to download file from url: " + url);
                return false;
            }
        }

        SR_PLATFORM_NS::Unzip(zipFile, installDir, true);

        if (!IsCompilerAvailable()) {
            SR_ERROR("CppCompiler::InstallMinGW() : failed to unzip file: " + zipFile.ToString());
            return false;
        }

        if (zipFile.IsFile()) {
            SR_PLATFORM_NS::Delete(zipFile);
        }
        else {
            SRHalt("Zip file is not a file!");
        }

        return true;
    }

    std::string CppCompiler::GetCompilerVersion() const {
        std::string version;

        if (m_settings.compilerType == CppCompilerType::MSVC) {
            std::string command = m_settings.compilerPath.ToString();
            version = SR_PLATFORM_NS::ExecuteCommand(command);
        }
        else {
            std::string command = m_settings.compilerPath.ToString() + " --version";
            version = SR_PLATFORM_NS::ExecuteCommand(command);
        }

        if (version.empty()) {
            SR_ERROR("CppCompiler::GetCompilerVersion() : failed to get compiler version!");
            return "";
        }

        return version;
    }

    bool CppCompiler::Compile(const CppCompilerContext& context) {
        if (!m_isInitialized) {
            SRHalt("CppCompiler::Compile() : compiler is not initialized!");
            return false;
        }

        std::string outModulePath = context.outFolder.Concat(context.moduleName);
        std::string outPdbPath = context.outFolder.Concat(context.moduleName).ToString() + ".pdb";

        std::string customArgs;

        if (m_settings.compilerType == CppCompilerType::MSVC) {
            customArgs += "-nologo /std:c++20 /EHsc ";
            customArgs += "/DSR_ENGINE_SCRIPT_API_MODE ";
            customArgs += "/DFMT_HEADER_ONLY ";
        }
        else {
            customArgs += "-DSR_ENGINE_SCRIPT_API_MODE ";
            customArgs += "-DFMT_HEADER_ONLY ";
            customArgs += "-std=c++20 ";
            customArgs += "-Wno-deprecated -Wno-unused-variable -Wno-parentheses -Wno-deprecated-declarations -Wno-reorder -Wno-unused-function -Wno-attributes -Wno-delete-incomplete -Wno-sign-compare -Wno-unused-function -Wno-overloaded-virtual -Wno-comment -Wno-template-body ";
        }

        const SR_UTILS_NS::PlatformType platform = SR_PLATFORM_NS::GetType();

        switch (platform) {
            case SR_UTILS_NS::PlatformType::Windows:
                outModulePath += context.isShared ? ".dll" : ".lib";

                if (m_settings.compilerType == CppCompilerType::MSVC) {
                    customArgs += "/DWIN32 ";
                    if (context.isShared) {
                        customArgs += context.isDebug ? "/LDd " : "/LD ";
                    }
                    else {
                        customArgs += context.isDebug ? "/MTd " : "/LD ";
                    }
                }
                else {
                    customArgs += "-DWIN32 ";
                    customArgs += "-shared ";
                }
                break;
            case SR_UTILS_NS::PlatformType::Linux:
            case SR_UTILS_NS::PlatformType::Android:
                outModulePath += context.isShared ? ".so" : ".a";
                customArgs += context.isShared ? "-shared -fPIC " : "";
                break;
            default:
                SRHalt("CppCompiler::Compile() : unknown platform!");
                return false;
        }

        if (context.isDebug) {
            if (m_settings.compilerType == CppCompilerType::MSVC) {
                customArgs += "/Zi /Od ";
            }
            else {
                customArgs += "-g -O0 -Wall ";

                if (platform == SR_UTILS_NS::PlatformType::Windows) {
                    customArgs += "-gdwarf-4 ";
                }
            }
        }
        else {
            if (m_settings.compilerType == CppCompilerType::MSVC) {
                customArgs += "/O2 ";
            }
            else {
                customArgs += "-O3 ";
            }
        }

        if (!SR_UTILS_NS::Path(outModulePath).Create()) {
            SR_ERROR("CppCompiler::Compile() : failed to create output folder: " + outModulePath);
            return false;
        }

        std::string sourceFiles = m_cachePath.Concat("Scripts/Codegen/{}.cxx "_format(context.moduleName));

        std::string includePaths;
        for (auto&& includePath : context.includePaths) {
            if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Windows) {
                includePaths += "-I\"" + includePath.ToStringRef() + "\" ";
            }
            else {
                includePaths += "-I" + includePath.ToStringRef() + " ";
            }
        }

        std::string outArgs;

        if (m_settings.compilerType == CppCompilerType::MSVC) {
            outArgs += "/Fe" + outModulePath + " ";
            std::string msvcInclude = m_settings.compilerPath.GetPrevious().GetPrevious().GetPrevious().GetPrevious().Concat("include");
            includePaths += "/I\"" + msvcInclude + "\" ";

            std::string windowsKitsUmLibs;
            std::string windowsKitsUcrtLibs;

        #if defined(SR_WINDOWS_SDK_DIR) && defined(SR_WINDOWS_SDK_VERSION)
            includePaths += "/I\"" + SR_UTILS_NS::Path(SR_WINDOWS_SDK_DIR).Concat("Include").Concat(SR_WINDOWS_SDK_VERSION).Concat("ucrt").ToString() + "\" ";

            windowsKitsUmLibs = SR_UTILS_NS::Path(SR_WINDOWS_SDK_DIR).Concat("Lib").Concat(SR_WINDOWS_SDK_VERSION).Concat("um/x64").ToString();
            windowsKitsUcrtLibs = SR_UTILS_NS::Path(SR_WINDOWS_SDK_DIR).Concat("Lib").Concat(SR_WINDOWS_SDK_VERSION).Concat("ucrt/x64").ToString();
        #else
            SRHalt("CppCompiler::Compile() : windows latest SDK dir is not defined!");
        #endif

            std::string msvcLibs = m_settings.compilerPath.GetPrevious().GetPrevious().GetPrevious().GetPrevious().Concat("lib/x64").ToString();

            sourceFiles += " \"{}/libcpmtd.lib\" "_format(msvcLibs);
            sourceFiles += " \"{}/LIBCMTD.lib\" "_format(msvcLibs);
            sourceFiles += " \"{}/OLDNAMES.lib\" "_format(msvcLibs);
            sourceFiles += " \"{}/libvcruntimed.lib\" "_format(msvcLibs);

            sourceFiles += " \"{}/kernel32.lib\" "_format(windowsKitsUmLibs);
            sourceFiles += " \"{}/uuid.lib\" "_format(windowsKitsUmLibs);

            sourceFiles += " \"{}/libucrtd.lib\" "_format(windowsKitsUcrtLibs);
        }
        else {
            outArgs += "-o " + outModulePath + " ";
        }

        for (auto&& lib : m_engineLibs) {
            outArgs += " \"{}\" "_format(lib.ToString());
        }

        std::string command = "{} {} {} {} {}"_format(
            m_settings.compilerPath, customArgs, outArgs, sourceFiles, includePaths
        );

        if (m_settings.compilerType == CppCompilerType::MSVC) {
            //command += " /LIBPATH:\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/lib/x64\"";
            if (context.isDebug) {
                command += " /link /DEBUG /PDB:" + outPdbPath;
            }
        }

        SR_LOG("CppCompiler::Compile() : command: " + command);

        const SR_UTILS_NS::TimePointType startTime = SR_HTYPES_NS::Time::Instance().Now();

        const std::string result = SR_PLATFORM_NS::ExecuteCommand(command);
        const bool hasErrors =
                result.find("compilation terminated") != std::string::npos ||
                result.find("fatal error") != std::string::npos ||
                result.find("error") != std::string::npos;

        const SR_UTILS_NS::TimePointType endTime = SR_HTYPES_NS::Time::Instance().Now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();
        SR_LOG("CppCompiler::Compile() : compilation time: {} ms", duration);

        if (hasErrors) {
            SR_ERROR("CppCompiler::Compile() : \"{}\" module compilation failed!\n{}", context.moduleName, result);
        }
        else if (!result.empty()) {
            SR_LOG("CppCompiler::Compile() : \"{}\" module compilation succeeded!\n{}", context.moduleName, result);
        }
        else {
            SR_LOG("CppCompiler::Compile() : \"{}\" module compilation succeeded!", context.moduleName);
        }

        if (m_settings.compilerType == CppCompilerType::MSVC) {
            if (SR_PLATFORM_NS::IsExists(outPdbPath)) {
                if (!SR_PLATFORM_NS::Copy(outPdbPath, outPdbPath + ".protected")) {
                    SR_ERROR("CppCompiler::Compile() : failed to copy PDB file!");
                }
                SR_PLATFORM_NS::Delete(outPdbPath);
            }
        }

        return !hasErrors;
    }

    SR_UTILS_NS::Path CppCompiler::GetBuiltInMSVCCompilerPath() const {
    #ifdef SR_MSVC_COMPILER_PATH
        return SR_MSVC_COMPILER_PATH;
    #else
        SRHalt("MSVC compiler path is not defined!");
        return SR_UTILS_NS::Path();
    #endif
    }

    bool CppCompiler::FindEngineLibs() {
        if (m_settings.compilerType != CppCompilerType::MSVC) {
            /// При сборке .so не создается и не нужен .a
            /// Когда собираем .dll, то .lib нужен
            return true;
        }

        static std::vector<std::pair<std::string, std::string>> libs = {
            //{"Engine/Core", "Core"},
            //{"Engine/Core/libs/Graphics", "Graphics"},
            {"Engine/Core/libs/Utils", "Utils"},
            {"Engine/Core/libs/Scripting", "Scripting"},
            {"Engine/Core/libs/Audio", "Audio"},
            //{"Engine/Core/libs/Utils/libs/fmt", "fmt"},
            {"Engine/Core/libs/Physics", "Physics"}
        };

        auto&& buildDir = m_pScriptSystem->GetBuildFolderPath();

        for (auto&& [libPath, libName] : libs) {
        #ifdef SR_WIN32
            auto&& pathDebug = buildDir.Concat(libPath).Concat("{}d.lib"_format(libName));
            auto&& pathRelease = buildDir.Concat(libPath).Concat("{}.lib"_format(libName));
        #else
            auto&& pathDebug = buildDir.Concat(libPath).Concat("lib{}d.a"_format(libName));
            auto&& pathRelease = buildDir.Concat(libPath).Concat("lib{}.a"_format(libName));
        #endif

            if (SR_PLATFORM_NS::IsExists(pathRelease)) {
                m_engineLibs.emplace_back(pathRelease);
                continue;
            }

            if (SR_PLATFORM_NS::IsExists(pathDebug)) {
                m_engineLibs.emplace_back(pathDebug);
                continue;
            }

            SR_ERROR("CppCompiler::FindEngineLibs() : failed to find engine lib: {} or {}!", pathDebug, pathRelease);
            return false;
        }

        return true;
    }

    bool CppCompiler::FindWindowsCompiler() {
        if (!SR_PLATFORM_NS::IsCompiledUnderMSVC()) {
            SR_ERROR("CppCompiler::FindWindowsCompiler() : windows application not compiled under MSVC!");
            return false;
        }

        m_settings.compilerType = CppCompilerType::MSVC;
        m_settings.useBuiltInCompiler = false;

        const auto builtInCompilerPath = GetBuiltInMSVCCompilerPath();
        if (SR_PLATFORM_NS::IsExists(builtInCompilerPath)) {
            const auto&& result = SR_PLATFORM_NS::ShowMessageBox(
                "Choose compiler",
                "MSVC built-in compiler is available. Do you want to use it? Use only if you are developer.",
                SR_PLATFORM_NS::MessageBoxType::YesNo,
                SR_PLATFORM_NS::MessageBoxIconType::Question,
                SR_PLATFORM_NS::MessageBoxDefaultButtonType::YesOk
            );
            if (result == SR_PLATFORM_NS::MessageBoxResultType::YesOk) {
                m_settings.useBuiltInCompiler = true;
                m_settings.compilerPath = builtInCompilerPath;
                return true;
            }
        }

        const auto&& result = SR_PLATFORM_NS::ShowMessageBox(
            "MSVC compiler not set",
            "Do you want to select existing compiler? (Yes). Or you want to install it? (No)",
            SR_PLATFORM_NS::MessageBoxType::YesNoCancel,
            SR_PLATFORM_NS::MessageBoxIconType::Question,
            SR_PLATFORM_NS::MessageBoxDefaultButtonType::YesOk
        );

        if (result == SR_PLATFORM_NS::MessageBoxResultType::Cancel) {
            SR_ERROR("CppCompiler::FindWindowsCompiler() : user canceled compiler selection!");
            return false;
        }

        if (result == SR_PLATFORM_NS::MessageBoxResultType::No) {
            SR_PLATFORM_NS::ShowMessageBox(
                "Compiler installation",
                "After press OK button, compiler installer will be launched, and current application will be closed. Please, restart application after installation.",
                SR_PLATFORM_NS::MessageBoxType::Ok,
                SR_PLATFORM_NS::MessageBoxIconType::Info,
                SR_PLATFORM_NS::MessageBoxDefaultButtonType::YesOk
            );
            auto&& pathToVSBuildToolsInstaller = m_resourcesPath.Concat("Engine/Utilities/vs_BuildTools.exe");
            SR_SYSTEM_LOG("CppCompiler::FindWindowsCompiler() : path to VS Build Tools installer: " + pathToVSBuildToolsInstaller.ToStringRef());
            SR_SYSTEM_LOG("CppCompiler::FindWindowsCompiler() : engine will be terminated after installer launched!");
            SR_PLATFORM_NS::ExecuteCommand(pathToVSBuildToolsInstaller.ToStringRef());
            SR_PLATFORM_NS::Terminate(false);
        }

        if (result == SR_PLATFORM_NS::MessageBoxResultType::YesOk) {
            SR_LOG("CppCompiler::FindWindowsCompiler() : requesting compiler path from user...");
            m_settings.compilerPath = SR_UTILS_NS::FileDialog::Instance().OpenDialog(m_resourcesPath, { { "cl.exe msvc compiler", "exe" } });
            if (!IsCompilerAvailable()) {
                SR_ERROR("CppCompiler::FindWindowsCompiler() : invalid compiler path!");
                SR_PLATFORM_NS::ShowMessageBox(
                    "Invalid compiler",
                    "Please select valid MSVC (cl.exe) compiler!",
                    SR_PLATFORM_NS::MessageBoxType::Ok,
                    SR_PLATFORM_NS::MessageBoxIconType::Error,
                    SR_PLATFORM_NS::MessageBoxDefaultButtonType::YesOk
                );
                return false;
            }
        }

        return true;
    }

    bool CppCompiler::ValidateCompilerAndOS() {
        if (m_settings.compilerType == CppCompilerType::MSVC) {
            if (SR_PLATFORM_NS::GetType() != SR_UTILS_NS::PlatformType::Windows) {
                SR_ERROR("CppCompiler::ValidateCompilerAndOS() : MSVC compiler is not available on this platform!");
                return false;
            }

            if (!SR_PLATFORM_NS::IsCompiledUnderMSVC()) {
                SR_ERROR("CppCompiler::ValidateCompilerAndOS() : application is not compiled under MSVC, but MSVC compiler is selected!");
                return false;
            }

            if (m_settings.compilerPath.GetBaseNameAndExt() != "cl.exe") {
                SR_ERROR("CppCompiler::ValidateCompilerAndOS() : invalid MSVC compiler path! Path: {}", m_settings.compilerPath);
                return false;
            }

            const std::string buildInCompilerVersion = GetBuiltInMSVCCompilerPath().GetPrevious().GetPrevious().GetPrevious().GetPrevious().GetBaseNameAndExt();
            const std::string currentCompilerVersion = m_settings.compilerPath.GetPrevious().GetPrevious().GetPrevious().GetPrevious().GetBaseNameAndExt();

            if (buildInCompilerVersion != currentCompilerVersion) {
                const std::string mismatchCompilerLogMessage = "CppCompiler::ValidateCompilerAndOS() : built-in compiler version is not equal to current compiler version! "
                                                               "Undefined behaviour possible!\n\tBuilt-in: {}\n\tCurrent: {}"_format(buildInCompilerVersion, currentCompilerVersion);

                if (!m_settings.ignoreCompilerVersion) {
                    SR_WARN(mismatchCompilerLogMessage);

                    const std::string message = "Do you want to continue? Continuing may cause undefined behaviour. Use on your own risk. Built-in version: {}, current version: {}"_format(
                        buildInCompilerVersion, currentCompilerVersion
                    );

                    const auto&& result = SR_PLATFORM_NS::ShowMessageBox(
                        "MSVC compiler version mismatch",
                        message,
                        SR_PLATFORM_NS::MessageBoxType::YesNo,
                        SR_PLATFORM_NS::MessageBoxIconType::Warning,
                        SR_PLATFORM_NS::MessageBoxDefaultButtonType::No
                    );

                    if (result == SR_PLATFORM_NS::MessageBoxResultType::No) {
                        return false;
                    }
                    m_settings.ignoreCompilerVersion = true;
                }
                else {
                    SR_INFO(mismatchCompilerLogMessage);
                }

                SR_INFO("CppCompiler::ValidateCompilerAndOS() : user accepted to continue with different compiler version!");
            }
        }
        else if (m_settings.compilerType == CppCompilerType::GCC) {
            if (SR_PLATFORM_NS::GetType() != SR_UTILS_NS::PlatformType::Linux) {
                SR_ERROR("CppCompiler::ValidateCompilerAndOS() : GCC compiler is not available on this platform!");
                return false;
            }
        }
        else {
            SR_ERROR("CppCompiler::ValidateCompilerAndOS() : unsupported compiler type! Type: {}", m_settings.compilerType);
            return false;
        }

        return true;
    }
}
