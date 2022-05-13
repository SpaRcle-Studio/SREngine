//
// Created by Nikita on 11.07.2021.
//

#include "Impl/EvoScriptImpl.h"
#include <Impl/EvoCompiler.h>
#include <Utils/Features.h>

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

    m_script->Awake();
}

void Framework::Scripting::EvoScriptImpl::Start() {
    if (m_isDestroy || m_isStart)
        return;

    m_script->Start();
    m_isStart = true;
}

void Framework::Scripting::EvoScriptImpl::Close() {
    if (m_isDestroy)
        return;

    m_script->Close();
}

void Framework::Scripting::EvoScriptImpl::Update() {
    if (m_isDestroy)
        return;

    if (!m_isStart)
        Start();

    using clock = std::chrono::high_resolution_clock;
    auto delta_time = clock::now() - m_lastUpd;
    m_lastUpd = clock::now();
    m_script->Update((float)delta_time.count() / 1000000.f);
}

void Framework::Scripting::EvoScriptImpl::FixedUpdate() {
    if (m_isDestroy)
        return;

    if (!m_isStart)
        Start();

    m_script->FixedUpdate();
}

void Framework::Scripting::EvoScriptImpl::OnGUI() {
    if (m_isDestroy)
        return;

    if (!m_isStart)
        Start();

    m_script->OnGUI();
}

bool Framework::Scripting::EvoScriptImpl::Compile() {
    auto* compiler = dynamic_cast<Scripting::EvoCompiler*>(m_compiler);

    if (!compiler || !compiler->GetGenerator()) {
        SR_ERROR("EvoScriptImpl::Compile() : compiler isn't init! \n\tPath: " + m_path);
        return false;
    }

    m_script = EvoScript::Script::Allocate(
            m_name, compiler->GetEvoScriptCompiler(), compiler->GetGenerator()->GetAddresses(), true);

    const bool canCompile = Helper::Features::Instance().Enabled("EvoCompiler");
    if (!m_script->Load(m_path, canCompile)) {
        Helper::Debug::Error("EvoScriptImpl::Compile() : failed to load script!");
        return false;
    }

    m_compiler->RegisterScript(this);

    return true;
}

bool Framework::Scripting::EvoScriptImpl::DelayedDestroyAndFree() {
    m_needFreeAfterDestroy = true;
    m_compiler->RemoveScript(this);
    m_isDestroy = true;

    return true;
}

