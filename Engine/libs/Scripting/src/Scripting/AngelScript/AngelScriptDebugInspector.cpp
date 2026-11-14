//
// Created by Codex on 14.11.2026.
//

#include <Scripting/AngelScript/AngelScriptDebugInspector.h>

#if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
#include <Scripting/AngelScript/AngelScriptBindings.h>
#include <Utils/FileSystem/VFS.h>
#include <Utils/Types/SharedPtr.h>

namespace SR_SCRIPTING_NS {
    AngelScriptDebugInspector::~AngelScriptDebugInspector() {
        End();
    }

    void AngelScriptDebugInspector::Begin(asIScriptContext* pContext, bool linesStartAt1, bool columnsStartAt1) {
        End();
        m_pContext = pContext;
        m_linesStartAt1 = linesStartAt1;
        m_columnsStartAt1 = columnsStartAt1;
        m_references.clear();
        m_frameBase = m_nextId;
        m_nextId += pContext->GetCallstackSize();
    }

    void AngelScriptDebugInspector::End() {
        m_pContext = nullptr;
        m_references.clear();
        for (uint64_t i = m_nativeReferences.size(); i > 0; --i) {
            delete m_nativeReferences[i - 1];
        }
        m_nativeReferences.clear();
    }

    bool AngelScriptDebugInspector::HasFrame(int64_t frame) const {
        return m_pContext && frame >= m_frameBase && frame < m_frameBase + m_pContext->GetCallstackSize();
    }

    bool AngelScriptDebugInspector::HasReference(int64_t reference) const {
        for (auto&& item : m_references) {
            if (item.id == reference) {
                return true;
            }
        }
        return false;
    }

    int64_t AngelScriptDebugInspector::AddReference(Reference::Kind kind, uint32_t frame, void* pObject) {
        for (auto&& item : m_references) {
            if (item.kind == kind && item.frame == frame && item.pObject == pObject) {
                return item.id;
            }
        }
        const auto id = m_nextId++;
        m_references.emplace_back(Reference{id, kind, frame, pObject});
        return id;
    }

    SR_UTILS_NS::String AngelScriptDebugInspector::SourcePath(const char* pSection) {
        if (!pSection || pSection[0] == '<') {
            return {};
        }
        SR_UTILS_NS::Path path(pSection);
        if (!path.IsAbs() && !SR_UTILS_NS::VFS::Instance().ResolvePath(path, SR_UTILS_NS::FileMode::Read)) {
            return {};
        }
        path.Normalize();
        return path.ToStringRef();
    }

    SR_UTILS_NS::SerializationNode AngelScriptDebugInspector::StackTrace(int64_t start, int64_t levels) {
        auto body = DebugAdapterProtocol::Object("body");
        auto frames = DebugAdapterProtocol::Array("stackFrames");
        const auto total = static_cast<int64_t>(m_pContext->GetCallstackSize());
        start = SR_MIN(start, total);
        const auto end = levels > 0 ? SR_MIN(total, start + SR_MIN(levels, total)) : total;
        for (int64_t i = start; i < end; ++i) {
            auto&& pFunction = m_pContext->GetFunction(static_cast<uint32_t>(i));
            const char* pSection = nullptr;
            int32_t column = 0;
            const auto line = m_pContext->GetLineNumber(static_cast<uint32_t>(i), &column, &pSection);
            auto frame = DebugAdapterProtocol::Object();
            DebugAdapterProtocol::Set(frame, "id", m_frameBase + i);
            DebugAdapterProtocol::Set(frame, "name", pFunction ? pFunction->GetDeclaration() : "<native>");
            DebugAdapterProtocol::Set(frame, "line", SR_MAX(0, line - (m_linesStartAt1 ? 0 : 1)));
            DebugAdapterProtocol::Set(frame, "column", SR_MAX(0, column - (m_columnsStartAt1 ? 0 : 1)));
            const auto path = SourcePath(pSection);
            if (!path.empty()) {
                auto source = DebugAdapterProtocol::Object("source");
                DebugAdapterProtocol::Set(source, "name", pSection);
                DebugAdapterProtocol::Set(source, "path", path);
                frame.children.emplace_back(std::move(source));
            }
            frames.children.emplace_back(std::move(frame));
        }
        body.children.emplace_back(std::move(frames));
        DebugAdapterProtocol::Set(body, "totalFrames", total);
        return body;
    }

