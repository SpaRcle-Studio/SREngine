//
// Created by Monika on 22.12.2022.
//

#include <Utils/World/SceneLogic.h>

#include <Utils/World/SceneDefaultLogic.h>
#include <Utils/World/SceneCubeChunkLogic.h>
#include <Utils/World/ScenePrefabLogic.h>

namespace SR_WORLD_NS {
    SceneLogic::SceneLogic(const SceneLogic::ScenePtr& pScene)
        : SR_HTYPES_NS::SafePtr<SceneLogic>(this)
        , m_scene(pScene)
    { }

    SceneLogic::Ptr SceneLogic::CreateByExt(const SceneLogic::ScenePtr& pScene, const std::string& ext) {
        if (ext == "scene") {
            return (new SceneCubeChunkLogic(pScene))->GetThis();
        }

        if (ext == SR_UTILS_NS::Prefab::EXTENSION) {
            return (new ScenePrefabLogic(pScene))->GetThis();
        }

        SRHalt("SceneLogic::CreateByExt() : unknown extension! Create default...\n\tExtension: " + ext);

        return (new SceneDefaultLogic(pScene))->GetThis();
    }

    bool SceneLogic::Save(const Path& path) {
        auto&& documentXml = SR_XML_NS::Document::New();
        auto&& settingsXml = documentXml.Root().AppendNode("Settings");

        auto&& stringsXml = settingsXml.AppendNode("Strings");
        for (auto&& [name, value] : m_scene->GetDataStorage().GetValues<std::string>()) {
            stringsXml.AppendNode(name).AppendAttribute(value);
        }

        auto&& pathsXml = settingsXml.AppendNode("Paths");
        for (auto&& [name, value] : m_scene->GetDataStorage().GetValues<SR_UTILS_NS::Path>()) {
            pathsXml.AppendNode(name).AppendAttribute(value);
        }

        auto&& seetingsPath = path.Concat("data/settings.xml");
        if (!documentXml.Save(seetingsPath)) {
            SR_ERROR("SceneLogic::Save() : failed save settings!\n\tPath: " + seetingsPath.ToStringRef());
            return false;
        }

        return true;
    }

    bool SceneLogic::Load(const Path& path) {
        return true;
    }
}
