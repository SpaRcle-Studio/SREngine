//
// Created by Monika on 07.04.2025.
//

#include <Scripting/Cpp/ModuleManager.h>
#include <Scripting/Cpp/ScriptSystem.h>

namespace SR_SCRIPTING_NS {
    void CppBehaviourInstance::OnBehaviourUnloaded(ManagerPasskey) {

    }

    void CppBehaviourInstance::OnBehaviourLoaded(ManagerPasskey) {

    }

    void CppBehaviourInstance::SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject) {

    }

    ModuleManager::~ModuleManager() {
        SRAssert2(m_behaviourInstances.empty(), "ModuleManager::~ModuleManager() : behaviours not unloaded!");

        for (auto&& module : m_modules) {
            if (!UnloadModule(module)) {
                SRHalt("ModuleManager::~ModuleManager() : failed to unload module!\n\tPath: " + module.GetPath().ToString());
            }
        }
        m_modules.clear();
    }

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

        if (!UnloadModule(module)) {
            SR_ERROR("ModuleManager::ReloadModule() : failed to unload module!\n\tPath: " + path.ToString());
            return false;
        }

        if (auto&& pLibraryHandle = LoadModule(path)) {
            module.SetModuleHandle(pLibraryHandle);
            InitModule(module);
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

        return pLibraryHandle;

        /*if (m_pScriptSystem->IsUseEngineSourcesAPI()) {
            return pLibraryHandle;
        }

        auto&& pModulesCountFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModulesCount");
        auto&& pModuleNameFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModuleName");
        auto&& pModuleVersionFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "GetScriptModuleCompilerVersion");
        auto&& pDestroyScriptCoreAPIFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "DestroyScriptCoreAPI");

        if (pModuleNameFunction && pModuleVersionFunction && pModulesCountFunction && pDestroyScriptCoreAPIFunction) {
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
        reinterpret_cast<void(*)()>(pDestroyScriptCoreAPIFunction)();
        SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle);
        return nullptr;*/
    }

    CppBehaviourInstance* ModuleManager::AllocateBehaviourInstance(const SR_UTILS_NS::StringAtom& behaviourName) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        auto&& pInstance = new CppBehaviourInstance();

        pInstance->SetBehaviourName(behaviourName, SR_UTILS_NS::Passkey<ModuleManager>(this));

        AllocateBehaviourInternalInstance(pInstance);

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
            FreeBehaviourInternalInstance(pInstance);
            delete *pIt;
            m_behaviourInstances.erase(pIt);
        }
        else {
            SRHalt("ModuleManager::FreeBehaviourInstance() : instance not found!");
        }
    }

    bool ModuleManager::InitModule(ScriptModule& module) {
        module.ResetBehaviours();

        auto&& pTestCallFunction = (void*(*)())SR_PLATFORM_NS::GetLibraryFunctionAddress(module.GetModuleHandle(), "TestFunction");
        if (pTestCallFunction) {
            pTestCallFunction();
        }
        return true;

        /*void* pGetBehaviourNameFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(
            module.GetModuleHandle(), "GetScriptModuleBehaviourName"
        );

        void* pInitScriptCoreAPIFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(
            module.GetModuleHandle(), "InitScriptCoreAPI"
        );

        void* pSetScriptFunctionFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(
            module.GetModuleHandle(), "SetScriptFunction"
        );

        const uint32_t behavioursCount = reinterpret_cast<uint32_t(*)(uint32_t)>(SR_PLATFORM_NS::GetLibraryFunctionAddress(
            module.GetModuleHandle(), "GetScriptModuleBehavioursCount"))(0);

        for (uint32_t i = 0; i < behavioursCount; ++i) {
            const std::string_view behaviourName = reinterpret_cast<const char* (*)(uint32_t, uint32_t)>(pGetBehaviourNameFunction)(0, i);
            module.AddBehaviour(behaviourName);
        }

        SpaRcleAPIRegister::Instance().RegisterAPI();

        const uint64_t countFunctions = SpaRcleAPIRegister::Instance().GetCountFunctions();

        reinterpret_cast<void(*)(uint64_t)>(pInitScriptCoreAPIFunction)(countFunctions);
        for (uint64_t i = 0; i < countFunctions; ++i) {
            void* pFunction = SpaRcleAPIRegister::Instance().GetFunction(i);
            reinterpret_cast<void(*)(uint64_t, void*)>(pSetScriptFunctionFunction)(i, pFunction);
        }

        for (auto&& pInstance : m_behaviourInstances) {
            // if (!pInstance->GetInstance()) {
            //     AllocateBehaviourInternalInstance(pInstance);
            // }
        }

        return true;*/
    }

    ScriptModule* ModuleManager::FindModule(SR_UTILS_NS::StringAtom moduleName) {
        auto&& pIt = std::ranges::find_if(m_modules, [&moduleName](const auto& module) {
            return module.GetModuleName() == moduleName;
        });
        return pIt != m_modules.end() ? &(*pIt) : nullptr;
    }

    bool ModuleManager::HasBehaviour(SR_UTILS_NS::StringAtom behaviourName) const {
        return std::ranges::any_of(m_modules, [&behaviourName](const auto& module) {
            return module.HasBehaviour(behaviourName);
        });
    }

    bool ModuleManager::UnloadModule(ScriptModule& module) {
        auto&& pLibraryHandle = module.GetModuleHandle();
        if (!pLibraryHandle) {
            return true;
        }

        for (auto&& pInstance : m_behaviourInstances) {
            if (pInstance->GetModuleName() == module.GetModuleName()) {
                FreeBehaviourInternalInstance(pInstance);
            }
        }

        //if (!m_pScriptSystem->IsUseEngineSourcesAPI()) {
        //    auto&& pDestroyScriptCoreAPI = SR_PLATFORM_NS::GetLibraryFunctionAddress(pLibraryHandle, "DestroyScriptCoreAPI");
        //    reinterpret_cast<void(*)()>(pDestroyScriptCoreAPI)();
        //}

        if (!SR_PLATFORM_NS::UnloadLibraryModule(pLibraryHandle)) {
            SRHalt("ModuleManager::UnloadModule() : failed to unload module! Something went wrong...\n\tPath: " + module.GetPath().ToString());
            return false;
        }
        else {
            SR_LOG("ModuleManager::UnloadModule() : module \"" + module.GetPath().ToString() + "\" unloaded.");
        }

        module.SetModuleHandle(nullptr);

        return true;
    }

    void ModuleManager::FreeBehaviourInternalInstance(CppBehaviourInstance* pInstance) {
        /*if (!m_pScriptSystem->IsUseEngineSourcesAPI() && pInstance->GetInstance()) {
            auto&& pModule = FindModule(pInstance->GetModuleName());
            if (pModule) {
                void* pFreeScriptBehaviourFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(pModule->GetModuleHandle(), "FreeScriptBehaviour");
                reinterpret_cast<void(*)(void*)>(pFreeScriptBehaviourFunction)(pInstance->GetInstance());
            }
            else {
                SRHalt("ModuleManager::FreeBehaviourInternalInstance() : module \"{}\" not found!", pInstance->GetModuleName());
            }
        }*/
        pInstance->SetModuleName(SR_UTILS_NS::StringAtom(), SR_UTILS_NS::Passkey<ModuleManager>(this));
        pInstance->OnBehaviourUnloaded(SR_UTILS_NS::Passkey<ModuleManager>(this));
        //pInstance->SetInstance(nullptr, SR_UTILS_NS::Passkey<ModuleManager>(this));
        //pInstance->SetModuleHandle(nullptr, SR_UTILS_NS::Passkey<ModuleManager>(this));
    }

    bool ModuleManager::AllocateBehaviourInternalInstance(CppBehaviourInstance* pInstance) {
        /*if (m_pScriptSystem->IsUseEngineSourcesAPI()) {
            return true;
        }

        const SR_UTILS_NS::StringAtom behaviourName = pInstance->GetBehaviourName();

        for (auto&& module : m_modules) {
            if (module.HasBehaviour(behaviourName)) {
                void* pAllocateBehaviourFunction = SR_PLATFORM_NS::GetLibraryFunctionAddress(module.GetModuleHandle(), "AllocateScriptBehaviour");
                void* pScriptBehaviour = reinterpret_cast<void*(*)(const char*)>(pAllocateBehaviourFunction)(behaviourName.c_str());

                if (!pScriptBehaviour) {
                    SRHalt("ModuleManager::AllocateBehaviourInternalInstance() : failed to allocate behaviour instance!\n\tBehaviour: {}", behaviourName);
                    delete pInstance;
                    return false;
                }

                pInstance->SetInstance(pScriptBehaviour, SR_UTILS_NS::Passkey<ModuleManager>(this));
                pInstance->SetModuleHandle(module.GetModuleHandle(), SR_UTILS_NS::Passkey<ModuleManager>(this));
                pInstance->SetModuleName(module.GetModuleName(), SR_UTILS_NS::Passkey<ModuleManager>(this));
                pInstance->OnBehaviourLoaded(SR_UTILS_NS::Passkey<ModuleManager>(this));

                if (auto&& reloadCallback = pInstance->GetReloadCallback()) {
                    reloadCallback();
                }

                return true;
            }
        }

        return false;*/
        return true;
    }
}