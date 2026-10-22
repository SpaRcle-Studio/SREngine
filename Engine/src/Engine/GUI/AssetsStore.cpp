//
// Created by Monika on 20.10.2026.
//

#include <Engine/GUI/AssetsStore.h>
#include <Engine/GUI/EditorGUI.h>

#include <Graphics/Overlay/OverlayType.h>
#include <Graphics/Overlay/Overlay.h>
#include <Graphics/Render/RenderContext.h>
#include <Graphics/Pipeline/Pipeline.h>

#include <Utils/Common/StoreUtils.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/FileSystem/FileDialog.h>
#include <Utils/FileSystem/VFS.h>

#include <Codegen/AssetsStore.generated.hpp>
#include <Utils/FileSystem/DirectoryVFSBackend.h>

namespace SR_CORE_GUI_NS {
    AssetsStore::AssetsStore()
        : Super("Assets store")
    {
        SetDefaultSize(SR_MATH_NS::IVector2(800, 600));
        m_noIconTexture = "Editor/Textures/missing.png";
    }

    void AssetsStore::Draw() {
        const static SR_UTILS_NS::StringAtom packagesPathKey = "PackagesPath";
        if (SR_IMMEDIATE_GUI_NS::BeginChild("AssetList", SR_MATH_NS::FVector2(0, 0), SR_IMMEDIATE_GUI_NS::ChildWindowFlags::Borders)) {
            bool pathIsPresent = SR_UTILS_NS::StoreUtils::User::HasString(packagesPathKey);
            m_packagesPathTmp = pathIsPresent ? SR_UTILS_NS::StoreUtils::User::GetString(packagesPathKey) : SR_UTILS_NS::String();

            const float_t availX = SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x;
            const float_t buttonSize = SR_MIN(50.f, availX * 0.2f);
            const float_t inputSize = availX - buttonSize;

            if (SR_IMMEDIATE_GUI_NS::Button("...", SR_MATH_NS::FVector2(buttonSize, 0.f))) {
                m_packagesPathTmp = SR_UTILS_NS::FileDialog::Instance().PickFolder(CoreResLoader::GetResPath()).ToStringRef();
            }
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::PushItemWidth(inputSize);
            if (SR_IMMEDIATE_GUI_NS::InputText("##InputPath", &m_packagesPathTmp, SR_GRAPH_GUI_NS::Immediate::InputTextFlags::EnterReturnsTrue)) {
                m_packagesPathTmp = SR_UTILS_NS::StringUtils::RemoveCharsFromString(m_packagesPathTmp, "\"");
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();
            pathIsPresent &= !m_packagesPathTmp.empty();
            if (!pathIsPresent) {
                SR_IMMEDIATE_GUI_NS::WarningBox("You need to select valid folder for packages!");
                SR_IMMEDIATE_GUI_NS::BeginDisabled(true);
            }

            if (pathIsPresent && m_packagesPathTmp != m_packagesPath) {
                m_packagesPath = m_packagesPathTmp;
                m_pVFSBackend = new SR_UTILS_NS::DirectoryVFSBackend(m_packagesPath);
                m_pVFSBackend.SetDeleter([](SR_UTILS_NS::IVFSBackend* pVFS) {
                    SR_UTILS_NS::VFS::Instance().Unmount(pVFS);
                    delete pVFS;
                });
                SR_UTILS_NS::VFS::Instance().Mount(m_packagesPath, m_pVFSBackend.Get(), -10000);

                SR_UTILS_NS::StoreUtils::User::SetString(packagesPathKey, m_packagesPath);
                SR_UTILS_NS::StoreUtils::Storage::Instance().Save();
            }

            SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0, 6.0f));

            auto&& pSettings = dynamic_cast<EditorGUI*>(GetManager())->GetSettings();
            uint64_t index = 0;
            for (auto&& package : pSettings->GetPackages()) {
                SR_IMMEDIATE_GUI_NS::PushID(index++);
                if (DrawPackage(package, index == m_selectedAsset, SR_MATH_NS::FVector2(availX, 100.0f))) {
                    m_selectedAsset = index;
                }
                SR_IMMEDIATE_GUI_NS::Dummy(SR_MATH_NS::FVector2(0, 6.0f));
                SR_IMMEDIATE_GUI_NS::PopID();
            }

            if (!pathIsPresent) {
                SR_IMMEDIATE_GUI_NS::EndDisabled();
            }
        }
        SR_IMMEDIATE_GUI_NS::EndChild();
    }

    bool AssetsStore::DrawPackage(const EditorPackage& package, bool selected, const SR_MATH_NS::FVector2& size) {
        const bool isNotAvailable = package.url.empty();

        if (isNotAvailable) {
            SR_IMMEDIATE_GUI_NS::BeginDisabled(true);
        }

        const SR_MATH_NS::FVector2 pos = SR_IMMEDIATE_GUI_NS::GetCursorScreenPos();
        const SR_MATH_NS::FVector2 end = SR_MATH_NS::FVector2(pos.x + size.x, pos.y + size.y);

        SR_IMMEDIATE_GUI_NS::InvisibleButton("##asset", size);

        const bool hovered = SR_IMMEDIATE_GUI_NS::IsItemHovered();
        const bool clicked = SR_IMMEDIATE_GUI_NS::IsItemClicked();

        auto&& pDrawList = SR_IMMEDIATE_GUI_NS::GetWindowDrawList();

        const auto bg = SR_IMMEDIATE_GUI_NS::GetColorU32(
            selected ? SR_IMMEDIATE_GUI_NS::StyleColor::Header :
            hovered  ? SR_IMMEDIATE_GUI_NS::StyleColor::HeaderHovered :
            SR_IMMEDIATE_GUI_NS::StyleColor::ChildBg
        );

        const auto border = SR_IMMEDIATE_GUI_NS::GetColorU32(
            selected ? SR_IMMEDIATE_GUI_NS::StyleColor::CheckMark :
            SR_IMMEDIATE_GUI_NS::StyleColor::Border
        );

        SR_IMMEDIATE_GUI_NS::DrawListAddRectFilled(pDrawList, pos, end, bg, 6.0f);
        SR_IMMEDIATE_GUI_NS::DrawListAddRect(pDrawList, pos, end, border, 6.0f);

        const float_t padding = 10.0f;
        const float_t iconSize = size.y - padding * 2.0f;

        const SR_MATH_NS::FVector2 iconMin(pos.x + padding, pos.y + padding);
        const SR_MATH_NS::FVector2 iconMax(iconMin.x + iconSize, iconMin.y + iconSize);

        if (m_noIconTexture) {
            if (auto&& pDescriptor = m_noIconTexture.GetResource()->GetDescriptor()) {
                SR_IMMEDIATE_GUI_NS::AddImage(pDrawList, pDescriptor, iconMin, iconMax);
            }
        }

        const float textX = iconMax.x + 14.0f;

        const SR_MATH_NS::FVector2 buttonSize(112.0f, 30.0f);
        const float_t buttonPadding = 10.0f;

        const SR_MATH_NS::FVector2 buttonMin(end.x - buttonSize.x - buttonPadding, pos.y + buttonPadding);
        const SR_MATH_NS::FVector2 buttonMax(buttonMin.x + buttonSize.x, buttonMin.y + buttonSize.y);

        const auto cursorPos = SR_IMMEDIATE_GUI_NS::GetCursorScreenPos();
        SR_IMMEDIATE_GUI_NS::SetCursorScreenPos(buttonMin);

        const bool installPressed = SR_IMMEDIATE_GUI_NS::InvisibleButton("##Install", buttonSize);
        const bool installHovered = SR_IMMEDIATE_GUI_NS::IsItemHovered();

        static const auto green = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.20f, 0.75f, 0.35f, 1.0f));
        static const auto greenHovered = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.25f, 0.90f, 0.40f, 1.0f));
        static const auto greenBg = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.08f, 0.20f, 0.11f, 1.0f));
        static const auto greenBgHovered = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.12f, 0.30f, 0.16f, 1.0f));

        static const auto red = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.75f, 0.20f, 0.35f, 1.0f));
        static const auto redHovered = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.90f, 0.25f, 0.40f, 1.0f));
        static const auto redBg = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.20f, 0.08f, 0.11f, 1.0f));
        static const auto redBgHovered = SR_IMMEDIATE_GUI_NS::ColorConvertFloat4ToU32(SR_MATH_NS::FVector4(0.30f, 0.12f, 0.16f, 1.0f));

        const auto buttonBg = isNotAvailable ? (installHovered ? redBgHovered : redBg) : (installHovered ? greenBgHovered : greenBg);
        const auto defaultColor = isNotAvailable ? red : green;
        const auto hoveredColor = isNotAvailable ? redHovered : greenHovered;

        SR_IMMEDIATE_GUI_NS::DrawListAddRectFilled(pDrawList, buttonMin, buttonMax, buttonBg, 5.0f);
        SR_IMMEDIATE_GUI_NS::DrawListAddRect(pDrawList, buttonMin, buttonMax, installHovered ? hoveredColor : defaultColor, 5.0f, SR_IMMEDIATE_GUI_NS::DrawFlags(), 1.5f);

        const char* installText = isNotAvailable ? "Coming soon..." : "Install";
        const auto textSize = SR_IMMEDIATE_GUI_NS::CalcTextSize(installText);

        SR_IMMEDIATE_GUI_NS::AddText(pDrawList,
            SR_MATH_NS::FVector2(
                buttonMin.x + (buttonSize.x - textSize.x) * 0.5f,
                buttonMin.y + (buttonSize.y - textSize.y) * 0.5f
            ),
            installHovered ? hoveredColor : defaultColor,
            installText
        );

        SR_IMMEDIATE_GUI_NS::AddText(pDrawList, SR_MATH_NS::FVector2(textX, pos.y + 12.0f),
            SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::Text),
            package.name.c_str()
        );

        SR_IMMEDIATE_GUI_NS::AddText(pDrawList, SR_MATH_NS::FVector2(textX, pos.y + 34.0f),
            SR_IMMEDIATE_GUI_NS::GetColorU32(SR_IMMEDIATE_GUI_NS::StyleColor::TextDisabled),
            package.description.c_str()
        );

        SR_IMMEDIATE_GUI_NS::SetCursorScreenPos(cursorPos);

        if (isNotAvailable) {
            SR_IMMEDIATE_GUI_NS::EndDisabled();
        }

        return clicked || installPressed;
    }
}