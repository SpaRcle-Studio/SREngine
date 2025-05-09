

# File EvoScriptManager.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Scripting**](dir_8d890c1ced0da046da53f80c44d31720.md) **>** [**inc**](dir_7f135c995c1edef3d688ff3261945ab5.md) **>** [**Scripting**](dir_1d502c2700a8bda2469c0cfc127e6ee9.md) **>** [**Old**](dir_7c26f9091b44a892879dd4e8d1d7c144.md) **>** [**Impl**](dir_cd3992da172c967afbd6efc49fe8c3a7.md) **>** [**EvoScriptManager.h**](EvoScriptManager_8h.md)

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


