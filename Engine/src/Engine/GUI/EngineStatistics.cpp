//
// Created by Monika on 26.03.2022.
//

#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/EngineStatistics.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/Engine.h>

#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/Skybox.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/Types/Mesh.h>
#include <Graphics/Memory/ShaderProgramManager.h>
#include <Graphics/Pass/FrameBufferPass.h>
#include <Graphics/Pass/AutoExposurePass.h>
#include <Graphics/Pass/MeshDrawerPass.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Render/DebugRenderer.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderQueue.h>
#include <Graphics/Overlay/Overlay.h>

#include <Utils/Types/IRawMeshHolder.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Resources/ResourceInfo.h>
#include <Utils/DebugDraw.h>
#include <Utils/Common/HashManager.h>
#include <Utils/CommandManager/CmdManager.h>
#include <Utils/TaskManager/TaskManager.h>

#include <Codegen/EngineStatistics.generated.hpp>

namespace SR_CORE_GUI_NS {
    EngineStatistics::EngineStatistics()
        : SR_GRAPH_GUI_NS::Widget("Engine statistics")
    {
        m_framerateHistory.reserve(m_framerateHistorySize);
        m_exposureHistory.reserve(m_exposureHistorySize);
    }

    void EngineStatistics::Draw() {
        if (SR_IMMEDIATE_GUI_NS::BeginTabBar("EngineStatsTabBar")) {
            SR_IMMEDIATE_GUI_NS::Separator();

            float_t framerate = SR_IMMEDIATE_GUI_NS::GetFramerate();
            m_framerateHistory.push_back(framerate);

            if (m_framerateHistory.size() > m_framerateHistorySize) {
                m_framerateHistory.erase(m_framerateHistory.begin());
            }

            CommonPage();
            ResourcesPage();
            ThreadsPage();
            WidgetsPage();
            VideoMemoryPage();
            SubmitQueuePage();
            RenderStrategyPage();
            StringAtoms();

            SR_IMMEDIATE_GUI_NS::EndTabBar();
        }
    }

    void EngineStatistics::ResourcesPage() {
        if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Resources manager")) {
            auto&& drawResource = [=](SR_UTILS_NS::IResource& resource, uint32_t index) {
                const bool isDestroyed = resource.IsDestroyed();

                std::string node = SR_FORMAT("[{}] {} = {}", index, resource.GetResourceId().data(), resource.GetCountUses());

                if (isDestroyed) {
                    SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(1.f, 0.f, 0.f));

                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(3) << static_cast<float>(SR_MAX(resource.GetLifetime(), 0) / SR_CLOCKS_PER_SEC);

                    node.append(" (").append(stream.str()).append(")");
                }

                SR_IMMEDIATE_GUI_NS::TreeNodeEx(&resource, SR_IMMEDIATE_GUI_NS::GetNodeFlagsWithoutChild(), "%s", node.c_str());

                if (isDestroyed) {
                    if (SR_IMMEDIATE_GUI_NS::IsMouseDoubleClicked(SR_IMMEDIATE_GUI_NS::MouseButton::Left) && SR_IMMEDIATE_GUI_NS::IsItemHovered()) {
                        resource.Kill();
                    }

                    SR_IMMEDIATE_GUI_NS::PopStyleColor();
                }
            };

            SR_UTILS_NS::ResourceManager::Instance().InspectResources([=](SR_UTILS_NS::ResourceManager::ResourcesTypes& groups) {
                for (auto& [groupHashName, pResourceType] : groups) {
                    const bool open = SR_IMMEDIATE_GUI_NS::TreeNodeEx((void*)(intptr_t)pResourceType, SR_IMMEDIATE_GUI_NS::GetNodeFlagsWithChild(), "%s", pResourceType->GetName().data());

                    if (open) {
                        uint32_t index = 0;
                        pResourceType->ForEach([&](SR_UTILS_NS::IResource& resource) {
                            drawResource(resource, index++);
                        });
                        SR_IMMEDIATE_GUI_NS::TreePop();
                    }
                }
            });

