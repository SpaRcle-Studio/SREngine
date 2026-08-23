//
// Created by Monika on 18.08.2026.
//

#ifndef SR_ENGINE_CORE_GUI_FLUX_EDITOR_H
#define SR_ENGINE_CORE_GUI_FLUX_EDITOR_H

#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/GUI/FluxEditor/FluxNodeLayout.h>

#include <Graphics/GUI/NodeWidget.h>

#include <Utils/Flux/Graph/FluxGraphAsset.h>

namespace SR_CORE_GUI_NS {
    class FluxEditor : public SR_GRAPH_GUI_NS::NodeWidget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::NodeWidget;
    public:
        FluxEditor();
        ~FluxEditor() override = default;

    public:
        void Inspect(const SR_UTILS_NS::Path& path);
        void Init() override;

    protected:
        void DrawNodeEditor() override;
        void DrawInspectPanel() override;

        void TopPanelSave() override;
        void TopPanelOpen() override;
        void Execute() override;

        void SyncLogicToVisual();
        void SyncVisualToLogic();

        void OnNodeTypeSelected(SR_UTILS_NS::StringAtom type, SR_MATH_NS::FVector2 pos) override;

    private:
        void DrawCreateNodeMenu(const SR_MATH_NS::FVector2& popupPos);
        void DrawNodeInspector(SR_FLUX_NS::FluxGraphNode& node);
        void DrawConstantInspector(SR_FLUX_NS::FluxGraphNode& node);
        void DrawCallableInspector(SR_FLUX_NS::FluxGraphNode& node);
        void DrawVariableSelector(SR_FLUX_NS::FluxGraphNode& node);
        void DrawGraphInspector();

        void OnLinkCreated(SR_IMMEDIATE_GUI_NS::LinkInstance& link);
        void OnLinkDeleted(SR_IMMEDIATE_GUI_NS::LinkInstance& link);
        void OnNodeDeleted(SR_IMMEDIATE_GUI_NS::NodeInstance& node);

        /// удаление откладывается до конца кадра: удаление узла сдвигает индексы остальных,
        /// а за один кадр редактор может удалить сразу несколько элементов
        void ApplyPendingRemoves();

        SR_NODISCARD SR_FLUX_NS::FluxGraph* GetGraph() const;
        SR_NODISCARD SR_FLUX_NS::FluxGraphNode* GetSelectedNode() const;

        /// узлы и связи адресуются индексами, так как указатели на элементы графа
        /// инвалидируются при добавлении и удалении
        SR_NODISCARD static void* IndexToUserData(uint32_t index);
        SR_NODISCARD static uint32_t UserDataToIndex(const void* pUserData);

    protected:
        SR_FLUX_NS::FluxGraphAsset::Ptr m_graphAsset;
        SR_UTILS_NS::Subscription m_onCommandUndoSubscription;
        SR_UTILS_NS::Subscription m_onCommandRedoSubscription;
        SR_UTILS_NS::Subscription m_doInspectEntitySubscription;
        SR_UTILS_NS::String m_backgroundText;
        bool m_skipInspect = false;

        SR_UTILS_NS::Vector<SR_FLUX_NS::FluxGraphLink> m_brokenLinks;
        SR_UTILS_NS::Vector<SR_IMMEDIATE_GUI_NS::NodeInstance*> m_nodes;
        SR_UTILS_NS::Vector<FluxNodeLayout> m_layouts;
        SR_UTILS_NS::Vector<SR_UTILS_NS::Reflection::TypeInfo*> m_tmpTypeInfos;
        SR_UTILS_NS::Vector<uint32_t> m_pendingNodeRemoves;
        SR_UTILS_NS::Vector<SR_FLUX_NS::FluxGraphLink> m_pendingLinkRemoves;

        std::string m_nameBuffer;
        std::string m_objectBuffer;
        std::string m_functionBuffer;
        std::string m_newVariableName;

    };
}

#endif //SR_ENGINE_CORE_GUI_FLUX_EDITOR_H
