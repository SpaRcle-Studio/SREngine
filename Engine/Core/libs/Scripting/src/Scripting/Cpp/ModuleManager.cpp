//
// Created by Monika on 07.04.2025.
//

#include <Scripting/Cpp/ModuleManager.h>
#include <Scripting/Cpp/ScriptSystem.h>

namespace SR_SCRIPTING_NS {
    bool ModuleManager::ReloadModule(const SR_UTILS_NS::Path& path) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        SR_LOG("ModuleManager::ReloadModule() : reloading module \"" + path.ToString() + "\"");

        const SR_UTILS_NS::StringAtom moduleName = path.GetBaseName();

        auto&& pIt = std::ranges::find_if(m_modules, [&path](const auto& module) {
            return module.GetPath() == path;
        });

        if (pIt == m_modules.end()) {
            ScriptModule module;
            module.SetPath(path);
            module.SetModuleName(moduleName);
            m_modules.emplace_back(module);
            pIt = std::prev(m_modules.end());
        }

        ScriptModule& module = *pIt;

        if (auto&& pLibraryHandle = module.GetModuleHandle()) {
            if (!SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle)) {
                SR_ERROR("ModuleManager::ReloadModule() : failed to unload module!\n\tPath: " + path.ToString());
                return false;
            }
            else {
                SR_LOG("ModuleManager::ReloadModule() : module \"" + path.ToString() + "\" unloaded.");
            }
            module.SetModuleHandle(nullptr);
        }

        if (auto&& pLibraryHandle = LoadModule(path)) {
            module.SetModuleHandle(pLibraryHandle);
        }
        else {
            SR_ERROR("ModuleManager::ReloadModule() : failed to load module!\n\tPath: " + path.ToString());
            return false;
        }

        return true;
    }

    bool ModuleManager::Init() {
        SR_TRACY_ZONE;

        SR_LOG("ModuleManager::Init() : initializing module manager...");

        m_resourcesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        m_cachePath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath();

        return true;
    }

    void* ModuleManager::LoadModule(const SR_UTILS_NS::Path& modulePath) {
        const SR_UTILS_NS::StringAtom moduleName = modulePath.GetBaseName();
        auto&& runtimePath = m_cachePath.Concat("Scripts/Runtime/Modules/{}.{}"_format(moduleName, ScriptSystem::GetDynamicLibraryExtension()));
        auto&& pdbRuntimePath = m_cachePath.Concat("Scripts/Runtime/Modules/{}.pdb"_format(moduleName));

        if (runtimePath.IsFile() && !SR_PLATFORM_NS::Delete(runtimePath)) {
            SR_ERROR("ModuleManager::LoadModule() : failed to delete module!\n\tPath: " + runtimePath.ToString());
            return nullptr;
        }

        if (pdbRuntimePath.IsFile() && !SR_PLATFORM_NS::Delete(pdbRuntimePath)) {
            SR_ERROR("ModuleManager::LoadModule() : failed to delete module pdb!\n\tPath: " + pdbRuntimePath.ToString());
            return nullptr;
        }

        if (!runtimePath.Create()) {
            SR_ERROR("ModuleManager::LoadModule() : failed to create module path!\n\tPath: " + modulePath.ToString());
            return nullptr;
        }

        auto&& sourcePdbPath = modulePath.GetFolder().Concat("{}.pdb"_format(moduleName));
        if (SR_PLATFORM_NS::IsExists(sourcePdbPath)) {
            if (!SR_PLATFORM_NS::Copy(sourcePdbPath, pdbRuntimePath)) {
                SR_ERROR("ModuleManager::LoadModule() : failed to copy module pdb!\n\tPath: " + sourcePdbPath.ToString());
                return nullptr;
            }
        }

        if (!SR_PLATFORM_NS::Copy(modulePath, runtimePath)) {
            SR_ERROR("ModuleManager::LoadModule() : failed to copy module!\n\tPath: " + modulePath.ToString());
            return nullptr;
        }

        if (!SR_PLATFORM_NS::IsExists(runtimePath)) {
            SR_ERROR("ModuleManager::LoadModule() : module not exists!\n\tPath: " + runtimePath.ToString());
            return nullptr;
        }

        auto&& pLibraryHandle = SR_PLATFORM_NS::LoadLibraryModule(runtimePath);
        if (!pLibraryHandle) {
            SR_ERROR("ModuleManager::LoadModule() : failed to load module!\n\tPath: " + runtimePath.ToString());
            return nullptr;
        }

        auto&& pModuleNameFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModuleName");
        auto&& pModuleVersionFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModuleCompilerVersion");

        if (pModuleNameFunction && pModuleVersionFunction) {
            const std::string_view scriptModuleName = reinterpret_cast<const char* (*)()>(pModuleNameFunction)();
            const std::string_view scriptCompilerVersion = reinterpret_cast<const char* (*)()>(pModuleVersionFunction)();

            if (scriptModuleName != moduleName) {
                SR_ERROR("ModuleManager::LoadModule() : module name mismatch!\n\tExpected: {}\n\tActual: {}"_format(moduleName.ToString(), scriptModuleName));
                SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle);
                return nullptr;
            }

            if (m_lastCompilerVersion.empty()) {
                m_lastCompilerVersion = scriptCompilerVersion;
            }
            else if (m_lastCompilerVersion != scriptCompilerVersion) {
                SR_ERROR("ModuleManager::LoadModule() : module compiler version mismatch!\n\tExpected: {}\n\tActual: {}"_format(m_lastCompilerVersion, scriptCompilerVersion));
                SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle);
                return nullptr;
            }
        }
        else {
            SR_ERROR("ModuleManager::LoadModule() : invalid module!\n\tPath: " + runtimePath.ToString());
            SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle);
            return nullptr;
        }

        SR_LOG("ModuleManager::LoadModule() : module {} is correct.", moduleName.ToString());
        return pLibraryHandle;
    }
}