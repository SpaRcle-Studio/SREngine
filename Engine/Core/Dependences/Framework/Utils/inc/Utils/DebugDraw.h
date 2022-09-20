//
// Created by Monika on 20.09.2022.
//

#ifndef SRENGINE_DEBUGDRAW_H
#define SRENGINE_DEBUGDRAW_H

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Function.h>

namespace SR_UTILS_NS {
    /**
     * \arg Time:
     *      SR_FLOAT_MAX - infinity life;
     *      0.f - remove;
     *
     * \arg Id: maybe SR_ID_INVALID
     */
    class SR_DLL_EXPORT DebugDraw : public Singleton<DebugDraw> {
        friend class Singleton<DebugDraw>;
    public:
        using DrawLineCallback = SR_HTYPES_NS::Function<uint64_t(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time)>;

        struct Callbacks {
            DrawLineCallback drawLineCallback;
        };

        static constexpr float_t DEFAULT_DURATION = 10.f;

    public:
        void SetCallbacks(void* pUserIdentifier, const DrawLineCallback& lineCallback);
        void RemoveCallbacks(void* pUserIdentifier);
        void SwitchCallbacks(void* pUserIdentifier);

    public:
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color);
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, float_t time);
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, float_t time);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end);
        void DrawLine(uint64_t id);

    private:
        void* m_currentSwitcher = nullptr;
        Callbacks* m_currentCallbacks = nullptr;
        std::map<void*, Callbacks> m_callbacks;

    };
}

#endif //SRENGINE_DEBUGDRAW_H
