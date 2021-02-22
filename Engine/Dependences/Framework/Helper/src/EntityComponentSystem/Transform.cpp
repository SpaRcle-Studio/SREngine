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

Framework::Helper::Transform::Transform(Framework::Helper::GameObject *parent) {
    this->m_gameObject = parent;
}

void Framework::Helper::Transform::SetPosition(glm::vec3 val) {
    m_globalPosition = val;

    if (m_gameObject->m_parent)
        m_localPosition = m_globalPosition - m_gameObject->m_parent->m_transform->m_globalPosition;
    else
        m_localPosition = m_globalPosition;

    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm->m_transform->UpdateChildPosition(this);
        //m.second->m_transform->UpdateChildPosition(this);
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

    m_globalRotation = val;
    //delta = m_globalRotation - delta;
    glm::vec3 delta = m_globalRotation;

    m_localRotation = m_globalRotation;

    m_gameObject->UpdateComponentsRotation();

    for (auto gm : m_gameObject->m_children) {
        gm->m_transform->UpdateChildRotation(this, delta);
        //gm.second->m_transform->UpdateChildRotation(this, delta);
    }
}

void Framework::Helper::Transform::SetScale(glm::vec3 val) {
    m_globalScale = val;

    // TODO
    if (m_gameObject->m_parent)
        m_localScale = m_globalScale - m_gameObject->m_parent->m_transform->m_globalScale;
    else
        m_localScale = val;

    m_gameObject->UpdateComponentsScale();

    for (auto gm : m_gameObject->m_children)
        gm->m_transform->UpdateChildScale(this);
        //gm.second->m_transform->UpdateChildScale(this);
}

void Framework::Helper::Transform::Translate(glm::vec3 val) noexcept {
    this->SetPosition(m_localPosition + val);
}

void Framework::Helper::Transform::Rotate(glm::vec3 angle) noexcept {
    this->SetRotation(m_localRotation + angle);

    /*if (!m_gameObject->m_parent)
        this->SetRotation(m_localRotation + angle);
    else {
        glm::fquat q = glm::radians(glm::vec3(
                m_globalRotation.x,
                m_globalRotation.y,
                -m_globalRotation.z
        ));

        q *= glm::quat(glm::radians(angle));

        this->m_localRotation = Lim360(m_localRotation + angle);
        this->m_globalRotation = Lim360(glm::degrees(glm::eulerAngles(q)));

        m_gameObject->UpdateComponentsScale();

        for (auto gm : m_gameObject->m_children)
            gm.second->m_transform->UpdateChildScale(this);
    }*/
}

void Framework::Helper::Transform::Scaling(glm::vec3 val) noexcept {
    //this->SetScale(m_scale + val);
    // TODO
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
    //this->CheckNaN_Position();

    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm->m_transform->UpdateChildPosition(this);
    }
}