            SR_IMMEDIATE_GUI_NS::EndTabItem();
        }
    }

    void EngineStatistics::CommonPage() {
        if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Common")) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& pCommandManager = pEngine->GetCmdManager();

            if (pCommandManager) {
                auto&& lastCmdName = pCommandManager->GetLastCmdName();

                SR_IMMEDIATE_GUI_NS::Text("Command manager:");
                SR_IMMEDIATE_GUI_NS::Text("  History PC: %i", pCommandManager->GetHistoryPC());
                SR_IMMEDIATE_GUI_NS::Text("  History size: %i", pCommandManager->GetHistorySize());
                SR_IMMEDIATE_GUI_NS::Text("  Max history size: %i", pCommandManager->GetMaxHistorySize());
                SR_IMMEDIATE_GUI_NS::Text("  Last command: %s", lastCmdName.c_str());
            }

            float_t mb = SR_UTILS_NS::GetApplicationHeapSize() / (1024 * 1024);
            SR_IMMEDIATE_GUI_NS::Text("Allocated memory: %.2fMb", mb);

            if (SR_IMMEDIATE_GUI_NS::BeginPlot("Framerate History")) {
                SR_IMMEDIATE_GUI_NS::PlotLine("Framerate", m_framerateHistory.data(), m_framerateHistory.size(), SR_IMMEDIATE_GUI_NS::ImmediateDataType::Float);
                SR_IMMEDIATE_GUI_NS::EndPlot();
            }

            SR_IMMEDIATE_GUI_NS::EndTabItem();
        }
    }

    void EngineStatistics::ThreadsPage() {
        if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Threads")) {
            if (SR_IMMEDIATE_GUI_NS::BeginTable("##ThreadsTable", 4)) {
                SR_UTILS_NS::TaskManager::Instance().ForEachTask([](SR_UTILS_NS::Task& task) {
                    SR_IMMEDIATE_GUI_NS::PushID(task.GetId());

                    SR_IMMEDIATE_GUI_NS::TableNextRow();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(0);
                    SR_IMMEDIATE_GUI_NS::Text("%i", task.GetId());
                    SR_IMMEDIATE_GUI_NS::Separator();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(1);
                    SR_IMMEDIATE_GUI_NS::Text("%s", task.GetDescription().c_str());
                    SR_IMMEDIATE_GUI_NS::Separator();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(2);
                    SR_IMMEDIATE_GUI_NS::Text("%s", SR_UTILS_NS::EnumReflector::ToStringAtom(task.GetPriority()).c_str());
                    SR_IMMEDIATE_GUI_NS::Separator();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(3);
                    SR_IMMEDIATE_GUI_NS::Text("%s", SR_UTILS_NS::EnumReflector::ToStringAtom(task.GetState()).c_str());
                    SR_IMMEDIATE_GUI_NS::Separator();

                    SR_IMMEDIATE_GUI_NS::PopID();
                });
                SR_IMMEDIATE_GUI_NS::EndTable();
            }
            SR_IMMEDIATE_GUI_NS::EndTabItem();
        }
    }

    void EngineStatistics::WidgetsPage() {
        if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Widgets")) {
            if (SR_IMMEDIATE_GUI_NS::BeginTable("##WidgetsTable", 4))
            {
                for (auto&& [name, pWidget] : GetManager()->GetWidgets()) {
                    SR_IMMEDIATE_GUI_NS::TableNextRow();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(0);
                    SR_IMMEDIATE_GUI_NS::Text("%s", name.c_str());
                    SR_IMMEDIATE_GUI_NS::Separator();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(1);
                    SR_IMMEDIATE_GUI_NS::Text("%s", pWidget->IsOpen() ? "Opened" : "Closed");
                    SR_IMMEDIATE_GUI_NS::Separator();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(2);
                    SR_IMMEDIATE_GUI_NS::Text("%s", pWidget->IsFocused() ? "Focused" : "Unfocused");
                    SR_IMMEDIATE_GUI_NS::Separator();

                    SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(3);
                    SR_IMMEDIATE_GUI_NS::Text("%s", pWidget->IsHovered() ? "Hovered" : "Not hovered");
                    SR_IMMEDIATE_GUI_NS::Separator();
                }

                SR_IMMEDIATE_GUI_NS::EndTable();
            }

            if (SR_IMMEDIATE_GUI_NS::Button("Show/Close GUI metrics window")) {
                auto&& pEditor = dynamic_cast<EditorGUI*>(GetManager());
                pEditor->ShowMetricsWindow(!pEditor->IsMetricsWindowShown());
            }

            SR_IMMEDIATE_GUI_NS::EndTabItem();
        }
    }
 
    void EngineStatistics::VideoMemoryPage() {
        if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Video memory")) {
            auto&& pContext = GetContext();

            auto&& framebuffers = pContext->GetFramebuffers();
            auto&& textures = pContext->GetTextures();
            auto&& techniques = pContext->GetRenderTechniques();
            auto&& skyboxes = pContext->GetSkyboxes();

            if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Shaders")) {
                auto&& shaders = pContext->GetShaders();

                SR_IMMEDIATE_GUI_NS::Checkbox("Macros", &m_showShaderMacros);
                SR_IMMEDIATE_GUI_NS::SameLine();
                SR_IMMEDIATE_GUI_NS::Checkbox("Programs", &m_showShaderPrograms);
                SR_IMMEDIATE_GUI_NS::SameLine();
                SR_IMMEDIATE_GUI_NS::Checkbox("Show unused", &m_showUnusedShaders);

                auto&& shadersManager = SR_GRAPH_NS::Memory::ShaderProgramManager::Instance();

                if (SR_IMMEDIATE_GUI_NS::BeginTable("##ShadersTable", 1)) {
                    for (auto&& pShader : shaders) {
                        auto&& virtualProgram = pShader->GetVirtualProgram();
                        if (virtualProgram == SR_ID_INVALID && !m_showUnusedShaders) {
                            continue;
                        }

                        SR_IMMEDIATE_GUI_NS::TableNextRow();

                        SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(0);
                        SR_IMMEDIATE_GUI_NS::Text("%s [%i]", pShader->GetResourceId().c_str(), virtualProgram);

                        if (auto&& macros = pShader->GetMacros(); m_showShaderMacros && !macros.empty()) {
                            SR_IMMEDIATE_GUI_NS::Text("\tMacros: ");
                            for (auto&& entry : macros.GetParams()) {
                                m_stringCache = entry.GetValue(macros.GetBuffer());
                                if (m_stringCache.empty()) {
                                    SR_IMMEDIATE_GUI_NS::Text("\t\t%s ", entry.key.c_str());
                                    continue;
                                }
                                SR_IMMEDIATE_GUI_NS::Text("\t\t%s=%s ", entry.key.c_str(), m_stringCache.c_str());
                            }
                        }

                        if (m_showShaderPrograms && shadersManager.HasProgram(virtualProgram)) {
                            auto&& pVirtualInfo = shadersManager.GetInfo(virtualProgram);

                            for (uint32_t dataIndex = 0; dataIndex < pVirtualInfo->m_dataUsed; ++dataIndex) {
                                auto&& [identifier, program] = pVirtualInfo->m_data[dataIndex];
                                SR_IMMEDIATE_GUI_NS::Text("\t[%llu] = %i", identifier, program.id);
                            }
                        }

                        SR_IMMEDIATE_GUI_NS::Separator();
                    }

                    SR_IMMEDIATE_GUI_NS::EndTable();
                }
            }

            #define __SR_DRAW_COLUMN_DATA(index, ...)                   \
                SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(index); \
                SR_IMMEDIATE_GUI_NS::Text(__VA_ARGS__);          \
                SR_IMMEDIATE_GUI_NS::Separator();                \

            if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Framebuffers")) {
                if (SR_IMMEDIATE_GUI_NS::BeginTable("##FramebuffersTable", 7)) {
                    SR_IMMEDIATE_GUI_NS::TableNextRow();

                    __SR_DRAW_COLUMN_DATA(0, "Id")
                    __SR_DRAW_COLUMN_DATA(1, "Name")
                    __SR_DRAW_COLUMN_DATA(2, "Size")
                    __SR_DRAW_COLUMN_DATA(3, "Depth")
                    __SR_DRAW_COLUMN_DATA(4, "Is valid")
                    __SR_DRAW_COLUMN_DATA(5, "Was rendered")
                    __SR_DRAW_COLUMN_DATA(6, "Is dirty")

                    for (auto&& pFramebuffer : framebuffers) {
                        SR_IMMEDIATE_GUI_NS::TableNextRow();

                        __SR_DRAW_COLUMN_DATA(0, "%i", pFramebuffer->GetId());
                        __SR_DRAW_COLUMN_DATA(1, "%s", pFramebuffer->GetName().c_str());
                        __SR_DRAW_COLUMN_DATA(2, "%ix%i", pFramebuffer->GetSize().x, pFramebuffer->GetSize().y);
                        __SR_DRAW_COLUMN_DATA(3, "%s", pFramebuffer->IsDepthEnabled() ? "true" : "false");
                        __SR_DRAW_COLUMN_DATA(4, "%s", pFramebuffer->IsValid() ? "true" : "false");
                        __SR_DRAW_COLUMN_DATA(5, "%s", pFramebuffer->IsWasRendered() ? "true" : "false");
                        __SR_DRAW_COLUMN_DATA(6, "%s", pFramebuffer->IsDirty() ? "true" : "false");
                    }

                    SR_IMMEDIATE_GUI_NS::EndTable();
                }
            }

            if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Textures")) {
                if (SR_IMMEDIATE_GUI_NS::BeginTable("##TexturesTable", 1)) {
                    for (auto&& pTexture : textures) {
                        SR_IMMEDIATE_GUI_NS::TableNextRow();

                        SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(0);
                        SR_IMMEDIATE_GUI_NS::Text("%s", pTexture->GetResourceId().c_str());
                        SR_IMMEDIATE_GUI_NS::Separator();
                    }

                    SR_IMMEDIATE_GUI_NS::EndTable();
                }
            }

            if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Render Techniques")) {
                if (SR_IMMEDIATE_GUI_NS::BeginTable("##RenderTechniquesTable", 1)) {
                    for (auto&& pRenderTechnique : techniques) {
                        SR_IMMEDIATE_GUI_NS::TableNextRow();

                        SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(0);

                        SR_IMMEDIATE_GUI_NS::Text("Technique: %s", pRenderTechnique->GetName().data());

                        DrawRenderTechnique(const_cast<Graphics::IRenderTechnique *>(pRenderTechnique.Get()));

                        SR_IMMEDIATE_GUI_NS::Separator();
                    }

                    SR_IMMEDIATE_GUI_NS::EndTable();
                }
            }

            //if (ImGui::CollapsingHeader("Materials")) {
            //    if (ImGui::BeginTable("##MaterialsTable", 1)) {
            //        for (auto&& pMaterial : materials) {
            //            ImGui::TableNextRow();
