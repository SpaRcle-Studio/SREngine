//
// Created by Monika on 08.01.2022.
//

#include <EngineCommands.h>
#include <Engine.h>

#include <EntityComponentSystem/GameObject.h>

bool Framework::Core::Commands::GameObjectRename::Redo() {
    return false;
}

bool Framework::Core::Commands::GameObjectRename::Undo() {
    return false;
}

//!-------------------------------------------------------

bool Framework::Core::Commands::GameObjectDelete::Redo() {
    auto entity = EntityManager::Instance().FindById(m_path.Last());
    auto ptrRaw = dynamic_cast<GameObject*>(entity);

    if (!ptrRaw)
        return false;

    GameObject::Ptr& ptr = ptrRaw->GetThis();

    return ptr.AutoFree([this](GameObject* ptr) {
        m_backup = ptr->Save();
        ptr->Destroy();
    });
}

bool Framework::Core::Commands::GameObjectDelete::Undo() {
    auto&& scene = Engine::Instance().GetScene();

    if (m_backup.Valid() && scene.LockIfValid()) {
        Helper::Debug::Log(m_backup.Dump());

        const auto gameObjectXml = m_backup.Root().GetNode("GameObject");

        const auto tag = gameObjectXml.TryGetAttribute("Tag").ToString("Untagged");
        const auto enabled = gameObjectXml.TryGetAttribute("Enabled").ToBool(true);

        auto ptr = scene->Instance(gameObjectXml.GetAttribute("Name").ToString());
        ptr->GetTransform()->Load(gameObjectXml.GetNode("Transform"));

        scene.Unlock();
        return true;
    }
    else
        return false;
}

Framework::Core::Commands::GameObjectDelete::GameObjectDelete(const Helper::Types::SafePtr<Helper::GameObject> &ptr) {
    m_path = ptr->GetEntityPath();
}

//!-------------------------------------------------------

bool Framework::Core::Commands::RegisterEngineCommands() {
    bool hasErrors = false;
    auto&& cmdManager = Engine::Instance().GetCmdManager();

    hasErrors |= SR_REGISTER_CMD(cmdManager, GameObjectRename);
    hasErrors |= SR_REGISTER_CMD(cmdManager, GameObjectDelete);

    return hasErrors;
}

