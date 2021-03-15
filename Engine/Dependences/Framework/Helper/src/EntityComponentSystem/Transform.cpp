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

#include <Math/Matrix4x4.h>

Framework::Helper::Transform::Transform(Framework::Helper::GameObject *parent) {
    this->m_gameObject = parent;
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

void Framework::Helper::Transform::SetLocalPosition(Framework::Helper::Math::Vector3 val, bool pivot) {
    //Vector3 delta = val - m_localPosition;
    //this->m_localPosition = val;

    //if (m_parent)
    //    this->UpdateChildPosition(delta, pivot);
}

void Framework::Helper::Transform::SetLocalRotation(Framework::Helper::Math::Vector3 val, bool pivot) {
    this->m_localRotation = val;

    if (m_parent)
        this->UpdateChildRotation(pivot);
}

void Framework::Helper::Transform::SetLocalScale(Framework::Helper::Math::Vector3 val, bool pivot) {
    //this->m_localScale = val;
}

void Framework::Helper::Transform::SetPosition(Vector3 val, bool pivot) {
    auto delta = m_globalPosition - val;
    m_globalPosition = val;

    //this->UpdateLocalPosition(delta);

    //this->UpdateDefParentDir();

    m_gameObject->UpdateComponentsPosition();

    for (auto a: m_gameObject->m_children)
        a->m_transform->UpdateChildPosition(delta, pivot);
}

void Framework::Helper::Transform::SetRotation(const Vector3& euler, bool pivot) {
    auto deltaRotate = m_globalRotation - euler;

    //glm::quat delta = glm::quat(glm::radians(m_globalRotation)) - glm::quat(glm::radians(val));
    m_globalRotation = euler;

    //std::cout << glm::to_string(glm::degrees(glm::eulerAngles(delta))) << std::endl;

    m_gameObject->UpdateComponentsRotation();

    //!this->UpdateLocalRotation(deltaRotate);

   for (auto a: m_gameObject->m_children)
       a->m_transform->UpdateChildRotation(pivot);
}

void Framework::Helper::Transform::SetScale(Vector3 val, bool pivot) {
    auto delta = m_globalScale / val;
    m_globalScale = val;

    m_gameObject->UpdateComponentsScale();

    auto temp = m_globalPosition;
    this->SetPosition(Vector3(0,0,0));

    //!this->UpdateLocalScale(delta);
    //this->UpdateLocalPosition();

    for (auto a: m_gameObject->m_children)
        a->m_transform->UpdateChildScale(delta, pivot);

    this->SetPosition(temp);
}
/*
void Framework::Helper::Transform::DeltaTranslate(Framework::Helper::Math::Vector3 delta) {
    if (!m_parent)
        this->Translate(delta, true);
    else {
        if (delta.Empty())
            return;

        Vector3 newPos = m_globalPosition + delta;

        double dist = m_globalPosition.Distance(newPos);
        Vector3 dir = m_globalPosition.Direction(newPos);

        Vector3 trans = Direction(dir, false) * dist;

        this->Translate(trans, true);

        //m_localPosition += delta.Rotate(m_parent->GetRotation().ToQuat());

        //this->UpdateChildRotation(true);

        //this->m_gameObject->UpdateComponentsPosition();
    }
}*/

void Framework::Helper::Transform::GlobalTranslate(Vector3 axis, double value) {
    if (!m_parent)
        this->Translate(axis * value, true);
    else {
        Matrix4x4 rotate = Matrix4x4(m_globalPosition, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), Vector3(1,1,1));
        Matrix4x4 mat = Matrix4x4(m_globalPosition, Vector3(0,0,0).ToQuat(), Vector3(1,1,1));

        Vector3 origin = (mat * rotate).GetQuat().EulerAngle().InverseAxis(2);
        Vector3 dir = origin.Radians().ToQuat() * axis;
        m_localPosition += dir * value;

        this->UpdateChildRotation(true);
    }
}

void Framework::Helper::Transform::Translate(Vector3 val, bool local) noexcept {
    if (local) {
        m_localPosition += val;

        if (!m_parent) {
            m_globalPosition += val;

            this->m_gameObject->UpdateComponentsPosition();

            for (auto a: m_gameObject->m_children)
                a->m_transform->UpdateChildPosition(-val, true);
        }
        else
           this->UpdateChildRotation(true);
    }
    else
        this->SetPosition(m_globalPosition + val);
}

