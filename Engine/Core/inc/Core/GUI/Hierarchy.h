//
// Created by Monika on 11.02.2022.
//

#ifndef SRENGINE_HIERARCHY_H
#define SRENGINE_HIERARCHY_H

#include <GUI/Widget.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/World/Scene.h>
#include <Utils/Input/InputEvents.h>
#include <Utils/ECS/GameObject.h>

namespace SR_CORE_NS::GUI {
    class Hierarchy : public SR_GRAPH_NS::GUI::Widget {
    public:
        Hierarchy();
        ~Hierarchy() override;

    public:
        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene);

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;

        SR_NODISCARD std::set<Helper::GameObject::Ptr> GetSelected() const;

    private:
        void Draw() override;
        void CheckSelected(const Helper::GameObject::Ptr& gm);
        void ContextMenu(const Helper::GameObject::Ptr& gm, uint64_t id);
        void DrawChild(const Helper::GameObject::Ptr& root);
        void Copy() const;
        void Paste();

    private:
        const ImGuiTreeNodeFlags m_nodeFlagsWithChild = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        const ImGuiTreeNodeFlags m_nodeFlagsWithoutChild = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;

        SR_WORLD_NS::Scene::Ptr m_scene;
        std::list<Helper::GameObject::Ptr> m_pointersHolder;
        std::set<Helper::GameObject::Ptr> m_selected;
        std::unordered_set<Helper::GameObject::Ptr> m_tree;

        std::atomic<bool> m_shiftPressed;

        SR_GRAPH_NS::GUI::Widget* m_sceneRunnerWidget = nullptr;

    };
}

#endif //SRENGINE_HIERARCHY_H
