//
// Created by Monika on 10.02.2022.
//

#include <Utils/Debug.h>
#include <Utils/Common/Features.h>
#include <Utils/Types/SafePtrLockGuard.h>

#include <Graphics/Render/RenderScene.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/GUI/WidgetManager.h>

namespace SR_GRAPH_NS::GUI {
    WidgetManager::WidgetManager()
        : SR_UTILS_NS::NonCopyable()
        , SR_UTILS_NS::InputHandler()
    {
        m_ignoreNonFocused = SR_UTILS_NS::Features::Instance().Enabled("InputIgnoreNonFocusedWidgets", true);
    }

    void WidgetManager::Draw() {
        SR_SCOPED_LOCK

        for (auto&&[name, widget] : m_widgets) {
            if (widget->IsOpen())
                widget->DrawWindow();
        }
    }

    bool WidgetManager::Register(Widget *widget) {
        SR_SCOPED_LOCK

        if (m_widgets.count(widget->GetName()) == 1) {
            SRHalt("Widget are already registered!");
            return false;
        }

        m_widgets.insert(std::make_pair(widget->GetName(), widget));

        widget->SetManager(this);
        widget->Init();

        return true;
    }

    bool WidgetManager::Remove(Widget *widget) {
        SR_SCOPED_LOCK

        if (m_widgets.count(widget->GetName()) == 0) {
            SRHalt("Widget is not registered!");
            return false;
        }

        m_widgets.erase(widget->GetName());

        widget->SetManager(nullptr);

        return true;
    }

    WidgetManager::~WidgetManager() {
        SRAssert2(m_widgets.empty(), "Memory leak is possible!");
        m_widgets.clear();
    }

    void WidgetManager::OnKeyDown(const SR_UTILS_NS::KeyboardInputData* data) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnKeyDown(data);
        }
    }

    void WidgetManager::OnKeyUp(const SR_UTILS_NS::KeyboardInputData* data) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnKeyUp(data);
        }
    }

    void WidgetManager::OnKeyPress(const SR_UTILS_NS::KeyboardInputData *data) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnKeyPress(data);
        }
    }

    void WidgetManager::OnMouseMove(const SR_UTILS_NS::MouseInputData *data) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnMouseMove(data);
        }
    }

    void WidgetManager::OnMouseUp(const SR_UTILS_NS::MouseInputData *data) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnMouseUp(data);
        }
    }

    void WidgetManager::OnMouseDown(const SR_UTILS_NS::MouseInputData *data) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnMouseDown(data);
        }
    }

    void WidgetManager::OnMousePress(const SR_UTILS_NS::MouseInputData *data) {
        SR_SCOPED_LOCK

        for (auto&&[name, pWidget] : m_widgets) {
            if (pWidget->IsFocused() || !m_ignoreNonFocused)
                pWidget->OnMousePress(data);
        }
    }

    void WidgetManager::SetRenderScene(const WidgetManager::RenderScenePtr& renderScene) {
        m_renderScene = renderScene;
    }

    WidgetManager::RenderScenePtr WidgetManager::GetRenderScene() const {
        return m_renderScene;
    }

    WidgetManager::ContextPtr WidgetManager::GetContext() const {
        if (!m_renderScene) {
            return ContextPtr();
        }

        return m_renderScene->GetContext();
    }

    void WidgetManager::SetScene(const WidgetManager::ScenePtr &scene) {
        SR_LOCK_GUARD

        SR_HTYPES_NS::SafePtrLockGuard<SR_WORLD_NS::Scene::Ptr> lockGuard(scene);

        for (auto&& [id, pWidget] : m_widgets) {
            pWidget->SetScene(scene);
        }
    }

    void WidgetManager::HideAll() {
        for (auto&& widget : ViewportsTableManager::Instance().GetViewportsTable()) {
            ShowWindow((HWND)widget.first->PlatformHandle, SW_HIDE);
        }
    }

    void WidgetManager::ShowAll() {
        for (auto&& widget : ViewportsTableManager::Instance().GetViewportsTable()) {
            ShowWindow((HWND)widget.first->PlatformHandle, SW_SHOW);
        }
    }

    Widget* ViewportsTableManager::GetWidgetByViewport(ImGuiViewport *viewport) const {
        if (m_viewports.count(viewport) == 0) {
            return nullptr;
        }

        return m_viewports.at(viewport);
    }

    void ViewportsTableManager::RegisterWidget(Widget* widget, ImGuiViewport* viewport) {
        m_viewports[viewport] = widget;
    }
}
