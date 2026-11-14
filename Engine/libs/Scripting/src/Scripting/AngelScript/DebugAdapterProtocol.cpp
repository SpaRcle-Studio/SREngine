//
// Created by Codex on 14.11.2026.
//

#include <Scripting/AngelScript/DebugAdapterProtocol.h>

#if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
namespace SR_SCRIPTING_NS::DebugAdapterProtocol {
    SR_UTILS_NS::SerializationNode Object(const char* pName) {
        return {SR_UTILS_NS::SerializationId::CreateFromCStr(pName), SR_UTILS_NS::SerializationDataType::Object};
    }

    SR_UTILS_NS::SerializationNode Array(const char* pName) {
        return {SR_UTILS_NS::SerializationId::CreateFromCStr(pName), SR_UTILS_NS::SerializationDataType::Array};
    }

    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, const SR_UTILS_NS::String& value) {
        auto child = Object(pName);
        child.type = SR_UTILS_NS::SerializationDataType::String;
        child.string = value;
        node.children.emplace_back(std::move(child));
    }

    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, const char* pValue) {
        Set(node, pName, SR_UTILS_NS::String(pValue ? pValue : ""));
    }

    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, int64_t value) {
        auto child = Object(pName);
        child.type = SR_UTILS_NS::SerializationDataType::Integer;
        child.data.integer = value;
        node.children.emplace_back(std::move(child));
    }

    void Set(SR_UTILS_NS::SerializationNode& node, const char* pName, bool value) {
        auto child = Object(pName);
        child.type = SR_UTILS_NS::SerializationDataType::Boolean;
        child.data.boolean = value;
        node.children.emplace_back(std::move(child));
    }

    const SR_UTILS_NS::SerializationNode& Get(const SR_UTILS_NS::SerializationNode& node, const char* pName) {
        const auto id = SR_UTILS_NS::SerializationId::CreateFromCStr(pName);
        for (auto&& child : node.children) {
            if (child.id == id) {
                return child;
            }
        }

        static const SR_UTILS_NS::SerializationNode empty;
        return empty;
    }

    SR_UTILS_NS::String Text(const SR_UTILS_NS::SerializationNode& node, const char* pName) {
        return Get(node, pName).string;
    }

    int64_t Integer(const SR_UTILS_NS::SerializationNode& node, const char* pName, int64_t fallback) {
        auto&& child = Get(node, pName);
        return child.type == SR_UTILS_NS::SerializationDataType::Integer ? child.data.integer : fallback;
    }

    bool Boolean(const SR_UTILS_NS::SerializationNode& node, const char* pName, bool fallback) {
        auto&& child = Get(node, pName);
        return child.type == SR_UTILS_NS::SerializationDataType::Boolean ? child.data.boolean : fallback;
    }

    bool Parse(const SR_UTILS_NS::String& bytes, SR_UTILS_NS::SerializationNode& node) {
        SR_UTILS_NS::JsonDeserializer parser;
        const auto wrapped = SR_UTILS_NS::String("{\"dap\":") + bytes + "}";
        if (!parser.LoadFromStringView(SR_UTILS_NS::StringView(wrapped))) {
            return false;
        }

        node = parser.GetCurrentNode().DetachAllocator();
        return true;
    }

    SR_UTILS_NS::String Serialize(const SR_UTILS_NS::SerializationNode& node) {
        SR_UTILS_NS::JsonSerializer writer;
        writer.SetPrettyPrint(false);
        writer.GetCurrentNode() = node;
        writer.GetCurrentNode().id = SR_UTILS_NS::SerializationId::Create("dap");
        const auto wrapped = writer.ToString();
        return wrapped.substr(7, wrapped.size() - 8);
    }
}
#endif
