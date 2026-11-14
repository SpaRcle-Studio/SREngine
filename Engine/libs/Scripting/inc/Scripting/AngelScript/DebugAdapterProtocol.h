//
// Created by Codex on 14.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_DEBUG_ADAPTER_PROTOCOL_H
#define SR_ENGINE_SCRIPTING_DEBUG_ADAPTER_PROTOCOL_H

#include <Scripting/stdInclude.h>
#include <Utils/Serialization/JsonSerialization.h>

namespace SR_SCRIPTING_NS::DebugAdapterProtocol {
    SR_UTILS_NS::SerializationNode Object(const char* pName = "dap");
    SR_UTILS_NS::SerializationNode Array(const char* pName);
    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, const SR_UTILS_NS::String& value);
    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, const char* pValue);
    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, int64_t value);
    inline void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, int32_t value) {
        Set(node, pName, static_cast<int64_t>(value));
    }
    inline void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, uint32_t value) {
        Set(node, pName, static_cast<int64_t>(value));
    }
    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, bool value);
    const SR_UTILS_NS::SerializationNode& Get(const SR_UTILS_NS::SerializationNode& node, const char* pName);
    SR_UTILS_NS::String Text(const SR_UTILS_NS::SerializationNode& node, const char* pName);
    int64_t Integer(const SR_UTILS_NS::SerializationNode& node, const char* pName, int64_t fallback = 0);
    bool Boolean(const SR_UTILS_NS::SerializationNode& node, const char* pName, bool fallback = false);
    bool Parse(const SR_UTILS_NS::String& bytes, SR_UTILS_NS::SerializationNode& node);
    SR_UTILS_NS::String Serialize(const SR_UTILS_NS::SerializationNode& node);
}

#endif
