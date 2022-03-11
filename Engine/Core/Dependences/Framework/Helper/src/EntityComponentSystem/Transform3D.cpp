//
// Created by Monika on 19.02.2022.
//

#include "EntityComponentSystem/Transform3D.h"
#include <EntityComponentSystem/GameObject.h>

using namespace Framework::Helper;

Transform3D::Transform3D(GameObject* parent)
    : m_gameObject(parent)
{
    m_translation = FVector3::Zero();
    m_rotation = FVector3::Zero();
    m_scale = FVector3::One();
    m_skew = FVector3::One();
}

void Transform3D::OnParentSet(Transform3D* parent) {
    m_parent = parent;
}

void Transform3D::UpdateComponents() {
    if (m_gameObject)
         m_gameObject->UpdateComponents();
}

void Transform3D::Translate(Math::FVector3 translation) {
    const auto&& direction = TransformDirection(translation);
    SetTranslation(m_translation + direction);
}

void Transform3D::Rotate(Math::FVector3 eulers) {
    Matrix4x4&& worldRotateMatrix = Matrix4x4::FromEulers(m_rotation);
    Matrix4x4&& rotatedMatrix = worldRotateMatrix * Matrix4x4::FromEulers(eulers);
    SetRotation(rotatedMatrix.GetQuat().EulerAngle());
}

void Transform3D::Rotate(Unit x, Unit y, Unit z) {
    Rotate(Math::FVector3(x, y, z));
}

void Transform3D::GlobalTranslate(Math::FVector3 translation) {
    SetTranslation(m_translation + translation);
}

void Transform3D::GlobalRotate(Math::FVector3 eulers) {
    SetRotation(m_rotation + eulers);
}

void Transform3D::GlobalRotate(Math::Unit x, Math::Unit y, Math::Unit z) {
    GlobalRotate(Math::FVector3(x, y, z));
}

void Transform3D::GlobalScale(const FVector3& scale) {
    SetScale(m_scale * scale);
}

void Transform3D::GlobalSkew(const FVector3& skew) {
    SetSkew(m_skew * skew);
}

Math::FVector3 Transform3D::TransformDirection(Math::FVector3 direction) const {
    return Quaternion::FromEuler(m_rotation) * direction;
}

void Transform3D::SetTranslation(FVector3 translation) {
    FVector3 delta = translation - m_translation;

    m_translation = translation;
    UpdateComponents();

    if (m_gameObject) {
        for (auto &&child : m_gameObject->m_children) {
            child->m_transform->GlobalTranslate(delta);
        }
    }
}

