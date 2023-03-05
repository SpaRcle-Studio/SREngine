//
// Created by Monika on 02.03.2023.
//

#ifndef SRENGINE_EVOSCRIPTMANAGER_H
#define SRENGINE_EVOSCRIPTMANAGER_H

#include <Utils/Types/Map.h>
#include <Scripting/Impl/EvoCompiler.h>
#include <Scripting/ScriptHolder.h>

namespace SR_SCRIPTING_NS {
    class EvoScriptManager : public SR_UTILS_NS::Singleton<EvoScriptManager> {
        friend class SR_UTILS_NS::Singleton<EvoScriptManager>;
        using ScriptPtr = ScriptHolder::Ptr;
        using ScirptsMap = ska::flat_hash_map<std::string, ScriptPtr>;
    public:
        SR_NODISCARD ScriptPtr Load(const SR_UTILS_NS::Path& localPath);
        SR_NODISCARD bool ReloadScript(const SR_UTILS_NS::Path& localPath);

        void Update(float_t dt, bool force);

    private:
        ScirptsMap m_scripts;
        std::optional<ScirptsMap::iterator> m_checkIterator;

    };
}

#endif //SRENGINE_EVOSCRIPTMANAGER_H
