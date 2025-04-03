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
            if (!SR_UTILS_NS::Platform::DownloadFile(url, zipFile)) {
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
            SR_UTILS_NS::Platform::Delete(zipFile);
        }
        else {
            SRHalt("Zip file is not a file!");
        }

        return true;
    }
}
