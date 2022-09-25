//
// Created by Monika on 20.09.2022.
//

#ifndef SRENGINE_DEBUGRENDERER_H
#define SRENGINE_DEBUGRENDERER_H

#include <Utils/Common/NonCopyable.h>

namespace SR_GRAPH_NS {
    class RenderContext;
    class RenderScene;

    class DebugRenderer : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        explicit DebugRenderer(RenderScene* pRenderScene);
        ~DebugRenderer() override;

        void DeInit();
        void Prepare();
        void Clear();

    private:
        uint64_t DrawLine(uint64_t id, const SR_MATH_NS::FVector3& start, const SR_MATH_NS::FVector3& end, const SR_MATH_NS::FColor& color, float_t time);
        uint64_t DrawCube(uint64_t id, const SR_MATH_NS::FVector3& pos, const SR_MATH_NS::Quaternion& rot, const SR_MATH_NS::FVector3& scale, const SR_MATH_NS::FColor& color, float_t time);

    private:
        uint64_t AddTimedObject(float_t seconds, SR_GTYPES_NS::Mesh* pMesh);
        void UpdateTimedObject(uint64_t id, float_t seconds);

    private:
        mutable std::recursive_mutex m_mutex;

        RenderScene* m_renderScene = nullptr;

        struct DebugTimedObject {
            uint64_t startPoint;
            uint64_t endPoint;
            uint64_t duration;
            SR_GTYPES_NS::Mesh* pMesh;
            bool registered;
        };

        std::vector<DebugTimedObject> m_timedObjects;
        std::list<uint64_t> m_emptyIds;
    };
}

#endif //SRENGINE_DEBUGRENDERER_H
