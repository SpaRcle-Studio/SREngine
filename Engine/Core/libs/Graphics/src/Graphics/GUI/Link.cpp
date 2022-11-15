//
// Created by Monika on 18.01.2022.
//

#include <Graphics/GUI/Link.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/NodeManager.h>

using namespace SR_GRAPH_NS::GUI;

uintptr_t Link::GetId() const {
    //return m_id.Get();
    return 0;
}

void Link::Draw() const {
    //ax::NodeEditor::Link(m_id, m_startPin->m_id, m_endPin->m_id);
}

Link::Link()
    : Link(nullptr, nullptr, ImColor(255, 255, 255, 255))
{ }

Link::Link(Pin* start, Pin* end)
    : Link(start, end, ImColor(255, 255, 255, 255))
{ }

Link::Link(Pin* start, Pin* end, ImColor color)
    : m_startPin(start)
    , m_endPin(end)
    , m_color(color)
{
    if (m_startPin)
        m_startPin->AddLink(this);

    if (m_endPin)
        m_endPin->AddLink(this);

    //m_id = NodeManager::Instance().AllocUniqueId(this);
}

Link::~Link() {
    //if (Valid())
    //    NodeManager::Instance().FreeUniqueId(m_id.Get());

    if (m_startPin) {
        m_startPin->RemoveLink(this);
        m_startPin = nullptr;
    }

    if (m_endPin) {
        m_endPin->RemoveLink(this);
        m_endPin = nullptr;
    }
}

bool Link::Valid() const {
    //return m_id != ax::NodeEditor::LinkId::Invalid;
    return false;
}