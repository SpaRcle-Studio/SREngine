//
// Created by Monika on 08.12.2025.
//

#ifndef SR_ENGINE_GUI_TEXTURE_INSPECTOR_H
#define SR_ENGINE_GUI_TEXTURE_INSPECTOR_H

#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PointerPropertyDrawer.h>

#include <Graphics/GUI/Widget.h>
#include <Graphics/Utils/ImageMetaInfo.h>

namespace SR_GTYPES_NS {
    class Texture;
}

namespace SR_CORE_GUI_NS {
    /// @inspector(TextureInspector)
    class TextureInspector : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        TextureInspector();
        ~TextureInspector() override;

    public:
        void Inspect(const SR_UTILS_NS::Path& path);

    private:
        void Draw() override;
        void Close() override;

        SR_NODISCARD PropertyDrawerContext CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue);

    private:
        SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Texture> m_texture;
        SR_GRAPH_NS::ImageMetaInfo m_imageMetaInfo;
        SR_GRAPH_NS::ImageMetaInfo m_originalImageMetaInfo;

        struct Context {
            SR_UTILS_NS::TimePointType lastUsage;
            ObjectPropertyDrawer::Ptr pObjectDrawer;
        };
        SR_UTILS_NS::Map<void*, Context> m_contexts;
        uint64_t m_maxContexts = 100;

        SR_CORE_GUI_NS::ObjectPropertyDrawer::Ptr m_drawer;
        float_t m_scrollBarWidth = 0.0f;
        bool m_isDragMode = false;
        SR_UTILS_NS::Subscription m_moduleReloadSubscription;
        SR_HTYPES_NS::Function<void(bool drag)> m_onBeforeChangeCallback;

    };
}

#endif //SR_ENGINE_GUI_TEXTURE_INSPECTOR_H
