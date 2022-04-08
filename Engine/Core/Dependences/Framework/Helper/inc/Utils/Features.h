//
// Created by Monika on 10.01.2022.
//

#ifndef SRENGINE_FEATURES_H
#define SRENGINE_FEATURES_H

#include <Utils/Singleton.h>

namespace Framework::Helper {
    class Features;

    class FeatureGroup {
        friend class Features;
    public:
        [[nodiscard]] bool Enabled(const std::string& name) const;
        [[nodiscard]] bool Enabled(const std::string& name, bool def) const;

    private:
        bool Register(const std::string& name, bool value);

    private:
        std::unordered_map<std::string, bool> m_values;

    };

    class Features : public Helper::Singleton<Features> {
        friend class Helper::Singleton<Features>;
    private:
        ~Features() override = default;

    public:
        bool Reload(const std::string& path = "");
        [[nodiscard]] bool Enabled(const std::string& name) const;
        [[nodiscard]] bool Enabled(const std::string& name, bool def) const;
        [[nodiscard]] bool Enabled(const std::string& group, const std::string& name) const;

    private:
        [[nodiscard]] const FeatureGroup& GetGroup(const std::string& name) const;
        bool Register(const std::string& group, const std::string& name, bool value);

    private:

        std::unordered_map<std::string, FeatureGroup> m_features;
        std::string m_path;
        mutable std::recursive_mutex m_mutex;

    };
}

#endif //SRENGINE_FEATURES_H
