//
// Created by Claude on 27.11.2026.
//

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/AngelScript/AngelScriptCoroutine.h>
#include <Scripting/AngelScript/AngelScriptBindingHelpers.h>

#include <Utils/Common/StringAtomLiterals.h>
#include <Utils/Profile/TracyContext.h>

#include <angelscript.h>

namespace SR_SCRIPTING_NS {
    namespace AngelScriptCoroutineState {
        /// корутины одного потока вложены строго стеком: каждая хранит предыдущую в m_pPrevious
        thread_local AngelScriptCoroutine* pCurrent = nullptr;

        std::mutex aliveMutex;
        AngelScriptCoroutine* pAlive = nullptr;
    }

    namespace AngelScriptCoroutineHelpers {
        asIScriptFunction* EntryFunction(asIScriptFunction* pEntry) {
            if (pEntry && pEntry->GetFuncType() == asFUNC_DELEGATE) {
                return pEntry->GetDelegateFunction();
            }

            return pEntry;
        }

        bool IsEntry(asIScriptFunction* pFunction) {
            return pFunction && pFunction->GetReturnTypeId() == asTYPEID_VOID && pFunction->GetParamCount() == 0 && !pFunction->GetObjectType();
        }

        void Factory(asIScriptGeneric* pCall) {
            auto&& pEntry = static_cast<asIScriptFunction*>(pCall->GetArgObject(0));

            if (!pEntry) {
                AngelScriptBindingHelpers::Exception("Coroutine : entry function is null");
                return;
            }

            pCall->SetReturnAddress(new AngelScriptCoroutine(pEntry));
        }

        void AddRef(asIScriptGeneric* pCall) {
            static_cast<AngelScriptCoroutine*>(pCall->GetObject())->AddRef();
        }

        void Release(asIScriptGeneric* pCall) {
            static_cast<AngelScriptCoroutine*>(pCall->GetObject())->Release();
        }

        void Resume(asIScriptGeneric* pCall) {
            pCall->SetReturnByte(static_cast<AngelScriptCoroutine*>(pCall->GetObject())->Resume());
        }

        void Abort(asIScriptGeneric* pCall) {
            static_cast<AngelScriptCoroutine*>(pCall->GetObject())->Abort();
        }

        void IsFinished(asIScriptGeneric* pCall) {
            pCall->SetReturnByte(static_cast<AngelScriptCoroutine*>(pCall->GetObject())->IsFinished());
        }

        void IsRunning(asIScriptGeneric* pCall) {
            pCall->SetReturnByte(static_cast<AngelScriptCoroutine*>(pCall->GetObject())->IsRunning());
        }

        void GetError(asIScriptGeneric* pCall) {
            auto&& error = static_cast<AngelScriptCoroutine*>(pCall->GetObject())->GetError();
            pCall->SetReturnObject(const_cast<SR_UTILS_NS::String*>(&error));
        }

        void Yield(asIScriptGeneric*) {
            auto&& pCoroutine = AngelScriptCoroutine::GetCurrent();

            if (!pCoroutine || !pCoroutine->Suspend()) {
                AngelScriptBindingHelpers::Exception("Yield() : called outside of a running coroutine");
            }
        }

        void IsInCoroutine(asIScriptGeneric* pCall) {
            auto&& pCoroutine = AngelScriptCoroutine::GetCurrent();
            pCall->SetReturnByte(pCoroutine && pCoroutine->IsRunning());
        }

        void FindEntry(asIScriptGeneric* pCall) {
            auto&& name = *static_cast<const SR_UTILS_NS::String*>(pCall->GetArgObject(0));
            auto&& pContext = asGetActiveContext();
            auto&& pCaller = pContext ? pContext->GetFunction(0) : nullptr;
            auto&& pModule = pCaller ? pCaller->GetModule() : nullptr;

            if (!pModule || name.empty()) {
                pCall->SetReturnObject(nullptr);
                return;
            }

            SR_UTILS_NS::String declaration;
            declaration.reserve(name.size() + 8);
            declaration += "void ";
            declaration += name;
            declaration += "()";

            auto&& pFunction = pModule->GetFunctionByDecl(declaration.c_str());
            pCall->SetReturnObject(IsEntry(pFunction) ? pFunction : nullptr);
        }

        void EntryName(asIScriptGeneric* pCall) {
            auto&& pFunction = EntryFunction(static_cast<asIScriptFunction*>(pCall->GetArgObject(0)));
            SR_UTILS_NS::String name;

            if (pFunction) {
                auto&& pNamespace = pFunction->GetNamespace();

                if (pNamespace && *pNamespace) {
                    name += pNamespace;
                    name += "::";
                }

                name += pFunction->GetName();
            }

            pCall->SetReturnObject(&name);
        }
    }

