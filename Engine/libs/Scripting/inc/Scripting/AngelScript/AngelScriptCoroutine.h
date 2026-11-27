//
// Created by Claude on 27.11.2026.
//

#ifndef SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_COROUTINE_H
#define SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_COROUTINE_H

#if defined(SR_ENGINE_ANGELSCRIPT_SUPPORT)

#include <Scripting/stdInclude.h>

class asIScriptEngine;
class asIScriptContext;
class asIScriptFunction;
class asIScriptModule;

namespace SR_SCRIPTING_NS {
    /// Скриптовая корутина: собственный контекст AngelScript, который приостанавливается через Yield()
    /// и продолжается через Resume(). Состояние стека не сериализуется.
    /// Все функции зарегистрированы через generic-конвенцию, поэтому работают на всех платформах (включая AS_MAX_PORTABILITY).
    class AngelScriptCoroutine {
    public:
        explicit AngelScriptCoroutine(asIScriptFunction* pEntry);
        ~AngelScriptCoroutine();

    public:
        void AddRef();
        void Release();

        /// выполняет корутину до следующего Yield() или до завершения; false при ошибке или прерывании
        bool Resume();
        /// прерывает корутину; из самой корутины прерывание применяется после возврата в скрипт
        void Abort();
        /// приостанавливает корутину, если она сейчас выполняется в активном контексте
        bool Suspend();

        SR_NODISCARD bool IsFinished() const { return m_finished; }
        SR_NODISCARD bool IsRunning() const { return m_running; }
        SR_NODISCARD const SR_UTILS_NS::String& GetError() const { return m_error; }

        /// корутина, выполняемая на текущем потоке (самая вложенная), или nullptr
        SR_NODISCARD static AngelScriptCoroutine* GetCurrent();

        /// Прерывает все невыполняющиеся корутины: освобождает их стеки и точки входа.
        /// Корутина держит делегат (а через него скриптовый объект), который не виден сборщику мусора AngelScript,
        /// поэтому перед выгрузкой модуля и остановкой движка такие циклы нужно разорвать явно.
        /// pModule != nullptr: только корутины, точка входа которых принадлежит этому модулю
        static void AbortAll(asIScriptModule* pModule = nullptr);

    private:
        bool Prepare();
        /// завершает корутину: освобождает контекст и точку входа, после этого Resume() невозможен
        void Finish();
        void ReleaseContext();

    private:
        asIScriptFunction* m_pEntry = nullptr;
        asIScriptContext* m_pContext = nullptr;
        AngelScriptCoroutine* m_pPrevious = nullptr;
        /// интрузивный список живых корутин для AbortAll()
        AngelScriptCoroutine* m_pPrevAlive = nullptr;
        AngelScriptCoroutine* m_pNextAlive = nullptr;
        SR_UTILS_NS::String m_error;
        uint32_t m_references = 1;
        bool m_finished = false;
        bool m_running = false;

    };

    bool RegisterAngelScriptCoroutine(asIScriptEngine* pEngine);
}

#endif // SR_ENGINE_ANGELSCRIPT_SUPPORT

#endif // SR_ENGINE_SCRIPTING_ANGEL_SCRIPT_COROUTINE_H
