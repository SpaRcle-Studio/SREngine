//
// Created by Monika on 27.04.2025.
//

#include <Scripting/Cpp/CppBehaviour.h>

#include <Codegen/CppBehaviour.generated.hpp>

namespace SR_SCRIPTING_NS {
    CppBehaviour::CppBehaviour()
        : Super(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
    { }

    CppBehaviour::~CppBehaviour() = default;

    void CppBehaviour::OnMatrixDirty() { }
    void CppBehaviour::OnPriorityChanged() { }
    void CppBehaviour::OnTransformSet() { }

    void CppBehaviour::OnAttached() { }
    void CppBehaviour::OnDetached() { }
    void CppBehaviour::OnDestroy() { }

    void CppBehaviour::OnEnable() { }
    void CppBehaviour::OnDisable() { }

    void CppBehaviour::Awake() { }
    void CppBehaviour::Start() { }
    void CppBehaviour::Update(float_t dt) { }
    void CppBehaviour::FixedUpdate() { }
    void CppBehaviour::LateUpdate() { }

    void CppBehaviour::OnBeforeLayerChanged() { }
    void CppBehaviour::OnLayerChanged() { }

    void CppBehaviour::OnCollisionEnter(const SR_UTILS_NS::CollisionData& data) { }
    void CppBehaviour::OnCollisionStay(const SR_UTILS_NS::CollisionData& data) { }
    void CppBehaviour::OnCollisionExit(const SR_UTILS_NS::CollisionData& data) { }

    void CppBehaviour::OnTriggerEnter(const SR_UTILS_NS::CollisionData& data) { }
    void CppBehaviour::OnTriggerStay(const SR_UTILS_NS::CollisionData& data) { }
    void CppBehaviour::OnTriggerExit(const SR_UTILS_NS::CollisionData& data) { }
}