    AngelScriptCoroutine::AngelScriptCoroutine(asIScriptFunction* pEntry)
        : m_pEntry(pEntry)
    {
        m_pEntry->AddRef();

        std::lock_guard lock(AngelScriptCoroutineState::aliveMutex);
        m_pNextAlive = AngelScriptCoroutineState::pAlive;
        if (m_pNextAlive) {
            m_pNextAlive->m_pPrevAlive = this;
        }
        AngelScriptCoroutineState::pAlive = this;
    }

    AngelScriptCoroutine::~AngelScriptCoroutine() {
        Finish();

        std::lock_guard lock(AngelScriptCoroutineState::aliveMutex);
        if (m_pPrevAlive) {
            m_pPrevAlive->m_pNextAlive = m_pNextAlive;
        }
        else {
            AngelScriptCoroutineState::pAlive = m_pNextAlive;
        }
        if (m_pNextAlive) {
            m_pNextAlive->m_pPrevAlive = m_pPrevAlive;
        }
    }

    void AngelScriptCoroutine::AbortAll(asIScriptModule* pModule) {
        SR_TRACY_ZONE;

        SR_UTILS_NS::Vector<AngelScriptCoroutine*> coroutines;

        {
            std::lock_guard lock(AngelScriptCoroutineState::aliveMutex);
            for (auto&& pCoroutine = AngelScriptCoroutineState::pAlive; pCoroutine; pCoroutine = pCoroutine->m_pNextAlive) {
                auto&& pFunction = AngelScriptCoroutineHelpers::EntryFunction(pCoroutine->m_pEntry);
                const bool owned = !pModule || (pFunction && pFunction->GetModule() == pModule);

                if (!pCoroutine->m_running && pCoroutine->m_pEntry && owned) {
                    pCoroutine->AddRef();
                    coroutines.emplace_back(pCoroutine);
                }
            }
        }

        /// без блокировки: освобождение стека может уничтожить другие корутины
        for (auto&& pCoroutine : coroutines) {
            pCoroutine->Finish();
            pCoroutine->Release();
        }
    }

    void AngelScriptCoroutine::Finish() {
        m_finished = true;
        ReleaseContext();

        if (m_pEntry) {
            /// копия указателя, не ссылка на поле: поле обнуляется до Release(), который может вызвать повторный вход
            asIScriptFunction* pEntry = m_pEntry;
            m_pEntry = nullptr;
            pEntry->Release();
        }
    }

    void AngelScriptCoroutine::AddRef() {
        ++m_references;
    }

    void AngelScriptCoroutine::Release() {
        if (--m_references == 0) {
            delete this;
        }
    }

    AngelScriptCoroutine* AngelScriptCoroutine::GetCurrent() {
        return AngelScriptCoroutineState::pCurrent;
    }

    bool AngelScriptCoroutine::Prepare() {
        auto&& pEngine = m_pEntry->GetEngine();
        m_pContext = pEngine->RequestContext();

        if (!m_pContext) {
            m_error = "Coroutine : failed to request a script context";
            return false;
        }

        auto&& pFunction = AngelScriptCoroutineHelpers::EntryFunction(m_pEntry);
        void* pObject = m_pEntry->GetFuncType() == asFUNC_DELEGATE ? m_pEntry->GetDelegateObject() : nullptr;

        if (m_pContext->Prepare(pFunction) < 0 || (pObject && m_pContext->SetObject(pObject) < 0)) {
            m_error = "Coroutine : failed to prepare the entry function";
            return false;
        }

        return true;
    }

    bool AngelScriptCoroutine::Resume() {
        SR_TRACY_ZONE;

        if (m_finished) {
            return false;
        }

        if (m_running) {
            AngelScriptBindingHelpers::Exception("Coroutine::Resume() : coroutine is already running");
            return false;
        }

        if (!m_pContext && !Prepare()) {
            Finish();
            return false;
        }

        /// корутина может освободить последнюю ссылку на себя во время выполнения
        AddRef();

        m_running = true;
        m_pPrevious = AngelScriptCoroutineState::pCurrent;
        AngelScriptCoroutineState::pCurrent = this;

        const auto result = m_pContext->Execute();

        AngelScriptCoroutineState::pCurrent = m_pPrevious;
        m_pPrevious = nullptr;
        m_running = false;

        if (result == asEXECUTION_EXCEPTION) {
            int32_t column = 0;
            const char* pSection = nullptr;
            const auto line = m_pContext->GetExceptionLineNumber(&column, &pSection);
            auto&& pFunction = m_pContext->GetExceptionFunction();

            m_error = "{} at {} ({}:{})"_format(
                m_pContext->GetExceptionString() ? m_pContext->GetExceptionString() : "<unknown exception>",
                pFunction ? pFunction->GetDeclaration(true, true) : "<unknown>",
                pSection ? pSection : "<unknown>",
                line
            );

            SR_ERROR("AngelScriptCoroutine::Resume() : {}", m_error);
        }
        else if (result == asEXECUTION_ABORTED && m_error.empty()) {
            m_error = "Coroutine : aborted";
        }
        else if (result != asEXECUTION_SUSPENDED && result != asEXECUTION_FINISHED && m_error.empty()) {
            m_error = "Coroutine : execution failed ({})"_format(static_cast<int32_t>(result));
        }

        if (result != asEXECUTION_SUSPENDED) {
            Finish();
        }

        const bool success = result == asEXECUTION_SUSPENDED || result == asEXECUTION_FINISHED;
        Release();

        return success;
    }

