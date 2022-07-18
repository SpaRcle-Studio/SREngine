//
// Created by Monika on 17.07.2022.
//

#include <Render/RenderTechnique.h>

namespace SR_GRAPH_NS {
    void RenderTechnique::Render() {
        for (auto&& pass : m_passes) {
            pass->PreRender();
        }

        for (auto&& pass : m_passes) {
            pass->Render();
        }

        for (auto&& pass : m_passes) {
            pass->PostRender();
        }
    }

    void RenderTechnique::Update() {
        for (auto&& pass : m_passes) {
            pass->Update();
        }
    }

    void RenderTechnique::OnResize(const Helper::Math::IVector2 &size) {

    }

    bool RenderTechnique::Init() {
        bool hasErrors = false;

        for (auto&& pass : m_passes) {
            hasErrors = pass->Init(this);
        }

        return !hasErrors;
    }

    void RenderTechnique::DeInit() {
        for (auto&& pass : m_passes) {
            pass->DeInit();
        }
    }
}
