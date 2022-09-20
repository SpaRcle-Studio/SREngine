//
// Created by Monika on 20.09.2022.
//

#include <Utils/DebugDraw.h>
#include <Utils/Debug.h>

namespace SR_UTILS_NS {
    /// ---------------------------------------------- CALLBACKS INITIALIZATIONS ---------------------------------------

    void DebugDraw::SetCallbacks(void* pUserIdentifier, const DrawLineCallback& lineCallback) {
        SR_LOCK_GUARD

        auto&& callbacks = m_callbacks[pUserIdentifier];

        callbacks.drawLineCallback = lineCallback;
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
        return DrawLine(SR_ID_INVALID, start, end, SR_MATH_NS::FColor(1.f), DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end) {
        return DrawLine(id, start, end, SR_MATH_NS::FColor(1.f), DEFAULT_DURATION);
    }

    uint64_t DebugDraw::DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, float_t time) {
        return DrawLine(id, start, end, SR_MATH_NS::FColor(1.f), time);
    }

    void DebugDraw::DrawLine(uint64_t id) {
        DrawLine(id, SR_MATH_NS::FVector3(0.f), SR_MATH_NS::FVector3(0.f), SR_MATH_NS::FColor(1.f), 0.f);
    }

    /// ---------------------------------------------------- LINE DRAWING ----------------------------------------------
}