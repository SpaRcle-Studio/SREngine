//
// Created by Monika on 22.05.2023.
//

#ifndef SRENGINE_CHUNKRENDERER_H
#define SRENGINE_CHUNKRENDERER_H

#include <Utils/Common/NonCopyable.h>

namespace SR_GRAPH_NS {
    class RenderContext;
    class RenderScene;
    class DebugRenderer;

    class ChunkRenderer : public SR_UTILS_NS::NonCopyable {
        using Super = SR_UTILS_NS::NonCopyable;
    public:
        explicit ChunkRenderer(DebugRenderer* pDebugRenderer);
        ~ChunkRenderer() override = default;

    public:


    private:
        DebugRenderer* m_debugRenderer = nullptr;

    };
}

#endif //SRENGINE_CHUNKRENDERER_H
