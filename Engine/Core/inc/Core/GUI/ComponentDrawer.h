//
// Created by Monika on 23.02.2022.
//

#ifndef SR_ENGINE_COMPONENT_DRAWER_H
#define SR_ENGINE_COMPONENT_DRAWER_H

#include <Graphics/Font/IText.h>
#include <Utils/stdInclude.h>

namespace SR_SCRIPTING_NS {
    class Behaviour;
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
    //class ITextComponent;
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
    class CollisionShape;
}

namespace SR_UTILS_NS {
    class Component;
}

#endif //SR_ENGINE_COMPONENTDRAWER_H
