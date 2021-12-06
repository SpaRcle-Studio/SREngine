//
// Created by Monika on 27.07.2021.
//

#include <FbxLoader/Parser.h>

FbxLoader::Parser::Node *FbxLoader::Parser::Parse(const std::string &text)  {
    Node* node = new Node { {}, "Fbx", "", nullptr };
    Node* currNode = node;

    uint64_t pos = 1;

    uint64_t oldValue = 0;
    Operation oldOperation = Operation::Unknown;

    while (true) {
        auto value = text.find(": ", pos);
        auto open  = text.find('{', pos);
        auto close = text.find('}', pos);

        if (open == std::string::npos)
            break;

        auto operation = MathOperation(value, open, close);
        switch (operation) {
            case Operation::Value: {
                std::string subData;

                if (oldOperation == Operation::Value) {
                    uint32_t space = text.rfind(' ', value);
                    uint32_t count = (space - oldValue) - 2;

                    auto subNode = new Node { {}, text.substr(oldValue + 2, count), "", (*(currNode->nodes.end() - 1)) };
                    (*(currNode->nodes.end() - 1))->nodes.emplace_back(subNode);

                    pos += count + 2;
                } else if (open - value > 2)
                    if (auto nextVal = text.find(": ", value + 1); nextVal > open) {
                        uint32_t count = (open - value) - 2;
                        subData = text.substr(value + 2, count);
                    }

                currNode->nodes.emplace_back(new Node{{}, text.substr(pos, value - pos), subData, currNode});

                pos = value + 1;
                oldValue = value;
                break;
            }
            case Operation::Open:
                pos = open + 2;
                currNode = *(currNode->nodes.end() - 1);
                break;
            case Operation::Close:
                if (oldOperation == Operation::Value) {
                    uint32_t count = (close - oldValue) - 3;
                    auto subNode = new Node { {}, text.substr(oldValue + 2, count), "", (*(currNode->nodes.end() - 1)) };
                    (*(currNode->nodes.end() - 1))->nodes.emplace_back(subNode);
                }

                currNode = currNode->parent;
                pos = close + 2;
                break;
            case Operation::Unknown:
                break;
        }

        oldOperation = operation;
    }

    return node;
}
