//
// Created by Monika on 23.02.2022.
//

#include <GUI/ComponentDrawer.h>

#include <Render/Camera.h>
#include <Types/Geometry/Mesh3D.h>
#include <GUI/Utils.h>

using namespace Framework::Graphics::Types;
using namespace Framework::Graphics;

void Framework::Core::GUI::ComponentDrawer::DrawComponent(Camera* camera) {
    float_t cameraFar  = camera->GetFar();
    if (ImGui::InputFloat("Far", &cameraFar, 5) && cameraFar >= 0) {
        camera->SetFar(cameraFar);
    }

    float_t cameraNear = camera->GetNear();
    if (ImGui::InputFloat("Near", &cameraNear, 0.01) && cameraNear >= 0) {
        camera->SetNear(cameraNear);
    }

    if (!camera->GetWindow())
        ImGui::TextColored(ImColor(1, 0, 0, 1), "WARN: Window is missing!");

        /*
       ImGui::Separator();

       Helper::GUI::DrawTextOnCenter("PostProcessing");

       PostProcessing* post = m_postProcessing;


       float gamma = post->GetGamma();
       if (ImGui::InputFloat("Gamma", &gamma, 0.05))
           post->SetGamma(gamma);

       float exposure = post->GetExposure();
       if (ImGui::InputFloat("Exposure", &exposure, 0.05))
           post->SetExposure(exposure);

       float saturation = post->GetSaturation();
       if (ImGui::InputFloat("Saturation", &saturation, 0.05))
           post->SetSaturation(saturation);

       auto color = post->GetColorCorrection();
       if (ImGui::InputFloat3("Color correction", reinterpret_cast<float*>(&color[0]))) // TODO: maybe unsafe
           post->SetColorCorrection(color);

       ImGui::NewLine();

       bool enabled = post->GetBloomEnabled();
       if (ImGui::Checkbox("Bloom", &enabled))
           post->SetBloom(enabled);

       ImGui::NewLine();

       float bloom_intensity = post->GetBloomIntensity();
       if (ImGui::InputFloat("Bloom intensity", &bloom_intensity, 0.1))
           post->SetBloomIntensity(bloom_intensity);

       color = post->GetBloomColor();
       if (ImGui::InputFloat3("Bloom color", reinterpret_cast<float*>(&color[0]))) // TODO: maybe unsafe
           post->SetBloomColor(color);

       int bloom_amount = post->GetBloomAmount();
       if (ImGui::InputInt("Bloom amount", &bloom_amount)) {
           if (bloom_amount == 0)
               bloom_amount = 1;
           post->SetBloomAmount(bloom_amount);
       }
            */
}

void Framework::Core::GUI::ComponentDrawer::DrawComponent(Mesh3D* mesh3d) {
    Graphics::GUI::DrawValue("Mesh", mesh3d->GetResourceId());
    Graphics::GUI::DrawValue("Id", mesh3d->GetMeshId());
    Graphics::GUI::DrawValue("Geometry name", mesh3d->GetGeometryName());
    Graphics::GUI::DrawValue("Vertices count", mesh3d->GetVerticesCount());
    Graphics::GUI::DrawValue("Indices count", mesh3d->GetIndicesCount());

    if (!mesh3d->IsRegistered())
        ImGui::TextColored(ImVec4(1, 0, 0, 1), "WARN: Mesh isn't registered!");

    ImGui::Separator();

    if (auto&& material = mesh3d->GetMaterial()) {
        const bool readOnly = material->IsReadOnly();

        Helper::GUI::DrawTextOnCenter(readOnly ? "Material (Read only)" : "Material");

        Graphics::GUI::DrawValue("Material", material->GetResourceId());

        auto color = material->GetColor();
        if (Graphics::GUI::DrawColorControl("Color", color, 1.f, !readOnly))
            material->SetColor(color);

        auto blending = material->IsTransparent();
        if (Graphics::GUI::CheckBox("Blend", blending))
            material->SetTransparent(blending);
    }
    else {
        Helper::GUI::DrawTextOnCenter("Material (Missing)");
    }

    ImGui::Separator();

    if (auto&& shader = mesh3d->GetShader()) {
        Helper::GUI::DrawTextOnCenter("Shader");
        Graphics::GUI::DrawValue("Shader name", shader->GetName());
    }
    else {
        Helper::GUI::DrawTextOnCenter("Shader (Missing)", ImVec4(1, 0, 0, 1));
    }
}