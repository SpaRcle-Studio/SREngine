//
// Created by Monika on 14.07.2022.
//

#ifndef SRENGINE_BASEPASS_H
#define SRENGINE_BASEPASS_H

#include <Utils/Common/NonCopyable.h>
#include <Utils/Math/Vector2.h>

namespace SR_GTYPES_NS {
    class Camera;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderTechnique;

    class BasePass : public SR_UTILS_NS::NonCopyable {
        using CameraPtr = Types::Camera*;
        using Context = RenderScene*;
    public:
        explicit BasePass(std::string name);
        ~BasePass() override = default;

    public:
        virtual bool Init(RenderTechnique* pTechnique);
        virtual void DeInit() { }

        virtual void PreRender() { }
        virtual void Render() { }
        virtual void PostRender() { }

        virtual void Update() { }

        virtual void OnResize(const SR_MATH_NS::IVector2& size) { }

    private:
        const std::string m_name;
        RenderTechnique* m_technique;
        Context m_context;

    };
}

#endif //SRENGINE_BASEPASS_H
