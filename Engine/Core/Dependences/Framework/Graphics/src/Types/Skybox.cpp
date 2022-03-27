//
// Created by Nikita on 20.11.2020.
//

#include "Types/Skybox.h"
#include <ResourceManager/ResourceManager.h>
#include <Utils/StringUtils.h>
#include <stbi/stb_image.h>
#include <Debug.h>
#include <Render/Render.h>
#include <Types/Vertices.h>
#include <Window/Window.h>
#include <Loaders/ObjLoader.h>
#include <Utils/Features.h>
#include <Utils/Vertices.hpp>

Framework::Graphics::Types::Skybox::Skybox()
    : m_env(Environment::Get())
{ }

Framework::Graphics::Types::Skybox *Framework::Graphics::Types::Skybox::Load(const std::string& name) {
    std::string skyboxName = name;

    std::string ext = StringUtils::GetExtensionFromFilePath(skyboxName);
    skyboxName.resize(skyboxName.size() - ext.size() - 1);

    const auto path = Helper::ResourceManager::Instance().GetResPath().Concat("Skyboxes").Concat(skyboxName);

    SR_LOG("Skybox::Load() : loading \""+skyboxName+"\" skybox...");

    std::array<uint8_t*, 6> sides = { };
    static const std::string files[6]{ "right", "left", "top", "bottom", "front", "back" };

    int W, H, C;

    for (uint8_t i = 0; i < 6; ++i) {
        const auto file = path.Concat(files[i]).ConcatExt(ext);

        int w = 0, h = 0, comp = 0;
        uint8_t* data = stbi_load(file.CStr(), &w, &h, &comp, STBI_rgb_alpha);

        if (!i) {
            W = w;
            H = h;
            C = comp;
        }
        else if (h != H || w != W || C != comp) {
            SR_WARN("Skybox::Load() : \"" + name + "\" skybox has different sizes!");
        }

        if (!data) {
            SR_ERROR("Skybox::Load() : failed load \"" + skyboxName + "\" skybox!\n\tPath: " + file.ToString());
            return nullptr;
        }
        sides[i] = data;
    }

    auto* skybox = new Skybox();

    skybox->m_name   = skyboxName;
    skybox->m_width  = W;
    skybox->m_height = H;
    skybox->m_data   = sides;

    return skybox;
}

bool Framework::Graphics::Types::Skybox::Calculate() {
    if (m_isCalculated) {
        SR_ERROR("Skybox::Calculate() : skybox already calculated!");
        return false;
    }

    const bool cpuUsage = Helper::Features::Instance().Enabled("SkyboxCPUUsage", false);
    if (m_cubeMap = m_env->CalculateCubeMap(m_width, m_height, m_data, cpuUsage); m_cubeMap < 0) {
        SR_ERROR("Skybox::Calculate() : failed to calculate cube map!");
        m_hasErrors = true;
        return false;
    }

    const auto path = Helper::ResourceManager::Instance().GetResPath().Concat("/Models/Engine/skybox.obj");
    auto&& indexedVertices = Vertices::CastVertices<Vertices::SkyboxVertex>(SKYBOX_INDEXED_VERTICES);

    if (m_env->GetPipeLine() == PipeLine::Vulkan) {
        auto&& indices = SKYBOX_INDICES;

        if (m_VBO = m_env->CalculateVBO(indexedVertices.data(), Vertices::Type::SkyboxVertex, indexedVertices.size()); m_VBO == SR_ID_INVALID) {
            SR_ERROR("Skybox::Calculate() : failed to calculate VBO!");
            m_hasErrors = true;
            return false;
        }

        if (m_IBO = m_env->CalculateIBO((void *)indices.data(), sizeof(uint32_t), indices.size(), SR_ID_INVALID); m_IBO == SR_ID_INVALID) {
            SR_ERROR("Skybox::Calculate() : failed to calculate IBO!");
            m_hasErrors = true;
            return false;
        }
    }
    else {
        auto&& vertices = IndexedVerticesToNonIndexed(indexedVertices, SKYBOX_INDICES);

        if (m_VBO = m_env->CalculateVBO(vertices.data(), Vertices::Type::SkyboxVertex, vertices.size()); m_VBO == SR_ID_INVALID) {
            SR_ERROR("Skybox::Calculate() : failed to calculate VBO!");
            m_hasErrors = true;
            return false;
        }
    }

    m_isCalculated = true;
    return true;
}

