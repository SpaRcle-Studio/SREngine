//
// Created by Monika on 12.05.2025.
//

#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <filesystem>
#include <regex>
#include <atomic>
#include <sstream>

#include <zlib.h>

#if defined(__linux__)
    #include <sys/stat.h>
#endif

constexpr uint64_t constexpr_strlen(const char* str) {
    return *str ? 1 + constexpr_strlen(str + 1) : 0;
}

static std::string SR_APPLICATION_NAME = "SREngine";

constexpr const char* ENTRY_POINT_MODULE_NAME = "SREngineEntryPoint";
constexpr const char* MAGIC = "MAGIC_ENGINE_MODULE_DATA";
constexpr uint64_t MAGIC_SIZE = constexpr_strlen(MAGIC);

enum ERROR_CODES {
    SUCCESS = 0,
    ERROR_MODULE_NOT_FOUND = 1,
    ERROR_MODULE_LOAD_FAILED = 2,
    ERROR_MODULE_ENTRY_POINT_NOT_FOUND = 3,
    ERROR_MODULE_UNLOAD_FAILED = 4,
    ERROR_ENGINE_EXIT = 5,
};

#if defined(WIN32)
	#include <Windows.h>
	std::string GetLastErrorAsString()
	{
	    //Get the error message ID, if any.
	    DWORD errorMessageID = ::GetLastError();
	    if (errorMessageID == 0) {
	        return std::string(); //No error message has been recorded
	    }
	    LPSTR messageBuffer = nullptr;
	    //Ask Win32 to give us the string version of that message ID.
	    //The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
	    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
	        NULL, errorMessageID, MAKELANGID(LANG_ENGLISH, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
	    //Copy the error message into a std::string.
	    std::string message(messageBuffer, size - 3);
	    //Free the Win32's string's buffer.
	    LocalFree(messageBuffer);
	    return message;
	}

    constexpr bool SR_IS_WINDOWS = true;
    constexpr bool SR_IS_LINUX = false;
    constexpr bool SR_IS_MACOS = false;
    constexpr bool SR_IS_EMSCRIPTEN = false;

    const char* DYNAMIC_MODULE_EXTENSION = ".dll";
    void* LoadDynamicModule(const char* moduleName) {
        auto&& pLibrary = LoadLibraryA(moduleName);
        if (!pLibrary) {
            auto&& errorMsg = GetLastErrorAsString();
            fprintf(stderr, "LoadDynamicModule() : LoadLibraryA failed, reason: %s\n", errorMsg.c_str());
        }
        return pLibrary;
    }
    bool UnloadDynamicModule(void* pModule) {
        return FreeLibrary((HMODULE)pModule);
    }
    auto FindEngineEntryPoint(void* pModule) {
        return (int(*)(int, char**))GetProcAddress((HMODULE)pModule, ENTRY_POINT_MODULE_NAME);
    }
#elif defined(__linux__)
    constexpr bool SR_IS_WINDOWS = false;
    constexpr bool SR_IS_LINUX = true;
    constexpr bool SR_IS_MACOS = false;
    constexpr bool SR_IS_EMSCRIPTEN = false;
    #include <dlfcn.h>
    #include <unistd.h>
    #include <cstring>
    const char* DYNAMIC_MODULE_EXTENSION = ".so";
    void* LoadDynamicModule(const char* moduleName) {
        void* pHandle = dlopen(moduleName, RTLD_NOW | RTLD_GLOBAL);
        if (!pHandle) {
            const char* error = dlerror();
            fprintf(stderr, "LoadDynamicModule() : dlopen failed, reason: %s\n", error);
        }
        return pHandle;
    }

    bool UnloadDynamicModule(void* pModule) {
        return dlclose(pModule) == 0;
    }
    auto FindEngineEntryPoint(void* pModule) {
        return (int(*)(int, char**))dlsym(pModule, ENTRY_POINT_MODULE_NAME);
    }
#elif defined(__APPLE__)
    constexpr bool SR_IS_WINDOWS = false;
    constexpr bool SR_IS_LINUX = false;
    constexpr bool SR_IS_MACOS = true;
    constexpr bool SR_IS_EMSCRIPTEN = true;
    #include <dlfcn.h>
    #include <unistd.h>
    const char* DYNAMIC_MODULE_EXTENSION = ".dylib";
    void* LoadDynamicModule(const char* moduleName) {
        void* pHandle = dlopen(moduleName, RTLD_NOW | RTLD_GLOBAL);
        if (!pHandle) {
            const char* error = dlerror();
            fprintf(stderr, "LoadDynamicModule() : dlopen failed, reason: %s\n", error);
        }
        return pHandle;
    }

    bool UnloadDynamicModule(void* pModule) {
        return dlclose(pModule) != 0;
    }
    auto FindEngineEntryPoint(void* pModule) {
        return (int(*)(int, char**))dlsym(pModule, ENTRY_POINT_MODULE_NAME);
    }
#else
    #error "Unsupported platform"
#endif

int SREngineEntryPointFromExternalModule(int argc, char** argv, bool notFoundAsError) {
    void* pModuleHandle = nullptr;
    namespace fs = std::filesystem;

    auto&& currentPath = fs::absolute(argv[0]).parent_path();

    constexpr bool isDebugBuild =
        #if defined(_DEBUG) || defined(DEBUG)
            true;
        #else
            false;
        #endif

    std::string debugEnginePath;
    std::string releaseEnginePath;

    for (const auto& entry : fs::directory_iterator(currentPath)) {
        if (!entry.is_regular_file() || entry.path().extension() != DYNAMIC_MODULE_EXTENSION) {
            continue;
        }

        if (entry.path().filename().string().find("Engine") != std::string::npos) {
            std::string modulePath = entry.path().generic_string();
            if (modulePath.empty()) {
                continue;
            }
            if (modulePath.back() == 'd') {
                debugEnginePath = modulePath;
            }
            else {
                releaseEnginePath = modulePath;
            }
        }
    }

    std::string preferredModulePath = isDebugBuild ? debugEnginePath : releaseEnginePath;
    preferredModulePath = !preferredModulePath.empty() ? preferredModulePath : (isDebugBuild ? releaseEnginePath : debugEnginePath);

    if (!preferredModulePath.empty()) {
        pModuleHandle = LoadDynamicModule(preferredModulePath.c_str());
        if (!pModuleHandle) {
            std::cerr << "Failed to load engine library: " << preferredModulePath << std::endl;
            std::cerr << "Enter any key to continue..." << std::endl;
            std::cin.get();
            return ERROR_MODULE_LOAD_FAILED;
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

    int code = pEntryPointFunction(argc, argv);
    if (code != 0) {
        std::cerr << "Engine entry point failed with code: " << code << std::endl;
        code = ERROR_ENGINE_EXIT;
    }

    if (!UnloadDynamicModule(pModuleHandle)) {
        std::cerr << "Failed to unload engine library!" << std::endl;
        return ERROR_MODULE_UNLOAD_FAILED;
    }

    return code != 0 ? code : SUCCESS;
}
