//
// Created by Codex on 14.11.2026.
//

#include <Scripting/AngelScript/AngelScriptDebugger.h>

#if defined(SR_ENGINE_ANGELSCRIPT_DEBUGGER)
#include <angelscript.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/StoreUtils.h>

namespace SR_SCRIPTING_NS {
    AngelScriptDebugger::AngelScriptDebugger() {
        const char* pPort = std::getenv("SR_ANGELSCRIPT_DAP_PORT");
        if (!pPort || !*pPort) {
            if (!SR_UTILS_NS::StoreUtils::Temp::GetBool("ApplicationIsEditor")) {
                return;
            }
            pPort = "4711";
        }

        uint32_t port = 0;
        for (const char* pDigit = pPort; *pDigit; ++pDigit) {
            if (*pDigit < '0' || *pDigit > '9' || port > 6553) {
                SR_ERROR("AngelScriptDebugger::AngelScriptDebugger() : invalid SR_ANGELSCRIPT_DAP_PORT.");
                return;
            }
            port = port * 10 + *pDigit - '0';
        }
        if (port == 0) {
            return;
        }
        if (port > 65535) {
            SR_ERROR("AngelScriptDebugger::AngelScriptDebugger() : DAP port must be between 1 and 65535.");
            return;
        }

        m_listening = m_transport.Start(static_cast<uint16_t>(port), [this](const SR_UTILS_NS::SerializationNode& request) {
            OnRequest(request);
        }, [this]() {
            OnDisconnect();
        });
    }

    AngelScriptDebugger::~AngelScriptDebugger() {
        Stop();
    }

    void AngelScriptDebugger::Stop() {
        {
            std::lock_guard lock(m_mutex);
            m_stopping = true;
            m_active = false;
            m_paused = false;
            m_condition.notify_all();
        }
        m_transport.Stop();
    }

    bool AngelScriptDebugger::IsPaused() const {
        std::lock_guard lock(m_mutex);
        return m_paused;
    }

    void AngelScriptDebugger::PrepareContext(asIScriptContext* pContext) {
        if (!m_listening) {
            return;
        }
        pContext->SetLineCallback(asFUNCTION(AngelScriptDebugger::LineCallback), this, asCALL_CDECL);
        pContext->SetExceptionCallback(asFUNCTION(AngelScriptDebugger::ExceptionCallback), this, asCALL_CDECL);
    }

    asIScriptContext* AngelScriptDebugger::RequestContext(asIScriptEngine* pEngine, void* pUser) {
        auto&& pContext = pEngine->CreateContext();
        if (pContext) {
            static_cast<AngelScriptDebugger*>(pUser)->PrepareContext(pContext);
        }
        return pContext;
    }

    void AngelScriptDebugger::ReturnContext(asIScriptEngine*, asIScriptContext* pContext, void* pUser) {
        static_cast<AngelScriptDebugger*>(pUser)->ExecutionFinished(pContext);
        pContext->Release();
    }

    void AngelScriptDebugger::ExecutionFinished(asIScriptContext* pContext) {
        if (!m_active) {
            return;
        }
        std::lock_guard lock(m_mutex);
        if (m_pStepContext == pContext) {
            m_pStepContext = nullptr;
            if (m_step != Step::Continue) {
                m_step = Step::Into;
            }
        }
    }

    void AngelScriptDebugger::LineCallback(asIScriptContext* pContext, void* pUser) {
        static_cast<AngelScriptDebugger*>(pUser)->OnLine(pContext, false);
    }

    void AngelScriptDebugger::ExceptionCallback(asIScriptContext* pContext, void* pUser) {
        static_cast<AngelScriptDebugger*>(pUser)->OnLine(pContext, true);
    }

    SR_UTILS_NS::String AngelScriptDebugger::NormalizePath(const SR_UTILS_NS::String& path) {
        auto result = AngelScriptDebugInspector::SourcePath(path.c_str());
        for (auto&& character : result) {
            if (character == '\\') {
                character = '/';
            }
        #if defined(SR_WIN32)
            if (character >= 'A' && character <= 'Z') {
                character += 'a' - 'A';
            }
        #endif
        }
        return result;
    }

