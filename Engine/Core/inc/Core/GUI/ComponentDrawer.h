//
// Created by Monika on 23.02.2022.
//

#ifndef SRENGINE_COMPONENTDRAWER_H
#define SRENGINE_COMPONENTDRAWER_H

#include <Utils/stdInclude.h>

namespace SR_SCRIPTING_NS {
    class Behaviour;
}

namespace SR_GRAPH_NS {
    namespace UI {
        class Sprite2D;
        class Anchor;
        class Canvas;
    }

    namespace Types {
        class Camera;
        class Mesh3D;
        class Material;
        class ProceduralMesh;
    }
}

namespace SR_CORE_NS::GUI {
    class EditorGUI;
}

namespace SR_PHYSICS_NS::Types {
    class Rigidbody3D;
}

namespace SR_CORE_NS::GUI::ComponentDrawer {
    void DrawComponent(SR_SCRIPTING_NS::Behaviour*& behaviour, EditorGUI* context, int32_t index);
    void DrawComponent(SR_PHYSICS_NS::Types::Rigidbody3D*& rigidbody3D, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::Camera*& camera, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::Mesh3D*& mesh3d, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::ProceduralMesh*& proceduralMesh, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::Types::Material*& material, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::UI::Sprite2D*& sprite, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::UI::Anchor*& anchor, EditorGUI* context, int32_t index);
    void DrawComponent(SR_GRAPH_NS::UI::Canvas*& canvas, EditorGUI* context, int32_t index);

    void DrawMaterialProps(SR_GRAPH_NS::Types::Material* material, EditorGUI* context, int32_t index);
}

#endif //SRENGINE_COMPONENTDRAWER_H