    SR_UTILS_NS::SerializationNode AngelScriptDebugInspector::Scopes(int64_t frame) {
        auto body = DebugAdapterProtocol::Object("body");
        auto scopes = DebugAdapterProtocol::Array("scopes");
        const auto level = static_cast<uint32_t>(frame - m_frameBase);
        for (uint32_t i = 0; i < 2; ++i) {
            auto scope = DebugAdapterProtocol::Object();
            DebugAdapterProtocol::Set(scope, "name", i == 0 ? "Locals" : "Globals");
            DebugAdapterProtocol::Set(scope, "presentationHint", i == 0 ? "locals" : "globals");
            DebugAdapterProtocol::Set(scope, "variablesReference", AddReference(
                i == 0 ? Reference::Kind::Locals : Reference::Kind::Globals, level));
            DebugAdapterProtocol::Set(scope, "expensive", false);
            scopes.children.emplace_back(std::move(scope));
        }
        body.children.emplace_back(std::move(scopes));
        return body;
    }

    SR_UTILS_NS::SerializationNode AngelScriptDebugInspector::Value(const char* pName, void* pAddress, int32_t typeId) {
        auto value = DebugAdapterProtocol::Object();
        DebugAdapterProtocol::Set(value, "name", pName);
        auto&& pEngine = m_pContext->GetEngine();
        DebugAdapterProtocol::Set(value, "type", pEngine->GetTypeDeclaration(typeId, true));
        SR_UTILS_NS::String text = "<unavailable>";
        int64_t reference = 0;
        if (pAddress && (typeId & asTYPEID_OBJHANDLE)) {
            pAddress = *static_cast<void**>(pAddress);
            if (!pAddress) {
                text = "null";
            }
        }

        if (pAddress) {
            switch (typeId) {
                case asTYPEID_BOOL:
                    text = *static_cast<bool*>(pAddress) ? "true" : "false";
                    break;
                case asTYPEID_INT8:
                    text = "{}"_format(*static_cast<int8_t*>(pAddress));
                    break;
                case asTYPEID_INT16:
                    text = "{}"_format(*static_cast<int16_t*>(pAddress));
                    break;
                case asTYPEID_INT32:
                    text = "{}"_format(*static_cast<int32_t*>(pAddress));
                    break;
                case asTYPEID_INT64:
                    text = "{}"_format(*static_cast<int64_t*>(pAddress));
                    break;
                case asTYPEID_UINT8:
                    text = "{}"_format(*static_cast<uint8_t*>(pAddress));
                    break;
                case asTYPEID_UINT16:
                    text = "{}"_format(*static_cast<uint16_t*>(pAddress));
                    break;
                case asTYPEID_UINT32:
                    text = "{}"_format(*static_cast<uint32_t*>(pAddress));
                    break;
                case asTYPEID_UINT64:
                    text = "{}"_format(*static_cast<uint64_t*>(pAddress));
                    break;
                case asTYPEID_FLOAT:
                    text = "{}"_format(*static_cast<float_t*>(pAddress));
                    break;
                case asTYPEID_DOUBLE:
                    text = "{}"_format(*static_cast<double_t*>(pAddress));
                    break;
                default: {
                    if (typeId & asTYPEID_SCRIPTOBJECT) {
                        text = "{...}";
                        reference = AddReference(Reference::Kind::Object, 0, pAddress);
                    }
                    else if (!(typeId & asTYPEID_MASK_OBJECT)) {
                        text = "{}"_format(*static_cast<int32_t*>(pAddress));
                    }
                    else {
                        const auto bareType = typeId & ~(asTYPEID_OBJHANDLE | asTYPEID_HANDLETOCONST);
                        auto&& pType = pEngine->GetTypeInfoById(bareType);
                        if (pType && pType->GetUserData(AngelScriptBindings::NativeTypeUserData)) {
                            auto&& pNative = static_cast<AngelScriptNativeObject*>(pAddress);
                            return NativeValue(pName, pNative->value.Ref(), pNative);
                        }
                        text = "<native object>";
                    }
                    break;
                }
            }
        }
        DebugAdapterProtocol::Set(value, "value", text);
        DebugAdapterProtocol::Set(value, "variablesReference", reference);
        return value;
    }