void Framework::Helper::Transform::RotateAxis(Framework::Helper::Math::Vector3 axis, double angle, bool local) noexcept {
    Matrix4x4 rotate = Matrix4x4(m_globalPosition, (axis * angle).InverseAxis(2).ToQuat(), Vector3(1,1,1));

    if (local) {
        Matrix4x4 matLocal = Matrix4x4(m_globalPosition, m_localRotation.InverseAxis(2).ToQuat(), Vector3(1,1,1));
        m_localRotation = (matLocal * rotate).GetQuat().EulerAngle().InverseAxis(2);

        if (m_parent)
            UpdateChildRotation(true);
        else
            this->m_globalRotation = m_localRotation;
    }
    else {
        Matrix4x4 matGlobal = Matrix4x4(m_globalPosition, m_globalRotation.InverseAxis(2).ToQuat(), Vector3(1,1,1));
        m_globalRotation = (matGlobal * rotate).GetQuat().EulerAngle().InverseAxis(2);
    }

    this->m_gameObject->UpdateComponentsRotation();

    for (auto a: m_gameObject->m_children)
        a->m_transform->UpdateChildRotation(true);
}

void Framework::Helper::Transform::GlobalRotateAxis(Framework::Helper::Math::Vector3 axis, double value) {
    //Matrix4x4 mat = Matrix4x4(Vector3(0.0), m_globalRotation.InverseAxis(2).ToQuat(), Vector3(1.0));
    //Matrix4x4 rotate = Matrix4x4(Vector3(0.0), axis.InverseAxis(2).ToQuat() * value, Vector3(1.0));

    //m_globalRotation = (mat * rotate).GetQuat().EulerAngle().InverseAxis(2);

    if (m_parent) {
        {
            Matrix4x4 rotate = Matrix4x4(0.0, (axis * value).InverseAxis(2).ToQuat(), Vector3(1,1,1));
            Matrix4x4 mat = Matrix4x4(0.0, m_globalRotation.InverseAxis(2).ToQuat(), Vector3(1,1,1));

            Matrix4x4 parMat = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), 1.0);

            m_globalRotation = ((rotate * mat)).GetQuat().EulerAngle().InverseAxis(2);

            this->m_gameObject->UpdateComponentsRotation();
            //this->UpdateChildRotation(true);
        }
        //Quaternion qPar = m_parent->m_globalRotation.InverseAxis(2).ToQuat();

        //Matrix4x4 rotate = Matrix4x4(0.0, (axis * value).InverseAxis(2).ToQuat(),  1.0);
        //Matrix4x4 matLocal = Matrix4x4(0.0, m_localRotation.InverseAxis(2).ToQuat(),  1.0);
        //m_localRotation = (rotate * matLocal).GetQuat().EulerAngle().InverseAxis(2);
        //this->UpdateChildRotation(true);

        /*Matrix4x4 rotate = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat().Inverse(), Vector3(1,1,1));
        Matrix4x4 mat = Matrix4x4(0.0, Vector3(0,0,0).ToQuat(), Vector3(1,1,1));

        Vector3 originGlobal = (mat * rotate).GetQuat().EulerAngle().InverseAxis(2);

        //!!!!!!

        Matrix4x4 matGlobal = Matrix4x4(0.0, m_parent->m_globalRotation.InverseAxis(2).ToQuat(), 1.0);
        Matrix4x4 matOrigin = Matrix4x4(0.0, originGlobal.InverseAxis(2).ToQuat(), 1.0);

        Matrix4x4 matLocal  = Matrix4x4(0.0, m_localRotation.InverseAxis(2).ToQuat(), 1.0);*/


        //this->m_gameObject->m_children[0]->m_transform->m_localRotation = origin;
        //this->m_gameObject->m_children[0]->m_transform->UpdateChildRotation(true);

        /*Transform* child = this->m_gameObject->m_children[0]->m_transform;

        {
            Matrix4x4 matGlobal = Matrix4x4(0.0, this->m_globalRotation.InverseAxis(2).ToQuat(), 1.0);
            Matrix4x4 matOrigin = Matrix4x4(0.0, origin.InverseAxis(2).ToQuat(), 1.0);

            Matrix4x4 matLocal  = Matrix4x4(0.0, child->m_localRotation.InverseAxis(2).ToQuat(), 1.0);

            child->m_globalRotation = ((matGlobal * matOrigin) * matLocal).GetQuat().EulerAngle().InverseAxis(2);

            child->m_gameObject->UpdateComponentsRotation();
        }*/
    }
    else {
        Matrix4x4 rotate = Matrix4x4(0.0, (axis * value).InverseAxis(2).ToQuat(), Vector3(1,1,1));
        Matrix4x4 matGlobal = Matrix4x4(0.0, m_globalRotation.InverseAxis(2).ToQuat(), Vector3(1,1,1));
        m_globalRotation = (rotate * matGlobal).GetQuat().EulerAngle().InverseAxis(2);

        this->m_gameObject->UpdateComponentsRotation();

        for (auto a: m_gameObject->m_children)
            a->m_transform->UpdateChildRotation(true);
    }
}

