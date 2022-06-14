//
// Created by Nikita on 20.11.2020.
//

#include <Types/Skybox.h>
#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/Common/StringUtils.h>
#include <stbi/stb_image.h>
#include <Render/Render.h>
#include <Types/Vertices.h>
#include <Window/Window.h>
#include <Loaders/ObjLoader.h>
#include <Utils/Common/Features.h>
#include <Utils/Common/Vertices.hpp>

namespace SR_GTYPES_NS {
    Skybox::Skybox()
        : SR_UTILS_NS::IResource(typeid(Skybox).name(), true /** autoRemove */)
        , m_env(Environment::Get())
    { }

    Skybox::~Skybox() {
        SetShader(nullptr);
        SRAssert(m_cubeMap == SR_ID_INVALID);

        for (auto&& img : m_data) {
            if (img) {
                stbi_image_free(img);
                img = nullptr;
            }
        }
    }

    Skybox *Skybox::Load(const SR_UTILS_NS::Path& path) {
        auto&& folder = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Skyboxes").Concat(path.GetBaseName());

        SR_LOG("Skybox::Load() : loading \"" + path.ToString() + "\" skybox...");

        std::array<uint8_t *, 6> sides = {};

        static constexpr const char* files[6] { "right", "left", "top", "bottom", "front", "back" };

        int32_t W, H, C;

        for (uint8_t i = 0; i < 6; ++i) {
            auto&& file = folder.Concat(files[i]).ConcatExt(path.GetExtension());

            int32_t w = 0, h = 0, comp = 0;
            uint8_t *data = stbi_load(file.CStr(), &w, &h, &comp, STBI_rgb_alpha);

            if (!data) {
                SR_ERROR("Skybox::Load() : failed to load skybox!\n\tPath: " + file.ToString());
                return nullptr;
            }

            if (i == 0) {
                W = w;
                H = h;
                C = comp;
            }
            else if (h != H || w != W || C != comp) {
                SR_WARN("Skybox::Load() : \"" + path.ToString() + "\" skybox has different sizes!");
            }

            sides[i] = data;
        }

        auto *skybox = new Skybox();

        skybox->m_width = W;
        skybox->m_height = H;
        skybox->m_data = sides;

        skybox->SetShader(Shader::Load("Engine/skybox.srsl"));

        skybox->SetId(path.ToString());

        return skybox;
    }

    bool Skybox::Calculate() {
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

        auto &&indexedVertices = Vertices::CastVertices<Vertices::SimpleVertex>(SR_UTILS_NS::SKYBOX_INDEXED_VERTICES);

        if (m_env->GetPipeLine() == PipeLine::Vulkan) {
            auto &&indices = SR_UTILS_NS::SKYBOX_INDICES;

            if (m_VBO = m_env->CalculateVBO(indexedVertices.data(), Vertices::Type::SimpleVertex, indexedVertices.size()); m_VBO == SR_ID_INVALID) {
                SR_ERROR("Skybox::Calculate() : failed to calculate VBO!");
                m_hasErrors = true;
                return false;
            }

            if (m_IBO = m_env->CalculateIBO((void *) indices.data(), sizeof(uint32_t), indices.size(), SR_ID_INVALID);
                    m_IBO == SR_ID_INVALID) {
                SR_ERROR("Skybox::Calculate() : failed to calculate IBO!");
                m_hasErrors = true;
                return false;
            }
        }
        else {
            auto &&vertices = SR_UTILS_NS::IndexedVerticesToNonIndexed(indexedVertices, SR_UTILS_NS::SKYBOX_INDICES);

            if (m_VBO = m_env->CalculateVBO(vertices.data(), Vertices::Type::SimpleVertex, vertices.size()); m_VBO == SR_ID_INVALID) {
                SR_ERROR("Skybox::Calculate() : failed to calculate VBO!");
                m_hasErrors = true;
                return false;
            }
        }

        m_isCalculated = true;

        return true;
    }

    void Skybox::DrawOpenGL() {
        m_env->DrawSkybox(m_VAO, m_cubeMap);
    }

