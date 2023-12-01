//
// Created by Monika on 16.02.2022.
//

#include <Graphics/Types/Camera.h>
#include <Graphics/GUI/Utils.h>

#include <Physics/LibraryImpl.h>

#include <Core/GUI/Guizmo.h>

namespace SR_CORE_GUI_NS {
    Guizmo::Guizmo(const EnginePtr& pEngine)
        : SR_UTILS_NS::InputHandler()
        , m_engine(pEngine)
    { }

    Guizmo::~Guizmo() {
        SR_SAFE_DELETE_PTR(m_marshal)
    }

    void Guizmo::Draw(const Guizmo::GameObjectPtr& gameObject, const Guizmo::GameObjectPtr& camera) {
        if (!camera.RecursiveLockIfValid()) {
            gameObject.Unlock();
            return;
        }

        if (auto&& pCamera = camera->GetComponent<SR_GRAPH_NS::Types::Camera>()) {
            ImGuizmo::SetOrthographic(false);
            ImGuizmo::SetDrawlist();

            SetRect(pCamera);

            float* view = &pCamera->GetImGuizmoView()[0][0];
            ImGuizmo::ViewManipulate(
                    view,
                    8.f,
                    ImVec2((ImGui::GetWindowPos().x + (float)ImGui::GetWindowWidth()) - 128, ImGui::GetWindowPos().y),
                    ImVec2(128, 128),
                    0x10101010
            );

            /// камера может быть выбранным объектом, поэтому может произойти двойная блокировка
            if (m_active && gameObject.RecursiveLockIfValid()) {
                m_transform = gameObject->GetTransform();
                m_barycenter = gameObject->GetBarycenter();

                DrawManipulation(pCamera);

                gameObject.Unlock();
            }
        }
        else {
            SRAssert2Once(false, "Camera component not found!");
        }

        camera.Unlock();
    }

