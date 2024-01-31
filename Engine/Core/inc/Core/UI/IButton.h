//
// Created by innerviewer on 2024-01-12.
//
#ifndef SR_ENGINE_IBUTTON_H
#define SR_ENGINE_IBUTTON_H

#include <Graphics/Types/IRenderComponent.h>

#include <utility>

namespace SR_GRAPH_NS {
    class RenderScene;
    class IColorBufferPass;
}

namespace SR_CORE_UI_NS {
    SR_ENUM_NS_STRUCT_T(ButtonState, uint8_t,
       Idle = 1 << 0,
       Hovered = 1 << 1,
       Pressed = 1 << 2);

    class IButton : public SR_GTYPES_NS::IRenderComponent {
        using Super = SR_GTYPES_NS::IRenderComponent;
        using RenderScenePtr = SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderScene>;
        using Callback = std::function<void()>;
    public:
        IButton();

    public:
        void Update(float_t dt) override;

        SR_NODISCARD ButtonStateFlag GetState() const { return m_state; }
        SR_NODISCARD bool IsIdle() const { return m_state & ButtonState::Idle; }
        SR_NODISCARD bool IsHovered() const { return m_state & ButtonState::Hovered; }
        SR_NODISCARD bool IsPressed() const { return m_state & ButtonState::Pressed; }

        void SetIdleCallback(Callback idleCallback) { m_onIdle = std::move(idleCallback);}
        void SetHoverCallback(Callback hoverCallback) { m_onHover = std::move(hoverCallback);}
        void SetKeyDownCallback(Callback keyDownCallback) { m_onKeyDown = std::move(keyDownCallback);}
        void SetKeyUpCallback(Callback keyUpCallback) { m_onKeyUp = std::move(keyUpCallback);}

    protected:
        virtual void OnIdle();
        virtual void OnHover();
        virtual void OnKeyDown();
        virtual void OnKeyUp();

        SR_NODISCARD SR_FORCE_INLINE bool ExecuteInEditMode() const override { return true; }
        SR_NODISCARD bool InitializeEntity() noexcept override;

    private:
        ButtonStateFlag m_state = ButtonState::Idle;
        ButtonStateFlag m_previousState = ButtonState::Idle;

        Callback m_onIdle;
        Callback m_onHover;
        Callback m_onKeyDown;
        Callback m_onKeyUp;
    };
}

#endif //SR_ENGINE_IBUTTON_H
