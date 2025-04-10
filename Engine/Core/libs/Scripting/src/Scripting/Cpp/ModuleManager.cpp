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
            auto&& pDestroyScriptCoreAPI = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "DestroyScriptCoreAPI");
            reinterpret_cast<void(*)()>(pDestroyScriptCoreAPI)();

            if (!SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle)) {
                SRHalt("ModuleManager::ReloadModule() : failed to unload module! Something went wrong...\n\tPath: " + path.ToString());
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
        SR_TRACY_ZONE;

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

        auto&& pModulesCountFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModulesCount");
        auto&& pModuleNameFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModuleName");
        auto&& pModuleVersionFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModuleCompilerVersion");
        auto&& pDestroyScriptCoreAPI = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "DestroyScriptCoreAPI");

        if (pModuleNameFunction && pModuleVersionFunction && pModulesCountFunction && pDestroyScriptCoreAPI) {
            const uint32_t countModules = reinterpret_cast<uint32_t(*)()>(pModulesCountFunction)();
            if (countModules != 1) {
                SR_ERROR("ModuleManager::LoadModule() : module count mismatch!\n\tExpected: 1\n\tActual: {}"_format(countModules));
                goto unload_module;
            }

            const std::string_view scriptModuleName = reinterpret_cast<const char* (*)(uint32_t)>(pModuleNameFunction)(0);
            const std::string_view scriptCompilerVersion = reinterpret_cast<const char* (*)()>(pModuleVersionFunction)();

            if (scriptModuleName != moduleName) {
                SR_ERROR("ModuleManager::LoadModule() : module name mismatch!\n\tExpected: {}\n\tActual: {}"_format(moduleName.ToString(), scriptModuleName));
                goto unload_module;
            }

            if (m_lastCompilerVersion.empty()) {
                m_lastCompilerVersion = scriptCompilerVersion;
            }
            else if (m_lastCompilerVersion != scriptCompilerVersion) {
                SR_ERROR("ModuleManager::LoadModule() : module compiler version mismatch!\n\tExpected: {}\n\tActual: {}"_format(m_lastCompilerVersion, scriptCompilerVersion));
                goto unload_module;
            }
        }
        else {
            SR_ERROR("ModuleManager::LoadModule() : invalid module!\n\tPath: " + runtimePath.ToString());
            SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle);
            return nullptr;
        }

        SR_LOG("ModuleManager::LoadModule() : module {} is correct.", moduleName.ToString());
        return pLibraryHandle;

    unload_module:
        reinterpret_cast<void(*)()>(pDestroyScriptCoreAPI)();
        SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle);
        return nullptr;
    }

    CppBehaviourInstance* ModuleManager::AllocateBehaviourInstance(const SR_UTILS_NS::StringAtom& behaviourName) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        auto&& pInstance = new CppBehaviourInstance();

        pInstance->SetBehaviourName(behaviourName, SR_UTILS_NS::Passkey<ModuleManager>(this));

        for (auto&& module : m_modules) {
            if (module.HasBehaviour(behaviourName)) {

                break;
            }
        }

        if (m_behaviourInstances.count(pInstance) > 0) {
            SRHalt("Memory address collision! Something went wrong...");
            delete pInstance;
            return nullptr;
        }

        m_behaviourInstances.insert(pInstance);
        return pInstance;
    }

    void ModuleManager::FreeBehaviourInstance(CppBehaviourInstance* pInstance) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        auto&& pIt = m_behaviourInstances.find(pInstance);

        if (pIt != m_behaviourInstances.end()) {
            delete *pIt;
            m_behaviourInstances.erase(pIt);
        }
        else {
            SRHalt("ModuleManager::FreeBehaviourInstance() : instance not found!");
        }
    }
}