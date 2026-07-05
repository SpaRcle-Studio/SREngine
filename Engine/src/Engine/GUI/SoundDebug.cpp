//
// Created by Monika on 16.07.2024.
//

#include <Audio/Sound.h>
#include <Audio/SoundData.h>
#include <Audio/SoundListener.h>
#include <Audio/SoundManager.h>

#include <Engine/GUI/SoundDebug.h>

#include <Graphics/GUI/ImmediateGUI.h>

#include <Codegen/SoundDebug.generated.hpp>

namespace SR_CORE_GUI_NS {
    SoundDebug::SoundDebug()
        : Super("Sound Debug")
    { }

    void SoundDebug::Draw() {
        SR_TRACY_ZONE;

        auto&& soundManager = SR_AUDIO_NS::SoundManager::Instance();

        const auto listeners = soundManager.GetListeners();
        for (auto&& pListener : listeners) {
            SR_GRAPH_GUI_NS::Immediate::Separator();
            auto&& optParams = soundManager.GetListenerParams(pListener);
            if (!optParams) {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to get params!");
                continue;
            }

            const SR_AUDIO_NS::ListenerData& params = *optParams;

            SR_GRAPH_GUI_NS::Immediate::Text("Gain: %.2f", params.gain);
            SR_GRAPH_GUI_NS::Immediate::Text("Distance model: %s", SR_UTILS_NS::EnumReflector::ToStringAtom(params.distanceModel).c_str());
            SR_GRAPH_GUI_NS::Immediate::Text("Position: %.2f %.2f %.2f", params.position.x, params.position.y, params.position.z);
            SR_GRAPH_GUI_NS::Immediate::Text("Orientation: %.2f %.2f %.2f %.2f %.2f %.2f", params.orientation.x, params.orientation.y, params.orientation.z, params.orientation.w, params.orientation.x, params.orientation.y);
            SR_GRAPH_GUI_NS::Immediate::Text("Velocity: %.2f %.2f %.2f", params.velocity.x, params.velocity.y, params.velocity.z);
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        const auto playStack = soundManager.GetPlayStack();
        for (auto&& pPlayData : playStack) {
            auto&& optParams = soundManager.GetSourceParams(pPlayData);
            SR_GRAPH_GUI_NS::Immediate::Separator();
            SR_GRAPH_GUI_NS::Immediate::Text("Sound: %s", pPlayData->pSound->GetResourcePath().c_str());
            if (!optParams) {
                SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "Failed to get params!");
                continue;
            }

            const SR_AUDIO_NS::PlayParams& params = *optParams;

            SR_GRAPH_GUI_NS::Immediate::Text("Volume: %.2f", params.gain.value());
            SR_GRAPH_GUI_NS::Immediate::Text("Pitch: %.2f", params.pitch.value());
            SR_GRAPH_GUI_NS::Immediate::Text("Max distance: %.2f", params.maxDistance.value());
            SR_GRAPH_GUI_NS::Immediate::Text("reference distance: %.2f", params.referenceDistance.value());
            SR_GRAPH_GUI_NS::Immediate::Text("Rolloff factor: %.2f", params.rolloffFactor.value());
            SR_GRAPH_GUI_NS::Immediate::Text("Cone inner angle: %.2f", params.coneInnerAngle.value());
            SR_GRAPH_GUI_NS::Immediate::Text("Position: %.2f %.2f %.2f", params.position.value().x, params.position.value().y, params.position.value().z);
            SR_GRAPH_GUI_NS::Immediate::Text("Direction: %.2f %.2f %.2f", params.direction.value().x, params.direction.value().y, params.direction.value().z);
            SR_GRAPH_GUI_NS::Immediate::Text("Velocity: %.2f %.2f %.2f", params.velocity.value().x, params.velocity.value().y, params.velocity.value().z);
            SR_GRAPH_GUI_NS::Immediate::Text("Orientation: %.2f %.2f %.2f %.2f %.2f %.2f", params.orientation.value().x, params.orientation.value().y, params.orientation.value().z, params.orientation.value().w, params.orientation.value().x, params.orientation.value().y);
            SR_GRAPH_GUI_NS::Immediate::Text("Loop: %s", params.loop.value() ? "true" : "false");
            SR_GRAPH_GUI_NS::Immediate::Text("Offset: %.2f", pPlayData->offset);
            SR_GRAPH_GUI_NS::Immediate::Text("State: %s", pPlayData->isPlaying ? "Playing" : "Stopped");
            SR_GRAPH_GUI_NS::Immediate::Text("Failed: %s", pPlayData->isFailed ? "true" : "false");
        }
    }
}
