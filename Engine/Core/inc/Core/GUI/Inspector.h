//
// Created by Monika on 14.02.2022.
//

#ifndef SR_ENGINE_CORE_INSPECTOR_H
#define SR_ENGINE_CORE_INSPECTOR_H

#include <Core/GUI/ComponentDrawer.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>

#include <Graphics/GUI/Widget.h>

namespace SR_UTILS_NS {
    class Transform3D;
    class Transform2D;
}

namespace SR_CORE_GUI_NS {
    class EditorGUI;
    class Hierarchy;

    class Inspector : public SR_GRAPH_GUI_NS::Widget {
    public:
        explicit Inspector(Hierarchy* hierarchy);
        ~Inspector() override = default;

    public:
        void Update(float_t dt) override;

        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene) override;

    protected:
        void Draw() override;

        void InspectGameObject();
        void InspectScene();

        void DrawComponents(SR_UTILS_NS::IComponentable* pIComponentable);

        void DrawSwitchTransform();
        void DrawTransform2D(SR_UTILS_NS::Transform2D* transform) const;
        void DrawTransform3D(SR_UTILS_NS::Transform3D* transform);

        SR_MAYBE_UNUSED void BackupTransform(const SR_UTILS_NS::GameObject::Ptr& ptr, const std::function<void()>& operation) const;

        template<typename T> SR_UTILS_NS::Component* DrawComponent(SR_UTILS_NS::Component* component, const std::string& name, uint32_t& index) {
            auto&& pComponent = dynamic_cast<T*>(component);
            auto&& context = dynamic_cast<EditorGUI*>(GetManager());

            if (!pComponent || !context) {
                return component;
            }

            SRAssert1Once(component->Valid());

            ++index;

            if (ImGui::BeginChild(SR_FORMAT_C("cmp-%s-%i"))) {
                bool enabled = pComponent->IsEnabled();
                if (ImGui::Checkbox(SR_UTILS_NS::Format("##%s-%i-checkbox", name.c_str(), index).c_str(), &enabled)) {
                    pComponent->SetEnabled(enabled);
                }

                ImGui::SameLine();

                if (ImGui::CollapsingHeader(SR_UTILS_NS::Format("[%i] %s", index, pComponent->GetComponentName().c_str()).c_str())) {
                    ComponentDrawer::DrawComponent(pComponent, context, index);
                }

                if (!ImGui::GetDragDropPayload() && ImGui::BeginDragDropSource(ImGuiDragDropFlags_SourceAllowNullID)) {
                    m_pointersHolder = { component->DynamicCast<SR_UTILS_NS::Component>() };
                    ImGui::SetDragDropPayload("InspectorComponent##Payload", &m_pointersHolder, sizeof(std::vector<SR_UTILS_NS::Component::Ptr>), ImGuiCond_Once);
                    ImGui::Text("%s ->", pComponent->GetComponentName().c_str());
                    ImGui::EndDragDropSource();
                }

                if (ImGui::BeginPopupContextWindow("InspectorMenu")) {
                    if (ImGui::BeginMenu("Remove component")) {
                        if (ImGui::MenuItem(component->GetComponentName().c_str())) {
                            component->GetParent()->RemoveComponent(component);
                            pComponent = nullptr;
                        }
                        ImGui::EndMenu();
                    }
                    ImGui::EndPopup();
                }

                ImGui::EndChild();
            }

            return dynamic_cast<SR_UTILS_NS::Component*>(pComponent);
        }

    private:
        std::list<SR_UTILS_NS::Component::Ptr> m_pointersHolder;
        SR_UTILS_NS::GameObject::Ptr m_gameObject;
        Hierarchy* m_hierarchy = nullptr;
        SR_WORLD_NS::Scene::Ptr m_scene;

        ///Для DrawTransform3D и может быть DrawTransofrm2D
        bool m_isUsed = false;
        SR_HTYPES_NS::Marshal* m_oldTransformMarshal = nullptr;
    };
}

#endif //SR_ENGINE_CORE_INSPECTOR_H
