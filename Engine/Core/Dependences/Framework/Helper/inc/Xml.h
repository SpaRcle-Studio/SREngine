//
// Created by Monika on 03.09.2021.
//

#ifndef GAMEENGINE_XML_H
#define GAMEENGINE_XML_H

#include <Debug.h>
#include <pugixml.hpp>
#include <vector>
#include <cmath>
#include <FileSystem/Path.h>
#include <Math/Vector4.h>

namespace Framework::Helper::Xml {
    class Node;

    class Attribute;

    static int32_t g_xml_last_error = 0;

    class Attribute {
    public:
        Attribute()
                : m_attribute(), m_valid(false) {}

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

        [[nodiscard]] std::string ToString(const std::string &def) const;

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
                SRAssert2(false, "Node::Name() : node is not valid!");
                g_xml_last_error = -4;
                return {};
            }

            return m_node.name();
        }

        [[nodiscard]] Attribute GetAttribute(const std::string &name) const {
            if (!m_valid) {
                SRAssert2(false, "Node::GetAttribute() : node is not valid!");
                g_xml_last_error = -4;
                return Attribute();
            }

            return Attribute(m_node.attribute(name.c_str()));
        }

        [[nodiscard]] Attribute TryGetAttribute(const std::string &name) const {
            return m_valid ? Attribute(m_node.attribute(name.c_str())) : Attribute();
        }

        [[nodiscard]] bool HasAttribute(const std::string &name) const {
            return m_valid ? !m_node.attribute(name.c_str()).empty() : false;
        }

        [[nodiscard]] std::vector<Node> TryGetNodes() const;
        [[nodiscard]] std::vector<Node> TryGetNodes(const std::string &name) const;
        [[nodiscard]] std::vector<Node> GetNodes(const std::string &name) const;
        [[nodiscard]] std::vector<Node> GetNodes() const;

        template<typename T>
        Xml::Node NAppendAttribute(const std::string &name, const T &value) {
            if (!m_valid) {
                SRAssert2(false, "Node::AddAttribute() : node is not valid!");
                g_xml_last_error = -2;
                return *this;
            }

            if (auto attrib = m_node.append_attribute(name.c_str()); !attrib.empty())
                attrib.set_value(value);

            return *this;
        }

        template<typename T>
        bool AppendAttribute(const std::string &name, const T &value) {
            if (!m_valid) {
                SRAssert2(false, "Node::AddAttribute() : node is not valid!");
                g_xml_last_error = -2;
                return false;
            }

            if (auto attrib = m_node.append_attribute(name.c_str()); !attrib.empty()) {
                attrib.set_value(value);
                return true;
            }

            return false;
        }


        Node AppendChild(const std::string &name);

        Node AppendChild(const Node &node);

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
    public:
        Document() {
            m_document = {};
            m_valid = false;
        }

    private:
        pugi::xml_document m_document;
        bool m_valid;
        std::string m_path;
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

        static Document Load(const std::string &path);
        static Document Load(const Helper::Path &path);

        static int32_t GetLastError() {
            auto last = Xml::g_xml_last_error;
            Xml::g_xml_last_error = 0;
            return last;
        }

    public:
        bool Save(const std::string &path) const {
            return m_document.save_file(path.c_str());
        }

        [[nodiscard]] std::string Dump() const;

        [[nodiscard]] Node Root() const {
            return Node(m_document.root());
        }

        [[nodiscard]] Node DocumentElement() const {
            return Node(m_document.document_element());
        }

        [[nodiscard]] bool Valid() const { return m_valid; }
    };

    static Helper::Math::FColor NodeToColor(const Xml::Node& node) {
        return Math::FColor(
                node.TryGetAttribute("r").ToFloat(0.f) / 255.f,
                node.TryGetAttribute("g").ToFloat(0.f) / 255.f,
                node.TryGetAttribute("b").ToFloat(0.f) / 255.f,
                node.TryGetAttribute("a").ToFloat(0.f) / 255.f
        );
    }

    static void AppendColorNode(Xml::Node& node, const Math::FColor& color) {
        node.AppendChild("Color")
            .NAppendAttribute("r", color.r * 255.f)
            .NAppendAttribute("g", color.g * 255.f)
            .NAppendAttribute("b", color.b * 255.f)
            .NAppendAttribute("a", color.a * 255.f);
    }
}

#endif //GAMEENGINE_XML_H
