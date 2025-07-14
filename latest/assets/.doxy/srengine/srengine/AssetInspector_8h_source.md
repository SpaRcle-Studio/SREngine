

# File AssetInspector.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**inc**](dir_384e30eefdcc60ad4aa259e47cd19ad6.md) **>** [**Engine**](dir_92c4f4d9e201e1e90834671676ddd6c7.md) **>** [**GUI**](dir_46dcd1c0cbf69a89692948707017f5a0.md) **>** [**AssetInspector.h**](AssetInspector_8h.md)

[Go to the documentation of this file](AssetInspector_8h.md)


```C++
//
// Created by Monika on 12.07.2025.
//

#ifndef SR_ENGINE_GUI_ASSET_INSPECTOR_H
#define SR_ENGINE_GUI_ASSET_INSPECTOR_H

#include <Engine/GUI/ComponentDrawer.h>
#include <Engine/GUI/PropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/ObjectPropertyDrawer.h>
#include <Engine/GUI/PropertyDrawers/PointerPropertyDrawer.h>

#include <Graphics/GUI/Widget.h>

#include <Utils/Resources/Asset.h>

namespace SR_CORE_GUI_NS {
    class AssetInspector : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        AssetInspector();
        ~AssetInspector() override;

    public:
        void Inspect(const SR_UTILS_NS::Path& path);

    private:
        void Update(float_t dt) override;
        void Draw() override;
        void Close() override;

        SR_NODISCARD PropertyDrawerContext CreateDrawerContext(SR_UTILS_NS::Reflection::Value* pValue);

    private:
        SR_UTILS_NS::Asset::Ptr m_pAsset;

        struct Context {
            SR_UTILS_NS::TimePointType lastUsage;
            ObjectPropertyDrawer::Ptr pObjectDrawer;
        };
        std::map<void*, Context> m_contexts;
        uint64_t m_maxContexts = 100;

        SR_CORE_GUI_NS::PointerPropertyDrawer::Ptr m_pPointerDrawer;
        float_t m_scrollBarWidth = 0.0f;
        bool m_isDragMode = false;
        SR_UTILS_NS::Subscription m_moduleReloadSubscription;
        SR_HTYPES_NS::Function<void(bool drag)> m_onBeforeChangeCallback;

    };
}

#endif //SR_ENGINE_GUI_ASSET_INSPECTOR_H
```


