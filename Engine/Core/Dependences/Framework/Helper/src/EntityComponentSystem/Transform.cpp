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

#include <Math/Matrix4x4.h>

using namespace Framework::Helper::Math;

Framework::Helper::Transform::Transform(GameObject* parent) {
    this->m_gameObject = parent;
    this->m_globalRotation = Math::CmpEpsilonFV3;
    this->m_localRotation  = Math::CmpEpsilonFV3;
}

void Framework::Helper::Transform::SetLocalPosition(Framework::Helper::Math::FVector3 val) {
    FVector3 delta = m_localPosition - val;
    this->m_localPosition = val;

    if (m_parent) {
        UpdateChildPosition(delta);
    }
    else {
        m_globalPosition = val;

        m_gameObject->UpdateComponentsPosition();

        ///TODO:for (const auto& child: m_gameObject->m_children)
            ///child->m_transform->UpdateChildPosition(delta);
    }
}

void Framework::Helper::Transform::SetLocalRotation(Framework::Helper::Math::FVector3 val) {
    m_localRotation = val.FixEulerAngles().Limits(360);

    if (m_parent) {
        m_globalRotation = m_localRotation;

        UpdateChildRotation();
    }
    else {
        m_globalRotation = m_localRotation;

        m_gameObject->UpdateComponentsRotation();

        ///TODO:for (const auto& child: m_gameObject->m_children)
            ///child->m_transform->UpdateChildRotation();
    }
}

void Framework::Helper::Transform::SetLocalScale(Framework::Helper::Math::FVector3 val) {
    const auto delta = m_localScale / val;
    m_localScale = val;

    if (m_parent)
        UpdateChildScale(delta);

    m_gameObject->UpdateComponentsPosition();

    ///TODO:for (const auto& child : m_gameObject->m_children)
    ///TODO:    child->m_transform->UpdateChildScale(delta);
}

/*
void Framework::Helper::Transform::SetPosition(FVector3 val, bool pivot) { // Todo: check working
    Helper::Debug::Error("Transform::SetPosition() : it is not work! Use SetGlobalPosition or SetLocalPosition!");

    auto delta = m_globalPosition - val;
    m_globalPosition = val;

    //this->UpdateLocalPosition(delta);

    //this->UpdateDefParentDir();

    m_gameObject->UpdateComponentsPosition();

    for (const auto& a: m_gameObject->m_children)
        a->m_transform->UpdateChildPosition(delta);
}

void Framework::Helper::Transform::SetRotation(const FVector3& angles) {
    if (m_parent) {
        Matrix4x4&& worldRotateMatrix = Matrix4x4::RotationYawPitchRoll(angles.Radians());
        Matrix4x4 localRotateMatrix = worldRotateMatrix * m_parent->GetInvWorldMatrix();

        SetLocalRotation(localRotateMatrix.GetQuat().EulerAngle().Degrees());
    }
    else
        SetLocalRotation(angles);
}

void Framework::Helper::Transform::SetScale(FVector3 val) {
    auto delta = m_globalScale / val;
    m_globalScale = val;

    m_gameObject->UpdateComponentsScale();

    auto temp = m_globalPosition;
    this->SetPosition(FVector3(0,0,0));

    for (auto&& child : m_gameObject->m_children) {
        child->m_transform->UpdateChildSkew(delta);
    }

    //for (auto a: m_gameObject->m_children)
    //    a->m_transform->UpdateChildScale(delta);

    this->SetPosition(temp);
} */

void Framework::Helper::Transform::SetWorldPosition(Framework::Helper::Math::FVector3 position) {
    if (!m_parent) {
        FVector3 delta = m_globalPosition - position;
        m_globalPosition = m_localPosition = position;

        m_gameObject->UpdateComponentsPosition();

        ///TODO:for (const auto& a: m_gameObject->m_children)
        ///TODO:   a->m_transform->UpdateChildPosition(delta);
    }
    else {
        GlobalTranslate(-m_globalPosition);
        GlobalTranslate(position);
    }
}

