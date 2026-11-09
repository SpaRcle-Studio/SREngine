//
// Created by Monika on 27.12.2021.
//

#include <Engine/Engine.h>
#include <Engine/Settings/EditorSettings.h>
#include <Engine/Settings/ProjectSettings.h>
#include <Engine/GUI/EditorGUI.h>
#include <Engine/GUI/FileBrowser.h>
#include <Engine/GUI/AnimatorEditor/AnimatorEditor.h>
#include <Engine/GUI/FluxEditor/FluxEditor.h>
#include <Engine/GUI/TextureInspector.h>
#include <Engine/GUI/RawMeshInspector.h>
#include <Engine/GUI/AssetInspector.h>

#include <Graphics/GUI/Icons.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Material/FileMaterial.h>
#include <Graphics/Animations/AnimationClip.h>
#include <Graphics/Overlay/ImGuiOverlay.h>
#include <Graphics/Render/RenderTechnique.h>
#include <Graphics/Pipeline/Pipeline.h>
#include <Graphics/Render/RenderContext.h>

#include <Utils/ECS/Prefab.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/TypeTraits/Factory.h>
#include <Utils/Common/StoreUtils.h>
#include <Utils/FileSystem/Path.h>
#include <Utils/Common/VectorUtils.h>
#include <Utils/TypeTraits/SRClassMeta.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/StringUtils.h>
#include <Utils/FileSystem/FileSystem.h>
#include <Utils/FileSystem/VFS.h>

#include <Enum/TreeNodeFlags.hpp>

#include <Codegen/FileBrowser.generated.hpp>

namespace SR_CORE_NS::GUI {
    FileBrowser::FileBrowser()
        : Widget("Assets")
    {
        SetFolder(CoreResLoader::GetResPath());
    }

    FileBrowser::~FileBrowser() {
        FreeTextures();
    }

    void FileBrowser::SetFolder(const SR_UTILS_NS::Path &path) {
        m_selectedDir = m_defaultRoot = path;
        m_dirtySelectedDir = true;
        m_dirtyFoldersTree = true;

        if (!m_selectedDir.IsDir()) {
            SR_ERROR("FileBrowser::SetFolder() : path is not folder! \n\tPath: " + m_selectedDir.ToString());
        }
    }

    void FileBrowser::CurrentDirectoryContextMenu(){
        SR_TRACY_ZONE;
        if(SR_IMMEDIATE_GUI_NS::BeginPopupContextWindow()){
            if (SR_IMMEDIATE_GUI_NS::Selectable("Paste")) {
                SR_UTILS_NS::Platform::PasteFilesFromClipboard(m_selectedDir);
                m_dirtySelectedDir = true;
            }
            if (SR_IMMEDIATE_GUI_NS::Selectable("Open in native Explorer")) {
                SR_UTILS_NS::Path path = m_selectedDir;
                SR_UTILS_NS::VFS::Instance().ResolvePath(path, SR_UTILS_NS::FileMode::None);
                SR_UTILS_NS::Platform::OpenWithAssociatedApp(path);
            }
            if (SR_IMMEDIATE_GUI_NS::Selectable("Refresh")) {
                m_dirtySelectedDir = true;
            }
            SR_IMMEDIATE_GUI_NS::EndPopup();
        }
    }

