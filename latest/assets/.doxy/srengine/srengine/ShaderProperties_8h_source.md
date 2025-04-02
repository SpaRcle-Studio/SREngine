

# File ShaderProperties.h

[**File List**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Graphics**](dir_3963f30637b7260601ed2fee5486623e.md) **>** [**inc**](dir_cf695446dee09d9ecb81ac3a708470c3.md) **>** [**Graphics**](dir_7d904954ae4eb5028070508fad42280f.md) **>** [**Loaders**](dir_3c21463f64aae35806a3291732eddb38.md) **>** [**ShaderProperties.h**](ShaderProperties_8h.md)

[Go to the documentation of this file](ShaderProperties_8h.md)


```C++
//
// Created by Monika on 07.08.2022.
//

#ifndef SR_ENGINE_SHADERPROPERTIES_H
#define SR_ENGINE_SHADERPROPERTIES_H

#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>
#include <Utils/Resources/Xml.h>
#include <Utils/TypeTraits/Properties.h>

namespace SR_GTYPES_NS {
    class Texture;
    class Shader;
}

namespace SR_GRAPH_NS {
    class BaseMaterial;

    typedef std::variant<
        SR_GTYPES_NS::Texture*,
        float_t,
        int32_t,
        SR_MATH_NS::FVector2,
        SR_MATH_NS::FVector3,
        SR_MATH_NS::FVector4
    > ShaderPropertyVariant;

    SR_ENUM_NS_CLASS_T(ShaderVarType, uint8_t,
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

    struct ShaderProperty {
        ShaderProperty() = default;
        ShaderProperty(const SR_UTILS_NS::StringAtom id, const ShaderVarType type, const bool pushConstant)
            : id(id)
            , type(type)
            , pushConstant(pushConstant)
        { }
        ShaderProperty(const SR_UTILS_NS::StringAtom id, const ShaderVarType type, const bool pushConstant, const std::optional<ShaderPropertyVariant>& defaultData)
            : id(id)
            , type(type)
            , pushConstant(pushConstant)
            , defaultData(defaultData)
        { }

        SR_UTILS_NS::StringAtom id;
        ShaderVarType type = ShaderVarType::Unknown;
        bool pushConstant = false;
        std::optional<ShaderPropertyVariant> defaultData;

        SR_NODISCARD bool IsPushConstant() const { return pushConstant; }
        SR_NODISCARD bool HasDefaultData() const { return defaultData.has_value(); }
        SR_NODISCARD ShaderPropertyVariant GetData() const;
        SR_NODISCARD ShaderPropertyVariant GetDefaultData() const;
    };

    typedef std::list<ShaderProperty> ShaderProperties;

    struct ShaderSampler {
        uint32_t binding = SR_ID_INVALID;
        uint32_t samplerId = SR_ID_INVALID;
        bool isArray = false;
        bool isAttachment = false;
        SR_UTILS_NS::StringAtom defaultValue;
    };
    typedef std::map<SR_UTILS_NS::StringAtom, ShaderSampler> ShaderSamplers;

    struct SSBOBinding {
        SR_UTILS_NS::StringAtom name;
        uint32_t binding = SR_ID_INVALID;
        uint32_t ssbo = SR_ID_INVALID;
    };
    typedef std::vector<SSBOBinding> SSBOBindings;

    SR_MAYBE_UNUSED static bool SR_FASTCALL IsSamplerType(const ShaderVarType type) {
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
            case ShaderVarType::Bool:
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
            case ShaderVarType::Bool:
                return static_cast<int32_t>(0);
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

        for (auto&& info : value) {
            res = SR_UTILS_NS::HashCombine(info.id.GetHash(), res);
            res = SR_UTILS_NS::HashCombine(info.type, res);
        }

        return res;
    }
};

#endif //SR_ENGINE_SHADERPROPERTIES_H
```


