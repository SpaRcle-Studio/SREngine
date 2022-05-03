//
// Created by Monika on 14.02.2022.
//

#ifndef SRENGINE_INSPECTOR_H
#define SRENGINE_INSPECTOR_H

#include <GUI/Widget.h>
#include <GUI/ComponentDrawer.h>
#include <EntityComponentSystem/GameObject.h>
#include <World/Scene.h>

namespace SR_UTILS_NS {
    class Transform3D;
}

namespace SR_CORE_NS::GUI {
    class Hierarchy;

    class Inspector : public Graphics::GUI::Widget {
    public:
        Inspector(Hierarchy* hierarchy);
        ~Inspector() override = default;

    public:
        void Update();

    protected:
        void Draw() override;
        void DrawComponents();
        void DrawTransform(Helper::Transform3D* transform) const;

        template<typename T> void DrawComponent(Helper::Component* component, const std::string& name, uint32_t& index) {
            auto&& pComponent = dynamic_cast<T*>(component);

            if (!pComponent)
                return;

            if (ImGui::CollapsingHeader(SR_UTILS_NS::Format("[%i] %s", index++, component->GetComponentName().c_str()).c_str()))
                ComponentDrawer::DrawComponent(pComponent);
        }

    private:
        Helper::Types::SafePtr<Helper::GameObject> m_gameObject;
        Hierarchy* m_hierarchy = nullptr;

    };
}

#endif //SRENGINE_INSPECTOR_H
