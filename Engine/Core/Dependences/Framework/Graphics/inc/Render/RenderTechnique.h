//
// Created by Monika on 17.07.2022.
//

#ifndef SRENGINE_RENDERTECHNIQUE_H
#define SRENGINE_RENDERTECHNIQUE_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Math/Vector2.h>

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_GRAPH_NS {
    class BasePass;

    class RenderTechnique : public SR_UTILS_NS::NonCopyable {
        using CameraPtr = Types::Camera*;
    public:
        ~RenderTechnique() override = default;

    public:
        virtual bool Init();
        virtual void DeInit();

        virtual void Render();
        virtual void Update();

        virtual void OnResize(const SR_MATH_NS::IVector2& size);

        SR_NODISCARD CameraPtr GetCamera() const { return m_camera; }

    private:
        std::forward_list<BasePass*> m_passes;
        CameraPtr m_camera = nullptr;

    };
}


#endif //SRENGINE_RENDERTECHNIQUE_H
