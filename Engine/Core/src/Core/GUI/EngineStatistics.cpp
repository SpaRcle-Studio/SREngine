//
// Created by Monika on 26.03.2022.
//

#include <Core/GUI/EngineStatistics.h>

#include <Utils/ResourceManager/ResourceManager.h>

#include <Graphics/Types/Framebuffer.h>
#include <Graphics/Types/Skybox.h>
#include <Graphics/Pass/IFramebufferPass.h>

#include <Graphics/Memory/ShaderProgramManager.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Pipeline/Vulkan/VulkanPipeline.h>
#include <Graphics/Pipeline/Vulkan/VulkanKernel.h>

namespace SR_CORE_GUI_NS {
    EngineStatistics::EngineStatistics()
        : SR_GRAPH_GUI_NS::Widget("Engine statistics")
    { }

    void EngineStatistics::Draw() {
        if (ImGui::BeginTabBar("EngineStatsTabBar")) {
            ImGui::Separator();

            ResourcesPage();
            ThreadsPage();
            WidgetsPage();
            VideoMemoryPage();
            SubmitQueuePage();
            FlatClusterPage();

            ImGui::EndTabBar();
        }
    }

    void EngineStatistics::ResourcesPage() {
        if (ImGui::BeginTabItem("Resources manager")) {
            auto&& drawResource = [=](SR_UTILS_NS::IResource* pRes, uint32_t index) {
                const bool isDestroyed = pRes->IsDestroyed();

                std::string node = SR_FORMAT("[{}] {} = {}", index, pRes->GetResourceId().data(), pRes->GetCountUses());

                if (isDestroyed) {
                    ImGui::PushStyleColor(ImGuiCol_::ImGuiCol_Text, ImVec4(255, 0, 0, 255));

                    std::stringstream stream;
                    stream << std::fixed << std::setprecision(3) << static_cast<float>(SR_MAX(pRes->GetLifetime(), 0) / SR_CLOCKS_PER_SEC);

                    node.append(" (").append(stream.str()).append(")");
                }

                ImGui::TreeNodeEx(node.c_str(), m_nodeFlagsWithoutChild);

                if (isDestroyed) {
                    if (ImGui::IsMouseDoubleClicked(ImGuiMouseButton_::ImGuiMouseButton_Left) && ImGui::IsItemHovered()) {
                        pRes->Kill();
                    }

                    ImGui::PopStyleColor();
                }
            };

            auto&& drawResources = [=](const std::unordered_set<SR_UTILS_NS::IResource*>& resources, uint32_t index) {
                uint32_t subIndex = 0;

                const auto node = SR_FORMAT("[{}] {} ({})", index, (*resources.begin())->GetResourceId().data(), resources.size());

                if (ImGui::TreeNodeEx(node.c_str(), m_nodeFlagsWithChild)) {
                    for (auto &&pRes : resources)
                        drawResource(pRes, subIndex++);
                    ImGui::TreePop();
                }
            };

            SR_UTILS_NS::ResourceManager::Instance().InspectResources([=](const auto &groups) {
                for (const auto& [groupHashName, pResourceType] : groups) {
                    if (ImGui::TreeNodeEx(pResourceType->GetName().data(), m_nodeFlagsWithChild)) {
                        uint32_t index = 0;

                        for (const auto&[resourceName, pResources] : pResourceType->GetCopiesRef()) {
                            if (pResources.size() == 1) {
                                drawResource(*pResources.begin(), index++);
                            }
                            else {
                                drawResources(pResources, index++);
                            }
                        }

                        ImGui::TreePop();
                    }
                }
            });

            ImGui::EndTabItem();
        }
    }

    void EngineStatistics::ThreadsPage() {
        if (ImGui::BeginTabItem("Threads")) {
            ImGui::EndTabItem();
        }
    }

    void EngineStatistics::WidgetsPage() {
        if (ImGui::BeginTabItem("Widgets")) {
            if (ImGui::BeginTable("##WidgetsTable", 4))
            {
                for (auto&& [name, pWidget] : GetManager()->GetWidgets()) {
                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("%s", name.c_str());
                    ImGui::Separator();

                    ImGui::TableSetColumnIndex(1);
                    ImGui::Text("%s", pWidget->IsOpen() ? "Opened" : "Closed");
                    ImGui::Separator();

                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("%s", pWidget->IsFocused() ? "Focused" : "Unfocused");
                    ImGui::Separator();

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%s", pWidget->IsHovered() ? "Hovered" : "Not hovered");
                    ImGui::Separator();
                }

                ImGui::EndTable();
            }

            ImGui::EndTabItem();
        }
    }
 
