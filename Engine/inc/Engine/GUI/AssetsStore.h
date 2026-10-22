//
// Created by Monika on 20.10.2026.
//

#ifndef SR_ENGINE_GUI_ASSETS_STORE_H
#define SR_ENGINE_GUI_ASSETS_STORE_H

#include <Engine/Settings/EditorSettings.h>

#include <Graphics/GUI/Widget.h>
#include <Graphics/Types/Texture.h>

#include <Utils/FileSystem/IVFSBackend.h>

namespace SR_CORE_GUI_NS {
    class AssetsStore : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        AssetsStore();

    protected:
        void Draw() override;
        bool DrawPackage(const EditorPackage& package, bool selected, const SR_MATH_NS::FVector2& size);

    private:
        uint32_t m_selectedAsset = SR_UINT32_MAX;
        SR_UTILS_NS::ResourceRef<SR_GTYPES_NS::Texture> m_noIconTexture;
        SR_UTILS_NS::String m_packagesPathTmp;
        SR_UTILS_NS::String m_packagesPath;
        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> m_pVFSBackend;

    };
}

#endif //SR_ENGINE_GUI_ASSETS_STORE_H
