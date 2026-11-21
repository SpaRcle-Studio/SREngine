//
// Created by Codex on 20.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_OBJECT_GRAPH_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_OBJECT_GRAPH_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)
#include <Scripting/AngelScript/AngelScriptValueSerialization.h>

#include <Utils/Types/FlatHashMap.h>

#include <angelscript.h>

namespace SR_SCRIPTING_NS {
    class AngelScriptBindings;
    struct AngelScriptValueSnapshot {
        const SR_UTILS_NS::Reflection::TypeInfo* pType = nullptr;
        SR_UTILS_NS::Reflection::Value scalar;
        SR_UTILS_NS::Vector<AngelScriptValueSnapshot> children;
        uint64_t objectId = 0;
        const void* pObjectType = nullptr;
        bool comparable = true;

        void Capture(const SR_UTILS_NS::Reflection::ValueRef& value, SR_HTYPES_NS::FlatHashMap<const void*, uint64_t>& objects);
        bool Matches(const SR_UTILS_NS::Reflection::ValueRef& value, SR_HTYPES_NS::FlatHashMap<const void*, uint64_t>& objects) const;
    };

    class AngelScriptObjectGraph {
    public:
        explicit AngelScriptObjectGraph(asIScriptObject* pRoot = nullptr);
        ~AngelScriptObjectGraph();
        void RegisterRoot(asIScriptObject* pSaved, asIScriptObject* pLoaded, uint64_t id);
        AngelScriptObjectGraph(const AngelScriptObjectGraph&) = delete;
        AngelScriptObjectGraph& operator=(const AngelScriptObjectGraph&) = delete;
    };

    void SaveAngelScriptObject(const SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::ISerializer& serializer);
    bool LoadAngelScriptObject(SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::IDeserializer& deserializer);
    bool PreloadAngelScriptValue(AngelScriptBindings* pBindings, asIScriptModule* pModule,
        const SR_UTILS_NS::String& declaration, SR_UTILS_NS::IDeserializer& deserializer);
}
#endif

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_OBJECT_GRAPH_H
