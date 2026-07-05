//
// Created by Monika on 14.01.2023.
//

#include <Engine/GUI/Hierarchy.h>
#include <Engine/GUI/AnimatorEditor.h>

#include <Graphics/Animations/Animator.h>
#include <Graphics/Animations/AnimationGraphNode.h>
#include <Graphics/GUI/WidgetManager.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/GUI/Link.h>
#include <Graphics/GUI/Pin.h>
#include <Graphics/GUI/NodeBuilder.h>
#include <Graphics/GUI/ImmediateGUI.h>

#include <Utils/Resources/ResourceManager.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/SRLM/DataType.h>

#include <Codegen/AnimatorEditor.generated.hpp>

namespace SR_CORE_GUI_NS {
    AnimatorEditor::AnimatorEditor()
        : Super("Animator")
    { }

    void AnimatorEditor::Init() {
        Super::Init();
        InitNodeTypes();
    }

    void AnimatorEditor::OnClose() {
    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::DestroyEditor(m_editor);
            m_editor = nullptr;
        }
    #endif

        Super::OnClose();
    }

    void AnimatorEditor::SetGraphPath(const SR_UTILS_NS::Path& path) {
        m_graphPath = path;
        m_graph.Reset();

        if (m_graphPath.IsEmpty()) {
            return;
        }

        Open();
        Focus();

        auto&& loadPath = path.RemoveSubPath(SR_UTILS_NS::ResourceManager::Instance().GetResPath());
        if (auto&& pAsset = SR_UTILS_NS::Asset::Load<SR_GRAPH_NS::Animations::AnimationGraphAsset>(loadPath)) {
            m_graph = new SR_GRAPH_NS::Animations::AnimationGraph();
            pAsset->GetData().CloneTo(*m_graph);
            m_graph->SetAsset(pAsset.Get());
            
            // Синхронизируем визуальные ноды с данными графа
            SyncGraphToVisualNodes();
        }
        else {
            SR_ERROR("AnimatorEditor::SetGraphPath() : failed to load animation graph asset: {}", loadPath);
        }
    }

    void AnimatorEditor::Draw() {
        if (!m_graph) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor::Red(), "No animator loaded!");
            return;
        }

        DrawTopPanel();
        
        SR_GRAPH_GUI_NS::Immediate::Separator();
        
        // Разделяем окно на левую панель и редактор
        auto&& availableSize = SR_GRAPH_GUI_NS::Immediate::GetContentRegionAvail();
        
        // Левая панель для свойств
        SR_GRAPH_GUI_NS::Immediate::BeginChild("LeftPanel", SR_MATH_NS::FVector2(m_leftPaneWidth, availableSize.y), false);
        DrawLeftPanel();
        SR_GRAPH_GUI_NS::Immediate::EndChild();
        
        SR_GRAPH_GUI_NS::Immediate::SameLine();
        
        // Редактор графа
        SR_GRAPH_GUI_NS::Immediate::BeginChild("NodeEditor", SR_MATH_NS::FVector2(availableSize.x - m_leftPaneWidth - 10, availableSize.y), false);
        DrawNodeEditor();
        SR_GRAPH_GUI_NS::Immediate::EndChild();
    }

    void AnimatorEditor::DrawNodeEditor() {
    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (!m_editor) {
            return;
        }

        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
        SR_GRAPH_GUI_NS::Immediate::Begin("Animation Graph Editor", SR_MATH_NS::FVector2());

        // Создаем NodeBuilder (без текстуры для заголовка пока)
        SR_GRAPH_GUI_NS::NodeBuilder builder(nullptr);

        // Отрисовываем все ноды
        for (auto&& [id, pNode] : m_nodes) {
            if (!pNode) {
                continue;
            }

            // Получаем цвет заголовка на основе типа ноды
            SR_MATH_NS::FColor headerColor = SR_MATH_NS::FColor(0.2f, 0.6f, 0.84f, 1.0f); // Синий по умолчанию
            if (auto&& graphNodeIt = m_visualToGraphNode.find(pNode); graphNodeIt != m_visualToGraphNode.end()) {
                if (auto&& pGraphNode = m_graph->GetNode(graphNodeIt->second)) {
                    if (auto&& pMeta = pGraphNode->GetMeta()) {
                        auto&& category = pMeta->GetCategory();
                        // Определяем цвет на основе категории
                        if (!category.empty()) {
                            // Хешируем первую категорию для получения цвета
                            uint32_t hash = 0;
                            for (char c : category[0].ToStringRef()) {
                                hash = hash * 31 + c;
                            }
                            headerColor = SR_MATH_NS::FColor(
                                std::max(0.3f, std::min(0.9f, ((hash & 0xFF) / 255.0f))),
                                std::max(0.3f, std::min(0.9f, (((hash >> 8) & 0xFF) / 255.0f))),
                                std::max(0.3f, std::min(0.9f, (((hash >> 16) & 0xFF) / 255.0f))),
                                1.0f
                            );
                        }
                    }
                }
            }

            builder.Begin(pNode);
            
            // Заголовок ноды
            builder.Header(headerColor);
            SR_GRAPH_GUI_NS::Immediate::Spring(0);
            SR_GRAPH_GUI_NS::Immediate::Text("%s", pNode->GetName().c_str());
            SR_GRAPH_GUI_NS::Immediate::Spring(1);
            builder.EndHeader();
            
            // Отрисовываем входные пины
            for (auto&& pPin : pNode->GetInputs()) {
                builder.Input(pPin);
                
                // Получаем цвет и тип иконки пина
                auto&& pinType = pPin->GetType();
                auto&& iconType = SR_GRAPH_NS::GUI::Pin::GetIconType(pinType);
                auto&& pinColor = GetPinColor(pinType);
                auto&& isLinked = pPin->IsLinked();
                
                // Рисуем иконку пина
                SR_GRAPH_GUI_NS::Immediate::DrawPinIcon(
                    SR_MATH_NS::FVector2(24.0f, 24.0f),
                    iconType,
                    isLinked,
                    pinColor,
                    SR_MATH_NS::FColor(0.125f, 0.125f, 0.125f, 1.0f)
                );
                SR_GRAPH_GUI_NS::Immediate::Spring(0);
                
                if (!pPin->GetName().empty()) {
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", pPin->GetName().c_str());
                    SR_GRAPH_GUI_NS::Immediate::Spring(0);
                }
                
                builder.EndInput();
            }
            
            // Отрисовываем выходные пины
            for (auto&& pPin : pNode->GetOutputs()) {
                builder.Output(pPin);
                
                SR_GRAPH_GUI_NS::Immediate::Spring(0);
                
                if (!pPin->GetName().empty()) {
                    SR_GRAPH_GUI_NS::Immediate::Text("%s", pPin->GetName().c_str());
                    SR_GRAPH_GUI_NS::Immediate::Spring(0);
                }
                
                // Получаем цвет и тип иконки пина
                auto&& pinType = pPin->GetType();
                auto&& iconType = SR_GRAPH_NS::GUI::Pin::GetIconType(pinType);
                auto&& pinColor = GetPinColor(pinType);
                auto&& isLinked = pPin->IsLinked();
                
                // Рисуем иконку пина
                SR_GRAPH_GUI_NS::Immediate::DrawPinIcon(
                    SR_MATH_NS::FVector2(24.0f, 24.0f),
                    iconType,
                    isLinked,
                    pinColor,
                    SR_MATH_NS::FColor(0.125f, 0.125f, 0.125f, 1.0f)
                );
                
                builder.EndOutput();
            }
            
            builder.End();
        }

        // Отрисовываем все связи
        for (auto&& [id, pLink] : m_links) {
            if (pLink && pLink->IsLinked()) {
                pLink->Draw();
            }
        }

        // Обработка создания новых связей
        if (SR_GRAPH_GUI_NS::Immediate::BeginCreate()) {
            uintptr_t startPinId = 0, endPinId = 0;
            if (SR_GRAPH_GUI_NS::Immediate::QueryNewLink(&startPinId, &endPinId)) {
                if (startPinId && endPinId) {
                    // Находим пины по ID
                    SR_GRAPH_GUI_NS::Pin* pStartPin = nullptr;
                    SR_GRAPH_GUI_NS::Pin* pEndPin = nullptr;

                    for (auto&& [nodeId, pNode] : m_nodes) {
                        for (auto&& pPin : pNode->GetInputs()) {
                            if (pPin->GetId() == startPinId || pPin->GetId() == endPinId) {
                                if (pPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input) {
                                    pEndPin = pPin;
                                }
                            }
                        }
                        for (auto&& pPin : pNode->GetOutputs()) {
                            if (pPin->GetId() == startPinId || pPin->GetId() == endPinId) {
                                if (pPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output) {
                                    pStartPin = pPin;
                                }
                            }
                        }
                    }

                    // Проверяем, что startPin - выходной, а endPin - входной
                    if (pStartPin && pEndPin && 
                        pStartPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output &&
                        pEndPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input &&
                        SR_GRAPH_GUI_NS::Immediate::AcceptNewItem()) {
                        auto&& pLink = new SR_GRAPH_GUI_NS::Link(pStartPin, pEndPin);
                        AddLink(pLink);
                        
                        // Синхронизируем с графом
                        SyncVisualNodesToGraph();
                    }
                }
            }
        }
        SR_GRAPH_GUI_NS::Immediate::EndCreate();

        // Обработка удаления
        if (SR_GRAPH_GUI_NS::Immediate::BeginDelete()) {
            uintptr_t linkId = 0;
            while (SR_GRAPH_GUI_NS::Immediate::QueryDeletedLink(&linkId, nullptr, nullptr)) {
                if (linkId) {
                    for (auto&& [id, pLink] : m_links) {
                        if (pLink->GetId() == linkId) {
                            RemoveLink(pLink);
                            SyncVisualNodesToGraph();
                            break;
                        }
                    }
                }
            }

            uintptr_t nodeId = 0;
            while (SR_GRAPH_GUI_NS::Immediate::QueryDeletedNode(&nodeId)) {
                if (nodeId) {
                    for (auto&& [id, pNode] : m_nodes) {
                        if (pNode->GetId() == nodeId) {
                            RemoveNode(pNode);
                            SyncVisualNodesToGraph();
                            break;
                        }
                    }
                }
            }
        }
        SR_GRAPH_GUI_NS::Immediate::EndDelete();

        // Контекстное меню
        DrawPopupMenu();

        SR_GRAPH_GUI_NS::Immediate::EndNodeEditor();
        SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
    #endif
    }

    void AnimatorEditor::DrawLeftPanel() {
        if (!m_graph) {
            return;
        }

        SR_GRAPH_GUI_NS::Immediate::Text("Properties");
        SR_GRAPH_GUI_NS::Immediate::Separator();

        // Показываем свойства выбранной ноды
        #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (m_editor) {
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(m_editor);
            auto&& selectedNodes = SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nullptr, 0);
            if (selectedNodes > 0) {
                std::vector<uintptr_t> nodeIds(selectedNodes);
                SR_GRAPH_GUI_NS::Immediate::GetSelectedNodes(nodeIds.data(), selectedNodes);
                
                if (!nodeIds.empty()) {
                    auto&& nodeId = nodeIds[0];
                    if (auto&& it = m_nodes.find(nodeId); it != m_nodes.end()) {
                        auto&& pVisualNode = it->second;
                        if (auto&& graphNodeIt = m_visualToGraphNode.find(pVisualNode); graphNodeIt != m_visualToGraphNode.end()) {
                            auto&& graphNodeIndex = graphNodeIt->second;
                            if (auto&& pGraphNode = m_graph->GetNode(graphNodeIndex)) {
                                SR_GRAPH_GUI_NS::Immediate::Text("Node: %s", pVisualNode->GetName().c_str());
                                SR_GRAPH_GUI_NS::Immediate::Text("Type: %llu", graphNodeIndex);
                            }
                        }
                    }
                }
            }
            SR_GRAPH_GUI_NS::Immediate::SetCurrentEditor(nullptr);
        }
        #endif
    }

    void AnimatorEditor::InitNodeTypes() {
        // Получаем все классы, наследующиеся от AnimationGraphNode
        m_availableNodeTypes = SR_UTILS_NS::Factory::Instance().GetInheritances(
            SR_ANIMATIONS_NS::AnimationGraphNode::GetClassStaticName()
        );

        // Фильтруем абстрактные и скрытые классы
        std::erase_if(m_availableNodeTypes, [](auto&& name) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            if (!pMeta) {
                return true;
            }
            return pMeta->IsAbstract() || pMeta->IsHidden();
        });
    }

    void AnimatorEditor::BuildNodeMenu(std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories) {
        categories.clear();

        for (auto&& nodeTypeName : m_availableNodeTypes) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(nodeTypeName);
            if (!pMeta) {
                continue;
            }

            auto&& category = pMeta->GetCategory();
            std::string categoryPath = "Nodes";
            if (!category.empty()) {
                categoryPath.clear();
                for (size_t i = 0; i < category.size(); ++i) {
                    if (i > 0) {
                        categoryPath += "/";
                    }
                    categoryPath += category[i].ToStringRef();
                }
            }

            categories[categoryPath].emplace_back(nodeTypeName);
        }
    }
    
    void AnimatorEditor::DrawNodeMenuRecursive(const std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>>& categories, const std::string& prefix) {
        // Группируем ноды по следующему уровню категорий
        std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> subCategories;
        std::vector<SR_UTILS_NS::StringAtom> directNodes;

        for (auto&& [categoryPath, nodeTypes] : categories) {
            if (categoryPath == prefix) {
                // Ноды напрямую в этой категории
                directNodes.insert(directNodes.end(), nodeTypes.begin(), nodeTypes.end());
            }
            else if (prefix.empty() || (categoryPath.size() >= prefix.size() + 1 && categoryPath.substr(0, prefix.size() + 1) == prefix + "/")) {
                // Определяем следующий уровень
                std::string remaining = prefix.empty() ? categoryPath : categoryPath.substr(prefix.size() + 1);
                auto&& nextSlash = remaining.find('/');
                
                if (nextSlash == std::string::npos) {
                    // Это конечный уровень для этой категории
                    directNodes.insert(directNodes.end(), nodeTypes.begin(), nodeTypes.end());
                }
                else {
                    // Есть подкатегория
                    std::string nextLevel = prefix.empty() ? remaining.substr(0, nextSlash) : prefix + "/" + remaining.substr(0, nextSlash);
                    subCategories[nextLevel].insert(subCategories[nextLevel].end(), nodeTypes.begin(), nodeTypes.end());
                }
            }
        }

        // Рисуем прямые элементы
        for (auto&& nodeTypeName : directNodes) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(nodeTypeName);
            if (!pMeta) {
                continue;
            }

            auto&& displayName = pMeta->GetDisplayName();
            SR_UTILS_NS::StringAtom menuName = displayName.empty() ? nodeTypeName : displayName;
            
            if (SR_GRAPH_GUI_NS::Immediate::MenuItem(menuName.c_str())) {
                if (m_graph) {
                    // Создаем ноду через Factory
                    if (auto&& pNode = SR_UTILS_NS::Factory::Instance().Create<SR_ANIMATIONS_NS::AnimationGraphNode>(nodeTypeName)) {
                        auto&& pGraphNode = m_graph->AddNode(pNode.Get());
                        auto&& pVisualNode = CreateVisualNode(pGraphNode);
                        AddNode(pVisualNode);
                        
                        auto&& mousePos = SR_GRAPH_GUI_NS::Immediate::GetMousePos();
                        auto&& pos = SR_GRAPH_GUI_NS::Immediate::ScreenToCanvas(mousePos);
                        SR_GRAPH_GUI_NS::Immediate::SetNodePosition(pVisualNode->GetId(), pos);
                        
                        // Обновляем маппинг
                        auto&& nodeIndex = pGraphNode->GetIndex();
                        m_graphNodeToVisual[nodeIndex] = pVisualNode;
                        m_visualToGraphNode[pVisualNode] = nodeIndex;
                    }
                }
            }
        }

        // Рисуем подменю
        for (auto&& [nextLevel, nodeTypes] : subCategories) {
            // Извлекаем имя следующего уровня
            std::string levelName = nextLevel;
            if (!prefix.empty()) {
                levelName = nextLevel.substr(prefix.size() + 1);
            }
            auto&& nextSlash = levelName.find('/');
            if (nextSlash != std::string::npos) {
                levelName = levelName.substr(0, nextSlash);
            }

            if (SR_GRAPH_GUI_NS::Immediate::BeginMenu(levelName.c_str())) {
                DrawNodeMenuRecursive(categories, nextLevel);
                SR_GRAPH_GUI_NS::Immediate::EndMenu();
            }
        }
    }

    void AnimatorEditor::DrawPopupMenu() {
    #ifdef SR_USE_IMGUI_NODE_EDITOR
        if (!m_editor) {
            return;
        }

        if (SR_GRAPH_GUI_NS::Immediate::ShowBackgroundContextMenu()) {
            SR_GRAPH_GUI_NS::Immediate::OpenPopup("CreateNode");
        }

        if (SR_GRAPH_GUI_NS::Immediate::BeginPopup("CreateNode")) {
            std::map<std::string, std::vector<SR_UTILS_NS::StringAtom>> categories;
            BuildNodeMenu(categories);
            
            // Рисуем меню рекурсивно
            DrawNodeMenuRecursive(categories, "");
            
            SR_GRAPH_GUI_NS::Immediate::EndPopup();
        }
    #endif
    }

    void AnimatorEditor::SyncGraphToVisualNodes() {
        if (!m_graph) {
            return;
        }

        // Очищаем существующие визуальные ноды
        Clear();

        // Создаем визуальные ноды для каждой граф-ноды
        for (auto&& pGraphNode : m_graph->GetNodes()) {
            if (pGraphNode) {
                auto&& pVisualNode = CreateVisualNode(const_cast<Graphics::Animations::AnimationGraphNode*>(pGraphNode.Get()));
                AddNode(pVisualNode);
                
                auto&& nodeIndex = pGraphNode->GetIndex();
                m_graphNodeToVisual[nodeIndex] = pVisualNode;
                m_visualToGraphNode[pVisualNode] = nodeIndex;
            }
        }

        // Создаем связи
        for (auto&& pGraphNode : m_graph->GetNodes()) {
            if (!pGraphNode) {
                continue;
            }

            auto&& nodeIndex = pGraphNode->GetIndex();
            auto&& visualNodeIt = m_graphNodeToVisual.find(nodeIndex);
            if (visualNodeIt == m_graphNodeToVisual.end()) {
                continue;
            }

            auto&& pVisualNode = visualNodeIt->second;

            // Обрабатываем выходные пины
            // Пока пропускаем автоматическое создание связей при загрузке
            // Связи будут создаваться вручную через редактор
            // TODO: Добавить публичный метод GetOutputLink в AnimationGraphNode для получения информации о связях
            // или использовать дружественный класс для доступа к m_outputPins
        }
    }

    void AnimatorEditor::SyncVisualNodesToGraph() {
        if (!m_graph) {
            return;
        }

        // Обновляем связи в графе на основе визуальных связей
        for (auto&& [linkId, pLink] : m_links) {
            if (!pLink || !pLink->IsLinked()) {
                continue;
            }

            auto&& pStartPin = pLink->GetStart();
            auto&& pEndPin = pLink->GetEnd();
            
            if (!pStartPin || !pEndPin) {
                continue;
            }

            auto&& pStartNode = pStartPin->GetNode();
            auto&& pEndNode = pEndPin->GetNode();

            auto&& startGraphIt = m_visualToGraphNode.find(pStartNode);
            auto&& endGraphIt = m_visualToGraphNode.find(pEndNode);

            if (startGraphIt == m_visualToGraphNode.end() || endGraphIt == m_visualToGraphNode.end()) {
                continue;
            }

            auto&& pStartGraphNode = m_graph->GetNode(startGraphIt->second);
            auto&& pEndGraphNode = m_graph->GetNode(endGraphIt->second);

            if (!pStartGraphNode || !pEndGraphNode) {
                continue;
            }

            auto&& startPinIndex = pStartNode->GetPinIndex(pStartPin);
            auto&& endPinIndex = pEndNode->GetPinIndex(pEndPin);

            // Проверяем валидность индексов
            if (startPinIndex == SR_ID_INVALID || endPinIndex == SR_ID_INVALID) {
                continue;
            }

            // Определяем, какой пин входной, а какой выходной
            if (pStartPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Output && 
                pEndPin->GetKind() == SR_GRAPH_GUI_NS::PinKind::Input) {
                pStartGraphNode->ConnectTo(pEndGraphNode, static_cast<uint16_t>(startPinIndex), static_cast<uint16_t>(endPinIndex));
            }
        }
    }

    SR_GRAPH_GUI_NS::Node* AnimatorEditor::CreateVisualNode(SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode) {
        if (!pGraphNode) {
            return nullptr;
        }

        // Получаем имя ноды из метаинформации
        std::string nodeName = "Node";
        if (auto&& pMeta = pGraphNode->GetMeta()) {
            auto&& displayName = pMeta->GetDisplayName();
            if (!displayName.empty()) {
                nodeName = displayName;
            }
            else {
                auto&& factoryName = SR_UTILS_NS::Factory::Instance().GetName(pMeta, false);
                if (!factoryName.empty()) {
                    nodeName = factoryName.ToStringRef();
                }
            }
        }

        auto&& pNode = new SR_GRAPH_GUI_NS::Node();
        pNode->SetName(nodeName);

        // Создаем входные пины
        for (uint32_t i = 0; i < pGraphNode->GetInputCount(); ++i) {
            auto&& pPin = new SR_GRAPH_GUI_NS::Pin("Input " + std::to_string(i), SR_GRAPH_GUI_NS::PinKind::Input);
            pNode->AddInput(pPin);
        }

        // Создаем выходные пины
        for (uint32_t i = 0; i < pGraphNode->GetOutputCount(); ++i) {
            auto&& pPin = new SR_GRAPH_GUI_NS::Pin("Output " + std::to_string(i), SR_GRAPH_GUI_NS::PinKind::Output);
            pNode->AddOutput(pPin);
        }

        return pNode;
    }

    void AnimatorEditor::UpdateVisualNode(SR_GRAPH_GUI_NS::Node* pVisualNode, SR_ANIMATIONS_NS::AnimationGraphNode* pGraphNode) {
        // Обновляем визуальную ноду на основе данных граф-ноды
        // Пока базовая реализация, можно расширить позже
    }

    void AnimatorEditor::TopPanelSave() {
        if (!m_graph) {
            return;
        }

        if (m_graphPath.IsEmpty()) {
            TopPanelSaveAt();
            return;
        }

        // Синхронизируем визуальные изменения с графом
        SyncVisualNodesToGraph();

        // Сохраняем граф через Asset
        // Asset должен автоматически сохранить граф при изменении через систему сериализации
        // Пока просто синхронизируем данные - сохранение произойдет автоматически
    }

    void AnimatorEditor::TopPanelOpen() {
        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(
            SR_UTILS_NS::ResourceManager::Instance().GetResPath(), 
            { { "Animator", "animator" } }
        );
        
        if (path.empty()) {
            return;
        }

        SetGraphPath(path);
    }

    SR_MATH_NS::FColor AnimatorEditor::GetPinColor(SR_SRLM_NS::DataTypeClass pinType) {
        // Цвета пинов на основе типа (аналогично примеру)
        switch (pinType) {
            case SR_SRLM_NS::DataTypeClass::Flow:
                return SR_MATH_NS::FColor(1.0f, 1.0f, 1.0f, 1.0f); // Белый
            case SR_SRLM_NS::DataTypeClass::Bool:
                return SR_MATH_NS::FColor(0.86f, 0.19f, 0.19f, 1.0f); // Красный
            case SR_SRLM_NS::DataTypeClass::Int8:
            case SR_SRLM_NS::DataTypeClass::Int16:
            case SR_SRLM_NS::DataTypeClass::Int32:
            case SR_SRLM_NS::DataTypeClass::Int64:
            case SR_SRLM_NS::DataTypeClass::UInt8:
            case SR_SRLM_NS::DataTypeClass::UInt16:
            case SR_SRLM_NS::DataTypeClass::UInt32:
            case SR_SRLM_NS::DataTypeClass::UInt64:
                return SR_MATH_NS::FColor(0.27f, 0.79f, 0.61f, 1.0f); // Зеленый
            case SR_SRLM_NS::DataTypeClass::Float:
                return SR_MATH_NS::FColor(0.58f, 0.89f, 0.29f, 1.0f); // Светло-зеленый
            case SR_SRLM_NS::DataTypeClass::String:
                return SR_MATH_NS::FColor(0.49f, 0.08f, 0.60f, 1.0f); // Фиолетовый
            case SR_SRLM_NS::DataTypeClass::Struct:
                return SR_MATH_NS::FColor(0.20f, 0.59f, 0.84f, 1.0f); // Синий
            case SR_SRLM_NS::DataTypeClass::Enum:
                return SR_MATH_NS::FColor(1.0f, 0.19f, 0.19f, 1.0f); // Красный
            case SR_SRLM_NS::DataTypeClass::Array:
                return SR_MATH_NS::FColor(0.85f, 0.0f, 0.72f, 1.0f); // Розовый
            default:
                return SR_MATH_NS::FColor(0.4f, 0.7f, 1.0f, 1.0f); // Голубой по умолчанию
        }
    }

    void AnimatorEditor::OnOpen() {
#ifdef SR_USE_IMGUI_NODE_EDITOR
        if (!m_editor) {
            static auto&& settingsPath = SR_UTILS_NS::ResourceManager::Instance().GetCachePath().Concat("Editor/Configs/AnimatorEditor.json");
            m_editor = SR_GRAPH_GUI_NS::Immediate::CreateEditor(settingsPath.CStr());
        }
#endif
        Super::OnOpen();
    }
}

