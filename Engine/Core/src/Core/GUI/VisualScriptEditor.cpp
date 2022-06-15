//
// Created by Monika on 11.01.2022.
//

#include <Core/GUI/VisualScriptEditor.h>
#include <Core/Parsers/BlueprintParser.h>

#include <Utils/ResourceManager/ResourceManager.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/Xml.h>
#include <GUI/NodeManager.h>

#include <GUI/Link.h>
#include <GUI/Node.h>
#include <GUI/Pin.h>

Framework::Core::GUI::VisualScriptEditor::VisualScriptEditor()
    : Framework::Graphics::GUI::Widget("Evo Script Editor")
{
    auto config = new ax::NodeEditor::Config();
    static std::string settingsFile = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("/NodeEditor.json");
    config->SettingsFile = settingsFile.c_str();

    m_editor = ax::NodeEditor::CreateEditor(config);

    LoadConfig();

    AddNode(CreateBlueprint("Branch"));

    AddNode(CreateBlueprint("X"));

    AddNode(CreateBlueprint("OnStart"));

    /*AddNode(Node("Node A")
            .AddInput(Pin("Pin AAAA", PinType::Flow))
            .AddInput(Pin("Pin B", PinType::Bool))
            .AddInput(Pin("Pin C", PinType::Float))
            .AddInput(Pin("Pin D", PinType::Delegate))
            .AddInput(Pin("Pin E", PinType::String))
            .AddOutput(Pin("Pin A", PinType::Flow))
            .AddOutput(Pin("Pin B", PinType::Function)));

    AddNode(Node("Node B")
            .AddInput(Pin("Pin A", PinType::Flow))
            .AddOutput(Pin("Pin A", PinType::Flow)));*/
}

Framework::Core::GUI::VisualScriptEditor::~VisualScriptEditor() {
    if (m_editor) {
        ax::NodeEditor::DestroyEditor(m_editor);
        m_editor = nullptr;
    }

    for (auto& [id, ptr] : m_links)
        delete ptr;

    for (auto& [id, ptr] : m_nodes)
        delete ptr;

    for (auto& [id, ptr] : m_blueprints)
        delete ptr;

    m_links.clear();
    m_nodes.clear();
    m_blueprints.clear();
}

void Framework::Core::GUI::VisualScriptEditor::AddNode(Framework::Graphics::GUI::Node* node) {
    if (!node) {
        SRAssert(false);
        return;
    }

    SRAssert(m_nodes.count(node->GetId()) == 0);
    m_nodes.insert(std::make_pair(node->GetId(), node));
}

void Framework::Core::GUI::VisualScriptEditor::Draw() {
    ax::NodeEditor::SetCurrentEditor(m_editor);

    ax::NodeEditor::Begin("Evo Visual Script");

    for (const auto& [id, node] : m_nodes)
        node->Draw();

    for (const auto& [id, link] : m_links)
        link->Draw();

    using namespace Framework::Graphics::GUI;

    if (ax::NodeEditor::BeginCreate()) {
        ax::NodeEditor::PinId inputPinId, outputPinId;
        if (ax::NodeEditor::QueryNewLink(&inputPinId, &outputPinId) && (inputPinId && outputPinId)) {
            auto&& startPin = NodeManager::Instance().GetUnique<Pin>(inputPinId.Get());
            auto&& endPin = NodeManager::Instance().GetUnique<Pin>(outputPinId.Get());

            if (ValidateLink(startPin, endPin) && ax::NodeEditor::AcceptNewItem()) {
                AddLink(new Link(startPin, endPin));
            }
        }
    }
    ax::NodeEditor::EndCreate(); // Wraps up object creation action handling.

    ax::NodeEditor::End();
}

void Framework::Core::GUI::VisualScriptEditor::AddLink(Framework::Graphics::GUI::Link* link) {
    SRAssert(m_links.count(link->GetId()) == 0);
    m_links.insert(std::make_pair(link->GetId(), link));
}

void Framework::Core::GUI::VisualScriptEditor::LoadConfig() {
    /*SR_LOG("VisualScriptEditor::LoadConfig() : loading config...");

    const auto& resManager = Helper::ResourceManager::Instance();
    const auto path = resManager.GetConfigPath().Concat("/EvoScript.xml");
    const std::string strPath = path.ToString();

    if (Helper::FileSystem::FileExists(strPath)) {
        auto xml = SR_XML_NS::Document::Load(strPath);
        for (const SR_XML_NS::Node& blueprintPath : xml.Root().GetNode("Configs").GetNode("BlueprintRefs").GetNodes()) {
            auto nodes = Core::BlueprintParser::Instance().Parse(resManager.GetResPath().Concat(blueprintPath.GetAttribute("Value").ToString()));
            for (auto&& node : nodes) {
                RegisterBlueprint(node);
            }
        }
    }
    else {
        SR_ERROR("VisualScriptEditor::LoadConfig() : config file not found! \n\tPath: " + strPath);
    }*/
}

SR_GRAPH_NS::GUI::Node* VisualScriptEditor::CreateBlueprint(const std::string &id) const {
    if (m_blueprints.count(id)) {
        return m_blueprints.at(id)->Copy();
    }

    SRAssert2(false, Helper::Format("Blueprint \"%s\" not found!", id.c_str()));

    return nullptr;
}

bool VisualScriptEditor::ValidateLink(SR_GRAPH_NS::GUI::Pin* start, SR_GRAPH_NS::GUI::Pin* end) const {
    if (!start || !end || start == end)
        return false;

    if (start->GetKind() == end->GetKind())
        return false;

    if (start->GetNode() == end->GetNode())
        return false;

    return start->GetType() == end->GetType();
}

void VisualScriptEditor::RegisterBlueprint(SR_GRAPH_NS::GUI::Node* blueprint) {
    const std::string name = blueprint->GetName();

    if (m_blueprints.count(name)) {
        SR_ERROR(Helper::Format("VisualScriptEditor::RegisterBlueprint() : blueprint \"%s\" already registered!"));
        return;
    }

    m_blueprints.insert(std::make_pair(name, blueprint));
}