    void FileBrowser::CacheElements(const SR_UTILS_NS::Path& root) {
        SR_TRACY_ZONE;
        FreeTextures();

        root.GetAll(m_currentDirElements);
        SR_UTILS_NS::String extension;
        for (const auto& path : m_currentDirElements) {
            if (path.GetBaseName().empty()) {
                continue;
            }
            else {
                FBElement current;
                current.filename = path.GetBaseNameAndExt();
                current.isDir = path.IsDir();
                current.isReadonly = !SR_UTILS_NS::VFS::Instance().IsWritable(path);

                current.cutName = SR_UTILS_NS::StringUtils::CutName(current.filename, static_cast<uint32_t>(17.f * m_itemsScale));

                extension = path.GetExtensionView();
                SR_UTILS_NS::StringUtils::Instance().ToLower(extension);
                if (extension == "meta") {
                    continue;
                }

                if (extension.empty()) { //TODO Сделать красивым
                    path.IsEmpty() ? current.iconType = Core::EditorIcon::EmptyFolder
                                   : current.iconType = Core::EditorIcon::Folder;
                } else if (extension == "zip") {
                    current.iconType = Core::EditorIcon::ZIP;
                } else if ((extension == "jpg") || (extension == "jpeg")) {
                    current.iconType = Core::EditorIcon::JPG;
                } else if ((extension == "obj") || (extension == "fbx")) {
                    current.iconType = Core::EditorIcon::Shapes;
                } else if ((extension == "wav") || (extension == "mp3") || (extension == "ogg")) {
                    current.iconType = Core::EditorIcon::Audio;
                } else if (extension == "txt") {
                    current.iconType = Core::EditorIcon::TXT;
                } else if (extension == "srsl") {
                    current.iconType = Core::EditorIcon::Shader;
                } else if (extension == "mat") {
                    current.iconType = Core::EditorIcon::Material;
                } else if (extension == "ttf" || extension == "font") {
                    current.iconType = Core::EditorIcon::Font;
                } else if (extension == "prefab") {
                    current.iconType = Core::EditorIcon::Prefab;
                } else if (extension == "srtech") {
                    current.iconType = Core::EditorIcon::RenderTechnique;
                } else if (extension == "theme") {
                    current.iconType = Core::EditorIcon::Theme;
                } else if (extension == "animation") {
                    current.iconType = Core::EditorIcon::Animation;
                } else if (extension == "animator") {
                    current.iconType = Core::EditorIcon::Animator;
                } else if (extension == "sras") {
                    current.iconType = Core::EditorIcon::Asset;
                } else if (extension == "scene") {
                    current.iconType = Core::EditorIcon::Scene;
                } else if (extension == "cpp" || extension == "h" || extension == "hpp") {
                    current.iconType = Core::EditorIcon::Script;
                } else if (extension == "xml") {
                    current.iconType = Core::EditorIcon::XML;
                } else if (extension == "png") {
                    current.iconType = Core::EditorIcon::PNG;
                }
                else if (extension == "dll") {
                    current.iconType = Core::EditorIcon::DLL;
                } else {
                    current.iconType = Core::EditorIcon::File;
                }

                if (extension == "png" || extension == "jpg") {
                    if (!current.pTexture) {
                        if (auto&& pTexture = CoreResLoader::Load<SR_GTYPES_NS::Texture>(path)) {
                            pTexture->AddUsePoint();
                            current.pTexture = pTexture;
                        }
                    }
                }
                
                m_elements.emplace_back(current);
            }
        }
        m_dirtySelectedDir = false;
    }

