//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_GUISYSTEM_H
#define GAMEENGINE_GUISYSTEM_H

#include <Environment/Environment.h>
#include <Utils/Math/Vector2.h>
#include <Utils/World/Scene.h>
#include <Render/Camera.h>
#include <Utils/Common/Singleton.h>
#include <Utils/ECS/GameObject.h>

namespace Framework::Core::GUI {
    class GUISystem : public SR_UTILS_NS::Singleton<GUISystem> {
        friend class Singleton<GUISystem>;
    private:
        GUISystem() : m_pipeLine(Graphics::Environment::Get()->GetPipeLine()) {
            m_env = Graphics::Environment::Get();
        }
        ~GUISystem() = default;

    private:
        float_t m_bounds[6] = { -0.5f, -0.5f, -0.5f, 0.5f, 0.5f, 0.5f };
        float_t m_boundsSnap[3] = { 0.1f, 0.1f, 0.1f };

        int32_t                  m_snapValue    = 100;
        Graphics::Environment*   m_env          = nullptr;
        const Graphics::PipeLine m_pipeLine     = Graphics::PipeLine::Unknown;
        bool                     m_shiftPressed = false;
        bool                     m_boundsActive = false;
        bool                     m_centerActive = false;
        bool                     m_snapActive   = false;

        ImGuizmo::OPERATION m_currentGuizmoOperation = ImGuizmo::OPERATION::TRANSLATE;
        ImGuizmo::MODE      m_currentGuizmoMode      = ImGuizmo::MODE::LOCAL;

    private:
        bool CollapsingHeader(const char* label, ImGuiTreeNodeFlags flags = 0);
        void DrawComponents(const SR_HTYPES_NS::SafePtr<SR_UTILS_NS::GameObject>& gameObject);
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

        static inline int ImTextCharToUtf8(char* buf, int buf_size, unsigned int c) {
            if (c < 0x80)
            {
                buf[0] = (char)c;
                return 1;
            }
            if (c < 0x800)
            {
                if (buf_size < 2) return 0;
                buf[0] = (char)(0xc0 + (c >> 6));
                buf[1] = (char)(0x80 + (c & 0x3f));
                return 2;
            }
            if (c < 0x10000)
            {
                if (buf_size < 3) return 0;
                buf[0] = (char)(0xe0 + (c >> 12));
                buf[1] = (char)(0x80 + ((c >> 6) & 0x3f));
                buf[2] = (char)(0x80 + ((c ) & 0x3f));
                return 3;
            }
            if (c <= 0x10FFFF)
            {
                if (buf_size < 4) return 0;
                buf[0] = (char)(0xf0 + (c >> 18));
                buf[1] = (char)(0x80 + ((c >> 12) & 0x3f));
                buf[2] = (char)(0x80 + ((c >> 6) & 0x3f));
                buf[3] = (char)(0x80 + ((c ) & 0x3f));
                return 4;
            }
            // Invalid code point, the max unicode is 0x10FFFF
            return 0;
        }

        static void DrawTextOnCenter(const std::string& text, bool sameLine = true) {
            float font_size = ImGui::GetFontSize() * text.size() / 2;

            if (sameLine)
                ImGui::SameLine(
                        ImGui::GetWindowSize().x / 2 -
                        font_size + (font_size / 2)
                );

            ImGui::Text("%s", text.c_str());
        }

        void DrawInspector(Helper::Types::SafePtr<Helper::World::Scene> scene);
        void DrawWorldEdit(Helper::Types::SafePtr<Helper::World::Scene> scene);

        void CheckSelected(const Helper::Types::SafePtr<Helper::GameObject>& gm) const;

        [[nodiscard]] Helper::Math::IVector2 GetWindowSize() const {
            ImVec2 size = ImGui::GetWindowSize();
            return { (int32_t)size.x, (int32_t)size.y };
        }
        bool ImageButton(std::string_view&& id, void* descriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding, ImGuiButtonFlags flags);
        bool ImageButtonDouble(std::string_view&& id, void* descriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding);
        bool ImageButton(std::string_view&& id, void* descriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding);
        bool ImageButton(void* descriptor, const SR_MATH_NS::IVector2& size, int32_t framePadding);
        bool ImageButton(void* descriptor, const SR_MATH_NS::IVector2& size);
        void DrawTexture(void* descriptor, const SR_MATH_NS::IVector2& size);
        void DrawTexture(Helper::Math::IVector2 winSize, Helper::Math::IVector2 texSize, uint32_t id, bool centralize);
        void DrawGuizmo(Graphics::Camera* camera, Helper::Types::SafePtr<Helper::GameObject> gameObject);
        void DrawGuizmoTools();
        bool BeginDockSpace();
        bool BeginWindow(const char* name);
        void EndWindow();
        bool BeginChildWindow(const char* name);
        void EndChildWindow();
        bool BeginMenuBar();
        void EndMenuBar();
    };
}

#endif //GAMEENGINE_GUISYSTEM_H
