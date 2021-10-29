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
#include <Render/Camera.h>
#include <ImGuizmo.h>
#include <imgui.h>

namespace Framework::Core::GUI {
    class GUISystem {
    private:
        inline static bool Vec4Null(const ImVec4& v1) { return (v1.x == 0) && (v1.y == 0) && (v1.z == 0) && (v1.w == 0); }
    private:
        inline static const ImGuiTreeNodeFlags g_node_flags_with_child    = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
        inline static const ImGuiTreeNodeFlags g_node_flags_without_child = ImGuiTreeNodeFlags_NoTreePushOnOpen | ImGuiTreeNodeFlags_Leaf;
    private:
        GUISystem() : m_pipeLine(Graphics::Environment::Get()->GetPipeLine()) {
            m_env = Graphics::Environment::Get();
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
        inline static const ImVec2 m_sizeB = { 30, 25 };
        inline static const short  m_space = 3;
        inline static const ImVec4 m_def = {0.1, 0.1, 0.1, 0.7};
        inline static const ImVec4 m_act = {0.6, 0.6, 0.6, 0.85};

        int m_snapValue = 100;
    private:
        Graphics::Environment*   m_env          = nullptr;
        const Graphics::PipeLine m_pipeLine     = Graphics::PipeLine::Unknown;
        bool                     m_shiftPressed = false;
        bool                     m_boundsActive = false;
        bool                     m_centerActive = false;

        ImGuizmo::OPERATION m_currentGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
        ImGuizmo::MODE      m_currentGuizmoMode      = ImGuizmo::MODE::LOCAL;
    private:
        bool CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);
        void DrawComponents(const Helper::Types::SafePtr<GameObject>& gameObject);
        static void DrawImage(
                ImTextureID user_texture_id,
                const ImVec2& size,
                const ImVec2& uv0,
                const ImVec2& uv1,
                const ImVec4& tint_col,
                const ImVec4& border_col,
                bool imposition = false);
    public:
        bool ButtonWithId(
                const char* _id,
                const char* label,
                ImVec2 button_size = ImVec2(0, 0),
                ImGuiButtonFlags flags = ImGuiButtonFlags_None,
                bool imposition = false,
                ImVec2 offset = ImVec2(0,0),
                ImVec4 color = ImVec4(0,0,0,0));

        void SetGuizmoTool(uint8_t toolId);

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

        [[nodiscard]] Helper::Math::Vector2 GetWindowSize() const {
            ImVec2 size = ImGui::GetWindowSize();
            return { (Helper::Math::Unit)size.x, (Helper::Math::Unit)size.y };
        }
        void DrawTexture(Helper::Math::Vector2 winSize, Helper::Math::Vector2 texSize, uint32_t id, bool centralize);
        void DrawGuizmo(Graphics::Camera* camera, Helper::Types::SafePtr<Helper::GameObject> gameObject);
        void DrawGuizmoTools();
        void BeginDockSpace();
        void EndDockSpace();
        bool BeginWindow(const char* name);
        void EndWindow();
        bool BeginChildWindow(const char* name);
        void EndChildWindow();
        bool BeginMenuBar();
        void EndMenuBar();
    };
}

#endif //GAMEENGINE_GUISYSTEM_H
