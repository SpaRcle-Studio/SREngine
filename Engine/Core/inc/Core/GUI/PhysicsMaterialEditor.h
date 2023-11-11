//
// Created by innerviewer on 6/6/2023.
//

#ifndef SRENGINE_PHYSICSMATERIALEDITOR_H
#define SRENGINE_PHYSICSMATERIALEDITOR_H

#include <Physics/PhysicsMaterial.h>

#include <Graphics/GUI/Widget.h>

namespace SR_CORE_GUI_NS {
    class PhysicsMaterialEditor : public SR_GRAPH_GUI_NS::Widget {
        using Super = SR_GRAPH_GUI_NS::Widget;
    public:
        PhysicsMaterialEditor();
        ~PhysicsMaterialEditor() override = default;

    public:
        bool OpenFile(const SR_UTILS_NS::Path& path) override;

        void SetMaterialPath(const SR_UTILS_NS::Path& path) { m_materialPath = path; ReadData(); }

    protected:
        void Draw() override;

    private:
        void ChooseMaterial();
        void ReadData();

        void SetDynamicFriction(float_t dynamicFriction) { m_materialData.dynamicFriction = dynamicFriction; }
        void SetStaticFriction(float_t staticFriction) { m_materialData.staticFriction = staticFriction; }
        void SetBounciness(float_t bounciness) { m_materialData.bounciness = bounciness; }
        void SetFrictionCombine(SR_PHYSICS_NS::Combine frictionCombine) { m_materialData.frictionCombine = frictionCombine; }
        void SetBounceCombine(SR_PHYSICS_NS::Combine bounceCombine) { m_materialData.bounceCombine = bounceCombine; }

    private:
        SR_PTYPES_NS::PhysicsMaterialData m_materialData;
        SR_UTILS_NS::Path m_materialPath;
    };
}

#endif //SRENGINE_PHYSICSMATERIALEDITOR_H