    SR_UTILS_NS::SerializationNode AngelScriptDebugInspector::NativeValue(const char* pName,
        SR_UTILS_NS::Reflection::Value value, AngelScriptNativeObject* pAnchor, NativeReference* pParent)
    {
        auto result = DebugAdapterProtocol::Object();
        DebugAdapterProtocol::Set(result, "name", pName);
        const auto type = pAnchor && pAnchor->pBindings ? pAnchor->pBindings->Declaration(value.GetTypeInfo()) : SR_UTILS_NS::String();
        DebugAdapterProtocol::Set(result, "type", type.empty() ? SR_UTILS_NS::String(value.GetTypeInfo().detailedType) : type);
        int64_t reference = 0;
        SR_UTILS_NS::String text = "<destroyed>";
        if ((!pAnchor || pAnchor->IsAlive()) && (!pParent || IsNativeAlive(pParent))) {
            text = AngelScriptDebugNativeValues::Summary(value);
            if (AngelScriptDebugNativeValues::HasChildren(value)) {
                NativeReference* pNative = nullptr;
                for (auto&& pExisting : m_nativeReferences) {
                    if (pExisting->pAnchor == pAnchor && pExisting->pParent == pParent && pExisting->value.Data() == value.Data() &&
                        pExisting->value.GetTypeInfo() == value.GetTypeInfo()) {
                        pNative = pExisting;
                        break;
                    }
                }
                if (!pNative) {
                    pNative = new NativeReference();
                    pNative->value = std::move(value);
                    pNative->pAnchor = pAnchor;
                    pNative->pParent = pParent;
                    m_nativeReferences.emplace_back(pNative);
                }
                reference = AddReference(Reference::Kind::Native, 0, pNative);
            }
        }
        DebugAdapterProtocol::Set(result, "value", text);
        DebugAdapterProtocol::Set(result, "variablesReference", reference);
        return result;
    }

    bool AngelScriptDebugInspector::IsNativeAlive(const NativeReference* pReference) const {
        if (pReference->pParent && !IsNativeAlive(pReference->pParent)) {
            return false;
        }
        if (pReference->pAnchor && !pReference->pAnchor->IsAlive()) {
            return false;
        }
        return !pReference->value.IsSharedPtr() || pReference->value.GetSharedPtrBase()->Valid();
    }

    SR_UTILS_NS::SerializationNode AngelScriptDebugInspector::Variables(int64_t reference, int64_t start, int64_t count) {
        auto body = DebugAdapterProtocol::Object("body");
        auto variables = DebugAdapterProtocol::Array("variables");
        Reference target;
        for (auto&& item : m_references) {
            if (item.id == reference) {
                target = item;
                break;
            }
        }

        if (target.kind == Reference::Kind::Locals) {
            auto&& pThis = m_pContext->GetThisPointer(target.frame);
            if (pThis) {
                variables.children.emplace_back(Value("this", pThis, m_pContext->GetThisTypeId(target.frame)));
            }
            const auto total = m_pContext->GetVarCount(target.frame);
            for (int32_t i = 0; i < total; ++i) {
                const char* pName = nullptr;
                int32_t type = 0;
                if (m_pContext->IsVarInScope(i, target.frame) && m_pContext->GetVar(i, target.frame, &pName, &type) >= 0 && pName && *pName) {
                    variables.children.emplace_back(Value(pName, m_pContext->GetAddressOfVar(i, target.frame), type));
                }
            }
        }
        else if (target.kind == Reference::Kind::Globals) {
            auto&& pFunction = m_pContext->GetFunction(target.frame);
            auto&& pModule = pFunction ? pFunction->GetModule() : nullptr;
            if (pModule) {
                for (uint32_t i = 0; i < pModule->GetGlobalVarCount(); ++i) {
                    const char* pName = nullptr;
                    const char* pNamespace = nullptr;
                    int32_t type = 0;
                    pModule->GetGlobalVar(i, &pName, &pNamespace, &type);
                    const auto name = pNamespace && *pNamespace ? SR_UTILS_NS::String(pNamespace) + "::" + pName : SR_UTILS_NS::String(pName);
                    variables.children.emplace_back(Value(name.c_str(), pModule->GetAddressOfGlobalVar(i), type));
                }
            }
        }
        else if (target.kind == Reference::Kind::Native && target.pObject) {
            auto&& pNative = static_cast<NativeReference*>(target.pObject);
            if (IsNativeAlive(pNative)) {
                if (!pNative->expanded) {
                    pNative->children = AngelScriptDebugNativeValues::Children(pNative->value);
                    pNative->expanded = true;
                }
                for (auto&& child : pNative->children) {
                    variables.children.emplace_back(NativeValue(child.name.c_str(), child.value.Ref(), pNative->pAnchor, pNative));
                }
            }
        }
        else if (target.pObject) {
            auto&& pObject = static_cast<asIScriptObject*>(target.pObject);
            for (uint32_t i = 0; i < pObject->GetPropertyCount(); ++i) {
                variables.children.emplace_back(Value(pObject->GetPropertyName(i), pObject->GetAddressOfProperty(i), pObject->GetPropertyTypeId(i)));
            }
        }

        auto page = DebugAdapterProtocol::Array("variables");
        const auto total = static_cast<int64_t>(variables.children.size());
        start = SR_MIN(start, total);
        const auto end = count > 0 ? SR_MIN(total, start + SR_MIN(count, total)) : total;
        for (int64_t i = start; i < end; ++i) {
            page.children.emplace_back(std::move(variables.children[i]));
        }
        body.children.emplace_back(std::move(page));
        return body;
    }

