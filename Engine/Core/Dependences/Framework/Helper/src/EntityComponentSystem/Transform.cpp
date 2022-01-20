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

Framework::Helper::Transform::Transform(GameObject* parent) {
    this->m_gameObject = parent;
    this->m_globalRotation = Math::CmpEpsilonFV3;
    this->m_localRotation  = Math::CmpEpsilonFV3;
}

void Framework::Helper::Transform::UpdateDefParentDir() {
    if (m_parent) {
       //! this->m_defParentDir = m_globalPosition.Direction(m_parent->m_globalPosition);

       /*glm::vec3 rot = m_parent->m_globalRotation.Radians().ToQuat().EulerAngle().ToGLM();
        glm::fquat q = glm::vec3(
                rot.x,
                rot.y,
                rot.z
        );

        this->m_defParentDir =  q * m_defParentDir.ToGLM();*/

        //this->m_defParentDir = m_parent->m_globalRotation.Radians().ToQuat() * m_defParentDir;
        //this->m_defParentDir = this->m_defParentDir.Rotate(m_parent->m_globalRotation.Radians().ToQuat());
    }
}

void Framework::Helper::Transform::SetLocalPosition(Framework::Helper::Math::FVector3 val) {
    FVector3 delta = m_localPosition - val;
    this->m_localPosition = val;

    if (m_parent)
        this->UpdateChildPosition(delta);
    else {
        this->m_globalPosition = val;

        m_gameObject->UpdateComponentsPosition();

        for (const auto& child: m_gameObject->m_children)
            child->m_transform->UpdateChildPosition(delta);
    }
}

void Framework::Helper::Transform::SetLocalRotation(Framework::Helper::Math::FVector3 val) {
    this->m_localRotation = FVector3::FixEulerAngles(val);

    if (m_parent)
        this->UpdateChildRotation();
    else {
        this->m_globalRotation = m_localRotation;

        m_gameObject->UpdateComponentsRotation();

        for (const auto& child: m_gameObject->m_children)
            child->m_transform->UpdateChildRotation();
    }
}

void Framework::Helper::Transform::SetLocalScale(Framework::Helper::Math::FVector3 val) {
    //this->m_localScale = val;
}

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

void Framework::Helper::Transform::SetRotation(const FVector3& euler, bool pivot) {
    auto deltaRotate = m_globalRotation - euler;

    //glm::quat delta = glm::quat(glm::radians(m_globalRotation)) - glm::quat(glm::radians(val));
    m_globalRotation = euler;

    //std::cout << glm::to_string(glm::degrees(glm::eulerAngles(delta))) << std::endl;

    m_gameObject->UpdateComponentsRotation();

    //!this->UpdateLocalRotation(deltaRotate);

   for (auto a: m_gameObject->m_children)
       a->m_transform->UpdateChildRotation();
}

void Framework::Helper::Transform::SetScale(FVector3 val, bool pivot) {
    auto delta = m_globalScale / val;
    m_globalScale = val;

    m_gameObject->UpdateComponentsScale();

    auto temp = m_globalPosition;
    this->SetPosition(FVector3(0,0,0));

    for (auto a: m_gameObject->m_children)
        a->m_transform->UpdateChildScale(delta);

    this->SetPosition(temp);
}

void Framework::Helper::Transform::SetGlobalPosition(Framework::Helper::Math::FVector3 position) {
    if (!m_parent) {
        FVector3 delta = m_globalPosition - position;
        m_globalPosition = m_localPosition = position;

        this->m_gameObject->UpdateComponentsPosition();
        for (const auto& a: m_gameObject->m_children)
            a->m_transform->UpdateChildPosition(delta);
    } else {
        // TODO: optimize
        GlobalTranslate(-m_globalPosition);
        GlobalTranslate(position);
    }
}

