//
// Created by Monika on 23.02.2022.
//

#include <Core/GUI/ComponentDrawer.h>
#include <Core/GUI/GUISystem.h>
#include <Core/GUI/EditorGUI.h>
#include <Core/GUI/DragNDropHelper.h>
#include <Core/Settings/EditorSettings.h>

#include <Utils/Types/DataStorage.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/AnyVisitor.h>
#include <Utils/Locale/Encoding.h>
#include <Utils/FileSystem/FileDialog.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/Rigidbody.h>
#include <Physics/2D/Rigidbody2D.h>
#include <Physics/3D/Rigidbody3D.h>

#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/Animator.h>
#include <Graphics/Types/Geometry/Mesh3D.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/UI/Sprite2D.h>
#include <Graphics/Render/Render.h>
#include <Graphics/Types/Material.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/UI/Anchor.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/Font/Text.h>

namespace SR_CORE_NS::GUI {
    void ComponentDrawer::DrawComponent(SR_PTYPES_NS::Rigidbody3D*& pComponent, EditorGUI* context, int32_t index) {
        auto pCopy = dynamic_cast<SR_PTYPES_NS::Rigidbody*>(pComponent);
        DrawComponent(pCopy, context, index);

        auto&& linearLock = pComponent->GetLinearLock();
        if (SR_GRAPH_NS::GUI::DrawBVec3Control("Linear lock", linearLock, false, 70.f, ++index)) {
            pComponent->SetLinearLock(linearLock);
        }

        auto&& angularLock = pComponent->GetAngularLock();
        if (SR_GRAPH_NS::GUI::DrawBVec3Control("Angular lock", angularLock, false, 70.f, ++index)) {
            pComponent->SetAngularLock(angularLock);
        }

        const bool hasMesh =
                pComponent->GetCollisionShape()->GetType() == SR_PHYSICS_NS::ShapeType::Convex3D ||
                pComponent->GetCollisionShape()->GetType() == SR_PHYSICS_NS::ShapeType::TriangleMesh3D;

        if (hasMesh) {
            if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Shapes)) {
                if (GUISystem::Instance().ImageButton(SR_FORMAT("##imgMeshBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(50), 5)) {
                    auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                    auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Mesh", "obj,pmx,fbx,blend,stl,dae" } });

                    if (path.Exists()) {
                        if (auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(path)){
                            pComponent->SetRawMesh(pRawMesh);
                            pComponent->SetShapeDirty(true);
                        }
                        else {
                            SR_ERROR("ComponentDrawer::DrawComponent() : mesh is nullptr!");
                        }
                    }
                }
            }

            int32_t meshId = pComponent->GetMeshId();
            if (Graphics::GUI::InputInt("Id", meshId, 1, true, index) && meshId >= 0) {
                pComponent->SetMeshId(meshId);
                pComponent->SetShapeDirty(true);
            }
        }

        if ((void*)pComponent != (void*)pCopy) {
            pComponent = dynamic_cast<SR_PTYPES_NS::Rigidbody3D*>(pCopy);
        }
    }

