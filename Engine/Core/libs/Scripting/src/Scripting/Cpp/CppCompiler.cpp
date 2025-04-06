//
// Created by Monika on 31.03.2025.
//

#include <Scripting/Cpp/CppCompiler.h>

#include <Utils/Platform/Platform.h>

namespace SR_SCRIPTING_NS {
    bool CppCompiler::Init() {
        if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Windows) {
            auto&& cache = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();
            m_gccPath = cache.Concat("mingw/mingw64/bin").Concat("g++.exe");

            if (!IsCompilerAvailable()) {
                if (!InstallMinGW()) {
                    SR_ERROR("CppCompiler::Init() : failed to install MinGW!");
                    return false;
                }
            }
        }
        else if (SR_PLATFORM_NS::GetType() == SR_UTILS_NS::PlatformType::Linux) {
            m_gccPath = "/usr/bin/g++";
            if (!IsCompilerAvailable()) {
                SR_ERROR("CppCompiler::Init() : g++ compiler not found by path {}! Please install g++ by command: sudo apt install g++", m_gccPath);
                return false;
            }
        }

        SR_LOG("CppCompiler::Init() : compiler path: " + m_gccPath.ToString());
        SR_LOG("CppCompiler::Init() : compiler version: \n" + GetCompilerVersion());

        m_isInitialized = true;

        return true;
    }

    bool CppCompiler::IsCompilerAvailable() const {
        return SR_PLATFORM_NS::IsExists(m_gccPath);
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
        std::string command = m_gccPath.ToString() + " --version";
        std::string version = SR_PLATFORM_NS::ExecuteCommand(command);
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
        std::string customArgs;

        const SR_UTILS_NS::PlatformType platform = SR_PLATFORM_NS::GetType();

        switch (platform) {
            case SR_UTILS_NS::PlatformType::Windows:
                outModulePath += context.isShared ? ".dll" : ".lib";
                break;
            case SR_UTILS_NS::PlatformType::Linux:
            case SR_UTILS_NS::PlatformType::Android:
                outModulePath += context.isShared ? ".so" : ".a";
                customArgs += context.isShared ? "-fPIC " : "";
                break;
            default:
                SRHalt("CppCompiler::Compile() : unknown platform!");
                return false;
        }

        if (context.isDebug) {
            customArgs += "-g ";
        }
        else {
            customArgs += "-O3 ";
        }

        if (!SR_UTILS_NS::Path(outModulePath).Create()) {
            SR_ERROR("CppCompiler::Compile() : failed to create output folder: " + outModulePath);
            return false;
        }

        std::string sourceFiles;
        for (auto&& filePath : context.sourceFiles) {
            sourceFiles += filePath.ToStringRef() + " ";
        }

        if (sourceFiles.empty()) {
            SR_ERROR("CppCompiler::Compile() : no source files provided!");
            return false;
        }

        std::string includePaths;
        for (auto&& includePath : context.includePaths) {
            includePaths += "-I" + includePath.ToStringRef() + " ";
        }

        std::string command = "{} -shared {} -o {} {} {}"_format(
            m_gccPath, customArgs, outModulePath, sourceFiles, includePaths
        );

        SR_LOG("CppCompiler::Compile() : command: " + command);

        const std::string result = SR_PLATFORM_NS::ExecuteCommand(command);
        const bool hasErrors =
                result.find("compilation terminated") != std::string::npos ||
                result.find("error:") != std::string::npos;

        if (hasErrors) {
            SR_ERROR("CppCompiler::Compile() : \"{}\" module compilation failed!\n{}", context.moduleName, result);
        }
        else if (!result.empty()) {
            SR_LOG("CppCompiler::Compile() : \"{}\" module compilation succeeded!\n{}", context.moduleName, result);
        }
        else {
            SR_LOG("CppCompiler::Compile() : \"{}\" module compilation succeeded!", context.moduleName);
        }

        return !hasErrors;
    }

    std::string_view CppCompiler::GetDynamicModuleExtension() const {
        const SR_UTILS_NS::PlatformType platform = SR_PLATFORM_NS::GetType();

        switch (platform) {
            case SR_UTILS_NS::PlatformType::Windows:
                return "dll";
            case SR_UTILS_NS::PlatformType::Linux:
            case SR_UTILS_NS::PlatformType::Android:
                return "so";
            default:
                SRHalt("CppCompiler::Compile() : unknown platform!");
                return "";
        }
    }
}