void Framework::Helper::Transform::UpdateChildRotation(Framework::Helper::Transform *parent, glm::vec3 delta) noexcept {
    this->SetRotateAround(parent->m_globalPosition, m_childDefRotation + delta);


    //this->m_globalRotation = Lim360(parent->m_globalRotation + m_localRotation);

    //this->SetRotateAround(parent, parent->m_globalRotation);

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
    this->m_globalScale = parent->m_globalScale + m_localScale;
    //CheckNaN_Scale();

    m_gameObject->UpdateComponentsScale();

    for (auto gm : m_gameObject->m_children) {
        gm->m_transform->UpdateChildScale(this);
    }
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
        rot.x, //rot.x,
        rot.y, //rot.y,
        -rot.z  //-rot.z
    ));

    return q * -forward; // return q * -forward;
}
glm::vec3 Framework::Helper::Transform::Right(bool local) const noexcept {
    const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x, //rot.x,
        rot.y, //-rot.y, //rot.y,
        -rot.z //-rot.z
    ));

    return q * -right; //return q * right;
}
glm::vec3 Framework::Helper::Transform::Up(bool local) const noexcept {
    const glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    glm::fquat q = glm::radians(glm::vec3(
        rot.x, // rot.x,
        rot.y, //rot.y,
        -rot.z //-rot.z
    ));

    return q * up; //return q * up;
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

//! COMPLETED
void Framework::Helper::Transform::RotateAround(glm::vec3 point, glm::vec3 angle) noexcept {
    if (angle == glm::vec3(0,0,0))
        return;

    glm::vec3 vector3 = glm::quat(RAD3(angle)) * (m_globalPosition - point);
    this->m_globalPosition = point + vector3;

    if (m_gameObject->m_parent)
        m_localPosition = m_globalPosition - m_gameObject->m_parent->m_transform->m_globalPosition;
    else
        m_localPosition = m_globalPosition;

    ///====================================

    const glm::quat q = RAD3(angle);
    const glm::quat self = RAD3(m_globalRotation);

    glm::vec3 delta = m_globalRotation;
    this->m_globalRotation = DEG3(glm::eulerAngles(q * self));
    delta = m_globalRotation - delta;

    this->m_localRotation = m_globalRotation;

    CheckNaN_Rotation();

    m_gameObject->UpdateComponentsRotation();
    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm->m_transform->UpdateChildRotation(this, delta);
        gm->m_transform->UpdateChildPosition(this);
        //gm.second->m_transform->UpdateChildRotation(this, delta);
        //gm.second->m_transform->UpdateChildPosition(this);
    }

    if (false) {
        glm::fquat q = glm::radians(glm::vec3(
                angle.x,
                angle.y,
                -angle.z
        ));

        glm::quat q_global = glm::radians(glm::vec3(
                m_globalRotation.x,
                m_globalRotation.y,
                -m_globalRotation.z
        ));

        glm::quat q_self = q_global * q;

        m_globalRotation = Lim360(glm::degrees(glm::eulerAngles(q_self)));

        CheckNaN_Rotation();

        ///=====================================================

        glm::vec3 dir = glm::quat(glm::radians(glm::vec3(
                m_globalRotation.x,
                m_globalRotation.y,
                -m_globalRotation.z
        ))) * (m_globalPosition - point);

        {
            m_globalPosition = point + dir;

            if (m_gameObject->m_parent)
                m_localPosition = m_globalPosition - m_gameObject->m_parent->m_transform->m_globalPosition;
            else
                m_localPosition = m_globalPosition;
        }

        ///===================================

        m_gameObject->UpdateComponentsRotation();
        m_gameObject->UpdateComponentsPosition();

        for (auto gm : m_gameObject->m_children) {
            gm->m_transform->UpdateChildRotation(this, delta);
            gm->m_transform->UpdateChildPosition(this);
            //gm.second->m_transform->UpdateChildRotation(this, delta);
            //gm.second->m_transform->UpdateChildPosition(this);
        }

        ///===================================
    }

    /*glm::quat qq = glm::angleAxis(1.f, glm::radians(glm::vec3(
            angle.x,
            angle.y,
            -angle.z
            )));

    glm::vec3 dir = qq * (m_globalPosition - point);
    m_globalPosition = point + dir;*/

    /*
    //float dist = this->Distance(point);
    //glm::vec3 direction = Direction(point);
    //glm::vec3 dir = (q * -direction) * dist;

    m_globalRotation = glm::degrees(glm::eulerAngles(q_global * q));


    // Set game object position

    //this->SetRotateAround(point, m_aroundRotation + angle);
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
    }

    //glm::mat transMat = glm::translate(glm::mat4(1), m_globalPosition);

    //glm::vec3 rotation = m_globalRotation + angle;

    /*glm::fquat q = glm::radians(glm::vec3(
            rotation.x,
            rotation.y,
            -rotation.z
    ));

    glm::vec3 dir = q * (m_globalPosition - point);

    glm::vec3 pos = point + dir;


    //glm::mat4 rotateMat = glm::mat4_cast(q);

    //transMat *= rotateMat;

    //this->SetRotation(glm::degrees(glm::eulerAngles(glm::getRotation(transMat))));

    //glm::quat q2 = glm::getRotation(transMat);


    //!===================================================

    //this->SetRotation(rotation);

    //this->SetPosition(pos);

    //this->Rotate(angle); */
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
    if (angle == glm::vec3(0,0,0))
        return;

    //std::cout << glm::to_string(angle) << std::endl;

    glm::fquat q = glm::radians(glm::vec3(
            angle.x,
            angle.y,
            -angle.z
    ));

    float dist = this->Distance(point);

    glm::vec3 dir = (q * forward) * dist;

    // Set game object position
    {
        m_globalPosition = point + dir;

        if (m_gameObject->m_parent)
            m_localPosition = m_globalPosition - m_gameObject->m_parent->m_transform->m_globalPosition;
        else
            m_localPosition = m_globalPosition;
    }

    ///===================================
    /*
    glm::quat q_self = q * glm::quat(glm::radians(m_localRotation));

    m_globalRotation = Lim360(glm::degrees(glm::eulerAngles(q_self)));
*/
    glm::vec3 delta = glm::vec3();

    CheckNaN_Position();
    CheckNaN_Rotation();

    m_gameObject->UpdateComponentsRotation();
    m_gameObject->UpdateComponentsPosition();

    for (auto gm : m_gameObject->m_children) {
        gm->m_transform->UpdateChildRotation(this, delta);
        gm->m_transform->UpdateChildPosition(this);
        //gm.second->m_transform->UpdateChildRotation(this, delta);
        //gm.second->m_transform->UpdateChildPosition(this);
    }
}