    void ComponentDrawer::DrawComponent(SR_PTYPES_NS::Rigidbody*& pComponent, EditorGUI* context, int32_t index) {
        if (!pComponent) {
            return;
        }

        static auto&& shapes = SR_UTILS_NS::EnumReflector::GetNames<SR_PHYSICS_NS::ShapeType>();
        auto shape = static_cast<int>(SR_UTILS_NS::EnumReflector::GetIndex(pComponent->GetType()));

        if (ImGui::Combo(SR_FORMAT_C("Shape##rgbd%i", index), &shape, [](void* vec, int idx, const char** out_text){
            auto&& vector = reinterpret_cast<std::vector<std::string>*>(vec);
            if (idx < 0 || idx >= vector->size())
                return false;

            *out_text = vector->at(idx).c_str();

            return true;
        }, reinterpret_cast<void*>(&shapes), shapes.size())) {
            pComponent->SetType(SR_UTILS_NS::EnumReflector::At<SR_PHYSICS_NS::ShapeType>(shape));
        }

        ComponentDrawer::DrawCollisionShape(pComponent->GetCollisionShape(), context, index);

        auto&& center = pComponent->GetCenter();
        if (Graphics::GUI::DrawVec3Control("Center", center, 0.f, 70.f, 0.01f, index)) {
            pComponent->SetCenter(center);
        }

        auto&& isTrigger = pComponent->IsTrigger();
        if (ImGui::Checkbox(SR_FORMAT_C("Is trigger##rgbd%i", index), &isTrigger)) {
            pComponent->SetIsTrigger(isTrigger);
        }

        ImGui::SameLine();

        auto&& isStatic = pComponent->IsStatic();
        if (ImGui::Checkbox(SR_FORMAT_C("Is static##rgbd%i", index), &isStatic)) {
            pComponent->SetIsStatic(isStatic);
        }

        if (!pComponent->IsStatic()) {
            auto &&mass = pComponent->GetMass();
            if (ImGui::DragFloat(SR_FORMAT_C("Mass##rgbd%i", index), &mass, 0.01f)) {
                pComponent->SetMass(mass);
            }
        }
    }

