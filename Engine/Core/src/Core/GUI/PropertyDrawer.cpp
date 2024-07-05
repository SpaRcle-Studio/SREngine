//
// Created by Monika on 09.11.2023.
//

#include <Core/GUI/PropertyDrawer.h>
#include <Graphics/Material/UniqueMaterial.h>

namespace SR_CORE_GUI_NS {
    bool DrawMaterialProperty(const DrawPropertyContext& context, SR_GRAPH_NS::MaterialProperty* pProperty) {
        auto&& data = pProperty->GetData();

        std::visit([pProperty, &context](SR_GRAPH_NS::ShaderPropertyVariant&& arg){
            auto&& name = SR_FORMAT("{}##{}", pProperty->GetName().ToCStr(), (void*)pProperty);

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
                if (Graphics::GUI::DrawVec3Control(pProperty->GetName(), value, 0.f, 0.01f)) {
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
                    if (SR_GRAPH_GUI_NS::ImageButton(SR_FORMAT("##{}", (void*)pProperty), (void*)pDescriptor, SR_MATH_NS::IVector2(55), 3)) {
                        auto&& texturesPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(texturesPath, { { "Images", "jpeg,png,jpg,bmp,tga" } });

                        if (path.Exists()) {
                            if (auto&& pTexture = SR_GTYPES_NS::Texture::Load(path)) {
                                pProperty->SetData(pTexture);
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

                if (ImGui::InputText(SR_FORMAT_C("##texture{}", (void*)pProperty), &id, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_NoUndoRedo)) {
                    if (auto&& pTexture = SR_GTYPES_NS::Texture::Load(id)) {
                        pProperty->SetData(pTexture);
                        value = pTexture;
                    }
                }

                ImGui::EndGroup();

                ImGui::Separator();
            }
        }, data);

        return true;
    }

    bool DrawMeshMaterialProperty(const DrawPropertyContext& context, SR_GRAPH_NS::MeshMaterialProperty* pProperty) {
        ImGui::Separator();
        SR_GRAPH_GUI_NS::DrawTextOnCenter("Material");
        ImGui::Separator();

        static auto pickFileMaterialFn = []() -> SR_GRAPH_NS::FileMaterial* {
            auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
            auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder,  { { "Material", "mat" } });

            if (!path.IsEmpty()) {
                return SR_GRAPH_NS::FileMaterial::Load(path);
            }
            return nullptr;
        };

        static auto pickShaderFn = []() -> SR_GTYPES_NS::Shader* {
            auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
            auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder,  { { "Shader", "srsl" } });

            if (!path.IsEmpty()) {
                return SR_GTYPES_NS::Shader::Load(path);
            }
            return nullptr;
        };

        static const std::string materialClipboard = "SR_MATERIAL_CLIPBOARD";

        if (SR_GRAPH_GUI_NS::Button("Copy", (void*)pProperty)) {
            SR_HTYPES_NS::Marshal marshal;
            pProperty->SaveProperty(marshal);
            SR_PLATFORM_NS::TextToClipboard(materialClipboard + marshal.ToBase64());
        }

        ImGui::SameLine();

        if (SR_GRAPH_GUI_NS::Button("Paste", (void*)pProperty)) {
            if (std::string text = SR_PLATFORM_NS::GetClipboardText(); text.find(materialClipboard) == 0) {
                text.erase(0, materialClipboard.size());
                auto&& marshal = SR_HTYPES_NS::Marshal::LoadFromBase64(text);
                pProperty->LoadProperty(marshal);
            }
        }

        SR_GRAPH_GUI_NS::EnumCombo<SR_GRAPH_NS::MaterialType>("Type", pProperty->GetMaterialType(), [pProperty](auto&& value) {
            switch (value) {
                case SR_GRAPH_NS::MaterialType::File: {
                    pProperty->SetMaterial(pickFileMaterialFn());
                    break;
                }
                case SR_GRAPH_NS::MaterialType::Unique: {
                    pProperty->SetMaterial(new SR_GRAPH_NS::UniqueMaterial());
                    break;
                }
                case SR_GRAPH_NS::MaterialType::None:
                default:
                    pProperty->SetMaterial(nullptr);
                    break;
            }
        }, (void*)pProperty);

        switch (pProperty->GetMaterialType()) {
            case Graphics::MaterialType::None:
                break;
            case Graphics::MaterialType::File: {
                if (ImGui::Button(SR_FORMAT_C("Pick##Material{}", static_cast<void*>(pProperty)))) {
                    if (auto&& pNewMaterial = pickFileMaterialFn()) {
                        pProperty->SetMaterial(pNewMaterial);
                    }
                    return true;
                }

                ImGui::SameLine();

                auto&& pFileMaterial = SR_UTILS_NS::PolymorphicCast<SR_GRAPH_NS::FileMaterial>(pProperty->GetMaterial());
                std::string path = pFileMaterial->GetResourcePath().ToStringRef();
                if (ImGui::InputText(SR_FORMAT_C("Material##{}", static_cast<void*>(pProperty)), &path, ImGuiInputTextFlags_EnterReturnsTrue)) {
                    pProperty->SetMaterial(path);
                }
                break;
            }
            default:
                break;
        }

        if (auto&& pMaterial = pProperty->GetMaterial()) {
            static auto setShaderFn = [](SR_GRAPH_NS::BaseMaterial* pMaterial, SR_GTYPES_NS::Shader* pShader) {
                if (pMaterial && pShader) {
                    SR_HTYPES_NS::Marshal marshal;
                    pMaterial->GetProperties().SaveProperty(marshal);
                    marshal.SetPosition(0);
                    pMaterial->SetShader(pShader);
                    pMaterial->GetProperties().LoadProperty(marshal);
                }
            };

            if (ImGui::Button(SR_FORMAT_C("Pick##Shader{}", static_cast<void*>(pProperty)))) {
                setShaderFn(pMaterial, pickShaderFn());
            }

            ImGui::SameLine();

            auto pShader = pProperty->GetMaterial()->GetShader();
            std::string shaderPath = pShader ? pShader->GetResourcePath().ToStringRef() : "";
            if (ImGui::InputText(SR_FORMAT_C("Shader##{}", "Shader", static_cast<void*>(pProperty)), &shaderPath, ImGuiInputTextFlags_EnterReturnsTrue)) {
                if (pShader = SR_GTYPES_NS::Shader::Load(shaderPath); pShader) {
                    setShaderFn(pMaterial, pShader);
                }
            }

            DrawProperty(context, &pMaterial->GetProperties());
        }

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
        if (ImGui::Button(SR_FORMAT_C("Pick##{}", (void*)pProperty))) {
            auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
            auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, pProperty->GetFileFilter());

            if (!path.IsEmpty()) {
                pProperty->SetPath(path);
            }
        }

        if (!pProperty->GetWidgetEditor().Empty()) {
            ImGui::SameLine();

            if (ImGui::Button(SR_FORMAT_C("Edit##{}", (void*)pProperty))) {
                if (auto&& pWidget = context.pEditor->GetWidget(pProperty->GetWidgetEditor())) {
                    pWidget->OpenFile(pProperty->GetPath());
                }
            }
        }

        ImGui::SameLine();

        std::string path = pProperty->GetPath().ToString();
        if (ImGui::InputText(SR_FORMAT_C("{}##{}", pProperty->GetName().ToCStr(), (void*)pProperty), &path, ImGuiInputTextFlags_EnterReturnsTrue)) {
            pProperty->SetPath(path);
        }

        return true;
    }

