//
// Created by Monika on 03.09.2021.
//

#ifndef GAMEENGINE_XML_H
#define GAMEENGINE_XML_H

#include <Debug.h>
#include <pugixml.hpp>
#include <vector>
#include <cmath>

namespace Framework::Helper {
    namespace Xml {
        class Node;
        class Attribute;

        static int32_t g_xml_last_error = 0;

        class Attribute {
        public:
            explicit Attribute(const pugi::xml_attribute &attribute) {
                m_attribute = attribute;
                m_valid = !m_attribute.empty();
            }

        private:
            pugi::xml_attribute m_attribute;
            bool m_valid;
        private:
            [[nodiscard]] bool CheckError(const std::string &msg) const {
                if (m_valid)
                    return true;
                else {
                    Helper::Debug::Error(msg);
                    g_xml_last_error = -1;
                    return false;
                }
            }

        public:
            explicit operator bool() const {
                return Valid();
            }

            [[nodiscard]] bool Valid() const {
                return m_valid;
            }

            [[nodiscard]] std::string ToString() const;

            [[nodiscard]] int32_t ToInt() const;

            [[nodiscard]] int32_t ToFloat() const;

            [[nodiscard]] int32_t ToBool() const;
        };

        class Node {
            friend class Document;

        private:
            Node() {
                m_node = {};
                m_valid = false;
            }

            explicit Node(const pugi::xml_node &node) {
                m_node = node;
                m_valid = !node.empty();
            }

        private:
            pugi::xml_node m_node;
            bool m_valid;
        public:
            static Node Empty() {
                return Node();
            }
        public:
            explicit operator bool() const {
                return Valid();
            }
        public:
            [[nodiscard]] bool Valid() const {
                return m_valid;
            }

            [[nodiscard]] std::string Name() const {
                if (!m_valid) {
                    Helper::Debug::Error("Node::Name() : node is not valid!");
                    g_xml_last_error = -4;
                    return {};
                }

                return m_node.name();
            }

            [[nodiscard]] Attribute GetAttribute(const std::string &name) const {
                return Attribute(m_node.attribute(name.c_str()));
            }

            [[nodiscard]] std::vector<Node> GetNodes(const std::string &name) const {
                if (!m_valid) {
                    Helper::Debug::Error("Node::GetNodes() : node is not valid!");
                    g_xml_last_error = -2;
                    return {};
                }

                auto nodes = std::vector<Node>();
                for (const auto child : m_node.children())
                    if (std::string(child.name()) == name)
                        nodes.emplace_back(Node(child));

                return nodes;
            }

            [[nodiscard]] std::vector<Node> GetNodes() const {
                if (!m_valid) {
                    Helper::Debug::Error("Node::GetNodes() : node is not valid!");
                    g_xml_last_error = -2;
                    return {};
                }

                auto nodes = std::vector<Node>();
                for (const auto child : m_node.children())
                    nodes.emplace_back(Node(child));

                return nodes;
            }

            template<typename T> bool AppendAttribute(const std::string &name, const T& value)  {
                if (!m_valid) {
                    Helper::Debug::Error("Node::AddAttribute() : node is not valid!");
                    g_xml_last_error = -2;
                    return false;
                }

                if (auto attrib = m_node.append_attribute(name.c_str()); !attrib.empty()) {
                    attrib.set_value(value);
                    return true;
                }

                return false;
            }


            Node AppendChild(const std::string& name) {
                if (!m_valid) {
                    Helper::Debug::Error("Node::AppendChild() : node is not valid!");
                    g_xml_last_error = -2;
                    return Node();
                }

                return Node(m_node.append_child(name.c_str()));
            }

            [[nodiscard]] Node GetNode(const std::string &name) const {
                if (!m_valid) {
                    Helper::Debug::Error("Node::GetNode() : node is not valid!");
                    g_xml_last_error = -2;
                    return Node();
                }

                return Node(m_node.child(name.c_str()));
            }
        };

        class Document {
        private:
            Document() {
                m_document = {};
                m_valid = false;
            }
        private:
            pugi::xml_document m_document;
            bool               m_valid;
            std::string        m_path;
        public:
            static Document Empty() {
                return Document();
            }

            static Document New() {
                auto xml = Document();
                xml.m_valid = true;
                xml.m_path = "None";
                xml.m_document = pugi::xml_document();
                return xml;
            }

            static Document Load(const std::string& path);
            static int32_t GetLastError() {
                auto last = Xml::g_xml_last_error;
                Xml::g_xml_last_error = 0;
                return last;
            }
        public:
            bool Save(const std::string& path) const {
                return m_document.save_file(path.c_str());
            }
            [[nodiscard]] Node Root() const {
                return Node(m_document.root());
            }
            [[nodiscard]] bool Valid() const { return m_valid; }
        };
    }
}

#endif //GAMEENGINE_XML_H
