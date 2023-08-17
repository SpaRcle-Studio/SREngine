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

//!-------------------------------------------------------

bool Framework::Core::Commands::ChangeHierarchySelected::Redo() {
    std::set<SR_UTILS_NS::GameObject::Ptr> changeSelected;
    for (SR_UTILS_NS::EntityId gmId:m_newSelected) {
        auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(gmId);
        auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

        if (!pObject) {
            return false;
        }

        changeSelected.insert(pObject);
    }

    m_hierarchy->SetSelectedImpl(changeSelected);
    return true;
}

bool Framework::Core::Commands::ChangeHierarchySelected::Undo() {
    std::set<SR_UTILS_NS::GameObject::Ptr> changeSelected;
    for (SR_UTILS_NS::EntityId gmId:m_oldSelected) {
        auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(gmId);
        auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

        if (!pObject) {
            return false;
        }

        changeSelected.insert(pObject);
    }

    m_hierarchy->SetSelectedImpl(changeSelected);
    return true;
}

Framework::Core::Commands::ChangeHierarchySelected::ChangeHierarchySelected(SR_CORE_NS::GUI::Hierarchy* hierarchy,
                                                              const std::set<SR_UTILS_NS::GameObject::Ptr>& oldSelected,
                                                              const std::set<SR_UTILS_NS::GameObject::Ptr>& newSelected) {
    m_hierarchy = hierarchy;
    for (const SR_UTILS_NS::GameObject::Ptr& sPtr : oldSelected) {
        SRAssert(sPtr);
        m_oldSelected.insert(sPtr->GetEntityId());
    }
    for (const SR_UTILS_NS::GameObject::Ptr& sPtr : newSelected) {
        SRAssert(sPtr);
        m_newSelected.insert(sPtr->GetEntityId());
    }
}

Framework::Core::Commands::ChangeHierarchySelected::~ChangeHierarchySelected() = default;

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectTransform::Redo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    SR_HTYPES_NS::Marshal copy = m_newMarshal->Copy();
    pObject->SetTransform(SR_UTILS_NS::Transform::Load(copy, pObject.Get()));
    return true;
}

bool Framework::Core::Commands::GameObjectTransform::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    SR_HTYPES_NS::Marshal copy = m_oldMarshal->Copy();
    pObject->SetTransform(SR_UTILS_NS::Transform::Load(copy, pObject.Get()));
    return true;
}

Framework::Core::Commands::GameObjectTransform::GameObjectTransform(const SR_UTILS_NS::GameObject::Ptr& ptr, SR_HTYPES_NS::Marshal::Ptr pOldMarshal) {
    m_path = ptr->GetEntityPath();
    m_newMarshal = ptr->GetTransform()->Save(nullptr, SR_UTILS_NS::SavableFlagBits::SAVABLE_FLAG_NONE);
    m_oldMarshal = pOldMarshal;
}

Framework::Core::Commands::GameObjectTransform::~GameObjectTransform() {
    m_path.UnReserve();
    SR_SAFE_DELETE_PTR(m_newMarshal)
    SR_SAFE_DELETE_PTR(m_oldMarshal)
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectRename::Redo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    pObject->SetName(m_newName);
    return true;
}

bool Framework::Core::Commands::GameObjectRename::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    pObject->SetName(m_previousName);
    return true;
}

Framework::Core::Commands::GameObjectRename::GameObjectRename(const SR_UTILS_NS::GameObject::Ptr& ptr, SR_UTILS_NS::GameObject::Name newName) {
    m_path = ptr->GetEntityPath();
    m_previousName = ptr->GetName();
    m_newName = std::move(newName);
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectEnable::Redo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    pObject->SetEnabled(m_newEnabled);
    return true;
}

bool Framework::Core::Commands::GameObjectEnable::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    pObject->SetEnabled(m_previousEnabled);
    return true;
}