void Framework::Helper::Transform::Rotate(Vector3 angle, bool local) noexcept {
    if (angle == Vector3(0,0,0))
        return;

    Vector3 newRot = m_globalRotation + angle;
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


Framework::Helper::Math::Vector3 Framework::Helper::Transform::Direction(Framework::Helper::Math::Vector3 preDir, bool local) const noexcept {
    if (local)
        return m_localRotation.Radians().ToQuat() * preDir;
    else
        return m_globalRotation.Radians().ToQuat() * preDir;
}

Framework::Helper::Math::Vector3 Framework::Helper::Transform::Forward(bool local) const noexcept {
    return m_globalRotation.Radians().ToQuat() * forward;
}
Framework::Helper::Math::Vector3 Framework::Helper::Transform::Right(bool local) const noexcept {
    //return right.Rotate(m_globalRotation);
    return m_globalRotation.Radians().ToQuat() * right;
}
Framework::Helper::Math::Vector3 Framework::Helper::Transform::Up(bool local) const noexcept {
    //return up.Rotate(m_globalRotation);
    return m_globalRotation.Radians().ToQuat() * up;
}

//float Magnitude(glm::vec3 vec){
//    return sqrt(pow(vec.x, 2) + pow(vec.y, 2) + pow(vec.z, 2));
//}

//glm::vec3 Framework::Helper::Transform::Direction(glm::vec3 point) noexcept {
    //glm::vec3 heading = point - m_globalPosition;
    //float distance = Magnitude(heading);
    //if (std::isnan(distance))
   //     return glm::vec3(0,0,0);
   // return heading / distance;
//}
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
        this->UpdateChildRotation(pivot);

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
    Vector3 deltaScale = m_globalScale / scale;
    //Vector3 deltaPosition = m_globalPosition - translation;


    //if (!deltaPosition.Empty() && m_parent) {
        //this->UpdateDefParentDir();
    //}
        //this->m_defParentDir = m_globalPosition.Direction(m_parent->m_globalPosition);
        //this->m_defParentDir = m_globalRotation.Radians().ToQuat() * m_globalPosition.Direction(m_parent->m_globalPosition);

    if (deltaScale != Vector3(1,1,1)) {
        this->SetPosition(Vector3(0,0,0));
        this->m_globalScale = scale;

        //!this->UpdateLocalScale(deltaScale);

        for (auto a : this->m_gameObject->m_children)
            a->m_transform->UpdateChildScale(deltaScale, pivot);
    }


    if (m_globalRotation != euler) {
        this->m_globalRotation = euler;
        //!this->UpdateLocalRotation(deltaRotate);
        for (auto a : this->m_gameObject->m_children)
            a->m_transform->UpdateChildRotation(pivot);
    }

    this->SetPosition(translation);
    //this->m_globalPosition = translation;

    //this->UpdateLocalPosition(deltaPosition);
    //if (m_parent)
    //    this->UpdateChildRotation(Vector3(0,0,0), pivot);

    m_gameObject->UpdateComponents();

    //for (auto a : this->m_gameObject->m_children) {
    //    a->m_transform->UpdateChildPosition(deltaPosition, pivot);
    //}
}

