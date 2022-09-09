//
// Created by Monika on 07.08.2022.
//

#ifndef SRENGINE_SHADERPROPERTIES_H
#define SRENGINE_SHADERPROPERTIES_H

#include <Utils/Common/StringUtils.h>
#include <Utils/Common/Hashes.h>
#include <Utils/Common/Enumerations.h>

namespace SR_GTYPES_NS {
    class Texture;
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
          Int,
          Float,
          Vec2,
          Vec3,
          Vec4,
          Mat2,
          Mat3,
          Mat4,
          Sampler1D,
          Sampler2D,
          Sampler3D,
          SamplerCube,
          Sampler1DShadow,
          Sampler2DShadow
    )

    struct MaterialProperty {
        std::string id;
        std::string displayName;
        ShaderPropertyVariant data;
        uint64_t hashId;
        ShaderVarType type;
    };

    typedef std::vector<MaterialProperty> MaterialProperties;
    typedef std::list<std::pair<std::string, ShaderVarType>> ShaderProperties;
    typedef std::map<uint64_t, std::pair<ShaderVarType, uint32_t>> ShaderSamplers;

    SR_NODISCARD MaterialProperties LoadMaterialProperties(const SR_XML_NS::Node& propertiesNode);
    std::list<SR_GTYPES_NS::Texture*> GetTexturesFromMatProperties(const MaterialProperties& properties);

    static bool IsSamplerType(ShaderVarType type) {
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

    static bool IsMatrixType(ShaderVarType type) {
        switch (type) {
            case ShaderVarType::Mat2:
            case ShaderVarType::Mat3:
            case ShaderVarType::Mat4:
                return true;
            default:
                return false;
        }
    }

    static std::string ShaderVarTypeToString(ShaderVarType type) {
        std::string str = SR_UTILS_NS::EnumReflector::ToString(type);

        if (!str.empty()) {
            str[0] = tolower(str[0]);
        }

        return str;
    }

    static uint32_t GetShaderVarSize(ShaderVarType type) {
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
            case ShaderVarType::Unknown:
            default:
                SRAssert2(false, "unknown type!");
                return 0;
        }
    }

    static ShaderPropertyVariant GetVariantFromShaderVarType(ShaderVarType type) {
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

    static ShaderVarType GetShaderVarTypeFromString(std::string str) {
        if (!str.empty()) {
            str[0] = toupper(str[0]);
        }

        return SR_UTILS_NS::EnumReflector::FromString<ShaderVarType>(str);
    }
}

namespace std {
    template<> struct hash<SR_GRAPH_NS::ShaderSamplers> {
        size_t operator()(SR_GRAPH_NS::ShaderSamplers const& value) const {
            std::size_t res = 0;

            for (auto&& [key, val] : value) {
                res = SR_UTILS_NS::HashCombine(key, res);
                res = SR_UTILS_NS::HashCombine(val.first, res);
                res = SR_UTILS_NS::HashCombine(val.second, res);
            }

            return res;
        }
    };

    template<> struct hash<SR_GRAPH_NS::ShaderProperties> {
        size_t operator()(SR_GRAPH_NS::ShaderProperties const& value) const {
            std::size_t res = 0;

            for (auto&& [key, val] : value) {
                res = SR_UTILS_NS::HashCombine(key, res);
                res = SR_UTILS_NS::HashCombine(val, res);
            }

            return res;
        }
    };
}

#endif //SRENGINE_SHADERPROPERTIES_H
