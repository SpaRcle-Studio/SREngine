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

Framework::Graphics::Types::Skybox::Skybox() {
    this->m_env = Environment::Get();
}

Framework::Graphics::Types::Skybox::~Skybox() = default;

Framework::Graphics::Types::Skybox *Framework::Graphics::Types::Skybox::Load(const std::string& name) {
    std::string skyboxName = name;

    std::string ext = StringUtils::GetExtensionFromFilePath(skyboxName);
    skyboxName.resize(skyboxName.size() - ext.size() - 1);

    const auto path = Helper::ResourceManager::Instance().GetResPath().Concat("/Skyboxes/").Concat(skyboxName).Concat("/");

    Helper::Debug::Log("Skybox::Load() : loading \""+skyboxName+"\" skybox...");

    std::array<uint8_t*, 6> sides = { };
    static const std::string files[6]{ "right", "left", "top", "bottom", "front", "back" };

    int W, H, C;

    for (unsigned char i = 0; i < 6; i++) {
        const auto file = path.Concat(files[i]).Concat(".").Concat(ext);

        int w = 0, h = 0, comp = 0;
        unsigned char* data = stbi_load(file.CStr(), &w, &h, &comp, STBI_rgb_alpha);

        if (!i) {
            W = w;
            H = h;
            C = comp;
        } else if (h != H || w != W || C != comp) {
            Helper::Debug::Warn("Skybox::Load() : \"" + name + "\" skybox has different sizes!");
        }

        if (!data) {
            Helper::Debug::Error("Skybox::Load() : failed load \"" + skyboxName + "\" skybox!\n\tPath: " + file.ToString());
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
        Helper::Debug::Error("Skybox::Calculate() : skybox already calculated!");
        return false;
    }

    if (m_cubeMap = m_env->CalculateCubeMap(m_width, m_height, m_data); m_cubeMap < 0) {
        Helper::Debug::Error("Skybox::Calculate() : failed calculate cube map!");
        this->m_hasErrors = true;
        return false;
    }

    if (m_env->GetPipeLine() == PipeLine::Vulkan) {
        const auto path = Helper::ResourceManager::Instance().GetResPath().Concat("/Models/Engine/skybox.obj");
        auto skyboxObj = Graphics::ObjLoader::LoadSourceWithIndices<Vertices::SkyboxVertex>(path.ToString());
        if (skyboxObj.size() != 1) {
            Helper::Debug::Error("Skybox::Calculate() : failed to load skybox model!");
            this->m_hasErrors = true;
            return false;
        }

        auto& [name, indices, vertices] = skyboxObj[0];

        if (m_VBO = m_env->CalculateVBO(vertices.data(), Vertices::Type::SkyboxVertex, vertices.size()); m_VBO == SR_ID_INVALID) {
            Helper::Debug::Error("Skybox::Calculate() : failed to calculate VBO!");
            this->m_hasErrors = true;
            return false;
        }

        if (m_IBO = m_env->CalculateIBO(indices.data(), sizeof(uint32_t), indices.size(), SR_ID_INVALID); m_IBO == SR_ID_INVALID) {
            Helper::Debug::Error("Skybox::Calculate() : failed to calculate IBO!");
            this->m_hasErrors = true;
            return false;
        }
    } else
        m_VAO = m_env->CalculateSkybox();

    m_isCalculated = true;
    return true;
}

bool Framework::Graphics::Types::Skybox::Free() {
    Debug::Log("Skybox::Free() : free skybox pointer...");

    if (m_isCalculated)
        if (!m_isVideoMemFree) {
            if (m_render->GetWindow()->IsWindowOpen()) {
                Debug::Error("Skybox::Free() : video memory is not free!");
                return false;
            }
            else
                Debug::Warn("Skybox::Free() : video memory is not free! Window is closed.");
        }

    delete this;
    return true;
}

void Framework::Graphics::Types::Skybox::DrawOpenGL() {
    if (!m_isCalculated)
        if (m_hasErrors || !this->Calculate())
            return;

    m_env->DrawSkybox(m_VAO, m_cubeMap);
}

void Framework::Graphics::Types::Skybox::DrawVulkan() {
    if (m_hasErrors)
        return;

    if (!m_isCalculated) {
        if (!this->Calculate())
            return;
        else if (m_descriptorSet < 0) {
            if (this->m_descriptorSet = m_env->AllocDescriptorSet({ DescriptorType::Uniform }); m_descriptorSet < 0) {
                Helper::Debug::Error("Skybox::DrawVulkan() : failed to calculate descriptor set!");
                this->m_hasErrors = true;
                return;
            } else {
                this->m_env->UpdateDescriptorSets(m_descriptorSet, {
                        { DescriptorType::Uniform, { 0, Shader::GetCurrentShader()->GetUBO(0) } },
                });

                //this->m_env->SetDescriptorID(m_descriptorSet);
                m_env->BindDescriptorSet(m_descriptorSet);
                /*
                 * 0 - view/proj
                 * 1 - cube map
                */
                this->m_env->BindTexture(1, m_cubeMap);
            }
        }
    }

    m_env->BindVBO(m_VBO);
    m_env->BindIBO(m_IBO);
    m_env->BindDescriptorSet(m_descriptorSet);

    m_env->DrawIndices(36);
}

bool Framework::Graphics::Types::Skybox::SetRender(Render *render) {
    if (m_render) {
        Debug::Error("Skybox::SetRender() : render already set!");
        return false;
    }

    this->m_render = render;

    return true;
}

bool Framework::Graphics::Types::Skybox::FreeVideoMemory() {
    if (m_isVideoMemFree) {
        Debug::Error("Skybox::FreeVideoMemory() : video memory already is freed!");
        return false;
    }

    Debug::Log("Skybox::FreeVideoMemory() : free skybox video memory...");

    if (m_VAO != -1) {
        if (!this->m_env->FreeVAO(m_VAO))
            Helper::Debug::Error("Skybox::FreeVideoMemory() : failed to free VAO!");
        m_VAO = -1;
    }

    if (m_VBO != -1) {
        if (!m_env->FreeVBO(m_VBO))
            Helper::Debug::Error("Skybox::FreeVideoMemory() : failed to free VBO!");
        m_VBO = -1;
    }

    if (m_IBO != -1) {
        if (!m_env->FreeIBO(m_IBO))
            Helper::Debug::Error("Skybox::FreeVideoMemory() : failed to free IBO!");
        m_IBO = -1;
    }

    if (m_cubeMap != -1) {
        this->m_env->FreeCubeMap(m_cubeMap);
        this->m_cubeMap = -1;
    }

    if (m_descriptorSet >= 0) {
        this->m_env->FreeDescriptorSet(m_descriptorSet);
        this->m_descriptorSet = -1;
    }

    this->m_isCalculated = false;
    this->m_isVideoMemFree = true;

    return true;
}

bool Framework::Graphics::Types::Skybox::AwaitFreeVideoMemory() {
    if (m_isVideoMemFree) {
        Helper::Debug::Error("Skybox::AwaitFreeVideoMemory() : video memory is already freed!");
        return false;
    }

    if (!m_isCalculated) {
        Helper::Debug::Error("Skybox::AwaitFreeVideoMemory() : skybox isn't calculated!");
        return false;
    }

    if (!m_env->IsWindowOpen()) {
        Helper::Debug::Error("Skybox::AwaitFreeVideoMemory() : window has been closed!");
        return false;
    }

    if (m_render)
        m_render->FreeSkyboxMemory(this);

    ret:
    if (m_isVideoMemFree)
        goto ret;

    return true;
}
