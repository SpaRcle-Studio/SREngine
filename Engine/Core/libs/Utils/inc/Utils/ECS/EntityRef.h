//
// Created by Monika on 26.11.2022.
//

#ifndef SRENGINE_ENTITYREF_H
#define SRENGINE_ENTITYREF_H

#include <Utils/ECS/EntityRefUtils.h>

namespace SR_UTILS_NS {
    class GameObject;
    class Component;

    class EntityRef {
    public:
        EntityRef();
        explicit EntityRef(bool relative);

        EntityRef(const EntityRef& other) noexcept;
        EntityRef(EntityRef&& other) noexcept;

        EntityRef& operator=(const EntityRef& other);

    public:
        void AddPathItem(EntityRefUtils::Action action);
        void AddPathItem(EntityRefUtils::Action action, const std::string& name);
        void AddPathItem(EntityRefUtils::Action action, const std::string& name, uint16_t index);

    public:
        SR_NODISCARD GameObject* GetGameObject(GameObject* pFrom) const;

        void SetRelative(bool relative);

    private:
        void Update() const;

    private:
        SR_UTILS_NS::EntityRefUtils::RefPath m_path;
        bool m_relative;
        mutable EntityId m_fromEntityId;
        mutable EntityId m_entityId;

    };
}

#endif //SRENGINE_ENTITYREF_H
