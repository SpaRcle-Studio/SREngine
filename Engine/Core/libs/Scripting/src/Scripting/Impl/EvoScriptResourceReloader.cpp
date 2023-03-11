//
// Created by Monika on 11.03.2023.
//

#include <Utils/Common/Features.h>
#include <Utils/Types/Marshal.h>

#include <Scripting/Impl/EvoScriptResourceReloader.h>
#include <Scripting/Impl/EvoScriptManager.h>
#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    bool EvoScriptResourceReloader::Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) {
        SR_SCOPED_LOCK

        if (SR_UTILS_NS::Features::Instance().Enabled("CompilePDB", false)) {
            SR_WARN("EvoScriptResourceReloader::Reload() : PDB compilation enabled! Script reloading impossible.");
            return false;
        }

        StashedProperties stashedProps;

        stashedProps.reserve(pResourceInfo->m_loaded.size());

        for (auto&& pResource : pResourceInfo->m_loaded) {
            if (!IsResourceSuitableForReload(pResource)) {
                continue;
            }

            if (auto&& pBehaviour = dynamic_cast<Behaviour*>(pResource)) {
                auto&& pMarshal = new SR_HTYPES_NS::Marshal();
                auto&& properties = pBehaviour->GetProperties();

                pMarshal->Write<uint64_t>(properties.size());

                for (auto&& propertyName : properties) {
                    pMarshal->Write<std::string>(propertyName);
                    pMarshal->Write<std::any>(pBehaviour->GetProperty(propertyName));
                }

                pMarshal->SetPosition(0);
                stashedProps.emplace_back(std::make_pair(pBehaviour, pMarshal));
            }

            pResource->Unload();
        }

        if (!EvoScriptManager::Instance().ReloadScript(path)) {
            SR_ERROR("EvoScriptResourceReloader::Reload() : failed to reload script!\n\tPath: " + path.ToStringRef());
            FreeStashedProperties(stashedProps);
            return false;
        }

        for (auto&& [pBehaviour, pMarshal] : stashedProps) {
            pBehaviour->Load();

            const uint64_t countProperties = pMarshal->Read<uint64_t>();
            for (uint64_t i = 0; i < countProperties; ++i) {
                auto&& name = pMarshal->Read<std::string>();
                auto&& value = pMarshal->Read<std::any>();
                pBehaviour->SetProperty(name, value);
            }

            pBehaviour->PostLoad();
        }

        FreeStashedProperties(stashedProps);

        return true;
    }

    void EvoScriptResourceReloader::FreeStashedProperties(const EvoScriptResourceReloader::StashedProperties& properties) {
        for (auto&& [pBehaviour, pMarshal] : properties) {
            delete pMarshal;
        }
    }
}