    void AngelScriptCoroutine::Abort() {
        if (m_finished) {
            return;
        }

        if (m_running) {
            /// прервать можно только саму себя: Execute() вернёт asEXECUTION_ABORTED в Resume()
            if (asGetActiveContext() != m_pContext) {
                AngelScriptBindingHelpers::Exception("Coroutine::Abort() : cannot abort a coroutine that is waiting for a nested one");
                return;
            }

            m_error = "Coroutine : aborted";
            m_pContext->Abort();
            return;
        }

        Finish();
    }

    bool AngelScriptCoroutine::Suspend() {
        if (!m_running || !m_pContext || asGetActiveContext() != m_pContext) {
            return false;
        }

        return m_pContext->Suspend() >= 0;
    }

    void AngelScriptCoroutine::ReleaseContext() {
        if (!m_pContext) {
            return;
        }

        const auto state = m_pContext->GetState();

        if (state == asEXECUTION_SUSPENDED) {
            m_pContext->Abort();
        }

        /// освобождает стек, локальные объекты и аргументы приостановленной функции
        m_pContext->Unprepare();
        m_pContext->GetEngine()->ReturnContext(m_pContext);
        m_pContext = nullptr;
    }

    bool RegisterAngelScriptCoroutine(asIScriptEngine* pEngine) {
        SR_TRACY_ZONE;

        /// Параметры-хендлы объявлены как "@+": при asEP_GENERIC_CALL_MODE = 1 обычный хендл-аргумент
        /// generic-функции не освобождается движком и считался бы переданным во владение.

        return pEngine->RegisterFuncdef("void CoroutineEntry()") >= 0 &&
            pEngine->RegisterObjectType("Coroutine", 0, asOBJ_REF) >= 0 &&
            pEngine->RegisterObjectBehaviour("Coroutine", asBEHAVE_FACTORY, "Coroutine@ f(CoroutineEntry@+ entry)",
                asFUNCTION(AngelScriptCoroutineHelpers::Factory), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterObjectBehaviour("Coroutine", asBEHAVE_ADDREF, "void f()",
                asFUNCTION(AngelScriptCoroutineHelpers::AddRef), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterObjectBehaviour("Coroutine", asBEHAVE_RELEASE, "void f()",
                asFUNCTION(AngelScriptCoroutineHelpers::Release), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterObjectMethod("Coroutine", "bool Resume()",
                asFUNCTION(AngelScriptCoroutineHelpers::Resume), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterObjectMethod("Coroutine", "void Abort()",
                asFUNCTION(AngelScriptCoroutineHelpers::Abort), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterObjectMethod("Coroutine", "bool IsFinished() const",
                asFUNCTION(AngelScriptCoroutineHelpers::IsFinished), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterObjectMethod("Coroutine", "bool IsRunning() const",
                asFUNCTION(AngelScriptCoroutineHelpers::IsRunning), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterObjectMethod("Coroutine", "String GetError() const",
                asFUNCTION(AngelScriptCoroutineHelpers::GetError), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterGlobalFunction("void Yield()",
                asFUNCTION(AngelScriptCoroutineHelpers::Yield), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterGlobalFunction("bool IsInCoroutine()",
                asFUNCTION(AngelScriptCoroutineHelpers::IsInCoroutine), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterGlobalFunction("CoroutineEntry@ FindCoroutineEntry(const String &in name)",
                asFUNCTION(AngelScriptCoroutineHelpers::FindEntry), asCALL_GENERIC) >= 0 &&
            pEngine->RegisterGlobalFunction("String GetCoroutineEntryName(CoroutineEntry@+ entry)",
                asFUNCTION(AngelScriptCoroutineHelpers::EntryName), asCALL_GENERIC) >= 0;
    }
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT
