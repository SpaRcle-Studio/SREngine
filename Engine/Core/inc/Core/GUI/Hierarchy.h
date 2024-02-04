//
// Created by Monika on 11.02.2022.
//

#ifndef SR_ENGINE_HIERARCHY_H
#define SR_ENGINE_HIERARCHY_H

#include <Utils/Types/SafePointer.h>
#include <Utils/World/Scene.h>
#include <Utils/Input/InputEvents.h>
#include <Utils/ECS/GameObject.h>

#include <Graphics/GUI/Widget.h>

namespace SR_CORE_GUI_NS {
    class Hierarchy : public SR_GRAPH_NS::GUI::Widget {
        static constexpr ImVec4 SR_PREFAB_COLOR_FIRST = ImVec4(39.f / 255.f, 225 / 255.f, 193.f / 255.f, 1.f);
        static constexpr ImVec4 SR_PREFAB_COLOR_SECOND = ImVec4(1.f, 140.f / 255.f, 0, 1.f);
    public:
        Hierarchy();
        ~Hierarchy() override;

    public:
        void Update(float_t dt) override;

        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;

        SR_NODISCARD const std::set<SR_UTILS_NS::GameObject::Ptr>& GetSelected() const;

        void ClearSelected();
        void SelectGameObject(const SR_UTILS_NS::GameObject::Ptr& ptr);

        void SetSelectedImpl(const std::set<SR_UTILS_NS::GameObject::Ptr>& changeSelected);

    private:
        void ExpandPath(const SR_UTILS_NS::GameObject::Ptr& gm);
        void Draw() override;
        void CheckSelected(const SR_UTILS_NS::GameObject::Ptr& gm);
        void SR_INLINE ContextMenu();
        void ChildContextMenu(const SR_UTILS_NS::GameObject::Ptr& gm, uint64_t id);
        void DrawChild(const SR_UTILS_NS::GameObject::Ptr& root, uint32_t prefabIndex);
        void SR_INLINE Copy() const;
        void SR_INLINE Paste(const SR_UTILS_NS::GameObject::Ptr& pParent = nullptr);
        void SR_INLINE Delete();

    private:
        const ImGuiTreeNodeFlags m_nodeFlagsWithChild = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        const ImGuiTreeNodeFlags m_nodeFlagsWithoutChild = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;

        SR_WORLD_NS::Scene::Ptr m_scene;
        std::list<SR_UTILS_NS::GameObject::Ptr> m_pointersHolder;
        std::set<SR_UTILS_NS::GameObject::Ptr> m_selected;
        SR_UTILS_NS::GameObject::GameObjects m_tree;

        std::atomic<bool> m_shiftPressed;

        SR_GRAPH_NS::GUI::Widget* m_sceneRunnerWidget = nullptr;

    };
}

#endif //SR_ENGINE_HIERARCHY_H
