//
// Created by Monika on 09.11.2023.
//

#ifndef SR_ENGINE_CORE_PROPERTY_DRAWER_H
#define SR_ENGINE_CORE_PROPERTY_DRAWER_H

#include <Engine/stdInclude.h>

#include <Utils/Types/SafePointer.h>
#include <Utils/TypeTraits/SRClass.h>
#include <Utils/Reflection/Property.h>

namespace SR_UTILS_NS {
    class Component;
}

namespace SR_GRAPH_NS {
    class RenderContext;
}

namespace SR_CORE_GUI_NS {
    class EditorGUI;

    struct DrawPropertyContext {
        EditorGUI* pEditor = nullptr;
    };

    SR_MAYBE_UNUSED SR_UTILS_NS::StringAtom GetValueInspector(const SR_UTILS_NS::Reflection::Value& value);

    struct PropertyDrawerContext {
        explicit PropertyDrawerContext(const SR_UTILS_NS::Reflection::Property& property)
            : pProperty(&property)
        { }

        explicit PropertyDrawerContext(SR_UTILS_NS::Reflection::Value* pValue)
            : pValue(pValue)
        { }

        bool noHeader = false;
        bool openedByDefault = false;
        bool isDebugMode = false;

        float_t lineHeight = 1.f;
        float_t spaceWidth = 1.f;

        float_t axisButtonWidth = 30.f;
        uint32_t maxPartsInLine = 3;

        float_t fieldTitleWidth = 90.f;
        float_t fieldWidth = 250.f;
        float_t fieldHeight = 0.f;

        SR_HTYPES_NS::Function<bool(SR_UTILS_NS::StringAtom)> isEnumValueAvailableCheckFn;

        SR_NODISCARD float_t GetArrowWidth() const { return lineHeight * 0.85f; }

        SR_NODISCARD SR_UTILS_NS::Reflection::Property const& GetProperty() const { SRAssert(pProperty); return *pProperty; }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetPropertyName() const { return pProperty ? pProperty->GetName() : SR_UTILS_NS::StringAtom(); }
        SR_NODISCARD SR_UTILS_NS::StringAtom GetPropertyDisplayName() const { return pProperty ? pProperty->GetDisplayName() : customDisplayName; }
        SR_NODISCARD const SR_UTILS_NS::Reflection::EditorPropertyParams& GetEditorParams() const { return pProperty ? pProperty->GetEditorParams() : editorPropertyParams; }

        SR_NODISCARD SR_UTILS_NS::Reflection::Value GetValue() const;

        SR_NODISCARD bool HasExplicitSetter() const {
            return pProperty && pProperty->HasExplicitSetter();
        }

        SR_HTYPES_NS::Function<void(bool drag)> onBeforeChangeCallback;
        SR_UTILS_NS::Reflection::EditorPropertyParams editorPropertyParams;
        SR_HTYPES_NS::SharedPtr<SR_UTILS_NS::Component> pComponent;
        uint64_t propertyIndex = 0;
        SR_UTILS_NS::StringAtom customDisplayName;
        SR_UTILS_NS::Reflection::Value* pValue = nullptr;
        SR_UTILS_NS::Reflection::Property const* pProperty = nullptr;
        EditorGUI* pEditor = nullptr;
        SR_UTILS_NS::SRClass* pOwner = nullptr;
        void* pUID = nullptr;
    };

    struct PropertyDrawerFeedback {
        bool isChanged = false;
        bool isDrag = false;
    };

    /// @abstract
    class PropertyDrawerBase : public SR_UTILS_NS::SRClass, public SR_HTYPES_NS::SharedPtr<PropertyDrawerBase> {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<PropertyDrawerBase>;

        PropertyDrawerBase()
            : Ptr(this, SR_UTILS_NS::SharedPtrPolicy::Automatic)
        { }

        virtual PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) { return {}; }

        SR_NODISCARD static bool CheckSearchMatch(std::string_view searchBuffer, std::string_view text) {
            for (uint64_t textStartPos = 0; textStartPos < text.size(); ++textStartPos) {
                bool isMatch = true;
                for (uint64_t searchPos = 0; searchPos < searchBuffer.size(); ++searchPos) {
                    if (textStartPos + searchPos >= text.size()) {
                        isMatch = false;
                        break;
                    }

                    if (std::tolower(searchBuffer[searchPos]) != std::tolower(text[textStartPos + searchPos])) {
                        isMatch = false;
                        break;
                    }
                }

                if (isMatch) {
                    return true;
                }
            }
            return false;
        }

    protected:
        static void SetValue(const PropertyDrawerContext& context, const PropertyDrawerFeedback& feedback, const SR_UTILS_NS::Reflection::Value& value);

        static void SetReflectedValue(const PropertyDrawerContext& context, PropertyDrawerFeedback& feedback, const SR_UTILS_NS::Reflection::Value& value, bool drag = false);

        SR_NODISCARD SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext> GetRenderContext() const;

    private:
        mutable SR_HTYPES_NS::SafePtr<SR_GRAPH_NS::RenderContext> m_context;

    };

    class BoolPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<BoolPropertyDrawer>;
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;
    };

    class NumericPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<NumericPropertyDrawer>;
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;
    };

    class MathVectorPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<MathVectorPropertyDrawer>;
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    };

    class AABBPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<MathVectorPropertyDrawer>;
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    };

    class FColorPropertyDrawer : public PropertyDrawerBase {
    SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<FColorPropertyDrawer>;
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    };

    class OptionalPropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        using Ptr = SR_HTYPES_NS::SharedPtr<OptionalPropertyDrawer>;
    public:
        ~OptionalPropertyDrawer() override;

    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;

    private:
        PropertyDrawerBase::Ptr m_valueDrawer;

    };

    class MathSizePropertyDrawer : public PropertyDrawerBase {
        SR_CLASS()
    public:
        PropertyDrawerFeedback Draw(const PropertyDrawerContext& context) override;
    };
}

#endif //SR_ENGINE_CORE_PROPERTY_DRAWER_H
