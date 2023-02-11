//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGET_H
#define SRENGINE_WIDGET_H

#include <Utils/GUI.h>

#include <Utils/Common/NonCopyable.h>
#include <Utils/Types/DataStorage.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Input/InputHandler.h>

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
}

namespace SR_GRAPH_NS::GUI {
    class WidgetManager;
    typedef ImGuiWindowFlags WindowFlags;

    enum WidgetFlags : uint32_t {
        WIDGET_FLAG_NONE         = 1 << 0,
        WIDGET_FLAG_HOVERED      = 1 << 1,
        WIDGET_FLAG_FOCUSED      = 1 << 2,
    };
    typedef uint32_t WidgetFlagBits;

    class Widget : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::InputHandler {
        friend class WidgetManager;
    public:
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using ContextPtr = RenderContext*;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;

    public:
        explicit Widget(std::string name, SR_MATH_NS::IVector2 size = SR_MATH_NS::IVector2MAX)
            : m_name(std::move(name))
            , m_open(false)
            , m_center(false)
            , m_internalFlags(WIDGET_FLAG_NONE)
            , m_windowFlags(ImGuiWindowFlags_::ImGuiWindowFlags_None)
            , m_size(size)
            , m_manager(nullptr)
            , m_widgetFlags(WIDGET_FLAG_NONE)
        { }

        ~Widget() override = default;

    public:
        SR_NODISCARD bool IsOpen() const { return m_open; }
        SR_NODISCARD bool IsFocused() const { return m_internalFlags & WIDGET_FLAG_FOCUSED; }
        SR_NODISCARD bool IsHovered() const { return m_internalFlags & WIDGET_FLAG_HOVERED; }
        SR_NODISCARD WidgetManager* GetManager() const { return m_manager; }
        SR_NODISCARD std::string GetName() const { return m_name; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD ContextPtr GetContext() const;
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetWeakStorage() const { return m_weakStorage; }
        SR_NODISCARD SR_HTYPES_NS::DataStorage& GetStrongStorage() const { return m_strongStorage; }

        virtual void Open();
        virtual void Close();

        virtual void SetScene(const ScenePtr& scene) { }

        void DrawAsSubWindow();

    protected:
        virtual void Draw() = 0;
        virtual void OnClose() { }
        virtual void OnOpen() { }

        void SetCenter(bool value) { m_center = value; }
        void SetName(const std::string& name) { m_name = name; }
        void SetFlags(WindowFlags flags) { m_windowFlags = flags; }

        void TextCenter(const std::string& text) const;

        void ResetWeakStorage();
        void ResetStrongStorage();

        void CheckFocused();
        void CheckHovered();

    private:
        void SetManager(WidgetManager* manager);

        void InternalCheckFocused();
        void InternalCheckHovered();
        void DrawWindow();

    private:
        std::string m_name;
        std::atomic<bool> m_open;
        std::atomic<bool> m_center;
        std::atomic<WidgetFlagBits> m_internalFlags;
        WindowFlags m_windowFlags;
        SR_MATH_NS::IVector2 m_size;
        WidgetManager* m_manager;

        mutable SR_HTYPES_NS::DataStorage m_weakStorage;
        mutable SR_HTYPES_NS::DataStorage m_strongStorage;

    protected:
        mutable std::recursive_mutex m_mutex;
        WidgetFlagBits m_widgetFlags;

    };
}

#endif //SRENGINE_WIDGET_H