void Framework::Helper::Transform::GlobalTranslate(FVector3 axis, double value) {
    if (!m_parent)
        this->Translate(axis * value);
    else {
        Matrix4x4 rotate = Matrix4x4(m_globalPosition, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), FVector3(1,1,1));
        Matrix4x4 mat = Matrix4x4(m_globalPosition, FVector3(0,0,0).ToQuat(), FVector3(1,1,1));

        FVector3 origin = (mat * rotate).GetQuat().EulerAngle().InverseAxis(2);
        FVector3 dir = origin.Radians().ToQuat() * axis;
        m_localPosition += (dir * value) / m_parent->m_globalScale;

        this->UpdateChildRotation();
    }
}

void Framework::Helper::Transform::GlobalTranslate(Framework::Helper::Math::FVector3 value) {
    if (!m_parent)
        this->Translate(value);
    else {
        Matrix4x4 rotate = Matrix4x4(m_globalPosition, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), FVector3(1,1,1));
        Matrix4x4 mat = Matrix4x4(m_globalPosition, FVector3(0,0,0).ToQuat(), FVector3(1,1,1));

        FVector3 origin = (mat * rotate).GetQuat().EulerAngle().InverseAxis(2);
        auto preDir = origin.Radians().ToQuat();
        m_localPosition += (preDir * value) / m_parent->m_globalScale;

        this->UpdateChildRotation();
    }
}

void Framework::Helper::Transform::Translate(FVector3 val) noexcept {
    val /= m_globalScale;

    //if (local) {
        m_localPosition += val;

        if (!m_parent) {
            m_globalPosition += val;

            this->m_gameObject->UpdateComponentsPosition();

            for (const auto& a: m_gameObject->m_children)
                a->m_transform->UpdateChildPosition(-val);
        }
        else
           this->UpdateChildRotation();
    //} else
    //    this->SetPosition(m_globalPosition + val);
}

void Framework::Helper::Transform::RotateAxis(Framework::Helper::Math::FVector3 axis, double angle) noexcept {
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
    }
}

void Framework::Helper::Transform::GlobalRotateAxis(Framework::Helper::Math::FVector3 axis, double value) {
    if (m_parent) {
        Matrix4x4 matLocal = Matrix4x4(0.0, m_localRotation.InverseAxis(2).ToQuat(), 1.0);
        Matrix4x4 matGlobal = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat(), 1.0);
        Matrix4x4 invMatGlobal = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), 1.0);

        Matrix4x4 rotate = Matrix4x4(0.0, (axis * value).InverseAxis(2).ToQuat(), FVector3(1, 1, 1));

        matLocal = matGlobal * matLocal;
        matLocal = rotate * matLocal;
        matLocal = invMatGlobal * matLocal;

        m_localRotation = matLocal.GetQuat().EulerAngle().InverseAxis(2);

        this->UpdateChildRotation();
    } else {
        Matrix4x4 rotate = Matrix4x4(0.0, (axis * value).InverseAxis(2).ToQuat(), FVector3(1, 1, 1));
        Matrix4x4 matGlobal = Matrix4x4(0.0, m_globalRotation.InverseAxis(2).ToQuat(), FVector3(1, 1, 1));
        m_localRotation = m_globalRotation = (rotate * matGlobal).GetQuat().EulerAngle().InverseAxis(2);

        this->m_gameObject->UpdateComponentsRotation();

        for (const auto& a: m_gameObject->m_children)
            a->m_transform->UpdateChildRotation();
    }
}

void Framework::Helper::Transform::RotateAround(FVector3 point, FVector3 axis, Unit angle, bool local) noexcept {
    if (local) {
        auto q = m_globalRotation.InverseAxis(1).ToQuat();
        axis = axis.InverseAxis(1).Rotate(q).InverseAxis(1);

        this->GlobalRotateAxis(axis, angle);
    }
    else
        this->GlobalRotateAxis(axis, angle);

    FVector3 worldPos = m_globalPosition;

    Quaternion q = Quaternion(axis.Radians() * angle);
    FVector3 dif = worldPos - point;
    dif = q * dif;
    worldPos = point + dif;

    this->SetGlobalPosition(worldPos);
}

