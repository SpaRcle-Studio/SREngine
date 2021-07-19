//
// Created by Nikita on 11.07.2021.
//

#include "Impl/EvoScriptImpl.h"
#include <Impl/EvoCompiler.h>

#include <ctime>
#include <ratio>
#include <chrono>

bool Framework::Scripting::EvoScriptImpl::AwaitDestroy() {
    Helper::Debug::Log("EvoScriptImpl::AwaitDestroy() : await destroy \"" + m_name + "\" script...");

    this->m_compiler->RemoveScript(this);
ret:
    if (m_compiler->Contains(this))
        goto ret;

    m_isDestroy = true;

    return true;
}

void Framework::Scripting::EvoScriptImpl::Awake() {
    if (m_isDestroy)
        return;

    this->m_script->Awake();
}

void Framework::Scripting::EvoScriptImpl::Start() {
    if (m_isDestroy)
        return;

    this->m_script->Start();
    this->m_isStart = true;
}

void Framework::Scripting::EvoScriptImpl::Close() {
    if (m_isDestroy)
        return;

    this->m_script->Close();
}

void Framework::Scripting::EvoScriptImpl::Update() {
    if (m_isDestroy)
        return;

    if (!m_isStart)
        this->Start();

    using clock = std::chrono::high_resolution_clock;
    auto delta_time = clock::now() - m_lastUpd;
    m_lastUpd = clock::now();
    this->m_script->Update((float)delta_time.count() / 1000000.f);
}

void Framework::Scripting::EvoScriptImpl::FixedUpdate() {
    if (m_isDestroy)
        return;

    if (!m_isStart)
        this->Start();
    this->m_script->FixedUpdate();
}

void Framework::Scripting::EvoScriptImpl::OnGUI() {
    if (m_isDestroy)
        return;

    if (!m_isStart)
        this->Start();
    m_script->OnGUI();
}

bool Framework::Scripting::EvoScriptImpl::Compile() {
    auto* compiler = dynamic_cast<Scripting::EvoCompiler*>(m_compiler);

    this->m_script = EvoScript::Script::Allocate(
            m_name, compiler->GetEvoScriptCompiler(), compiler->GetGenerator()->GetAddresses(), true);

    if (!m_script->Load(m_path)) {
        Helper::Debug::Error("EvoScriptImpl::Compile() : failed to load script!");
        return false;
    }

    this->m_compiler->RegisterScript(this);

    return true;
}

bool Framework::Scripting::EvoScriptImpl::DelayedDestroyAndFree() {
    this->m_needFreeAfterDestroy = true;
    this->m_compiler->RemoveScript(this);
    this->m_isDestroy = true;

    return true;
}

