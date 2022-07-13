//
// Created by Monika on 16.05.2022.
//

#ifndef SRENGINE_RENDERSCENE_H
#define SRENGINE_RENDERSCENE_H

#include <Utils/Common/NonCopyable.h>

#include <Render/RenderContext.h>

namespace SR_GRAPH_NS {
    class RenderScene : public SR_UTILS_NS::NonCopyable {
    public:
        ~RenderScene() override = default;

    public:
        void OnRender() {
            // if dirty => rebuild cmd buffer

            // pre render
            // render
            // post render
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

        // environment (pipe line)
        // может использоваться несколькими RenderScene'ами

    };
}

#endif //SRENGINE_RENDERSCENE_H