    void Guizmo::DrawTools() {
        ImGui::PushStyleVar(ImGuiStyleVar_ChildRounding, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 0);
        ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 0));

        const ImVec4 activeColor = ImVec4(0.20, 0.35, 0.20, 1);
        const ImVec4 notActiveColor = ImVec4(0.25, 0.25, 0.25, 1);
        const ImVec4 toggleActiveColor = ImVec4(0.60, 0.50, 0.25, 1);
        const ImVec4 toggleNotActiveColor = ImVec4(0.32, 0.28, 0.25, 1);

        if (ImGui::BeginChild("GuizmoTools", ImVec2(0, 20))) {
            if (SR_GRAPH_NS::GUI::Button("T", IsTranslate() && m_active ? activeColor : notActiveColor))
                SetOperation(ImGuizmo::OPERATION::TRANSLATE);

            ImGui::SameLine();
            if (SR_GRAPH_NS::GUI::Button("R", IsRotate() && m_active ? activeColor : notActiveColor))
                SetOperation(ImGuizmo::OPERATION::ROTATE);

            ImGui::SameLine();
            if (SR_GRAPH_NS::GUI::Button(IsBounds() && m_active ? "S+" : "S", ((IsScale() || IsBounds()) && m_active) ? activeColor : notActiveColor)) {
                if (IsScale())
                    SetOperation(ImGuizmo::OPERATION::BOUNDS);
                else
                    SetOperation(ImGuizmo::OPERATION::SCALE);
            }

            ImGui::SameLine();
            if (SR_GRAPH_NS::GUI::Button("U", IsUniversal() && m_active ? activeColor : notActiveColor))
                SetOperation(ImGuizmo::OPERATION::UNIVERSAL);

            ImGui::SameLine();
            if (SR_GRAPH_NS::GUI::Button("L", IsLocal() ? toggleActiveColor : toggleNotActiveColor)) {
                if (IsLocal())
                    SetMode(ImGuizmo::MODE::WORLD);
                else
                    SetMode(ImGuizmo::MODE::LOCAL);
            }

            ImGui::SameLine();
            if (SR_GRAPH_NS::GUI::Button("C", IsCenter() ? toggleActiveColor : toggleNotActiveColor))
                m_center = !m_center;

            ImGui::SameLine();

            ImGui::SameLine();
            ImGui::Text(" [ Camera Speed ] ");

            ImGui::SameLine();
            ImGui::PushItemWidth(200.f);
            ImGui::SliderFloat("##", &m_cameraVelocityFactor, 0.01f, 10.f);
            ImGui::PopItemWidth();

            ImGui::SameLine();

            ImGui::Text(" | ");

            ImGui::SameLine();

            ImGui::PushItemWidth(150.f);

            if (ImGui::BeginCombo("View Mode", SR_UTILS_NS::EnumReflector::ToStringAtom(m_viewMode).c_str())) {
                auto&& names = SR_UTILS_NS::EnumReflector::GetNames<EditorSceneViewMode>();
                for (auto&& name : names) {
                    if (ImGui::Selectable(name.c_str())) {
                        ImGui::SetItemDefaultFocus();
                        m_viewMode = SR_UTILS_NS::EnumReflector::FromString<EditorSceneViewMode>(name);
                    }
                }

                ImGui::EndCombo();
            }

            ImGui::SameLine();

            ImGui::Text("   | ");

            ImGui::SameLine();

            if (ImGui::Button("Connect PVD")) {
                auto&& pLibrary = SR_PHYSICS_NS::PhysicsLibrary::Instance().GetActiveLibrary(SR_UTILS_NS::Measurement::Space3D);
                if (pLibrary) {
                    pLibrary->ConnectPVD();
                }
            }

            ImGui::PopItemWidth();

            ImGui::EndChild();
        }

        ImGui::PopStyleVar(5);
    }

    void Guizmo::DrawManipulation(SR_GTYPES_NS::Camera* camera) {
        if (!m_transform) {
            return;
        }

        glm::mat4 transform = GetMatrix();
        glm::mat4 view;
        glm::mat4 projection = camera->GetProjectionRef().ToGLM();

        ImGuizmo::OPERATION operation = m_operation;

        switch (m_transform->GetMeasurement()) {
            case SR_UTILS_NS::Measurement::Space3D:
                ImGuizmo::SetOrthographic(false);
                view = camera->GetImGuizmoView().ToGLM();
                break;
            case SR_UTILS_NS::Measurement::Space2D: {
                ImGuizmo::SetOrthographic(true);
                projection = camera->GetOrthogonalRef().ToGLM();
                SR_MATH_NS::Matrix4x4 matrix = SR_MATH_NS::Matrix4x4::Identity();
                matrix = matrix.RotateAxis(SR_MATH_NS::FVector3(0, 1, 0), 180);
                matrix = matrix.RotateAxis(SR_MATH_NS::FVector3(0, 0, 1), 180);
                view = matrix.ToGLM();
                operation = static_cast<ImGuizmo::OPERATION>(operation & ~ImGuizmo::OPERATION::TRANSLATE_Z);
                operation = static_cast<ImGuizmo::OPERATION>(operation & ~ImGuizmo::OPERATION::ROTATE_Z);
                operation = static_cast<ImGuizmo::OPERATION>(operation & ~ImGuizmo::OPERATION::SCALE_Z);
                break;
            }
            default:
                return;
        }

        if (ImGuizmo::Manipulate(
                glm::value_ptr(view),
                glm::value_ptr(projection),
                operation,
                m_mode,
                glm::value_ptr(transform),
                NULL, /// delta matrix
                m_snapActive ? m_snap : NULL,
                m_boundsActive ? m_bounds : NULL,
                m_snapActive && m_boundsActive ? m_boundsSnap : NULL
        )) {
            if (!IsUse()) {
                SR_SAFE_DELETE_PTR(m_marshal)
                m_marshal = m_transform->Save(SR_UTILS_NS::SavableSaveData(nullptr, SR_UTILS_NS::SavableFlagBits::SAVABLE_FLAG_NONE));
                m_isUse = true;
            }
        }
        else {
            if (IsUse() && SR_UTILS_NS::Input::Instance().GetMouseUp(SR_UTILS_NS::MouseCode::MouseLeft)) {
                auto&& cmd = new SR_CORE_NS::Commands::GameObjectTransform(m_engine, m_transform->GetGameObject(), m_marshal->CopyPtr());
                m_engine->GetCmdManager()->Execute(cmd, SR_UTILS_NS::SyncType::Async);

                SR_SAFE_DELETE_PTR(m_marshal)
                m_isUse = false;
            }
        }

        if (ImGuizmo::IsUsing()) {
            SR_MATH_NS::FVector3 translation, rotation, scale;
            SR_MATH_NS::DecomposeTransform(transform, translation, rotation, scale);

            switch (m_transform->GetMeasurement()) {
                case SR_UTILS_NS::Measurement::Space2D:
                    break;
                case SR_UTILS_NS::Measurement::Space3D:
                    translation = translation.InverseAxis(SR_MATH_NS::Axis::AXIS_X);
                    rotation = rotation.Degrees().InverseAxis(SR_MATH_NS::Axis::AXIS_YZ);
                    break;
                default:
                    break;
            }

            switch (m_operation) {
                case ImGuizmo::TRANSLATE: {
                    m_transform->SetGlobalTranslation(translation);
                    break;
                }
                case ImGuizmo::ROTATE: {
                    m_transform->SetGlobalRotation(rotation);
                    break;
                }
                case ImGuizmo::SCALE: {
                    m_transform->SetScale(scale);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void Guizmo::SetRect(SR_GTYPES_NS::Camera* pCamera) {
        ImGuiWindow *window = ImGui::GetCurrentWindow();
        if (!window || window->SkipItems)
            return;

        auto imgSize = pCamera->GetSize();

        const auto winSize = SR_MATH_NS::FVector2(window->Size.x, window->Size.y);

        const SR_MATH_NS::Unit dx = winSize.x / imgSize.x;
        const SR_MATH_NS::Unit dy = winSize.y / imgSize.y;

        if (dy > dx)
            imgSize *= dx;
        else
            imgSize *= dy;

        ImGuizmo::SetRect(
            static_cast<float_t>(ImGui::GetWindowPos().x + (winSize.x - imgSize.x) / 2.f),
            static_cast<float_t>(ImGui::GetWindowPos().y + (winSize.y - imgSize.y) / 2.f),
            imgSize.x,
            imgSize.y
        );
    }

    glm::mat4 Guizmo::GetMatrix() {
        glm::mat4 matrix;

        auto&& transformation = m_transform->GetMatrix();

        switch (m_transform->GetMeasurement()) {
            case SR_UTILS_NS::Measurement::SpaceZero:
            case SR_UTILS_NS::Measurement::Space1D:
            case SR_UTILS_NS::Measurement::Space4D:
            default:
                matrix = glm::mat4(0);
                break;
            case SR_UTILS_NS::Measurement::Space2D: {
                //const SR_MATH_NS::FVector3 rotation = transformation.GetQuat().RotateY(90.f).EulerAngle();
                matrix = glm::translate(glm::mat4(1), transformation.GetTranslate().ToGLM());
                //matrix *= mat4_cast(SR_MATH_NS::Quaternion::FromEuler(rotation).ToGLM());
                //matrix = glm::scale(matrix, transformation.GetScale().ToGLM());
                matrix = glm::scale(matrix, m_transform->GetScale().ToGLM());
                break;
            }
            case SR_UTILS_NS::Measurement::Space3D: {
                const SR_MATH_NS::FVector3 translation = transformation.GetTranslate().InverseAxis(SR_MATH_NS::Axis::AXIS_X);
                const SR_MATH_NS::FVector3 rotation = transformation.GetQuat().EulerAngle().InverseAxis(SR_MATH_NS::Axis::AXIS_YZ);
                const SR_MATH_NS::FVector3 scale = m_transform->GetScale();

                matrix = glm::translate(glm::mat4(1), translation.ToGLM());
                matrix *= mat4_cast(SR_MATH_NS::Quaternion::FromEuler(rotation).ToGLM());
                matrix = glm::scale(matrix, scale.ToGLM());
                break;
            }
        }

        return matrix;
    }

    void Guizmo::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
        switch (data->GetKeyCode()) {
            case SR_UTILS_NS::KeyCode::_1: m_active = false; break;
            case SR_UTILS_NS::KeyCode::_2: SetOperation(ImGuizmo::OPERATION::TRANSLATE); break;
            case SR_UTILS_NS::KeyCode::_3: SetOperation(ImGuizmo::OPERATION::ROTATE); break;
            case SR_UTILS_NS::KeyCode::_4: SetOperation(ImGuizmo::OPERATION::SCALE); break;
            case SR_UTILS_NS::KeyCode::_5: SetOperation(ImGuizmo::OPERATION::UNIVERSAL); break;
            default:
                break;
        }
    }

    void Guizmo::OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) {
        if (!m_transform) {
            return;
        }

        switch (data->GetKeyCode()) {
            case SR_UTILS_NS::KeyCode::F: {
                //m_transform->RotateAroundParent(SR_MATH_NS::FVector3(0, 1, 0));
                break;
            }
            default:
                break;
        }
    }
}