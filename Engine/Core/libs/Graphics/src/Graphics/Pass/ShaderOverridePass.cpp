//
// Created by Monika on 21.01.2023.
//

#include <Graphics/Pass/ShaderOverridePass.h>

namespace SR_GRAPH_NS {
    SR_REGISTER_RENDER_PASS(ShaderOverridePass)

    ShaderOverridePass::ShaderOverridePass(RenderTechnique *pTechnique, BasePass* pParent)
        : Super(pTechnique, pParent)
    { }

    ShaderOverridePass::~ShaderOverridePass() {
        for (auto&& [type, pShader] : m_shaders) {
            if (!pShader) {
                continue;
            }

            pShader->RemoveUsePoint();
            pShader = nullptr;
        }
        m_shaders.clear();

        if (m_framebuffer) {
            m_framebuffer->RemoveUsePoint();
            m_framebuffer = nullptr;
        }
    }

    bool ShaderOverridePass::Load(const SR_XML_NS::Node& passNode) {
        LoadFramebufferSettings(passNode.TryGetNode("FramebufferSettings"));

        m_isDirectional = passNode.GetAttribute("Directional").ToBool(false);

        for (auto&& subNode : passNode.GetNodes()) {
            if (subNode.NameView() == "PreScale") {
                m_preScale.x = subNode.TryGetAttribute("X").ToFloat(1.f);
                m_preScale.y = subNode.TryGetAttribute("Y").ToFloat(1.f);
            }
        }

        if (auto&& shadersNode = passNode.TryGetNode("Shaders")) {
            for (auto&& overrideNode : shadersNode.TryGetNodes("Override")) {
                if (auto&& pShader = SR_GTYPES_NS::Shader::Load(overrideNode.GetAttribute("Path").ToString())) {
                    m_shaders.emplace_back(std::make_pair(
                            SR_UTILS_NS::EnumReflector::FromString<SR_SRSL_NS::ShaderType>(overrideNode.GetAttribute("Type").ToString()),
                            pShader
                    ));
                }
            }
        }

        for (auto&& [type, pShader] : m_shaders) {
            if (!pShader) {
                continue;
            }

            pShader->AddUsePoint();
        }

        return BasePass::Load(passNode);
    }


    void ShaderOverridePass::OnResize(const SR_MATH_NS::UVector2 &size) {
        IFramebufferPass::ResizeFrameBuffer(size);
        BasePass::OnResize(size);
    }

    bool ShaderOverridePass::Init() {
        if (!IsDirectional() && GetParentPass()) {
            SR_ERROR("ShaderOverridePass::Init() : if the rendering pass of the color buffer is not directional, then it cannot be nested!");
            return BasePass::Init() && false;
        }

        return BasePass::Init() && (IsDirectional() || InitializeFramebuffer(GetContext()));
    }

    bool ShaderOverridePass::DrawCluster(MeshCluster* pCluster) {
        if (!pCluster || pCluster->Empty()) {
            return false;
        }

        for (auto&&[_, subCluster] : *pCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader) {
                continue;
            }

            if (pShader->Use() == ShaderBindResult::Failed) {
                continue;
            }

            for (auto&& [key, meshGroup] : subCluster) {
                (*meshGroup.begin())->BindMesh();

                for (auto&& pMesh : meshGroup) {
                    pMesh->Draw();
                }
            }

            pShader->UnUse();
        }

        return true;
    }

    bool ShaderOverridePass::Render() {
        if (!m_framebuffer && !IsDirectional()) {
            return false;
        }

        auto&& pRenderScene = GetRenderScene();

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        if (IsDirectional()) {
            SR_MAYBE_UNUSED bool hasDrawData = DrawCluster(&pRenderScene->GetOpaque());
            hasDrawData |= DrawCluster(&pRenderScene->GetTransparent());
        }
        else {
            RenderInternal(pRenderScene);
        }

        m_uboManager.SetIdentifier(pIdentifier);

        return IsDirectional();
    }

    void ShaderOverridePass::RenderInternal(const RenderScenePtr& pRenderScene) {
        if (!m_framebuffer->Bind()) {
            return;
        }

        GetPipeline()->ResetCmdBuffer();

        m_framebuffer->BeginCmdBuffer(SR_MATH_NS::FColor(0.0), 1.f);
        {
            m_framebuffer->BeginRender();

            DrawCluster(&pRenderScene->GetOpaque());
            DrawCluster(&pRenderScene->GetTransparent());

            m_framebuffer->EndRender();
        }
        m_framebuffer->EndCmdBuffer();
    }

    void ShaderOverridePass::Update() {
        if (!m_camera) {
            return;
        }

        if (!IsDirectional() && (!m_framebuffer || m_framebuffer->IsDirty())) {
            return;
        }

        m_pipeline->SetCurrentFramebuffer(m_framebuffer);

        auto&& pRenderScene = GetRenderScene();

        auto&& pIdentifier = m_uboManager.GetIdentifier();
        m_uboManager.SetIdentifier(this);

        UpdateCluster(&pRenderScene->GetOpaque());
        UpdateCluster(&pRenderScene->GetTransparent());

        m_uboManager.SetIdentifier(pIdentifier);

        Super::Update();

        m_pipeline->SetCurrentFramebuffer(nullptr);
    }

    void ShaderOverridePass::UpdateCluster(MeshCluster* pCluster) {
        for (auto const& [_, subCluster] : *pCluster) {
            auto&& pShader = GetShader(subCluster.GetShaderType());
            if (!pShader || !pShader->Ready()) {
                continue;
            }

            m_context->SetCurrentShader(pShader);

            /**
             * TODO: нужно сделать что-то вроде SetSharedMat4, который будет биндить не в BLOCK а в SHARED_BLOCK
             */
            pShader->SetMat4(SHADER_VIEW_MATRIX, m_camera->GetViewTranslateRef());
            pShader->SetMat4(SHADER_PROJECTION_MATRIX, m_camera->GetProjectionRef());
            pShader->SetMat4(SHADER_ORTHOGONAL_MATRIX, m_camera->GetOrthogonalRef());

            for (auto const& [key, meshGroup] : subCluster) {
                for (const auto &pMesh : meshGroup) {
                    if (!pMesh->IsMeshActive()) {
                        continue;
                    }

                    auto&& virtualUbo = pMesh->GetVirtualUBO();
                    if (virtualUbo == SR_ID_INVALID) {
                        continue;
                    }

                    pMesh->UseMaterial();

                    pShader->SetVec3(SHADER_VIEW_DIRECTION, m_camera->GetViewDirection());

                    if (m_uboManager.BindUBO(virtualUbo) == Memory::UBOManager::BindResult::Duplicated) {
                        SR_ERROR("ShaderOverridePass::Update() : memory has been duplicated!");
                    }

                    pShader->Flush();
                }
            }
        }

        m_context->SetCurrentShader(nullptr);
    }

    ShaderOverridePass::ShaderPtr ShaderOverridePass::GetShader(SR_SRSL_NS::ShaderType type) const {
        for (auto&& [shaderType, pShader] : m_shaders) {
            if (shaderType == type) {
                return pShader;
            }
        }

        return nullptr;
    }
}
