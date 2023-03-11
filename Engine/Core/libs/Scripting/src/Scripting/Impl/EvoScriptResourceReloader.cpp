//
// Created by Monika on 11.03.2023.
//

#include <Utils/Common/Features.h>

#include <Scripting/Impl/EvoScriptResourceReloader.h>
#include <Scripting/Impl/EvoScriptManager.h>
#include <Scripting/Impl/EvoBehaviour.h>

namespace SR_SCRIPTING_NS {
    bool EvoScriptResourceReloader::Reload(const SR_UTILS_NS::Path& path, SR_UTILS_NS::ResourceInfo* pResourceInfo) {
        if (SR_UTILS_NS::Features::Instance().Enabled("CompilePDB", false)) {
            SR_WARN("EvoScriptResourceReloader::Reload() : PDB compilation enabled! Script reloading impossible.");
            return false;
        }

        std::vector<std::pair<Behaviour*, SR_HTYPES_NS::DataStorage>> stashedProps;

        stashedProps.reserve(pResourceInfo->m_loaded.size());

        for (auto&& pResource : pResourceInfo->m_loaded) {
            if (!IsResourceSuitableForReload(pResource)) {
                continue;
            }

            if (auto&& pBehaviour = dynamic_cast<Behaviour*>(pResource)) {
                stashedProps.emplace_back(std::make_pair(pBehaviour, pBehaviour->Stash()));
            }

            pResource->Unload();
        }

        if (!EvoScriptManager::Instance().ReloadScript(path)) {
            SR_ERROR("EvoScriptResourceReloader::Reload() : failed to reload script!\n\tPath: " + path.ToStringRef());
            return false;
        }

        for (auto&& pResource : pResourceInfo->m_loaded) {
            if (!IsResourceSuitableForReload(pResource)) {
                continue;
            }

            pResource->Load();
        }

        for (auto&& [pBehaviour, stash] : stashedProps) {
            pBehaviour->ApplyStash(stash);
        }

        return true;
    }
}
