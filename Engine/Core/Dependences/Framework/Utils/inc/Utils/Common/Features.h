//
// Created by Monika on 10.01.2022.
//

#ifndef SRENGINE_FEATURES_H
#define SRENGINE_FEATURES_H

#include <Utils/Common/Singleton.h>

namespace SR_UTILS_NS {
    class Features;

    class SR_DLL_EXPORT FeatureGroup {
        friend class Features;
    public:
        SR_NODISCARD bool Enabled(const std::string& name) const;
        SR_NODISCARD bool Enabled(const std::string& name, bool def) const;

    private:
        bool Register(const std::string& name, bool value);

    private:
        std::unordered_map<std::string, bool> m_values;

    };

    class SR_DLL_EXPORT Features : public Singleton<Features> {
        friend class Singleton<Features>;
    private:
        ~Features() override = default;

    public:
        bool Reload(const std::string& path = "");
        SR_NODISCARD bool Enabled(const std::string& name) const;
        SR_NODISCARD bool Enabled(const std::string& name, bool def) const;
        SR_NODISCARD bool Enabled(const std::string& group, const std::string& name) const;

    private:
        SR_NODISCARD const FeatureGroup& GetGroup(const std::string& name) const;
        bool Register(const std::string& group, const std::string& name, bool value);

    private:
        std::unordered_map<std::string, FeatureGroup> m_features;
        std::string m_path;

    };
}

#endif //SRENGINE_FEATURES_H