glm::mat4 Framework::Helper::Transform::GetMatrix(bool local) const noexcept  {

    //glm::vec3 v = checkVec3Zero(m_globalRotation.EulerAngle().Degrees().ToGLM());
    //modelMat *= mat4_cast(glm::quat(glm::radians(v)));

    //glm::vec3 v = m_globalRotation.ToQuat().EulerAngle().ToGLM();
    //modelMat *= mat4_cast(glm::quat(v));



    if (local) {
        glm::mat4 localMat = glm::translate(glm::mat4(1.0f), m_globalPosition.ToGLM());
        //!localMat *= mat4_cast(m_globalRotation.InverseAxis(2).ToQuat().ToGLM());
        localMat *= mat4_cast(m_localRotation.InverseAxis(2).ToQuat().ToGLM());
        //localMat *= mat4_cast(glm::inverse(m_localRotation.ToQuat().ToGLM()));
        //localMat *= mat4_cast(glm::inverse(m_localRotation.InverseAxis(2).Degrees().ToQuat().ToGLM()));
        //localMat *= mat4_cast(glm::inverse(m_localRotation.InverseAxis(2).ToQuat(true).ToGLM()));
        localMat = glm::scale(localMat, m_globalScale.ToGLM());
        return localMat;
    } else {
        glm::mat4 globalMat = glm::translate(glm::mat4(1.0f), m_globalPosition.ToGLM());
        globalMat *= mat4_cast(m_globalRotation.InverseAxis(2).ToQuat().ToGLM());
        globalMat =  glm::scale(globalMat, m_globalScale.ToGLM());
        return globalMat;
    }

    //return glm::mat4(1);
}

void Framework::Helper::Transform::UpdateChildPosition(Vector3 delta, bool pivot) {
    m_globalPosition -= delta;

    //!this->UpdateLocalPosition();

    this->m_gameObject->UpdateComponentsPosition();

    for (auto a : m_gameObject->m_children)
        a->m_transform->UpdateChildPosition(delta, pivot);
}

void Framework::Helper::Transform::UpdateChildScale(Vector3 delta, bool pivot) {
    auto newScale = m_parent->m_globalScale * m_localScale;
    this->m_globalScale = newScale;

    //!this->UpdateLocalScale();

    this->m_globalPosition /= delta;
    this->UpdateChildRotation(pivot);

    this->m_gameObject->UpdateComponentsPosition();
    this->m_gameObject->UpdateComponentsScale();

    //!this->UpdateLocalPosition();

    for (auto a : m_gameObject->m_children)
        a->m_transform->UpdateChildScale(delta, pivot);
}

void Framework::Helper::Transform::UpdateChildRotation(bool pivot) {
    this->m_globalRotation = m_parent->m_globalRotation;
    {
        Vector3 point = m_parent->m_globalPosition;
        //!Vector3 defDir = -m_parent->Direction(m_defParentDir);
        //double dist = m_globalPosition.Distance(point); // некорректно когда объект сдвинут, нужно компенсировать!

        //Vector3 newPos = point + defDir * dist;
        Vector3 newPos = point;//! + defDir;
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

    Matrix4x4 matGlobal = Matrix4x4(m_globalPosition, m_globalRotation.InverseAxis(2).ToQuat(), Vector3(1,1,1));
    Matrix4x4 matLocal = Matrix4x4(m_globalPosition, m_localRotation.InverseAxis(2).ToQuat(), Vector3(1,1,1));

    m_globalRotation = (matGlobal * matLocal).GetQuat().EulerAngle().InverseAxis(2);

    this->m_gameObject->UpdateComponentsRotation();
    this->m_gameObject->UpdateComponentsPosition();

    for (auto a : m_gameObject->m_children)
        a->m_transform->UpdateChildRotation(pivot);

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

void Framework::Helper::Transform::UpdateLocalPosition(Vector3 delta) {


    //if (m_parent) {
    //    m_localPosition = (m_globalPosition - m_parent->m_globalPosition) / m_parent->m_globalScale;
    //} else
    //    m_localPosition = m_globalPosition;
}

void Framework::Helper::Transform::UpdateLocalScale(Vector3 delta) {
    //if (m_parent) {
    //    this->m_localScale = m_globalScale / m_parent->m_globalScale;
    //} else
    //    m_localScale = m_globalScale;
}

void Framework::Helper::Transform::UpdateLocalRotation(Vector3 delta) {

    //if (m_parent) {
    //    this->m_localRotation = m_globalRotation - m_parent->m_globalRotation;
    //} else
    //    m_localRotation = m_globalRotation;
}

void Framework::Helper::Transform::OnParentSet(Framework::Helper::Transform *parent) {
    this->m_parent = parent;
    this->UpdateDefParentDir();
    this->UpdateChildRotation(true);
}






