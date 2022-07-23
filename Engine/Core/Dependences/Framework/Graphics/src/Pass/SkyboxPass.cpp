//
// Created by Monika on 20.07.2022.
//

#include <Pass/SkyboxPass.h>
#include <Types/Skybox.h>
#include <Types/Shader.h>
#include <Environment/Basic/IShaderProgram.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(SkyboxPass)

    SkyboxPass::SkyboxPass(RenderTechnique *pTechnique)
        : BasePass(pTechnique)
    { }

    SkyboxPass::~SkyboxPass() {
        if (m_skybox) {
            m_skybox->RemoveUsePoint();
        }
    }

    bool SkyboxPass::Load(const SR_XML_NS::Node &passNode) {
        auto&& path = passNode.GetAttribute<SR_UTILS_NS::Path>();

        if (!(m_skybox = SR_GTYPES_NS::Skybox::Load(path))) {
            SR_ERROR("SkyboxPass::Load() : failed to load skybox!\n\tPath: " + path.ToString());
            return false;
        }
        else {
            m_skybox->AddUsePoint();
        }

        return BasePass::Load(passNode);
    }

    void SkyboxPass::Render() {
        if (!m_skybox) {
            return;
        }

        auto&& shader = m_skybox->GetShader();

        if (!shader || !shader->Use()) {
            return;
        }

        m_skybox->Draw();

        shader->UnUse();

        BasePass::Render();
    }

    void SkyboxPass::Update() {
        if (!m_skybox) {
            return;
        }

        auto&& shader = m_skybox->GetShader();

        if (!shader || !shader->Ready() || !m_camera) {
            return;
        }

        shader->SetMat4(SHADER_VIEW_NO_TRANSLATE_MATRIX, m_camera->GetViewRef());
        shader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());

        /// TODO: вынести в глобальный счетчик, так как операция ресурсозатратная
        shader->SetFloat(SHADER_TIME, clock());

        auto&& virtualUbo = m_skybox->GetVirtualUBO();
        if (virtualUbo == SR_ID_INVALID) {
            return;
        }

        if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
            SR_ERROR("SkyboxPass::Update() : memory has been duplicated!");
        }

        shader->Flush();

        BasePass::Update();
    }

    void SkyboxPass::DeInit() {
        if (m_skybox) {
            m_skybox->FreeVideoMemory();
        }

        BasePass::DeInit();
    }
}