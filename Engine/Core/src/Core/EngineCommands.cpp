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
        auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject *>(entity);

        if (!ptrRaw)
            return false;

        if (auto &&ptr = ptrRaw->GetThis()) {
            changeSelected.insert(ptr);
        }
    }

    m_hierarchy->SetSelectedImpl(changeSelected);
    return true;
}

bool Framework::Core::Commands::ChangeHierarchySelected::Undo() {
    std::set<SR_UTILS_NS::GameObject::Ptr> changeSelected;
    for (SR_UTILS_NS::EntityId gmId:m_oldSelected) {
        auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(gmId);
        auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject *>(entity);

        if (!ptrRaw)
            return false;

        if (auto &&ptr = ptrRaw->GetThis()) {
            changeSelected.insert(ptr);
        }
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
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        SR_HTYPES_NS::Marshal copy = m_newMarshal->Copy();
        ptr->SetTransform(SR_UTILS_NS::Transform::Load(copy, ptr.Get()));
        return true;
    }

    return false;
}

bool Framework::Core::Commands::GameObjectTransform::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        SR_HTYPES_NS::Marshal copy = m_oldMarshal->Copy();
        ptr->SetTransform(SR_UTILS_NS::Transform::Load(copy, ptr.Get()));
        return true;
    }
    return false;
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
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        ptr->SetName(m_newName);
        return true;
    }

    return false;
}

bool Framework::Core::Commands::GameObjectRename::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        ptr->SetName(m_previousName);
        return true;
    }
    return false;
}

Framework::Core::Commands::GameObjectRename::GameObjectRename(const SR_UTILS_NS::GameObject::Ptr& ptr, SR_UTILS_NS::GameObject::Name newName) {
    m_path = ptr->GetEntityPath();
    m_previousName = ptr->GetName();
    m_newName = std::move(newName);
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectEnable::Redo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        ptr->SetEnabled(m_newEnabled);
        return true;
    }

    return false;
}

bool Framework::Core::Commands::GameObjectEnable::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        ptr->SetEnabled(m_previousEnabled);
        return true;
    }
    return false;
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
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    auto&& ptr = ptrRaw->GetThis();

    //m_scene = ptr.Do<Scene::Ptr>([](SR_UTILS_NS::GameObject* gm) -> Scene::Ptr { return gm->GetScene(); }, Scene::Ptr());
    m_scene = ptr->GetScene();

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
        SR_SAFE_DELETE_PTR(m_backup);
        m_backup = ptr->Save(nullptr, SR_UTILS_NS::SAVABLE_FLAG_NONE);
        m_backup->SetPosition(0);
        ptr->Destroy();

        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

bool Framework::Core::Commands::GameObjectDelete::Undo() {
    if (!m_backup || !m_backup->Valid())
        return false;

    if (m_scene.RecursiveLockIfValid()) {
        auto ptr = m_scene->Instance(*m_backup);

        if (m_parent) {     ///попытка восстановить дочерность объекта
            auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_parent);
            auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);
            if (!ptrRaw)
                return false;

            auto&& parentPtr = ptrRaw->GetThis();
            parentPtr->AddChild(ptr->GetThis());
            ptr->SetParent(parentPtr);
        }

        SR_SAFE_DELETE_PTR(m_backup);
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
    SR_SAFE_DELETE_PTR(m_backup);
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectPaste::Redo() {
    if (!m_backup || !m_backup->Valid())
        return false;

    if (m_scene.RecursiveLockIfValid()) {
        SR_MAYBE_UNUSED auto gameObject = m_scene->Instance(*m_backup);
        SR_SAFE_DELETE_PTR(m_backup);
        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

bool Framework::Core::Commands::GameObjectPaste::Undo() {
    using namespace SR_WORLD_NS;

    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    auto&& ptr = ptrRaw->GetThis();

    m_scene = ptr->GetScene();

    /// та же специфичная синхронизация, что и в GameObjectDelete::Redo()
    if (m_scene.RecursiveLockIfValid()) {
        SR_HTYPES_NS::SafePtrLockGuard m_lock(m_scene->GetDataStorage().GetValue<SR_GRAPH_NS::RenderScene::Ptr>());

        /// резервируем все дерево сущностей, чтобы после отмены команды его можно было восстановить
        m_reserved.Reserve();
        SR_SAFE_DELETE_PTR(m_backup);
        m_backup = ptr->Save(nullptr, SR_UTILS_NS::SAVABLE_FLAG_NONE);
        ptr->Destroy();

        m_scene.Unlock();
        return true;
    }
    else
        return false;

    if (!m_backup || !m_backup->Valid())
        return false;

    if (m_scene.RecursiveLockIfValid()) {
        SR_MAYBE_UNUSED auto gameObject = m_scene->Instance(*m_backup);
        SR_SAFE_DELETE_PTR(m_backup);
        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

Framework::Core::Commands::GameObjectPaste::GameObjectPaste(const SR_UTILS_NS::GameObject::Ptr& ptr) {
    m_path = ptr->GetEntityPath();
    m_reserved = ptr->GetEntityTree();
}

Framework::Core::Commands::GameObjectPaste::~GameObjectPaste() {
    m_path.UnReserve();
    m_reserved.UnReserve();
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectMove::Redo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        auto parentEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_newDestinationPath.Last());
        auto parentPtrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(parentEntity);
        if (parentPtrRaw)
            ptr->MoveToTree(parentPtrRaw->GetThis());
        else
            ptr->MoveToTree(SR_UTILS_NS::GameObject::Ptr());
        return true;
    }

    return false;
}

bool Framework::Core::Commands::GameObjectMove::Undo() {
    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    if (auto&& ptr = ptrRaw->GetThis()) {
        auto parentEntity = SR_UTILS_NS::EntityManager::Instance().FindById(m_oldDestinationPath.Last());
        auto parentPtrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(parentEntity);
        if (parentPtrRaw)
            ptr->MoveToTree(parentPtrRaw->GetThis());
        else
            ptr->MoveToTree(SR_UTILS_NS::GameObject::Ptr());
        return true;
    }
    return false;
}

Framework::Core::Commands::GameObjectMove::GameObjectMove(const SR_UTILS_NS::GameObject::Ptr& ptr,
                                                                    const SR_UTILS_NS::GameObject::Ptr& newDestination) {
    m_path = ptr->GetEntityPath();
    if (newDestination)
        m_newDestinationPath = newDestination->GetEntityPath();
    SR_UTILS_NS::GameObject::Ptr parentPtr = ptr->GetParent();
    if (parentPtr)
        m_oldDestinationPath = parentPtr->GetEntityPath();
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
    hasErrors |= SR_REGISTER_REVERSIBLE_CMD(cmdManager, GameObjectPaste);

    return hasErrors;
}

