//
// Created by Monika on 23.02.2022.
//

#include <Core/GUI/ComponentDrawer.h>
#include <Core/GUI/EditorGUI.h>
#include <Core/GUI/FileBrowser.h>
#include <Core/GUI/PhysicsMaterialEditor.h>
#include <Core/GUI/DragNDropHelper.h>
#include <Core/GUI/PropertyDrawer.h>
#include <Core/Settings/EditorSettings.h>
#include <Core/Common/Importers.h>

#include <Utils/Types/DataStorage.h>
#include <Utils/Types/RawMesh.h>
#include <Utils/Resources/ResourceManager.h>
#include <Utils/Common/AnyVisitor.h>
#include <Utils/Game/LookAtComponent.h>
#include <Utils/Localization/Encoding.h>
#include <Utils/FileSystem/FileDialog.h>

#include <Scripting/Base/Behaviour.h>

#include <Physics/Rigidbody.h>
#include <Physics/2D/Rigidbody2D.h>
#include <Physics/3D/Rigidbody3D.h>
#include <Physics/PhysicsMaterial.h>

#include <Graphics/Animations/Skeleton.h>
#include <Graphics/Animations/BoneComponent.h>
#include <Graphics/Animations/Animator.h>
#include <Graphics/Types/Geometry/Mesh3D.h>
#include <Graphics/Types/Shader.h>
#include <Graphics/Types/Geometry/SkinnedMesh.h>
#include <Graphics/Types/Geometry/ProceduralMesh.h>
#include <Graphics/GUI/Utils.h>
#include <Graphics/Types/Texture.h>
#include <Graphics/Types/Geometry/Sprite.h>
#include <Graphics/Material/FileMaterial.h>
#include <Graphics/Types/Camera.h>
#include <Graphics/UI/Anchor.h>
#include <Graphics/UI/Canvas.h>
#include <Graphics/Font/Font.h>
#include <Graphics/Utils/MeshUtils.h>

#include <Audio/Types/AudioSource.h>
#include <Audio/Types/AudioListener.h>

namespace SR_CORE_GUI_NS {
    /*
    auto&& text = SR_UTILS_NS::Localization::UtfToUtf<char, char32_t>(pComponent->GetText());

    if (ImGui::InputTextMultiline(SR_FORMAT_C("##textBox{}", index), &text, ImVec2(ImGui::GetWindowWidth() - 10, 100))) {
        pComponent->SetText(text);
    }

    if (Graphics::GUI::Button("Import", (void*)pComponent)) {
        auto&& resourcesFolder = SR_UTILS_NS::ResourceManager::Instance().GetResPath();
        auto&& path = SR_UTILS_NS::FileDialog::Instance().OpenDialog(resourcesFolder, { { "Mesh with skeleton", "fbx,pmx,blend,gltf" } });

        if (!path.Exists()) {
        return;
        }

        auto&& pRawMesh = SR_HTYPES_NS::RawMesh::Load(path);
        if (!pRawMesh) {
        return;
        }

        pRawMesh->Execute([&]() -> bool {
        return Importers::ImportSkeletonFromRawMesh(pRawMesh, pComponent);
        });
        pComponent->OnAttached();
    }
    */
}