Framework::Core::Commands::GameObjectEnable::GameObjectEnable(const SR_UTILS_NS::GameObject::Ptr& ptr, bool newEnabled) {
    m_path = ptr->GetEntityPath();
    m_previousEnabled = ptr->IsEnabled();
    m_newEnabled = newEnabled;
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectDelete::Redo() {
    using namespace SR_WORLD_NS;

    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

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
    if (m_scene.RecursiveLockIfValid()) {
        SR_HTYPES_NS::SafePtrLockGuard m_lock(m_scene->GetDataStorage().GetValue<SR_GRAPH_NS::RenderScene::Ptr>());

        /// резервируем все дерево сущностей, чтобы после отмены команды его можно было восстановить
        m_reserved.Reserve();
        SR_SAFE_DELETE_PTR(m_backup)
        if ((m_backup = pObject->Save(nullptr, SR_UTILS_NS::SAVABLE_FLAG_NONE))) {
            m_backup->SetPosition(0);
        }
        pObject->Destroy();

        m_scene.Unlock();
        return true;
    }

    return false;
}

bool Framework::Core::Commands::GameObjectDelete::Undo() {
    if (!m_backup || !m_backup->Valid()) {
        return false;
    }

    if (m_scene.RecursiveLockIfValid()) {
        SR_UTILS_NS::GameObject::Ptr ptr = m_scene->Instance(*m_backup);

        if (m_parent) {     ///попытка восстановить дочерность объекта
            auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_parent);
            auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

            if (!pObject) {
                m_scene.Unlock();
                return false;
            }

            pObject->AddChild(ptr);
        }

        SR_SAFE_DELETE_PTR(m_backup)
        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

Framework::Core::Commands::GameObjectDelete::GameObjectDelete(const SR_UTILS_NS::GameObject::Ptr& ptr) {
    m_path = ptr->GetEntityPath();
    m_reserved = ptr->GetEntityTree();
    SR_UTILS_NS::GameObject::Ptr parentPtr = ptr->GetParent();
    if (parentPtr.Valid()) {
        m_parent = parentPtr->GetEntityId();
    }
}

Framework::Core::Commands::GameObjectDelete::~GameObjectDelete() {
    m_path.UnReserve();
    m_reserved.UnReserve();
    SR_SAFE_DELETE_PTR(m_backup)
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectInstance::Redo() {
    if (!m_marshal || !m_marshal->Valid()) {
        return false;
    }

    m_scene = Engine::Instance().GetScene();
    if (m_scene.RecursiveLockIfValid()) {
        SR_UTILS_NS::GameObject::Ptr ptr = m_scene->Instance(*m_marshal);

        if (m_parent) {     ///попытка восстановить дочерность объекта
            auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_parent);
            auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

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
    }
    else
        return false;
}

bool Framework::Core::Commands::GameObjectInstance::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    m_scene = Engine::Instance().GetScene();
    /// та же специфичная синхронизация, что и в GameObjectDelete::Redo()
    if (m_scene.RecursiveLockIfValid()) {
        SR_HTYPES_NS::SafePtrLockGuard m_lock(m_scene->GetDataStorage().GetValue<SR_GRAPH_NS::RenderScene::Ptr>());

        // резервируем все дерево сущностей, чтобы после отмены команды его можно было восстановить
        m_reserved.Reserve();
        SR_SAFE_DELETE_PTR(m_marshal)
        if ((m_marshal = pObject->Save(nullptr, SR_UTILS_NS::SAVABLE_FLAG_NONE))) {
            m_marshal->SetPosition(0);
        }
        pObject->Destroy();

        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

Framework::Core::Commands::GameObjectInstance::GameObjectInstance(SR_HTYPES_NS::Marshal::Ptr pMarshal,
                                                                  const SR_UTILS_NS::GameObject::Ptr& pParent) {
    m_marshal = pMarshal;
    if (pParent.Valid()) {
        m_parent = pParent->GetEntityId();
    }
}

Framework::Core::Commands::GameObjectInstance::~GameObjectInstance() {
    m_path.UnReserve();
    m_reserved.UnReserve();
}

//!-------------------------------------------------------

bool Framework::Core::Commands::HierarchyPaste::Redo() {
    m_scene = Engine::Instance().GetScene();
    if (m_scene.RecursiveLockIfValid()) {
        auto &&count = m_marshal->Read<uint64_t>();
        if (count > 1000) {
            SR_WARN("Hierarchy::Paste() : attempting to insert a large number of objects! Count: " + SR_UTILS_NS::ToString(count))
        }

        std::set<SR_UTILS_NS::GameObject::Ptr> newSelected;
        for (uint64_t i = 0; i < count; ++i) {
            if (SR_UTILS_NS::GameObject::Ptr ptr = m_scene->Instance(*m_marshal)) {
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
            auto pParent = entity.DynamicCast<SR_UTILS_NS::GameObject>();
            if (!pParent.Valid()) {
                return false;
            }
            for (SR_UTILS_NS::GameObject::Ptr ptr : newSelected) {
                ptr->MoveToTree(pParent);
            }
        }

        m_hierarchy->SetSelectedImpl(newSelected);

        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

bool Framework::Core::Commands::HierarchyPaste::Undo() {
    /// та же специфичная синхронизация, что и в GameObjectDelete::Redo()
    m_scene = Engine::Instance().GetScene();
    if (m_scene.RecursiveLockIfValid()) {
        SR_HTYPES_NS::SafePtrLockGuard m_lock(m_scene->GetDataStorage().GetValue<SR_GRAPH_NS::RenderScene::Ptr>());

        SR_SAFE_DELETE_PTR(m_marshal)

        m_marshal = new SR_HTYPES_NS::Marshal;
        m_marshal->Write<uint64_t>(m_paths.size());
        for (auto&& path : m_paths) {
            auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(path.Last());
            auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();
            if (m_marshal = pObject->Save(m_marshal, SR_UTILS_NS::SAVABLE_FLAG_NONE); !m_marshal) {
                return false;
            }
            pObject->Destroy();
        }
        for (auto&& branch : m_reserved)
            branch.Reserve();

        m_marshal->SetPosition(0);

        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

Framework::Core::Commands::HierarchyPaste::HierarchyPaste(SR_CORE_NS::GUI::Hierarchy* hierarchy, SR_HTYPES_NS::Marshal::Ptr marshal) {
    m_hierarchy = hierarchy;
    m_marshal = marshal;
    m_marshal->SetPosition(23); ///Нужно, так как в начале любого валидного содержимого буфера обмена Hierarchy должен быть префикс "SRCopyPaste#Hierarchy"
    if (auto&& selected = m_hierarchy->GetSelected(); selected.size() == 1)
        if (auto&& pParent = selected.begin()->Get(); pParent)
            m_parent = pParent->GetEntityId();
}

Framework::Core::Commands::HierarchyPaste::~HierarchyPaste() {
    SR_SAFE_DELETE_PTR(m_marshal)
    for (auto&& path : m_paths)
        path.UnReserve();
    for (auto&& branch : m_reserved)
        branch.UnReserve();
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectMove::Redo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    auto&& parentEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_newDestinationPath.Last());
    auto&& parentPtrRaw = parentEntity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (parentPtrRaw) {
        pObject->MoveToTree(parentPtrRaw);
    }
    else {
        pObject->MoveToTree(SR_UTILS_NS::GameObject::Ptr());
    }

    return true;
}

bool Framework::Core::Commands::GameObjectMove::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto pObject = entity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (!pObject) {
        return false;
    }

    auto parentEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_oldDestinationPath.Last());
    auto parentPtrRaw = parentEntity.DynamicCast<SR_UTILS_NS::GameObject>();

    if (parentPtrRaw) {
        pObject->MoveToTree(parentPtrRaw);
    }
    else {
        pObject->MoveToTree(SR_UTILS_NS::GameObject::Ptr());
    }

    return true;
}

Framework::Core::Commands::GameObjectMove::GameObjectMove(const SR_UTILS_NS::GameObject::Ptr& ptr, const SR_UTILS_NS::GameObject::Ptr& newDestination) {
    m_path = ptr->GetEntityPath();

    if (newDestination) {
        m_newDestinationPath = newDestination->GetEntityPath();
    }

    SR_UTILS_NS::GameObject::Ptr parentPtr = ptr->GetParent();

    if (parentPtr) {
        m_oldDestinationPath = parentPtr->GetEntityPath();
    }
}

Framework::Core::Commands::GameObjectMove::~GameObjectMove() {
    m_path.UnReserve();
    m_newDestinationPath.UnReserve();
    m_oldDestinationPath.UnReserve();
}

//!-------------------------------------------------------

bool Framework::Core::Commands::RegisterEngineCommands() {
    bool hasErrors = false;
    auto&& cmdManager = Engine::Instance().GetCmdManager();

    hasErrors |= SR_REGISTER_REVERSIBLE_CMD(cmdManager, GameObjectRename);
    hasErrors |= SR_REGISTER_REVERSIBLE_CMD(cmdManager, GameObjectDelete);
    hasErrors |= SR_REGISTER_REVERSIBLE_CMD(cmdManager, HierarchyPaste);

    return hasErrors;
}