    void EngineStatistics::VideoMemoryPage() {
        if (ImGui::BeginTabItem("Video memory")) {
            auto&& pContext = GetContext();

            auto&& framebuffers = pContext->GetFramebuffers();
            auto&& textures = pContext->GetTextures();
            auto&& techniques = pContext->GetRenderTechniques();
            auto&& materials = pContext->GetMaterials();
            auto&& skyboxes = pContext->GetSkyboxes();

            if (ImGui::CollapsingHeader("Shaders")) {
                auto&& shaders = pContext->GetShaders();

                auto&& shadersManager = SR_GRAPH_NS::Memory::ShaderProgramManager::Instance();

                if (ImGui::BeginTable("##ShadersTable", 1)) {
                    for (auto&& pShader : shaders) {
                        ImGui::TableNextRow();

                        auto&& virtualProgram = pShader->GetVirtualProgram();

                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%s [%i]", pShader->GetResourceId().c_str(), virtualProgram);

                        if (shadersManager.HasProgram(virtualProgram)) {
                            auto&& pVirtualInfo = shadersManager.GetInfo(virtualProgram);

                            for (auto&& [identifier, program] : pVirtualInfo->m_data) {
                                ImGui::Text("\t[%llu] = %i", identifier, program.id);
                            }
                        }

                        ImGui::Separator();
                    }

                    ImGui::EndTable();
                }
            }

            if (ImGui::CollapsingHeader("Framebuffers")) {
                if (ImGui::BeginTable("##FramebuffersTable", 1)) {
                    for (auto&& pFramebuffer : framebuffers) {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%i", pFramebuffer->GetId());
                        ImGui::Separator();
                    }

                    ImGui::EndTable();
                }
            }

            if (ImGui::CollapsingHeader("Textures")) {
                if (ImGui::BeginTable("##TexturesTable", 1)) {
                    for (auto&& pTexture : textures) {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%s", pTexture->GetResourceId().c_str());
                        ImGui::Separator();
                    }

                    ImGui::EndTable();
                }
            }

            if (ImGui::CollapsingHeader("Render Techniques")) {
                if (ImGui::BeginTable("##RenderTechniquesTable", 1)) {
                    for (auto&& pRenderTechnique : techniques) {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);

                        if (auto&& pResource = dynamic_cast<SR_UTILS_NS::IResource*>(pRenderTechnique)) {
                            ImGui::Text("%s", pResource->GetResourceId().c_str());
                        }
                        else {
                            ImGui::Text("%s", pRenderTechnique->GetName().data());
                        }

                        pRenderTechnique->ForEachPass([this](auto&& pPass) -> bool {
                            //if (pPass->GetName() != "SceneViewFBO") {
                            //    return;
                            //}

                            auto&& pFramebufferPass = dynamic_cast<SR_GRAPH_NS::IFramebufferPass*>(pPass);
                            if (!pFramebufferPass) {
                                return true;
                            }

                            auto&& pFramebuffer = pFramebufferPass->GetFramebuffer();
                            if (!pFramebuffer) {
                                return true;
                            }

                            for (uint32_t i = 0; i < pFramebuffer->GetColorLayersCount(); ++i) {
                                if (auto&& textureId = pFramebuffer->GetColorTexture(i); textureId != SR_ID_INVALID) {
                                    auto&& pPipeline = GetContext()->GetPipeline();
                                    SR_GRAPH_GUI_NS::DrawTexture(pPipeline.Get(), textureId, 256, false);
                                }
                            }

                            if (pFramebuffer->GetDepthAspect() == SR_GRAPH_NS::ImageAspect::Depth) {
                                for (uint32_t i = 0; i < pFramebuffer->GetLayersCount(); ++i) {
                                    if (auto&& textureId = pFramebuffer->GetDepthTexture(i); textureId != SR_ID_INVALID) {
                                        auto&& pPipeline = GetContext()->GetPipeline();
                                        SR_GRAPH_GUI_NS::DrawTexture(pPipeline.Get(), textureId, 256, false);
                                    }
                                }
                            }

                            return true;
                        });

                        ImGui::Separator();
                    }

                    ImGui::EndTable();
                }
            }

            if (ImGui::CollapsingHeader("Materials")) {
                if (ImGui::BeginTable("##MaterialsTable", 1)) {
                    for (auto&& pMaterial : materials) {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%s", pMaterial->GetResourceId().c_str());
                        ImGui::Separator();
                    }

                    ImGui::EndTable();
                }
            }

            if (ImGui::CollapsingHeader("Skyboxes")) {
                if (ImGui::BeginTable("##SkyboxesTable", 1)) {
                    for (auto&& pSkybox : skyboxes) {
                        ImGui::TableNextRow();

                        ImGui::TableSetColumnIndex(0);
                        ImGui::Text("%s", pSkybox->GetResourceId().c_str());
                        ImGui::Separator();
                    }

                    ImGui::EndTable();
                }
            }

            ImGui::EndTabItem();
        }
    }

    void EngineStatistics::SubmitQueuePage() {
        if (ImGui::BeginTabItem("Submit queue")) {
            auto&& pVulkan = GetContext()->GetPipeline().DynamicCast<SR_GRAPH_NS::VulkanPipeline>();
            if (!pVulkan) {
                ImGui::Text("Not supported!");
                ImGui::EndTabItem();
                return;
            }

            auto&& pKernel = pVulkan->GetKernel();
            if (!pKernel) {
                ImGui::Text("Kernel invalid!");
                ImGui::EndTabItem();
                return;
            }

            ImGui::CollapsingHeader(SR_FORMAT_C("Present complete semaphore [{}]", (void*)pKernel->GetPresentCompleteSemaphore()));

            auto&& queue = pKernel->GetSubmitQueue();

            uint32_t index = 0;
            for (auto&& submitInfo : queue) {
                if (ImGui::CollapsingHeader(SR_FORMAT_C("Queue {}", index))) {
                    DrawSubmitInfo(submitInfo);
                }
                ++index;
            }

            if (ImGui::CollapsingHeader("Graphics queue")) {
                DrawSubmitInfo(pKernel->GetSubmitInfo());
            }

            ImGui::CollapsingHeader(SR_FORMAT_C("Render complete semaphore [{}]", (void*)pKernel->GetRenderCompleteSemaphore()));

            ImGui::EndTabItem();
        }
    }

    void EngineStatistics::DrawSubmitInfo(const EvoVulkan::SubmitInfo& submitInfo) {
        ImGui::Separator();

        uint32_t waitIndex = 0;
        for (auto&& pSemaphore : submitInfo.waitSemaphores) {
            ImGui::Text("Wait semaphore %i [%p]", waitIndex, pSemaphore);
            ++waitIndex;
        }

        ImGui::Separator();

        uint32_t cmdIndex = 0;
        for (auto&& pCmd : submitInfo.commandBuffers) {
            ImGui::Text("Cmd buffer %i [%p]", cmdIndex, pCmd);
            ++cmdIndex;
        }

        ImGui::Separator();

        uint32_t signalIndex = 0;
        for (auto&& pSemaphore : submitInfo.signalSemaphores) {
            ImGui::Text("Signal semaphore %i [%p]", signalIndex, pSemaphore);
            ++signalIndex;
        }

        ImGui::Separator();
    }

    void EngineStatistics::FlatClusterPage() {
        auto&& pRenderScene = GetRenderScene();
        if (!pRenderScene) {
            return;
        }

        if (ImGui::BeginTabItem("Flat cluster"))
        {
            if (ImGui::BeginTable("##FlatCluster", 4))
            {
                uint32_t index = 0;

                for (auto&& pMesh : pRenderScene->GetFlatCluster()) {
                    ++index;

                    if (!pMesh) {
                        continue;
                    }

                    ImGui::TableNextRow();

                    ImGui::TableSetColumnIndex(0);
                    ImGui::Text("Index: %i", index);
                    ImGui::Separator();

                    ImGui::TableSetColumnIndex(1);
                    if (auto&& pMeshComponent = dynamic_cast<SR_GTYPES_NS::MeshComponent*>(pMesh); pMeshComponent && pMeshComponent->GetGameObject()) {
                        ImGui::Text("GameObject: %s", pMeshComponent->GetGameObject()->GetName().c_str());
                    }
                    else {
                        ImGui::Text("Geometry: %s", pMesh->GetGeometryName().c_str());
                    }
                    ImGui::Separator();

                    ImGui::TableSetColumnIndex(2);
                    ImGui::Text("Priority: %lli", pMesh->GetSortingPriority());
                    ImGui::Separator();

                    ImGui::TableSetColumnIndex(3);
                    ImGui::Text("%s", pMesh->GetShader() ? pMesh->GetShader()->GetResourceId().data() : "[no shader]");
                    ImGui::Separator();
                }

                ImGui::EndTable();
            }

            ImGui::EndTabItem();
        }
    }
}