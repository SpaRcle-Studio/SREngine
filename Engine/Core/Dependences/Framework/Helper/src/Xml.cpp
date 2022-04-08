//
// Created by Monika on 03.09.2021.
//

#include "Xml.h"
#include <iostream>

using namespace Framework::Helper;

std::string Framework::Helper::Xml::Attribute::ToString() const {
    if (!CheckError("Attribute::ToString() : attribute isn't valid!"))
        return std::string();
    else
        return m_attribute.as_string();
}

int32_t Framework::Helper::Xml::Attribute::ToInt() const {
    if (!CheckError("Attribute::ToInt() : attribute isn't valid!"))
        return 0;
    else
        return m_attribute.as_int();
}

float_t Framework::Helper::Xml::Attribute::ToFloat() const {
    if (!CheckError("Attribute::ToFloat() : attribute isn't valid!"))
        return 0.f;
    else
        return m_attribute.as_float();
}

bool Framework::Helper::Xml::Attribute::ToBool() const {
    if (!CheckError("Attribute::ToBool() : attribute isn't valid!"))
        return false;
    else
        return m_attribute.as_bool();
}

std::string Xml::Attribute::ToString(const std::string &def) const {
    return m_valid ? m_attribute.as_string() : def;
}

int32_t Xml::Attribute::ToInt(int32_t def) const {
    return m_valid ? m_attribute.as_int() : def;
}

float_t Xml::Attribute::ToFloat(float_t def) const {
    return m_valid ? m_attribute.as_float() : def;
}

bool Xml::Attribute::ToBool(bool def) const {
    return m_valid ? m_attribute.as_bool() : def;
}

int64_t Xml::Attribute::ToInt64(int64_t def) const {
    return m_valid ? m_attribute.as_llong() : def;
}

int64_t Xml::Attribute::ToInt64() const {
    if (!CheckError("Attribute::ToInt64() : attribute isn't valid!"))
        return 0;
    else
        return m_attribute.as_llong();
}

uint64_t Xml::Attribute::ToUInt64() const {
    if (!CheckError("Attribute::ToInt64() : attribute isn't valid!"))
        return 0;
    else
        return m_attribute.as_ullong();
}

uint32_t Xml::Attribute::ToUInt() const {
    if (!CheckError("Attribute::ToUInt() : attribute isn't valid!"))
        return 0;
    else
        return m_attribute.as_uint();
}

uint32_t Xml::Attribute::ToUInt(uint32_t def) const {
    return m_valid ? m_attribute.as_uint() : def;
}

uint64_t Xml::Attribute::ToUInt64(uint64_t def) const {
    return m_valid ? m_attribute.as_ullong() : def;
}

Framework::Helper::Xml::Document Framework::Helper::Xml::Document::Load(const std::string &path)  {
    auto xml = Document::New();
    if (pugi::xml_parse_result result = xml.m_document->load_file(path.c_str())) {
        xml.m_valid = true;
        xml.m_path = path;
    } else {
        Helper::Debug::Error("Document::Load() : failed to load xml! \n\tPath: " + path + "\n\tDescription: " + std::string(result.description()));
        Xml::g_xml_last_error = -3;
    }
    return xml;
}

std::string Xml::Document::Dump() const {
    if (!Valid())
        return std::string();

    std::ostringstream stream;
    m_document->save(stream, PUGIXML_TEXT("    "));

    return stream.str();
}

Xml::Document Xml::Document::Load(const Helper::Path &path) {
    return Load(path.ToString());
}

Framework::Helper::Xml::Node::Node()
    : m_node()
    , m_valid(false)
{ }

Xml::Document Xml::Node::ToDocument() const {
    auto doc = Document::New();
    doc.Root().AppendChild(*this);
    return doc;
}

Xml::Node Xml::Node::AppendChild(const std::string &name)  {
    if (!m_valid) {
        SRAssert2(false,"Node::AppendChild() : node is not valid!");
        g_xml_last_error = -2;
        return Node();
    }

    return Node(m_node.append_child(name.c_str()));
}

std::vector<Xml::Node> Xml::Node::GetNodes() const  {
    if (!m_valid) {
        SRAssert2(false,"Node::GetNodes() : node is not valid!");
        g_xml_last_error = -2;
        return {};
    }

    auto nodes = std::vector<Node>();
    for (const auto child : m_node.children())
        nodes.emplace_back(Node(child));

    return nodes;
}

std::vector<Xml::Node> Xml::Node::TryGetNodes(const std::string &name) const {
    if (Valid())
        return GetNodes(name);

    return std::vector<Node>();
}

std::vector<Xml::Node> Xml::Node::TryGetNodes() const {
    if (Valid())
        return GetNodes();

    return std::vector<Node>();
}


std::vector<Xml::Node> Xml::Node::GetNodes(const std::string &name) const  {
    if (!m_valid) {
        SRAssert2(false,"Node::GetNodes() : node is not valid!");
        g_xml_last_error = -2;
        return {};
    }

    auto nodes = std::vector<Node>();
    for (const auto child : m_node.children())
        if (std::string(child.name()) == name)
            nodes.emplace_back(Node(child));

    return nodes;
}

Xml::Node Xml::Node::AppendChild(const Xml::Node& node) {
    return Xml::Node(m_node.append_copy(node.m_node));
}


