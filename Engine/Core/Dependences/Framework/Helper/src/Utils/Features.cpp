//
// Created by Monika on 13.01.2022.
//

#include <Utils/Features.h>
#include <Xml.h>

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

    bool Features::Reload(const std::string &path) {
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (!path.empty()) {
            if (!FileSystem::FileExists(path)) {
                SR_ERROR("Features::Reload() : file not found! Path: " + path);
                return false;
            }

            m_path = path;
        }

        m_features.clear();

        const auto& doc = Xml::Document::Load(m_path);
        if (const auto& features = doc.Root().GetNode("Features")) {
            for (const auto& group : features.GetNodes()) {
                for (const auto& feature : group.GetNodes()) {
                    SRVerifyFalse(Register(group.Name(), feature.Name(), feature.GetAttribute("Value").ToBool(false)));
                }
            }
        }
        else {
            SR_ERROR("Features::Reload() : error while loading file! Path: " + m_path);
            return false;
        }

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
        std::lock_guard<std::recursive_mutex> lock(m_mutex);

        if (auto pIt = m_features.find(name); pIt != m_features.end())
            return pIt->second;

        static FeatureGroup defaultFeature = FeatureGroup();
        return defaultFeature;
    }
}