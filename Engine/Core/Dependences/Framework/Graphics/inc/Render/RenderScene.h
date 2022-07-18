//
// Created by Monika on 16.05.2022.
//

#ifndef SRENGINE_RENDERSCENE_H
#define SRENGINE_RENDERSCENE_H

#include <Utils/Common/NonCopyable.h>
#include <Render/MeshCluster.h>

namespace SR_GRAPH_NS {
    class RenderContext;

    class RenderScene : public SR_UTILS_NS::NonCopyable {
        enum class State {
            Idle, WaitRebuild, Rebuild, Update, Submit
        };
    public:
        ~RenderScene() override = default;

    public:
        void OnRender() {
            // if dirty => rebuild cmd buffer

            // pre render
            // render
            // post render
        }

        void SetDirty() {
            m_dirty = true;
        }

    private:
        // command buffer

        // is dirty
        // добавили новые меши, поменяли шейдры/текстуры, изменили графическую очередь

        // cameras

        // Opaque mesh cluster

        // Transparent mesh cluster

        // Skybox

        // lights

        MeshCluster       m_opaque      = { };
        MeshCluster       m_transparent = { };

        Types::Skybox*    m_skybox      = nullptr;
        RenderContext*    m_context     = nullptr;

        std::atomic<bool> m_dirty       = false;

    };
}

#endif //SRENGINE_RENDERSCENE_H
