//
// Created by Monika on 12.05.2025.
//

#include <string>
#include <iostream>
#include <filesystem>

const char* ENTRY_POINT_MODULE_NAME = "SREngineEntryPoint";

enum ERROR_CODES {
    SUCCESS = 0,
    ERROR_MODULE_NOT_FOUND = 1,
    ERROR_MODULE_LOAD_FAILED = 2,
    ERROR_MODULE_ENTRY_POINT_NOT_FOUND = 3,
    ERROR_MODULE_UNLOAD_FAILED = 4
};

#if defined(WIN32)
    #include <Windows.h>
    const char* DYNAMIC_MODULE_EXTENSION = ".dll";
    void* LoadDynamicModule(const char* moduleName) {
        return LoadLibraryA(moduleName);
    }
    bool UnloadDynamicModule(void* pModule) {
        return FreeLibrary((HMODULE)pModule);
    }
    auto FindEngineEntryPoint(void* pModule) {
        return (int(*)(int, char**))GetProcAddress((HMODULE)pModule, ENTRY_POINT_MODULE_NAME);
    }
#elif defined(__linux__)
    #include <dlfcn.h>
    const char* DYNAMIC_MODULE_EXTENSION = ".so";
    void* LoadDynamicModule(const char* moduleName) {
        return dlopen(moduleName, RTLD_NOW);
    }
    bool UnloadDynamicModule(void* pModule) {
        return dlclose(pModule) != 0;
    }
    auto FindEngineEntryPoint(void* pModule) {
        return (int(*)(int, char**))dlsym(pModule, ENTRY_POINT_MODULE_NAME);
    }
#elif defined(__APPLE__)
    #include <dlfcn.h>
    const char* DYNAMIC_MODULE_EXTENSION = ".dylib";
    void* LoadDynamicModule(const char* moduleName) {
        return dlopen(moduleName, RTLD_NOW);
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