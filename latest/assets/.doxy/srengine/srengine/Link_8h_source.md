

# File Link.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**GUI**](dir_271010341ad15844ff85fbf4e71592f2.md) **>** [**Link.h**](Link_8h.md)

[Go to the documentation of this file](Link_8h.md)


```C++
//
// Created by Monika on 18.01.2022.
//

#ifndef SR_ENGINE_LINK_H
#define SR_ENGINE_LINK_H

#include <Utils/Common/Enumerations.h>
#include <Graphics/GUI/Icons.h>

namespace SR_GRAPH_NS::GUI {
    class Pin;

    class Link : private SR_UTILS_NS::NonCopyable {
    public:
        Link();
        Link(Pin* start, Pin* end);
//        Link(Pin* start, Pin* end, ImColor color);
        ~Link() override;

    public:
        SR_NODISCARD uintptr_t GetId() const;
        SR_NODISCARD bool IsLinked(Pin* pPin) const;
        SR_NODISCARD bool IsLinked() const { return m_endPin && m_startPin; }
        SR_NODISCARD Pin* GetStart() const { return m_startPin; }
        SR_NODISCARD Pin* GetEnd() const { return m_endPin; }

        void SetStart(Pin* pPin);
        void SetEnd(Pin* pPin);

        void Draw() const;
        void Broke(Pin* pFrom);

    private:
        Pin* m_startPin = nullptr;
        Pin* m_endPin = nullptr;

       // ImColor m_color;

    };
}

#endif //SR_ENGINE_LINK_H
```


