//
// Created by Monika on 18.01.2022.
//

#ifndef SRENGINE_LINK_H
#define SRENGINE_LINK_H

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
        [[nodiscard]] uintptr_t GetId() const;
        [[nodiscard]] bool Valid() const;

        void Draw() const;

    private:
        ax::NodeEditor::LinkId m_id;

        Pin* m_startPin;
        Pin* m_endPin;

        ImColor m_color;

    };
}

#endif //SRENGINE_LINK_H
