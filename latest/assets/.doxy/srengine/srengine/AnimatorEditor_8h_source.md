

# File AnimatorEditor.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**inc**](dir_9bceefd1de4616d8c4c29c5c810ccf2f.md) **>** [**Core**](dir_69060d94e27077a49c91b4da0482ce5e.md) **>** [**GUI**](dir_44a92b6c7b958f78c0d3d9d4e761e8ae.md) **>** [**AnimatorEditor.h**](AnimatorEditor_8h.md)

[Go to the documentation of this file](AnimatorEditor_8h.md)


```C++
//
// Created by Monika on 14.01.2023.
//

#ifndef SR_ENGINE_ANIMATOREDITOR_H
#define SR_ENGINE_ANIMATOREDITOR_H

#include <Utils/Types/SharedPtr.h>

#include <Graphics/GUI/NodeWidget.h>
#include <Graphics/GUI/Node.h>
#include <Graphics/Animations/AnimationGraph.h>

namespace SR_ANIMATIONS_NS {
    class Animator;
}

namespace SR_CORE_GUI_NS {
    class AnimatorEditor : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
        static constexpr uint16_t VERSION = 1000;
        using AnimatorPtr = SR_HTYPES_NS::SharedPtr<SR_ANIMATIONS_NS::Animator>;
    public:
        AnimatorEditor();
        ~AnimatorEditor() override = default;

    public:
        void SetAnimator(const AnimatorPtr& pAnimator) noexcept;

        void Draw() override;

    protected:
        AnimatorPtr m_pAnimator;

    };
}

#endif //SR_ENGINE_ANIMATOREDITOR_H
```


