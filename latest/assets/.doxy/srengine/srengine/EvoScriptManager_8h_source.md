

# File EvoScriptManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Scripting**](dir_5986759bc4f73c4edd437f1c9a37190d.md) **>** [**inc**](dir_4119b3a7205d9e389f51f0e00ee95b80.md) **>** [**Scripting**](dir_b374709534ecc2762456a7a7dcb6760c.md) **>** [**Old**](dir_b244a4bff51c9cedd445e3d7c2557c90.md) **>** [**Impl**](dir_4eaf059bf86cb1a50633501e0fe5274e.md) **>** [**EvoScriptManager.h**](EvoScriptManager_8h.md)

[Go to the documentation of this file](EvoScriptManager_8h.md)


```C++
//
// Created by Monika on 02.03.2023.
//

#ifndef SR_ENGINE_EVOSCRIPTMANAGER_H
#define SR_ENGINE_EVOSCRIPTMANAGER_H

#include <Utils/Types/Map.h>
#include <Scripting/Impl/EvoCompiler.h>
#include <Scripting/ScriptHolder.h>

namespace SR_SCRIPTING_NS {
    #define SR_EVO_SCRIPT_MANAGER_LOCK_CONTEXT                               \
        auto&& mutex_1 = SR_UTILS_NS::ResourceManager::GetMutex();           \
        auto&& mutex_2 = SR_SCRIPTING_NS::EvoScriptManager::GetMutex();      \
        std::lock(mutex_1, mutex_2);                                         \
        std::lock_guard<std::recursive_mutex> lk1(mutex_1, std::adopt_lock); \
        std::lock_guard<std::recursive_mutex> lk2(mutex_2, std::adopt_lock); \

    class EvoScriptManager : public SR_UTILS_NS::Singleton<EvoScriptManager> {
        SR_REGISTER_SINGLETON(EvoScriptManager);
        using ScriptPtr = ScriptHolder::Ptr;
        using ScirptsMap = ska::flat_hash_map<std::string, ScriptPtr>;
    public:
        SR_NODISCARD ScriptPtr Load(const SR_UTILS_NS::Path& localPath);
        SR_NODISCARD bool ReloadScript(const SR_UTILS_NS::Path& localPath);

        void Update(bool force);

        void OnSingletonDestroy() override;

        SR_UTILS_NS::Path FindMSVCCompiler() const;

    private:
        ScirptsMap m_scripts;
        std::optional<ScirptsMap::iterator> m_checkIterator;

        SR_UTILS_NS::Path m_compilerPath;

    };
}

#endif //SR_ENGINE_EVOSCRIPTMANAGER_H
```


