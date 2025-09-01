//
// Created by Monika on 26.03.2022.
//

#include <Engine/GUI/EngineStatistics.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/DebugDraw.h>

#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/Skybox.h>

#include <Graphics/Memory/ShaderProgramManager.h>
#include <Graphics/Pass/FrameBufferPass.h>
#include <Graphics/Pass/MeshDrawerPass.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Render/DebugRenderer.h>
#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderQueue.h>

// #include <Graphics/Pipeline/Vulkan/VulkanPipeline.h>
// #include <Graphics/Pipeline/Vulkan/VulkanKernel.h>
// #include <Graphics/Pipeline/Vulkan/VulkanMemory.h>

namespace SR_CORE_GUI_NS {
    EngineStatistics::EngineStatistics()
        : SR_GRAPH_GUI_NS::Widget("Engine statistics")
    { }

    void EngineStatistics::Draw() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginTabBar("EngineStatsTabBar")) {
            SR_GRAPH_GUI_NS::Immediate::Separator();

            CommonPage();
            ResourcesPage();
            ThreadsPage();
            WidgetsPage();
            VideoMemoryPage();
            SubmitQueuePage();
            RenderStrategyPage();
            StringAtoms();

            SR_GRAPH_GUI_NS::Immediate::EndTabBar();
        }
    }

    void EngineStatistics::ResourcesPage() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Resources manager")) {
            auto&& drawResource = [=](SR_UTILS_NS::IResource* pRes, uint32_t index) {
                const bool isDestroyed = pRes->IsDestroyed();

                std::string node = SR_FORMAT("[{}] {} = {}", index, pRes->GetResourceId().data(), pRes->GetCountUses());

                if (isDestroyed) {
                    SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(1.f, 0.f, 0.f));

                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(3) << static_cast<float>(SR_MAX(pRes->GetLifetime(), 0) / SR_CLOCKS_PER_SEC);

                    node.append(" (").append(stream.str()).append(")");
                }

                SR_GRAPH_GUI_NS::Immediate::TreeNodeEx(pRes, SR_GRAPH_GUI_NS::Immediate::SR_NODE_FLAGS_WITHOUT_CHILD, "%s", node.c_str());

                if (isDestroyed) {
                    if (SR_GRAPH_GUI_NS::Immediate::IsMouseDoubleClicked(SR_GRAPH_GUI_NS::Immediate::MouseButton::Left) && SR_GRAPH_GUI_NS::Immediate::IsItemHovered()) {
                        pRes->Kill();
                    }

                    SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
                }
            };

            auto&& drawResources = [=](std::unordered_set<SR_UTILS_NS::IResource::Ptr>& resources, uint32_t index) {
                uint32_t subIndex = 0;

                const auto node = SR_FORMAT("[{}] {} ({})", index, (*resources.begin())->GetResourceId().data(), resources.size());

                const bool open = SR_GRAPH_GUI_NS::Immediate::TreeNodeEx((void*)(intptr_t)index, SR_GRAPH_GUI_NS::Immediate::SR_NODE_FLAGS_WITH_CHILD, "%s", node.c_str());

                if (open) {
                    for (const SR_UTILS_NS::IResource::Ptr& pRes : resources) {
                        drawResource(const_cast<SR_UTILS_NS::IResource*>(pRes.Get()), subIndex++);
                    }
                    SR_GRAPH_GUI_NS::Immediate::TreePop();
                }
            };

            SR_UTILS_NS::ResourceManager::Instance().InspectResources([=](auto &groups) {
                for (auto& [groupHashName, pResourceType] : groups) {
                    const bool open = SR_GRAPH_GUI_NS::Immediate::TreeNodeEx((void*)(intptr_t)pResourceType, SR_GRAPH_GUI_NS::Immediate::SR_NODE_FLAGS_WITH_CHILD, "%s", pResourceType->GetName().data());

                    if (open) {
                        uint32_t index = 0;

                        SR_UTILS_NS::ResourceType::CopiesMap& copies = pResourceType->GetCopiesRef();

                        for (auto& [resourceName, pResources] : copies) {
                            if (pResources.size() == 1) {
                                drawResource(const_cast<SR_UTILS_NS::IResource*>((*pResources.begin()).Get()), index++);
                            }
                            else {
                                drawResources(pResources, index++);
                            }
                        }

                        SR_GRAPH_GUI_NS::Immediate::TreePop();
                    }
                }
            });

            SR_GRAPH_GUI_NS::Immediate::EndTabItem();
        }
    }

    void EngineStatistics::CommonPage() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Common")) {
            auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
            auto&& pCommandManager = pEngine->GetCmdManager();

            if (pCommandManager) {
                std::string lastCmdName = pCommandManager->GetLastCmdName();

                SR_GRAPH_GUI_NS::Immediate::Text("Command manager:");
                SR_GRAPH_GUI_NS::Immediate::Text("  History PC: %i", pCommandManager->GetHistoryPC());
                SR_GRAPH_GUI_NS::Immediate::Text("  History size: %i", pCommandManager->GetHistorySize());
                SR_GRAPH_GUI_NS::Immediate::Text("  Max history size: %i", pCommandManager->GetMaxHistorySize());
                SR_GRAPH_GUI_NS::Immediate::Text("  Last command: %s", lastCmdName.c_str());
            }

            SR_GRAPH_GUI_NS::Immediate::EndTabItem();
        }
    }

    void EngineStatistics::ThreadsPage() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Threads")) {
            SR_GRAPH_GUI_NS::Immediate::EndTabItem();
        }
    }

    void EngineStatistics::WidgetsPage() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Widgets")) {
            if (SR_GRAPH_GUI_NS::Immediate::BeginTable("##WidgetsTable", 4))
            {
                for (auto&& [name, pWidget] : GetManager()->GetWidgets()) {
                    SR_GRAPH_GUI_NS::Immediate::TableNextRow();

                    SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(0);
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", name.c_str());
                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(1);
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", pWidget->IsOpen() ? "Opened" : "Closed");
                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(2);
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", pWidget->IsFocused() ? "Focused" : "Unfocused");
                    SR_GRAPH_GUI_NS::Immediate::Separator();

                    SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(3);
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", pWidget->IsHovered() ? "Hovered" : "Not hovered");
                    SR_GRAPH_GUI_NS::Immediate::Separator();
                }

                SR_GRAPH_GUI_NS::Immediate::EndTable();
            }

            SR_GRAPH_GUI_NS::Immediate::EndTabItem();
        }
    }
 
    void EngineStatistics::VideoMemoryPage() {
        if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Video memory")) {
            auto&& pContext = GetContext();

            auto&& framebuffers = pContext->GetFramebuffers();
            auto&& textures = pContext->GetTextures();
            auto&& techniques = pContext->GetRenderTechniques();
            auto&& skyboxes = pContext->GetSkyboxes();

            if (SR_GRAPH_GUI_NS::Immediate::CollapsingHeader("Shaders")) {
                auto&& shaders = pContext->GetShaders();

                auto&& shadersManager = SR_GRAPH_NS::Memory::ShaderProgramManager::Instance();

                if (SR_GRAPH_GUI_NS::Immediate::BeginTable("##ShadersTable", 1)) {
                    for (auto&& pShader : shaders) {
                        SR_GRAPH_GUI_NS::Immediate::TableNextRow();

                        auto&& virtualProgram = pShader->GetVirtualProgram();

                        SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(0);
                        SR_GRAPH_GUI_NS::Immediate::Text("%s [%i]", pShader->GetResourceId().c_str(), virtualProgram);

                        if (shadersManager.HasProgram(virtualProgram)) {
                            auto&& pVirtualInfo = shadersManager.GetInfo(virtualProgram);

                            for (auto&& [identifier, program] : pVirtualInfo->m_data) {
                                SR_GRAPH_GUI_NS::Immediate::Text("\t[%llu] = %i", identifier, program.id);
                            }
                        }

                        SR_GRAPH_GUI_NS::Immediate::Separator();
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndTable();
                }
            }

            if (SR_GRAPH_GUI_NS::Immediate::CollapsingHeader("Framebuffers")) {
                if (SR_GRAPH_GUI_NS::Immediate::BeginTable("##FramebuffersTable", 1)) {
                    for (auto&& pFramebuffer : framebuffers) {
                        SR_GRAPH_GUI_NS::Immediate::TableNextRow();

                        SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(0);
                        SR_GRAPH_GUI_NS::Immediate::Text("%i", pFramebuffer->GetId());
                        SR_GRAPH_GUI_NS::Immediate::Separator();
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndTable();
                }
            }

            if (SR_GRAPH_GUI_NS::Immediate::CollapsingHeader("Textures")) {
                if (SR_GRAPH_GUI_NS::Immediate::BeginTable("##TexturesTable", 1)) {
                    for (auto&& pTexture : textures) {
                        SR_GRAPH_GUI_NS::Immediate::TableNextRow();

                        SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(0);
                        SR_GRAPH_GUI_NS::Immediate::Text("%s", pTexture->GetResourceId().c_str());
                        SR_GRAPH_GUI_NS::Immediate::Separator();
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndTable();
                }
            }

            if (SR_GRAPH_GUI_NS::Immediate::CollapsingHeader("Render Techniques")) {
                if (SR_GRAPH_GUI_NS::Immediate::BeginTable("##RenderTechniquesTable", 1)) {
                    for (auto&& pRenderTechnique : techniques) {
                        SR_GRAPH_GUI_NS::Immediate::TableNextRow();

                        SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(0);

                        SR_GRAPH_GUI_NS::Immediate::Text("%s", pRenderTechnique->GetName().data());

                        DrawRenderTechnique(const_cast<Graphics::IRenderTechnique *>(pRenderTechnique.Get()));

                        SR_GRAPH_GUI_NS::Immediate::Separator();
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndTable();
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

            if (SR_GRAPH_GUI_NS::Immediate::CollapsingHeader("Skyboxes")) {
                if (SR_GRAPH_GUI_NS::Immediate::BeginTable("##SkyboxesTable", 1)) {
                    for (auto&& pSkybox : skyboxes) {
                        SR_GRAPH_GUI_NS::Immediate::TableNextRow();

                        SR_GRAPH_GUI_NS::Immediate::TableSetColumnIndex(0);
                        SR_GRAPH_GUI_NS::Immediate::Text("%s", pSkybox->GetResourceId().c_str());
                        SR_GRAPH_GUI_NS::Immediate::Separator();
                    }

                    SR_GRAPH_GUI_NS::Immediate::EndTable();
                }
            }

            SR_GRAPH_GUI_NS::Immediate::EndTabItem();
        }
    }

    void EngineStatistics::SubmitQueuePage() {
        /*if (SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Submit queue")) {
            auto&& pVulkan = GetContext()->GetPipeline().DynamicCast<SR_GRAPH_NS::VulkanPipeline>();
            if (!pVulkan) {
                SR_GRAPH_GUI_NS::Immediate::Text("Not supported!");
                SR_GRAPH_GUI_NS::Immediate::EndTabItem();
                return;
            }

            auto&& pKernel = pVulkan->GetKernel();
            if (!pKernel) {
                SR_GRAPH_GUI_NS::Immediate::Text("Kernel invalid!");
                SR_GRAPH_GUI_NS::Immediate::EndTabItem();
                return;
            }

            SR_GRAPH_GUI_NS::Immediate::CollapsingHeader(SR_FORMAT_C("Present complete semaphore [{}]", (void*)pKernel->GetPresentCompleteSemaphore()));

            auto&& queue = pKernel->GetSubmitQueue();

            uint32_t index = 0;
            for (auto&& submitInfo : queue) {
                if (SR_GRAPH_GUI_NS::Immediate::CollapsingHeader(SR_FORMAT_C("Queue {}", index))) {
                    DrawSubmitInfo(submitInfo);
                }
                ++index;
            }

            if (SR_GRAPH_GUI_NS::Immediate::CollapsingHeader("Graphics queue")) {
                DrawSubmitInfo(pKernel->GetSubmitInfo());
            }

            SR_GRAPH_GUI_NS::Immediate::CollapsingHeader(SR_FORMAT_C("Render complete semaphore [{}]", (void*)pKernel->GetRenderCompleteSemaphore()));

            SR_GRAPH_GUI_NS::Immediate::EndTabItem();
        }*/
    }

    void EngineStatistics::DrawSubmitInfo(const EvoVulkan::SubmitInfo& submitInfo) {
        /*SR_GRAPH_GUI_NS::Immediate::Separator();

        uint32_t waitIndex = 0;
        for (auto&& pSemaphore : submitInfo.waitSemaphores) {
            SR_GRAPH_GUI_NS::Immediate::Text("Wait semaphore %i [%p]", waitIndex, pSemaphore);
            ++waitIndex;
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        uint32_t cmdIndex = 0;
        for (auto&& pCmd : submitInfo.commandBuffers) {
            SR_GRAPH_GUI_NS::Immediate::Text("Cmd buffer %i [%p]", cmdIndex, pCmd);
            ++cmdIndex;
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        uint32_t signalIndex = 0;
        for (auto&& pSemaphore : submitInfo.signalSemaphores) {
            SR_GRAPH_GUI_NS::Immediate::Text("Signal semaphore %i [%p]", signalIndex, pSemaphore);
            ++signalIndex;
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();*/
    }

    void EngineStatistics::DrawRenderTechnique(SR_GRAPH_NS::IRenderTechnique* pRenderTechnique) {
        pRenderTechnique->ForEachPass([this](auto&& pass) -> bool {
            if (auto&& pMeshDrawerPass = dynamic_cast<SR_GRAPH_NS::MeshDrawerPass*>(&pass)) {
                DrawMeshDrawerPass(pMeshDrawerPass);
            }

            auto&& pFramebufferPass = dynamic_cast<SR_GRAPH_NS::FrameBufferPass*>(&pass);
            if (!pFramebufferPass) {
                return true;
            }

            auto&& pFramebuffer = pFramebufferPass->GetFrameBuffer();
            if (!pFramebuffer) {
                return true;
            }

            for (uint32_t i = 0; i < pFramebuffer->GetColorLayersCount(); ++i) {
                if (auto&& textureId = pFramebuffer->GetColorTexture(i); textureId != SR_ID_INVALID) {
                    auto&& pPipeline = GetContext()->GetPipeline();
                    SR_GRAPH_GUI_NS::Immediate::DrawTexture(pPipeline.Get(), textureId, 256, false);
                }
            }

            if (pFramebuffer->GetDepthAspect() == SR_GRAPH_NS::ImageAspect::Depth) {
                for (uint32_t i = 0; i < pFramebuffer->GetLayersCount(); ++i) {
                    if (auto&& textureId = pFramebuffer->GetDepthTexture(i); textureId != SR_ID_INVALID) {
                        auto&& pPipeline = GetContext()->GetPipeline();
                        SR_GRAPH_GUI_NS::Immediate::DrawTexture(pPipeline.Get(), textureId, 256, false);
                    }
                }
            }

            return true;
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

        SR_GRAPH_GUI_NS::Immediate::Separator();
        SR_GRAPH_GUI_NS::Immediate::Text("Queue:");

        for (auto&& [layer, queue] : pRenderQueue->GetQueues()) {
            SR_GRAPH_GUI_NS::Immediate::Text("* Layer: %s", layer.c_str());

            for (auto&& meshInfo : queue) {
                if (first || priority != meshInfo.priority) {
                    priority = meshInfo.priority;
                    SR_GRAPH_GUI_NS::Immediate::Text("\t* Priority: %lli", priority);
                }

                if (first || pShader != meshInfo.pShader) {
                    pShader = meshInfo.pShader;
                    if (meshInfo.pShader) {
                        SR_GRAPH_GUI_NS::Immediate::Text("\t\t* Shader: %s", meshInfo.pShader->GetResourceId().c_str());
                    }
                    else {
                        SR_GRAPH_GUI_NS::Immediate::Text("\t\t* Shader: [no shader]");
                    }
                }

                if (first || vbo != meshInfo.vbo) {
                    vbo = meshInfo.vbo;
                    SR_GRAPH_GUI_NS::Immediate::Text("\t\t\t* VBO: %i", vbo);
                }

                if (auto&& pMeshComponent = dynamic_cast<SR_GTYPES_NS::Mesh*>(meshInfo.pMesh); pMeshComponent && pMeshComponent->GetGameObject()) {
                    SR_GRAPH_GUI_NS::Immediate::Text("\t\t\t\t* GameObject: %s", pMeshComponent->GetGameObject()->GetName().c_str());
                }
                else {
                    SR_GRAPH_GUI_NS::Immediate::Text("\t\t\t\t* Geometry: %s", meshInfo.pMesh->GetMeshIdentifier().c_str());
                }

                SR_GRAPH_GUI_NS::Immediate::SameLine();
                SR_GRAPH_GUI_NS::Immediate::Text(" : ");

                const bool vboError = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_VBO_ERROR);
                const bool shaderError = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_SHADER_ERROR);
                const bool notRendered = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_NOT_RENDERED);
                const bool waitRegister = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_WAIT_REGISTER);
                const bool missingShader = SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_MISSING_SHADER);

                if (vboError || shaderError || notRendered || waitRegister || missingShader) {
                    if (vboError) {
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "VBO error");
                    }

                    if (shaderError) {
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "Shader error");
                    }

                    if (missingShader) {
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "Missing shader");
                    }

                    if (notRendered) {
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.0f, 0.5f, 0.0f, 1.0f), "Not rendered");
                    }

                    if (waitRegister) {
                        SR_GRAPH_GUI_NS::Immediate::SameLine();
                        SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0.5f, 0.5f, 0.0f, 1.0f), "Wait register");
                    }
                }
                else if (SR_UTILS_NS::Math::IsMaskIncludedSubMask(meshInfo.state, SR_GRAPH_NS::RenderQueue::QUEUE_STATE_ERROR)) {
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                    SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1, 0, 1, 1), "Inactive");
                }

                if (meshInfo.state == SR_GRAPH_NS::RenderQueue::QUEUE_STATE_OK) {
                    SR_GRAPH_GUI_NS::Immediate::SameLine();
                    SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0, 1, 0, 1), "Ok");
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

        if (!SR_GRAPH_GUI_NS::Immediate::BeginTabItem("Render strategy")) {
            return;
        }

        auto&& pRenderStrategy = pRenderScene->GetRenderStrategy();
        auto&& pPipeline = pRenderScene->GetPipeline();

        SR_GRAPH_GUI_NS::Immediate::Text("Cameras:");
        auto&& pMainCamera = pRenderScene->GetMainCamera();
        for (auto&& cameraInfo : pRenderScene->GetCameras()) {
            if (!cameraInfo.pCamera) {
                SR_GRAPH_GUI_NS::Immediate::Text("* Invalid camera");
                continue;
            }

            if (cameraInfo.pCamera == pMainCamera) {
                SR_GRAPH_GUI_NS::Immediate::Text("* Main camera: %s", cameraInfo.pCamera->GetRenderTechniquePath().c_str());
            }
            else {
                SR_GRAPH_GUI_NS::Immediate::Text("* Offscreen camera: %s", cameraInfo.pCamera->GetRenderTechniquePath().c_str());
            }

            if (SR_GRAPH_GUI_NS::Immediate::Button(SR_FORMAT_C("Raycast test##{}", cameraInfo.pCamera.GetRawPtr()))) {
                SR_UTILS_NS::DebugDraw::Instance().DrawLine(SR_ID_INVALID, cameraInfo.pCamera->GetPosition(), SR_MATH_NS::FVector3::Zero(), SR_MATH_NS::FColor::Red(), 5.0f);
            }
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Pipeline use count: {}", pPipeline->GetPtrData()->strongCount.load()));

        if (pPipeline->GetPreviousState().transferredMemory >= 1024) {
            const uint32_t transferredKBytes = pPipeline->GetPreviousState().transferredMemory / 1024;
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Transferred memory: {}Kb", transferredKBytes));
        }
        else {
            const uint32_t transferredBytes = pPipeline->GetPreviousState().transferredMemory;
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Transferred memory: {}B", transferredBytes));
        }

        SR_GRAPH_GUI_NS::Immediate::Text("%", SR_FORMAT_C("Transferred count: {}", pPipeline->GetPreviousState().transferredCount));

        SR_GRAPH_GUI_NS::Immediate::Separator();
        SR_GRAPH_GUI_NS::Immediate::Text("Draw info:");

        auto&& buildState = pPipeline->GetBuildState(pPipeline->GetCurrentFrameIndex());

        SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Vertices count: {}", buildState.vertices));
        SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Triangles count: {}", static_cast<uint32_t>(buildState.vertices / 3)));
        SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Draw calls: {}", buildState.drawCalls));
        SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Used textures: {}", buildState.usedTextures));
        SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Used shaders: {}", buildState.usedShaders));

        if (auto&& pDebugRenderer = pRenderScene->GetRenderer<SR_GRAPH_NS::DebugRenderer>()) {
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Timed objects pool size: {}", pDebugRenderer->GetTimedObjectPoolSize()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Timed empty ids pool size: {}", pDebugRenderer->GetEmptyIdsPoolSize()));
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::PushStyleColor(SR_GRAPH_GUI_NS::Immediate::StyleColor::Text, SR_MATH_NS::FColor(1, 0, 0, 1));
            SR_GRAPH_GUI_NS::Immediate::Text("Debug renderer not found!");
            SR_GRAPH_GUI_NS::Immediate::PopStyleColor();
        }

        /*if (auto&& pVulkanPipeline = pPipeline.DynamicCast<SR_GRAPH_NS::VulkanPipeline>()) {
            SR_GRAPH_GUI_NS::Immediate::Separator();
            SR_GRAPH_GUI_NS::Immediate::Text("Vulkan memory:");
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Descriptor sets count: {}", pVulkanPipeline->GetMemoryManager()->GetDescriptorSetsCount()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Shader programs count: {}", pVulkanPipeline->GetMemoryManager()->GetShaderProgramsCount()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("UBOs count: {}", pVulkanPipeline->GetMemoryManager()->GetUBOsCount()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("VBOs count: {}", pVulkanPipeline->GetMemoryManager()->GetVBOsCount()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("IBOs count: {}", pVulkanPipeline->GetMemoryManager()->GetIBOsCount()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("SSBOs count: {}", pVulkanPipeline->GetMemoryManager()->GetSSBOsCount()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("FBOs count: {}", pVulkanPipeline->GetMemoryManager()->GetFBOsCount()));
            SR_GRAPH_GUI_NS::Immediate::Text(SR_FORMAT_C("Textures count: {}", pVulkanPipeline->GetMemoryManager()->GetTexturesCount()));
        }*/

        SR_GRAPH_GUI_NS::Immediate::Separator();

        SR_GRAPH_GUI_NS::Immediate::Text("Status:");
        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (!pRenderStrategy->GetErrors().empty()) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1, 0, 0, 1), "Error");

            if (SR_GRAPH_GUI_NS::Immediate::BeginListBox("Render errors")) {
                for (auto&& error : pRenderScene->GetRenderStrategy()->GetErrors()) {
                    SR_GRAPH_GUI_NS::Immediate::Selectable(error.c_str());
                }
                SR_GRAPH_GUI_NS::Immediate::EndListBox();
            }
        }
        else {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(0, 1, 0, 1), "Ok");
        }

        bool debugMode = pRenderStrategy->IsDebugModeEnabled();
        if (SR_GRAPH_GUI_NS::Immediate::Checkbox("Debug mode", &debugMode)) {
            pRenderStrategy->SetDebugMode(debugMode);
        }

        auto&& pHierarchy = GetManager()->GetWidget<Hierarchy>();

        if (SR_GRAPH_GUI_NS::Immediate::BeginListBox("Invalid meshes")) {
            for (auto&& pMesh : pRenderStrategy->GetProblemMeshes()) {
                auto&& pRenderComponent = dynamic_cast<SR_GTYPES_NS::IRenderComponent*>(pMesh);
                auto&& pRawMeshHolder = dynamic_cast<SR_HTYPES_NS::IRawMeshHolder*>(pMesh);

                SR_UTILS_NS::StringAtom name;

                if (pRenderComponent && pRenderComponent->GetGameObject()) {
                    name = pRenderComponent->GetGameObject()->GetName();
                }

                if (name.empty() && pRawMeshHolder) {
                    name = pRawMeshHolder->GetMeshPath().ToStringView();
                }

                if (name.empty()) {
                    name = pMesh->GetMeshIdentifier();
                }

                if (name.empty()) {
                    name = SR_UTILS_NS::EnumReflector::ToStringAtom(pMesh->GetMeshType());
                }

                if (SR_GRAPH_GUI_NS::Immediate::Selectable(name.c_str())) {
                    if (pHierarchy && pRenderComponent) {
                        pHierarchy->SelectGameObject(pRenderComponent->GetSceneObject());
                    }
                }
            }

            SR_GRAPH_GUI_NS::Immediate::EndListBox();
        }

        SR_GRAPH_GUI_NS::Immediate::EndTabItem();
    }

    void EngineStatistics::StringAtoms() {
        if (!SR_GRAPH_GUI_NS::Immediate::BeginTabItem("String atoms")) {
            return;
        }

        auto&& hashManager = SR_UTILS_NS::HashManager::Instance();

        hashManager.Lock();

        SR_GRAPH_GUI_NS::Immediate::Text("String atoms count: %llu", hashManager.GetStorage().size());

        SR_GRAPH_GUI_NS::Immediate::Separator();

        for (auto&& [hash, pStringInfo] : hashManager.GetStorage()) {
            SR_GRAPH_GUI_NS::Immediate::Text("%s", pStringInfo->data.c_str());
        }

        hashManager.Unlock();

        SR_GRAPH_GUI_NS::Immediate::EndTabItem();
    }
}