//
            //            ImGui::TableSetColumnIndex(0);
            //            ImGui::Text("%s", pMaterial->GetResourceId().c_str());
            //            ImGui::Separator();
            //        }
//
            //        ImGui::EndTable();
            //    }
            //}

            if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Skyboxes")) {
                if (SR_IMMEDIATE_GUI_NS::BeginTable("##SkyboxesTable", 1)) {
                    for (auto&& pSkybox : skyboxes) {
                        SR_IMMEDIATE_GUI_NS::TableNextRow();

                        SR_IMMEDIATE_GUI_NS::TableSetColumnIndex(0);
                        SR_IMMEDIATE_GUI_NS::Text("%s", pSkybox->GetResourceId().c_str());
                        SR_IMMEDIATE_GUI_NS::Separator();
                    }

                    SR_IMMEDIATE_GUI_NS::EndTable();
                }
            }

            SR_IMMEDIATE_GUI_NS::EndTabItem();
        }
    }

    void EngineStatistics::SubmitQueuePage() {
        /*if (SR_IMMEDIATE_GUI_NS::BeginTabItem("Submit queue")) {
            auto&& pVulkan = GetContext()->GetPipeline().DynamicCast<SR_GRAPH_NS::VulkanPipeline>();
            if (!pVulkan) {
                SR_IMMEDIATE_GUI_NS::Text("Not supported!");
                SR_IMMEDIATE_GUI_NS::EndTabItem();
                return;
            }

            auto&& pKernel = pVulkan->GetKernel();
            if (!pKernel) {
                SR_IMMEDIATE_GUI_NS::Text("Kernel invalid!");
                SR_IMMEDIATE_GUI_NS::EndTabItem();
                return;
            }

            SR_IMMEDIATE_GUI_NS::CollapsingHeader(SR_FORMAT_C("Present complete semaphore [{}]", (void*)pKernel->GetPresentCompleteSemaphore()));

            auto&& queue = pKernel->GetSubmitQueue();

            uint32_t index = 0;
            for (auto&& submitInfo : queue) {
                if (SR_IMMEDIATE_GUI_NS::CollapsingHeader(SR_FORMAT_C("Queue {}", index))) {
                    DrawSubmitInfo(submitInfo);
                }
                ++index;
            }

            if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Graphics queue")) {
                DrawSubmitInfo(pKernel->GetSubmitInfo());
            }

            SR_IMMEDIATE_GUI_NS::CollapsingHeader(SR_FORMAT_C("Render complete semaphore [{}]", (void*)pKernel->GetRenderCompleteSemaphore()));

            SR_IMMEDIATE_GUI_NS::EndTabItem();
        }*/
    }

    void EngineStatistics::DrawSubmitInfo(const EvoVulkan::SubmitInfo& submitInfo) {
        /*SR_IMMEDIATE_GUI_NS::Separator();

        uint32_t waitIndex = 0;
        for (auto&& pSemaphore : submitInfo.waitSemaphores) {
            SR_IMMEDIATE_GUI_NS::Text("Wait semaphore %i [%p]", waitIndex, pSemaphore);
            ++waitIndex;
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        uint32_t cmdIndex = 0;
        for (auto&& pCmd : submitInfo.commandBuffers) {
            SR_IMMEDIATE_GUI_NS::Text("Cmd buffer %i [%p]", cmdIndex, pCmd);
            ++cmdIndex;
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        uint32_t signalIndex = 0;
        for (auto&& pSemaphore : submitInfo.signalSemaphores) {
            SR_IMMEDIATE_GUI_NS::Text("Signal semaphore %i [%p]", signalIndex, pSemaphore);
            ++signalIndex;
        }

        SR_IMMEDIATE_GUI_NS::Separator();*/
    }

    void EngineStatistics::DrawRenderTechnique(SR_GRAPH_NS::IRenderTechnique* pRenderTechnique) {
        pRenderTechnique->ForEachPass([this](SR_GRAPH_NS::BasePass& pass) {
            auto&& pMeshDrawerPass = dynamic_cast<SR_GRAPH_NS::MeshDrawerPass*>(&pass);
            auto&& pFramebufferPass = dynamic_cast<SR_GRAPH_NS::FrameBufferPass*>(&pass);

            SR_IMMEDIATE_GUI_NS::PushID((void*)&pass);

            if (!pMeshDrawerPass && !pFramebufferPass) {
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor::Yellow());
                SR_IMMEDIATE_GUI_NS::Dummy(10.f);
                SR_IMMEDIATE_GUI_NS::SameLine();
                if (SR_IMMEDIATE_GUI_NS::CollapsingHeader(pass.GetPassName())) {
                    SR_IMMEDIATE_GUI_NS::PopStyleColor();
                    if (auto&& pAutoExposure = dynamic_cast<SR_GRAPH_NS::AutoExposurePass*>(&pass)) {
                        auto&& exposure = pAutoExposure->GetExposure();
                        SR_IMMEDIATE_GUI_NS::Text("Previous: %f | Current: %f", exposure.first, exposure.second);
                        m_exposureHistory.push_back(exposure.first);
                        if (m_exposureHistory.size() > m_exposureHistorySize) {
                            m_exposureHistory.erase(m_exposureHistory.begin());
                        }
                        if (SR_IMMEDIATE_GUI_NS::BeginPlot("History")) {
                            SR_IMMEDIATE_GUI_NS::PlotLine("Exposure", m_exposureHistory.data(), m_exposureHistory.size(), SR_IMMEDIATE_GUI_NS::ImmediateDataType::Float);
                            SR_IMMEDIATE_GUI_NS::EndPlot();
                        }
                    }
                }
                else {
                    SR_IMMEDIATE_GUI_NS::PopStyleColor();
                }
                SR_IMMEDIATE_GUI_NS::PopID();
                return;
            }

            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, pFramebufferPass ? SR_MATH_NS::FColor::Cyan() : SR_MATH_NS::FColor::White());

            SR_IMMEDIATE_GUI_NS::Dummy(10.f);
            SR_IMMEDIATE_GUI_NS::SameLine();

            if (!SR_IMMEDIATE_GUI_NS::CollapsingHeader(pass.GetPassName())) {
                SR_IMMEDIATE_GUI_NS::PopID();
                SR_IMMEDIATE_GUI_NS::PopStyleColor();
                return;
            }
            SR_IMMEDIATE_GUI_NS::PopStyleColor();

            if (pMeshDrawerPass) {
                DrawMeshDrawerPass(pMeshDrawerPass);
            }

            auto&& pFramebuffer = pFramebufferPass ? pFramebufferPass->GetFrameBuffer() : nullptr;
            if (!pFramebuffer) {
                SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Yellow(), "Framebuffer is nullptr!");
                SR_IMMEDIATE_GUI_NS::PopID();
                return;
            }

            if (pFramebuffer->GetArrayLayersCount() > 1) {
                SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Yellow(), "Cannot display framebuffer with multiple layers!");
                SR_IMMEDIATE_GUI_NS::Text("Array layers: %i", pFramebuffer->GetArrayLayersCount());
                SR_IMMEDIATE_GUI_NS::PopID();
                return;
            }

            for (uint32_t i = 0; i < pFramebuffer->GetColorLayersCount(); ++i) {
                if (auto&& textureId = pFramebuffer->GetColorTexture(i, pFramebuffer->GetPipeline()->GetCurrentImageIndex()); textureId != SR_ID_INVALID) {
                    auto&& pPipeline = GetContext()->GetPipeline();
                    auto&& pDescriptor = pPipeline->GetOverlay(SR_GRAPH_NS::OverlayType::ImGui)->GetTextureDescriptorSet(textureId);
                    SR_IMMEDIATE_GUI_NS::DrawTexture(pDescriptor, 256, false);
                }
                else {
                    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Yellow(), "Color texture %i is invalid!", i);
                }
            }

            if (pFramebuffer->GetDepthAspect() == SR_GRAPH_NS::ImageAspect::Depth) {
                for (uint32_t i = 0; i < pFramebuffer->GetLayersCount(); ++i) {
                    if (auto&& textureId = pFramebuffer->GetDepthTexture(i, pFramebuffer->GetPipeline()->GetCurrentImageIndex()); textureId != SR_ID_INVALID) {
                        auto&& pPipeline = GetContext()->GetPipeline();
                        auto&& pDescriptor = pPipeline->GetOverlay(SR_GRAPH_NS::OverlayType::ImGui)->GetTextureDescriptorSet(textureId);
                        SR_IMMEDIATE_GUI_NS::DrawTexture(pDescriptor, 256, false);
                    }
                    else {
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor::Yellow(), "Depth texture %i is invalid!", i);
                    }
                }
            }

            SR_IMMEDIATE_GUI_NS::PopID();
            return;
        });
    }

    void EngineStatistics::DrawMeshDrawerPass(SR_GRAPH_NS::MeshDrawerPass* pMeshDrawerPass) {
        for (auto&& pRenderQueue : pMeshDrawerPass->GetRenderQueues()) {
            DrawRenderQueue(pRenderQueue.Get());
        }
    }

    void EngineStatistics::DrawRenderQueue(const SR_GRAPH_NS::RenderQueue* pRenderQueue) {
        bool first = true;
        uint32_t vbo = SR_ID_INVALID;
        int64_t priority = 0;
        const SR_GTYPES_NS::Shader* pShader = nullptr;

        SR_IMMEDIATE_GUI_NS::Separator();
        SR_IMMEDIATE_GUI_NS::Text("Queue:");

        for (auto&& [layer, queue] : pRenderQueue->GetQueues()) {
            SR_IMMEDIATE_GUI_NS::Text("* Layer: %s", layer.c_str());

            for (auto&& meshInfo : queue) {
                if (first || priority != meshInfo.priority) {
                    priority = meshInfo.priority;
                    SR_IMMEDIATE_GUI_NS::Text("\t* Priority: %lli", priority);
                }

                if (first || pShader != meshInfo.pShader) {
                    pShader = meshInfo.pShader;
                    if (meshInfo.pShader) {
                        SR_IMMEDIATE_GUI_NS::Text("\t\t* Shader: %s", meshInfo.pShader->GetResourceId().c_str());
                    }
                    else {
                        SR_IMMEDIATE_GUI_NS::Text("\t\t* Shader: [no shader]");
                    }
                }

                if (first || vbo != meshInfo.vbo) {
                    vbo = meshInfo.vbo.value_or(-1);
                    SR_IMMEDIATE_GUI_NS::Text("\t\t\t* VBO: %i", vbo);
                }

                if (auto&& pObject = meshInfo.pObject) {
                    SR_IMMEDIATE_GUI_NS::Text("\t\t\t\t* Scene object: %s", pObject->GetGameObject()->GetName().c_str());
                }
                else {
                    SR_IMMEDIATE_GUI_NS::Text("\t\t\t\t* Geometry: Unknown");
                    //SR_IMMEDIATE_GUI_NS::Text("\t\t\t\t* Geometry: %s", meshInfo.pMesh->GetMeshIdentifier().c_str());
                }

                SR_IMMEDIATE_GUI_NS::SameLine();
                SR_IMMEDIATE_GUI_NS::Text(" : ");

                const bool vboError = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_VBO_ERROR);
                const bool shaderError = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_SHADER_ERROR);
                const bool notRendered = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_NOT_RENDERED);
                const bool waitRegister = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_WAIT_REGISTER);
                const bool missingShader = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_MISSING_SHADER);
                const bool invisible = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_INVISIBLE);

                if (vboError || shaderError || notRendered || waitRegister || missingShader || invisible) {
                    if (vboError) {
                        SR_IMMEDIATE_GUI_NS::SameLine();
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "VBO error");
                    }

                    if (shaderError) {
                        SR_IMMEDIATE_GUI_NS::SameLine();
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "Shader error");
                    }

                    if (missingShader) {
                        SR_IMMEDIATE_GUI_NS::SameLine();
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "Missing shader");
                    }

                    if (notRendered) {
                        SR_IMMEDIATE_GUI_NS::SameLine();
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1.0f, 0.5f, 0.0f, 1.0f), "Not rendered");
                    }

                    if (waitRegister) {
                        SR_IMMEDIATE_GUI_NS::SameLine();
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(0.5f, 0.5f, 0.0f, 1.0f), "Wait register");
                    }

                    if (invisible) {
                        SR_IMMEDIATE_GUI_NS::SameLine();
                        SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(0, 0, 1, 1), "Invisible");
                    }
                }
                else if (SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_ERROR)) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1, 0, 1, 1), "Inactive");
                }

                if (meshInfo.state == SR_GRAPH_NS::RenderQueue::QUEUE_STATE_OK) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                    SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(0, 1, 0, 1), "Ok");
                }

                first = false;
            }
        }
    }

    void EngineStatistics::RenderStrategyPage() {
        auto&& pRenderScene = GetRenderScene();
        if (!pRenderScene) {
            return;
        }

        if (!SR_IMMEDIATE_GUI_NS::BeginTabItem("Render strategy")) {
            return;
        }

        auto&& pRenderStrategy = pRenderScene->GetRenderStrategy();
        auto&& pPipeline = pRenderScene->GetPipeline();

        SR_IMMEDIATE_GUI_NS::Text("Cameras:");
        auto&& pMainCamera = pRenderScene->GetMainCamera();
        for (auto&& cameraInfo : pRenderScene->GetCameras()) {
            if (!cameraInfo.pCamera) {
                SR_IMMEDIATE_GUI_NS::Text("* Invalid camera");
                continue;
            }

            if (cameraInfo.pCamera == pMainCamera) {
                SR_IMMEDIATE_GUI_NS::Text("* Main camera: %s", cameraInfo.pCamera->GetRenderTechniquePath().c_str());
            }
            else {
                SR_IMMEDIATE_GUI_NS::Text("* Offscreen camera: %s", cameraInfo.pCamera->GetRenderTechniquePath().c_str());
            }

            if (SR_IMMEDIATE_GUI_NS::Button(SR_FORMAT_C("Raycast test##{}", cameraInfo.pCamera.GetRawPtr()))) {
                SR_UTILS_NS::DebugDraw::Instance().DrawLine(SR_ID_INVALID, cameraInfo.pCamera->GetPosition(), SR_MATH_NS::FVector3::Zero(), SR_MATH_NS::FColor::Red(), 5.0f);
            }
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Pipeline use count: {}", pPipeline->GetPtrData()->strongCount.load()));

        if (auto&& pDebugRenderer = pRenderScene->GetRenderer<SR_GRAPH_NS::DebugRenderer>()) {
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Timed objects pool size: {}", pDebugRenderer->GetTimedObjectPoolSize()));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Timed empty ids pool size: {}", pDebugRenderer->GetEmptyIdsPoolSize()));
        }
        else {
            SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(1, 0, 0, 1));
            SR_IMMEDIATE_GUI_NS::Text("Debug renderer not found!");
            SR_IMMEDIATE_GUI_NS::PopStyleColor();
        }

        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Draw info")) {
            auto&& buildState = pPipeline->GetBuildState(pPipeline->GetCurrentImageIndex());

            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Vertices count: {}", buildState.vertices));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Triangles count: {}", static_cast<uint32_t>(buildState.vertices / 3)));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Draw calls: {}", buildState.drawCalls));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Used textures: {}", buildState.usedTextures));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Used shaders: {}", buildState.usedShaders));
        }

        if (SR_IMMEDIATE_GUI_NS::CollapsingHeader("Video memory info")) {
            auto&& memoryInfo = pPipeline->GetUsedVideoMemoryInfo();

            if (pPipeline->GetPreviousState().transferredMemory >= 1024) {
                const uint32_t transferredKBytes = pPipeline->GetPreviousState().transferredMemory / 1024;
                SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Transferred memory: {}Kb", transferredKBytes));
            }
            else {
                const uint32_t transferredBytes = pPipeline->GetPreviousState().transferredMemory;
                SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Transferred memory: {}B", transferredBytes));
            }

            SR_IMMEDIATE_GUI_NS::Text("%", SR_FORMAT_C("Transferred count: {}", pPipeline->GetPreviousState().transferredCount));

            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Used memory: {} MB", uint64_t(memoryInfo.videoMemoryUsed / 1024 / 1024)));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Allocated heaps count: {}", memoryInfo.videoMemoryHeaps));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Descriptor sets count: {}", memoryInfo.descriptorSetsCount));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Shader programs count: {}", memoryInfo.shaderProgramsCount));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("UBOs count: {}", memoryInfo.UBOsCount));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("VBOs count: {}", memoryInfo.VBOsCount));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("IBOs count: {}", memoryInfo.IBOsCount));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("SSBOs count: {}", memoryInfo.SSBOsCount));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("FBOs count: {}", memoryInfo.FBOsCount));
            SR_IMMEDIATE_GUI_NS::Text(SR_FORMAT_C("Textures count: {}", memoryInfo.texturesCount));
        }

        SR_IMMEDIATE_GUI_NS::Separator();

        if (SR_IMMEDIATE_GUI_NS::Button("Crash video driver")) {
            pPipeline->CrashDriver();
        }

        SR_IMMEDIATE_GUI_NS::Text("Status:");
        SR_IMMEDIATE_GUI_NS::SameLine();

        if (!pRenderStrategy->GetErrors().empty()) {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "Error");

            if (SR_IMMEDIATE_GUI_NS::BeginListBox("Render errors")) {
                for (auto&& error : pRenderScene->GetRenderStrategy()->GetErrors()) {
                    SR_IMMEDIATE_GUI_NS::Selectable(error.c_str());
                }
                SR_IMMEDIATE_GUI_NS::EndListBox();
            }
        }
        else {
            SR_IMMEDIATE_GUI_NS::TextColored(SR_MATH_NS::FColor(0, 1, 0, 1), "Ok");
        }

        bool debugMode = pRenderStrategy->IsDebugModeEnabled();
        if (SR_IMMEDIATE_GUI_NS::Checkbox("Debug mode", &debugMode)) {
            pRenderStrategy->SetDebugMode(debugMode);
        }

        auto&& pHierarchy = GetManager()->GetWidget<Hierarchy>();

        if (SR_IMMEDIATE_GUI_NS::BeginListBox("Invalid meshes")) {
            for (auto&& pObject : pRenderStrategy->GetProblemObjects()) {
                auto&& pRawMeshHolder = dynamic_cast<SR_HTYPES_NS::IRawMeshHolder*>(pObject);

                SR_UTILS_NS::StringAtom name;

                if (pObject && pObject->GetGameObject()) {
                    name = pObject->GetGameObject()->GetName();
                }

                if (name.empty() && pRawMeshHolder) {
                    name = pRawMeshHolder->GetMeshPath().ToStringView();
                }

                //if (name.empty()) {
                //    name = pMesh->GetMeshIdentifier();
                //}

                if (name.empty()) {
                    name = "Unknown mesh";
                }

                if (SR_IMMEDIATE_GUI_NS::Selectable(name.c_str())) {
                    if (pHierarchy && pObject) {
                        pHierarchy->SelectGameObject(pObject->GetSceneObject());
                    }
                }
            }

            SR_IMMEDIATE_GUI_NS::EndListBox();
        }

        SR_IMMEDIATE_GUI_NS::EndTabItem();
    }

    void EngineStatistics::StringAtoms() {
        if (!SR_IMMEDIATE_GUI_NS::BeginTabItem("String atoms")) {
            return;
        }

        auto&& hashManager = SR_UTILS_NS::HashManager::Instance();

        hashManager.Lock();

        SR_IMMEDIATE_GUI_NS::Text("String atoms count: %llu", hashManager.GetStorage().size());

        SR_IMMEDIATE_GUI_NS::Separator();

        for (auto&& [hash, pStringInfo] : hashManager.GetStorage()) {
            SR_IMMEDIATE_GUI_NS::Text("%s", pStringInfo->data.c_str());
        }

        hashManager.Unlock();

        SR_IMMEDIATE_GUI_NS::EndTabItem();
    }
}
