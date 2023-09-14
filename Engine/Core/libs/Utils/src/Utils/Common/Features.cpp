//
// Created by Monika on 13.01.2022.
//

#include <Utils/Common/Features.h>
#include <Utils/Xml.h>
#include <Utils/Types/Thread.h>

namespace SR_UTILS_NS {
    bool FeatureGroup::Register(const std::string &name, bool value) {
        if (m_values.count(name))
            return false;

        m_values[name] = value;

        return true;
    }

    bool FeatureGroup::Enabled(const std::string &name) const {
        if (auto pIt = m_values.find(name); pIt != m_values.end())
            return pIt->second;

        SR_WARN("FeatureGroup::Enabled() : feature \"" + name + "\" not found!");

        return false;
    }

    bool FeatureGroup::Enabled(const std::string &name, bool def) const {
        if (auto pIt = m_values.find(name); pIt != m_values.end())
            return pIt->second;

        return def;
    }

    bool Features::Enabled(const std::string &group, const std::string &name) const {
        return GetGroup(group).Enabled(name);
    }

    void Features::SetPath(const SR_UTILS_NS::Path& path) {
        SR_LOCK_GUARD

        if (path.Empty() || !path.Exists()) {
            SR_ERROR("Features::Reload() : file not found! \n\tPath: " + path.ToString());
            return;
        }

        m_path = path;
    }

    bool Features::Reload() {
        SR_LOCK_GUARD;
        SR_TRACY_ZONE;

        if (m_path.Empty()) {
            SR_ERROR("Features::Reload() : path is empty!");
            return false;
        }

        m_features.clear();

        const auto& doc = SR_XML_NS::Document::Load(m_path);
        if (const auto& features = doc.Root().GetNode("Features")) {
            for (const auto& group : features.GetNodes()) {
                for (const auto& feature : group.GetNodes()) {
                    SRVerifyFalse(!Register(group.Name(), feature.Name(), feature.GetAttribute("Value").ToBool(false)));
                }
            }
        }
        else {
            SR_ERROR("Features::Reload() : error while loading file! \n\tPath: " + m_path.ToString());
            return false;
        }

        SR_LOG("Features::Reload() : features successfully reloaded!");

        return true;
    }

    bool Features::Enabled(const std::string &name) const {
        return GetGroup("Common").Enabled(name);
    }

    bool Features::Enabled(const std::string &name, bool def) const {
        return GetGroup("Common").Enabled(name, def);
    }

    bool Features::Register(const std::string &group, const std::string &name, bool value) {
        if (auto pIt = m_features.find(group); pIt == m_features.end())
            m_features.insert(std::make_pair(group, FeatureGroup()));

        return m_features.at(group).Register(name, value);
    }

    const FeatureGroup& Features::GetGroup(const std::string &name) const {
        SR_LOCK_GUARD

        if (auto pIt = m_features.find(name); pIt != m_features.end())
            return pIt->second;

        static FeatureGroup defaultFeature = FeatureGroup();
        return defaultFeature;
    }
}