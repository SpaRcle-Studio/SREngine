//
// Created by Monika on 07.04.2025.
//

#include <Scripting/Cpp/ModuleManager.h>
#include <Scripting/Cpp/ScriptSystem.h>

#include <Utils/Events/Broadcaster.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/Common/StringAtomLiterals.h>

namespace SR_SCRIPTING_NS {
    void CppBehaviourInstance::OnBehaviourUnloaded(ManagerPasskey) {
        m_pBehaviour.AutoFree();
    }

    void CppBehaviourInstance::SetSceneObject(const SR_UTILS_NS::SceneObject::Ptr& pSceneObject) {
        if (m_pBehaviour) {
            m_pBehaviour->sceneObject = pSceneObject;

            if (pSceneObject && pSceneObject->GetSceneObjectType() == SR_UTILS_NS::SceneObjectType::GameObject) {
                m_pBehaviour->gameObject = pSceneObject.StaticCast<SR_UTILS_NS::GameObject>();
                m_pBehaviour->transform = m_pBehaviour->gameObject->GetTransform();
            }
            else {
                m_pBehaviour->gameObject = nullptr;
                m_pBehaviour->transform = nullptr;
            }
        }
    }

    bool CppBehaviourInstance::ExecuteInEditMode() const {
        return m_pBehaviour && m_pBehaviour->ExecuteInEditMode();
    }

    ModuleManager::~ModuleManager() {
        SRAssert2(m_behaviourInstances.empty(), "ModuleManager::~ModuleManager() : behaviours not unloaded!");

        for (auto&& module : m_modules) {
            if (!UnloadModule(module, false)) {
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

        if (!UnloadModule(module, true)) {
            SR_ERROR("ModuleManager::ReloadModule() : failed to unload module!\n\tPath: " + path.ToString());
            return false;
        }

        if (auto&& pLibraryHandle = LoadModule(path)) {
            module.SetModuleHandle(pLibraryHandle);
        }
        else {
            SR_ERROR("ModuleManager::ReloadModule() : failed to load module!\n\tPath: " + path.ToString());
            return false;
        }

        OnModuleLoaded(module);

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
    }

    CppBehaviourInstance* ModuleManager::AllocateBehaviourInstance(const SR_UTILS_NS::StringAtom& behaviourName) {
        SR_TRACY_ZONE;
        SR_LOCK_GUARD;

        auto&& pInstance = new CppBehaviourInstance();

        pInstance->SetBehaviourName(behaviourName, SR_UTILS_NS::PassKey<ModuleManager>(this));

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

    ScriptModule* ModuleManager::FindModule(SR_UTILS_NS::StringAtom moduleName) {
        auto&& pIt = std::ranges::find_if(m_modules, [&moduleName](const auto& module) {
            return module.GetModuleName() == moduleName;
        });
        return pIt != m_modules.end() ? &(*pIt) : nullptr;
    }

    bool ModuleManager::UnloadModule(ScriptModule& module, bool willBeReloaded) {
        auto&& pLibraryHandle = module.GetModuleHandle();
        if (!pLibraryHandle) {
            return true;
        }

        for (auto&& pInstance : m_behaviourInstances) {
            if (pInstance->GetModuleName() == module.GetModuleName()) {
                if (willBeReloaded && pInstance->GetPreReloadCallback()) {
                    pInstance->GetPreReloadCallback()();
                }
                FreeBehaviourInternalInstance(pInstance);
            }
        }

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
        pInstance->SetModuleName(SR_UTILS_NS::StringAtom(), SR_UTILS_NS::PassKey<ModuleManager>(this));
        pInstance->OnBehaviourUnloaded(SR_UTILS_NS::PassKey<ModuleManager>(this));
    }

    bool ModuleManager::AllocateBehaviourInternalInstance(CppBehaviourInstance* pInstance) {
        if (pInstance->IsValid()) {
            SRHalt("ModuleManager::AllocateBehaviourInternalInstance() : instance already allocated!");
            return false;
        }

        auto&& factory = SR_UTILS_NS::Factory::Instance();

        auto&& pTypeInfo = factory.GetTypeInfo(pInstance->GetBehaviourName());
        if (!pTypeInfo) {
            return false;
        }

        auto&& pMeta = pTypeInfo->metaGetter ? pTypeInfo->metaGetter() : nullptr;
        if (!pMeta) {
            return false;
        }

        static const auto metaName = SR_SCRIPTING_NS::CppBehaviour::GetMetaStatic()->GetFactoryName();
        if (!pMeta->IsInherited(metaName)) {
            return false;
        }

        CppBehaviour::Ptr pBehaviour = factory.Create<CppBehaviour>(pMeta->GetFactoryName());
        if (!pBehaviour) {
            return false;
        }

        pInstance->SetInstance(pBehaviour, SR_UTILS_NS::PassKey<ModuleManager>(this));
        pInstance->SetModuleName(pTypeInfo->moduleName, SR_UTILS_NS::PassKey<ModuleManager>(this));

        return true;
    }

    void ModuleManager::OnModuleLoaded(ScriptModule& module) {
        for (auto&& pInstance : m_behaviourInstances) {
            if (pInstance->IsValid()) {
                continue;
            }

            if (AllocateBehaviourInternalInstance(pInstance)) {
                if (pInstance->GetLoadedCallback()) {
                    pInstance->GetLoadedCallback()();
                }
            }
        }

        SR_UTILS_NS::Broadcaster::Instance().Broadcast(SR_UTILS_NS::Events::EVENT_ON_SCRIPT_MODULE_RELOADED_ID);
    }
}