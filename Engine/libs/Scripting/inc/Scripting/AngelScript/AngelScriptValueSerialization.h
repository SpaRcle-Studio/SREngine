//
// Created by Codex on 13.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_VALUE_SERIALIZATION_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_VALUE_SERIALIZATION_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/stdInclude.h>

#include <Utils/Reflection/Value.h>
#include <Utils/Serialization/Serializer.h>
#include <Utils/Serialization/Deserializer.h>

namespace SR_SCRIPTING_NS {
    bool CanSerializeAngelScriptValue(const SR_UTILS_NS::Reflection::TypeInfo& type);
    void SaveAngelScriptValue(const SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::ISerializer& serializer);
    bool LoadAngelScriptValue(SR_UTILS_NS::Reflection::Value& value, SR_UTILS_NS::IDeserializer& deserializer);
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_VALUE_SERIALIZATION_H
