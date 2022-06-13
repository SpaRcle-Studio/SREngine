//
// Created by Monika on 27.07.2021.
//

#ifndef FBXLOADER_PARSER_H
#define FBXLOADER_PARSER_H

#include <FbxLoader/Debug.h>

#include <string>
#include <vector>
#include <iostream>

namespace FbxLoader::Parser {
    struct Node {
        ~Node() {
            for (auto node : nodes)
                delete node;
            parent = nullptr;
        }

        [[nodiscard]] Node* Find(const std::string& _value) const {
            for (auto node : nodes)
                if (node->value == _value)
                    return node;
            return nullptr;
        }

        [[nodiscard]] std::string GetSubNodeValue() const {
            return (*nodes.begin())->value;
        }

        [[nodiscard]] Node* Get2SubNode() const {
#ifdef _DEBUG
            if (nodes.empty()) {
                FBX_ERROR("Node::Get2SubNode() : nodes is empty!");
                return nullptr;
            }

            if (nodes[0]->nodes.empty()) {
                FBX_ERROR("Node::Get2SubNode() : sub nodes is empty!");
                return nullptr;
            }

            return nodes[0]->nodes[0];
#else
            return nodes[0]->nodes[0];
#endif
        }

        std::vector<Node*> nodes;
        std::string value;
        std::string subData;
        Node* parent;
    };

    enum class Operation {
        Unknown, Value, Open, Close
    };

    inline static Operation MathOperation(int32_t a, int32_t b, int32_t c) {
        if (a < b && a < c)
            return Operation::Value;
        else if (b < a && b < c)
            return Operation::Open;
        else
            return Operation::Close;
    }

    Node* Parse(const std::string& text);
}

#endif //FBXLOADER_PARSER_H
