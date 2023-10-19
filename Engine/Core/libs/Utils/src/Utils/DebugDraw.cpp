//
// Created by Monika on 20.09.2022.
//

#include <Utils/DebugDraw.h>
#include <Utils/Debug.h>

#include <Utils/Types/RawMesh.h>

#include <utility>

namespace SR_UTILS_NS {
    /// ---------------------------------------------- CALLBACKS INITIALIZATIONS ---------------------------------------

    void DebugDraw::SetCallbacks(void* pUserIdentifier, Callbacks callbacks)
    {
        SR_LOCK_GUARD

        m_callbacks[pUserIdentifier] = std::move(callbacks);
    }

    void DebugDraw::RemoveCallbacks(void* pUserIdentifier) {
        SR_LOCK_GUARD

        if (auto&& pIt = m_callbacks.find(pUserIdentifier); pIt != m_callbacks.end()) {
            if (&pIt->second == m_currentCallbacks) {
                m_currentCallbacks = nullptr;
                m_currentSwitcher = nullptr;
            }
            m_callbacks.erase(pIt);
        }
        else {
            SRHalt("Callbacks not found!");
        }
    }

    void DebugDraw::SwitchCallbacks(void* pUserIdentifier) {
        SR_LOCK_GUARD

        if (m_currentSwitcher == pUserIdentifier) {
            return;
        }

        if (auto&& pIt = m_callbacks.find(pUserIdentifier); pIt != m_callbacks.end()) {
            m_currentCallbacks = &pIt->second;
            m_currentSwitcher = pUserIdentifier;
        }
        else {
            SRHalt("Callbacks not found!");
        }
    }

    void DebugDraw::Remove(uint64_t id) {
        SR_LOCK_GUARD

        if (m_currentCallbacks && m_currentCallbacks->removeCallback) {
            m_currentCallbacks->removeCallback(id);
        }
    }

    /// ---------------------------------------------------- LINE DRAWING ----------------------------------------------

