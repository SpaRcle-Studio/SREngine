//
// Created by Monika on 20.09.2022.
//

#include <Render/DebugRenderer.h>
#include <Utils/DebugDraw.h>
#include <Utils/Types/Time.h>

namespace SR_GRAPH_NS {
    DebugRenderer::DebugRenderer(RenderScene* pRenderScene)
        : Super()
        , m_renderScene(pRenderScene)
    {
        using namespace std::placeholders;

        SR_UTILS_NS::DebugDraw::Instance().SetCallbacks(this, std::bind(&DebugRenderer::DrawLine, this, _1, _2, _3, _4, _5));
        SR_UTILS_NS::DebugDraw::Instance().SwitchCallbacks(this);
    }

    void DebugRenderer::DeInit() {
        SR_LOCK_GUARD
        SR_UTILS_NS::DebugDraw::Instance().RemoveCallbacks(this);
    }

    void DebugRenderer::Prepare() {
        SR_LOCK_GUARD

        auto&& timePoint = SR_HTYPES_NS::Time::Instance().Count();

        for (uint64_t i = 0; i < m_timedObjects.size(); ++i) {
            auto&& timed = m_timedObjects[i];

            if (!timed.pMesh) {
                continue;
            }

            if (timed.endPoint <= timePoint) {
                timed.pMesh->RemoveUsePoint();
                timed.pMesh = nullptr;
                m_emptyIds.emplace_back(i);
            }
        }
    }

    uint64_t DebugRenderer::DrawLine(uint64_t id, const SR_MATH_NS::FVector3 &start, const SR_MATH_NS::FVector3 &end, const SR_MATH_NS::FColor &color, float_t time) {
        SR_LOCK_GUARD

        if (id == SR_ID_INVALID) {
            auto&& pDebugLine = new SR_GTYPES_NS::DebugLine();
            pDebugLine->SetMaterial(SR_GTYPES_NS::Material::Load("Engine/Materials/Debug/line.mat"));
            pDebugLine->AddUsePoint();
            m_renderScene->Register(pDebugLine);
            return AddTimedObject(time, pDebugLine);
        }
        else if (id >= m_timedObjects.size()) {
            SRHalt0();
            return SR_ID_INVALID;
        }
        else {
            return SR_ID_INVALID;
        }
    }

    uint64_t DebugRenderer::AddTimedObject(float_t seconds, SR_GTYPES_NS::Mesh *pMesh) {
        auto&& duration = std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<float_t>(seconds));
        auto&& timePoint = SR_HTYPES_NS::Time::Instance().Count();

        DebugTimedObject timedObject;

        timedObject.pMesh = pMesh;
        timedObject.startPoint = timePoint;
        timedObject.duration = duration.count();
        timedObject.endPoint = timedObject.startPoint + timedObject.duration;

        if (m_emptyIds.empty()) {
            m_timedObjects.emplace_back(timedObject);
            return m_timedObjects.size() - 1;
        }
        else {
            uint64_t id = m_emptyIds.front();
            m_emptyIds.pop_front();
            m_timedObjects[id] = timedObject;
            return id;
        }
    }
}