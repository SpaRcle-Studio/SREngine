

# File DataTypeManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**SRLM**](dir_ccfa529a2c413666958bcf1b1fc32cf9.md) **>** [**DataTypeManager.h**](DataTypeManager_8h.md)

[Go to the documentation of this file](DataTypeManager_8h.md)


```C++
//
// Created by Monika on 26.08.2023.
//

#ifndef SR_ENGINE_DATATYPEMANAGER_H
#define SR_ENGINE_DATATYPEMANAGER_H

#include <Utils/SRLM/Utils.h>

namespace SR_SRLM_NS {
    class DataType;
    class DataTypeStruct;

    class DataTypeManager : public SR_UTILS_NS::Singleton<DataTypeManager> {
        SR_REGISTER_SINGLETON(DataTypeManager)
        using Hash = uint64_t;
        using Structs = std::unordered_map<Hash, DataTypeStruct*>;
    public:
        SR_NODISCARD bool IsStructExists(Hash hashName) const;
        SR_NODISCARD DataType* CreateByName(Hash hashName);
        SR_NODISCARD DataType* CreateByName(const std::string& name);
        SR_NODISCARD const DataTypeStruct* GetStruct(Hash hashName) const;
        SR_NODISCARD const Structs& GetStructs() const { return m_structs; }

    private:
        void InitSingleton() override;
        void OnSingletonDestroy() override;
        void ReloadSettings();
        void Clear();

    private:
        Structs m_structs;
        SR_UTILS_NS::FileWatcher::Ptr m_watcher;

    };
}

#endif //SR_ENGINE_DATATYPEMANAGER_H
```


