//
// Created by Monika on 14.10.2026.
//

#include <Engine/GUI/RawMeshInspector.h>
#include <Engine/GUI/EditorGUI.h>

#include <Utils/Types/RawMesh.h>
#include <Utils/Animations/SkeletonRig.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Serialization/SRASerialization.h>
#include <Utils/Reflection/Value.h>

#include <Codegen/RawMeshInspector.generated.hpp>

namespace SR_CORE_GUI_NS {
    RawMeshInspector::RawMeshInspector()
        : SR_GRAPH_GUI_NS::Widget("Mesh inspector")
    {
        m_drawer = SR_CORE_GUI_NS::PropertyDrawerBase::MakeShared<ObjectPropertyDrawer>();
        SetDefaultSize(SR_MATH_NS::IVector2(500, 300));
    }

    RawMeshInspector::~RawMeshInspector() {
        ResetRawMesh();
    }

    void RawMeshInspector::ResetRawMesh() {
        if (m_rawMesh) {
            m_rawMesh->RemoveUsePoint();
            m_rawMesh.Reset();
        }
    }

    void RawMeshInspector::Draw() {
        if (!m_rawMesh) {
            SR_GRAPH_GUI_NS::Immediate::TextColored(SR_MATH_NS::FColor(1.f, 0.f, 0.f, 1.f), "No mesh selected");
            return;
        }

        auto&& windowsWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x;

        auto&& path = m_rawMesh->GetResourcePath();
        SR_GRAPH_GUI_NS::Immediate::Text("Mesh: %s", path.c_str());

        if (SR_GRAPH_GUI_NS::Immediate::Button("Save", SR_MATH_NS::FVector2(windowsWidth / 2.f, 0.f))) {
            SR_UTILS_NS::SRASerializer serializer;
            serializer.SetUseTabs(true);
            m_metaInfo.Save(serializer);
            const auto metaPath = SR_UTILS_NS::ResourceManager::Instance().GetResPath().Concat(path).ConcatExt(".meta");
            if (serializer.SaveToFile(metaPath)) {
                SR_UTILS_NS::ResourceManager::Instance().ReloadResource(SR_UTILS_NS::StringAtom(path.View()), SR_HTYPES_NS::RawMesh::GetClassStaticName());
                SR_LOG("RawMeshInspector::Draw() : saved meta info for mesh at path: {}", metaPath);
            }
            else {
                SR_ERROR("RawMeshInspector::Draw() : failed to save meta info for mesh at path: {}", metaPath);
            }
        }

        SR_GRAPH_GUI_NS::Immediate::SameLine();

        if (SR_GRAPH_GUI_NS::Immediate::Button("Discard", SR_MATH_NS::FVector2(windowsWidth / 2.f, 0.f))) {
            m_metaInfo = m_rawMesh->GetMetaInfo();
        }

        SR_GRAPH_GUI_NS::Immediate::Separator();

        auto&& value = SR_UTILS_NS::Reflection::Value::CreateRef(m_metaInfo);
        auto&& context = CreateDrawerContext(&value);

        context.noHeader = true;
        context.openedByDefault = true;
        context.editorPropertyParams.SetNotNull();
        m_drawer->Draw(context);

        if (SR_GRAPH_GUI_NS::Immediate::GetScrollMaxY() > 0) {
            m_scrollBarWidth = SR_GRAPH_GUI_NS::Immediate::GetScrollbarSize();
        }
        else {
            m_scrollBarWidth = 0;
        }
    }

    void RawMeshInspector::Inspect(const SR_UTILS_NS::Path& path) {
        SR_LOG("RawMeshInspector::Inspect() : inspecting mesh at path: {}", path.ToString());

        Open();
        Focus();

        ResetRawMesh();

        m_rawMesh = CoreResLoader::Load<SR_HTYPES_NS::RawMesh>(path);
        if (!m_rawMesh) {
            SR_ERROR("RawMeshInspector::Inspect() : mesh not found at path: {}", path.ToString());
            return;
        }

        m_rawMesh->AddUsePoint();
        m_metaInfo = m_rawMesh->GetMetaInfo();
    }

    PropertyDrawerContext RawMeshInspector::CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue) {
        PropertyDrawerContext context(pValue);
        context.pEditor = dynamic_cast<EditorGUI*>(GetManager());

        const float_t lineHeight = SR_GRAPH_GUI_NS::Immediate::GetFontSize() + SR_GRAPH_GUI_NS::Immediate::GetFramePadding().y * 2.0f;
        const float_t windowWidth = SR_GRAPH_GUI_NS::Immediate::GetWindowSize().x - m_scrollBarWidth;
        context.lineHeight = lineHeight;
        context.axisButtonWidth = context.lineHeight;
        context.spaceWidth = windowWidth;
        context.fieldHeight = lineHeight;
        context.fieldTitleWidth = windowWidth * 0.3f;
        context.fieldWidth = windowWidth * 0.7f;
        context.noHeader = true;

        return context;
    }

    void RawMeshInspector::Close() {
        ResetRawMesh();
        Super::Close();
    }
}
