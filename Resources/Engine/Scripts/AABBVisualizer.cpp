//
// Created by Monika on 28.09.2025.
//

#include <Utils/DebugDraw.h>
#include <Utils/ECS/Component.h>
#include <Utils/ECS/SceneObject.h>

#include <Graphics/Types/Camera.h>

#include <Scripting/Cpp/CppBehaviour.h>

namespace SpaRcle::Scripts::SREngine {
    class AABBVisualizer : public SpaRcle::Scripting::CppBehaviour {
        SR_CLASS()
    public:
        SR_NODISCARD bool ExecuteInEditMode() const noexcept override { return true; }

    public:
        void OnDisable() override {
            RemoveDebug();
        }

        void OnDestroy() override {
            RemoveDebug();
        }

        void RemoveDebug() {
            if (debugId != SR_ID_INVALID) {
                SR_UTILS_NS::DebugDraw::Instance().Remove(debugId);
                debugId = SR_ID_INVALID;
            }

            for (auto& id : frustumIds) {
                if (id != SR_ID_INVALID) {
                    SR_UTILS_NS::DebugDraw::Instance().Remove(id);
                    id = SR_ID_INVALID;
                }
            }
        }

        void Update(float_t dt) override {
            if (!transform || !sceneObject || pause) {
                return;
            }

            if (auto&& pCamera = sceneObject->GetComponent<SR_GTYPES_NS::Camera>()) {
                const SR_GRAPH_NS::Frustum& frustum = pCamera->GetFrustum();

                auto& planes = frustum.planes;

                /*SR_MATH_NS::FVector3 ntl = IntersectFrustumPlanes(planes[4], planes[3], planes[0]); // Near + Top + Left
                SR_MATH_NS::FVector3 ntr = IntersectFrustumPlanes(planes[4], planes[3], planes[1]); // Near + Top + Right
                SR_MATH_NS::FVector3 nbl = IntersectFrustumPlanes(planes[4], planes[2], planes[0]); // Near + Bottom + Left
                SR_MATH_NS::FVector3 nbr = IntersectFrustumPlanes(planes[4], planes[2], planes[1]); // Near + Bottom + Right

                SR_MATH_NS::FVector3 ftl = IntersectFrustumPlanes(planes[5], planes[3], planes[0]); // Far + Top + Left
                SR_MATH_NS::FVector3 ftr = IntersectFrustumPlanes(planes[5], planes[3], planes[1]); // Far + Top + Right
                SR_MATH_NS::FVector3 fbl = IntersectFrustumPlanes(planes[5], planes[2], planes[0]); // Far + Bottom + Left
                SR_MATH_NS::FVector3 fbr = IntersectFrustumPlanes(planes[5], planes[2], planes[1]); // Far + Bottom + Right*/

                SR_MATH_NS::FVector3 ntl = IntersectFrustumPlanes(frustum.Near(), frustum.Top(), frustum.Left()); // Near + Top + Left
                SR_MATH_NS::FVector3 ntr = IntersectFrustumPlanes(frustum.Near(), frustum.Top(), frustum.Right()); // Near + Top + Right
                SR_MATH_NS::FVector3 nbl = IntersectFrustumPlanes(frustum.Near(), frustum.Bottom(), frustum.Left()); // Near + Bottom + Left
                SR_MATH_NS::FVector3 nbr = IntersectFrustumPlanes(frustum.Near(), frustum.Bottom(), frustum.Right()); // Near + Bottom + Right

                SR_MATH_NS::FVector3 ftl = IntersectFrustumPlanes(frustum.Far(), frustum.Top(), frustum.Left()); // Far + Top + Left
                SR_MATH_NS::FVector3 ftr = IntersectFrustumPlanes(frustum.Far(), frustum.Top(), frustum.Right()); // Far + Top + Right
                SR_MATH_NS::FVector3 fbl = IntersectFrustumPlanes(frustum.Far(), frustum.Bottom(), frustum.Left()); // Far + Bottom + Left
                SR_MATH_NS::FVector3 fbr = IntersectFrustumPlanes(frustum.Far(), frustum.Bottom(), frustum.Right()); // Far + Bottom + Right

                auto& dbg = SR_UTILS_NS::DebugDraw::Instance();
                SR_MATH_NS::FColor color = SR_MATH_NS::FColor::Red();

                // ближняя плоскость
                frustumIds[0] = dbg.DrawLine(frustumIds[0], ntl, ntr, color);
                frustumIds[1] = dbg.DrawLine(frustumIds[1], ntr, nbr, color);
                frustumIds[2] = dbg.DrawLine(frustumIds[2], nbr, nbl, color);
                frustumIds[3] = dbg.DrawLine(frustumIds[3], nbl, ntl, color);

                // дальняя плоскость
                frustumIds[4] = dbg.DrawLine(frustumIds[4], ftl, ftr, color);
                frustumIds[5] = dbg.DrawLine(frustumIds[5], ftr, fbr, color);
                frustumIds[6] = dbg.DrawLine(frustumIds[6], fbr, fbl, color);
                frustumIds[7] = dbg.DrawLine(frustumIds[7], fbl, ftl, color);

                // боковые рёбра
                frustumIds[8] = dbg.DrawLine(frustumIds[8], ntl, ftl, color);
                frustumIds[9] = dbg.DrawLine(frustumIds[9], ntr, ftr, color);
                frustumIds[10] = dbg.DrawLine(frustumIds[10], nbl, fbl, color);
                frustumIds[11] = dbg.DrawLine(frustumIds[11], nbr, fbr, color);
            }
            else {
                auto&& aabb = transform->GetAABB();
                const SR_MATH_NS::FVector3 position = aabb.GetCenter();
                const SR_MATH_NS::FVector3 size = aabb.GetExtends();
                debugId = SR_UTILS_NS::DebugDraw::Instance().DrawCube(debugId, position, SR_MATH_NS::Quaternion::Identity(), size, SR_MATH_NS::FColor::Green());
            }
        }

    private:
        int64_t debugId = SR_ID_INVALID;
        std::array<int64_t, 12> frustumIds = { SR_ID_INVALID, SR_ID_INVALID, SR_ID_INVALID, SR_ID_INVALID,
                                           SR_ID_INVALID, SR_ID_INVALID, SR_ID_INVALID, SR_ID_INVALID,
                                           SR_ID_INVALID, SR_ID_INVALID, SR_ID_INVALID, SR_ID_INVALID  };

        /// @property
        bool pause = false;


    };
}

#include <Codegen/AABBVisualizer.generated.hpp>
