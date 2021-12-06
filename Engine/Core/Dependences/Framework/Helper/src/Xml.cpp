//
// Created by Monika on 03.09.2021.
//

#include "Xml.h"

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

int32_t Framework::Helper::Xml::Attribute::ToFloat() const {
    if (!CheckError("Attribute::ToFloat() : attribute isn't valid!"))
        return 0.f;
    else
        return m_attribute.as_float();
}

int32_t Framework::Helper::Xml::Attribute::ToBool() const {
    if (!CheckError("Attribute::ToBool() : attribute isn't valid!"))
        return false;
    else
        return m_attribute.as_bool();
}

Framework::Helper::Xml::Document Framework::Helper::Xml::Document::Load(const std::string &path)  {
    auto xml = Document();
    if (pugi::xml_parse_result result = xml.m_document.load_file(path.c_str())) {
        xml.m_valid = true;
        xml.m_path = path;
    } else {
        Helper::Debug::Error("Document::Load() : failed to load xml! \n\tPath: " + path + "\n\tDescription: " + std::string(result.description()));
        Xml::g_xml_last_error = -3;
    }
    return xml;
}