void Transform::SetWorldRotation(FVector3 rotation) {
    if (!m_parent) {

    }
    else {
        SetLocalRotation(0.f);
        //Rotate(m_parent->m_globalRotation.ToQuat().Inverse().EulerAngle());
        //Rotate(-m_parent->m_globalRotation);
        //GlobalRotate(rotation);
    }
}

void Framework::Helper::Transform::GlobalTranslate(FVector3 axis, double value) {
    GlobalTranslate(axis * value);
}

void Framework::Helper::Transform::GlobalTranslate(Framework::Helper::Math::FVector3 value) {
    if (!m_parent) {
        Translate(value);
    }
    else {
        Matrix4x4 rotate = Matrix4x4(0.f, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), 1.f);
        FVector3 origin = rotate.GetQuat().EulerAngle().InverseAxis(2);
        auto preDir = origin.Radians().ToQuat();
        m_localPosition += (preDir * value) / m_parent->m_globalScale;

        UpdateChildRotation();
    }
}

void Framework::Helper::Transform::Translate(FVector3 val) noexcept {
    val /= m_globalScale;

    m_localPosition += val;

    if (!m_parent) {
        m_globalPosition += val;

        m_gameObject->UpdateComponentsPosition();

        ///TODO:for (const auto& child : m_gameObject->m_children)
        ///TODO:    child->m_transform->UpdateChildPosition(-val);
    }
    else
       UpdateChildRotation();
}

void Framework::Helper::Transform::Rotate(Framework::Helper::Math::FVector3 axis, double angle) noexcept {
    Rotate(axis * angle);

    /*
    Matrix4x4 rotate = Matrix4x4(m_globalPosition, (axis * angle).InverseAxis(2).ToQuat(), FVector3(1,1,1));
    Matrix4x4 matLocal = Matrix4x4(m_globalPosition, m_localRotation.InverseAxis(2).ToQuat(), FVector3(1,1,1));
    m_localRotation = (matLocal * rotate).GetQuat().EulerAngle().InverseAxis(2);

    if (m_parent)
        UpdateChildRotation();
    else {
        this->m_globalRotation = m_localRotation;

        this->m_gameObject->UpdateComponentsRotation();

        for (const auto& a: m_gameObject->m_children)
            a->m_transform->UpdateChildRotation();
    }*/
}

void Framework::Helper::Transform::GlobalRotate(Framework::Helper::Math::FVector3 axis, double value) {
    GlobalRotate(axis * value);

    /** Matrix4x4 matLocal = Matrix4x4(0.0, m_localRotation.InverseAxis(2).ToQuat(), 1.0);
        Matrix4x4 matGlobal = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat(), 1.0);
        Matrix4x4 invMatGlobal = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), 1.0);

        Matrix4x4 rotate = Matrix4x4(0.0, (axis * value).InverseAxis(2).ToQuat(), FVector3(1, 1, 1));

        matLocal = matGlobal * matLocal;
        matLocal = rotate * matLocal;
        matLocal = invMatGlobal * matLocal;

        m_localRotation = matLocal.GetQuat().EulerAngle().InverseAxis(2);

        UpdateChildRotation();
     */
}

void Framework::Helper::Transform::RotateAround(FVector3 point, FVector3 axis, Unit angle, bool local) noexcept {
    if (local) {
        auto q = m_globalRotation.InverseAxis(1).ToQuat();
        axis = axis.InverseAxis(1).Rotate(q).InverseAxis(1);

        GlobalRotate(axis, angle);
    }
    else
        GlobalRotate(axis, angle);

    FVector3 worldPos = m_globalPosition;

    Quaternion q = Quaternion(axis.Radians() * angle);
    FVector3 dif = worldPos - point;
    dif = q * dif;
    worldPos = point + dif;

    SetWorldPosition(worldPos);
}

