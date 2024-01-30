//
// Created by Monika on 07.08.2022.
//

#ifndef SR_ENGINE_SHADERPROPERTIES_H
#define SR_ENGINE_SHADERPROPERTIES_H

#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Xml.h>
#include <Utils/TypeTraits/Properties.h>

namespace SR_GTYPES_NS {
    class Texture;
    class Shader;
    class Material;
}

namespace SR_GRAPH_NS {
    struct ShaderAttachment {
        SR_GTYPES_NS::Texture* pTexture;
        std::string framebuffer;
        uint8_t layer;
    };

    typedef std::variant<
        SR_GTYPES_NS::Texture*,
        float_t,
        int32_t,
        SR_MATH_NS::FVector2,
        SR_MATH_NS::FVector3,
        SR_MATH_NS::FVector4,
        ShaderAttachment
    > ShaderPropertyVariant;

    SR_ENUM_NS_CLASS(ShaderVarType,
          Unknown,
          Bool,
          Int,
          Float,
          Vec2,
          Vec3,
          Vec4,
          IVec2,
          IVec3,
          IVec4,
          BVec2,
          BVec3,
          BVec4,
          Mat2,
          Mat3,
          Mat4,
          Sampler1D,
          Sampler2D,
          Sampler3D,
          SamplerCube,
          Sampler1DShadow,
          Sampler2DShadow, /// see MaterialProperty::IsSampler()
          Skeleton128
    )

    class MaterialProperty final : public SR_UTILS_NS::Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(MaterialProperty, 1001)
    public:
        MaterialProperty() = default;

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
        SR_NODISCARD SR_GTYPES_NS::Material* GetMaterial() const noexcept { return m_material; }
        SR_NODISCARD bool IsPushConstant() const noexcept { return m_pushConstant; }
        SR_NODISCARD bool IsSampler() const noexcept;

        MaterialProperty& SetDisplayName(SR_UTILS_NS::StringAtom value) noexcept { m_displayName = value; return *this; }
        MaterialProperty& SetData(const ShaderPropertyVariant& value) noexcept { m_data = value; return *this; }
        MaterialProperty& SetShaderVarType(ShaderVarType value) noexcept { m_type = value; return *this; }
        MaterialProperty& SetMaterial(SR_GTYPES_NS::Material* value) noexcept { m_material = value; return *this; }
        MaterialProperty& SetPushConstant(bool value) noexcept { m_pushConstant = value; return *this; }

        void Use(SR_GTYPES_NS::Shader* pShader) const noexcept;

