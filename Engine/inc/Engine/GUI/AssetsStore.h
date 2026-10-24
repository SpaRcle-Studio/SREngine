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
    class EditorGUI;

    class AssetsStore : public SR_GRAPH_GUI_NS::Widget {
        SR_CLASS()
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        AssetsStore();
        ~AssetsStore() override;

    public:
        static void ReMountPackages(EditorGUI* pEditor);
        static void UnMountPackages(EditorGUI* pEditor);

    protected:
        void Draw() override;
        bool DrawPackage(const EditorPackage& package, bool selected, const SR_MATH_NS::FVector2& size);

    private:
        void InstallPackage(SR_UTILS_NS::StringAtom name);
        void CollectPackageInstallOrder(SR_UTILS_NS::StringAtom name, SR_UTILS_NS::Vector<SR_UTILS_NS::StringAtom>& order);
        void OnPackageInstalled(SR_UTILS_NS::StringAtom name, bool success);

        const EditorPackage* FindPackage(SR_UTILS_NS::StringAtom name) const;

        SR_NODISCARD bool IsPackageInstalling(SR_UTILS_NS::StringAtom name) const;

    private:
        mutable std::recursive_mutex m_mutex;
        struct InstallInfo {
            SR_UTILS_NS::StringAtom name;
            uint64_t taskId = SR_ID_INVALID;
        };
        SR_UTILS_NS::Vector<InstallInfo> m_installQueue;
        uint32_t m_selectedAsset = SR_UINT32_MAX;
        SR_UTILS_NS::ResourceRef<SR_GTYPES_NS::Texture> m_noIconTexture;
        SR_UTILS_NS::String m_packagesPathTmp;
        SR_UTILS_NS::Path m_packagesPath;
        SR_UTILS_NS::RawPointerHolder<SR_UTILS_NS::IVFSBackend> m_pVFSBackend;

        static std::recursive_mutex g_packagesMountMutex;
        struct MountInfo {
            SR_UTILS_NS::StringAtom name;
            SR_UTILS_NS::IVFSBackend* pMount = nullptr;
        };
        static SR_UTILS_NS::Vector<MountInfo> g_mounts;

    };
}

#endif //SR_ENGINE_GUI_ASSETS_STORE_H
