//
// Created by Codex on 20.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_OBJECT_GRAPH_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_OBJECT_GRAPH_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptValueSerialization.h>

#include <angelscript.h>

namespace SR_SCRIPTING_NS {
    class AngelScriptObjectGraph {
    public:
        explicit AngelScriptObjectGraph(asIScriptObject* pRoot = nullptr);
        ~AngelScriptObjectGraph();
        AngelScriptObjectGraph(const AngelScriptObjectGraph&) = delete;
        AngelScriptObjectGraph& operator=(const AngelScriptObjectGraph&) = delete;
    };

    void SaveAngelScriptObject(const SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::ISerializer& serializer);
    bool LoadAngelScriptObject(SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::IDeserializer& deserializer);
}
#endif

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_OBJECT_GRAPH_H
