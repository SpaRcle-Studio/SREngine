//
// Created by Nikita on 19.07.2021.
//

#ifndef GAMEENGINE_GUISYSTEM_H
#define GAMEENGINE_GUISYSTEM_H

#include <cstdint>
#include <map>
#include <Math/Vector2.h>
#include <Environment/Environment.h>

namespace Framework::Graphics::GUI {
    class GUISystem {
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
        Environment*              m_env          = nullptr;
        const PipeLine            m_pipeLine     = PipeLine::Unknown;
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
