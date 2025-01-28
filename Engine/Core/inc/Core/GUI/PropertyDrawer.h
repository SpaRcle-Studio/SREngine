//
// Created by Monika on 09.11.2023.
//

#ifndef SR_ENGINE_CORE_PROPERTY_DRAWER_H
#define SR_ENGINE_CORE_PROPERTY_DRAWER_H

#include <Graphics/Material/BaseMaterial.h>

#include <Utils/TypeTraits/SRClass.h>
#include <Utils/Reflection/Property.h>

namespace SR_CORE_GUI_NS {
    class EditorGUI;

    struct DrawPropertyContext {
        EditorGUI* pEditor = nullptr;
    };

    SR_MAYBE_UNUSED bool DrawProperty(const DrawPropertyContext& context, SR_UTILS_NS::Property* pProperty);
    SR_MAYBE_UNUSED bool DrawStandardProperty(const DrawPropertyContext& context, SR_UTILS_NS::StandardProperty* pProperty);
    SR_MAYBE_UNUSED bool DrawEnumProperty(const DrawPropertyContext& context, SR_UTILS_NS::EnumProperty* pProperty);
    SR_MAYBE_UNUSED bool DrawPathProperty(const DrawPropertyContext& context, SR_UTILS_NS::PathProperty* pProperty);
    SR_MAYBE_UNUSED bool DrawPropertyContainer(const DrawPropertyContext& context, const SR_UTILS_NS::PropertyContainer* pProperties);
    SR_MAYBE_UNUSED bool DrawLabelProperty(const DrawPropertyContext& context, SR_UTILS_NS::LabelProperty* pProperty);
    SR_MAYBE_UNUSED bool DrawMaterialProperty(const DrawPropertyContext& context, SR_GRAPH_NS::MaterialProperty* pProperty);

    struct PropertyDrawerContext {
        explicit PropertyDrawerContext(const SR_UTILS_NS::Reflection::Property& property)
            : property(property)
        { }
        const SR_UTILS_NS::Reflection::Property& property;
        EditorGUI* pEditor = nullptr;
        void* pOwner = nullptr;
    };

    struct PropertyDrawerFeedback {
        bool isChanged = false;
    };

    class PropertyDrawerBase : public SR_UTILS_NS::SRClass, public SR_HTYPES_NS::SharedPtr<PropertyDrawerBase> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<PropertyDrawerBase>;

        PropertyDrawerBase()
            : Ptr(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

        virtual PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) = 0;
    };

    class BoolPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;
    };

    class NumericPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;
    };

    class VectorPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;
    };

    class SizePropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;
    };
}

#endif //SR_ENGINE_CORE_PROPERTY_DRAWER_H