    bool DrawEnumProperty(const DrawPropertyContext& context, SR_UTILS_NS::EnumProperty* pProperty) {
        auto&& label = pProperty->GetName().ToStringRef();
        SR_GRAPH_GUI_NS::EnumCombo(label, pProperty->GetEnumReflector(), pProperty->GetEnum(), [pProperty](auto&& value) {
            pProperty->SetEnum(value);
        }, pProperty->GetFilter());
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
            case SR_UTILS_NS::StandardType::FVector2: {
                auto&& value = pProperty->GetFVector2();
                if (SR_GRAPH_GUI_NS::DrawVec2Control(label, value, pProperty->GetResetValue(), pProperty->GetWidth(), pProperty->GetDrag())) {
                    pProperty->SetFVector2(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::UVector2: {
                auto&& value = pProperty->GetUVector2();
                if (SR_GRAPH_GUI_NS::DrawUVec2Control(label, value, pProperty->GetResetValue(), pProperty->GetWidth(), pProperty->GetDrag())) {
                    pProperty->SetUVector2(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::FVector3: {
                auto&& value = pProperty->GetFVector3();
                if (SR_GRAPH_GUI_NS::DrawVec3Control(label, value, pProperty->GetResetValue(), pProperty->GetDrag(), pProperty->GetWidth())) {
                    pProperty->SetFVector3(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::BVector3: {
                auto&& value = pProperty->GetBVector3();
                if (SR_GRAPH_GUI_NS::DrawBVec3Control(label, value, false, pProperty->GetWidth())) {
                    pProperty->SetBVector3(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::UnicodeString: {
                auto&& value = pProperty->GetUnicodeString();
                auto&& text = SR_UTILS_NS::Localization::UtfToUtf<char, char32_t>(value);

                if (pProperty->IsMultiline()) {
                    if (ImGui::InputTextMultiline(SR_FORMAT_C("##textBox{}", static_cast<void*>(pProperty)), &text, ImVec2(ImGui::GetWindowWidth() - 10, 100))) {
                        pProperty->SetUnicodeString(text);
                    }
                }
                else {
                    if (ImGui::InputText(SR_FORMAT_C("##textBox{}", static_cast<void*>(pProperty)), &text)) {
                        pProperty->SetUnicodeString(text);
                    }
                }
                break;
            }
            case SR_UTILS_NS::StandardType::Float: {
                float_t value = pProperty->GetFloat();

                const float_t lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
                const ImVec2 buttonSize = { lineHeight + pProperty->GetWidth(), lineHeight };

                if (SR_GRAPH_GUI_NS::DrawValueControl<SR_MATH_NS::Unit>(
                        label.c_str(), value, pProperty->GetResetValue(), buttonSize,
                        ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                        ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
                        ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, pProperty->GetDrag()
                )){
                    pProperty->SetFloat(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::Int32: {
                auto&& value = pProperty->GetInt32();
                if (SR_GRAPH_GUI_NS::InputInt(label, value, static_cast<int32_t>(pProperty->GetDrag()))) {
                    pProperty->SetInt32(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::UInt32: {
                auto&& value = pProperty->GetUInt32();
                if (SR_GRAPH_GUI_NS::UInputInt32(label, value, static_cast<uint32_t>(pProperty->GetDrag()))) {
                    pProperty->SetUInt32(value);
                }
                break;
            }
            case SR_UTILS_NS::StandardType::UInt16: {
                auto&& value = static_cast<uint32_t>(pProperty->GetUInt16());
                if (SR_GRAPH_GUI_NS::UInputInt32(label, value, static_cast<uint32_t>(pProperty->GetDrag()))) {
                    pProperty->SetUInt16(static_cast<uint16_t>(value));
                }
                break;
            }
            case SR_UTILS_NS::StandardType::Int16: {
                auto&& value = static_cast<int32_t>(pProperty->GetInt16());
                if (SR_GRAPH_GUI_NS::InputInt(label, value, static_cast<int32_t>(pProperty->GetDrag()))) {
                    pProperty->SetInt16(static_cast<int16_t>(value));
                }
                break;
            }
            default:
                ImGui::Text("Property \"%s\" has unknown type: %s",
                    pProperty->GetName().ToCStr(),
                            SR_UTILS_NS::EnumReflector::ToStringAtom(pProperty->GetStandardType()).c_str()
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

        if (pProperty->IsSameLine()) {
            ImGui::SameLine();
        }

        SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard guard(pProperty->GetPublicity() == SR_UTILS_NS::PropertyPublicity::ReadOnly);
        if (auto&& pContainer = dynamic_cast<SR_UTILS_NS::PropertyContainer*>(pProperty)) {
            if (!pContainer->GetName().Empty()) {
                ImGui::Separator();
                const std::string text = SR_FORMAT("[ {} ]", pContainer->GetName().ToCStr());
                SR_GRAPH_GUI_NS::DrawTextOnCenter(text, ImColor(0.f, 1.f, 1.f, 1.f));
            }
            return DrawPropertyContainer(context, pContainer);
        }
        else if (auto&& pStandardProperty = dynamic_cast<SR_UTILS_NS::StandardProperty*>(pProperty)) {
            return DrawStandardProperty(context, pStandardProperty);
        }
        else if (auto&& pEnumProperty = dynamic_cast<SR_UTILS_NS::EnumProperty*>(pProperty)) {
            return DrawEnumProperty(context, pEnumProperty);
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
        else if (auto&& pMeshMaterialProperty = dynamic_cast<SR_GRAPH_NS::MeshMaterialProperty*>(pProperty)) {
            return DrawMeshMaterialProperty(context, pMeshMaterialProperty);
        }
        else if (auto&& pExternalProperty = dynamic_cast<SR_UTILS_NS::ExternalProperty*>(pProperty)) {
            if (auto&& getter = pExternalProperty->GetPropertyGetter()) {
                return DrawProperty(context, getter());
            }
            return false;
        }
        else if (auto&& pEntityRefProperty = dynamic_cast<SR_UTILS_NS::EntityRefProperty*>(pProperty)) {
            SR_CORE_GUI_NS::DragDropTargetEntityRef(context.pEditor, pEntityRefProperty->GetEntityRef(), pProperty->GetName().ToCStr(), pProperty->GetWidth());
        }
        else {
            ImGui::TextColored(ImColor(1.f, 0.f, 0.f, 1.f), "No available drawer for property: %s", pProperty->GetPropertyTypeName().ToCStr());
        }

        return false;
    }

    bool DrawPropertyContainer(const DrawPropertyContext& context, const SR_UTILS_NS::PropertyContainer* pProperties) {
        bool isRendered = false;
        for (auto&& propertyInfo : pProperties->GetProperties()) {
            isRendered |= DrawProperty(context, propertyInfo.pProperty);
        }
        return isRendered;
    }
}
