//
// Created by Nikita on 27.11.2020.
//

#include <Utils/ECS/Component.h>
#include <Utils/ECS/GameObject.h>
#include <Utils/ECS/Transform2D.h>
#include <Utils/ECS/ComponentManager.h>
#include <Utils/Types/Thread.h>

namespace SR_UTILS_NS {
    SR_HTYPES_NS::Marshal Component::Save(SavableFlags flags) const {
        auto marshal = Entity::Save(flags);

        marshal.Write(m_name);
        marshal.Write(IsEnabled());
        marshal.Write<uint16_t>(ComponentManager::Instance().GetVersion(this));

        return marshal;
    }

    bool Component::IsActive() const noexcept {
        return IsEnabled() && m_parent.Do<bool>([](auto&& data) -> bool {
            return !data || data->m_isActive;
        });
    }

    void Component::SetParent(GameObject *parent) {
        m_parent.Replace(parent);
    }

    void Component::SetEnabled(bool value) {
        m_isEnabled = value;
    }

    void Component::CheckActivity() {
        const bool isActive = IsActive();
        if (isActive == m_isActive) {
            return;
        }

        if (isActive) {
            OnEnable();
        }
        else {
            OnDisable();
        }
    }

    SR_WORLD_NS::Scene::Ptr Component::GetScene() const {
        return m_parent.Do<SR_WORLD_NS::Scene::Ptr>([](auto&& data) {
            if (!data) {
                SRHalt("The component have not parent game object!");
                return SR_WORLD_NS::Scene::Ptr();
            }

            /// Игровой объект никогда не уничтожится до того, как не установит "m_parent" в "nullptr"
            return data->GetScene();
        });
    }

    bool Component::IsEnabled() const noexcept {
        return m_isEnabled;
    }

    GameObject *Component::GetParent() const {
        return m_parent;
    }

    Component::GameObjectPtr Component::GetRoot() const {
        return m_parent.Do<GameObjectPtr>([](auto&& data) -> GameObjectPtr {
            if (!data) {
                return GameObjectPtr();
            }

            GameObjectPtr root = data->GetThis();

            while (root.RecursiveLockIfValid()) {
                if (auto&& parent = root->GetParent()) {
                    root.Unlock();
                    root = parent;
                }
                else {
                    root.Unlock();
                }
            }

            return root;
        });
    }

    Transform *Component::GetTransform() const {
        return m_parent.Do<Transform *>([](auto &&data) {
            return data ? data->GetTransform() : nullptr;
        });
    }
}