    SR_UTILS_NS::SerializationNode AngelScriptDebugInspector::Evaluate(const SR_UTILS_NS::String& expression, int64_t frame) {
        auto scopes = Scopes(frame);
        auto body = DebugAdapterProtocol::Object("body");
        auto selected = DebugAdapterProtocol::Object();
        bool found = false;
        const auto dot = expression.find('.');
        const auto name = expression.substr(0, dot);
        if (name.empty() || expression.size() > 4096) {
            return body;
        }

        for (auto&& scope : DebugAdapterProtocol::Get(scopes, "scopes").children) {
            auto variables = Variables(DebugAdapterProtocol::Integer(scope, "variablesReference"));
            auto&& children = DebugAdapterProtocol::Get(variables, "variables").children;
            for (uint64_t i = children.size(); i > 0; --i) {
                if (DebugAdapterProtocol::Text(children[i - 1], "name") == name) {
                    selected = children[i - 1];
                    found = true;
                    break;
                }
            }
            if (found) {
                break;
            }
        }

        const auto level = static_cast<uint32_t>(frame - m_frameBase);
        auto&& pThis = m_pContext->GetThisPointer(level);
        if (!found && pThis && (m_pContext->GetThisTypeId(level) & asTYPEID_SCRIPTOBJECT)) {
            auto members = Variables(AddReference(Reference::Kind::Object, 0, pThis));
            for (auto&& member : DebugAdapterProtocol::Get(members, "variables").children) {
                if (DebugAdapterProtocol::Text(member, "name") == name) {
                    selected = member;
                    found = true;
                    break;
                }
            }
        }

        auto position = dot;
        while (found && position != SR_UTILS_NS::String::npos) {
            const auto next = expression.find('.', position + 1);
            const auto memberName = expression.substr(position + 1, next == SR_UTILS_NS::String::npos ? next : next - position - 1);
            const auto reference = DebugAdapterProtocol::Integer(selected, "variablesReference");
            found = false;
            if (!reference || memberName.empty()) {
                break;
            }
            auto members = Variables(reference);
            for (auto&& member : DebugAdapterProtocol::Get(members, "variables").children) {
                if (DebugAdapterProtocol::Text(member, "name") == memberName) {
                    selected = member;
                    found = true;
                    break;
                }
            }
            position = next;
        }

        if (found) {
            DebugAdapterProtocol::Set(body, "result", DebugAdapterProtocol::Text(selected, "value"));
            DebugAdapterProtocol::Set(body, "type", DebugAdapterProtocol::Text(selected, "type"));
            DebugAdapterProtocol::Set(body, "variablesReference", DebugAdapterProtocol::Integer(selected, "variablesReference"));
        }
        return body;
    }
}
#endif
