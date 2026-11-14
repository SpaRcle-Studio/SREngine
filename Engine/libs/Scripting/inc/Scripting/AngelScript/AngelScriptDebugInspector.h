//
// Created by Codex on 14.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUG_INSPECTOR_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUG_INSPECTOR_H

#include <Scripting/AngelScript/DebugAdapterProtocol.h>
#include <Scripting/AngelScript/AngelScriptDebugNativeValues.h>

class asIScriptContext;

namespace SR_SCRIPTING_NS {
    struct AngelScriptNativeObject;

    class AngelScriptDebugInspector {
    public:
        ~AngelScriptDebugInspector();
        void Begin(asIScriptContext* pContext, bool linesStartAt1, bool columnsStartAt1);
        void End();
        SR_UTILS_NS::SerializationNode StackTrace(int64_t start, int64_t levels);
        SR_UTILS_NS::SerializationNode Scopes(int64_t frame);
        SR_UTILS_NS::SerializationNode Variables(int64_t reference, int64_t start = 0, int64_t count = 0);
        SR_UTILS_NS::SerializationNode Evaluate(const SR_UTILS_NS::String& expression, int64_t frame);
        bool HasFrame(int64_t frame) const;
        bool HasReference(int64_t reference) const;
        int64_t GetTopFrame() const {
            return m_frameBase;
        }
        static SR_UTILS_NS::String SourcePath(const char* pSection);

    private:
        struct Reference {
            enum class Kind { Locals, Globals, Object, Native };
            int64_t id = 0;
            Kind kind = Kind::Locals;
            uint32_t frame = 0;
            void* pObject = nullptr;
        };

        struct NativeReference {
            SR_UTILS_NS::Reflection::Value value;
            AngelScriptNativeObject* pAnchor = nullptr;
            NativeReference* pParent = nullptr;
            SR_UTILS_NS::Vector<AngelScriptDebugNativeValues::Child> children;
            bool expanded = false;
        };

        int64_t AddReference(Reference::Kind kind, uint32_t frame, void* pObject = nullptr);
        SR_UTILS_NS::SerializationNode Value(const char* pName, void* pAddress, int32_t typeId);
        SR_UTILS_NS::SerializationNode NativeValue(const char* pName, SR_UTILS_NS::Reflection::Value value,
            AngelScriptNativeObject* pAnchor, NativeReference* pParent = nullptr);
        bool IsNativeAlive(const NativeReference* pReference) const;

    private:
        asIScriptContext* m_pContext = nullptr;
        SR_UTILS_NS::Vector<Reference> m_references;
        SR_UTILS_NS::Vector<NativeReference*> m_nativeReferences;
        int64_t m_nextId = 1;
        int64_t m_frameBase = 0;
        bool m_linesStartAt1 = true;
        bool m_columnsStartAt1 = true;
    };
}

#endif
