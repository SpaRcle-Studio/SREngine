//
// Created by Monika on 07.04.2022.
//

#include <Render/RenderManager.h>

#include <Render/Implementations/VulkanRender.h>
#include <Render/Implementations/OpenGLRender.h>
#include <Render/Render.h>

SR_GRAPH_NS::Render* SR_GRAPH_NS::RenderManager::Allocate(const std::string& name) {
    Render* render = nullptr;

    const auto&& pipeLine = Environment::Get()->GetPipeLine();

    switch (pipeLine) {
        case PipeLine::OpenGL:
            render = static_cast<Render *>(new Impl::OpenGLRender(name));
            break;
        case PipeLine::Vulkan:
            render = static_cast<Render *>(new Impl::VulkanRender(name));
            break;
        case PipeLine::DirectX9:
            break;
        case PipeLine::DirectX10:
            break;
        case PipeLine::DirectX11:
            break;
        case PipeLine::DirectX12:
            break;
        case PipeLine::Unknown:
        default:
            break;
    }

    if (!render) {
        SRAssert(false);
        return nullptr;
    }

    m_renders.insert(std::make_pair(name, render));

    return render;
}

SR_GRAPH_NS::Render* SR_GRAPH_NS::RenderManager::Get(const std::string &name) {
    SRAssert(m_renders.count(name) == 1);
    return m_renders.at(name);
}