void Framework::Helper::Transform::Rotate(FVector3 angle) {
    if (angle == FVector3(0, 0, 0))
        return;

    /*if (m_parent) {
        auto temp = m_parent->GetRotation();
        m_parent->SetRotation(FVector3(0, 0, 0));

        FVector3 rotate = m_globalRotation + angle;
        SetRotation(rotate.Limits(360));

        m_parent->SetRotation(temp);
    }
    else */ {
        FVector3 rotate = m_globalRotation + angle;
        SetLocalRotation(rotate.Limits(360));
    }
}

Framework::Helper::Math::FVector3 Framework::Helper::Transform::Direction(Framework::Helper::Math::FVector3 preDir, bool local) const noexcept {
    if (local)
        return m_localRotation.Radians().ToQuat() * preDir;
    else
        return m_globalRotation.Radians().ToQuat() * preDir;
}

Framework::Helper::Math::FVector3 Framework::Helper::Transform::Forward() const noexcept {
    return m_globalRotation.Radians().ToQuat() * forward;
}
Framework::Helper::Math::FVector3 Framework::Helper::Transform::Right() const noexcept {
    //return right.Rotate(m_globalRotation);
    return m_globalRotation.Radians().ToQuat() * right;
}
Framework::Helper::Math::FVector3 Framework::Helper::Transform::Up() const noexcept {
    //return up.Rotate(m_globalRotation);
    return m_globalRotation.Radians().ToQuat() * up;
}

void Framework::Helper::Transform::SetMatrix(glm::mat4 delta, glm::mat4 matrix, bool pivot) noexcept  {
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;

    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(matrix, scale, rotation, translation, skew, perspective);

    if (m_parent) {
        //Matrix4x4 matGlobal = Matrix4x4(m_globalPosition, m_globalRotation.InverseAxis(2).ToQuat(), m_globalScale);

        Matrix4x4 matGlobal = Matrix4x4(m_globalPosition, m_globalRotation.InverseAxis(2).ToQuat(), m_globalScale);
        Matrix4x4 matLocal = Matrix4x4(m_globalPosition, (m_localRotation.InverseAxis(2)).ToQuat().Inverse(), m_globalScale);

        Matrix4x4 originalMat = matGlobal * matLocal;

        Matrix4x4 matDelta = Matrix4x4(matrix) * originalMat.Inverse();

        //Debug::Log(originalMat.GetQuat().EulerAngle().InverseAxis(2).ToString());
        Debug::Log(matDelta.GetQuat().EulerAngle().InverseAxis(2).ToString());


        this->m_localRotation = matDelta.GetQuat().EulerAngle().InverseAxis(2);
        this->UpdateChildRotation();

        //Debug::Log(Matrix4x4(delta).GetQuat().EulerAngle().InverseAxis(2).ToString());

        //this->m_localRotation = (Matrix4x4(matrix) - matGlobal * matLocal).GetQuat().EulerAngle().InverseAxis(2);
       // this->UpdateChildRotation(pivot);
        //this->m_localRotation -= m_localRotation - (Matrix4x4(matrix) / (matGlobal * matLocal)).GetQuat().EulerAngle().InverseAxis(2);

        /*Quaternion deltaRotate = Matrix4x4(delta).GetQuat();

        Quaternion local = this->m_localRotation.InverseAxis(2);
        this->m_localRotation = (deltaRotate * local).EulerAngle().InverseAxis(2);

        this->UpdateChildRotation(pivot);*/

        return;
    }


    auto euler = Quaternion(rotation).EulerAngle().InverseAxis(2);

    //glm::vec3 deltaScale = scale / m_globalScale;
    FVector3 deltaScale = m_globalScale / FVector3(scale);
    //Vector3 deltaPosition = m_globalPosition - translation;


    //if (!deltaPosition.Empty() && m_parent) {
        //this->UpdateDefParentDir();
    //}
        //this->m_defParentDir = m_globalPosition.Direction(m_parent->m_globalPosition);
        //this->m_defParentDir = m_globalRotation.Radians().ToQuat() * m_globalPosition.Direction(m_parent->m_globalPosition);

    if (deltaScale != FVector3(1,1,1)) {
        //this->SetPosition(FVector3(0,0,0));
        this->m_globalScale = FVector3(scale);


        ///TODO:for (auto a : this->m_gameObject->m_children)
        ///TODO:    a->m_transform->UpdateChildScale(deltaScale);
    }


    if (m_globalRotation != euler) {
        this->m_globalRotation = euler;
        ///TODO:for (auto a : this->m_gameObject->m_children)
        ///TODO:    a->m_transform->UpdateChildRotation();
    }

   // this->SetPosition(FVector3(translation));
    //this->m_globalPosition = translation;

    //this->UpdateLocalPosition(deltaPosition);
    //if (m_parent)
    //    this->UpdateChildRotation(Vector3(0,0,0), pivot);

    m_gameObject->UpdateComponents();

    //for (auto a : this->m_gameObject->m_children) {
    //    a->m_transform->UpdateChildPosition(deltaPosition, pivot);
    //}
}

