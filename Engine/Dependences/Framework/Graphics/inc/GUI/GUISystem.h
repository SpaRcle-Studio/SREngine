//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_GUISYSTEM_H
#define GAMEENGINE_GUISYSTEM_H

#include <cstdint>
#include <map>
#include <Math/Vector2.h>
#include <Environment/Environment.h>
#include <EntityComponentSystem/Scene.h>
#include <EntityComponentSystem/Transform.h>

namespace Framework::Graphics::GUI {
    class GUISystem {
    private:
        inline static const ImGuiTreeNodeFlags g_node_flags_with_child    = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        inline static const ImGuiTreeNodeFlags g_node_flags_without_child = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
    private:
        GUISystem() : m_pipeLine(Environment::Get()->GetPipeLine()) {
            m_env = Environment::Get();
        }
        GUISystem(const GUISystem&) = default;
        ~GUISystem() = default;
    public:
        static GUISystem* Get() {
            static GUISystem* guiSystem = nullptr;
            if (!guiSystem)
                guiSystem = new GUISystem();
            return guiSystem;
        }
    private:
        Environment*   m_env          = nullptr;
        const PipeLine m_pipeLine     = PipeLine::Unknown;
        bool           m_shiftPressed = false;
    private:
        static void DrawImage(
                ImTextureID user_texture_id,
                const ImVec2& size,
                const ImVec2& uv0,
                const ImVec2& uv1,
                const ImVec4& tint_col,
                const ImVec4& border_col,
                bool imposition = false);
    public:
        static void DrawTextOnCenter(const std::string& text, bool sameLine = true) {
            float font_size = ImGui::GetFontSize() * text.size() / 2;

            if (sameLine)
                ImGui::SameLine(
                        ImGui::GetWindowSize().x / 2 -
                        font_size + (font_size / 2)
                );

            ImGui::Text("%s", text.c_str());
        }

        void DrawChild(Helper::Types::SafePtr<Helper::GameObject> root);
        void DrawHierarchy(Helper::Types::SafePtr<Helper::Scene> scene);
        void DrawInspector(Helper::Types::SafePtr<Helper::Scene> scene);

        void CheckSelected(const Helper::Types::SafePtr<Helper::GameObject>& gm);

        Helper::Math::Vector2 GetWindowSize() const {
            ImVec2 size = ImGui::GetWindowSize();
            return { (Helper::Math::Unit)size.x, (Helper::Math::Unit)size.y };
        }
        void DrawTexture(Helper::Math::Vector2 winSize, Helper::Math::Vector2 texSize, uint32_t id, bool centralize);
        void BeginDockSpace();
        void EndDockSpace();
        bool BeginWindow(const char* name);
        void EndWindow();
        bool BeginChildWindow(const char* name);
        void EndChildWindow();
    };
}

#endif //GAMEENGINE_GUISYSTEM_H
