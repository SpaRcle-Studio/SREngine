
//
// Created by Monika on 20.09.2022.
//

#ifndef SRENGINE_DEBUGDRAW_H
#define SRENGINE_DEBUGDRAW_H

#include <Utils/Math/Vector3.h>
#include <Utils/Math/Vector4.h>
#include <Utils/Common/Singleton.h>
#include <Utils/Types/Function.h>

namespace SR_HTYPES_NS {
    class RawMesh;
}

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
        using RemoveCallback = SR_HTYPES_NS::Function<void(uint64_t id)>;
        using DrawLineCallback = SR_HTYPES_NS::Function<uint64_t(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time)>;
        using DrawCubeCallback = SR_HTYPES_NS::Function<uint64_t(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time)>;
        using DrawPlaneCallback = DrawCubeCallback;
        using DrawSphereCallback = DrawCubeCallback;
        using DrawCapsuleCallback = DrawCubeCallback;
        using DrawMeshCallback = SR_HTYPES_NS::Function<uint64_t(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time)>;

        struct Callbacks {
            RemoveCallback removeCallback;
            DrawLineCallback drawLineCallback;
            DrawCubeCallback drawCubeCallback;
            DrawPlaneCallback drawPlaneCallback;
            DrawSphereCallback drawSphereCallback;
            DrawCapsuleCallback drawCapsuleCallback;
            DrawMeshCallback drawMeshCallback;
        };

        static constexpr float_t DEFAULT_DURATION = 10.f;
        static constexpr SR_MATH_NS::FColor DEFAULT_COLOR = SR_MATH_NS::FColor(255, 255, 255, 255);
        static constexpr SR_MATH_NS::FVector3 DEFAULT_POSITION = SR_MATH_NS::FVector3::Zero();
        static constexpr SR_MATH_NS::FVector3 DEFAULT_SCALE = SR_MATH_NS::FVector3::One();
        static constexpr SR_MATH_NS::Quaternion DEFAULT_QUATERNION = SR_MATH_NS::Quaternion::Identity();

    public:
        void SetCallbacks(void* pUserIdentifier, Callbacks callbacks);

        void* GetUserIdentifier() const { return m_currentSwitcher; }

        void RemoveCallbacks(void* pUserIdentifier);
        void SwitchCallbacks(void* pUserIdentifier);
        void Remove(uint64_t id);

    public:
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id, const SR_MATH_NS::FVector3& pos);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, const SR_MATH_NS::FVector3& pos);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh, uint64_t id);
        uint64_t DrawMesh(SR_HTYPES_NS::RawMesh* pRawMesh);

        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color);
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, float_t time);
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, float_t time);
        uint64_t DrawLine(const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end);
        uint64_t DrawLine(uint64_t id);
        uint64_t DrawLine();

        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawCube(const SR_MATH_NS::FVector3& pos);
        uint64_t DrawCube(uint64_t id);
        uint64_t DrawCube();

        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawPlane(uint64_t id, const SR_MATH_NS::FVector3& pos);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawPlane(const SR_MATH_NS::FVector3& pos);
        uint64_t DrawPlane(uint64_t id);
        uint64_t DrawPlane();

        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawSphere(uint64_t id, const SR_MATH_NS::FVector3& pos);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawSphere(const SR_MATH_NS::FVector3& pos);
        uint64_t DrawSphere(uint64_t id);
        uint64_t DrawSphere();

        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawCapsule(uint64_t id, const SR_MATH_NS::FVector3& pos);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::FColor& color);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos, float_t time);
        uint64_t DrawCapsule(const SR_MATH_NS::FVector3& pos);
        uint64_t DrawCapsule(uint64_t id);
        uint64_t DrawCapsule();

    private:
        void* m_currentSwitcher = nullptr;
        Callbacks* m_currentCallbacks = nullptr;
        std::map<void*, Callbacks> m_callbacks;

    };
}

#endif //SRENGINE_DEBUGDRAW_H
