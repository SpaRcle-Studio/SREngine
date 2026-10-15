//
// Created by Monika on 14.10.2026.
//

#ifndef SR_ENGINE_GUI_RAW_MESH_INSPECTOR_H
#define SR_ENGINE_GUI_RAW_MESH_INSPECTOR_H

#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>

#include <Graphics/GUI/Widget.h>

#include <Utils/Types/RawMeshMetaInfo.h>

namespace SR_HTYPES_NS {
    class RawMesh;
}

namespace SR_CORE_GUI_NS {
    class RawMeshInspector : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        RawMeshInspector();
        ~RawMeshInspector() override;

    public:
        void Inspect(const SR_UTILS_NS::Path& path);

    private:
        void Draw() override;
        void Close() override;

        void ResetRawMesh();

        SR_NODISCARD PropertyDrawerContext CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue);

    private:
        SR_HTYPES_NS::SharedPtr<SR_HTYPES_NS::RawMesh> m_rawMesh;
        SR_HTYPES_NS::RawMeshMetaInfo m_metaInfo;

        SR_CORE_GUI_NS::ObjectPropertyDrawer::Ptr m_drawer;
        float_t m_scrollBarWidth = 0.0f;

    };
}

#endif //SR_ENGINE_GUI_RAW_MESH_INSPECTOR_H
