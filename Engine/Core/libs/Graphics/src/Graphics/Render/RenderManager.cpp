//
// Created by Monika on 07.04.2022.
//

#include <Graphics/Render/RenderManager.h>

#include <Graphics/Render/Implementations/VulkanRender.h>
#include <Graphics/Render/Implementations/OpenGLRender.h>
#include <Graphics/Render/Render.h>

SR_GRAPH_NS::Render* SR_GRAPH_NS::RenderManager::Allocate(const std::string& name) {
    //Render* render = nullptr;

    //const auto&& pipeLine = Environment::Get()->GetType();

    //switch (pipeLine) {
    //    case PipelineType::OpenGL:
    //        //render = static_cast<Render *>(new Impl::OpenGLRender(name));
    //        break;
    //    case PipelineType::Vulkan:
    //        //render = static_cast<Render *>(new Impl::VulkanRender(name));
    //        break;
    //    default:
    //        break;
    //}

    //if (!render) {
    //    SRAssert(false);
    //    return nullptr;
    //}

    //m_renders.insert(std::make_pair(name, render));

    return nullptr;
}

SR_GRAPH_NS::Render* SR_GRAPH_NS::RenderManager::Get(const std::string &name) {
    SRAssert(m_renders.count(name) == 1);
    return m_renders.at(name);
}