void Framework::Helper::Transform::LookAt(Framework::Helper::GameObject *gameObject) noexcept {
    this->LookAt(gameObject->m_transform->m_globalPosition);
}

void Framework::Helper::Transform::CheckNaN_Position() noexcept {
    if (m_globalPosition.x != m_globalPosition.x) m_globalPosition.x = 0.f;
    if (m_globalPosition.y != m_globalPosition.y) m_globalPosition.y = 0.f;
    if (m_globalPosition.z != m_globalPosition.z) m_globalPosition.z = 0.f;

    if (m_localPosition.x != m_localPosition.x) m_localPosition.x = 0.f;
    if (m_localPosition.y != m_localPosition.y) m_localPosition.y = 0.f;
    if (m_localPosition.z != m_localPosition.z) m_localPosition.z = 0.f;
}

void Framework::Helper::Transform::CheckNaN_Rotation() noexcept {
    if (m_globalRotation.x != m_globalRotation.x) m_globalRotation.x = 0.f;
    if (m_globalRotation.y != m_globalRotation.y) m_globalRotation.y = 0.f;
    if (m_globalRotation.z != m_globalRotation.z) m_globalRotation.z = 0.f;

    if (m_localRotation.x != m_localRotation.x) m_localRotation.x = 0.f;
    if (m_localRotation.y != m_localRotation.y) m_localRotation.y = 0.f;
    if (m_localRotation.z != m_localRotation.z) m_localRotation.z = 0.f;
}

void Framework::Helper::Transform::CheckNaN_Scale() noexcept {
    if (m_globalScale.x != m_globalScale.x) m_globalScale.x = 1.f;
    if (m_globalScale.y != m_globalScale.y) m_globalScale.y = 1.f;
    if (m_globalScale.z != m_globalScale.z) m_globalScale.z = 1.f;

    if (m_localScale.x != m_localScale.x) m_localScale.x = 1.f;
    if (m_localScale.y != m_localScale.y) m_localScale.y = 1.f;
    if (m_localScale.z != m_localScale.z) m_localScale.z = 1.f;
}

glm::vec3 Framework::Helper::Transform::GetAngleOfPoint(glm::vec3 point) noexcept {
    glm::vec3 D = Direction(point); // direction

    float angle_H = asin(D.y);
    float angle_P = asin(D.z);

    return DEG3(glm::vec3(
        angle_H,
        angle_P,
        0
    ));

    /*
    glm::vec3 D = Direction(point); // direction

    glm::vec3 U = Up(); // Up direction

    float angle_H = atan2(D.y,D.x);
    float angle_P = asin(D.z);

    glm::vec3 W0 = glm::vec3( -D.y, D.x, 0 );
    glm::vec3 U0 = W0 * D;

    float f1 = glm::dot(W0,U);
    float f2 = glm::dot(U0,U) / Len(W0) * Len(U0);

    float angle_B = atan2(f1, f2);

    return DEG3(glm::vec3(
        angle_H,
        angle_P,
        0
    ));

     //////
     *     glm::vec3 D = point - m_globalPosition;

    D = glm::normalize(D);

    float angle = atan2( D.x, D.z ); // Note: I expected atan2(z,x) but OP reported success with atan2(x,z) instead! Switch around if you see 90° off.
    float qx = 0.f;
    float qy = 1.f * sin( angle/2.f );
    float qz = 0.f;
    float qw = cos( angle/2.f );

    return {
        qx,
        qy,
        qz,
        qw
    };
     */
}