    void ComponentDrawer::DrawCollisionShape(SR_PTYPES_NS::CollisionShape* pCollisionShape, EditorGUI* context, int32_t index){
        if (!pCollisionShape){
            return;
        }

        const float_t lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
        const ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

        if (SR_PHYSICS_UTILS_NS::IsShapeHasSize(pCollisionShape->GetType())) {
            auto&& size = pCollisionShape->GetSize();

            if (Graphics::GUI::DrawVec3Control("Size", size, 0.f, 70.f, 0.1, index)) {
                pCollisionShape->SetSize(size);
            }
        }

        if (SR_PHYSICS_UTILS_NS::IsShapeHasHeight(pCollisionShape->GetType())) {
            auto&& height = pCollisionShape->GetHeight();
            if (Graphics::GUI::DrawValueControl<SR_MATH_NS::Unit>(
                        "Height", height, 0.f, buttonSize,
                        ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f },
                        ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f },
                        ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f }, nullptr, true, 0.1f, index
            )){
                pCollisionShape->SetHeight(height);
            }
        }
    }

    void ComponentDrawer::DrawComponent(Scripting::Behaviour *&pBehaviour, EditorGUI* context, int32_t index) {
        if (!pBehaviour) {
            return;
        }

        if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Script)) {
            if (GUISystem::Instance().ImageButton(SR_FORMAT("##BehSelectBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(50), 5)) {
                auto &&scriptsPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                auto &&path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(scriptsPath, { { "Source file", "cpp" } });

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
                    pBehaviour = new SR_SCRIPTING_NS::Behaviour();
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
                    if (ImGui::DragFloat(SR_FORMAT_C("%s##BehProp%i", property.c_str(), index), &value, 0.01f)) {
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

        int32_t priority = camera->GetPriority();
        if (ImGui::InputInt("Priority", &priority, 1)) {
            camera->SetPriority(priority);
        }
    }

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::Mesh3D*& pComponent, EditorGUI* context, int32_t index) {
        if (!pComponent->IsCanCalculate())
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid mesh!");

        if (!pComponent->IsCalculated())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't calculated!");

        if (!pComponent->GetRenderContext())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't registered!");

        auto&& pMaterial = pComponent->GetMaterial();

        if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Shapes)) {
            if (GUISystem::Instance().ImageButton(SR_FORMAT("##imgMeshBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(50), 5)) {
                auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Mesh", "obj,pmx,fbx,blend,stl,dae" } });

                if (path.Exists()) {
                    pComponent->SetRawMesh(path);
                }
            }
        }

        ImGui::SameLine();
        ImGui::BeginGroup();

        if (auto&& pRawMesh = pComponent->GetRawMesh()) {
            Graphics::GUI::DrawValue("Path", pRawMesh->GetResourcePath().c_str(), index);
        }
        Graphics::GUI::DrawValue("Name", pComponent->GetGeometryName(), index);

        int32_t meshId = pComponent->GetMeshId();
        if (Graphics::GUI::InputInt("Id", meshId, 1, true, index) && meshId >= 0) {
            pComponent->SetMeshId(meshId);
        }

        ImGui::EndGroup();

        Graphics::GUI::DrawValue("Vertices count", pComponent->GetVerticesCount(), index);
        Graphics::GUI::DrawValue("Indices count", pComponent->GetIndicesCount(), index);

        ImGui::Separator();

        SR_GTYPES_NS::Material* copy = pMaterial;
        DrawComponent(copy, context, index);

        /// компилятор считает, что это недостижимый код (он ошибается)
        if (copy != pMaterial) {
            pComponent->SetMaterial(copy);
        }
    }

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::SkinnedMesh*& pComponent, EditorGUI* context, int32_t index) {
        if (!pComponent->IsCanCalculate())
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid mesh!");

        if (!pComponent->IsCalculated())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't calculated!");

        if (!pComponent->GetRenderContext())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't registered!");

        if (!pComponent->IsSkeletonUsable())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "No bones from skeleton to draw!");

        if (!pComponent->GetMaterial() || !pComponent->GetMaterial()->GetShader() || pComponent->GetMaterial()->GetShader()->GetType() != SR_SRSL_NS::ShaderType::Skinned)
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid material!");

        auto&& pMaterial = pComponent->GetMaterial();

        if (auto&& pDescriptor = context->GetIconDescriptor(EditorIcon::Shapes)) {
            if (GUISystem::Instance().ImageButton(SR_FORMAT("##imgMeshBtn%i", index), pDescriptor, SR_MATH_NS::IVector2(50), 5)) {
                auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
                auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Mesh", "obj,fbx,pmx,blend,stl,dae" } });

                if (path.Exists()) {
                    pComponent->SetRawMesh(path);
                }
            }
        }

        ImGui::SameLine();
        ImGui::BeginGroup();

        if (auto&& pRawMesh = pComponent->GetRawMesh()) {
            Graphics::GUI::DrawValue("Path", pRawMesh->GetResourcePath().c_str(), index);
        }
        0x0000ffff0000ffff0000;
        Graphics::GUI::DrawValue("Name", pComponent->GetGeometryName(), index);

        int32_t meshId = pComponent->GetMeshId();
        if (Graphics::GUI::InputInt("Id", meshId, 1, true, index) && meshId >= 0) {
           pComponent->SetMeshId(meshId);
        }

        ImGui::EndGroup();

        Graphics::GUI::DrawValue("Vertices count", pComponent->GetVerticesCount(), index);
        Graphics::GUI::DrawValue("Indices count", pComponent->GetIndicesCount(), index);

        SR_CORE_GUI_NS::DragDropTargetEntityRef(pComponent->GetSkeleton(), "Hierarchy##Payload", "Skeleton", index, 260.f);

        ImGui::Separator();

        SR_GTYPES_NS::Material* copy = pMaterial;
        DrawComponent(copy, context, index);

        /// компилятор считает, что это недостижимый код (он ошибается)
        if (copy != pMaterial) {
            pComponent->SetMaterial(copy);
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

                    std::string id = value ? std::string(value->GetResourceId()) : std::string();

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

    void ComponentDrawer::DrawComponent(SR_GRAPH_NS::UI::Anchor *&anchor, EditorGUI *context, int32_t index) {

    }

    void ComponentDrawer::DrawComponent(SR_GRAPH_NS::UI::Canvas *&canvas, EditorGUI *context, int32_t index) {

    }

    void ComponentDrawer::DrawComponent(SR_GRAPH_NS::UI::Sprite2D *&sprite, EditorGUI *context, int32_t index) {
        if (!sprite->IsCanCalculate())
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid mesh!");

        if (!sprite->IsCalculated())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't calculated!");

        if (!sprite->GetRenderContext())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't registered!");

        ImGui::Separator();

        auto&& pMaterial = sprite->GetMaterial();

        SR_GTYPES_NS::Material* copy = pMaterial;
        DrawComponent(copy, context, index);

        /// компилятор считает, что это недостижимый код (он ошибается)
        if (copy != pMaterial) {
            sprite->SetMaterial(copy);
        }
    }

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::ProceduralMesh *&pComponent, EditorGUI *context, int32_t index) {
        if (!pComponent->IsCanCalculate())
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid mesh!");

        if (!pComponent->IsCalculated())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't calculated!");

        if (!pComponent->GetRenderContext())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't registered!");

        Graphics::GUI::DrawValue("Vertices count", pComponent->GetVerticesCount(), index);
        Graphics::GUI::DrawValue("Indices count", pComponent->GetIndicesCount(), index);
    }

    void ComponentDrawer::DrawComponent(SR_GTYPES_NS::Text *&pComponent, EditorGUI *context, int32_t index) {
        if (!pComponent->IsCanCalculate())
            ImGui::TextColored(ImVec4(1, 0, 0, 1), "Invalid mesh!");

        if (!pComponent->IsCalculated())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't calculated!");

        if (!pComponent->GetRenderContext())
            ImGui::TextColored(ImVec4(1, 1, 0, 1), "Mesh isn't registered!");

        auto&& text = SR_UTILS_NS::Locale::UtfToUtf<char, char32_t>(pComponent->GetText());

        if (ImGui::InputTextMultiline(SR_FORMAT_C("##textBox%i", index), &text, ImVec2(ImGui::GetWindowWidth() - 10, 100))) {
            pComponent->SetText(text);
        }

        ImGui::Text("Atlas size: %ix%i", pComponent->GetAtlasWidth(), pComponent->GetAtlasHeight());

        auto&& pMaterial = pComponent->GetMaterial();

        SR_GTYPES_NS::Material* copy = pMaterial;
        DrawComponent(copy, context, index);

        /// компилятор считает, что это недостижимый код (он ошибается)
        if (copy != pMaterial) {
            pComponent->SetMaterial(copy);
        }
    }

    void ComponentDrawer::DrawComponent(SR_ANIMATIONS_NS::Animator *&pComponent, EditorGUI *context, int32_t index) {

    }

    void ComponentDrawer::DrawComponent(SR_ANIMATIONS_NS::Skeleton *&pComponent, EditorGUI *context, int32_t index) {
        bool debug = pComponent->IsDebugEnabled();
        if (Graphics::GUI::CheckBox("Debug", debug, index)) {
            pComponent->SetDebugEnabled(debug);
        }

        if (Graphics::GUI::Button("Import", index)) {
            auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
            auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Mesh with skeleton", "fbx,pmx,blend" } });

            if (!path.Exists()) {
                return;
            }

            auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(path);
            if (!pRawMesh) {
                return;
            }

            pRawMesh->Execute([&]() -> bool {
                return Importers::ImportSkeletonFromRawMesh(pRawMesh, pComponent);
            });
            pComponent->OnAttached();
        }

        const ImGuiTreeNodeFlags nodeFlagsWithChild = ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_OpenOnArrow;
        const ImGuiTreeNodeFlags nodeFlagsWithoutChild = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;

        const SR_HTYPES_NS::Function<void(SR_ANIMATIONS_NS::Bone*)> processBone = [&](SR_ANIMATIONS_NS::Bone* pBone) {
            const ImGuiTreeNodeFlags flags = !pBone->bones.empty() ? nodeFlagsWithChild : nodeFlagsWithoutChild;

            const bool isOpen = ImGui::TreeNodeEx((void*)(intptr_t)pBone, flags, "%s", pBone->name.c_str());

            if (!isOpen || pBone->bones.empty()) {
                return;
            }

            for (auto &&pSubBone : pBone->bones) {
                processBone(pSubBone);
            }

            ImGui::TreePop();
        };

        if (pComponent->GetRootBone()) {
            processBone(pComponent->GetRootBone());
        }
    }
}
