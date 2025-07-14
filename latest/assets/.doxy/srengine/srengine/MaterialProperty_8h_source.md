

# File MaterialProperty.h

[**File List**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Graphics**](dir_e4e4141e409277d12c2a4a311178ca74.md) **>** [**inc**](dir_e1be8c5e555e7ce65ff70a2ea1591de9.md) **>** [**Graphics**](dir_2a8d6e7cc5d2cb552d53ce15e1eac7f0.md) **>** [**Material**](dir_d7c89fdc4b5407f55bdfbb167bac987a.md) **>** [**MaterialProperty.h**](MaterialProperty_8h.md)

[Go to the documentation of this file](MaterialProperty_8h.md)


```C++
//
// Created by Monika on 27.05.2024.
//

#ifndef SR_ENGINE_GRAOHICS_MATERIAL_PROPERTY_H
#define SR_ENGINE_GRAOHICS_MATERIAL_PROPERTY_H

#include <Graphics/Loaders/ShaderProperties.h>
#include <Utils/Common/SubscriptionHolder.h>

namespace SR_GRAPH_NS {
    class BaseMaterial;

    class MaterialProperty final : public SR_UTILS_NS::Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(MaterialProperty, 1002)
        using Super = SR_UTILS_NS::Property;
    public:
        MaterialProperty() = default;
        ~MaterialProperty() override;

        explicit MaterialProperty(ShaderVarType type)
            : SR_UTILS_NS::Property()
            , m_type(type)
        { }

        MaterialProperty(MaterialProperty&& other) noexcept
            : m_material(SR_EXCHANGE(other.m_material, nullptr))
            , m_displayName(SR_EXCHANGE(other.m_displayName, { }))
            , m_data(SR_EXCHANGE(other.m_data, { }))
            , m_pushConstant(SR_EXCHANGE(other.m_pushConstant, { }))
            , m_type(SR_EXCHANGE(other.m_type, { }))
        { }

        MaterialProperty& operator=(MaterialProperty&& other) noexcept {
            m_material = SR_EXCHANGE(other.m_material, nullptr);
            m_displayName = SR_EXCHANGE(other.m_displayName, { });
            m_data = SR_EXCHANGE(other.m_data, { });
            m_pushConstant = SR_EXCHANGE(other.m_pushConstant, { });
            m_type = SR_EXCHANGE(other.m_type, { });
            return *this;
        }

        SR_NODISCARD SR_UTILS_NS::StringAtom GetDisplayName() const noexcept { return m_displayName; }
        SR_NODISCARD ShaderVarType GetShaderVarType() const noexcept { return m_type; }
        SR_NODISCARD const ShaderPropertyVariant& GetData() const noexcept { return m_data; }
        SR_NODISCARD BaseMaterial* GetMaterial() const noexcept { return m_material; }
        SR_NODISCARD bool IsPushConstant() const noexcept { return m_pushConstant; }
        SR_NODISCARD bool IsSampler() const noexcept;

        MaterialProperty& SetDisplayName(SR_UTILS_NS::StringAtom value) noexcept { m_displayName = value; return *this; }
        MaterialProperty& SetShaderVarType(ShaderVarType value) noexcept { m_type = value; return *this; }
        MaterialProperty& SetMaterial(BaseMaterial* value) noexcept { m_material = value; return *this; }
        MaterialProperty& SetPushConstant(bool value) noexcept { m_pushConstant = value; return *this; }

        void SaveProperty(MarshalRef marshal) const noexcept override;
        void LoadProperty(MarshalRef marshal) noexcept override;

        template<typename T> MaterialProperty& SetData(const T& value) noexcept {
            if constexpr (std::is_same_v<T, bool>) {
                if (std::get<int32_t>(m_data) == static_cast<int32_t>(value)) {
                    return *this;
                }
                m_data = static_cast<int32_t>(value);
                OnPropertyChanged(true);
            }
            else if constexpr (std::is_same_v<T, SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Texture>>) {
                if (std::get<SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Texture>>(m_data) == value) {
                    return *this;
                }
                SetTextureInternal(value);
                OnPropertyChanged(false);
            }
            else {
                if constexpr (std::is_same_v<T, int32_t>) {
                    if (std::get<int32_t>(m_data) == value) {
                        return *this;
                    }
                }
                else if constexpr (std::is_same_v<T, float_t>) {
                    if (std::get<float_t>(m_data) == value) {
                        return *this;
                    }
                }
                else if constexpr (std::is_same_v<T, SR_MATH_NS::FVector2>) {
                    if (std::get<SR_MATH_NS::FVector2>(m_data) == value) {
                        return *this;
                    }
                }
                else if constexpr (std::is_same_v<T, SR_MATH_NS::FVector3>) {
                    if (std::get<SR_MATH_NS::FVector3>(m_data) == value) {
                        return *this;
                    }
                }
                else if constexpr (std::is_same_v<T, SR_MATH_NS::FVector4>) {
                    if (std::get<SR_MATH_NS::FVector4>(m_data) == value) {
                        return *this;
                    }
                }

                m_data = value;
                OnPropertyChanged(true);
            }

            return *this;
        }

        void Use(SR_GTYPES_NS::Shader* pShader) const noexcept;

    private:
        void SetTextureInternal(SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Texture> pTexture);
        void OnPropertyChanged(bool onlyUniforms);

    private:
        BaseMaterial* m_material = nullptr;
        SR_UTILS_NS::StringAtom m_displayName;
        ShaderPropertyVariant m_data;
        bool m_pushConstant = false;
        ShaderVarType m_type = ShaderVarType::Unknown;
        SR_UTILS_NS::Subscription m_textureOnReloadDoneSubscription;

    };

    class MaterialProperties : public SR_UTILS_NS::PropertyContainer {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(MaterialProperties, 1001)
    public:
        MaterialProperties() = default;

        const std::vector<MaterialProperty*>& GetMaterialSamplerProperties() const noexcept { return m_materialSamplerProperties; }
        const std::vector<MaterialProperty*>& GetMaterialUniformsProperties() const noexcept { return m_materialUniformsProperties; }

        void ClearContainer() override {
            m_materialSamplerProperties.clear();
            m_materialUniformsProperties.clear();
            SR_UTILS_NS::PropertyContainer::ClearContainer();
        }

        void OnPropertyAdded(SR_UTILS_NS::Property* pProperty) override {
            if (auto&& pMaterialProperty = dynamic_cast<MaterialProperty*>(pProperty)) {
                if (pMaterialProperty->IsSampler()) {
                    m_materialSamplerProperties.emplace_back(pMaterialProperty);
                }
                else {
                    m_materialUniformsProperties.emplace_back(pMaterialProperty);
                }
            }
        }

        void UseMaterialSamplers(SR_GTYPES_NS::Shader* pShader) {
            for (auto&& pProperty : m_materialSamplerProperties) {
                pProperty->Use(pShader);
            }
        }

        void UseMaterialUniforms(SR_GTYPES_NS::Shader* pShader) {
            for (auto&& pProperty : m_materialUniformsProperties) {
                pProperty->Use(pShader);
            }
        }

    private:

        std::vector<MaterialProperty*> m_materialSamplerProperties;
        std::vector<MaterialProperty*> m_materialUniformsProperties;

    };

    void LoadMaterialProperties(const std::string& materialDebugIdentifier, const SR_XML_NS::Node& propertiesNode, MaterialProperties* pProperties);
}

#endif //SR_ENGINE_GRAOHICS_MATERIAL_PROPERTY_H
```


