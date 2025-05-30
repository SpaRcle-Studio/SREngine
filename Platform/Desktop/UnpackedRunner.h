//
// Created by Monika on 14.05.2025.
//

int RunUnpackedApplication(const std::string& mainExecutablePath) {
    namespace fs = std::filesystem;

    std::string fileName = fs::path(mainExecutablePath).filename().string();

    if (const auto pos = fileName.find("-packed"); pos != std::string::npos) {
        fileName.erase(pos, sizeof("-packed") - 1);
    }
    std::cout << "RunUnpackedApplication() : running file: " << fileName << std::endl;

    auto&& targetPath =
        fs::absolute(fs::path(mainExecutablePath).remove_filename() / SR_APPLICATION_NAME / "Engine" / "Bin")
            .generic_string();
    const std::string packedPath = absolute(fs::path(mainExecutablePath)).string();

#ifdef WIN32
    const std::string command =
        "cmd.exe /c \"cd \"" + targetPath + "\" && " + fileName + " --delete-packed \"" + packedPath + "\"\"";
#else
    const std::string command = "cd \"" + targetPath + "\" && " + fileName + " --delete-packed \"" + packedPath + "\"";
#endif

    std::cout << "RunUnpackedApplication() : running command: " << command << std::endl;

#ifdef WIN32
    STARTUPINFOA si = {sizeof(si)};
    PROCESS_INFORMATION pi = {};

    if (CreateProcessA(
            nullptr, const_cast<char*>(command.c_str()), nullptr, nullptr, FALSE, CREATE_NO_WINDOW | DETACHED_PROCESS,
            nullptr, nullptr, &si, &pi
        )) {
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    ExitProcess(0);
#else
    if (fork() == 0) {
        execlp("sh", "sh", "-c", command.c_str(), (char*)nullptr);
        _exit(1);
    }
#endif

    return 0;
}