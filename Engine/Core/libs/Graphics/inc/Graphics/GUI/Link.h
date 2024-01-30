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
        Link(Pin* start, Pin* end, ImColor color);
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

        ImColor m_color;

    };
}

#endif //SR_ENGINE_LINK_H
