//
// Created by Monika on 14.01.2023.
//

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/Types/Texture.h>

namespace SR_GRAPH_NS::GUI {
    NodeWidget::NodeWidget(std::string name, SR_MATH_NS::IVector2 size)
        : Super(std::move(name), size)
    {
        auto&& texturePath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat("Editor/Textures/BlueprintBackground.png");
        m_nodeBuilder = new NodeBuilder(SR_GTYPES_NS::Texture::Load(texturePath));
    }

    NodeWidget::~NodeWidget() {
        Clear();
        delete m_nodeBuilder;
    }

    void NodeWidget::UpdateTouch() {
        const auto deltaTime = ImGui::GetIO().DeltaTime;
        for (auto &&entry : m_nodeTouchTime) {
            if (entry.second > 0.0f) {
                entry.second -= deltaTime;
            }
        }
    }

    void NodeWidget::Clear() {
        for (auto&& [id, pLink] : m_links) {
            delete pLink;
        }

        for (auto&& [id, pNode] : m_nodes) {
            delete pNode;
        }

        m_nodes.clear();
        m_links.clear();
    }

    Node& NodeWidget::AddNode(Node* pNode) {
        if (!pNode) {
            SRHalt0();
            static Node def;
            return def;
        }

        SRAssert(m_nodes.count(pNode->GetId()) == 0);
        m_nodes.insert(std::make_pair(pNode->GetId(), pNode));

        return *pNode;
    }

    Link& NodeWidget::AddLink(Link* pLink) {
        if (!pLink) {
            SRHalt0();
            static Link def;
            return def;
        }

        SRAssert(m_links.count(pLink->GetId()) == 0);
        m_links.insert(std::make_pair(pLink->GetId(), pLink));

        return *pLink;
    }
}
