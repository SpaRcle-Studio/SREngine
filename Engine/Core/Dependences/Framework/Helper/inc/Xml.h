//
// Created by Monika on 03.09.2021.
//

#ifndef GAMEENGINE_XML_H
#define GAMEENGINE_XML_H

#include <Debug.h>
#include <pugixml.hpp>
#include <vector>
#include <cmath>

namespace Framework::Helper::Xml {
        class Node;
        class Attribute;

        static int32_t g_xml_last_error = 0;

        class Attribute {
        public:
            Attribute()
                : m_attribute()
                , m_valid(false)
            { }

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
                    SRAssert2(false, msg);
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
            [[nodiscard]] float_t ToFloat() const;
            [[nodiscard]] bool ToBool() const;

            [[nodiscard]] std::string ToString(const std::string& def) const;
            [[nodiscard]] int32_t ToInt(int32_t def) const;
            [[nodiscard]] float_t ToFloat(float_t def) const;
            [[nodiscard]] bool ToBool(bool def) const;
        };

        class Node {
            friend class Document;

        public:
            Node();

            explicit Node(const pugi::xml_node &node) {
                m_node = node;
                m_valid = !node.empty();
            }

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
                    SRAssert2(false,"Node::Name() : node is not valid!");
                    g_xml_last_error = -4;
                    return {};
                }

                return m_node.name();
            }

            [[nodiscard]] Attribute GetAttribute(const std::string &name) const {
                if (!m_valid) {
                    SRAssert2(false,"Node::GetAttribute() : node is not valid!");
                    g_xml_last_error = -4;
                    return Attribute();
                }

                return Attribute(m_node.attribute(name.c_str()));
            }

            [[nodiscard]] Attribute TryGetAttribute(const std::string &name) const {
                return m_valid ? Attribute(m_node.attribute(name.c_str())) : Attribute();
            }

            [[nodiscard]] std::vector<Node> GetNodes(const std::string &name) const;
            [[nodiscard]] std::vector<Node> GetNodes() const;

            template<typename T> bool AppendAttribute(const std::string &name, const T& value)  {
                if (!m_valid) {
                    SRAssert2(false,"Node::AddAttribute() : node is not valid!");
                    g_xml_last_error = -2;
                    return false;
                }

                if (auto attrib = m_node.append_attribute(name.c_str()); !attrib.empty()) {
                    attrib.set_value(value);
                    return true;
                }

                return false;
            }


            Node AppendChild(const std::string& name);

            [[nodiscard]] Node TryGetNode(const std::string &name) const {
                return m_valid ? Node(m_node.child(name.c_str())) : Node();
            }

            [[nodiscard]] Node GetNode(const std::string &name) const {
                if (!m_valid) {
                    SRAssert2(false, "Node::GetNode() : node is not valid!");
                    g_xml_last_error = -2;
                    return Node();
                }

                return Node(m_node.child(name.c_str()));
            }

        private:
            pugi::xml_node m_node;
            bool m_valid;

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

#endif //GAMEENGINE_XML_H
