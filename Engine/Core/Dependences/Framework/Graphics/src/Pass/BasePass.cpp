//
// Created by Monika on 17.07.2022.
//

#include <Pass/BasePass.h>

namespace SR_GRAPH_NS {
    BasePass::BasePass(std::string name)
        : m_name(std::move(name))
        , m_technique(nullptr)
        , m_context(nullptr)
    { }

    bool BasePass::Init(RenderTechnique* pTechnique) {
        m_technique = pTechnique;
        return true;
    }
}