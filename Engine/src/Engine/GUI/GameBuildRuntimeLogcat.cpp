//
// Created by OpenAI Codex on 12.11.2026.
//

#include <Engine/GUI/GameBuildRuntimeState.h>

namespace SR_CORE_GUI_NS {
    void GameBuildRuntime::RefreshLogcat(SR_UTILS_NS::String serial, SR_UTILS_NS::String package,
        SR_UTILS_NS::String priority, SR_UTILS_NS::String buffer)
    {
        m_state->Task([this, serial = std::move(serial), package = std::move(package),
            priority = std::move(priority), buffer = std::move(buffer)]()
        {
            const auto scope = serial + "\n" + package + "\n" + priority + "\n" + buffer;
            {
                std::lock_guard lock(m_state->mutex);
                if (m_state->logcatScope != scope) {
                    m_state->logcatScope = scope;
                    m_state->status.logcat.clear();
                    m_state->status.logcatMessage.clear();
                    m_state->status.logcatError = false;
                }
            }
            SR_UTILS_NS::String output;
            const bool success = m_state->android.ReadLogcat(serial, package, priority, buffer, output);
            std::lock_guard lock(m_state->mutex);
            m_state->status.logcatError = !success;
            if (!success) {
                m_state->status.logcatMessage = output.empty()
                    ? SR_UTILS_NS::String("Logcat refresh failed. Previously captured logs are retained.") : std::move(output);
            }
            else if (output.empty()) {
                m_state->status.logcatMessage = m_state->status.logcat.empty()
                    ? "No matching log records yet." : "No records returned by the latest query. Showing the last captured logs.";
            }
            else {
                m_state->status.logcat = std::move(output);
                m_state->status.logcatMessage.clear();
            }
        }, true);
    }

    void GameBuildRuntime::ClearLogcat(SR_UTILS_NS::String serial) {
        m_state->Task([this, serial = std::move(serial)]() {
            if (m_state->android.ClearLogcat(serial)) {
                std::lock_guard lock(m_state->mutex);
                m_state->status.logcat.clear();
                m_state->status.logcatMessage.clear();
                m_state->status.logcatError = false;
            }
        });
    }

    void GameBuildRuntime::OpenLogcat() {
        m_state->Task([]() {
            SR_PLATFORM_NS::OpenAssociated(GetToolsPath().Concat("logcat.txt").ToStringView());
        });
    }
}
