//
// Created by Monika on 31.01.2026.
//

#ifndef SR_ENGINE_CORE_EDITOR_UI_EDITOR_HIERARCHY_H
#define SR_ENGINE_CORE_EDITOR_UI_EDITOR_HIERARCHY_H

#include <Engine/stdInclude.h>

#include <Graphics/Font/Text.h>

#include <Utils/ECS/Component.h>
#include <Utils/ECS/EntityRef.h>
#include <Utils/ECS/SceneObject.h>
#include <Utils/Types/WeakPtr.h>

namespace SpaRcle::Editor::UI {
    class UIEditorHierarchy;

    /// @category(UI.Editor)
    class UIEditorHierarchyItem : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Update(float_t dt) override;

        /// @method
        void SwitchExpandCollapse();

    public:
        SR_UTILS_NS::StringAtom cachedName;
        SR_UTILS_NS::SceneObject::Ptr pSceneObject;
        SR_HTYPES_NS::WeakPtr<UIEditorHierarchy> pHierarchy;

        /// @property
        SR_UTILS_NS::EntityRef<SR_GTYPES_NS::Text> textComponent;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> expandButton;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> arrowDown;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> arrowRight;

        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_targetRoot;

    };

    /// @category(UI.Editor)
    class UIEditorHierarchy : public SR_UTILS_NS::Component {
        SR_CLASS()
        using Super = SR_UTILS_NS::Component;
    public:
        void Update(float_t dt) override;

    public:
        bool IsItemOpened(SR_UTILS_NS::EntityId id) const;
        void SwitchItemOpened(SR_UTILS_NS::EntityId id);

        SR_NODISCARD SR_UTILS_NS::SceneObject* GetProto() const noexcept;

    private:
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_targetRoot;
        /// @property
        SR_UTILS_NS::EntityRef<SR_UTILS_NS::SceneObject> m_itemProto;

        SR_UTILS_NS::Set<SR_UTILS_NS::EntityId> m_openedItems;

    };
}

#endif //SR_ENGINE_CORE_EDITOR_UI_EDITOR_HIERARCHY_H
