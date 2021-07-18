//
// Created by Nikita on 11.07.2021.
//

#include "Impl/EvoScriptImpl.h"
#include <Impl/EvoCompiler.h>

#include <ctime>
#include <ratio>
#include <chrono>

bool Framework::Scripting::EvoScriptImpl::Destroy() {
    this->m_compiler->RemoveScript(this);
    return true;
}

void Framework::Scripting::EvoScriptImpl::Awake() {
    this->m_script->Awake();
}

void Framework::Scripting::EvoScriptImpl::Start() {
    this->m_script->Start();
    this->m_isStart = true;
}

void Framework::Scripting::EvoScriptImpl::Close() {
    this->m_script->Close();
}

void Framework::Scripting::EvoScriptImpl::Update() {
    if (!m_isStart)
        this->Start();

    //auto timeNow = std::chrono::high_resolution_clock::now();
    //std::chrono::duration<double, std::milli> time_span = timeNow - m_lastUpd;
    //this->m_script->Update(time_span.count());
    //this->m_lastUpd = timeNow;

    using clock = std::chrono::high_resolution_clock;
    auto delta_time = clock::now() - m_lastUpd;
    m_lastUpd = clock::now();
    this->m_script->Update((float)delta_time.count() / 1000000.f);
}

void Framework::Scripting::EvoScriptImpl::FixedUpdate() {
    if (!m_isStart)
        this->Start();
    this->m_script->FixedUpdate();
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
