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
    m_globalPosition = val;

    if (m_gameObject->m_parent) {
        //m_localPosition = m_globalPosition - m_gameObject->m_transform->m_globalPosition;
        m_localPosition = m_globalPosition - m_gameObject->m_parent->m_transform->m_globalPosition;
        //m_localPosition = val;
    }
    else
        m_localPosition = m_globalPosition;

    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildPosition(this);
    }
}

/* С увеличением угла поворота повышается шанс ошибки float,
 * потому его необходимо ограничить. Все равно он циклический. */
glm::vec3 Lim360(glm::vec3 vec) noexcept {
    int xi = (int)vec.x / 360;
    int yi = (int)vec.y / 360;
    int zi = (int)vec.z / 360;

    float xf = vec.x - 360.f * (float)xi;
    float yf = vec.y - 360.f * (float)yi;
    float zf = vec.z - 360.f * (float)zi;

    return {xf, yf, zf};
}

void Framework::Helper::Transform::SetRotation(glm::vec3 val) {
    m_globalRotation = Lim360(val);

    if (m_gameObject->m_parent)
        m_localRotation = Lim360(m_globalRotation - m_gameObject->m_parent->m_transform->m_globalRotation);
    else
        m_localRotation = Lim360(m_globalRotation);

    m_gameObject->UpdateComponentsRotation();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildRotation(this);
    }
}

void Framework::Helper::Transform::SetScale(glm::vec3 val) {
    m_globalScale = val;

    if (m_gameObject->m_parent)
        m_localScale = m_globalScale - m_gameObject->m_parent->m_transform->m_globalScale;
    else
        m_localScale = val;

    m_gameObject->UpdateComponentsScale();

    for (auto gm : m_gameObject->m_children)
        gm.second->m_transform->UpdateChildScale(this);
}

void Framework::Helper::Transform::Translate(glm::vec3 val) noexcept {
    this->SetPosition(m_globalPosition + val);
}

void Framework::Helper::Transform::Rotate(glm::vec3 angle) noexcept {
    this->SetRotation(m_globalRotation + angle);
}

void Framework::Helper::Transform::Scaling(glm::vec3 val) noexcept {
    //this->SetScale(m_scale + val);
}

nlohmann::json Framework::Helper::Transform::Save() {
    nlohmann::json json;

    /*json["Transform"]["Position"] = {
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
    };*/

    return json;
}

void Framework::Helper::Transform::UpdateChildPosition(Transform* parent) noexcept {
    this->m_globalPosition = parent->m_globalPosition + m_localPosition;

    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildPosition(this);
    }
}

void Framework::Helper::Transform::UpdateChildRotation(Framework::Helper::Transform *parent) noexcept {
    //this->m_globalRotation = Lim360(parent->m_globalRotation + m_localRotation);

    this->SetRotateAround(parent, parent->m_globalRotation);

    //m_gameObject->UpdateComponentsRotation();

    //for (auto gm : m_gameObject->m_children) {
    //    gm.second->m_transform->UpdateChildRotation(this, {}); //TODO
    //}

    //!this->m_parent_rotation = parent->m_rotation + parent->m_parent_rotation;

    //this->SetRotation(m_rotation);
    //this->RotateAround(m_parent_position, m_parent_rotation);
    //this->SetRotationAround(m_parent_position, m_parent_rotation);
}

void Framework::Helper::Transform::UpdateChildScale(Framework::Helper::Transform *parent) noexcept {

}


glm::vec3 Framework::Helper::Transform::GetLookAt(glm::vec3 target, glm::vec3 axis) noexcept {
    glm::mat4 mat = glm::lookAt(m_globalPosition, target, axis);

    mat = glm::inverse(mat); // if use quaternions in mesh calc model

    glm::quat rotation = glm::getRotation(mat);

    glm::vec3 deg = glm::degrees(glm::eulerAngles(rotation));
    glm::vec3 rotate = glm::vec3({
                                         -deg.x,
                                         deg.y + 180.f,
                                         deg.z,
                                 });

    // Check nan
    if (rotate.x != rotate.x) rotate.x = 0.f;
    if (rotate.y != rotate.y) rotate.y = 0.f;
    if (rotate.z != rotate.z) rotate.z = 0.f;

    return rotate;
}

