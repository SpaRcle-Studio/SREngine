//
// Created by Monika on 26.08.2023.
//

#ifndef SRENGINE_DATATYPEMANAGER_H
#define SRENGINE_DATATYPEMANAGER_H

#include <Utils/SRLM/Utils.h>

namespace SR_SRLM_NS {
    class DataType;
    class DataTypeStruct;

    class DataTypeManager : public SR_UTILS_NS::Singleton<DataTypeManager> {
        friend class SR_UTILS_NS::Singleton<DataTypeManager>;
        using Hash = uint64_t;
        using Structs = std::unordered_map<Hash, DataTypeStruct*>;
    public:
        SR_NODISCARD const std::string& HashToString(Hash hash) const;
        SR_NODISCARD DataType* CreateByName(Hash hashName);
        SR_NODISCARD DataType* CreateByName(const std::string& name);
        SR_NODISCARD const Structs& GetStructs() const { return m_structs; }

    private:
        void InitSingleton() override;
        void OnSingletonDestroy() override;
        void ReloadSettings();
        void Clear();

    private:
        std::unordered_map<Hash, std::string> m_strings;
        Structs m_structs;
        SR_UTILS_NS::FileWatcher::Ptr m_watcher;

    };
}

#endif //SRENGINE_DATATYPEMANAGER_H