void Framework::Helper::Transform::Rotate(FVector3 angle) noexcept {
    if (angle == FVector3(0,0,0))
        return;

    FVector3 newRot = m_globalRotation + angle;
    this->SetRotation(newRot.Limits(360));

    //RotateAxis(angle, 1.f, local);

    //glm::quat q = this->m_globalRotation;
    //q = glm::quat(glm::radians(angle)) * q;

    //if (angle.x != 0)
    //   q = glm::rotate(q, glm::radians(angle.x), glm::vec3(1,0,0));
    //if (angle.y != 0)
    //    q = glm::rotate(q, glm::radians(angle.y), glm::vec3(0,1,0));
    //if (angle.z != 0)
    //    q = glm::rotate(q, glm::radians(angle.z), glm::vec3(0,0,1));

    //this->SetRotation(q);

    //if (!local)
        //!this->SetRotation(m_globalRotation + angle);
    /*else {
        this->m_localRotation += angle;
        m_localRotation = m_localRotation.Limits(360);

        if (m_parent)
            this->UpdateChildRotation(true);
        else{
            Matrix4x4 matGlobal = Matrix4x4(m_globalPosition, m_globalRotation.InverseAxis(2).ToQuat(), m_globalScale);
            Matrix4x4 matLocal = Matrix4x4(m_globalPosition, m_localRotation.InverseAxis(2).ToQuat(), m_globalScale);

            m_globalRotation = (matGlobal * matLocal).GetQuat().EulerAngle().InverseAxis(2);
            this->m_gameObject->UpdateComponentsRotation();

            for (auto a: m_gameObject->m_children)
                a->m_transform->UpdateChildRotation(true);
        }
    }*/
    //!this->SetRotation(m_globalRotation.EulerAngle() + angle.Radians());
    //this->SetRotation(m_globalRotation * Quaternion(angle.Radians()));
   //Vector3 vec3 = Vector3::FromGLM(angle).Radians();
   //Vector3 euler = m_globalRotation.EulerAngle();

   //std::cout << (euler + vec3).Degrees().ToString() << std::endl;

   //this->SetRotation(euler + vec3);
    //this->SetRotation(m_localRotation + angle);
    //this->SetRotation(glm::degrees(glm::eulerAngles(
    //       m_globalRotation + glm::quat(glm::radians(angle))
    //        )));
   // this->SetRotation(glm::degrees(glm::eulerAngles(m_globalRotation)) + angle);
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


    auto euler = Quaternion(rotation).EulerAngle(true).InverseAxis(2);

    //glm::vec3 deltaScale = scale / m_globalScale;
    FVector3 deltaScale = m_globalScale / FVector3(scale);
    //Vector3 deltaPosition = m_globalPosition - translation;


    //if (!deltaPosition.Empty() && m_parent) {
        //this->UpdateDefParentDir();
    //}
        //this->m_defParentDir = m_globalPosition.Direction(m_parent->m_globalPosition);
        //this->m_defParentDir = m_globalRotation.Radians().ToQuat() * m_globalPosition.Direction(m_parent->m_globalPosition);

    if (deltaScale != FVector3(1,1,1)) {
        this->SetPosition(FVector3(0,0,0));
        this->m_globalScale = FVector3(scale);

        //!this->UpdateLocalScale(deltaScale);

        for (auto a : this->m_gameObject->m_children)
            a->m_transform->UpdateChildScale(deltaScale);
    }


    if (m_globalRotation != euler) {
        this->m_globalRotation = euler;
        //!this->UpdateLocalRotation(deltaRotate);
        for (auto a : this->m_gameObject->m_children)
            a->m_transform->UpdateChildRotation();
    }

    this->SetPosition(FVector3(translation));
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

    //!this->UpdateLocalPosition();

    this->m_gameObject->UpdateComponentsPosition();

    for (const auto& a : m_gameObject->m_children)
        a->m_transform->UpdateChildPosition(delta);
}

