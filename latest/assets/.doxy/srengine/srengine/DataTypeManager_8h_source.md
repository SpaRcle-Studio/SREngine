

# File DataTypeManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**SRLM**](dir_a6f28b551a04c8f6c9ec3f9b059c2feb.md) **>** [**DataTypeManager.h**](DataTypeManager_8h.md)

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


