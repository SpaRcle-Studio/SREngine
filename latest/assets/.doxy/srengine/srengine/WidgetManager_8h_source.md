

# File WidgetManager.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**WidgetManager.h**](WidgetManager_8h.md)

[Go to the documentation of this file](WidgetManager_8h.md)


```C++
//
// Created by Monika on 10.02.2022.
//

#ifndef SR_ENGINE_WIDGETMANAGER_H
#define SR_ENGINE_WIDGETMANAGER_H

#include <Graphics/macros.h>

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

namespace SR_GRAPH_NS::GUI {
    class Widget;

    typedef ska::flat_hash_map<std::string, Widget*> Widgets;
    typedef ska::flat_hash_map<void*, Widget*> ViewportsTable;

    class WidgetManager : public SR_UTILS_NS::NonCopyable, public SR_UTILS_NS::InputHandler {
        using RenderScenePtr = SR_HTYPES_NS::SharedPtr<RenderScene>;
        using ContextPtr = RenderContext*;
        using ScenePtr = SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
    public:
        WidgetManager();
        ~WidgetManager() override;

        virtual void Draw();

        bool Register(Widget* widget);
        bool Remove(Widget* widget);

        void HideAll();
        void ShowAll();

        void SetRenderScene(const RenderScenePtr& renderScene);
        void SetRenderContext(ContextPtr pContext);

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
        ContextPtr m_renderContext = nullptr;
        Widgets m_widgets;
        bool m_ignoreNonFocused;

    };

    class GlobalWidgetManager : public WidgetManager, public SR_UTILS_NS::Singleton<GlobalWidgetManager> {
        SR_REGISTER_SINGLETON(GlobalWidgetManager)
    public:
        ~GlobalWidgetManager() override = default;
    };

    class ViewportsTableManager : public SR_UTILS_NS::Singleton<ViewportsTableManager> {
        SR_REGISTER_SINGLETON(ViewportsTableManager)
    public:
        SR_NODISCARD ViewportsTable& GetViewportsTable() { return m_viewports; }
        SR_NODISCARD Widget* GetWidgetByViewport(void* viewport) const;

        void RegisterWidget(Widget* widget, void* viewport);

    private:
        ViewportsTable m_viewports;
    };
}

#endif //SR_ENGINE_WIDGETMANAGER_H
```


