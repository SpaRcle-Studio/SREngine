#include <Engine/GUI/GameBuildExporter.h>
#include <Engine/GUI/GameBuildUI.h>
#include <Utils/Common/StringUtils.h>

namespace SR_CORE_GUI_NS {
    void GameBuildExporter::DrawLogcat(const GameBuildRuntime::Status& runtime) {
        if (!m_devicesScanned && runtime.toolsReady && !runtime.busy) {
            m_runtime.RefreshDevices();
            m_devicesScanned = true;
        }
        if (!m_logcatPackageInitialized) {
            if (const auto profile = GetActiveProfile()) {
                m_logcatPackage = profile->androidPackageId;
                m_logcatPackageInitialized = true;
            }
        }
        BuildField("Device", [&]() {
            if (SR_IMMEDIATE_GUI_NS::BeginCombo("##logcat-device", m_androidSerial.empty() ? "Select a device" : m_androidSerial.c_str())) {
                for (const auto& device : runtime.devices) {
                    if (SR_IMMEDIATE_GUI_NS::Selectable(device.description.c_str(), device.serial == m_androidSerial)) {
                        m_androidSerial = device.serial;
                        m_logcatRefresh = {};
                    }
                }
                SR_IMMEDIATE_GUI_NS::EndCombo();
            }
        });
        SR_IMMEDIATE_GUI_NS::Checkbox("Application UID only", &m_logcatAppOnly);
        BuildField("Package ID", [&]() {
            SR_IMMEDIATE_GUI_NS::InputText("##logcat-package", &m_logcatPackage);
        });
        BuildField("Minimum level", [&]() {
            if (SR_IMMEDIATE_GUI_NS::BeginCombo("##logcat-level", m_logcatPriority.c_str())) {
                for (const char* level : {"V", "D", "I", "W", "E", "F"}) {
                    if (SR_IMMEDIATE_GUI_NS::Selectable(level, m_logcatPriority == level)) {
                        m_logcatPriority = level;
                        m_logcatRefresh = {};
                    }
                }
                SR_IMMEDIATE_GUI_NS::EndCombo();
            }
        });
        BuildField("Buffers", [&]() {
            if (SR_IMMEDIATE_GUI_NS::BeginCombo("##logcat-buffer", m_logcatBuffer.c_str())) {
                for (const char* buffer : {"main + system + crash", "crash"}) {
                    if (SR_IMMEDIATE_GUI_NS::Selectable(buffer, m_logcatBuffer == buffer)) {
                        m_logcatBuffer = buffer;
                        m_logcatRefresh = {};
                    }
                }
                SR_IMMEDIATE_GUI_NS::EndCombo();
            }
        });
        BuildField("Include text / tag", [&]() {
            SR_IMMEDIATE_GUI_NS::InputText("##logcat-include", &m_logcatInclude);
        });
        BuildField("Exclude text", [&]() {
            SR_IMMEDIATE_GUI_NS::InputText("##logcat-exclude", &m_logcatExclude);
        });
        SR_IMMEDIATE_GUI_NS::Checkbox("Auto refresh", &m_logcatLive);
        SR_IMMEDIATE_GUI_NS::SameLine();
        bool jumpToEnd = SR_IMMEDIATE_GUI_NS::Checkbox("Follow tail", &m_logcatFollow) && m_logcatFollow;
        SR_IMMEDIATE_GUI_NS::SameLine();
        if (SR_IMMEDIATE_GUI_NS::Button("Jump to end")) {
            jumpToEnd = true;
        }
        SR_UTILS_NS::String visibleLog;
        SR_UTILS_NS::Vector<SR_UTILS_NS::StringView> lines;
        SR_UTILS_NS::StringUtils::Instance().SplitView(runtime.logcat, "\n", lines);
        for (const auto& line : lines) {
            if ((!m_logcatInclude.empty() && !line.contains(m_logcatInclude)) ||
                (!m_logcatExclude.empty() && line.contains(m_logcatExclude)))
            {
                continue;
            }
            visibleLog += line;
            visibleLog += '\n';
        }
        if (SR_IMMEDIATE_GUI_NS::Button("Copy visible logs")) {
            SR_IMMEDIATE_GUI_NS::CopyTextToClipboard(visibleLog.empty() ? "" : visibleLog.c_str());
        }
        SR_IMMEDIATE_GUI_NS::BeginDisabled((runtime.busy && !runtime.logcatRefreshing) || m_androidSerial.empty() || !runtime.toolsReady);
        if (SR_IMMEDIATE_GUI_NS::Button("Refresh logcat")) {
            m_logcatRefreshRequested = true;
        }
        SR_IMMEDIATE_GUI_NS::SameLine();
        if (SR_IMMEDIATE_GUI_NS::Button("Clear device buffers")) {
            m_logcatClearRequested = true;
        }
        SR_IMMEDIATE_GUI_NS::SameLine();
        if (SR_IMMEDIATE_GUI_NS::Button("Open saved snapshot")) {
            m_logcatOpenRequested = true;
        }
        SR_IMMEDIATE_GUI_NS::EndDisabled();
        const auto now = std::chrono::steady_clock::now();
        if (!runtime.busy && m_logcatClearRequested) {
            m_runtime.ClearLogcat(m_androidSerial);
            m_logcatClearRequested = false;
            m_logcatRefreshRequested = true;
        }
        else if (!runtime.busy && m_logcatOpenRequested) {
            m_runtime.OpenLogcat();
            m_logcatOpenRequested = false;
        }
        else if ((m_logcatRefreshRequested || (m_logcatLive && now - m_logcatRefresh >= std::chrono::seconds(2))) &&
            !runtime.busy && runtime.toolsReady && !m_androidSerial.empty())
        {
            m_runtime.RefreshLogcat(m_androidSerial, m_logcatAppOnly ? m_logcatPackage : SR_UTILS_NS::String(), m_logcatPriority, m_logcatBuffer);
            m_logcatRefresh = now;
            m_logcatRefreshRequested = false;
        }
        SR_IMMEDIATE_GUI_NS::TextWrapped("Last 1000 records. UID survives app restarts. Disable the application filter for system/native crash diagnostics. Snapshot: RuntimeTools/logcat.txt");
        if (!runtime.logcatMessage.empty()) {
            if (runtime.logcatError) {
                SR_IMMEDIATE_GUI_NS::WarningBox(runtime.logcatMessage.c_str());
            }
            else {
                SR_IMMEDIATE_GUI_NS::TextWrapped("%s", runtime.logcatMessage.c_str());
            }
        }
        if (SR_IMMEDIATE_GUI_NS::BeginChild("LogcatOutput", SR_MATH_NS::FVector2(0.f, 300.f),
            static_cast<SR_IMMEDIATE_GUI_NS::ChildWindowFlags>(
                SR_IMMEDIATE_GUI_NS::ChildWindowFlags::ResizeY | SR_IMMEDIATE_GUI_NS::ChildWindowFlags::Borders)))
        {
            const bool atBottom = SR_IMMEDIATE_GUI_NS::IsScrolledToBottom();
            const bool changed = visibleLog != m_logcatVisibleLog;
            SR_IMMEDIATE_GUI_NS::Text("%s", visibleLog.empty() ? "" : visibleLog.c_str());
            if (jumpToEnd || (m_logcatFollow && atBottom && changed)) {
                SR_IMMEDIATE_GUI_NS::ScrollToBottom();
            }
            m_logcatVisibleLog = std::move(visibleLog);
        }
        SR_IMMEDIATE_GUI_NS::EndChild();
    }
}
