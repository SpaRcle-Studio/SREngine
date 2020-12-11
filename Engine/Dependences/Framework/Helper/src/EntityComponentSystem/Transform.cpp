//
// Created by Nikita on 27.11.2020.
//

#include <Math/Mathematics.h>
#include "EntityComponentSystem/Transform.h"
#include <EntityComponentSystem/GameObject.h>

Framework::Helper::Transform::Transform(Framework::Helper::GameObject *parent) {
    this->m_parent = parent;
}

Framework::Helper::Transform::~Transform() {

}

void Framework::Helper::Transform::SetPosition(glm::vec3 val) {
    m_position = val;

    m_parent->UpdateComponentsPosition();

    for (GameObject* gm : m_parent->m_children)
        gm->m_transform->UpdateChild(this);
}

void Framework::Helper::Transform::SetRotation(glm::vec3 val) {
    m_rotation = val;

    m_parent->UpdateComponentsRotation();

    for (GameObject* gm : m_parent->m_children)
        gm->m_transform->UpdateChild(this);
}

void Framework::Helper::Transform::SetScale(glm::vec3 val) {
    m_scale = val;

    m_parent->UpdateComponentsScale();

    for (GameObject* gm : m_parent->m_children)
        gm->m_transform->UpdateChild(this);
}

void Framework::Helper::Transform::Translate(glm::vec3 val) noexcept {
    // TODO: calculate direction

    val = LocalDirection(val);

    this->SetPosition(m_position + val);
}

void Framework::Helper::Transform::Rotate(glm::vec3 val) noexcept {
    this->SetRotation(m_rotation + val);
}

void Framework::Helper::Transform::Scaling(glm::vec3 val) noexcept {
    this->SetScale(m_scale + val);
}

void Framework::Helper::Transform::UpdateChild(Framework::Helper::Transform *parent) {
    this->m_parent_position = parent->m_position + parent->m_parent_position;
    this->m_parent_rotation = parent->m_rotation + parent->m_parent_rotation;
    this->m_parent_scale	= parent->m_scale    + parent->m_parent_scale;

    this->m_parent->UpdateComponentsPosition();
    this->m_parent->UpdateComponentsRotation();
    this->m_parent->UpdateComponentsScale();
}

glm::vec3 Framework::Helper::Transform::LocalDirection(const glm::vec3 &dir) {
    float dx = cos(m_rotation.x * M_PI / 45.f / 4.f);
    float dy = cos(m_rotation.y * M_PI / 45.f / 4.f);
    float dz = 0;

    return glm::vec3(
            dir.x * dy,
            dir.y * dx,
            dir.z * dy
            );
}