glm::mat4 Framework::Helper::Transform::GetMatrix(Helper::Graph::PipeLine pipeLine, FVector3 position, bool local) const noexcept {
    switch (pipeLine) {
        case Graph::PipeLine::OpenGL: {
            if (local) {
                glm::mat4 localMat = glm::translate(glm::mat4(1.0f), position.InverseAxis(0).ToGLM());
                localMat *= mat4_cast(m_localRotation.InverseAxis(1).ToQuat().ToGLM());
                localMat = glm::scale(localMat, glm::vec3(1));
                return localMat;
            } else {
                glm::mat4 globalMat = glm::translate(glm::mat4(1.0f), position.InverseAxis(0).ToGLM());
                globalMat *= mat4_cast(m_globalRotation.InverseAxis(1).ToQuat().ToGLM());
                globalMat = glm::scale(globalMat, glm::vec3(1));
                return globalMat;
            }
        }
        case Graph::PipeLine::Vulkan:
        case Graph::PipeLine::DirectX:
        default:
            return glm::mat4(1);
    }
}

glm::mat4 Framework::Helper::Transform::GetMatrix(Helper::Graph::PipeLine pipeLine, bool local) const noexcept {
    if (local)
        return GetMatrix(pipeLine, m_localPosition, local);
    else
        return GetMatrix(pipeLine, m_globalPosition, local);
}

void Framework::Helper::Transform::UpdateChildPosition(FVector3 delta) {
    m_globalPosition -= delta;

    this->m_gameObject->UpdateComponentsPosition();

    ///TODO: for (const auto& a : m_gameObject->m_children)
    ///TODO:    a->m_transform->UpdateChildPosition(delta);
}

void Framework::Helper::Transform::UpdateChildSkew(FVector3 delta) {
    //this->m_globalPosition /= delta;
    //this->UpdateChildRotation();

    //m_skew = m_globalRotation.Radians().ToQuat() * m_parent->m_globalScale;
    //this->m_gameObject->UpdateComponents();
    UpdateChildRotation();

    //for (const auto& a : m_gameObject->m_children)
   //     a->m_transform->UpdateChildSkew(false, delta);
}

void Framework::Helper::Transform::UpdateChildScale(FVector3 delta) {
    auto newScale = m_parent->m_globalScale * m_localScale;
    this->m_globalScale = newScale;

    this->m_globalPosition /= delta;
    this->UpdateChildRotation();

    this->m_gameObject->UpdateComponents();

    ///TODO:for (const auto& a : m_gameObject->m_children)
    ///TODO:    a->m_transform->UpdateChildScale(delta);
}

void Framework::Helper::Transform::UpdateChildRotation() {
    this->m_globalRotation = m_parent->m_globalRotation;

    Matrix4x4 matGlobal = Matrix4x4(m_globalPosition, m_globalRotation.InverseAxis(2).ToQuat(), FVector3(1,1,1));

    {
        {
            Matrix4x4 skewMat = Matrix4x4(0, Quaternion(), m_parent->m_globalScale);
            m_skew = (skewMat * matGlobal).GetScale();
        }

        const FVector3 newPos = m_parent->m_globalPosition;

        if (m_localPosition.Empty())
            this->m_globalPosition = newPos;
        else
            this->m_globalPosition = newPos + Direction(m_localPosition * m_parent->m_globalScale * m_parent->m_skew);
    }

    Matrix4x4 matLocal = Matrix4x4(m_globalPosition, m_localRotation.InverseAxis(2).ToQuat(), FVector3(1,1,1));

    m_globalRotation = (matGlobal * matLocal).GetQuat().EulerAngle().InverseAxis(2);

    this->m_gameObject->UpdateComponents();

    ///TODO:for (const auto& a : m_gameObject->m_children)
    ///TODO:    a->m_transform->UpdateChildRotation();
}