    private:
        SR_GTYPES_NS::Material* m_material = nullptr;
        SR_UTILS_NS::StringAtom m_displayName;
        ShaderPropertyVariant m_data;
        bool m_pushConstant = false;
        ShaderVarType m_type = ShaderVarType::Unknown;

    };

    class MaterialProperties : public SR_UTILS_NS::PropertyContainer {
    public:
        MaterialProperties() = default;

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

    typedef std::list<std::pair<std::string, ShaderVarType>> ShaderProperties;

    struct ShaderSampler {
        uint32_t binding = SR_ID_INVALID;
        uint32_t samplerId = SR_ID_INVALID;
        bool isArray = false;
        bool isAttachment = false;
    };
    typedef std::map<SR_UTILS_NS::StringAtom, ShaderSampler> ShaderSamplers;

    void LoadMaterialProperties(const SR_GTYPES_NS::Material* pMaterial, const SR_XML_NS::Node& propertiesNode, MaterialProperties* pProperties);
    std::list<SR_GTYPES_NS::Texture*> GetTexturesFromMatProperties(const MaterialProperties& properties);

    SR_MAYBE_UNUSED static bool IsSamplerType(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Sampler1D:
            case ShaderVarType::Sampler2D:
            case ShaderVarType::Sampler3D:
            case ShaderVarType::SamplerCube:
            case ShaderVarType::Sampler1DShadow:
            case ShaderVarType::Sampler2DShadow:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static bool IsMatrixType(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Mat2:
            case ShaderVarType::Mat3:
            case ShaderVarType::Mat4:
            case ShaderVarType::Skeleton128:
                return true;
            default:
                return false;
        }
    }

    SR_MAYBE_UNUSED static std::string ShaderVarTypeToString(ShaderVarType type) {
        if (type == ShaderVarType::Skeleton128) {
            type = ShaderVarType::Mat4;
        }

        std::string str = SR_UTILS_NS::EnumReflector::ToStringAtom(type);

        if (!str.empty()) {
            str[0] = tolower(str[0]);
        }

        return str;
    }

    SR_MAYBE_UNUSED static std::string MakeShaderVariable(ShaderVarType type, const std::string& name) {
        if (type == ShaderVarType::Skeleton128) {
            return ShaderVarTypeToString(type) + " " + name + "[128]";
        }

        return ShaderVarTypeToString(type) + " " + name;
    }

    SR_MAYBE_UNUSED static uint32_t GetShaderVarSize(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Int:
            case ShaderVarType::Float:
                return 4;
            case ShaderVarType::Vec2:
                return 4 * 2;
            case ShaderVarType::Vec3:
                return 4 * 3;
            case ShaderVarType::Vec4:
                return 4 * 4;
            case ShaderVarType::Mat2:
                return 4 * 2 * 2;
            case ShaderVarType::Mat3:
                return 4 * 3 * 3;
            case ShaderVarType::Mat4:
                return 4 * 4 * 4;
            case ShaderVarType::Skeleton128:
                return 4 * 4 * 4 * 128;
            case ShaderVarType::Unknown:
            default:
                SRAssert2(false, "unknown type!");
                return 0;
        }
    }

    SR_MAYBE_UNUSED static ShaderPropertyVariant GetVariantFromShaderVarType(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Int:
                return static_cast<int32_t>(0);
            case ShaderVarType::Float:
                return static_cast<float_t>(0.f);
            case ShaderVarType::Vec2:
                return SR_MATH_NS::FVector2(SR_MATH_NS::Unit(0));
            case ShaderVarType::Vec3:
                return SR_MATH_NS::FVector3(SR_MATH_NS::Unit(0));
            case ShaderVarType::Vec4:
                return SR_MATH_NS::FVector4(SR_MATH_NS::Unit(0));
            case ShaderVarType::Sampler1D:
            case ShaderVarType::Sampler2D:
            case ShaderVarType::Sampler3D:
            case ShaderVarType::SamplerCube:
            case ShaderVarType::Sampler1DShadow:
            case ShaderVarType::Sampler2DShadow:
                return static_cast<Types::Texture*>(nullptr);
            default:
                SRAssert(false);
                return ShaderPropertyVariant();
        }
    }

    SR_MAYBE_UNUSED static ShaderVarType GetShaderVarTypeFromString(std::string str) {
        if (!str.empty()) {
            str[0] = toupper(str[0]);
        }

        return SR_UTILS_NS::EnumReflector::FromString<ShaderVarType>(str);
    }
}

template<> struct SR_UTILS_NS::SRHash<SR_GRAPH_NS::ShaderSamplers> {
    size_t operator()(SR_GRAPH_NS::ShaderSamplers const& value) const {
        std::size_t res = 0;

        for (auto&& [key, val] : value) {
            res = SR_UTILS_NS::HashCombine(key.GetHash(), res);
            res = SR_UTILS_NS::HashCombine(val.binding, res);
        }

        return res;
    }
};

template<> struct SR_UTILS_NS::SRHash<SR_GRAPH_NS::ShaderProperties> {
    size_t operator()(SR_GRAPH_NS::ShaderProperties const& value) const {
        std::size_t res = 0;

        for (auto&& [key, val] : value) {
            res = SR_UTILS_NS::HashCombine(key, res);
            res = SR_UTILS_NS::HashCombine(val, res);
        }

        return res;
    }
};

#endif //SR_ENGINE_SHADERPROPERTIES_H
