//
// Created by Monika on 03.09.2021.
//

#ifndef GAMEENGINE_XML_H
#define GAMEENGINE_XML_H

#include <Debug.h>

#include <FileSystem/Path.h>
#include <Math/Vector4.h>
#include <Math/Vector3.h>
#include <Math/Vector2.h>
#include <Utils/NonCopyable.h>

#include "../../Depends/assimp/contrib/pugixml/src/pugixml.hpp"

namespace Framework::Helper::Xml {
    class Node;

    class Attribute;
    class Document;

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
        [[nodiscard]] uint32_t ToUInt() const;
        [[nodiscard]] int64_t ToInt64() const;
        [[nodiscard]] uint64_t ToUInt64() const;
        [[nodiscard]] float_t ToFloat() const;
        [[nodiscard]] bool ToBool() const;

        [[nodiscard]] std::string ToString(const std::string &def) const;
        [[nodiscard]] int32_t ToInt(int32_t def) const;
        [[nodiscard]] uint32_t ToUInt(uint32_t def) const;
        [[nodiscard]] int64_t ToInt64(int64_t def) const;
        [[nodiscard]] uint64_t ToUInt64(uint64_t def) const;
        [[nodiscard]] float_t ToFloat(float_t def) const;
        [[nodiscard]] bool ToBool(bool def) const;
    };

    class Node {
        friend class Document;

    public:
        Node();

        explicit Node(pugi::xml_node node) {
            m_node = node;
            m_valid = !m_node.empty();
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

        [[nodiscard]] Document ToDocument() const;

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

        template<typename T> Xml::Node NAppendAttribute(const std::string &name, const T &value) {
            if (!m_valid) {
                SRAssert2(false, "Node::NAppendAttribute() : node is not valid!");
                g_xml_last_error = -2;
                return *this;
            }

            auto attrib = m_node.append_attribute(name.c_str());
            if (attrib.empty())
                return *this;

            if constexpr (std::is_same<T, std::string>()) {
                attrib.set_value(value.c_str());
            }
            else {
                attrib.set_value(value);
            }

            return *this;
        }

        template<typename T, typename U> Xml::Node NAppendAttributeDef(const std::string &name, const T &value, const U& def) {
            if (!m_valid) {
                SRAssert2(false, "Node::NAppendAttributeDef() : node is not valid!");
                g_xml_last_error = -2;
                return *this;
            }

            if (value != def) {
                auto attrib = m_node.append_attribute(name.c_str());
                if (attrib.empty())
                    return *this;

                if constexpr (std::is_same<T, std::string>()) {
                    attrib.set_value(value.c_str());
                } else {
                    attrib.set_value(value);
                }
            }

            return *this;
        }

        template<typename T> T GetAttribute() const {
            if constexpr (std::is_same<T, Helper::Math::FColor>()) {
                Helper::Math::FColor color;

                color.r = GetAttribute("r").ToFloat();
                color.g = GetAttribute("g").ToFloat();
                color.b = GetAttribute("b").ToFloat();
                color.a = GetAttribute("a").ToFloat();

                return color;
            }
            else if constexpr (std::is_same<T, Helper::Math::FVector2>()) {
                Helper::Math::FVector2 vector2;

                vector2.x = GetAttribute("x").ToFloat();
                vector2.y = GetAttribute("y").ToFloat();

                return vector2;
            }
            else if constexpr (std::is_same<T, Helper::Math::IVector3>()) {
                Helper::Math::IVector3 vector3;

                vector3.x = GetAttribute("x").ToInt();
                vector3.y = GetAttribute("y").ToInt();
                vector3.z = GetAttribute("z").ToInt();

                return vector3;
            }
            else
                static_assert("Unknown type!");
        }

        template<typename T> bool AppendAttribute(const T &value) {
            if (!m_valid) {
                SRAssert2(false, "Node::AddAttribute() : node is not valid!");
                g_xml_last_error = -2;
                return false;
            }

            bool hasErrors = false;

            if constexpr (std::is_same<T, Helper::Math::FColor>()) {
                hasErrors |= AppendAttribute("r", value.r);
                hasErrors |= AppendAttribute("g", value.g);
                hasErrors |= AppendAttribute("b", value.b);
                hasErrors |= AppendAttribute("a", value.a);
            }
            else if constexpr (std::is_same<T, Helper::Math::FVector2>()) {
                hasErrors |= AppendAttribute("x", value.x);
                hasErrors |= AppendAttribute("y", value.y);
            }
            else if constexpr (std::is_same<T, Helper::Math::IVector2>()) {
                hasErrors |= AppendAttribute("x", value.x);
                hasErrors |= AppendAttribute("y", value.y);
            }
            else if constexpr (std::is_same<T, Helper::Math::FVector3>()) {
                hasErrors |= AppendAttribute("x", value.x);
                hasErrors |= AppendAttribute("y", value.y);
                hasErrors |= AppendAttribute("z", value.z);
            }
            else if constexpr (std::is_same<T, Helper::Math::IVector3>()) {
                hasErrors |= AppendAttribute("x", value.x);
                hasErrors |= AppendAttribute("y", value.y);
                hasErrors |= AppendAttribute("z", value.z);
            }
            else
                static_assert("Unknown type!");

            return !hasErrors;
        }

        template<typename T> bool AppendAttribute(const std::string &name, const T &value) {
            if (!m_valid) {
                SRAssert2(false, "Node::AddAttribute() : node is not valid!");
                g_xml_last_error = -2;
                return false;
            }

            auto attrib = m_node.append_attribute(name.c_str());
            if (attrib.empty())
                return false;

            if constexpr (std::is_same<T, std::string>()) {
                attrib.set_value(value.c_str());
            }
            else {
                attrib.set_value(value);
            }

            return true;
        }

        template<typename T, typename U> bool AppendAttributeDef(const std::string &name, const T &value, const U& def) {
            if (!m_valid) {
                SRAssert2(false, "Node::AddAttribute() : node is not valid!");
                g_xml_last_error = -2;
                return false;
            }

            if (value != def) {
                auto attrib = m_node.append_attribute(name.c_str());
                if (attrib.empty())
                    return false;

                if constexpr (std::is_same<T, std::string>()) {
                    attrib.set_value(value.c_str());
                } else {
                    attrib.set_value(value);
                }
            }

            return true;
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

    class Document : public NonCopyable {
    public:
        Document() {
            m_valid = false;
        }

        Document(Document&& document) noexcept
            : m_document(std::exchange(document.m_document, {}))
            , m_valid(std::exchange(document.m_valid, {}))
            , m_path(std::exchange(document.m_path, {}))
        { }

        ~Document() override {
            if (m_document) {
                delete m_document;
            }
        }

        Document& operator=(Document&& document) noexcept {
            m_document = std::exchange(document.m_document, {});
            m_valid = std::exchange(document.m_valid, {});
            m_path = std::exchange(document.m_path, {});
            return *this;
        }

    private:
        pugi::xml_document* m_document = nullptr;
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
            xml.m_document = new pugi::xml_document();
            return std::move(xml);
        }

        static Document Load(const std::string &path);
        static Document Load(const Helper::Path &path);

        static int32_t GetLastError() {
            auto last = Xml::g_xml_last_error;
            Xml::g_xml_last_error = 0;
            return last;
        }

    public:
        Xml::Node AppendChild(const std::string& name) {
            if (!m_valid) {
                SRAssert2(false,"Document::AppendChild() : document is not valid!");
                g_xml_last_error = -2;
                return Node();
            }

            auto node = m_document->append_child(name.c_str());
            return Node(node);
        }

        bool Save(const Helper::Path& path) const {
            if (!path.Exists()) {
                path.Make();
            }
            return m_document->save_file(path.CStr());
        }

        [[nodiscard]] std::string Dump() const;

        [[nodiscard]] Node Root() const {
            return Node(m_document->root());
        }

        [[nodiscard]] Node TryRoot() const {
            if (!Valid())
                return Node();

            return Node(m_document->root());
        }

        [[nodiscard]] Node DocumentElement() const {
            return Node(m_document->document_element());
        }

        [[nodiscard]] bool Valid() const { return m_valid; }
    };

    template<bool NeedConvert> static Helper::Math::FColor NodeToColor(const Xml::Node& node) {
        if constexpr(NeedConvert) {
            return Math::FColor(
                    node.TryGetAttribute("r").ToFloat(0.f) / 255.f,
                    node.TryGetAttribute("g").ToFloat(0.f) / 255.f,
                    node.TryGetAttribute("b").ToFloat(0.f) / 255.f,
                    node.TryGetAttribute("a").ToFloat(0.f) / 255.f
            );
        }
        else {
            return Math::FColor(
                    node.TryGetAttribute("r").ToFloat(0.f),
                    node.TryGetAttribute("g").ToFloat(0.f),
                    node.TryGetAttribute("b").ToFloat(0.f),
                    node.TryGetAttribute("a").ToFloat(0.f)
            );
        }
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
