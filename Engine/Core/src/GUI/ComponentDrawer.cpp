//
// Created by Monika on 23.02.2022.
//

#include <GUI/ComponentDrawer.h>

#include <Render/Camera.h>
#include <Environment/Basic/IShaderProgram.h>
#include <Types/Geometry/Mesh3D.h>
#include <GUI/Utils.h>
#include <Types/Texture.h>
#include <Types/Material.h>

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

    const auto&& drawTexture = [](const std::string& name, Texture* texture) {
        if (texture) {
            Graphics::GUI::DrawValue(name, texture->GetName());
        }
        else
            Graphics::GUI::DrawValue(name, "None");
    };

    if (auto&& material = mesh3d->GetMaterial()) {
        const bool readOnly = material->IsReadOnly();

        Helper::GUI::DrawTextOnCenter(readOnly ? "Material (Read only)" : "Material");

        Graphics::GUI::DrawValue("Material", material->GetResourceId());

        if (auto&& shader = material->GetShader()) {
            Graphics::GUI::DrawValue("Shader name", shader->GetName());
        }

        for (auto&& property : material->GetProperties()) {
            std::visit([&property, &material](ShaderPropertyVariant&& arg){
                if (std::holds_alternative<int32_t>(arg)) {
                    auto&& value = std::get<int32_t>(arg);
                    if (ImGui::InputInt(property.displayName.c_str(), &value)) {
                        property.data = value;
                    }
                }
                else if (std::holds_alternative<float_t>(arg)) {
                    float_t value = std::get<float_t>(arg);
                    if (ImGui::InputFloat(property.displayName.c_str(), &value)) {
                        property.data = value;
                    }
                }
                else if (std::holds_alternative<SR_MATH_NS::FVector3>(arg)) {
                    auto&& value = std::get<SR_MATH_NS::FVector3>(arg);
                    if (Graphics::GUI::DrawVec3Control(property.displayName, value, 0.f, 70.f, 0.01f)) {
                        property.data = value;
                    }
                }
                else if (std::holds_alternative<Texture*>(arg)) {
                    auto&& value = std::get<Texture*>(arg);
                    std::string id = value ? value->GetResourceId() : std::string();
                    if (ImGui::InputText(property.displayName.c_str(), &id, ImGuiInputTextFlags_EnterReturnsTrue)) {
                        auto&& texture = SR_GTYPES_NS::Texture::Load(id);
                        material->SetTexture(property, texture);
                    }
                }
            }, property.data);
        }

        /*drawTexture("Diffuse", material->GetTexture(MAT_PROPERTY_DIFFUSE_TEXTURE));
        drawTexture("Normal", material->GetTexture(MAT_PROPERTY_NORMAL_TEXTURE));
        drawTexture("Specular", material->GetTexture(MAT_PROPERTY_SPECULAR_TEXTURE));
        drawTexture("Glossiness", material->GetTexture(MAT_PROPERTY_GLOSSINESS_TEXTURE));

        auto color = material->GetColor(MAT_PROPERTY_DIFFUSE_COLOR);
        if (Graphics::GUI::DrawColorControl("Color", color, 1.f, !readOnly))
            material->SetColor(MAT_PROPERTY_DIFFUSE_COLOR, color);

        auto blending = material->IsTransparent();
        if (Graphics::GUI::CheckBox("Blend", blending))
            material->SetTransparent(blending);*/
    }
    else {
        Helper::GUI::DrawTextOnCenter("Material (Missing)");
    }
}