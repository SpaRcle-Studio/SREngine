//
// Created by Monika on 09.11.2023.
//

#include <Core/GUI/PropertyDrawer.h>

namespace SR_CORE_GUI_NS {
    bool DrawMaterialProperty(const DrawPropertyContext& context, SR_GRAPH_NS::MaterialProperty* pProperty) {
        auto&& data = pProperty->GetData();

        std::visit([pProperty, &context](SR_GRAPH_NS::ShaderPropertyVariant&& arg){
            auto&& name = SR_FORMAT("%s##%p", pProperty->GetName().ToCStr(), pProperty);

            if (std::holds_alternative<int32_t>(arg)) {
                auto&& value = std::get<int32_t>(arg);
                if (ImGui::InputInt(name.c_str(), &value)) {
                    pProperty->SetData(value);
                }
            }
            else if (std::holds_alternative<float_t>(arg)) {
                float_t value = std::get<float_t>(arg);
                if (ImGui::InputFloat(name.c_str(), &value)) {
                    pProperty->SetData(value);
                }
            }
            else if (std::holds_alternative<SR_MATH_NS::FVector3>(arg)) {
                auto&& value = std::get<SR_MATH_NS::FVector3>(arg);
                if (Graphics::GUI::DrawVec3Control(pProperty->GetName(), value, 0.f, 70.f, 0.01f)) {
                    pProperty->SetData(value);
                }
            }
            else if (std::holds_alternative<SR_MATH_NS::FVector4>(arg)) {
                auto&& value = std::get<SR_MATH_NS::FVector4>(arg);
                if (Graphics::GUI::DrawColorControl(pProperty->GetName(), value, 0.f, 70.f)) {
                    pProperty->SetData(value);
                }
            }
            else if (std::holds_alternative<SR_GTYPES_NS::Texture*>(arg)) {
                auto&& value = std::get<SR_GTYPES_NS::Texture*>(arg);

                ImGui::Separator();

                void* pDescriptor = value ? value->GetDescriptor() : nullptr;

                /// пробуем взять иконку из редактора
                if (!pDescriptor) {
                    pDescriptor = context.pEditor->GetIconDescriptor(EditorIcon::Unknown);
                }

                /// если нашли хоть какой-то дескриптор
                if (pDescriptor) {
                    if (SR_GRAPH_GUI_NS::ImageButton(SR_FORMAT("##%p", pProperty), pDescriptor, SR_MATH_NS::IVector2(55), 3)) {
                        auto&& texturesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(texturesPath, { { "Images", "png,jpg,bmp,tga" } });

                        if (path.Exists()) {
                            if (auto&& texture = SR_GTYPES_NS::Texture::Load(path)) {
                                pProperty->GetMaterial()->SetTexture(pProperty, texture);
                            }
                        }
                    }
                }

                /// -------------------------

                ImGui::SameLine();
                ImGui::BeginGroup();

                ImGui::Text("Property: %s", pProperty->GetDisplayName().c_str());

                if (value) {
                    ImGui::Text("Size: %ix%i\nChannels: %i", value->GetWidth(), value->GetHeight(), value->GetChannels());
                }
                else {
                    ImGui::Text("Size: None\nChannels: None");
                }

                std::string id = value ? std::string(value->GetResourceId()) : std::string();

                if (ImGui::InputText(SR_FORMAT_C("##texture%p", pProperty), &id, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_NoUndoRedo)) {
                    auto&& texture = SR_GTYPES_NS::Texture::Load(id);
                    pProperty->GetMaterial()->SetTexture(pProperty, texture);
                    value = texture;
                }

                ImGui::EndGroup();

                ImGui::Separator();
            }
        }, data);

        return true;
    }

    bool DrawLabelProperty(const DrawPropertyContext& context, SR_UTILS_NS::LabelProperty* pProperty) {
        auto&& color = ImColor(
            pProperty->GetColor().r,
            pProperty->GetColor().g,
            pProperty->GetColor().b,
            pProperty->GetColor().a
        );

        ImGui::TextColored(color, "%s", pProperty->GetLabel().ToCStr());
        return true;
    }

    bool DrawPathProperty(const DrawPropertyContext& context, SR_UTILS_NS::PathProperty* pProperty) {
        if (ImGui::Button(SR_FORMAT_C("Pick##%i", (void*)pProperty))) {
            auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
            auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Material", "mat" } });

            if (!path.Empty()) {
                pProperty->SetPath(path);
            }
        }

        ImGui::SameLine();

        std::string path = pProperty->GetPath().ToString();
        if (ImGui::InputText(SR_FORMAT_C("%s##%p", pProperty->GetName().ToCStr(), pProperty), &path, ImGuiInputTextFlags_EnterReturnsTrue)) {
            pProperty->SetPath(path);
        }

        return true;
    }

