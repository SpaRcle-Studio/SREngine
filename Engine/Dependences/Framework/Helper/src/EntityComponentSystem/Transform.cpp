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
#include <Debug.h>
#include <imgui.h>

Framework::Helper::Transform::Transform(Framework::Helper::GameObject *parent) {
    this->m_gameObject = parent;
}

void Framework::Helper::Transform::SetPosition(glm::vec3 val, bool pivot) {
    glm::vec3 delta = m_globalPosition - val;

    m_globalPosition = val;

    m_gameObject->UpdateComponentsPosition();

    this->UpdateLocalPosition();

    for (auto a: m_gameObject->m_children)
        a->m_transform->UpdateChildPosition(delta, pivot);
}

void Framework::Helper::Transform::SetRotation(glm::vec3 val, bool pivot) {
    m_globalRotation = val;

    m_gameObject->UpdateComponentsRotation();
}

void Framework::Helper::Transform::SetScale(glm::vec3 val, bool pivot) {
    glm::vec3 delta = m_globalScale / val;

    m_globalScale = val;

    m_gameObject->UpdateComponentsScale();

    glm::vec3 temp = m_globalPosition;
    this->SetPosition(glm::vec3(0,0,0));

    this->UpdateLocalScale();
    this->UpdateLocalPosition();

    for (auto a: m_gameObject->m_children)
        a->m_transform->UpdateChildScale(delta, pivot);

    this->SetPosition(temp);
}

void Framework::Helper::Transform::Translate(glm::vec3 val) noexcept {
    //this->SetPosition(m_localPosition + val);
    this->SetPosition(m_globalPosition + val);
}

void Framework::Helper::Transform::Rotate(glm::vec3 angle) noexcept {
    //this->SetRotation(m_localRotation + angle);
    this->SetRotation(m_globalRotation + angle);
}

glm::vec3 Framework::Helper::Transform::Forward(bool local) const noexcept {
    const glm::vec3 rot = m_globalRotation;
    //const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x, //rot.x,
        rot.y, //rot.y,
        -rot.z  //-rot.z
    ));

    return q * forward; // return q * -forward;
}
glm::vec3 Framework::Helper::Transform::Right(bool local) const noexcept {
    const glm::vec3 rot = m_globalRotation;
    //const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x, //rot.x,
        rot.y, //-rot.y, //rot.y,
        -rot.z //-rot. z
    ));

    return q * -right; //return q * right;
}
glm::vec3 Framework::Helper::Transform::Up(bool local) const noexcept {
    const glm::vec3 rot =  m_globalRotation;
    //const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x, // rot.x,
        rot.y, //rot.y,
        -rot.z //-rot.z
    ));

    return q * up; //return q * up;
}

float Magnitude(glm::vec3 vec){
    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
}

glm::vec3 Framework::Helper::Transform::Direction(glm::vec3 point) noexcept {
    glm::vec3 heading = point - m_globalPosition;
    float distance = Magnitude(heading);
    return heading / distance;
}
void Framework::Helper::Transform::SetMatrix(glm::mat4 matrix, bool pivot) noexcept  {
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;

    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(matrix, scale, rotation, translation, skew, perspective);

    glm::vec3 euler = glm::degrees(glm::eulerAngles(rotation));

    //glm::vec3 deltaScale = scale / m_globalScale;
    glm::vec3 deltaScale = m_globalScale / scale;
    glm::vec3 deltaPosition = m_globalPosition - translation;
    //glm::vec3 deltaRotate = euler - m_globalRotation;

    this->SetPosition(glm::vec3(0,0,0));

    this->m_globalScale    = scale;

    for (auto a : this->m_gameObject->m_children)
        if (deltaScale != glm::vec3(1,1,1))
            a->m_transform->UpdateChildScale(deltaScale, pivot);

    this->SetPosition(translation);
    //this->m_globalPosition = translation;
    this->m_globalRotation = euler;

    this->UpdateLocalScale();
    this->UpdateLocalPosition();

    m_gameObject->UpdateComponents();

    //for (auto a : this->m_gameObject->m_children) {
    //    a->m_transform->UpdateChildPosition(deltaPosition, pivot);
    //}
}

glm::mat4 Framework::Helper::Transform::GetMatrix() const noexcept  {
    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), m_globalPosition);

    glm::vec3 rot = m_globalRotation;
    const glm::mat4 rotationMatrix = mat4_cast(glm::quat(glm::radians(rot)));

    modelMat *= rotationMatrix;

    return glm::scale(modelMat, m_globalScale);
}

void Framework::Helper::Transform::UpdateChildPosition(glm::vec3 delta, bool pivot) {
    m_globalPosition -= delta;

    this->UpdateLocalPosition();

    this->m_gameObject->UpdateComponentsPosition();

    for (auto a : m_gameObject->m_children)
        a->m_transform->UpdateChildPosition(delta, pivot);
}

void Framework::Helper::Transform::UpdateChildScale(glm::vec3 delta, bool pivot) {
    glm::vec3 newScale = m_parent->m_globalScale * m_localScale;
    //glm::vec3 deltaInternal = m_globalScale / newScale;
    this->m_globalScale = newScale;

    this->UpdateLocalScale();

    //this->m_globalPosition = (m_localPosition + m_parent->m_globalPosition) / delta;
    //this->m_globalPosition /= delta;
    //glm::vec3 offset = m_parent->m_globalPosition;
    //std::cout << glm::to_string(m_globalPosition) << " | " << glm::to_string(delta) << std::endl;
    //std::cout << glm::to_string(m_localPosition) << " | " << glm::to_string(m_globalPosition) << std::endl;

    //this->m_globalPosition = (m_globalPosition) / delta;
    this->m_globalPosition /= (delta);
    //this->m_globalPosition -= m_parent->m_localPosition;
    //this->m_globalPosition -= m_parent->m_localPosition * (m_globalPosition - (m_localScale * m_localPosition));

    // (m_globalPosition - (m_localScale * m_localPosition))

    //this->m_globalPosition = (m_globalPosition - (m_parent->m_localPosition / m_globalScale)) / delta;
    //this->m_globalPosition -= m_parent->m_localPosition;
    //this->m_globalPosition -= m_globalPosition / m_globalScale - m_parent->m_localPosition;

    this->m_gameObject->UpdateComponentsPosition();
    this->m_gameObject->UpdateComponentsScale();

    this->UpdateLocalPosition();

    for (auto a : m_gameObject->m_children)
        a->m_transform->UpdateChildScale(delta, pivot);
}

void Framework::Helper::Transform::UpdateLocalPosition() {
    if (m_parent) {
        ///glm::vec3 scaleDelta = m_globalScale / m_parent->m_globalScale;

        m_localPosition = (m_globalPosition - m_parent->m_globalPosition) / m_parent->m_globalScale;
        ///m_localPosition /= m_globalScale;
    } else
        m_localPosition = m_globalPosition;
}

void Framework::Helper::Transform::UpdateLocalScale() {
    if (m_parent) {
        this->m_localScale = m_globalScale / m_parent->m_globalScale;
    } else
        m_localScale = m_globalScale;
}
