//
// Created by Monika on 12.05.2025.
//

#include <atomic>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <ostream>
#include <regex>
#include <string>

#include <zlib.h>

constexpr uint64_t constexpr_strlen(const char* str) { return *str ? 1 + constexpr_strlen(str + 1) : 0; }

static std::string SR_APPLICATION_NAME = "SREngine";

constexpr const char* ENTRY_POINT_MODULE_NAME = "SREngineEntryPoint";
constexpr const char* MAGIC = "MAGIC_ENGINE_MODULE_DATA";
constexpr uint64_t MAGIC_SIZE = constexpr_strlen(MAGIC);

enum ERROR_CODES {
    SUCCESS = 0,
    ERROR_MODULE_NOT_FOUND = 1,
    ERROR_MODULE_LOAD_FAILED = 2,
    ERROR_MODULE_ENTRY_POINT_NOT_FOUND = 3,
    ERROR_MODULE_UNLOAD_FAILED = 4
};

#if defined(WIN32)
constexpr bool SR_IS_WINDOWS = true;
constexpr bool SR_IS_LINUX = false;
constexpr bool SR_IS_MACOS = false;
    #include <Windows.h>
const char* DYNAMIC_MODULE_EXTENSION = ".dll";
void* LoadDynamicModule(const char* moduleName) { return LoadLibraryA(moduleName); }
bool UnloadDynamicModule(void* pModule) { return FreeLibrary((HMODULE)pModule); }
auto FindEngineEntryPoint(void* pModule) {
    return (int (*)(int, char**))GetProcAddress((HMODULE)pModule, ENTRY_POINT_MODULE_NAME);
}
#elif defined(__linux__)
constexpr bool SR_IS_WINDOWS = false;
constexpr bool SR_IS_LINUX = true;
constexpr bool SR_IS_MACOS = false;
    #include <cstring>
    #include <dlfcn.h>
    #include <unistd.h>
const char* DYNAMIC_MODULE_EXTENSION = ".so";
void* LoadDynamicModule(const char* moduleName) { return dlopen(moduleName, RTLD_NOW); }
bool UnloadDynamicModule(void* pModule) { return dlclose(pModule) != 0; }
auto FindEngineEntryPoint(void* pModule) { return (int (*)(int, char**))dlsym(pModule, ENTRY_POINT_MODULE_NAME); }
#elif defined(__APPLE__)
constexpr bool SR_IS_WINDOWS = false;
constexpr bool SR_IS_LINUX = false;
constexpr bool SR_IS_MACOS = true;
    #include <dlfcn.h>
    #include <unistd.h>
const char* DYNAMIC_MODULE_EXTENSION = ".dylib";
void* LoadDynamicModule(const char* moduleName) { return dlopen(moduleName, RTLD_NOW); }
bool UnloadDynamicModule(void* pModule) { return dlclose(pModule) != 0; }
auto FindEngineEntryPoint(void* pModule) { return (int (*)(int, char**))dlsym(pModule, ENTRY_POINT_MODULE_NAME); }
#else
    #error "Unsupported platform"
#endif

int SREngineEntryPointFromExternalModule(int argc, char** argv, bool notFoundAsError) {
    void* pModuleHandle = nullptr;
    namespace fs = std::filesystem;

    for (const auto& entry : fs::directory_iterator(fs::current_path())) {
        if (!entry.is_regular_file() || entry.path().extension() != DYNAMIC_MODULE_EXTENSION) {
            continue;
        }

        if (entry.path().filename().string().find("Engine") != std::string::npos) {
            pModuleHandle = LoadDynamicModule(entry.path().string().c_str());
            if (!pModuleHandle) {
                std::cerr << "Failed to load engine library: " << entry.path() << std::endl;
                std::cerr << "Enter any key to continue..." << std::endl;
                std::cin.get();
                return ERROR_MODULE_LOAD_FAILED;
            }
        }
    }

    if (!pModuleHandle) {
        if (notFoundAsError) {
            std::cerr << "Engine library not found!" << std::endl;
            std::cerr << "Enter any key to continue..." << std::endl;
            std::cin.get();
        }
        return ERROR_MODULE_NOT_FOUND;
    }

    auto&& pEntryPointFunction = FindEngineEntryPoint(pModuleHandle);
    if (!pEntryPointFunction) {
        std::cerr << "Failed to find entry point in Engine library!" << std::endl;
        std::cerr << "Enter any key to continue..." << std::endl;
        std::cin.get();
        return ERROR_MODULE_ENTRY_POINT_NOT_FOUND;
    }

    const int code = pEntryPointFunction(argc, argv);
    if (code != 0) {
        std::cerr << "Engine entry point failed with code: " << code << std::endl;
    }

    if (!UnloadDynamicModule(pModuleHandle)) {
        std::cerr << "Failed to unload engine library!" << std::endl;
        return ERROR_MODULE_UNLOAD_FAILED;
    }

    return code != 0 ? code : SUCCESS;
}