    void AngelScriptDebugger::OnLine(asIScriptContext* pContext, bool exception) {
        if (!m_active) {
            return;
        }

        std::unique_lock lock(m_mutex);
        m_condition.wait(lock, [this]() {
            return !m_paused || m_stopping || !m_active;
        });
        if (!m_active || m_stopping || (exception && !m_breakOnException)) {
            return;
        }

        auto&& pFunction = pContext->GetFunction();
        if (pFunction && pFunction->GetFuncType() == asFUNC_SCRIPT && !m_functions.contains(pFunction)) {
            CollectLocations(pFunction);
            RefreshBreakpoints();
        }

        const char* pSection = nullptr;
        const auto line = pContext->GetLineNumber(0, nullptr, &pSection);
        bool breakpointHit = false;
        int64_t hitId = 0;
        if (!exception && pSection && *pSection && pSection[0] != '<') {
            auto cached = m_sectionPaths.find(pSection);
            if (cached == m_sectionPaths.end()) {
                m_sectionPaths[pSection] = NormalizePath(pSection);
                cached = m_sectionPaths.find(pSection);
            }
            const auto found = m_breakpoints.find(cached->second);
            if (found != m_breakpoints.end()) {
                for (auto&& breakpoint : found->second) {
                    if (breakpoint.line == line) {
                        breakpointHit = true;
                        hitId = breakpoint.id;
                        break;
                    }
                }
            }
        }

        const auto depth = pContext->GetCallstackSize();
        const bool stepHit = !exception && (m_step == Step::Into || (m_pStepContext == pContext &&
            ((m_step == Step::Over && depth <= m_stepDepth) || (m_step == Step::Out && depth < m_stepDepth))));
        if (!exception && !breakpointHit && !m_pauseRequested && !stepHit) {
            return;
        }

        SR_TRACY_ZONE_N("AngelScript debugger stop");
        const char* pReason = exception ? "exception" : breakpointHit ? "breakpoint" : m_pauseRequested ? "pause" : "step";
        m_pauseRequested = false;
        m_step = Step::Continue;
        m_paused = true;
        m_pPausedContext = pContext;
        m_inspector.Begin(pContext, m_linesStartAt1, m_columnsStartAt1);
        auto stopped = DebugAdapterProtocol::Object("body");
        DebugAdapterProtocol::Set(stopped, "reason", pReason);
        DebugAdapterProtocol::Set(stopped, "threadId", 1);
        DebugAdapterProtocol::Set(stopped, "allThreadsStopped", true);
        if (exception) {
            DebugAdapterProtocol::Set(stopped, "text", pContext->GetExceptionString());
        }
        if (breakpointHit) {
            auto hitIds = DebugAdapterProtocol::Array("hitBreakpointIds");
            auto id = DebugAdapterProtocol::Object();
            id.type = SR_UTILS_NS::SerializationDataType::Integer;
            id.data.integer = hitId;
            hitIds.children.emplace_back(std::move(id));
            stopped.children.emplace_back(std::move(hitIds));
        }
        Event("stopped", std::move(stopped));

        while (m_paused && m_active && !m_stopping) {
            m_condition.wait(lock, [this]() {
                return !m_requests.empty() || !m_paused || !m_active || m_stopping;
            });
            SR_UTILS_NS::Vector<SR_UTILS_NS::SerializationNode> requests;
            requests.swap(m_requests);
            for (auto&& request : requests) {
                if (m_paused && m_active) {
                    Inspect(request);
                }
                else {
                    Reply(request, DebugAdapterProtocol::Object("body"), "Script is no longer stopped.");
                }
            }
        }

        m_inspector.End();
        m_pPausedContext = nullptr;
        m_condition.notify_all();
    }

    void AngelScriptDebugger::Reply(const SR_UTILS_NS::SerializationNode& request, SR_UTILS_NS::SerializationNode body, const char* pError) {
        auto response = DebugAdapterProtocol::Object();
        DebugAdapterProtocol::Set(response, "type", "response");
        DebugAdapterProtocol::Set(response, "request_seq", DebugAdapterProtocol::Integer(request, "seq"));
        DebugAdapterProtocol::Set(response, "command", DebugAdapterProtocol::Text(request, "command"));
        DebugAdapterProtocol::Set(response, "success", pError == nullptr);
        if (pError) {
            DebugAdapterProtocol::Set(response, "message", pError);
        }
        response.children.emplace_back(std::move(body));
        m_transport.Send(std::move(response));
    }

    void AngelScriptDebugger::Event(const char* pName, SR_UTILS_NS::SerializationNode body) {
        auto event = DebugAdapterProtocol::Object();
        DebugAdapterProtocol::Set(event, "type", "event");
        DebugAdapterProtocol::Set(event, "event", pName);
        event.children.emplace_back(std::move(body));
        m_transport.Send(std::move(event));
    }