    void FileBrowser::DrawFoldersTree(FBFolder& parentFolder) {
        SR_TRACY_ZONE;
        const auto WITH_CHILD = SR_IMMEDIATE_GUI_NS::TreeNodeFlags::OpenOnArrow | SR_IMMEDIATE_GUI_NS::TreeNodeFlags::OpenOnDoubleClick;
        const auto SELECTED_WITH_CHILD = SR_IMMEDIATE_GUI_NS::TreeNodeFlags::OpenOnArrow | SR_IMMEDIATE_GUI_NS::TreeNodeFlags::OpenOnDoubleClick | SR_IMMEDIATE_GUI_NS::TreeNodeFlags::Selected;
        const auto WITHOUT_CHILD = SR_IMMEDIATE_GUI_NS::TreeNodeFlags::NoTreePushOnOpen | SR_IMMEDIATE_GUI_NS::TreeNodeFlags::Leaf;
        const auto SELECTED_WITHOUT_CHILD = SR_IMMEDIATE_GUI_NS::TreeNodeFlags::NoTreePushOnOpen | SR_IMMEDIATE_GUI_NS::TreeNodeFlags::Leaf | SR_IMMEDIATE_GUI_NS::TreeNodeFlags::Selected;

        unsigned short index = 0;
        for (auto& folder : parentFolder.innerFolders) {
            const bool selected = m_selectedDir.GetHash() == folder.path.GetHash();
            const bool isLeaf = !folder.hasSubfolders;

            if (folder.isReadonly) {
                SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(0.7f, 0.5f, 0.5f, 1.0f));
            }

            if (isLeaf) {
                SR_IMMEDIATE_GUI_NS::TreeNodeEx((void*)(intptr_t)index, selected ? SELECTED_WITHOUT_CHILD : WITHOUT_CHILD, "%s",
                    folder.filename.c_str());

                if (SR_IMMEDIATE_GUI_NS::IsItemClicked()) {
                    m_selectedDir = folder.path;
                    m_dirtySelectedDir = true;
                    m_dirtyFoldersTree = true;
                }
            } else {
                bool open = SR_IMMEDIATE_GUI_NS::TreeNodeEx((void*)(intptr_t)index, selected ? SELECTED_WITH_CHILD : WITH_CHILD,
                    "%s", folder.filename.c_str());

                if (SR_IMMEDIATE_GUI_NS::IsItemClicked() && !SR_IMMEDIATE_GUI_NS::IsItemToggledOpen()) {
                    m_selectedDir = folder.path;
                    m_dirtySelectedDir = true;
                    m_dirtyFoldersTree = true;
                }

                if (open) {
                    LoadFolderChildren(folder);
                    DrawFoldersTree(folder);
                    SR_IMMEDIATE_GUI_NS::TreePop();
                }
            }

            if (folder.isReadonly) {
                SR_IMMEDIATE_GUI_NS::PopStyleColor();
            }

            index++;
        }
    }

    void FileBrowser::LoadFolderChildren(FBFolder& parentFolder) {
        SR_TRACY_ZONE;
        if (parentFolder.childrenLoaded) {
            return;
        }
        SR_UTILS_NS::Vector<SR_UTILS_NS::Path> folders;
        parentFolder.path.GetFolders(folders);
        parentFolder.innerFolders.clear();
        for (const auto& path : folders) {
            if (path.IsEmpty()) {
                continue;
            }
            FBFolder child;
            child.path = path;
            child.filename = path.GetBaseNameAndExt();
            child.childrenLoaded = false;
            path.GetFolders(m_tmp);
            child.hasSubfolders = !m_tmp.empty();
            child.isReadonly = !SR_UTILS_NS::VFS::Instance().IsWritable(path);
            parentFolder.innerFolders.emplace_back(std::move(child));
        }
        parentFolder.childrenLoaded = true;
    }

    void FileBrowser::FileContextMenu(const std::string &filename){
        SR_TRACY_ZONE;
        if (!SR_IMMEDIATE_GUI_NS::BeginPopupContextItem()) {
            return;
        }

        if (SR_IMMEDIATE_GUI_NS::Selectable("Open")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            OpenFileWithApp(path);
        }
        //if (SR_IMMEDIATE_GUI_NS::Selectable("Extract animations")) {
        //    SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
        //    //auto&& animations = SR_ANIMATIONS_NS::AnimationClip::Load(path);
        //    //for (auto&& pAnimation : animations) {
        //    //   // pAnimation->Save()
        //    //}
        //}
        if (SR_IMMEDIATE_GUI_NS::Selectable("Copy path")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            SR_UTILS_NS::Platform::TextToClipboard(path.ToString());
        }
        if (SR_IMMEDIATE_GUI_NS::Selectable("Copy")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            std::list<SR_UTILS_NS::Path> paths({path}); ///TODO: убрать, когда будет сделано выделение нескольких файлов и их передача в метод
            SR_UTILS_NS::Platform::CopyFilesToClipboard(paths);
        }
        if (SR_IMMEDIATE_GUI_NS::Selectable("Cut")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            ///SR_UTILS_NS::Platform::CopyFilesToClipboard(paths);
            ///for (auto &&path:paths) {
            /// SR_UTILS_NS::Platform::Delete(path);
            ///}
            m_dirtySelectedDir = true;
        }
        if (SR_IMMEDIATE_GUI_NS::Selectable("Paste")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            SR_UTILS_NS::Platform::PasteFilesFromClipboard(path);
            m_dirtySelectedDir = true;
        }
        if (SR_IMMEDIATE_GUI_NS::Selectable("Delete")) {
            SR_UTILS_NS::Path path = m_selectedDir.Concat(filename);
            ///метод Delete является слишком опасным, поскольку проводит удаление рекурсивно и безвозвратно
            ///TODO:раскомментировать SR_UTILS_NS::Platform::Delete, если обезопасили от безвозвратного удаления файлов
            ///SR_UTILS_NS::Platform::Delete(path);
            m_dirtySelectedDir = true;
        }

        SR_IMMEDIATE_GUI_NS::EndPopup();
    }

    void FileBrowser::CurrentDirectoryPanel() {
        SR_TRACY_ZONE;

        const float_t fontSize = SR_UTILS_NS::StoreUtils::User::GetFloat("EditorFontSize", SR_IMMEDIATE_GUI_NS::DEFAULT_FONT_SIZE);
        const float_t panelHeight = fontSize * 1.6f;

        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FrameRounding, 0.0f);
        SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::FramePadding, SR_MATH_NS::FVector2(1.f, 1.f) * fontSize * 0.25f);

        if (SR_IMMEDIATE_GUI_NS::BeginChild("current directory panel", SR_MATH_NS::FVector2(0.f, panelHeight)))
        {
            SR_IMMEDIATE_GUI_NS::PushItemWidth(fontSize * 6.f);
            if (SR_IMMEDIATE_GUI_NS::SliderFloat("##assets-scale", &m_itemsScale, 0.0, 4.0)) {
                m_dirtySelectedDir = true;
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            SR_IMMEDIATE_GUI_NS::SameLine();

            if (SR_IMMEDIATE_GUI_NS::Button("Back", SR_MATH_NS::FVector2(fontSize * 4.f, 0.f))) {
                auto&& prevPath = m_selectedDir.GetPrevious();
                m_selectedDir = prevPath;
                m_dirtySelectedDir = true;
            }

            SR_IMMEDIATE_GUI_NS::SameLine();

            if (SR_IMMEDIATE_GUI_NS::Button("Home", SR_MATH_NS::FVector2(fontSize * 4.f, 0.f))) {
                m_selectedDir = "";
                m_dirtySelectedDir = true;
            }
            /// Current Directory Text
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::Text("%s", m_selectedDir.empty() ? "Home" : m_selectedDir.c_str());
            /// Refresh Button
            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::SetCursorPosX(SR_IMMEDIATE_GUI_NS::GetCursorPos().x + SR_IMMEDIATE_GUI_NS::GetContentRegionAvail().x - panelHeight);

            if (SR_IMMEDIATE_GUI_NS::ImageButton(dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(Core::EditorIcon::Reset), panelHeight - 10.f)){
                m_dirtySelectedDir = true;
                m_dirtyFoldersTree = true;
            }

            SR_IMMEDIATE_GUI_NS::EndChild();
        }

        SR_IMMEDIATE_GUI_NS::PopStyleVar(2);
    }

    void FileBrowser::ItemViewPanel() {
        SR_TRACY_ZONE;
        auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
        auto&& pOverlay = pEngine->GetRenderContext()->GetPipeline()->GetOverlay(SR_GRAPH_NS::OverlayType::ImGui);
        auto&& pSmallFont = pOverlay.DynamicCast<SR_GRAPH_NS::ImGuiOverlay>()->GetMainFont();

        const float frameHeight = SR_IMMEDIATE_GUI_NS::GetFrameHeightWithSpacing();

        if (SR_IMMEDIATE_GUI_NS::BeginChild("item view", SR_MATH_NS::FVector2(0, -frameHeight * 1.2f)))
        {
            SR_IMMEDIATE_GUI_NS::Separator();

            CurrentDirectoryContextMenu();

            auto wndSize = SR_IMMEDIATE_GUI_NS::GetWindowSize();

            uint32_t index = 1;

            const float_t fontSize = SR_UTILS_NS::StoreUtils::User::GetFloat("EditorFontSize", SR_IMMEDIATE_GUI_NS::DEFAULT_FONT_SIZE);
            const float_t iconSize = fontSize * 6.0f * m_itemsScale;

            for (const auto &element : m_elements) {
                ++index;

                SR_IMMEDIATE_GUI_NS::BeginGroup();

                if (element.isReadonly) {
                    SR_IMMEDIATE_GUI_NS::PushStyleColor(SR_IMMEDIATE_GUI_NS::StyleColor::Text, SR_MATH_NS::FColor(0.7f, 0.5f, 0.5f, 1.0f));
                }

                SR_IMMEDIATE_GUI_NS::PushID(element.filename.c_str());
                if (element.isDir) {
                    void* descriptor = dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(element.iconType);

                    if (SR_IMMEDIATE_GUI_NS::ImageButtonDouble("", descriptor, SR_MATH_NS::FVector2(iconSize), iconSize / 3.f)) {
                        m_selectedDir = m_selectedDir.Concat(element.filename);
                        m_dirtySelectedDir = true;
                    }

                    FileContextMenu(element.filename);
                }
                else {
                    void* descriptor = nullptr;

                    if (element.pTexture && element.pTexture->CanBeUsed()) {
                        descriptor = element.pTexture->GetDescriptor();
                    }

                    if (!descriptor) {
                        descriptor = dynamic_cast<EditorGUI *>(GetManager())->GetIconDescriptor(element.iconType);
                    }

                    if (SR_IMMEDIATE_GUI_NS::ImageButtonDouble("", descriptor, SR_MATH_NS::FVector2(iconSize), iconSize / 3.f)) {
                        SR_UTILS_NS::Path path = m_selectedDir.Concat(element.filename);
                        OpenFileWithApp(path);
                    }

                    FileContextMenu(element.filename);
                }

                SR_IMMEDIATE_GUI_NS::PopID();
                SR_IMMEDIATE_GUI_NS::PushFont(pSmallFont);
                SR_IMMEDIATE_GUI_NS::Text("%s", element.cutName.c_str());
                SR_IMMEDIATE_GUI_NS::PopFont();

                SR_IMMEDIATE_GUI_NS::EndGroup();

                if (element.isReadonly) {
                    SR_IMMEDIATE_GUI_NS::PopStyleColor();
                }

                if ((SR_IMMEDIATE_GUI_NS::GetItemRectSize().x * index) + m_assetWidth < wndSize.x) {
                    SR_IMMEDIATE_GUI_NS::SameLine();
                }
                else {
                    index = 1;
                }
            }

            CheckHovered();
            CheckFocused();

        }
        SR_IMMEDIATE_GUI_NS::EndChild();

        if (SR_IMMEDIATE_GUI_NS::BeginChild("create new asset"))
        {
            SR_IMMEDIATE_GUI_NS::Separator();

            auto wndSize = SR_IMMEDIATE_GUI_NS::GetWindowSize();

            bool isAvailable = true;

            isAvailable &= m_newAssetIndex >= 0 && m_newAssetIndex < (int32_t)m_availableAssets.size();
            isAvailable &= m_newAssetPath.IsValidPath() && !SR_UTILS_NS::VFS::Instance().IsExists(m_newAssetPath);

            {
                SR_GRAPH_GUI_NS::ImGuiDisabledLockGuard lock(!isAvailable);
                if (SR_IMMEDIATE_GUI_NS::Button("Create asset") && isAvailable) {
                    auto&& pAsset = SR_UTILS_NS::Asset::CreateNew(m_newAssetPath, m_availableAssets[m_newAssetIndex]);
                    if (pAsset) {
                        pAsset->Destroy();
                    }
                    m_dirtySelectedDir = true;
                    m_newAssetPath.clear();
                    m_newAssetName.clear();
                    m_newAssetIndex = -1;
                }
            }

            bool doUpdatePath = false;

            SR_IMMEDIATE_GUI_NS::SameLine();

            SR_IMMEDIATE_GUI_NS::PushItemWidth(wndSize.x * 0.25f);
            if (SR_IMMEDIATE_GUI_NS::Combo("Type", &m_newAssetIndex, m_comboBoxBuffer.data())) {
                doUpdatePath = true;
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            SR_IMMEDIATE_GUI_NS::SameLine();
            SR_IMMEDIATE_GUI_NS::PushItemWidth(wndSize.x * 0.25f);
            if (SR_IMMEDIATE_GUI_NS::InputText("Name", &m_newAssetName)) {
                std::erase_if(m_newAssetName, [](char c) {
                    return !SR_UTILS_NS::FileSystem::IsAllowedPathSymbol(c) || SR_UTILS_NS::FileSystem::IsPathSeparator(c);
                });
                doUpdatePath = true;
            }
            SR_IMMEDIATE_GUI_NS::PopItemWidth();

            if (doUpdatePath) {
                m_newAssetPath = m_selectedDir.Concat(m_newAssetName);
                if (m_newAssetIndex >= 0 && m_newAssetIndex < (int32_t)m_availableAssets.size()) {
                    std::string_view extension = SR_UTILS_NS::Factory::Instance().GetType(m_availableAssets[m_newAssetIndex])->GetExtension();
                    if (m_newAssetName.ends_with(extension) && m_newAssetName.size() > extension.size() && m_newAssetName[m_newAssetName.size() - extension.size() - 1] == '.') {
                        /// ok
                    }
                    else {
                        m_newAssetPath = m_newAssetPath.ConcatExt(extension);
                    }
                }
            }
        }
        SR_IMMEDIATE_GUI_NS::EndChild();
    }

    void FileBrowser::FileCatalogPanel(const float_t& leftWidth) {
        SR_TRACY_ZONE;

        if (SR_IMMEDIATE_GUI_NS::BeginChild("left panel", SR_MATH_NS::FVector2(leftWidth, 0)))
        {
            SR_IMMEDIATE_GUI_NS::PushStyleVar(SR_IMMEDIATE_GUI_NS::StyleVar::IndentSpacing, SR_IMMEDIATE_GUI_NS::GetFontSize());

            DrawFoldersTree(m_foldersTree);

            m_assetWidth = SR_IMMEDIATE_GUI_NS::GetItemRectSize().x;

            SR_IMMEDIATE_GUI_NS::PopStyleVar();

            CheckHovered();
            CheckFocused();

            SR_IMMEDIATE_GUI_NS::EndChild();
        }
    }

    void FileBrowser::Draw() {
        // left
        SR_TRACY_ZONE;

        m_assetWidth = 0.f;

        const float_t leftWidth = 250;

        if (m_dirtyFoldersTree) {
            m_foldersTree.innerFolders.clear();
            m_foldersTree.path = m_defaultRoot;
            m_foldersTree.filename = m_defaultRoot.GetBaseNameAndExt();
            m_foldersTree.childrenLoaded = false;
            LoadFolderChildren(m_foldersTree);
            m_dirtyFoldersTree = false;
        }

        FileCatalogPanel(leftWidth); //Отрисовка панели файлового древа

        float_t windowWidth = SR_IMMEDIATE_GUI_NS::GetWindowSize().x;          //код для исключения ошибок ImGui
        if (leftWidth > windowWidth - 40)                       //проверяет ширину панели каталога файлов
            return;                                             //для прекращения отрисовки

        SR_IMMEDIATE_GUI_NS::SameLine();

        // right

        SR_IMMEDIATE_GUI_NS::BeginGroup();

        CurrentDirectoryPanel(); //Отрисовка панели нынешней директории

        auto&& DirectoryPanelHeight = SR_IMMEDIATE_GUI_NS::GetWindowSize().y; //код для исключения ошибок ImGui
        if (DirectoryPanelHeight < 50) {                        //проверяет высоту панели нынешней директории
            SR_IMMEDIATE_GUI_NS::EndGroup();                                  //для прекращения отрисовки
            return;
        }

        if (m_dirtySelectedDir) {
            CacheElements(m_selectedDir);
            m_dirtySelectedDir = false;
        }
        ItemViewPanel(); //Отрисовка панели файлового древа

        SR_IMMEDIATE_GUI_NS::EndGroup();
    }

    void FileBrowser::OpenFileWithApp(const SR_UTILS_NS::Path& path) {
        if (m_callbackFunction) {
            m_callbackFunction(path);
            m_callbackFunction = CallbackFn();
        }
        else {
            SR_UTILS_NS::String extension = path.GetExtension();
            SR_UTILS_NS::StringUtils::Instance().ToLower(extension);

            static bool initialized = false;
            static SR_UTILS_NS::Set<SR_UTILS_NS::StringView> supportedAssets;
            if (!initialized) {
                for (const auto& name : SR_UTILS_NS::Factory::Instance().GetInheritances(SR_UTILS_NS::Asset::GetClassStaticName())) {
                    auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
                    if (!pMeta->IsAbstract() && !pMeta->IsHidden()) {
                        supportedAssets.insert(pMeta->GetExtension());
                    }
                }
                initialized = true;
            }

            if (SR_GTYPES_NS::Texture::GetMetaStatic()->HasExtension(extension)) {
                if (auto&& pInspector = GetManager()->GetWidget<TextureInspector>()) {
                    pInspector->Inspect(path);
                }
                return;
            }
            else if (SR_HTYPES_NS::RawMesh::GetMetaStatic()->HasExtension(extension)) {
                if (auto&& pInspector = GetManager()->GetWidget<RawMeshInspector>()) {
                    pInspector->Inspect(path);
                }
                return;
            }
            else if (SR_ANIMATIONS_NS::AnimationGraphAsset::GetMetaStatic()->HasExtension(extension)) {
                if (auto&& pInspector = GetManager()->GetWidget<AnimatorEditor>()) {
                    pInspector->Inspect(path);
                }
                return;
            }
            else if (SR_FLUX_NS::FluxGraphAsset::GetMetaStatic()->HasExtension(extension)) {
                if (auto&& pInspector = GetManager()->GetWidget<FluxEditor>()) {
                    pInspector->Inspect(path);
                }
                return;
            }
            else if (supportedAssets.count(extension) != 0) {
                if (auto&& pInspector = GetManager()->GetWidget<AssetInspector>()) {
                    pInspector->Inspect(path);
                }
                return;
            }
            else if (extension == SR_UTILS_NS::Prefab::GetMetaStatic()->GetExtension() || extension == "scene") {
                auto&& pEngine = dynamic_cast<EditorGUI*>(GetManager())->GetEngine();
                if (auto&& pScene = SR_WORLD_NS::Scene::LoadScene(path)) {
                    pEngine->AddSceneToQueue(pScene);
                    pEngine->GetEditor()->CacheScenePath(pScene->GetPath());
                }
                return;
            }
            SR_UTILS_NS::Platform::OpenWithAssociatedApp(path);
        }
    }

    void FileBrowser::FreeTextures() {
        SR_TRACY_ZONE;
        for (auto&& element : m_elements) {
            if (element.pTexture) {
                element.pTexture->RemoveUsePoint();
            }
        }
        m_elements.clear();
    }

    void FileBrowser::OnOpen() {
        m_availableAssets = SR_UTILS_NS::Factory::Instance().GetInheritances(SR_UTILS_NS::Asset::GetClassStaticName());

        std::erase_if(m_availableAssets, [](auto&& name) {
            auto&& pMeta = SR_UTILS_NS::Factory::Instance().GetType(name);
            return pMeta->IsAbstract() || pMeta->IsHidden();
        });

        m_comboBoxBuffer.clear();
        for (auto&& name : m_availableAssets) {
            std::copy(name.begin(), name.end(), std::back_inserter(m_comboBoxBuffer));
            m_comboBoxBuffer.push_back('\0');
        }
        m_comboBoxBuffer.push_back('\0');

        Super::OnOpen();
    }

    void FileBrowser::OnClose() {
        FreeTextures();
        Super::OnClose();
    }
}
