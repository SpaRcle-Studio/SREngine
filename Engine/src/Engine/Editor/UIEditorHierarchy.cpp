//
// Created by Monika on 31.01.2026.
//

#include <Engine/Editor/UIEditorHierarchy.h>

#include <Utils/World/Scene.h>

#include <Codegen/UIEditorHierarchy.generated.hpp>

namespace SpaRcle::Editor::UI {
    void ProcessHierarchyTree(const SR_UTILS_NS::Vector<SR_UTILS_NS::SceneObject::Ptr>& root, const SR_UTILS_NS::SceneObject::Ptr& pTarget, SR_UTILS_NS::SceneObject* pProto, UIEditorHierarchy* pHierarchy) {
        uint32_t used = 0;
        uint32_t childCount = pTarget->GetChildrenRef().size();

        for (auto&& pSceneObject : root) {
            used++;

            if (used >= childCount) {
                auto&& pClone = pProto->CloneSceneObject();
                pTarget->AddChild(pClone);
                if (auto&& pUIItem = pClone->GetComponent<UIEditorHierarchyItem>()) {
                    pUIItem->pHierarchy = pHierarchy->GetWeakThis<UIEditorHierarchy>();
                }
                childCount++;
            }

            auto&& pItem = pTarget->GetChildrenRef().at(used - 1).Get();
            pItem->SetEnabled(true);
            if (auto&& pUIItem = pItem->GetComponent<UIEditorHierarchyItem>()) {
                pUIItem->pSceneObject = pSceneObject;
            }
        }

        for (uint32_t i = used; i < childCount; ++i) {
            pTarget->GetChildrenRef().at(i)->SetEnabled(false);
        }
    }

    void UIEditorHierarchyItem::Update(float_t dt) {
        SR_TRACY_ZONE;

        Super::Update(dt);

        if (!pSceneObject) {
            return;
        }

        if (cachedName != pSceneObject->GetName()) {
            cachedName = pSceneObject->GetName();
            if (auto&& pText = textComponent.Get()) {
                pText->SetText(cachedName.ToStringRef());
            }
        }

        auto&& pExpandButton = expandButton.Get();
        auto&& pHierarchyStrong = pHierarchy.Lock();
        auto&& pTarget = m_targetRoot.Get();
        auto&& pProto = pHierarchyStrong->GetProto();

        if (!pTarget || !pProto || !pHierarchyStrong || !pExpandButton) {
            return;
        }

        if (pSceneObject->HasChildren()) {
            pExpandButton->SetEnabled(true);

            const bool isOpened = pHierarchyStrong->IsItemOpened(pSceneObject->GetEntityId());
            if (auto&& pArrowRight = arrowRight.Get()) {
                pArrowRight->SetEnabled(!isOpened);
            }
            if (auto&& pArrowDown = arrowDown.Get()) {
                pArrowDown->SetEnabled(isOpened);
            }

            pTarget->SetEnabled(isOpened);

            if (isOpened) {
                auto&& root = pSceneObject->GetChildrenRef();
                ProcessHierarchyTree(root, pTarget, pProto, pHierarchyStrong.Get());
            }
        }
        else {
            pTarget->SetEnabled(false);
            pExpandButton->SetEnabled(false);
        }
    }

    void UIEditorHierarchyItem::SwitchExpandCollapse() {
        SR_TRACY_ZONE;

        if (!pSceneObject) {
            return;
        }

        if (auto&& pHierarchyStrong = pHierarchy.Lock()) {
            pHierarchyStrong->SwitchItemOpened(pSceneObject->GetEntityId());
        }
    }

    void UIEditorHierarchy::Update(float_t dt) {
        SR_TRACY_ZONE;

        Super::Update(dt);

        auto&& pScene = GetScene();
        if (!pScene) {
            return;
        }

        auto&& pTarget = m_targetRoot.Get();
        auto&& pProto = m_itemProto.Get();
        if (!pTarget || !pProto) {
            return;
        }

        pProto->SetEnabled(false);
        ProcessHierarchyTree(pScene->GetRootSceneObjects(), pTarget, pProto.Get(), this);
    }

    bool UIEditorHierarchy::IsItemOpened(SR_UTILS_NS::EntityId id) const {
        return m_openedItems.count(id) > 0;
    }

    void UIEditorHierarchy::SwitchItemOpened(SR_UTILS_NS::EntityId id) {
        SR_TRACY_ZONE;

        if (IsItemOpened(id)) {
            m_openedItems.erase(id);
        }
        else {
            m_openedItems.insert(id);
        }
    }

    SR_UTILS_NS::SceneObject* UIEditorHierarchy::GetProto() const noexcept {
        return m_itemProto.Get().Get();
    }
}