    void AngelScriptDebugger::OnDisconnect() {
        std::lock_guard lock(m_mutex);
        m_active = false;
        m_initialized = false;
        m_attached = false;
        m_configured = false;
        m_paused = false;
        m_pauseRequested = false;
        m_breakOnException = false;
        m_step = Step::Continue;
        m_pStepContext = nullptr;
        m_requests.clear();
        m_breakpoints.clear();
        m_condition.notify_all();
    }

    void AngelScriptDebugger::OnRequest(const SR_UTILS_NS::SerializationNode& request) {
        std::lock_guard lock(m_mutex);
        if (DebugAdapterProtocol::Text(request, "type") != "request") {
            return;
        }
        const auto command = DebugAdapterProtocol::Text(request, "command");
        auto&& arguments = DebugAdapterProtocol::Get(request, "arguments");
        if (command == "initialize" && !m_initialized) {
            if (DebugAdapterProtocol::Text(arguments, "pathFormat") == "uri") {
                Reply(request, DebugAdapterProtocol::Object("body"), "Use native file paths (pathFormat: path).");
                return;
            }
            m_linesStartAt1 = DebugAdapterProtocol::Boolean(arguments, "linesStartAt1", true);
            m_columnsStartAt1 = DebugAdapterProtocol::Boolean(arguments, "columnsStartAt1", true);
            m_initialized = true;
            auto capabilities = DebugAdapterProtocol::Object("body");
            DebugAdapterProtocol::Set(capabilities, "supportsConfigurationDoneRequest", true);
            DebugAdapterProtocol::Set(capabilities, "supportsEvaluateForHovers", true);
            DebugAdapterProtocol::Set(capabilities, "supportsExceptionInfoRequest", true);
            auto filters = DebugAdapterProtocol::Array("exceptionBreakpointFilters");
            auto filter = DebugAdapterProtocol::Object();
            DebugAdapterProtocol::Set(filter, "filter", "all");
            DebugAdapterProtocol::Set(filter, "label", "AngelScript exceptions");
            DebugAdapterProtocol::Set(filter, "default", false);
            filters.children.emplace_back(std::move(filter));
            capabilities.children.emplace_back(std::move(filters));
            Reply(request, std::move(capabilities));
            return;
        }
        if (!m_initialized) {
            Reply(request, DebugAdapterProtocol::Object("body"), "Initialize the adapter first.");
            return;
        }
        if (command == "attach" && !m_attached) {
            m_attached = true;
            m_pauseRequested = DebugAdapterProtocol::Boolean(arguments, "stopOnEntry");
            Reply(request);
            Event("initialized");
        }
        else if (command == "disconnect") {
            Reply(request);
            Event("terminated");
            m_active = false;
            m_paused = false;
            m_condition.notify_all();
            m_transport.DisconnectAfterFlush();
        }
        else if (!m_attached) {
            Reply(request, DebugAdapterProtocol::Object("body"), "Use Attach to connect to the running SREngine.");
        }
        else if (command == "configurationDone" && !m_configured) {
            m_configured = true;
            Reply(request);
            m_active = true;
        }
        else if (command == "setBreakpoints") {
            SetBreakpoints(request);
        }
        else if (command == "setExceptionBreakpoints") {
            m_breakOnException = false;
            for (auto&& filter : DebugAdapterProtocol::Get(arguments, "filters").children) {
                m_breakOnException = m_breakOnException || filter.string == "all";
            }
            Reply(request);
        }
        else if (command == "threads") {
            auto body = DebugAdapterProtocol::Object("body");
            auto threads = DebugAdapterProtocol::Array("threads");
            auto thread = DebugAdapterProtocol::Object();
            DebugAdapterProtocol::Set(thread, "id", 1);
            DebugAdapterProtocol::Set(thread, "name", "AngelScript");
            threads.children.emplace_back(std::move(thread));
            body.children.emplace_back(std::move(threads));
            Reply(request, std::move(body));
        }
        else if (command == "pause" && DebugAdapterProtocol::Integer(arguments, "threadId", 1) == 1) {
            m_pauseRequested = !m_paused;
            Reply(request);
        }
        else if (command == "stackTrace" || command == "scopes" || command == "variables" || command == "evaluate" ||
            command == "exceptionInfo" || command == "continue" || command == "next" || command == "stepIn" || command == "stepOut")
        {
            if (!m_paused || DebugAdapterProtocol::Integer(arguments, "threadId", 1) != 1) {
                Reply(request, DebugAdapterProtocol::Object("body"), "AngelScript thread must be stopped.");
                return;
            }
            m_requests.emplace_back(request);
            m_condition.notify_all();
        }
        else {
            Reply(request, DebugAdapterProtocol::Object("body"), "Unsupported DAP request.");
        }
    }

