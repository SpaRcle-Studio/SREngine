//
// Created by Monika on 08.01.2022.
//

#include <EngineCommands.h>
#include <Engine.h>

#include <EntityComponentSystem/GameObject.h>
#include <World/Scene.h>

bool Framework::Core::Commands::GameObjectRename::Redo() {
    return false;
}

bool Framework::Core::Commands::GameObjectRename::Undo() {
    return false;
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectDelete::Redo() {
    using namespace Helper::World;

    auto entity = EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<GameObject*>(entity);

    if (!ptrRaw)
        return false;

    GameObject::Ptr& ptr = ptrRaw->GetThis();

    m_scene = ptr.Do<Scene::Ptr>([](GameObject* gm) -> Scene::Ptr { return gm->GetScene(); }, Scene::Ptr());

    /**
        Специфичная синхронизация, чтобы небыло дедлока, происходящего когда CommandManager пытается удалить объект,
        при этом блокируя его, но для удаления объекта нужно заблокировать сцену, а сцена в этот момент блокируется
        иерархией, которая натыкается на блокировку еще не уничтоженного объекта, в итоге получается цикл блокировки из трех потоков.

        Чтобы этого избежать, сперва блокируем сцену.
     */
    if (m_scene.LockIfValid()) {
        const bool result = ptr.AutoFree([this](GameObject *ptr) {
            /// резервируем все дерево сущностей, чтобы после отмены команды его можно было восстановить
            m_reserved.Reserve();
            m_backup = ptr->Save(SAVABLE_FLAG_NONE);
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

    if (m_scene.LockIfValid()) {
        const auto&& gameObjectXml = m_backup.Root().GetNode("GameObject");
        auto ptr = m_scene->Instance(gameObjectXml);

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

    hasErrors |= SR_REGISTER_CMD(cmdManager, GameObjectRename);
    hasErrors |= SR_REGISTER_CMD(cmdManager, GameObjectDelete);

    return hasErrors;
}