glm::vec3 Framework::Helper::Transform::GetNormalizedAngleOfPoint(glm::vec3 point) noexcept {
    Location locX = GetGlobal_LCR_Location(point);
    Location locZ = GetGlobal_FCB_Location(point);

    glm::vec3 angle = GetAngleOfPoint(point);

    switch (locX) {
        case Location::Right: // left
            if (angle.y < 0)
                angle.y = -(angle.y + 90.f);
            else if (angle.y > 0)
                angle.y = -angle.y - 90.f;
            else
                angle.y = -90.f;
            break;
        case Location::Left: // right
            if (angle.y < 0)
                angle.y = (angle.y + 90.f);
            else if (angle.y > 0)
                angle.y += 90.f;
            else
                angle.y = 90.f;
            break;
        case Location::Center:
            // additional maths
            switch (locZ) {
                case Location::Forward: // back
                    angle.y = 180.f;
                    break;
                case Location::Back: // forward
                    angle.y = 0.f;
                    break;
                case Location::Center:
                    angle.y = 0.f;
                    //Helper::Debug::Warn("Transform::GetNormalizedAngleOfPoint() : in center? TODO AND SEE!");
                    // what?
                    break;
            }
            break;
        default:
            Helper::Debug::Error("Transform::GetNormalizedAngleOfPoint() : [FATAL] location is not correct! Something went wrong...");
            return glm::vec3();
    }

    return angle;
}

void Framework::Helper::Transform::SetMatrix(glm::mat4 matrix, bool pivot) noexcept  {
    glm::vec3 scale;
    glm::quat rotation;
    glm::vec3 translation;

    glm::vec3 skew;
    glm::vec4 perspective;

    glm::decompose(matrix, scale, rotation, translation, skew, perspective);

    glm::vec3 rot = glm::degrees(glm::eulerAngles(rotation));
    this->m_globalPosition = {translation.x, translation.y, translation.z};
    this->m_globalRotation = { rot.x, rot.y, rot.z };
    this->m_globalScale    = scale;

    if (!m_gameObject->m_parent) {
        m_localScale    = m_globalScale;
        m_localRotation = m_globalRotation;
        m_localPosition = m_globalPosition;
    } else {
        m_localPosition = m_globalPosition - m_gameObject->m_parent->m_transform->m_globalPosition;
        m_localRotation = m_globalRotation - m_gameObject->m_parent->m_transform->m_globalRotation;
        m_localScale    = m_globalScale    - m_gameObject->m_parent->m_transform->m_globalScale;
    }

    //!---------------------------------------------------------------------------------------------------------

    m_gameObject->UpdateComponents();

    for (auto gm : m_gameObject->m_children) {
        gm->m_transform->UpdateChildPosition(this);
        gm->m_transform->UpdateChildScale(this);
        //gm->m_transform->UpdateChildRotation(this);
    }
}

glm::mat4 Framework::Helper::Transform::GetMatrix(bool local) const noexcept  {
    //bool local = m_gameObject->m_parent != nullptr;

    glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), {
            local ? m_localPosition.x : m_globalPosition.x,
            local ? m_localPosition.y : m_globalPosition.y,
            local ? m_localPosition.z : m_globalPosition.z
    });

    glm::vec3 rot = local ? m_localRotation : m_globalRotation;
    const glm::mat4 rotationMatrix = mat4_cast(glm::quat(glm::radians(glm::vec3(
            { rot.x, rot.y, rot.z }
            // {0, 45,0}
    ))));

    modelMat *= rotationMatrix;

    return glm::scale(modelMat, local ? m_localScale : m_globalScale);
}




