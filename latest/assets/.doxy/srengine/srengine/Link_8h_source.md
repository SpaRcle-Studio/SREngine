

# File Link.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**Link.h**](Link_8h.md)

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


