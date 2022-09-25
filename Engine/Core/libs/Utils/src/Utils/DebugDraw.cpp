//
// Created by Monika on 20.09.2022.
//

#include <Utils/DebugDraw.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    /// ---------------------------------------------- CALLBACKS INITIALIZATIONS ---------------------------------------

    void DebugDraw::SetCallbacks(void* pUserIdentifier, const DrawLineCallback& lineCallback, const DrawCubeCallback& cubeCallback) {
        SR_LOCK_GUARD

        auto&& callbacks = m_callbacks[pUserIdentifier];

        callbacks.drawLineCallback = lineCallback;
        callbacks.drawCubeCallback = cubeCallback;
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
    }

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

    /// ---------------------------------------------------- CUBE DRAWING ----------------------------------------------
}