void Framework::Helper::Transform::LookAt(glm::vec3 target) {
    glm::mat4 mat = glm::lookAt(m_globalPosition, target, {0,1,0});

    mat = glm::inverse(mat); // if use quaternions in mesh calc model

    glm::quat rotation = glm::getRotation(mat);

    glm::vec3 deg = glm::degrees(glm::eulerAngles(rotation));
    glm::vec3 rotate = glm::vec3({
        -deg.x,
        deg.y + 180.f,
        deg.z,
    });

    // Check nan
    if (rotate.x != rotate.x) rotate.x = 0.f;
    if (rotate.y != rotate.y) rotate.y = 0.f;
    if (rotate.z != rotate.z) rotate.z = 0.f;

    //glm::vec3 rotate = this->GetLookAt(target, {0,1,0});

    this->SetRotation(rotate);
}

// TODO: Clear next methods. They is finished and worked.

glm::vec3 Framework::Helper::Transform::Forward(bool local) const noexcept {
    const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x,
        rot.y,
        -rot.z
    ));

    return q * forward;
}
glm::vec3 Framework::Helper::Transform::Right(bool local) const noexcept {
    const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x,
        rot.y,
        -rot.z
    ));

    return q * right;
}
glm::vec3 Framework::Helper::Transform::Up(bool local) const noexcept {
    const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x,
        rot.y,
        -rot.z
    ));

    return q * up;
}

void Framework::Helper::Transform::RotateAround(glm::vec3 point, glm::vec3 axis, float angle) noexcept {
    /*glm::vec3 vector3 = glm::angleAxis(glm::radians(angle), axis) * (m_globalPosition - point);
    this->SetPosition(point + vector3);

    //!===================================================

    m_gameObject->UpdateComponentsRotation();
    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildRotation(this);
        gm.second->m_transform->UpdateChildPosition(this);
    }*/
}

void Framework::Helper::Transform::RotateAround(glm::vec3 point, glm::vec3 angle) noexcept {
    this->SetRotateAround(point, m_aroundRotation + angle);
    //LookAt(point);

    /*glm::vec3 vector3, pos = m_globalPosition;

    if (angle.x != 0) {
        vector3 = glm::angleAxis(glm::radians(angle.x), pitch) * (pos - point);
        pos = point + vector3;
    }
    if (angle.y != 0) {
        vector3 = glm::angleAxis(glm::radians(angle.y), yaw) * (pos - point);
        pos = point + vector3;
    }
    if (angle.z != 0) {
        vector3 = glm::angleAxis(glm::radians(angle.z), -roll) * (pos - point);
        pos = point + vector3;
    }*/

    //glm::mat transMat = glm::translate(glm::mat4(1), m_globalPosition);

    //glm::vec3 rotation = m_globalRotation + angle;

    /*glm::fquat q = glm::radians(glm::vec3(
            rotation.x,
            rotation.y,
            -rotation.z
    ));

    glm::vec3 dir = q * (m_globalPosition - point);

    glm::vec3 pos = point + dir;
     */

    //glm::mat4 rotateMat = glm::mat4_cast(q);

    //transMat *= rotateMat;

    //this->SetRotation(glm::degrees(glm::eulerAngles(glm::getRotation(transMat))));

    //glm::quat q2 = glm::getRotation(transMat);


    //!===================================================

    //this->SetRotation(rotation);

    //this->SetPosition(pos);

    //this->Rotate(angle);
}

float Magnitude(glm::vec3 vec){
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

glm::vec3 Framework::Helper::Transform::Direction(glm::vec3 point) noexcept {
    glm::vec3 heading = point - m_globalPosition;
    float distance = Magnitude(heading);
    return heading / distance;
}

void Framework::Helper::Transform::SetRotateAround(glm::vec3 point, glm::vec3 angle) noexcept {
    this->m_aroundRotation = angle;

    glm::fquat q = glm::radians(glm::vec3(
            angle.x,
            angle.y,
            -angle.z
    ));

    float dist = this->Distance(point);

    glm::vec3 dir = (q * forward) * dist;

    this->SetPosition(point + dir);

    ///===================================

    glm::quat q_self = q * glm::quat(glm::radians(m_localRotation));

    //m_globalRotation = Lim360(m_aroundRotation + m_localRotation);
    m_globalRotation = Lim360(glm::degrees(glm::eulerAngles(q_self)));

    if (m_globalRotation.x != m_globalRotation.x) m_globalRotation.x = 0.f;
    if (m_globalRotation.y != m_globalRotation.y) m_globalRotation.y = 0.f;
    if (m_globalRotation.z != m_globalRotation.z) m_globalRotation.z = 0.f;

    m_gameObject->UpdateComponentsRotation();

    for (auto gm : m_gameObject->m_children) {
        gm.second->m_transform->UpdateChildRotation(this);
    }
}

void Framework::Helper::Transform::LookAt(Framework::Helper::GameObject *gameObject) noexcept {
    this->LookAt(gameObject->m_transform->m_globalPosition);
}