void Transform3D::SetRotation(Math::FVector3 euler) {
    FVector3 delta = (Quaternion::FromEuler(euler.FixEulerAngles()) * Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

    m_rotation = euler.Limits(360);
    UpdateComponents();

    if (m_gameObject) {
        for (auto &&child : m_gameObject->m_children) {
            child->m_transform->RotateAroundParent(delta);
        }
    }
}

void Transform3D::SetTranslationAndRotation(const Math::FVector3& translation, const Math::FVector3& euler) {
    FVector3 deltaTranslation = translation - m_translation;
    FVector3 deltaRotation = (Quaternion::FromEuler(euler) * Quaternion::FromEuler(m_rotation).Inverse()).EulerAngle();

    m_translation = translation;
    m_rotation = euler.Limits(360);

    UpdateComponents();

    if (m_gameObject) {
        for (auto &&child : m_gameObject->m_children) {
            child->m_transform->GlobalTranslate(deltaTranslation);
            child->m_transform->RotateAroundParent(deltaRotation);
        }
    }
}

void Transform3D::SetScale(Math::FVector3 scale) {
    if (scale.ContainsNaN()) {
        SR_WARN("Transform3D::SetScale() : scale contains NaN! Reset...");
        scale = FVector3::One();
    }

    FVector3 delta = scale / m_scale;

    m_scale = scale;
    UpdateComponents();

    //Matrix4x4&& scaleMatrix = Matrix4x4::FromScale(delta);
    //Matrix4x4&& rotationMatrix = Matrix4x4::FromEulers(m_rotation);
    //delta = (rotationMatrix * scaleMatrix).GetScale();

    if (m_gameObject) {
        for (auto &&child : m_gameObject->m_children) {
            child->m_transform->GlobalSkew(delta);

            //FVector3 childTranslation = (child->m_transform->GetTranslation() - m_translation) * delta + m_translation;
            //child->m_transform->SetTranslation(childTranslation);
        }
    }
}

void Transform3D::SetSkew(Math::FVector3 skew) {
    if (skew.ContainsNaN()) {
        SR_WARN("Transform3D::GlobalSkew() : skew contains NaN! Reset...");
        skew = FVector3::One();
    }

    FVector3 delta = skew / m_skew;

    m_skew = skew;
    UpdateComponents();

    if (m_gameObject) {
        for (auto &&child : m_gameObject->m_children) {
            child->m_transform->GlobalSkew(delta);

            FVector3 childTranslation = (child->m_transform->GetTranslation() - m_translation) * delta + m_translation;
            child->m_transform->SetTranslation(childTranslation);
        }
    }
}

void Transform3D::RotateAround(Math::FVector3 point, Math::FVector3 eulers) {
    const Quaternion&& q = Quaternion::FromEuler(eulers);
    const Quaternion&& rotation = q * Quaternion::FromEuler(m_rotation);

    const FVector3&& worldPos = m_translation - point;
    const FVector3&& rotatedPos = q * worldPos;

    SetTranslationAndRotation(point + rotatedPos, rotation.EulerAngle());
}

void Transform3D::RotateAroundParent(Math::FVector3 eulers) {
    if (m_parent) {
        RotateAround(m_parent->m_translation, eulers);
    }
    else {
        Rotate(eulers); /// TODO: check working
    }
}

Xml::Document Transform3D::Save(SavableFlags flags) const {
    auto doc = Xml::Document::New();
    auto root = doc.Root().AppendChild("Transform3D");

    const auto& translation = GetTranslation();
    const auto& rotation    = GetRotation();
    const auto& scale       = GetScale();
    const auto& skew        = GetSkew();

    if (translation != FVector3::Zero()) {
        root.AppendChild("Translation")
                .NAppendAttributeDef("X", translation.x, (Unit) 0)
                .NAppendAttributeDef("Y", translation.y, (Unit) 0)
                .NAppendAttributeDef("Z", translation.z, (Unit) 0);
    }

    if (rotation != FVector3::Zero()) {
        root.AppendChild("Rotation")
                .NAppendAttributeDef("X", rotation.x, (Unit) 0)
                .NAppendAttributeDef("Y", rotation.y, (Unit) 0)
                .NAppendAttributeDef("Z", rotation.z, (Unit) 0);
    }

    if (scale != FVector3::One()) {
        root.AppendChild("Scale")
                .NAppendAttributeDef("X", scale.x, (Unit) 1)
                .NAppendAttributeDef("Y", scale.y, (Unit) 1)
                .NAppendAttributeDef("Z", scale.z, (Unit) 1);
    }

    if (skew != FVector3::One()) {
        root.AppendChild("Skew")
                .NAppendAttributeDef("X", skew.x, (Unit) 1)
                .NAppendAttributeDef("Y", skew.y, (Unit) 1)
                .NAppendAttributeDef("Z", skew.z, (Unit) 1);
    }

    return doc;
}

Transform3D* Transform3D::Load(const Xml::Node &xml) {
    Transform3D* transform3D = new Transform3D();

    const auto& position = xml.TryGetNode("Translation");
    const auto& rotation = xml.TryGetNode("Rotation");
    const auto& scale    = xml.TryGetNode("Scale");
    const auto& skew     = xml.TryGetNode("Skew");

    transform3D->SetTranslation(position.TryGetAttribute("X").ToFloat(0.f), position.TryGetAttribute("Y").ToFloat(0.f), position.TryGetAttribute("Z").ToFloat(0.f));
    transform3D->SetRotation(rotation.TryGetAttribute("X").ToFloat(0.f), rotation.TryGetAttribute("Y").ToFloat(0.f), rotation.TryGetAttribute("Z").ToFloat(0.f));
    transform3D->SetScale(scale.TryGetAttribute("X").ToFloat(1.f), scale.TryGetAttribute("Y").ToFloat(1.f), scale.TryGetAttribute("Z").ToFloat(1.f));
    transform3D->SetSkew(skew.TryGetAttribute("X").ToFloat(1.f), skew.TryGetAttribute("Y").ToFloat(1.f), skew.TryGetAttribute("Z").ToFloat(1.f));

    return transform3D;
}

void Transform3D::SetTranslation(Math::Unit x, Math::Unit y, Math::Unit z) {
    SetTranslation(FVector3(x, y, z));
}

void Transform3D::SetRotation(Math::Unit yaw, Math::Unit pitch, Math::Unit roll) {
    SetRotation(FVector3(yaw, pitch, roll));
}

void Transform3D::SetScale(Math::Unit x, Math::Unit y, Math::Unit z) {
    SetScale(FVector3(x, y, z));
}

void Transform3D::SetSkew(Math::Unit x, Math::Unit y, Math::Unit z) {
    SetSkew(FVector3(x, y, z));
}

void Transform3D::SetGameObject(GameObject *gameObject) {
    if (m_gameObject) {
        SR_WARN("Transform3D::SetGameObject() : game object already set!");
    }

    m_gameObject = gameObject;

    UpdateComponents();
}




