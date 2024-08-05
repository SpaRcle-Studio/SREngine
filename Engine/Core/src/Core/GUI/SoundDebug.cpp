//
// Created by Monika on 16.07.2024.
//

#include <Audio/Sound.h>
#include <Audio/SoundData.h>
#include <Audio/SoundListener.h>
#include <Audio/SoundManager.h>
#include <Core/GUI/SoundDebug.h>

namespace SR_CORE_GUI_NS {
    SoundDebug::SoundDebug()
        : Super("Sound Debug")
    { }

    void SoundDebug::Draw() {
        SR_TRACY_ZONE;

        auto&& soundManager = SR_AUDIO_NS::SoundManager::Instance();

        const auto listeners = soundManager.GetListeners();
        for (auto&& pListener : listeners) {
            ImGui::Separator();
            auto&& optParams = soundManager.GetListenerParams(pListener);
            if (!optParams) {
                ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Failed to get params!");
                continue;
            }

            const SR_AUDIO_NS::ListenerData& params = *optParams;

            ImGui::Text("Gain: %.2f", params.gain);
            ImGui::Text("Distance model: %s", SR_UTILS_NS::EnumReflector::ToStringAtom(params.distanceModel).c_str());
            ImGui::Text("Position: %.2f %.2f %.2f", params.position.x, params.position.y, params.position.z);
            ImGui::Text("Orientation: %.2f %.2f %.2f %.2f %.2f %.2f", params.orientation.x, params.orientation.y, params.orientation.z, params.orientation.w, params.orientation.x, params.orientation.y);
            ImGui::Text("Velocity: %.2f %.2f %.2f", params.velocity.x, params.velocity.y, params.velocity.z);
        }

        ImGui::Separator();

        const auto playStack = soundManager.GetPlayStack();
        for (auto&& pPlayData : playStack) {
            auto&& optParams = soundManager.GetSourceParams(pPlayData);
            ImGui::Separator();
            ImGui::Text("Sound: %s", pPlayData->pSound->GetResourcePath().c_str());
            if (!optParams) {
                ImGui::TextColored(ImVec4(1.f, 0.f, 0.f, 1.f), "Failed to get params!");
                continue;
            }

            const SR_AUDIO_NS::PlayParams& params = *optParams;

            ImGui::Text("Volume: %.2f", params.gain.value());
            ImGui::Text("Pitch: %.2f", params.pitch.value());
            ImGui::Text("Max distance: %.2f", params.maxDistance.value());
            ImGui::Text("reference distance: %.2f", params.referenceDistance.value());
            ImGui::Text("Rolloff factor: %.2f", params.rolloffFactor.value());
            ImGui::Text("Cone inner angle: %.2f", params.coneInnerAngle.value());
            ImGui::Text("Position: %.2f %.2f %.2f", params.position.value().x, params.position.value().y, params.position.value().z);
            ImGui::Text("Direction: %.2f %.2f %.2f", params.direction.value().x, params.direction.value().y, params.direction.value().z);
            ImGui::Text("Velocity: %.2f %.2f %.2f", params.velocity.value().x, params.velocity.value().y, params.velocity.value().z);
            ImGui::Text("Orientation: %.2f %.2f %.2f %.2f %.2f %.2f", params.orientation.value().x, params.orientation.value().y, params.orientation.value().z, params.orientation.value().w, params.orientation.value().x, params.orientation.value().y);
            ImGui::Text("Loop: %s", params.loop.value() ? "true" : "false");
            ImGui::Text("Offset: %.2f", pPlayData->offset);
            ImGui::Text("State: %s", pPlayData->isPlaying ? "Playing" : "Stopped");
            ImGui::Text("Failed: %s", pPlayData->isFailed ? "true" : "false");
        }
    }
}