    void AngelScriptDebugger::Inspect(const SR_UTILS_NS::SerializationNode& request) {
        const auto command = DebugAdapterProtocol::Text(request, "command");
        auto&& arguments = DebugAdapterProtocol::Get(request, "arguments");
        const auto frame = DebugAdapterProtocol::Integer(arguments, "frameId", command == "evaluate" ? m_inspector.GetTopFrame() : -1);
        if ((command == "scopes" || command == "evaluate") && !m_inspector.HasFrame(frame)) {
            Reply(request, DebugAdapterProtocol::Object("body"), "Invalid or expired frameId.");
            return;
        }
        if (command == "stackTrace") {
            Reply(request, m_inspector.StackTrace(SR_MAX(int64_t(0), DebugAdapterProtocol::Integer(arguments, "startFrame")),
                SR_MAX(int64_t(0), DebugAdapterProtocol::Integer(arguments, "levels"))));
        }
        else if (command == "scopes") {
            Reply(request, m_inspector.Scopes(frame));
        }
        else if (command == "variables") {
            const auto reference = DebugAdapterProtocol::Integer(arguments, "variablesReference");
            if (!m_inspector.HasReference(reference)) {
                Reply(request, DebugAdapterProtocol::Object("body"), "Invalid or expired variablesReference.");
                return;
            }
            Reply(request, m_inspector.Variables(reference,
                SR_MAX(int64_t(0), DebugAdapterProtocol::Integer(arguments, "start")),
                SR_MAX(int64_t(0), DebugAdapterProtocol::Integer(arguments, "count"))));
        }
        else if (command == "evaluate") {
            auto result = m_inspector.Evaluate(DebugAdapterProtocol::Text(arguments, "expression"), frame);
            const bool found = DebugAdapterProtocol::Get(result, "result").type != SR_UTILS_NS::SerializationDataType::Unknown;
            Reply(request, std::move(result), found ? nullptr : "Variable or script member not found. Function calls and arithmetic are not supported.");
        }
        else if (command == "exceptionInfo") {
            if (m_pPausedContext->GetState() != asEXECUTION_EXCEPTION) {
                Reply(request, DebugAdapterProtocol::Object("body"), "Not stopped on an exception.");
                return;
            }
            auto body = DebugAdapterProtocol::Object("body");
            DebugAdapterProtocol::Set(body, "exceptionId", "AngelScript");
            DebugAdapterProtocol::Set(body, "description", m_pPausedContext->GetExceptionString());
            DebugAdapterProtocol::Set(body, "breakMode", "always");
            Reply(request, std::move(body));
        }
        else {
            m_step = command == "stepIn" ? Step::Into : command == "next" ? Step::Over : command == "stepOut" ? Step::Out : Step::Continue;
            m_pStepContext = m_step == Step::Continue ? nullptr : m_pPausedContext;
            m_stepDepth = m_pPausedContext->GetCallstackSize();
            auto body = DebugAdapterProtocol::Object("body");
            if (command == "continue") {
                DebugAdapterProtocol::Set(body, "allThreadsContinued", true);
            }
            Reply(request, std::move(body));
            m_paused = false;
            auto continued = DebugAdapterProtocol::Object("body");
            DebugAdapterProtocol::Set(continued, "threadId", 1);
            DebugAdapterProtocol::Set(continued, "allThreadsContinued", true);
            Event("continued", std::move(continued));
        }
    }

    SR_UTILS_NS::SerializationNode AngelScriptDebugger::DescribeBreakpoint(const Breakpoint& breakpoint) const {
        auto result = DebugAdapterProtocol::Object();
        DebugAdapterProtocol::Set(result, "id", breakpoint.id);
        DebugAdapterProtocol::Set(result, "verified", breakpoint.line > 0);
        if (breakpoint.requestedLine > 0) {
            DebugAdapterProtocol::Set(result, "line", (breakpoint.line > 0 ? breakpoint.line : breakpoint.requestedLine) - (m_linesStartAt1 ? 0 : 1));
        }
        if (!breakpoint.supported) {
            DebugAdapterProtocol::Set(result, "message", "Conditional breakpoints, hit conditions and logpoints are not supported.");
        }
        else if (!breakpoint.line) {
            DebugAdapterProtocol::Set(result, "message", "No executable line found; breakpoint will be checked after module compilation.");
        }
        return result;
    }

