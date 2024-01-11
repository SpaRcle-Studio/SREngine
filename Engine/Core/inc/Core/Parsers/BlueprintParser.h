////
//// Created by Monika on 17.01.2022.
////
//
//#ifndef SR_ENGINE_BLUEPRINTPARSER_H
//#define SR_ENGINE_BLUEPRINTPARSER_H
//
//#include <Utils/Common/Singleton.h>
//#include <Utils/Xml.h>
//
//namespace SR_GRAPH_NS::GUI {
//    class Pin;
//    class Node;
//}
//
//namespace SR_CORE_NS {
//    class BlueprintParser : public SR_UTILS_NS::Singleton<BlueprintParser> {
//        friend class SR_UTILS_NS::Singleton<BlueprintParser>;
//    public:
//        std::vector<SR_GRAPH_NS::GUI::Node*> Parse(const std::string& path);
//
//    private:
//        ImVec4 ParseColor(const SR_XML_NS::Node& xml);
//        SR_GRAPH_NS::GUI::Node* ParseBlueprint(const SR_XML_NS::Node& blueprintXml);
//        SR_GRAPH_NS::GUI::Pin* ParsePin(const SR_XML_NS::Node& pinXml);
//
//    };
//}
//
//#endif //SR_ENGINE_BLUEPRINTPARSER_H
