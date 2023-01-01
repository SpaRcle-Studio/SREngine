//
// Created by Monika on 07.08.2022.
//

#include <Graphics/Loaders/ShaderProperties.h>

namespace SR_GRAPH_NS {
    MaterialProperties LoadMaterialProperties(const SR_XML_NS::Node &propertiesNode) {
        MaterialProperties properties;

        for (auto&& propertyXml : propertiesNode.TryGetNodes()) {
            MaterialProperty materialProperty;

            materialProperty.id = propertyXml.GetAttribute("Id").ToString();
            materialProperty.hashId = SR_RUNTIME_TIME_CRC32_STR(materialProperty.id.c_str());
            materialProperty.type = SR_UTILS_NS::EnumReflector::FromString<ShaderVarType>(propertyXml.GetAttribute("Type").ToString());

            switch (materialProperty.type) {
                case ShaderVarType::Int:
                    materialProperty.data = propertyXml.GetAttribute<int32_t>();
                    break;
                case ShaderVarType::Float:
                    materialProperty.data = propertyXml.GetAttribute<float_t>();
                    break;
                case ShaderVarType::Vec2:
                    materialProperty.data = propertyXml.GetAttribute<SR_MATH_NS::FVector2>();
                    break;
                case ShaderVarType::Vec3:
                    materialProperty.data = propertyXml.GetAttribute<SR_MATH_NS::FVector3>();
                    break;
                case ShaderVarType::Vec4:
                    materialProperty.data = propertyXml.GetAttribute<SR_MATH_NS::FVector4>();
                    break;
                case ShaderVarType::Sampler2D: {
                    auto&& pTexture = SR_GTYPES_NS::Texture::Load(propertyXml.GetAttribute<std::string>());
                    materialProperty.data = pTexture;
                    break;
                }
                default:
                    SRHalt("Unknown property!");
                    break;
            }

            properties.emplace_back(materialProperty);
        }

        return properties;
    }

    std::list<SR_GTYPES_NS::Texture*> GetTexturesFromMatProperties(const MaterialProperties &properties) {
        std::list<SR_GTYPES_NS::Texture*> textures;

        for (auto&& property : properties) {
            std::visit([&textures](ShaderPropertyVariant &&arg) {
                if (std::holds_alternative<SR_GTYPES_NS::Texture*>(arg)) {
                    if (auto &&value = std::get<SR_GTYPES_NS::Texture*>(arg)) {
                        textures.emplace_back(value);
                    }
                }
            }, property.data);
        }

        return textures;
    }
}