bool Framework::Graphics::Types::Skybox::Free() {
    SR_LOG("Skybox::Free() : free skybox pointer...");

    if (m_isCalculated) {
        if (!m_isVideoMemFree) {
            if (m_render->GetWindow()->IsWindowOpen()) {
                SR_ERROR("Skybox::Free() : video memory is not free!");
                return false;
            } else {
                SR_ERROR("Skybox::Free() : video memory is not free! Window is closed.");
            }
        }
    }

    delete this;
    return true;
}

void Framework::Graphics::Types::Skybox::DrawOpenGL() {
    if (!m_isCalculated && (m_hasErrors || !Calculate())) {
        return;
    }

    m_env->DrawSkybox(m_VAO, m_cubeMap);
}

void Framework::Graphics::Types::Skybox::DrawVulkan() {
    if (!m_isCalculated && (m_hasErrors || !Calculate())) {
        return;
    }

    if (m_descriptorSet < 0) {
        if (m_descriptorSet = m_env->AllocDescriptorSet({ DescriptorType::Uniform }); m_descriptorSet < 0) {
            SR_ERROR("Skybox::DrawVulkan() : failed to calculate descriptor set!");
            m_hasErrors = true;
            return;
        }
        else {
            m_env->UpdateDescriptorSets(m_descriptorSet, {
                    { DescriptorType::Uniform, { 0, Shader::GetCurrentShader()->GetUBO(0) } },
            });

            m_env->BindDescriptorSet(m_descriptorSet);
            /**
             * 0 - view/proj
             * 1 - cube map
            */
            m_env->BindTexture(1, m_cubeMap);
        }
    }

    m_env->BindVBO(m_VBO);
    m_env->BindIBO(m_IBO);
    m_env->BindDescriptorSet(m_descriptorSet);

    m_env->DrawIndices(36);
}

bool Framework::Graphics::Types::Skybox::SetRender(Render *render) {
    if (m_render) {
        SR_ERROR("Skybox::SetRender() : render already set!");
        return false;
    }

    m_render = render;

    return true;
}

bool Framework::Graphics::Types::Skybox::FreeVideoMemory() {
    if (m_isVideoMemFree) {
        SR_ERROR("Skybox::FreeVideoMemory() : video memory already is freed!");
        return false;
    }

    SR_LOG("Skybox::FreeVideoMemory() : free skybox video memory...");

    if (m_VAO != -1) {
        if (!m_env->FreeVAO(m_VAO)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free VAO!");
        }
        m_VAO = -1;
    }

    if (m_VBO != -1) {
        if (!m_env->FreeVBO(m_VBO)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free VBO!");
        }
        m_VBO = -1;
    }

    if (m_IBO != -1) {
        if (!m_env->FreeIBO(m_IBO)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free IBO!");
        }
        m_IBO = -1;
    }

    if (m_cubeMap != -1) {
        m_env->FreeCubeMap(m_cubeMap);
        m_cubeMap = -1;
    }

    if (m_descriptorSet >= 0) {
        m_env->FreeDescriptorSet(m_descriptorSet);
        m_descriptorSet = -1;
    }

    m_isCalculated = false;
    m_isVideoMemFree = true;

    return true;
}

bool Framework::Graphics::Types::Skybox::AwaitFreeVideoMemory() {
    if (m_isVideoMemFree) {
        SR_ERROR("Skybox::AwaitFreeVideoMemory() : video memory is already freed!");
        return false;
    }

    if (!m_isCalculated) {
        SR_ERROR("Skybox::AwaitFreeVideoMemory() : skybox isn't calculated!");
        return false;
    }

    if (!m_env->IsWindowOpen()) {
        SR_ERROR("Skybox::AwaitFreeVideoMemory() : window has been closed!");
        return false;
    }

    if (m_render)
        m_render->FreeSkyboxMemory(this);

    ret:
    if (m_isVideoMemFree)
        goto ret;

    return true;
}
