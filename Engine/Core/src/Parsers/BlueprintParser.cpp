//
// Created by Monika on 17.01.2022.
//

#include <Parsers/BlueprintParser.h>
#include <GUI/Pin.h>
#include <GUI/Node.h>

std::vector<SR_GRAPH_NS::GUI::Node*> SR_CORE_NS::BlueprintParser::Parse(const std::string &path) {
    std::vector<SR_GRAPH_NS::GUI::Node*> blueprints;

    if (Helper::FileSystem::FileExists(path)) {
        auto xml = Helper::Xml::Document::Load(path);
        for (const Helper::Xml::Node& blueprint : xml.Root().GetNode("Blueprints").GetNodes())
            blueprints.emplace_back(ParseBlueprint(blueprint));
    }
    else
        Helper::Debug::Error("BlueprintParser::Parse : config file not found! \n\tPath: " + path);

    return blueprints;
}

ImVec4 SR_CORE_NS::BlueprintParser::ParseColor(const SR_XML_NS::Node& xml) {
    return ImVec4(
            xml.TryGetAttribute("r").ToInt(255),
            xml.TryGetAttribute("g").ToInt(255),
            xml.TryGetAttribute("b").ToInt(255),
            xml.TryGetAttribute("a").ToInt(255)
    );
}

SR_GRAPH_NS::GUI::Pin* SR_CORE_NS::BlueprintParser::ParsePin(const Framework::Helper::Xml::Node &pinXml) {
    auto pin = new Framework::Graphics::GUI::Pin(
            pinXml.TryGetAttribute("Name").ToString("Unnamed"),
            SR_GRAPH_NS::GUI::StringToEnumPinType(pinXml.TryGetAttribute("Type").ToString("None"))
    );

    return pin;
}

SR_GRAPH_NS::GUI::Node* SR_CORE_NS::BlueprintParser::ParseBlueprint(const Framework::Helper::Xml::Node &blueprintXml) {
    const auto name = blueprintXml.TryGetAttribute("Name").ToString(blueprintXml.Name());

    auto node = new Framework::Graphics::GUI::Node(
        name,
        SR_GRAPH_NS::GUI::StringToEnumNodeType(blueprintXml.TryGetAttribute("Type").ToString("None")),
        ParseColor(blueprintXml.TryGetNode("Color"))
    );

    for (const auto& input : blueprintXml.TryGetNode("Inputs").TryGetNodes())
        node->AddInput(ParsePin(input));

    for (const auto& input : blueprintXml.TryGetNode("Outputs").TryGetNodes())
        node->AddOutput(ParsePin(input));

    return node;
}