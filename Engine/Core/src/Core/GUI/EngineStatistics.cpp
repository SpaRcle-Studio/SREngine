//
// Created by Monika on 26.03.2022.
//

#include <Core/GUI/EngineStatistics.h>

#include <Utils/ResourceManager/ResourceManager.h>

namespace Framework::Core::GUI {
    EngineStatistics::EngineStatistics()
        : Graphics::GUI::Widget("Engine statistics")
    { }

    void EngineStatistics::Draw() {
        if (ImGui::BeginTabBar("EngineStatsTabBar")) {
            ImGui::Separator();

            ResourcesPage();
            ThreadsPage();

            ImGui::EndTabBar();
        }
    }

    void EngineStatistics::ResourcesPage() {
        if (ImGui::BeginTabItem("Resources manager")) {
            auto&& drawResource = [=](SR_UTILS_NS::IResource* pRes, uint32_t index) {
                const bool isDestroyed = pRes->IsDestroyed();

                std::string node = Helper::Format("[%u] %s = %u", index, pRes->GetResourceId().data(), pRes->GetCountUses());

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

                const auto node = Helper::Format("[%u] %s (%u)", index, (*resources.begin())->GetResourceId().data(), resources.size());

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
            ImGui::Text("Thread 1");
            ImGui::Text("Thread 2");
            ImGui::Text("Thread 3");
            ImGui::Text("Thread 4");
            ImGui::EndTabItem();
        }
    }
}