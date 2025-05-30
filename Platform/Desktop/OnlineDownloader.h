//
// Created by Monika on 15.05.2025.
//

#if defined(WIN32)
    #include <wininet.h>

bool DownloadFile(const std::string& url, const std::string& outputPath) {
    std::cout << "Downloading file from: " << url << std::endl;

    HINTERNET hInternet = InternetOpenA("SREngine", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {
        std::cerr << "Failed to open internet connection." << std::endl;
        return false;
    }

    HINTERNET hUrl = InternetOpenUrlA(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hUrl) {
        std::cerr << "Failed to open URL: " << url << std::endl;
        InternetCloseHandle(hInternet);
        return false;
    }

    std::ofstream file(outputPath, std::ios::binary);
    char buffer[4096]; // 4 КБ buffer
    DWORD bytesRead;
    uint64_t totalBytesRead = 0;
    uint64_t packetInterval = 0;

    while (InternetReadFile(hUrl, buffer, sizeof(buffer), &bytesRead) && bytesRead) {
        ++packetInterval;
        totalBytesRead += bytesRead;
        if (packetInterval % 200 == 0) {
            std::cout << "Total MBytes read: " << static_cast<uint64_t>(totalBytesRead / 1024.f / 1024.f) << std::endl;
            packetInterval = 0;
        }
        file.write(buffer, bytesRead);
    }

    file.close();
    InternetCloseHandle(hUrl);
    InternetCloseHandle(hInternet);

    std::cout << "File downloaded successfully to: " << outputPath << std::endl;

    return true;
}
#elif defined(__linux__) || defined(__APPLE__)
bool DownloadFile(const std::string& url, const std::string& outputPath) {
    std::cout << "Downloading file from: " << url << std::endl;

    std::string command = "wget -O \"" + outputPath + "\" \"" + url + "\"";
    int result = system(command.c_str());

    if (result != 0) {
        std::cerr << "Failed to download file." << std::endl;
        return false;
    }

    std::cout << "File downloaded successfully to: " << outputPath << std::endl;

    return true;
}
#endif

int DownloadEngineDataFromGithub(const std::string& executablePath) {
    std::string platform;
    std::string buildType;

#if defined(WIN32)
    platform = "windows";
#elif defined(__linux__)
    platform = "linux";
#elif defined(__APPLE__)
    platform = "macos";
#else
    std::cerr << "Unsupported platform." << std::endl;
    return -1;
#endif

#if defined(NDEBUG)
    buildType = "release";
#else
    buildType = "debug";
#endif

    std::string branch = "dev";
    std::string link = "https://github.com/SpaRcle-Studio/SRE2R/releases/download/" + branch + "-" + platform + "-" +
                       buildType + "/engine-online-data.dmp";

    std::filesystem::path outputPath = std::filesystem::path(executablePath).parent_path() / "engine-online-data.dmp";
    if (!DownloadFile(link, outputPath.generic_string())) {
        std::cerr << "DownloadEngineDataFromGithub() : failed to download "
                     "engine data from GitHub."
                  << std::endl;
        return -1;
    }

    std::ifstream dataFile(outputPath.generic_string(), std::ios::binary | std::ios::ate);
    if (!dataFile) {
        std::cerr << "DownloadEngineDataFromGithub() : failed to open file: " << outputPath.generic_string() << "\n";
        return UNPACK_FILE_NOT_FOUND;
    }

    const bool result = TryUnpackFiles(executablePath, dataFile);

    dataFile.close();

    if (is_regular_file(outputPath)) {
        std::cout << "DownloadEngineDataFromGithub() : removing file: " << outputPath.generic_string() << "\n";
        std::filesystem::remove(outputPath);
    }

    return result;
}