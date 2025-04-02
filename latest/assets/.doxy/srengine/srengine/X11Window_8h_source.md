

# File X11Window.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Window**](dir_eceba3be4a9ee281baac1dc94ed42c6c.md) **>** [**X11Window.h**](X11Window_8h.md)

[Go to the documentation of this file](X11Window_8h.md)


```C++
//
// Created by innerviewer on 06/11/23.
//

#ifndef SR_ENGINE_X11WINDOW_H
#define SR_ENGINE_X11WINDOW_H

#include <Graphics/Window/BasicWindowImpl.h>

#include <xcb/xcb.h>

namespace SR_GRAPH_NS {
/*    class X11Window : public BasicWindowImpl {
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
        void PollEvents() override;

        xcb_intern_atom_reply_t* ChangeWMProperty(const std::string& atomName);
        xcb_intern_atom_reply_t* ChangeAtom(const std::string& propertyName, const std::string& atomName);
        std::vector<xcb_intern_atom_reply_t*> ChangeAtoms(const std::string& propertyName, const std::vector<std::string>& atomNames);

        void Close() override;
        //void Maximize() override;
        //void Restore() override;
        //void Collapse() override;
        //void Expand() override;
        //void Centralize() override;

        SR_NODISCARD void* GetHandle() const override;
        SR_NODISCARD xcb_connection_t* GetConnection() const;
        SR_NODISCARD uint32_t GetWindow() const;
        SR_NODISCARD void* GetDisplay() const;
        SR_NODISCARD SR_MATH_NS::IVector2 GetScreenResolution() const override;

        void SetResizable(bool resizable) const;
        void SetFullscreen(bool fullscreen) const;
        //void SetHeaderEnabled(bool enable) override;
        //void SetIcon(const std::string& path) override;
        //void Move(int32_t x, int32_t y) override;
        //void Resize(uint32_t w, uint32_t h) override;
    private:
        void PollEventsHandler();

    private:
        void* m_display = nullptr;
        uint32_t m_window = 0;
        xcb_connection_t* m_connection = nullptr;

        xcb_intern_atom_reply_t* m_deleteWindowReply = nullptr;
        xcb_intern_atom_reply_t* m_wmProtocols = nullptr;
    };*/
}

#endif //SR_ENGINE_X11WINDOW_H
```


