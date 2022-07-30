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
#include <Types/Camera.h>
#include <Core/GUI/EditorGUI.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Core/Settings/EditorSettings.h>
#include <Utils/Common/AnyVisitor.h>

namespace SR_CORE_NS::GUI {
    void ComponentDrawer::DrawComponent(Scripting::Behaviour *&pBehaviour, EditorGUI* context, int32_t index) {
        if (!pBehaviour) {
            return;
        }

        if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Script)) {
            if (GUISystem::Instance().ImageButton(SR_FORMAT("##BehSelectBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(50), 5)) {
                auto &&scriptsPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                auto &&path = SR_UTILS_NS::FileDialog::Instance().PickFolder(scriptsPath);

                if (path.Exists()) {
                    if (auto &&newBehaviour = Scripting::Behaviour::Load(path)) {
                        pBehaviour = newBehaviour;
                    }
                }
                else if (!path.Empty()) {
                    SR_WARN("ComponentDrawer::DrawComponent() : behaviour is not found!\n\tPath: " + path.ToString());
                }
            }
        }

        ImGui::SameLine();

        ImGui::BeginGroup();
        {
            if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Reset)) {
                if (GUISystem::Instance().ImageButton(SR_FORMAT("##BehResetBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(25), 5)) {
                    pBehaviour = Scripting::Behaviour::CreateEmpty();
                }
            }

            Graphics::GUI::DrawValue("Script", pBehaviour->GetResourceId());
        }
        ImGui::EndGroup();

        if (pBehaviour->IsEmpty()) {
            return;
        }

        auto&& properties = pBehaviour->GetProperties();

        if (!properties.empty()) {
            ImGui::Separator();
            SR_UTILS_NS::GUI::DrawTextOnCenter("Properties");
        }

        for (auto&& property : properties) {
            std::any&& value = pBehaviour->GetProperty(property);

            auto&& visitor = SR_UTILS_NS::Overloaded {
                [&](int value) {
                    if (ImGui::InputInt(SR_FORMAT_C("%s##BehProp%i", property.c_str(), index), &value)) {
                        pBehaviour->SetProperty(property, value);
                    }
                },
                [&](bool value) {
                    if (ImGui::Checkbox(SR_FORMAT_C("%s##BehProp%i", property.c_str(), index), &value)) {
                        pBehaviour->SetProperty(property, value);
                    }
                },
                [&](float value) {
                    if (ImGui::InputFloat(SR_FORMAT_C("%s##BehProp%i", property.c_str(), index), &value)) {
                        pBehaviour->SetProperty(property, value);
                    }
                },
                [&](double value) {
                    if (ImGui::InputDouble(SR_FORMAT_C("%s##BehProp%i", property.c_str(), index), &value)) {
                        pBehaviour->SetProperty(property, value);
                    }
                },
                [&](auto&&) {
                    ImGui::Text("%s : [Unknown property type]", property.c_str());
                }
            };
            SR_UTILS_NS::AnyVisitor<int, bool, float, double>{}(value, visitor);
        }
    }

    void ComponentDrawer::DrawComponent(SR_GRAPH_NS::Types::Camera*& camera, EditorGUI* context, int32_t index) {
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

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::Mesh3D*& mesh3d, EditorGUI* context, int32_t index) {
        if (!mesh3d->IsCanCalculate())
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid mesh!");

        if (!mesh3d->IsCalculated())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't calculated!");

        auto&& pMaterial = mesh3d->GetMaterial();

        if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Shapes)) {
            if (GUISystem::Instance().ImageButton(SR_FORMAT("##imgMeshBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(50), 5)) {
                auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Mesh", "obj,fbx,blend" } });

                if (path.Exists()) {
                    if (auto&& pMesh = SR_GTYPES_NS::Mesh::TryLoad(path, SR_GTYPES_NS::MeshType::Static, 0)) {
                        if (pMaterial) {
                            pMesh->SetMaterial(pMaterial);
                        }

                        mesh3d = dynamic_cast<SR_GTYPES_NS::Mesh3D *>(pMesh);

                        return;
                    }
                }
            }
        }

        ImGui::SameLine();
        ImGui::BeginGroup();

        Graphics::GUI::DrawValue("Path", mesh3d->GetResourcePath(), index);
        Graphics::GUI::DrawValue("Name", mesh3d->GetGeometryName(), index);

        int32_t meshId = mesh3d->GetMeshId();
        if (Graphics::GUI::InputInt("Id", meshId, 1, true, index) && meshId >= 0) {
            auto&& path = mesh3d->GetResourcePath();

            if (auto&& pMesh = SR_GTYPES_NS::Mesh::TryLoad(path, SR_GTYPES_NS::MeshType::Static, meshId)) {
                if (pMaterial) {
                    pMesh->SetMaterial(pMaterial);
                }

                mesh3d = dynamic_cast<SR_GTYPES_NS::Mesh3D *>(pMesh);

                ImGui::EndGroup();

                return;
            }
        }

        ImGui::EndGroup();

        Graphics::GUI::DrawValue("Vertices count", mesh3d->GetVerticesCount(), index);
        Graphics::GUI::DrawValue("Indices count", mesh3d->GetIndicesCount(), index);

        ImGui::Separator();

        SR_GTYPES_NS::Material* copy = pMaterial;
        DrawComponent(copy, context, index);

        /// компилятор считает, что это недостижимый код (он ошибается)
        if (copy != pMaterial) {
            mesh3d->SetMaterial(copy);
        }
    }

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::Material *&material, EditorGUI* context, int32_t index) {
        if (material) {
            const bool readOnly = material->IsReadOnly();

            Helper::GUI::DrawTextOnCenter(readOnly ? "Material (Read only)" : "Material");

            if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Material)) {
                if (GUISystem::Instance().ImageButton(SR_FORMAT("##imgMatBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(75), 5)) {
                    auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                    auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Material", "mat" } });

                    if (path.Exists()) {
                        if (auto&& pMaterial = SR_GTYPES_NS::Material::Load(path)) {
                            material = pMaterial;
                            return;
                        }
                    }
                }
            }

            ImGui::SameLine();
            ImGui::BeginGroup();

            Graphics::GUI::DrawValue("Material", material->GetResourceId(), index);

            if (auto &&shader = material->GetShader()) {
                //Graphics::GUI::DrawValue("Shader", shader->GetName());
            }

            ImGui::EndGroup();

            DrawMaterialProps(material, context, index);
        }
    }

    void ComponentDrawer::DrawMaterialProps(SR_GTYPES_NS::Material* material, EditorGUI *context, int32_t index) {
        for (auto&& property : material->GetProperties()) {
            std::visit([&property, &material, index, context](SR_GRAPH_NS::ShaderPropertyVariant&& arg){
                if (std::holds_alternative<int32_t>(arg)) {
                    auto&& value = std::get<int32_t>(arg);
                    if (ImGui::InputInt(SR_FORMAT_C("%i##%s", property.displayName.c_str(), index), &value)) {
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
                    if (Graphics::GUI::DrawVec3Control(property.displayName, value, 0.f, 70.f, 0.01f, index)) {
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

                    void* pDescriptor = value ? value->GetDescriptor() : nullptr;

                    /// пробуем взять иконку из редактора
                    if (!pDescriptor) {
                        pDescriptor = context->GetIconDescriptor(EditorIcon::Unknown);
                    }

                    /// если нашли хоть какой-то дескриптор
                    if (pDescriptor) {
                        if (GUISystem::Instance().ImageButton(SR_FORMAT("##imgBtnTex%i", index), pDescriptor, SR_MATH_NS::IVector2(55), 3)) {
                            auto&& texturesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                            auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(texturesPath, { { "Images", "png,jpg,bmp,tga" } });

                            if (path.Exists()) {
                                if (auto&& texture = SR_GTYPES_NS::Texture::Load(path)) {
                                    material->SetTexture(&property, texture);
                                }
                            }
                        }
                    }

                    /// -------------------------

                    ImGui::SameLine();
                    ImGui::BeginGroup();

                    ImGui::Text("Property: %s", property.displayName.c_str());

                    if (value) {
                        ImGui::Text("Size: %ix%i\nChannels: %i", value->GetWidth(), value->GetHeight(), value->GetChannels());
                    }
                    else {
                        ImGui::Text("Size: None\nChannels: None");
                    }

                    std::string id = value ? value->GetResourceId() : std::string();

                    auto&& inputLabel = SR_UTILS_NS::Format("##%s-%i-mat-tex", property.displayName.c_str(), index);
                    if (ImGui::InputText(inputLabel.c_str(), &id, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_NoUndoRedo)) {
                        auto&& texture = SR_GTYPES_NS::Texture::Load(id);
                        material->SetTexture(&property, texture);
                        value = texture;
                    }

                    ImGui::EndGroup();

                    ImGui::Separator();
                }
            }, property.data);
        }
    }

    void ComponentDrawer::DrawComponent(Graphics::UI::Sprite2D *&sprite, EditorGUI *context, int32_t index) {

    }
}
