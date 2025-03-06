//
// Created by Monika on 08.01.2022.
//

#include <Core/EngineCommands.h>
#include <Core/Engine.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Graphics/Render/RenderScene.h>

#include <Core/GUI/Hierarchy.h>

namespace SR_CORE_NS::Commands {
    ChangeHierarchySelected::ChangeHierarchySelected(const EnginePtr& pEngine, SR_CORE_GUI_NS::Hierarchy* pHierarchy, const Selection& oldSelected, const Selection& newSelected)
        : Base(pEngine)
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
            auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(gmId);
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
            auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(gmId);
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
        auto&& pEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_entityId);

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
        auto&& pEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::GameObject>()) {
            auto&& pDeserializer = m_pOld->CreateDeserializer();

            SR_UTILS_NS::Transform::Ptr pTransform;
            SR_UTILS_NS::Serialization::Load(*pDeserializer, pTransform, DATA_ID);
            pObject->SetTransform(pTransform);

            return true;
        }

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    GameObjectRename::GameObjectRename(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& pSO, SR_UTILS_NS::SceneObject::ObjectNameT newName)
        : Super(pEngine)
        , m_entityId(pSO->GetEntityId())
        , m_previousName(pSO->GetName())
        , m_newName(newName)
    { }

    bool GameObjectRename::Redo() {
        auto&& pEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetName(m_newName);
            return true;
        }

        return false;
    }

    bool GameObjectRename::Undo() {
        auto&& pEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_entityId);

        if (auto&& pObject = pEntity.DynamicCast<SR_UTILS_NS::SceneObject>()) {
            pObject->SetName(m_previousName);
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
        auto&& pEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_entityId);
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
        auto&& pEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_entityId);
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

    GameObjectDelete::GameObjectDelete(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& ptr)
        : Base(pEngine)
    {
        m_path = ptr->GetEntityPath();
        m_reserved = ptr->GetEntityTree();
        SR_UTILS_NS::SceneObject::Ptr parentPtr = ptr->GetParent();
        if (parentPtr.Valid()) {
            m_parent = parentPtr->GetEntityId();
        }
    }

    GameObjectDelete::~GameObjectDelete() {
        m_path.UnReserve();
        m_reserved.UnReserve();
        SR_SAFE_DELETE_PTR(m_backup)
    }

    bool GameObjectDelete::Redo() {
        auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
        auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pObject) {
            return false;
        }

        m_scene = pObject->GetScene();

        /**
            Специфичная синхронизация, чтобы не было дедлока, происходящего когда CommandManager пытается удалить объект,
            при этом блокируя его, но для удаления объекта нужно заблокировать сцену, а сцена в этот момент блокируется
            иерархией, которая натыкается на блокировку еще не уничтоженного объекта, в итоге получается цикл блокировки из трех потоков.

            Чтобы этого избежать, сперва блокируем сцену.
         */
        /*if (m_scene.RecursiveLockIfValid()) {
            /// резервируем все дерево сущностей, чтобы после отмены команды его можно было восстановить
            m_reserved.Reserve();
            SR_SAFE_DELETE_PTR(m_backup)
            if ((m_backup = pObject->SaveLegacy(SR_UTILS_NS::SavableContext(nullptr, SR_UTILS_NS::SAVABLE_FLAG_NONE)))) {
                m_backup->SetPosition(0);
            }
            pObject->Destroy();

            m_scene.Unlock();
            return true;
        }*/

        return false;
    }

    bool GameObjectDelete::Undo() {
        if (!m_backup || !m_backup->Valid()) {
            return false;
        }

        /*if (m_scene.RecursiveLockIfValid()) {
            SR_UTILS_NS::SceneObject::Ptr ptr = m_scene->Instance(*m_backup);

            /// попытка восстановить дочерность объекта
            if (m_parent) {
                auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_parent);
                auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

                if (!pObject) {
                    m_scene.Unlock();
                    return false;
                }

                pObject->AddChild(ptr);
            }

            SR_SAFE_DELETE_PTR(m_backup)
            m_scene.Unlock();
            return true;
        }*/

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    GameObjectInstance::GameObjectInstance(const EnginePtr& pEngine, SR_HTYPES_NS::Marshal::Ptr pMarshal, const SR_UTILS_NS::SceneObject::Ptr& pParent)
        : Base(pEngine)
    {
        m_marshal = pMarshal;
        if (pParent.Valid()) {
            m_parent = pParent->GetEntityId();
        }
    }

    GameObjectInstance::~GameObjectInstance() {
        m_path.UnReserve();
        m_reserved.UnReserve();
    }

    bool GameObjectInstance::Redo() {
        if (!m_marshal || !m_marshal->Valid()) {
            return false;
        }

        m_scene = m_engine->GetScene();

        /*if (m_scene.RecursiveLockIfValid()) {
            SR_UTILS_NS::SceneObject::Ptr ptr = m_scene->Instance(*m_marshal);

            /// попытка восстановить дочерность объекта
            if (m_parent) {
                auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_parent);
                auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

                if (!pObject) {
                    m_scene.Unlock();
                    return false;
                }

                pObject->AddChild(ptr);
                ptr->SetParent(pObject);
            }

            m_path = ptr->GetEntityPath();
            m_reserved = ptr->GetEntityTree();

            SR_SAFE_DELETE_PTR(m_marshal)
            m_scene.Unlock();
            return true;
        }*/

        return false;
    }

    bool GameObjectInstance::Undo() {
        auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
        auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pObject) {
            return false;
        }

        m_scene = m_engine->GetScene();

        /// та же специфичная синхронизация, что и в GameObjectDelete::Redo()
        /*if (m_scene) {
            // SR_HTYPES_NS::SafePtrLockGuard m_lock(m_scene->GetDataStorage().GetValue<SR_GRAPH_NS::RenderScene::Ptr>());

            // резервируем все дерево сущностей, чтобы после отмены команды его можно было восстановить
            m_reserved.Reserve();
            SR_SAFE_DELETE_PTR(m_marshal)
            if ((m_marshal = pObject->SaveLegacy(SR_UTILS_NS::SavableContext(nullptr, SR_UTILS_NS::SAVABLE_FLAG_NONE)))) {
                m_marshal->SetPosition(0);
            }
            pObject->Destroy();
            return true;
        }*/

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    HierarchyPaste::HierarchyPaste(const EnginePtr& pEngine, SR_CORE_GUI_NS::Hierarchy* hierarchy,
            SR_HTYPES_NS::Marshal::Ptr marshal, const SR_UTILS_NS::SceneObject::Ptr& pParent = nullptr)
        : Base(pEngine)
    {
        m_hierarchy = hierarchy;
        m_marshal = marshal;
        m_marshal->SetPosition(23); ///Нужно, так как в начале любого валидного содержимого буфера обмена Hierarchy должен быть префикс "SRCopyPaste#Hierarchy", который следует пропустить
        if (pParent.Valid())
            m_parent = pParent->GetEntityId();
    }

    HierarchyPaste::~HierarchyPaste() {
        SR_SAFE_DELETE_PTR(m_marshal)
        for (auto&& path : m_paths) {
            path.UnReserve();
        }
        for (auto&& branch : m_reserved) {
            branch.UnReserve();
        }
    }

    bool HierarchyPaste::Redo() {
        m_scene = m_engine->GetScene();

        /*if (m_scene.RecursiveLockIfValid()) {
            auto &&count = m_marshal->Read<uint64_t>();
            if (count > 1000) {
                SR_WARN("Hierarchy::Paste() : attempting to insert a large number of objects! Count: " + SR_UTILS_NS::ToString(count));
            }

            std::set<SR_UTILS_NS::SceneObject::Ptr> newSelected;
            for (uint64_t i = 0; i < count; ++i) {
                if (SR_UTILS_NS::SceneObject::Ptr ptr = m_scene->Instance(*m_marshal)) {
                    newSelected.insert(ptr);
                }
                else
                    return false; ///ermmmmm
            }

            if (m_paths.empty()) { ///Исполняется единожды при начальном Redo
                for (auto&& ptr : newSelected) {
                    m_paths.emplace_back(ptr->GetEntityPath());
                    m_reserved.emplace_back(ptr->GetEntityTree());
                }
            }

            if (m_parent) {
                auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_parent);
                auto pParent = entity.DynamicCast<SR_UTILS_NS::SceneObject>();
                if (!pParent.Valid()) {
                    return false;
                }
                for (SR_UTILS_NS::SceneObject::Ptr ptr : newSelected) {
                    ptr->MoveToTree(pParent);
                }
            }

            m_hierarchy->SetSelectedImpl(newSelected); ///TODO: HierarchyPaste::Undo() тоже должен иметь смену выделенных в иерархии объектов

            m_scene.Unlock();
            return true;
        }*/

        return false;
    }

    bool HierarchyPaste::Undo() {
        /// та же специфичная синхронизация, что и в GameObjectDelete::Redo()
        m_scene = m_engine->GetScene();

        /*if (m_scene) {
            //SR_HTYPES_NS::SafePtrLockGuard m_lock(m_scene->GetDataStorage().GetValue<SR_GRAPH_NS::RenderScene::Ptr>());
            SR_SAFE_DELETE_PTR(m_marshal)

            m_marshal = new SR_HTYPES_NS::Marshal;
            m_marshal->Write<uint64_t>(m_paths.size());

            for (auto &&path : m_paths) {
                auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(path.Last());
                auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();
                if (m_marshal = pObject->SaveLegacy(SR_UTILS_NS::SavableContext(m_marshal, SR_UTILS_NS::SAVABLE_FLAG_NONE)); !m_marshal) {
                    return false;
                }
                pObject->Destroy();
            }

            for (auto &&branch : m_reserved) {
                branch.Reserve();
            }

            m_marshal->SetPosition(0);
            return true;
        }*/

        return false;
    }

    //! ----------------------------------------------------------------------------------------------------------------

    GameObjectMove::GameObjectMove(const EnginePtr& pEngine, const SR_UTILS_NS::SceneObject::Ptr& ptr, const SR_UTILS_NS::SceneObject::Ptr& newDestination)
        : Base(pEngine)
    {
        m_path = ptr->GetEntityPath();

        if (newDestination) {
            m_newDestinationPath = newDestination->GetEntityPath();
        }

        SR_UTILS_NS::SceneObject::Ptr parentPtr = ptr->GetParent();
        if (parentPtr) {
            m_oldDestinationPath = parentPtr->GetEntityPath();
        }
    }

    GameObjectMove::~GameObjectMove() {
        m_path.UnReserve();
        m_newDestinationPath.UnReserve();
        m_oldDestinationPath.UnReserve();
    }

    bool GameObjectMove::Redo() {
        auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
        auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pObject) {
            return false;
        }

        auto&& parentEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_newDestinationPath.Last());
        auto&& parentPtrRaw = parentEntity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (parentPtrRaw) {
            pObject->MoveToTree(parentPtrRaw);
        }
        else {
            pObject->MoveToTree(SR_UTILS_NS::SceneObject::Ptr());
        }

        return true;
    }

    bool GameObjectMove::Undo() {
        auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
        auto pObject = entity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (!pObject) {
            return false;
        }

        auto parentEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_oldDestinationPath.Last());
        auto parentPtrRaw = parentEntity.DynamicCast<SR_UTILS_NS::SceneObject>();

        if (parentPtrRaw) {
            pObject->MoveToTree(parentPtrRaw);
        }
        else {
            pObject->MoveToTree(SR_UTILS_NS::SceneObject::Ptr());
        }

        return true;
    }
}