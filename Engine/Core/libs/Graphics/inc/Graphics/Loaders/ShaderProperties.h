//
// Created by Monika on 07.08.2022.
//

#ifndef SRENGINE_SHADERPROPERTIES_H
#define SRENGINE_SHADERPROPERTIES_H

#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Xml.h>
#include <Utils/TypeTraits/Properties.h>

namespace SR_GTYPES_NS {
    class Texture;
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
          Sampler2DShadow,
          Skeleton128
    )

    class MaterialProperty : public SR_UTILS_NS::Property {
        SR_REGISTER_TYPE_TRAITS_PROPERTY(MaterialProperty, 1000)
    public:
        SR_NODISCARD SR_UTILS_NS::StringAtom GetDisplayName() const noexcept { return m_displayName; }
        SR_NODISCARD ShaderVarType GetShaderVarType() const noexcept { return m_type; }
        SR_NODISCARD const ShaderPropertyVariant& GetData() const noexcept { return m_data; }
        SR_NODISCARD SR_GTYPES_NS::Material* GetMaterial() const noexcept { return m_material; }

        MaterialProperty& SetDisplayName(SR_UTILS_NS::StringAtom value) noexcept { m_displayName = value; return *this; }
        MaterialProperty& SetData(const ShaderPropertyVariant& value) noexcept { m_data = value; return *this; }
        MaterialProperty& SetShaderVarType(ShaderVarType value) noexcept { m_type = value; return *this; }
        MaterialProperty& SetMaterial(SR_GTYPES_NS::Material* value) noexcept { m_material = value; return *this; }

    private:
        SR_GTYPES_NS::Material* m_material = nullptr;
        SR_UTILS_NS::StringAtom m_displayName;
        ShaderPropertyVariant m_data;
        ShaderVarType m_type = ShaderVarType::Unknown;

    };

    typedef SR_UTILS_NS::PropertyContainer MaterialProperties;
    typedef std::list<std::pair<std::string, ShaderVarType>> ShaderProperties;

    struct ShaderSampler {
        uint32_t binding = SR_ID_INVALID;
        uint32_t samplerId = SR_ID_INVALID;
        bool isAttachment = false;
    };
    typedef std::map<uint64_t, ShaderSampler> ShaderSamplers;

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

        std::string str = SR_UTILS_NS::EnumReflector::ToString(type);

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
            res = SR_UTILS_NS::HashCombine(key, res);
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

#endif //SRENGINE_SHADERPROPERTIES_H