    uint64_t DebugDraw::DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time) {
        SR_LOCK_GUARD

        if (m_currentCallbacks && m_currentCallbacks->drawLineCallback) {
            return m_currentCallbacks->drawLineCallback(id, start, end, color, time);
        }

        return SR_ID_INVALID;
    }

    uint64_t DebugDraw::DrawLine(uint64_t id, const SR_MATH_NS::FVector3 &start, const SR_MATH_NS::FVector3 &end, const SR_MATH_NS::FColor &color) {
        return DrawLine(id, start, end, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time) {
        return DrawLine(SR_ID_INVALID, start, end, color, time);
    }

    uint64_t DebugDraw::DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color) {
        return DrawLine(SR_ID_INVALID, start, end, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, float_t time) {
        return DrawLine(SR_ID_INVALID, start, end, time);
    }

    uint64_t DebugDraw::DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end) {
        return DrawLine(SR_ID_INVALID, start, end, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end) {
        return DrawLine(id, start, end, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, float_t time) {
        return DrawLine(id, start, end, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawLine(uint64_t id) {
        return DrawLine(id, DEFAULT_POSITION, DEFAULT_POSITION, DEFAULT_COLOR, 0.f);
    }

    uint64_t DebugDraw::DrawLine() {
        return DrawLine(SR_ID_INVALID, DEFAULT_POSITION, DEFAULT_POSITION, DEFAULT_COLOR, DEFAULT_DURATION);
    } /// не расстраивай гориллу, вызови DrawLine(DEFAULT_POSITION, DEFAULT_POSITION, DEFAULT_COLOR, DEFAULT_DURATION)

    /// ---------------------------------------------------- CUBE DRAWING ----------------------------------------------

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time) {
        SR_LOCK_GUARD

        if (m_currentCallbacks && m_currentCallbacks->drawCubeCallback) {
            return m_currentCallbacks->drawCubeCallback(id, pos, rot, scale, color, time);
        }

        return SR_ID_INVALID;
    }

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawCube(id, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawCube(id, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawCube(id, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3 &pos) {
        return DrawCube(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawCube(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawCube(SR_ID_INVALID, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawCube(SR_ID_INVALID, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawCube(SR_ID_INVALID, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3 &pos) {
        return DrawCube(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color) {
        return DrawCube(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(uint64_t id, const SR_MATH_NS::FVector3 &pos, float_t time) {
        return DrawCube(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawCube(SR_ID_INVALID, pos, rot, scale, color, time);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time) {
        return DrawCube(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color) {
        return DrawCube(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCube(const SR_MATH_NS::FVector3& pos, float_t time) {
        return DrawCube(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawCube(uint64_t id) {
        return DrawCube(id, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, 0.f);
    }

    uint64_t DebugDraw::DrawCube() {
        return DrawCube(SR_ID_INVALID, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    /// ---------------------------------------------------- PLANE DRAWING ----------------------------------------------

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time) {
        SR_LOCK_GUARD

        if (m_currentCallbacks && m_currentCallbacks->drawPlaneCallback) {
            return m_currentCallbacks->drawPlaneCallback(id, pos, rot, scale, color, time);
        }

        return SR_ID_INVALID;
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawPlane(id, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawPlane(id, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawPlane(id, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3 &pos) {
        return DrawPlane(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawPlane(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawPlane(SR_ID_INVALID, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawPlane(SR_ID_INVALID, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawPlane(SR_ID_INVALID, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3 &pos) {
        return DrawPlane(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color) {
        return DrawPlane(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id, const SR_MATH_NS::FVector3 &pos, float_t time) {
        return DrawPlane(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawPlane(SR_ID_INVALID, pos, rot, scale, color, time);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time) {
        return DrawPlane(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color) {
        return DrawPlane(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawPlane(const SR_MATH_NS::FVector3& pos, float_t time) {
        return DrawPlane(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawPlane(uint64_t id) {
        return DrawPlane(id, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, 0.f);
    }

    uint64_t DebugDraw::DrawPlane() {
        return DrawPlane(SR_ID_INVALID, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    /// ---------------------------------------------------- SPHERE DRAWING ----------------------------------------------

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time) {
        SR_LOCK_GUARD

        if (m_currentCallbacks && m_currentCallbacks->drawSphereCallback) {
            return m_currentCallbacks->drawSphereCallback(id, pos, rot, scale, color, time);
        }

        return SR_ID_INVALID;
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawSphere(id, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawSphere(id, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawSphere(id, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3 &pos) {
        return DrawSphere(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawSphere(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawSphere(SR_ID_INVALID, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawSphere(SR_ID_INVALID, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawSphere(SR_ID_INVALID, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3 &pos) {
        return DrawSphere(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color) {
        return DrawSphere(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id, const SR_MATH_NS::FVector3 &pos, float_t time) {
        return DrawSphere(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawSphere(SR_ID_INVALID, pos, rot, scale, color, time);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time) {
        return DrawSphere(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color) {
        return DrawSphere(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawSphere(const SR_MATH_NS::FVector3& pos, float_t time) {
        return DrawSphere(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawSphere(uint64_t id) {
        return DrawSphere(id, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, 0.f);
    }

    uint64_t DebugDraw::DrawSphere() {
        return DrawSphere(SR_ID_INVALID, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    /// ---------------------------------------------------- CAPSULE DRAWING ----------------------------------------------

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time) {
        SR_LOCK_GUARD

        if (m_currentCallbacks && m_currentCallbacks->drawCapsuleCallback) {
            return m_currentCallbacks->drawCapsuleCallback(id, pos, rot, scale, color, time);
        }

        return SR_ID_INVALID;
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawCapsule(id, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawCapsule(id, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawCapsule(id, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3 &pos) {
        return DrawCapsule(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawCapsule(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawCapsule(SR_ID_INVALID, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawCapsule(SR_ID_INVALID, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawCapsule(SR_ID_INVALID, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3 &pos) {
        return DrawCapsule(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color) {
        return DrawCapsule(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3 &pos, float_t time) {
        return DrawCapsule(id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawCapsule(SR_ID_INVALID, pos, rot, scale, color, time);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time) {
        return DrawCapsule(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color) {
        return DrawCapsule(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawCapsule(const SR_MATH_NS::FVector3& pos, float_t time) {
        return DrawCapsule(SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawCapsule(uint64_t id) {
        return DrawCapsule(id, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, 0.f);
    }

    uint64_t DebugDraw::DrawCapsule() {
        return DrawCapsule(SR_ID_INVALID, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    /// ---------------------------------------------------- CAPSULE DRAWING ----------------------------------------------

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time) {
        SR_LOCK_GUARD

        if (!pRawMesh) {
            return SR_ID_INVALID;
        }

        if (m_currentCallbacks && m_currentCallbacks->drawMeshCallback) {
            return m_currentCallbacks->drawMeshCallback(pRawMesh, id, pos, rot, scale, color, time);
        }

        return SR_ID_INVALID;
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawMesh(pRawMesh, id, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawMesh(pRawMesh, id, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawMesh(pRawMesh, id, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3 &pos) {
        return DrawMesh(pRawMesh, id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawMesh(pRawMesh, id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, rot, scale, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, rot, scale, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, rot, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3 &pos) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::FColor &color) {
        return DrawMesh(pRawMesh, id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3 &pos, float_t time) {
        return DrawMesh(pRawMesh, id, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3 &pos, const SR_MATH_NS::Quaternion &rot, const SR_MATH_NS::FVector3 &scale, const SR_MATH_NS::FColor &color, float_t time) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, rot, scale, color, time);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, time);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, color, DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, float_t time) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, pos, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, time);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id) {
        return DrawMesh(pRawMesh, id, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, 0.f);
    }

    uint64_t DebugDraw::DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh) {
        return DrawMesh(pRawMesh, SR_ID_INVALID, DEFAULT_POSITION, DEFAULT_QUATERNION, DEFAULT_SCALE, DEFAULT_COLOR, DEFAULT_DURATION);
    }

    /// ---------------------------------------------------- MESH DRAWING ----------------------------------------------
}