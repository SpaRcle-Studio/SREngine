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
