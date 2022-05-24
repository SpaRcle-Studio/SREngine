//
// Created by Nikita on 11.07.2021.
//

#include <Scripting/Impl/EvoScriptImpl.h>
#include <Scripting/Impl/EvoCompiler.h>

#include <Utils/Features.h>

namespace SR_SCRIPTING_NS {
    bool EvoScriptImpl::AwaitDestroy() {
        SR_LOG("EvoScriptImpl::AwaitDestroy() : await destroy \"" + m_name + "\" script...");

        m_compiler->RemoveScript(this);

    ret:
        if (m_compiler->Contains(this))
            goto ret;

        m_isDestroy = true;

        return true;
    }

    void EvoScriptImpl::Awake() {
        if (m_isDestroy)
            return;

        SR_MAYBE_UNUSED_VAR m_script->Awake();
    }

    void EvoScriptImpl::Start() {
        if (m_isDestroy || m_isStart)
            return;

        SR_MAYBE_UNUSED_VAR m_script->Start();
        m_isStart = true;
    }

    void EvoScriptImpl::Close() {
        if (m_isDestroy)
            return;

        SR_MAYBE_UNUSED_VAR m_script->Close();
    }

    void EvoScriptImpl::Update() {
        if (m_isDestroy)
            return;

        if (!m_isStart)
            Start();

        using clock = std::chrono::high_resolution_clock;
        auto delta_time = clock::now() - m_lastUpd;
        m_lastUpd = clock::now();
        SR_MAYBE_UNUSED_VAR m_script->Update((float)delta_time.count() / 1000000.f);
    }

    void EvoScriptImpl::FixedUpdate() {
        if (m_isDestroy)
            return;

        if (!m_isStart)
            Start();

        SR_MAYBE_UNUSED_VAR m_script->FixedUpdate();
    }

    void EvoScriptImpl::OnGUI() {
        if (m_isDestroy)
            return;

        if (!m_isStart)
            Start();

        SR_MAYBE_UNUSED_VAR m_script->OnGUI();
    }

    bool EvoScriptImpl::Compile() {
        auto&& compiler = dynamic_cast<Scripting::EvoCompiler*>(m_compiler);

        if (!compiler || !compiler->GetGenerator()) {
            SR_ERROR("EvoScriptImpl::Compile() : compiler isn't init! \n\tPath: " + m_path);
            return false;
        }

        m_script = EvoScript::Script::Allocate(
                m_name,
                compiler->GetEvoScriptCompiler(),
                compiler->GetGenerator()->GetAddresses(),
                true
        );

        const bool canCompile = Helper::Features::Instance().Enabled("EvoCompiler");
        if (!m_script->Load(m_path, canCompile)) {
            SR_ERROR("EvoScriptImpl::Compile() : failed to load script!");
            return false;
        }

        m_compiler->RegisterScript(this);

        return true;
    }

    bool Framework::Scripting::EvoScriptImpl::DelayedDestroyAndFree() {
        m_autoFree = true;
        m_compiler->RemoveScript(this);
        m_isDestroy = true;

        return true;
    }
}
