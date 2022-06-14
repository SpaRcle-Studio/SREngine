//
// Created by Monika on 23.02.2022.
//

#include <Core/GUI/ComponentDrawer.h>

#include <Core/GUI/GUISystem.h>
#include <Utils/Types/DataStorage.h>
#include <Scripting/Base/Behaviour.h>
#include <Types/Geometry/Mesh3D.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <GUI/Utils.h>
#include <Types/Texture.h>
#include <Render/Render.h>
#include <Types/Material.h>
#include <Render/Camera.h>

namespace SR_CORE_NS::GUI {
    void ComponentDrawer::DrawComponent(Scripting::Behaviour *&pBehaviour, int32_t index) {
        if (!pBehaviour) {
            return;
        }

        if (ImGui::Button("Select script")) {
            auto&& path = SR_UTILS_NS::Path(SR_UTILS_NS::ResourceManager::Instance().GetScriptsPath()).FolderDialog();

            if (path.Exists()) {
                if (auto&& newBehaviour = Scripting::Behaviour::Load(path)) {
                    pBehaviour = newBehaviour;
                }
            }
        }

        ImGui::SameLine();

        if (ImGui::Button("Reset")) {
            pBehaviour = Scripting::Behaviour::CreateEmpty();
        }

        if (pBehaviour->IsEmpty()) {
            return;
        }

        Graphics::GUI::DrawValue("Script", pBehaviour->GetResourceId());
    }

    void ComponentDrawer::DrawComponent(SR_GRAPH_NS::Camera*& camera, int32_t index) {
        float_t cameraFar  = camera->GetFar();
        if (ImGui::InputFloat("Far", &cameraFar, 5) && cameraFar >= 0) {
            camera->SetFar(cameraFar);
        }

        float_t cameraNear = camera->GetNear();
        if (ImGui::InputFloat("Near", &cameraNear, 0.01) && cameraNear >= 0) {
            camera->SetNear(cameraNear);
        }

        float_t cameraFOV = camera->GetFOV();
        if (ImGui::InputFloat("FOV", &cameraFOV, 0.5) && cameraFOV >= 0) {
            camera->SetFOV(cameraFOV);
        }
    }

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::Mesh3D*& mesh3d, int32_t index) {
        Graphics::GUI::DrawValue("Mesh", mesh3d->GetResourceId());
        Graphics::GUI::DrawValue("Id", mesh3d->GetMeshId());
        Graphics::GUI::DrawValue("Geometry name", mesh3d->GetGeometryName());
        Graphics::GUI::DrawValue("Vertices count", mesh3d->GetVerticesCount());
        Graphics::GUI::DrawValue("Indices count", mesh3d->GetIndicesCount());

        if (!mesh3d->IsRegistered())
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "WARN: Mesh isn't registered!");

        ImGui::Separator();

        if (auto&& material = mesh3d->GetMaterial()) {
            DrawComponent(material, index);
        }
        else {
            Helper::GUI::DrawTextOnCenter("Material (Missing)");
        }
    }

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::Material *&material, int32_t index) {
        const bool readOnly = material->IsReadOnly();

        Helper::GUI::DrawTextOnCenter(readOnly ? "Material (Read only)" : "Material");

        Graphics::GUI::DrawValue("Material", material->GetResourceId());

        if (auto&& shader = material->GetShader()) {
            Graphics::GUI::DrawValue("Shader name", shader->GetName());
        }

        for (auto&& property : material->GetProperties()) {
            std::visit([&property, &material, index](SR_GRAPH_NS::ShaderPropertyVariant&& arg){
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
                else if (std::holds_alternative<SR_MATH_NS::FVector4>(arg)) {
                    auto&& value = std::get<SR_MATH_NS::FVector4>(arg);
                    if (Graphics::GUI::DrawColorControl(property.displayName, value, 0.f, true, 70.f)) {
                        property.data = value;
                    }
                }
                else if (std::holds_alternative<SR_GTYPES_NS::Texture*>(arg)) {
                    auto&& value = std::get<SR_GTYPES_NS::Texture*>(arg);

                    ImGui::Separator();

                    auto&& pDescriptor = value ? value->GetDescriptor() : SR_GTYPES_NS::Texture::GetNone();
                    if (pDescriptor) {
                        if (GUISystem::Instance().ImageButton(pDescriptor, SR_MATH_NS::IVector2(50))) {
                            auto&& path = SR_UTILS_NS::ResourceManager::Instance().GetTexturesPath().FileDialog();

                            if (path.Exists()) {
                                if (auto&& texture = SR_GTYPES_NS::Texture::Load(path)) {
                                    if (auto&& render = SR_THIS_THREAD->GetContext()->GetPointer<SR_GRAPH_NS::Render>(); render && !texture->HasRender()) {
                                        render->RegisterTexture(texture);
                                    }
                                    material->SetTexture(&property, texture);
                                }
                            }
                        }
                        ImGui::SameLine();
                    }

                    if (value) {
                        ImGui::Text("Width: %i\nHeight: %i\nChannels: %i", value->GetWidth(), value->GetHeight(), value->GetChannels());
                    }
                    else {
                        ImGui::Text("Width: None\nHeight: None\nChannels: None");
                    }

                    std::string id = value ? value->GetResourceId() : std::string();
                    if (ImGui::InputText(property.displayName.c_str(), &id, ImGuiInputTextFlags_EnterReturnsTrue)) {
                        auto&& texture = SR_GTYPES_NS::Texture::Load(id);
                        material->SetTexture(&property, texture);
                    }

                    ImGui::Separator();
                }
            }, property.data);
        }
    }
}
