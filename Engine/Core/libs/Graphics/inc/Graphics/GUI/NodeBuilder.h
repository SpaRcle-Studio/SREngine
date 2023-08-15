//
// Created by Monika on 14.01.2023.
//

#ifndef SRENGINE_NODEBUILDER_H
#define SRENGINE_NODEBUILDER_H

#include <Graphics/GUI/ImNodeEditorUtils.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_GRAPH_NS::GUI {
    class Node;
    class Pin;
    class Link;

    class NodeBuilder : public SR_UTILS_NS::NonCopyable {
        enum class Stage : uint8_t {
            Invalid,
            Begin,
            Header,
            Content,
            Input,
            Output,
            Middle,
            End
        };
    public:
        explicit NodeBuilder(SR_GTYPES_NS::Texture* pTexture);
        ~NodeBuilder() override;

        void Begin(Node* pNode);
        void End();

        void Header(const ImVec4& color = ImVec4(1, 1, 1, 1));
        void EndHeader();

        void Input(Pin* pPin);
        void EndInput();

        void Middle();

        void Output(Pin* pPin);
        void EndOutput();

    private:
        bool SetStage(Stage stage);

        SR_NODISCARD ImTextureID GetTextureId() const;

    private:
        SR_GTYPES_NS::Texture* m_texture = nullptr;

        uintptr_t m_currentNodeId = 0;

        Node* m_currentNode = nullptr;
        Pin* m_currentPin = nullptr;

        Stage m_currentStage = Stage::Invalid;
        ImU32 m_headerColor = 0;

        ImVec2 m_nodeMin;
        ImVec2 m_nodeMax;
        ImVec2 m_headerMin;
        ImVec2 m_headerMax;
        ImVec2 m_contentMin;
        ImVec2 m_contentMax;

        bool m_hasHeader = false;

    };

}

#endif //SRENGINE_NODEBUILDER_H
