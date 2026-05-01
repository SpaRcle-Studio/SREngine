//
// Created by Monika on 08.01.2022.
//

#include <Engine/EngineCommands.h>
#include <Engine/Engine.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Graphics/Render/RenderScene.h>

#include <Engine/GUI/Hierarchy.h>

namespace SR_CORE_NS::Commands {
    ChangeHierarchySelected::ChangeHierarchySelected(const EnginePtr& pEngine, SR_CORE_GUI_NS::Hierarchy* pHierarchy, const Selection& oldSelected, const Selection& newSelected)
        : Super(pEngine)
        , m_hierarchy(pHierarchy)
    {
        for (const SR_UTILS_NS::SceneObject::Ptr& pObject : oldSelected) {
            SRAssert(pObject);
            m_oldSelected.insert(pObject->GetEntityId());
        }
        for (const SR_UTILS_NS::SceneObject::Ptr& pObject : newSelected) {
            SRAssert(pObject);
            m_newSelected.insert(pObject->GetEntityId());
        }
    }

    bool ChangeHierarchySelected::Redo() {
        Selection changeSelected;
        for (SR_UTILS_NS::EntityId gmId:m_newSelected) {
            auto entity = m_scene->GetEntityController()->FindById(gmId);
            auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

            if (!pObject) {
                return false;
            }

            changeSelected.insert(pObject);
        }

        if (m_hierarchy) {
            m_hierarchy->SetSelectedImpl(changeSelected);
        }
        else {
            SRHalt("Hierarchy is nullptr!");
        }

        return true;
    }

    bool ChangeHierarchySelected::Undo() {
        Selection changeSelected;
        for (SR_UTILS_NS::EntityId gmId:m_oldSelected) {
            auto entity = m_scene->GetEntityController()->FindById(gmId);
            auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

            if (!pObject) {
                return false;
            }

            changeSelected.insert(pObject);
        }

        m_hierarchy->SetSelectedImpl(changeSelected);
        return true;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    bool GameObjectTransform::Redo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::GameObject>()) {
            auto&& pDeserializer = m_pNew->CreateDeserializer();

            SR_UTILS_NS::Transform::Ptr pTransform;
            SR_UTILS_NS::Serialization::Load(*pDeserializer, pTransform, DATA_ID);
            pObject->SetTransform(pTransform);

            return true;
        }