void Framework::Helper::Transform::OnParentSet(Framework::Helper::Transform *parent) {
    if ((m_parent = parent)) {
        UpdateChildRotation();
    }
    else {
        /// TODO!
    }
}

Framework::Helper::Xml::Document Framework::Helper::Transform::Save() const {
    auto doc = Xml::Document::New();
    auto root = doc.Root().AppendChild("Transform");

    const auto& position = GetPosition();
    const auto& rotation = GetRotation();
    const auto& scale    = GetScale();

    root.AppendChild("Position")
            .NAppendAttribute("X", position.x)
            .NAppendAttribute("Y", position.y)
            .NAppendAttribute("Z", position.z);

    root.AppendChild("Rotation")
            .NAppendAttribute("X", rotation.x)
            .NAppendAttribute("Y", rotation.y)
            .NAppendAttribute("Z", rotation.z);

    root.AppendChild("Scale")
            .NAppendAttribute("X", scale.x)
            .NAppendAttribute("Y", scale.y)
            .NAppendAttribute("Z", scale.z);

    return doc;
}

void Framework::Helper::Transform::Scale(FVector3 val) {
    /*if (m_parent) { // local
        m_localScale += val;
        this->UpdateChildRotation();
        auto delta = m_localScale / val;

        this->UpdateChildScale(delta);
    }
    else { // global
        this->SetScale(m_globalScale + val, true);
    }*/

    SetLocalScale(m_globalScale * val);
}

//void Framework::Helper::Transform::SetSkew(FVector3 val) {
//    m_skew = val;
//    m_gameObject->UpdateComponentsSkew();
//}

void Framework::Helper::Transform::GlobalRotate(FVector3 value) {
    if (!m_parent) {
        Rotate(value);
    }
    else {
        //Matrix4x4&& worldRotateMatrix = Matrix4x4::RotationYawPitchRoll(value);
        //Matrix4x4 localRotateMatrix = worldRotateMatrix * m_parent->GetInvWorldMatrix();
        //m_localRotation = localRotateMatrix.GetQuat().EulerAngle();

        //Matrix4x4 rotate = Matrix4x4(0.0, value.InverseAxis(2).ToQuat(), 1.f);
        //Matrix4x4 matGlobal = Matrix4x4(0.0, m_globalRotation.InverseAxis(2).ToQuat(), 1.f);
        //m_localRotation = (rotate * matGlobal).GetQuat().EulerAngle().InverseAxis(2);

        /*m_gameObject->UpdateComponentsRotation();

        for (const auto& a: m_gameObject->m_children)
            a->m_transform->UpdateChildRotation();*/

        Matrix4x4 matLocal = Matrix4x4(0.0, m_localRotation.InverseAxis(2).ToQuat(), 1.0);
        Matrix4x4 matGlobal = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat(), 1.0);
        Matrix4x4 invMatGlobal = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), 1.0);

        Matrix4x4 rotate = Matrix4x4(0.0, value.InverseAxis(2).ToQuat(), FVector3(1, 1, 1));

        matLocal = matGlobal * matLocal;
        matLocal = rotate * matLocal;
        matLocal = invMatGlobal * matLocal;

        m_localRotation = matLocal.GetQuat().EulerAngle().InverseAxis(2);

        UpdateChildRotation();
    }
}

Matrix4x4 Transform::GetInvWorldMatrix() const {
    return Matrix4x4(m_globalPosition, m_globalRotation.Radians().ToQuat(), m_globalScale).Inverse();
}





