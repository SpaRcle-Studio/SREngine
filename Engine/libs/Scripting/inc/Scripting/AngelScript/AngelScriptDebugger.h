//
// Created by Codex on 14.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUGGER_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_DEBUGGER_H

#include <Scripting/AngelScript/AngelScriptDebugInspector.h>
#include <Scripting/AngelScript/AngelScriptDebugTransport.h>
#include <Utils/Types/Map.h>
#include <Utils/Types/Set.h>

class asIScriptEngine;
class asIScriptModule;
class asIScriptFunction;

namespace SR_SCRIPTING_NS {
    class AngelScriptDebugger {
    public:
        AngelScriptDebugger();
        ~AngelScriptDebugger();
        void Stop();
        void PrepareContext(asIScriptContext* pContext);
        void ExecutionFinished(asIScriptContext* pContext);
        void ModuleBuilt(asIScriptModule* pModule);
        bool IsPaused() const;
        bool IsListening() const {
            return m_listening;
        }

        static asIScriptContext* RequestContext(asIScriptEngine* pEngine, void* pUser);
        static void ReturnContext(asIScriptEngine* pEngine, asIScriptContext* pContext, void* pUser);

    private:
        enum class Step { Continue, Into, Over, Out };
        struct Breakpoint {
            int64_t id = 0;
            int32_t requestedLine = 0;
            int32_t line = 0;
            bool supported = true;
        };

        static void LineCallback(asIScriptContext* pContext, void* pUser);
        static void ExceptionCallback(asIScriptContext* pContext, void* pUser);
        static SR_UTILS_NS::String NormalizePath(const SR_UTILS_NS::String& path);
        void OnLine(asIScriptContext* pContext, bool exception);
        void OnRequest(const SR_UTILS_NS::SerializationNode& request);
        void OnDisconnect();
        void Inspect(const SR_UTILS_NS::SerializationNode& request);
        void Reply(const SR_UTILS_NS::SerializationNode& request, SR_UTILS_NS::SerializationNode body = DebugAdapterProtocol::Object("body"), const char* pError = nullptr);
        void Event(const char* pName, SR_UTILS_NS::SerializationNode body = DebugAdapterProtocol::Object("body"));
        void SetBreakpoints(const SR_UTILS_NS::SerializationNode& request);
        SR_UTILS_NS::SerializationNode DescribeBreakpoint(const Breakpoint& breakpoint) const;
        void BindBreakpoint(Breakpoint& breakpoint, const SR_UTILS_NS::String& path);
        void CollectLocations(asIScriptFunction* pFunction);
        void RefreshBreakpoints();

    private:
        AngelScriptDebugTransport m_transport;
        AngelScriptDebugInspector m_inspector;
        mutable std::mutex m_mutex;
        std::condition_variable m_condition;
        std::atomic<bool> m_active = false;
        bool m_stopping = false;
        bool m_listening = false;
        bool m_initialized = false;
        bool m_attached = false;
        bool m_configured = false;
        bool m_paused = false;
        bool m_pauseRequested = false;
        bool m_breakOnException = false;
        bool m_linesStartAt1 = true;
        bool m_columnsStartAt1 = true;
        Step m_step = Step::Continue;
        uint32_t m_stepDepth = 0;
        asIScriptContext* m_pStepContext = nullptr;
        asIScriptContext* m_pPausedContext = nullptr;
        int64_t m_nextBreakpoint = 1;
        SR_UTILS_NS::Map<SR_UTILS_NS::String, SR_UTILS_NS::Vector<Breakpoint>> m_breakpoints;
        SR_UTILS_NS::Map<SR_UTILS_NS::String, SR_UTILS_NS::Set<int32_t>> m_locations;
        SR_UTILS_NS::Map<const char*, SR_UTILS_NS::String> m_sectionPaths;
        SR_UTILS_NS::Set<asIScriptFunction*> m_functions;
        SR_UTILS_NS::Vector<SR_UTILS_NS::SerializationNode> m_requests;
    };
}

#endif