    bool DrawStandardProperty(const DrawPropertyContext& context, SR_UTILS_NS::StandardProperty* pProperty) {
        auto&& label = pProperty->GetName().ToStringRef();

        switch (pProperty->GetStandardType()) {
            case SR_UTILS_NS::StandardType::Bool: {
                bool value = pProperty->GetBool();
                if (SR_GRAPH_GUI_NS::CheckBox(label, value)) {
                    pProperty->SetBool(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::Enum: {
                SR_GRAPH_GUI_NS::EnumCombo(label, pProperty->GetEnumReflector(), pProperty->GetEnum(), [pProperty](auto&& value) {
                    pProperty->SetEnum(value);
                });
                break;
            }
            case SR_UTILS_NS::StandardType::FVector2: {
                auto&& value = pProperty->GetFVector2();
                if (SR_GRAPH_GUI_NS::DrawVec2Control(label, value, 0.f, pProperty->GetWidth(), pProperty->GetDrag())) {
                    pProperty->SetFVector2(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::Int8:
            case SR_UTILS_NS::StandardType::UInt8:
            case SR_UTILS_NS::StandardType::Int16:
            case SR_UTILS_NS::StandardType::UInt16:
            case SR_UTILS_NS::StandardType::Int32:
            case SR_UTILS_NS::StandardType::UInt32:
            case SR_UTILS_NS::StandardType::Int64:
            case SR_UTILS_NS::StandardType::UInt64:
            case SR_UTILS_NS::StandardType::Float:
            case SR_UTILS_NS::StandardType::Double:
            case SR_UTILS_NS::StandardType::String:
            case SR_UTILS_NS::StandardType::FVector3:
            case SR_UTILS_NS::StandardType::FVector4:
            case SR_UTILS_NS::StandardType::FVector5:
            case SR_UTILS_NS::StandardType::FVector6:
            case SR_UTILS_NS::StandardType::IVector2:
            case SR_UTILS_NS::StandardType::IVector3:
            case SR_UTILS_NS::StandardType::IVector4:
            case SR_UTILS_NS::StandardType::IVector5:
            case SR_UTILS_NS::StandardType::IVector6:
            case SR_UTILS_NS::StandardType::UVector2:
            case SR_UTILS_NS::StandardType::UVector3:
            case SR_UTILS_NS::StandardType::UVector4:
            case SR_UTILS_NS::StandardType::UVector5:
            case SR_UTILS_NS::StandardType::UVector6:
            case SR_UTILS_NS::StandardType::BVector2:
            case SR_UTILS_NS::StandardType::BVector3:
            case SR_UTILS_NS::StandardType::BVector4:
            case SR_UTILS_NS::StandardType::BVector5:
            case SR_UTILS_NS::StandardType::BVector6:
            default:
                ImGui::Text("Property \"%s\" has unknown type: %s",
                    pProperty->GetName().ToCStr(),
                    SR_UTILS_NS::EnumReflector::ToString(pProperty->GetStandardType()).c_str()
                );
                break;
        }

        return true;
    }

    bool DrawProperty(const DrawPropertyContext& context, SR_UTILS_NS::Property* pProperty) {
        if (!pProperty || !pProperty->IsActive()) {
            return false;
        }

        if (pProperty->GetPublicity() == SR_UTILS_NS::PropertyPublicity::Private) {
            return false;
        }

        SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(pProperty->GetPublicity() == SR_UTILS_NS::PropertyPublicity::ReadOnly);
        if (auto&& pContainer = dynamic_cast<SR_UTILS_NS::PropertyContainer*>(pProperty)) {
            if (!pContainer->GetName().Empty()) {
                ImGui::Separator();
                const std::string text = SR_FORMAT("[ %s ]", pContainer->GetName().ToCStr());
                SR_GRAPH_GUI_NS::DrawTextOnCenter(text, ImColor(0.f, 1.f, 1.f, 1.f));
            }
            return DrawPropertyContainer(context, pContainer);
        }
        else if (auto&& pStandardProperty = dynamic_cast<SR_UTILS_NS::StandardProperty*>(pProperty)) {
            return DrawStandardProperty(context, pStandardProperty);
        }
        else if (auto&& pMaterialProperty = dynamic_cast<SR_GRAPH_NS::MaterialProperty*>(pProperty)) {
            return DrawMaterialProperty(context, pMaterialProperty);
        }
        else if (auto&& pPathProperty = dynamic_cast<SR_UTILS_NS::PathProperty*>(pProperty)) {
            return DrawPathProperty(context, pPathProperty);
        }
        else if (auto&& pLabelProperty = dynamic_cast<SR_UTILS_NS::LabelProperty*>(pProperty)) {
            return DrawLabelProperty(context, pLabelProperty);
        }
        else if (auto&& pExternalProperty = dynamic_cast<SR_UTILS_NS::ExternalProperty*>(pProperty)) {
            if (auto&& getter = pExternalProperty->GetPropertyGetter()) {
                return DrawProperty(context, getter());
            }
            return false;
        }

        return false;
    }

    bool DrawPropertyContainer(const DrawPropertyContext& context, const SR_UTILS_NS::PropertyContainer* pProperties) {
        bool isRendered = false;
        for (auto&& pProperty : pProperties->GetProperties()) {
            isRendered |= DrawProperty(context, pProperty);
        }
        return isRendered;
    }
}