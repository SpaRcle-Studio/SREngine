//
// Created by Monika on 10.02.2022.
//

#ifndef SRENGINE_WIDGETMANAGER_H
#define SRENGINE_WIDGETMANAGER_H

#include <Utils/Types/Thread.h>
#include <Utils/Types/SafePointer.h>
#include <Utils/Input/InputHandler.h>
#include <Utils/Input/InputSystem.h>
#include <Utils/Types/SafePointer.h>

namespace SR_WORLD_NS {
    class Scene;
}

namespace SR_GRAPH_NS {
    class RenderScene;
    class RenderContext;
}

struct ImGuiViewport;

namespace SR_GRAPH_NS::GUI {
    class Widget;

    typedef ska::flat_hash_map<std::string, Widget*> Widgets;
    typedef ska::flat_hash_map<ImGuiViewport*, Widget*> ViewportsTable;

    class WidgetManager : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::InputHandler {
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<RenderScene>;
        using ContextPtr = RenderContext*;
        using ScenePtr = SR_HTYPES_NS::SafePtr<SR_WORLD_NS::Scene>;
    public:
        WidgetManager();
        ~WidgetManager() override;

        virtual void Draw();

        bool Register(Widget* widget);
        bool Remove(Widget* widget);

        void HideAll();
        void ShowAll();

        void SetRenderScene(const RenderScenePtr& renderScene);

    public:
        SR_NODISCARD Widgets& GetWidgets() { return m_widgets; }
        SR_NODISCARD RenderScenePtr GetRenderScene() const;
        SR_NODISCARD ContextPtr GetContext() const;

        template<typename T> T* GetWidget() const {
            for (auto&& widget : m_widgets) {
                if (auto&& pWidget = dynamic_cast<T*>(widget.second)) {
                    return dynamic_cast<T*>(widget.second);
                }
            }

            SRHalt("WidgetManager::GetWidget() : unable to find widget!");
            return nullptr;
        }

        void OnMouseMove(const SR_UTILS_NS::MouseInputData* data) override;
        void OnMousePress(const SR_UTILS_NS::MouseInputData* data) override;
        void OnMouseDown(const SR_UTILS_NS::MouseInputData* data) override;
        void OnMouseUp(const SR_UTILS_NS::MouseInputData* data) override;

        void OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) override;
        void OnKeyPress(const SR_UTILS_NS::KeyboardInputData* data) override;

        void SetScene(const ScenePtr& scene);

    protected:
        mutable std::recursive_mutex m_mutex;

    private:
        RenderScenePtr m_renderScene;
        Widgets m_widgets;
        bool m_ignoreNonFocused;

    };

    class GlobalWidgetManager : public WidgetManager, public SR_UTILS_NS::Singleton<GlobalWidgetManager> {
        friend class SR_UTILS_NS::Singleton<GlobalWidgetManager>;
    public:
        ~GlobalWidgetManager() override = default;
    };

    class ViewportsTableManager : public SR_UTILS_NS::Singleton<ViewportsTableManager> {
    public:
        SR_NODISCARD ViewportsTable& GetViewportsTable() { return m_viewports; }
        SR_NODISCARD Widget* GetWidgetByViewport(ImGuiViewport* viewport) const;

        void RegisterWidget(Widget* widget, ImGuiViewport* viewport);

    private:
        ViewportsTable m_viewports;
    };
}

#endif //SRENGINE_WIDGETMANAGER_H
