

# File Hierarchy.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**Hierarchy.h**](Hierarchy_8h.md)

[Go to the documentation of this file](Hierarchy_8h.md)


```C++
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
    public:
        Hierarchy();
        ~Hierarchy() override;

    public:
        void Update(float_t dt) override;

        void SetScene(const SR_WORLD_NS::Scene::Ptr& scene) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;

        SR_NODISCARD const std::set<SR_UTILS_NS::SceneObject::Ptr>& GetSelected() const;

        void ClearSelected();
        void SelectGameObject(const SR_UTILS_NS::SceneObject::Ptr& ptr);

        void SetSelectedImpl(const std::set<SR_UTILS_NS::SceneObject::Ptr>& changeSelected);

    private:
        void ExpandPath(const SR_UTILS_NS::SceneObject::Ptr& gm);
        void Draw() override;
        void CheckSelected(const SR_UTILS_NS::SceneObject::Ptr& gm);
        void SR_INLINE ContextMenu();
        void ChildContextMenu(const SR_UTILS_NS::SceneObject::Ptr& gm, uint64_t id);
        void DrawChild(const SR_UTILS_NS::SceneObject::Ptr& root, uint32_t prefabIndex);
        void SR_INLINE Copy() const;
        void SR_INLINE Paste(const SR_UTILS_NS::SceneObject::Ptr& pParent, bool fromGUI);
        void SR_INLINE Delete();

    private:
        std::vector<SR_UTILS_NS::StringAtom> m_availableUINodes;
        SR_WORLD_NS::Scene::Ptr m_scene;
        std::list<SR_UTILS_NS::SceneObject::Ptr> m_pointersHolder;
        std::set<SR_UTILS_NS::SceneObject::Ptr> m_selected;
        std::vector<SR_UTILS_NS::SceneObject::Ptr> m_tree;

        std::atomic<bool> m_shiftPressed;

        SR_GRAPH_NS::GUI::Widget* m_sceneRunnerWidget = nullptr;

    };
}

#endif //SR_ENGINE_HIERARCHY_H
```