    void Skybox::DrawVulkan() {
        if (m_dirtyShader)
        {
            m_dirtyShader = false;

            if (m_descriptorSet != SR_ID_INVALID && !m_env->FreeDescriptorSet(&m_descriptorSet)) {
                SR_ERROR("Skybox::DrawVulkan() : failed to free descriptor set!");
            }

            if (m_UBO != SR_ID_INVALID && !m_env->FreeUBO(&m_UBO)) {
                SR_ERROR("Skybox::DrawVulkan() : failed to free uniform buffer object!");
            }

            if (m_shader->GetUBOBlockSize() > 0) {
                if (m_descriptorSet = m_env->AllocDescriptorSet({DescriptorType::Uniform}); m_descriptorSet == SR_ID_INVALID) {
                    SR_ERROR("Skybox::DrawVulkan() : failed to calculate descriptor set!");
                    m_hasErrors = true;
                    return;
                }

                if (m_UBO = m_env->AllocateUBO(m_shader->GetUBOBlockSize()); m_UBO == SR_ID_INVALID) {
                    SR_ERROR("Mesh3D::DrawVulkan() : failed to allocate uniform buffer object!");
                    m_hasErrors = true;
                    return;
                }

                m_env->BindUBO(m_UBO);
                m_env->BindDescriptorSet(m_descriptorSet);
            }
            else if (m_shader->GetSamplersCount() > 0) {
                if (m_descriptorSet = m_env->AllocDescriptorSet({DescriptorType::CombinedImage}); m_descriptorSet == SR_ID_INVALID) {
                    SR_ERROR("Skybox::DrawVulkan() : failed to calculate descriptor set!");
                    m_hasErrors = true;
                    return;
                }
                m_env->BindDescriptorSet(m_descriptorSet);
            }
            else
                m_env->ResetDescriptorSet();

            m_shader->InitUBOBlock();
            m_shader->Flush();

            m_shader->SetSamplerCube(Shader::SKYBOX_DIFFUSE, m_cubeMap);
        }

        m_env->BindVBO(m_VBO);
        m_env->BindIBO(m_IBO);

        if (m_descriptorSet != SR_ID_INVALID) {
            m_env->BindDescriptorSet(m_descriptorSet);
        }

        m_env->DrawIndices(36);
    }

    bool Framework::Graphics::Types::Skybox::FreeVideoMemory() {
        if (!m_isCalculated) {
            return false;
        }

        SR_LOG("Skybox::FreeVideoMemory() : free skybox video memory...");

        if (m_VAO != SR_ID_INVALID && !m_env->FreeVAO(&m_VAO)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free VAO!");
        }

        if (m_VBO != SR_ID_INVALID && !m_env->FreeVBO(&m_VBO)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free VBO!");
        }

        if (m_IBO != SR_ID_INVALID && !m_env->FreeIBO(&m_IBO)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free IBO!");
        }

        if (m_UBO != SR_ID_INVALID && !m_env->FreeUBO(&m_UBO)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free uniform buffer object!");
        }

        if (m_cubeMap != SR_ID_INVALID && !m_env->FreeCubeMap(&m_cubeMap)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free cube map!");
        }

        if (m_descriptorSet >= 0 && !m_env->FreeDescriptorSet(&m_descriptorSet)) {
            SR_ERROR("Skybox::FreeVideoMemory() : failed to free descriptor set!");
        }

        m_isCalculated = false;

        return true;
    }

    void Skybox::Draw() {
        if (!m_isCalculated && (m_hasErrors || !Calculate())) {
            return;
        }

        switch (m_env->GetPipeLine()) {
            case PipeLine::Vulkan:
                DrawVulkan();
                break;
            default:
                SRAssertOnce(false);
                break;
        }
    }

    void Skybox::OnResourceUpdated(IResource *pResource, int32_t depth) {
        if (dynamic_cast<Shader*>(pResource) == m_shader && m_shader) {
            m_dirtyShader = true;
            m_hasErrors = false;
        }

        IResource::OnResourceUpdated(pResource, depth);
    }

    void Skybox::SetShader(Shader *shader) {
        SR_SCOPED_LOCK

        if (m_shader == shader) {
            return;
        }

        m_dirtyShader = true;

        if (m_shader) {
            auto&& render = m_shader->GetRender();
            RemoveDependency(m_shader);
            if (m_shader->GetCountUses() == 0) {
                SRAssert2(render, "Render are nullptr!");
                if (render) {
                    render->FreeShader(m_shader);
                }
            }
            m_shader = nullptr;
        }

        if (!(m_shader = shader)) {
            return;
        }

        AddDependency(m_shader);
    }

    int32_t Skybox::GetVBO() {
        if (!m_isCalculated && (m_hasErrors || !Calculate())) {
            return SR_ID_INVALID;
        }

        return m_VBO;
    }

    int32_t Skybox::GetIBO() {
        if (!m_isCalculated && (m_hasErrors || !Calculate())) {
            return SR_ID_INVALID;
        }

        return m_IBO;
    }

    int32_t Skybox::GetUBO() {
        return m_UBO;
    }
}