//
// Created by Monika on 08.01.2022.
//

#include <Core/EngineCommands.h>
#include <Core/Engine.h>

#include <Utils/ECS/GameObject.h>
#include <Utils/World/Scene.h>
#include <Utils/Types/SafePtrLockGuard.h>
#include <Render/RenderScene.h>

bool Framework::Core::Commands::GameObjectRename::Redo() {
    return false;
}

bool Framework::Core::Commands::GameObjectRename::Undo() {
    return false;
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectDelete::Redo() {
    using namespace SR_WORLD_NS;

    auto entity = SR_UTILS_NS::EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<SR_UTILS_NS::GameObject*>(entity);

    if (!ptrRaw)
        return false;

    auto&& ptr = ptrRaw->GetThis();

    m_scene = ptr.Do<Scene::Ptr>([](SR_UTILS_NS::GameObject* gm) -> Scene::Ptr { return gm->GetScene(); }, Scene::Ptr());

    /**
        Специфичная синхронизация, чтобы небыло дедлока, происходящего когда CommandManager пытается удалить объект,
        при этом блокируя его, но для удаления объекта нужно заблокировать сцену, а сцена в этот момент блокируется
        иерархией, которая натыкается на блокировку еще не уничтоженного объекта, в итоге получается цикл блокировки из трех потоков.

        Чтобы этого избежать, сперва блокируем сцену.
     */
    if (m_scene.LockIfValid()) {
        SR_HTYPES_NS::SafePtrLockGuard m_lock(m_scene->GetDataStorage().GetValue<SR_GRAPH_NS::RenderScene::Ptr>());

        const bool result = ptr.AutoFree([this](SR_UTILS_NS::GameObject *ptr) {
            /// резервируем все дерево сущностей, чтобы после отмены команды его можно было восстановить
            m_reserved.Reserve();
            m_backup = ptr->Save(SR_UTILS_NS::SAVABLE_FLAG_NONE);
            ptr->Destroy();
        });

        m_scene.Unlock();
        return result;
    }
    else
        return false;
}

bool Framework::Core::Commands::GameObjectDelete::Undo() {
    if (!m_backup.Valid())
        return false;

    if (m_scene.RecursiveLockIfValid()) {
        auto ptr = m_scene->Instance(m_backup);
        m_scene.Unlock();
        return true;
    }
    else
        return false;
}

Framework::Core::Commands::GameObjectDelete::GameObjectDelete(const Helper::Types::SafePtr<Helper::GameObject> &ptr) {
    m_path = ptr->GetEntityPath();
    m_reserved = ptr->GetEntityTree();
}

Framework::Core::Commands::GameObjectDelete::~GameObjectDelete() {
    m_reserved.UnReserve();
}

//!-------------------------------------------------------

bool Framework::Core::Commands::RegisterEngineCommands() {
    bool hasErrors = false;
    auto&& cmdManager = Engine::Instance().GetCmdManager();

    hasErrors |= SR_REGISTER_REVERSIBLE_CMD(cmdManager, GameObjectRename);
    hasErrors |= SR_REGISTER_REVERSIBLE_CMD(cmdManager, GameObjectDelete);

    return hasErrors;
}

