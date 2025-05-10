

# File NodeBuilder.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**GUI**](dir_a12e42d7d4180b47da59cbd43b47a80e.md) **>** [**NodeBuilder.h**](NodeBuilder_8h.md)

[Go to the documentation of this file](NodeBuilder_8h.md)


```C++
//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_NODEBUILDER_H
#define SR_ENGINE_NODEBUILDER_H

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

        //void Header(const ImVec4& color = ImVec4(1, 1, 1, 1));
        void EndHeader();

        void Input(Pin* pPin);
        void EndInput();

        void Middle();

        void Output(Pin* pPin);
        void EndOutput();

    private:
        bool SetStage(Stage stage);

        //SR_NODISCARD ImTextureID GetTextureId() const;

    private:
        SR_GTYPES_NS::Texture* m_texture = nullptr;

        uintptr_t m_currentNodeId = 0;

        Node* m_currentNode = nullptr;
        Pin* m_currentPin = nullptr;

        Stage m_currentStage = Stage::Invalid;
        //ImU32 m_headerColor = 0;
//
        //ImVec2 m_headerMin;
        //ImVec2 m_headerMax;

        bool m_hasHeader = false;

    };

}

#endif //SR_ENGINE_NODEBUILDER_H
```


