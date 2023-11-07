//
// Created by innerviewer on 06/11/23.
//

#ifndef SRENGINE_X11WINDOW_H
#define SRENGINE_X11WINDOW_H

#include <Graphics/Window/BasicWindowImpl.h>
#include <xcb/xcb.h>

namespace SR_GRAPH_NS {
    class X11Window : public BasicWindowImpl {
        using Super = BasicWindowImpl;
    public:
        explicit X11Window()
                : Super()
        { }

    public:
        bool Initialize(const std::string& name,
                        const SR_MATH_NS::IVector2& position,
                        const SR_MATH_NS::UVector2& size,
                        bool fullScreen, bool resizable) override;

        SR_NODISCARD WindowType GetType() const override { return BasicWindowImpl::WindowType::X11; }
    public:
        //void PollEvents() const override;

        //void Close() override;
        //void Maximize() override;
        //void Restore() override;
        //void Collapse() override;
        //void Expand() override;
        //void Centralize() override;

        SR_NODISCARD void* GetHandle() const override;
        SR_NODISCARD xcb_connection_t* GetConnection() const;
        SR_NODISCARD uint32_t GetWindow() const;
        SR_NODISCARD void* GetDisplay() const;


        void SetResizable(bool resizable) const;
        void SetFullscreen(bool fullscreen) const;
        //void SetHeaderEnabled(bool enable) override;
        //void SetIcon(const std::string& path) override;
        //void Move(int32_t x, int32_t y) override;
        //void Resize(uint32_t w, uint32_t h) override;
    private:
        void* m_display = nullptr;
        uint32_t m_window = 0;
        xcb_connection_t* m_connection = nullptr;

    };
}

#endif //SRENGINE_X11WINDOW_H
