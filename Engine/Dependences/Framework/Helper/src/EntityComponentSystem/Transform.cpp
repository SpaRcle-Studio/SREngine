//
// Created by Nikita on 27.11.2020.
//

#include <Math/Mathematics.h>
#include "EntityComponentSystem/Transform.h"
#include <EntityComponentSystem/GameObject.h>
#include <map>
#include <vector>
#include <iostream>

Framework::Helper::Transform::Transform(Framework::Helper::GameObject *parent) {
    this->m_gameObject = parent;
}

void Framework::Helper::Transform::SetPosition(glm::vec3 val) {
    m_position = val;

    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildPosition(this);
    }
}

void Framework::Helper::Transform::SetRotation(glm::vec3 val) {
    m_rotation = val;

    m_gameObject->UpdateComponentsRotation();

    //for (auto gm : m_gameObject->m_children) {
    //    gm.second->m_transform->UpdateChildRotation(this);
    //}
}

void Framework::Helper::Transform::SetScale(glm::vec3 val) {
    m_scale = val;

    m_gameObject->UpdateComponentsScale();

    //for (GameObject* gm : m_parent->m_children)
    //    gm->m_transform->UpdateChild(this);
}

void Framework::Helper::Transform::Translate(glm::vec3 val) noexcept {
    val = LocalDirection(val);

    this->SetPosition(m_position + val);
}

void Framework::Helper::Transform::Rotate(glm::vec3 val) noexcept {
    this->SetRotation(m_rotation + val);
}

void Framework::Helper::Transform::Scaling(glm::vec3 val) noexcept {
    this->SetScale(m_scale + val);
}


//void Framework::Helper::Transform::UpdateChild(Framework::Helper::Transform *parent) {
  //  this->m_parent_position = parent->m_position + parent->m_parent_position;
    //this->m_parent_rotation = parent->m_rotation + parent->m_parent_rotation;
    //this->m_parent_scale	= parent->m_scale    + parent->m_parent_scale;

 //   this->m_parent->UpdateComponentsPosition();
    //this->m_parent->UpdateComponentsRotation();
    //this->m_parent->UpdateComponentsScale();
//}

glm::vec3 Framework::Helper::Transform::LocalDirection(const glm::vec3 &dir) {
    //float dx = cos(m_rotation.x * M_PI / 45.f / 4.f);
    //float dy = cos(m_rotation.y * M_PI / 45.f / 4.f);
    //float dz = 0;

    glm::vec3 rad = {
            m_rotation.x * M_PI / 45.f / 4.f,
            m_rotation.y * M_PI / 45.f / 4.f,
            m_rotation.z * M_PI / 45.f / 4.f
    };

    return glm::vec3(
            dir.x * cos(rad.y)                  + sin(rad.y) * dir.z * cos(rad.x),
            dir.y * cos(rad.x)                  - sin(rad.x) * dir.z, // + sin(rad.x) * dir.y
            dir.z * cos(rad.y) * cos(rad.x)     - sin(rad.y) * dir.x
            );
}

nlohmann::json Framework::Helper::Transform::Save() {
    nlohmann::json json;

    json["Transform"]["Position"] = {
            m_position.x,
            m_position.y,
            m_position.z
    };

    json["Transform"]["Rotation"] = {
            m_rotation.x,
            m_rotation.y,
            m_rotation.z
    };

    json["Transform"]["Scale"] = {
            m_scale.x,
            m_scale.y,
            m_scale.z
    };

    return json;
}

void Framework::Helper::Transform::UpdateChildPosition(Transform* parent) noexcept {
    this->m_parent_position = parent->m_position + parent->m_parent_position;

    this->m_gameObject->UpdateComponentsPosition();

    this->SetPosition(m_position);
}

void Framework::Helper::Transform::UpdateChildRotation(Framework::Helper::Transform *parent) noexcept {
    //this->m_parent_rotation = parent->m_rotation + parent->m_parent_rotation;

    //this->m_gameObject->UpdateComponentsRotation();
}

void Framework::Helper::Transform::UpdateChildScale(Framework::Helper::Transform *parent) noexcept {

}

void Framework::Helper::Transform::RotateAbout(glm::vec3 point, glm::vec3 angle) noexcept {

}