    void AngelScriptDebugger::BindBreakpoint(Breakpoint& breakpoint, const SR_UTILS_NS::String& path) {
        breakpoint.line = 0;
        const auto location = m_locations.find(path);
        if (!breakpoint.supported || breakpoint.requestedLine <= 0 || location == m_locations.end()) {
            return;
        }
        const auto line = location->second.lower_bound(breakpoint.requestedLine);
        if (line != location->second.end()) {
            breakpoint.line = *line;
        }
    }

    void AngelScriptDebugger::SetBreakpoints(const SR_UTILS_NS::SerializationNode& request) {
        auto&& arguments = DebugAdapterProtocol::Get(request, "arguments");
        const auto path = NormalizePath(DebugAdapterProtocol::Text(DebugAdapterProtocol::Get(arguments, "source"), "path"));
        if (path.empty()) {
            Reply(request, DebugAdapterProtocol::Object("body"), "A source.path is required.");
            return;
        }
        auto&& breakpoints = m_breakpoints[path];
        breakpoints.clear();
        auto body = DebugAdapterProtocol::Object("body");
        auto results = DebugAdapterProtocol::Array("breakpoints");
        for (auto&& requested : DebugAdapterProtocol::Get(arguments, "breakpoints").children) {
            Breakpoint breakpoint;
            breakpoint.id = m_nextBreakpoint++;
            const auto line = DebugAdapterProtocol::Integer(requested, "line", -1);
            breakpoint.requestedLine = line >= 0 && line < INT32_MAX ? static_cast<int32_t>(line) + (m_linesStartAt1 ? 0 : 1) : 0;
            breakpoint.supported = DebugAdapterProtocol::Text(requested, "condition").empty() &&
                DebugAdapterProtocol::Text(requested, "hitCondition").empty() && DebugAdapterProtocol::Text(requested, "logMessage").empty();
            BindBreakpoint(breakpoint, path);
            results.children.emplace_back(DescribeBreakpoint(breakpoint));
            breakpoints.emplace_back(breakpoint);
        }
        body.children.emplace_back(std::move(results));
        Reply(request, std::move(body));
    }

    void AngelScriptDebugger::CollectLocations(asIScriptFunction* pFunction) {
        if (!pFunction || pFunction->GetFuncType() != asFUNC_SCRIPT || m_functions.contains(pFunction)) {
            return;
        }
        m_functions.insert(pFunction);
        const auto count = pFunction->GetLineEntryCount();
        for (int32_t i = 0; i < count; ++i) {
            const char* pSection = nullptr;
            int32_t line = 0;
            if (pFunction->GetLineEntry(i, &line, nullptr, &pSection, nullptr) < 0 || !pSection || line <= 0) {
                continue;
            }
            const auto path = NormalizePath(pSection);
            if (!path.empty()) {
                m_locations[path].insert(line);
            }
        }
    }

    void AngelScriptDebugger::ModuleBuilt(asIScriptModule* pModule) {
        if (!m_listening) {
            return;
        }
        SR_TRACY_ZONE;
        std::lock_guard lock(m_mutex);
        m_locations.clear();
        m_sectionPaths.clear();
        m_functions.clear();
        for (uint32_t i = 0; pModule && i < pModule->GetFunctionCount(); ++i) {
            CollectLocations(pModule->GetFunctionByIndex(i));
        }
        for (uint32_t i = 0; pModule && i < pModule->GetObjectTypeCount(); ++i) {
            auto&& pType = pModule->GetObjectTypeByIndex(i);
            for (uint32_t j = 0; j < pType->GetMethodCount(); ++j) {
                CollectLocations(pType->GetMethodByIndex(j, false));
            }
            for (uint32_t j = 0; j < pType->GetBehaviourCount(); ++j) {
                asEBehaviours behaviour;
                CollectLocations(pType->GetBehaviourByIndex(j, &behaviour));
            }
        }
        RefreshBreakpoints();
    }

    void AngelScriptDebugger::RefreshBreakpoints() {
        for (auto&& source : m_breakpoints) {
            for (auto&& breakpoint : source.second) {
                BindBreakpoint(breakpoint, source.first);
                auto body = DebugAdapterProtocol::Object("body");
                DebugAdapterProtocol::Set(body, "reason", "changed");
                auto description = DescribeBreakpoint(breakpoint);
                description.id = SR_UTILS_NS::SerializationId::Create("breakpoint");
                body.children.emplace_back(std::move(description));
                Event("breakpoint", std::move(body));
            }
        }
    }
}
#endif
