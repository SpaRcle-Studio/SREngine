//
// Created by Monika on 10.01.2022.
//

#ifndef SR_ENGINE_FEATURES_H
#define SR_ENGINE_FEATURES_H

#include <Utils/Common/Singleton.h>
#include <Utils/FileSystem/Path.h>

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
        SR_REGISTER_SINGLETON(Features);
    private:
        ~Features() override = default;

    public:
        bool Reload();

        void SetPath(const SR_UTILS_NS::Path& path);

        SR_NODISCARD bool Enabled(const std::string& name) const;
        SR_NODISCARD bool Enabled(const std::string& name, bool def) const;
        SR_NODISCARD bool Enabled(const std::string& group, const std::string& name) const;

    private:
        SR_NODISCARD const FeatureGroup& GetGroup(const std::string& name) const;
        bool Register(const std::string& group, const std::string& name, bool value);

    private:
        std::unordered_map<std::string, FeatureGroup> m_features;
        Path m_path;

    };
}

#endif //SR_ENGINE_FEATURES_H