        return false;
    }

    bool GameObjectTransform::Undo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::GameObject>()) {
            auto&& pDeserializer = m_pOld->CreateDeserializer();

            SR_UTILS_NS::Transform::Ptr pTransform;
            SR_UTILS_NS::Serialization::Load(*pDeserializer, pTransform, DATA_ID);

            if (pTransform) {
                pObject->SetTransform(pTransform);
            }

            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    bool SceneObjectChangeProperties::Redo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            auto&& pDeserializer = m_pNew->CreateDeserializer();

            SR_UTILS_NS::Serialization::Load(*pDeserializer, *pObject, DATA_ID);
            if (auto&& pGameObject = pObject.DynamicCast<SR_UTILS_NS::GameObject>()) {
                pGameObject->OnMatrixDirty();
            }

            return true;
        }

        return false;
    }

    bool SceneObjectChangeProperties::Undo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            auto&& pDeserializer = m_pOld->CreateDeserializer();

            SR_UTILS_NS::Serialization::Load(*pDeserializer, *pObject, DATA_ID);
            if (auto&& pGameObject =pObject.DynamicCast<SR_UTILS_NS::GameObject>()) {
                pGameObject->OnMatrixDirty();
            }

            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    bool ComponentsChange::Redo() {
        SR_TRACY_ZONE;

        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::IComponentable>()) {
            auto&& pDeserializer = m_pNew->CreateDeserializer();

            std::vector<SR_UTILS_NS::Component::Ptr> components;
            SR_UTILS_NS::Serialization::Load(*pDeserializer, components, DATA_ID);
            pObject->RemoveComponents();

            for (auto&& pComponent : components) {
                pObject->AddComponent(pComponent);
            }

            return true;
        }

        return false;
    }

    bool ComponentsChange::Undo() {
        SR_TRACY_ZONE;

        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::IComponentable>()) {
            auto&& pDeserializer = m_pOld->CreateDeserializer();

            std::vector<SR_UTILS_NS::Component::Ptr> components;
            SR_UTILS_NS::Serialization::Load(*pDeserializer, components, DATA_ID);
            pObject->RemoveComponents();

            for (auto&& pComponent : components) {
                pObject->AddComponent(pComponent);
            }

            return true;
        }

        return false;
    }


    //! ----------------------------------------------------------------------------------------------------------------

    bool ComponentChange::Redo() {
        SR_TRACY_ZONE;

        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::Component>()) {
            auto&& pDeserializer = m_pNew->CreateDeserializer();
            SR_UTILS_NS::Serialization::Load(*pDeserializer, *pObject, DATA_ID);
            pObject->GetMeta()->ForEachProperty([&](auto&& property, uint64_t index) {
                property.OnChanged(pObject.Get());
            });
            return true;
        }

        return false;
    }

    bool ComponentChange::Undo() {
        SR_TRACY_ZONE;

        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::Component>()) {
            auto&& pDeserializer = m_pOld->CreateDeserializer();
            SR_UTILS_NS::Serialization::Load(*pDeserializer, *pObject, DATA_ID);
            pObject->GetMeta()->ForEachProperty([&](auto&& property, uint64_t index) {
                property.OnChanged(pObject.Get());
            });
            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    SceneObjectRename::SceneObjectRename(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::SceneObject::ObjectNameT newName)
        : Super(pEngine)
        , m_entityId(pSO->GetEntityId())
        , m_previousName(pSO->GetName())
        , m_newName(newName)
    { }

    bool SceneObjectRename::Redo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetName(m_newName);
            return true;
        }

        return false;
    }

    bool SceneObjectRename::Undo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetName(m_previousName);
            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    SceneObjectTag::SceneObjectTag(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::StringAtom newTag)
        : Super(pEngine)
        , m_entityId(pSO->GetEntityId())
        , m_previousTag(pSO->GetTag())
        , m_newTag(newTag)
    { }

    bool SceneObjectTag::Redo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetTag(m_newTag);
            return true;
        }

        return false;
    }

    bool SceneObjectTag::Undo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetTag(m_previousTag);
            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    SceneObjectLayer::SceneObjectLayer(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::StringAtom newLayer)
        : Super(pEngine)
        , m_entityId(pSO->GetEntityId())
        , m_previousLayer(pSO->GetLayer())
        , m_newLayer(newLayer)
    { }

    bool SceneObjectLayer::Redo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetLayer(m_newLayer);
            return true;
        }

        return false;
    }

    bool SceneObjectLayer::Undo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetLayer(m_previousLayer);
            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    EntityEnable::EntityEnable(const EnginePtr& pEngine, const SR_UTILS_NS::Entity::Ptr& pEntity, bool newEnabled)
        : Super(pEngine)
        , m_entityId(pEntity->GetEntityId())
        , m_newEnabled(newEnabled)
    {
        if (auto&& pSO = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>())  {
            m_previousEnabled = pSO->IsEnabled();
        }
        else if (auto&& pComponent = pEntity.DynamicCast<SR_UTILS_NS::Component>()) {
            m_previousEnabled = pComponent->IsEnabled();
        }
        else {
            SRHalt("EntityEnable::EntityEnable() : entity is not SceneObject or Component!");
        }
    }

    bool EntityEnable::Redo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);
        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetEnabled(m_newEnabled);
            return true;
        }
        if (auto&& pComponent = pEntity.DynamicCast<SR_UTILS_NS::Component>()) {
            pComponent->SetEnabled(m_newEnabled);
            return true;
        }

        return false;
    }

    bool EntityEnable::Undo() {
        auto&& pEntity = m_scene->GetEntityController()->FindById(m_entityId);
        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetEnabled(m_previousEnabled);
            return true;
        }
        if (auto&& pComponent = pEntity.DynamicCast<SR_UTILS_NS::Component>()) {
            pComponent->SetEnabled(m_previousEnabled);
            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    SceneObjectDelete::SceneObjectDelete(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO)
        : Super(pEngine)
        , m_entityId(pSO->GetEntityId())
    { }

    SceneObjectDelete::~SceneObjectDelete() {
        if (m_reserved && m_reserved->IsReserved()) {
            m_reserved->UnReserveIds();
        }
    }

    bool SceneObjectDelete::Redo() {
        auto&& pController = m_scene->GetEntityController();
        auto&& pEntity = pController->FindById(m_entityId);
        auto&& pSO = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pSO) {
            m_pBackup = nullptr;
            return false;
        }

        if (auto&& pParent = pSO->GetParent()) {
            m_parentEntityId = pParent->GetEntityId();
        }
        else {
            m_parentEntityId = SR_ID_INVALID;
        }

        m_pBackup = SR_CORE_NS::Commands::CreateSerializer();
        SR_UTILS_NS::Serialization::Save(*m_pBackup, pSO, DATA_ID);

        m_reserved = pSO->GetEntityIdList();
        m_reserved->ReserveIds();

        pSO->Destroy();

        return true;
    }

    bool SceneObjectDelete::Undo() {
        if (!m_pBackup) {
            return false;
        }

        auto&& pController = m_scene->GetEntityController();
        auto&& pDeserializer = m_pBackup->CreateDeserializer();

        SR_UTILS_NS::SceneObject::Ptr pParent;
        if (m_parentEntityId != SR_ID_INVALID) {
            auto&& pParentEntity = pController->FindById(m_parentEntityId);
            pParent = pParentEntity.DynamicCast<SR_UTILS_NS::SceneObject>();
        }

        m_reserved->UnReserveIds();

        SR_UTILS_NS::SceneObject::Ptr pObject;
        SR_UTILS_NS::Serialization::Load(*pDeserializer, pObject, DATA_ID);

        if (!pObject) {
            return false;
        }

        if (pParent) {
            pParent->AddChild(pObject);
        }
        else {
            m_scene->RegisterSceneObject(pObject);
        }

        return true;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    SceneObjectInstance::SceneObjectInstance(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO)
        : Super(pEngine)
        , m_entityId(pSO->GetEntityId())
    {
        m_parentEntityId = pSO->GetParent() ? pSO->GetParent()->GetEntityId() : SR_ID_INVALID;
    }

    SceneObjectInstance::~SceneObjectInstance() {
        if (m_reserved && m_reserved->IsReserved()) {
            m_reserved->UnReserveIds();
        }
    }

    bool SceneObjectInstance::Redo() {
        auto&& pController = m_scene->GetEntityController();

        SR_UTILS_NS::SceneObject::Ptr pParent;

        if (m_parentEntityId != SR_ID_INVALID) {
            auto&& pParentEntity = pController->FindById(m_parentEntityId);
            pParent = pParentEntity.DynamicCast<SR_UTILS_NS::SceneObject>();
            if (!pParent) {
                return false;
            }
        }

        if (m_reserved && m_reserved->IsReserved()) {
            m_reserved->UnReserveIds();
        }

        SR_UTILS_NS::SceneObject::Ptr pSO;

        auto&& pDeserializer = m_pBackup->CreateDeserializer();

        SR_UTILS_NS::Serialization::Load(*pDeserializer, pSO, DATA_ID);
        if (!pSO) {
            return false;
        }

        if (pParent) {
            pParent->AddChild(pSO);
        }
        else {
            m_scene->RegisterSceneObject(pSO);
        }

        m_entityId = pSO->GetEntityId();

        return true;
    }

    bool SceneObjectInstance::Undo() {
        auto&& pController = m_scene->GetEntityController();
        auto&& pEntity = pController->FindById(m_entityId);
        auto&& pSO = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pSO) {
            m_pBackup = nullptr;
            return false;
        }

        m_reserved = pSO->GetEntityIdList();
        m_reserved->ReserveIds();

        m_pBackup = SR_CORE_NS::Commands::CreateSerializer();
        SR_UTILS_NS::Serialization::Save(*m_pBackup, pSO, DATA_ID);

        pSO->Destroy();

        return true;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    GameObjectMove::GameObjectMove(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::EntityId newParentId)
        : Super(pEngine)
        , m_entityId(pSO->GetEntityId())
        , m_newParentId(newParentId)
        , m_previousParentId(pSO->GetParent() ? pSO->GetParent()->GetEntityId() : SR_ID_INVALID)
    { }

    bool GameObjectMove::Redo() {
        auto&& pController = m_scene->GetEntityController();
        auto&& pEntity = pController->FindById(m_entityId);
        auto&& pSO = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pSO) {
            return false;
        }

        auto&& pNewParent = m_newParentId != SR_ID_INVALID ? pController->FindById(m_newParentId).DynamicCast<SR_UTILS_NS::SceneObject>() : nullptr;
        pSO->MoveToTree(pNewParent);

        return true;
    }

    bool GameObjectMove::Undo() {
        auto&& pController = m_scene->GetEntityController();
        auto&& pEntity = pController->FindById(m_entityId);
        auto&& pSO = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pSO) {
            return false;
        }

        auto&& pNewParent = m_previousParentId != SR_ID_INVALID ? pController->FindById(m_previousParentId).DynamicCast<SR_UTILS_NS::SceneObject>() : nullptr;
        pSO->MoveToTree(pNewParent);

        return true;
    }
}