void Framework::Helper::Transform::UpdateChildScale(FVector3 delta) {
    auto newScale = m_parent->m_globalScale * m_localScale;
    this->m_globalScale = newScale;

    //!this->UpdateLocalScale();

    this->m_globalPosition /= delta;
    this->UpdateChildRotation();

    this->m_gameObject->UpdateComponentsPosition();
    this->m_gameObject->UpdateComponentsScale();

    //!this->UpdateLocalPosition();

    for (const auto& a : m_gameObject->m_children)
        a->m_transform->UpdateChildScale(delta);
}

void Framework::Helper::Transform::UpdateChildRotation() {
    this->m_globalRotation = m_parent->m_globalRotation;
    {
        FVector3 point = m_parent->m_globalPosition;
        //!Vector3 defDir = -m_parent->Direction(m_defParentDir);
        //double dist = m_globalPosition.Distance(point); // некорректно когда объект сдвинут, нужно компенсировать!

        //Vector3 newPos = point + defDir * dist;
        FVector3 newPos = point;//! + defDir;
        //this->m_globalPosition = originPos;

        //!----------------------------------------------------------

        //Vector3 offsetDir = originPos.Direction(m_globalPosition) + defDir;
        //double offsetDist = originPos.Distance(m_globalPosition);

        //Debug::Log(offsetDir.ToString() + std::to_string(offsetDist));

        //Debug::Log((-Direction(origDir) * origDist).ToString());
        //Debug::Log(origDir.ToString());

        //this->m_globalPosition = originPos - (offsetDir * offsetDist);
        //if (origDist > 0)
        //    this->m_globalPosition = newPos - Direction(origDir);
        //else

        if (m_localPosition.Empty())
            this->m_globalPosition = newPos;//! - defDir;
        else
            this->m_globalPosition =
                    newPos +
                    Direction(m_localPosition * m_parent->m_globalScale)// * m_parent->m_globalScale
                    ;//!- defDir;
    }

    Matrix4x4 matGlobal = Matrix4x4(m_globalPosition, m_globalRotation.InverseAxis(2).ToQuat(), FVector3(1,1,1));
    Matrix4x4 matLocal = Matrix4x4(m_globalPosition, m_localRotation.InverseAxis(2).ToQuat(), FVector3(1,1,1));

    m_globalRotation = (matGlobal * matLocal).GetQuat().EulerAngle().InverseAxis(2);

    this->m_gameObject->UpdateComponentsRotation();
    this->m_gameObject->UpdateComponentsPosition();

    for (const auto& a : m_gameObject->m_children)
        a->m_transform->UpdateChildRotation();

    //!===================================

    //glm::quat newRotate = glm::quat(glm::radians(m_parent->m_globalRotation)) * glm::quat(glm::radians(m_localRotation));
    //this->m_globalRotation = glm::degrees(glm::eulerAngles(newRotate));

    /*this->m_globalRotation = m_parent->m_globalRotation + m_localRotation;

    this->UpdateLocalRotation();

    this->m_gameObject->UpdateComponentsRotation();

    this->UpdateLocalPosition();

    for (auto a : m_gameObject->m_children)
        a->m_transform->UpdateChildRotation(delta, pivot);*/
}

void Framework::Helper::Transform::OnParentSet(Framework::Helper::Transform *parent) {
    if ((m_parent = parent)) {
        UpdateDefParentDir();
        UpdateChildRotation();
    }
    else {
        /// TODO!
    }
}

void Framework::Helper::Transform::Scaling(Framework::Helper::Math::FVector3 val) {
    //Debug::Log(val.ToString());

    if (m_parent) { // local
        m_localScale += val;
        this->UpdateChildRotation();
        auto delta = m_localScale / val;

        this->UpdateChildScale(delta);
    }
    else { // global
        this->SetScale(m_globalScale + val, true);
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





