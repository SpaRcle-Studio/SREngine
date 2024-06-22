//
// Created by Monika on 23.02.2022.
//

#ifndef SR_ENGINE_COMPONENT_DRAWER_H
#define SR_ENGINE_COMPONENT_DRAWER_H

#include <Utils/stdInclude.h>

namespace SR_SCRIPTING_NS {
    class Behaviour;
}

namespace SR_AUDIO_NS {
    class AudioSource;
    class AudioListener;
}

namespace SR_ANIMATIONS_NS {
    class Animator;
    class BoneComponent;
    class Skeleton;
}

namespace SR_GRAPH_NS {
    class BaseMaterial;
    namespace UI {
        class Anchor;
        class Canvas;
    }
}

namespace SR_GTYPES_NS {
    class Camera;
    class Mesh3D;
    class SkinnedMesh;
    class ProceduralMesh;
    class ITextComponent;
    class Sprite;
    class Text2D;
    class Text3D;
}

namespace SR_CORE_GUI_NS {
    class EditorGUI;
}

namespace SR_UTILS_NS {
    class LookAtComponent;
}

namespace SR_PTYPES_NS {
    class Rigidbody;
    class Rigidbody2D;
    class Rigidbody3D;
    class CollisionShape;
}

namespace SR_UTILS_NS {
    class Component;
}

namespace SR_CORE_NS::GUI::ComponentDrawer {
    bool DrawComponentOld(SR_UTILS_NS::Component* pComponent, EditorGUI* context, int32_t index);

    void DrawComponent(SR_SCRIPTING_NS::Behaviour*& behaviour, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::Camera*& camera, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::Mesh3D*& mesh3d, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::SkinnedMesh*& pComponent, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::ProceduralMesh*& proceduralMesh, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::BaseMaterial*& material, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GTYPES_NS::Sprite*& sprite, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::UI::Anchor*& anchor, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::UI::Canvas*& canvas, EditorGUI* context, int32_t index);
    void DrawComponent(SR_PTYPES_NS::Rigidbody3D*& pComponent, EditorGUI* context, int32_t index);
    void DrawComponent(SR_ANIMATIONS_NS::Animator*& pComponent, EditorGUI* context, int32_t index);
    void DrawComponent(SR_ANIMATIONS_NS::Skeleton*& pComponent, EditorGUI* context, int32_t index);
    void DrawComponent(SR_ANIMATIONS_NS::BoneComponent*& pComponent, EditorGUI* context, int32_t index) { }
    void DrawComponent(SR_UTILS_NS::LookAtComponent*& pComponent, EditorGUI* context, int32_t index);

    void DrawComponent(SR_PTYPES_NS::Rigidbody*& pComponent, EditorGUI* context, int32_t index);
    void DrawCollisionShape(SR_PTYPES_NS::CollisionShape* pCollisionShape, EditorGUI* context, int32_t index);
    void DrawMaterialProps(SR_GRAPH_NS::BaseMaterial* material, EditorGUI* context, int32_t index);

    void DrawComponent(SR_GTYPES_NS::ITextComponent* pComponent, EditorGUI* context, int32_t index);

    void DrawComponent(SR_AUDIO_NS::AudioSource*& pComponent, EditorGUI* context, int32_t index);
    void DrawComponent(SR_AUDIO_NS::AudioListener*& pComponent,EditorGUI* context,int32_t index);
}

#endif //SR_ENGINE_COMPONENTDRAWER_H
