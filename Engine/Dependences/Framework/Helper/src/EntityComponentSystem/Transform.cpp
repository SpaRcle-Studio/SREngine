//
// Created by Nikita on 27.11.2020.
//
#define GLM_ENABLE_EXPERIMENTAL

#include <Math/Mathematics.h>
#include "EntityComponentSystem/Transform.h"
#include <EntityComponentSystem/GameObject.h>
#include <map>
#include <vector>
#include <iostream>
#include <glm/gtx/string_cast.hpp>
#include <glm/gtx/matrix_decompose.hpp>

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

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildRotation(this);
    }
}

void Framework::Helper::Transform::SetScale(glm::vec3 val) {
    m_scale = val;

    m_gameObject->UpdateComponentsScale();

    //for (GameObject* gm : m_parent->m_children)
    //    gm->m_transform->UpdateChild(this);
}

void Framework::Helper::Transform::Translate(glm::vec3 val) noexcept {
    //val = LocalDirection(val);
    this->SetPosition(m_position + val);
}

void Framework::Helper::Transform::Rotate(glm::vec3 val) noexcept {
    //glm::fquat q = glm::radians(val);

    //this->SetRotation(q * m_rotation);
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

/*
glm::vec3 Framework::Helper::Transform::LocalDirection(const glm::vec3 &dir) {
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
}*/

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

    this->SetPosition(m_position);
}

void Framework::Helper::Transform::UpdateChildRotation(Framework::Helper::Transform *parent) noexcept {
    this->m_parent_rotation = parent->m_rotation + parent->m_parent_rotation;

    //this->SetRotation(m_rotation);
    //this->RotateAround(m_parent_position, m_parent_rotation);
    //this->SetRotationAround(m_parent_position, m_parent_rotation);
}

void Framework::Helper::Transform::UpdateChildScale(Framework::Helper::Transform *parent) noexcept {

}

/*
void Framework::Helper::Transform::SetRotationAround(glm::vec3 point, glm::vec3 newAngle) noexcept {


    m_gameObject->UpdateComponentsRotation();
    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildRotation(this);
        gm.second->m_transform->UpdateChildPosition(this);
    }
}*/

/*
void Framework::Helper::Transform::RotateAround(glm::vec3 point, glm::vec3 angle) noexcept {
    //this->m_rotation = angle;

    glm::vec3 delta = angle - m_rotation;

    //m_rotation = angle;
    //glm::vec3 rad = glm::radians(m_rotation);

    {
        glm::vec3 dir = glm::angleAxis((float) (glm::radians(delta.x)), glm::vec3(
                1,
                0,
                0
        )) * (m_position - point);

        this->m_position = point + dir;
    }

    //m_rotation = angle;

    m_gameObject->UpdateComponentsRotation();
    m_gameObject->UpdateComponentsPosition();

    //std::cout << glm::to_string(m_rotation) << std::endl;
    //std::cout << glm::to_string(m_rotation) << std::endl;

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildRotation(this);
        gm.second->m_transform->UpdateChildPosition(this);
    }
}*/

void Framework::Helper::Transform::LookAt(glm::vec3 target) {
    glm::mat4 mat = glm::lookAt({m_position.x, m_position.y, m_position.z}, target, {0,1,0});

    mat = glm::inverse(mat); // if use quaternions in mesh calc model

    glm::mat4 transformation;
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;
    glm::vec3 skew;
    glm::vec4 perspective;
    glm::decompose(transformation, scale, rotation, translation, skew, perspective);

    glm::vec3 deg = glm::degrees(glm::eulerAngles(rotation));
    this->m_rotation = glm::vec3({
        deg.x,
        deg.y + 180.f,
        deg.z,
    });

//    this->m_rotation = glm::vec3({
//         deg.x,
//         -deg.y + 180.f,
//         -deg.z,
//     });


    // Check nan
    if (m_rotation.x != m_rotation.x) m_rotation.x = 0.f;
    if (m_rotation.y != m_rotation.y) m_rotation.y = 0.f;
    if (m_rotation.z != m_rotation.z) m_rotation.z = 0.f;

    this->m_gameObject->UpdateComponentsRotation();

    this->UpdateChildRotation(this);
}

// TODO: Clear next methods. They is finished and worked.

glm::vec3 Framework::Helper::Transform::Forward() const noexcept {
    glm::vec3 rad = glm::radians(m_rotation);

    glm::fquat q = glm::vec3(
            -rad.x,
            rad.y,
            -rad.z
    );

    glm::vec3 dir = q * forward;

    return glm::vec3({
        dir.x,
        dir.y,
        dir.z // -dir.z
    });
}
glm::vec3 Framework::Helper::Transform::Right() const noexcept {
    glm::fquat rad = glm::radians(glm::vec3(
            -m_rotation.x,
            m_rotation.y,
            -m_rotation.z
    ));

    glm::vec3 dir = rad * right;

    return glm::vec3({
         dir.x,
         dir.y,
         dir.z // -dir.z
    });
}
glm::vec3 Framework::Helper::Transform::Up() const noexcept {
    glm::fquat rad = glm::radians(glm::vec3(
            -m_rotation.x,
            m_rotation.y,
            -m_rotation.z //-m_rotation.z
    ));

    glm::vec3 dir = rad * up;

    return glm::vec3({
         dir.x,
         dir.y,
         dir.z // -dir.z
    });
}

void Framework::Helper::Transform::RotateAround(glm::vec3 point, glm::vec3 axis, float angle) noexcept {
    glm::vec3 vector3 = glm::angleAxis(glm::radians(angle), axis) * (m_position - point);
    this->m_position = point + vector3;

    //!===================================================

    m_gameObject->UpdateComponentsRotation();
    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildRotation(this);
        gm.second->m_transform->UpdateChildPosition(this);
    }
}
