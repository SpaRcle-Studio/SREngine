//
// Created by Monika on 17.06.2022.
//

#include <Utils/Settings.h>

namespace SR_UTILS_NS {
    bool Settings::Load() {
        SR_LOCK_GUARD

        bool hasErrors = false;

        Path path = GetResourcePath();
        if (!path.IsAbs()) {
            path = GetAssociatedPath().Concat(path);
        }

        auto&& document = SR_XML_NS::Document::Load(path);
        if (!document.Valid()) {
            SR_ERROR("Settings::Load() : file not found! \n\tPath: " + path.ToString());
            return false;
        }

        if (auto&& settings = document.Root().GetNode("Settings")) {
            LoadSettings(settings);
        }
        else {
            SR_ERROR("Settings::Load() : \"Settings\" node not found! \n\tPath: " + path.ToString());
            return false;
        }

        return IResource::Load();
    }

    bool Settings::Unload() {
        SR_LOCK_GUARD

        ClearSettings();

        return IResource::Unload();
    }

    bool Settings::Reload() {
        SR_SCOPED_LOCK

        SR_LOG("Settings::Reload() : reloading \"" + std::string(GetResourceId()) + "\" settings...");

        m_loadState = LoadState::Reloading;

        bool hasErrors = false;

        hasErrors |= !Unload();
        hasErrors |= !Load();

        UpdateResources();

        return !hasErrors;
    }

    Path Settings::GetAssociatedPath() const {
        return ResourceManager::Instance().GetResPath();
    }

    bool Settings::Destroy() {
        return IResource::Destroy();
    }

    SR_XML_NS::Document Settings::LoadDocument() const {
        Path path = GetResourcePath();
        if (!path.IsAbs()) {
            path = GetAssociatedPath().Concat(path);
        }

        return std::move(SR_XML_NS::Document::Load(path));
    }
}

