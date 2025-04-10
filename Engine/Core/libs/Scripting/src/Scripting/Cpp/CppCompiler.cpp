//
// Created by Monika on 31.03.2025.
//

#include <Scripting/Cpp/CppCompiler.h>

#include <Utils/Platform/Platform.h>

namespace SR_SCRIPTING_NS {
    bool CppCompiler::Init() {
        if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Windows) {
            /// You can change this value under debugger for disabling MSVC compiler
            static std::atomic<bool> disableMSVC = false;
            if (SR_PLATFORM_NS::IsRunningUnderDebugger() && SR_PLATFORM_NS::IsCompiledUnderMSVC() && !disableMSVC) {
                m_compilerType = CppCompilerType::MSVC;
                m_compilerPath = FindMSVCCompilerPath();
            }
            else {
                m_compilerType = CppCompilerType::MinGW;

                auto&& cache = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
                m_compilerPath = cache.Concat("mingw/mingw64/bin").Concat("g++.exe");

                if (!IsCompilerAvailable()) {
                    if (!InstallMinGW()) {
                        SR_ERROR("CppCompiler::Init() : failed to install MinGW!");
                        return false;
                    }
                }
            }
        }
        else if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Linux) {
            m_compilerType = CppCompilerType::GCC;

            m_compilerPath = "/usr/bin/g++";
            if (!IsCompilerAvailable()) {
                SR_ERROR("CppCompiler::Init() : g++ compiler not found by path {}! Please install g++ by command: sudo apt install g++", m_compilerPath);
                return false;
            }
        }

        m_cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();

        SR_LOG("CppCompiler::Init() : compiler path: " + m_compilerPath.ToString());
        SR_LOG("CppCompiler::Init() : compiler version: \n" + GetCompilerVersion());

        m_isInitialized = true;

        return true;
    }

    bool CppCompiler::IsCompilerAvailable() const {
        return SR_PLATFORM_NS::IsExists(m_compilerPath);
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

        if (m_compilerType == CppCompilerType::MSVC) {
            std::string command = m_compilerPath.ToString();
            version = SR_PLATFORM_NS::ExecuteCommand(command);
        }
        else {
            std::string command = m_compilerPath.ToString() + " --version";
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

        if (m_compilerType == CppCompilerType::MSVC) {
            customArgs += "-nologo /std:c++17 /EHsc ";
        }

        const SR_UTILS_NS::PlatformType platform = SR_PLATFORM_NS::GetType();

        switch (platform) {
            case SR_UTILS_NS::PlatformType::Windows:
                outModulePath += context.isShared ? ".dll" : ".lib";

                if (m_compilerType == CppCompilerType::MSVC) {
                    if (context.isShared) {
                        customArgs += context.isDebug ? "/LDd " : "/LD ";
                    }
                    else {
                        customArgs += context.isDebug ? "/MTd " : "/LD ";
                    }
                }
                else {
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
            if (m_compilerType == CppCompilerType::MSVC) {
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
            if (m_compilerType == CppCompilerType::MSVC) {
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
            includePaths += "-I\"" + includePath.ToStringRef() + "\" ";
        }

        std::string outArgs;

        if (m_compilerType == CppCompilerType::MSVC) {
            outArgs += "/Fe" + outModulePath + " ";
            std::string msvcInclude = m_compilerPath.GetPrevious().GetPrevious().GetPrevious().GetPrevious().Concat("include");
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

            std::string msvcLibs = m_compilerPath.GetPrevious().GetPrevious().GetPrevious().GetPrevious().Concat("lib/x64").ToString();

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

        std::string command = "{} {} {} {} {}"_format(
            m_compilerPath, customArgs, outArgs, sourceFiles, includePaths
        );

        if (m_compilerType == CppCompilerType::MSVC) {
            //command += " /LIBPATH:\"C:/Program Files/Microsoft Visual Studio/2022/Community/VC/Tools/MSVC/14.42.34433/lib/x64\"";
            if (context.isDebug) {
                command += " /link /DEBUG /PDB:" + outPdbPath;
            }
        }

        SR_LOG("CppCompiler::Compile() : command: " + command);

        const std::string result = SR_PLATFORM_NS::ExecuteCommand(command);
        const bool hasErrors =
                result.find("compilation terminated") != std::string::npos ||
                result.find("fatal error") != std::string::npos ||
                result.find("error") != std::string::npos;

        if (hasErrors) {
            SR_ERROR("CppCompiler::Compile() : \"{}\" module compilation failed!\n{}", context.moduleName, result);
        }
        else if (!result.empty()) {
            SR_LOG("CppCompiler::Compile() : \"{}\" module compilation succeeded!\n{}", context.moduleName, result);
        }
        else {
            SR_LOG("CppCompiler::Compile() : \"{}\" module compilation succeeded!", context.moduleName);
        }

        if (m_compilerType == CppCompilerType::MSVC) {
            if (SR_PLATFORM_NS::IsExists(outPdbPath)) {
                if (!SR_PLATFORM_NS::Copy(outPdbPath, outPdbPath + ".protected")) {
                    SR_ERROR("CppCompiler::Compile() : failed to copy PDB file!");
                }
                SR_PLATFORM_NS::Delete(outPdbPath);
            }
        }

        return !hasErrors;
    }

    SR_UTILS_NS::Path CppCompiler::FindMSVCCompilerPath() const {
    #ifdef SR_MSVC_COMPILER_PATH
        return SR_MSVC_COMPILER_PATH;
    #else
        SRHalt("MSVC compiler path is not defined!");
        return SR_UTILS_NS::Path();
    #endif
    }
}
