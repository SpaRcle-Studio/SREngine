//
// Created by Monika on 07.08.2022.
//

#include <Graphics/Loaders/ShaderProperties.h>
#include <Graphics/Types/Material.h>

namespace SR_GRAPH_NS {
    void LoadMaterialProperties(const SR_GTYPES_NS::Material* pMaterial, const SR_XML_NS::Node& propertiesNode, MaterialProperties* pProperties) {
        for (auto&& propertyXml : propertiesNode.TryGetNodes()) {
            auto&& type = SR_UTILS_NS::EnumReflector::FromString<ShaderVarType>(propertyXml.GetAttribute("Type").ToString());
            auto&& id = propertyXml.GetAttribute("Id").ToString();

            auto&& pMaterialProperty = pProperties->Find<MaterialProperty>(id);
            if (!pMaterialProperty) {
                continue;
            }

            if (pMaterialProperty->GetShaderVarType() != type) {
                SR_ERROR("LoadMaterialProperties() : invalid property!\n\tFile: " + pMaterial->GetResourcePath().ToStringRef() +
                     "\n\tProperty: " + id + "\n\tLoaded type: " + SR_UTILS_NS::EnumReflector::ToStringAtom(type).ToStringRef() +
                     "\n\tExpected type: " + SR_UTILS_NS::EnumReflector::ToStringAtom(pMaterialProperty->GetShaderVarType()).ToStringRef()
                );
                continue;
            }

            switch (type) {
                case ShaderVarType::Int:
                    pMaterialProperty->SetData(propertyXml.GetAttribute<int32_t>());
                    break;
                case ShaderVarType::Float:
                    pMaterialProperty->SetData(propertyXml.GetAttribute<float_t>());
                    break;
                case ShaderVarType::Vec2:
                    pMaterialProperty->SetData(propertyXml.GetAttribute<SR_MATH_NS::FVector2>());
                    break;
                case ShaderVarType::Vec3:
                    pMaterialProperty->SetData(propertyXml.GetAttribute<SR_MATH_NS::FVector3>());
                    break;
                case ShaderVarType::Vec4:
                    pMaterialProperty->SetData(propertyXml.GetAttribute<SR_MATH_NS::FVector4>());
                    break;
                case ShaderVarType::Sampler2D: {
                    auto&& pTexture = SR_GTYPES_NS::Texture::Load(propertyXml.GetAttribute<std::string>());
                    pMaterialProperty->SetData(pTexture);
                    break;
                }
                default:
                    SRHalt("Unknown property!");
                    break;
            }
        }
    }

    std::list<SR_GTYPES_NS::Texture*> GetTexturesFromMatProperties(const MaterialProperties& properties) {
        std::list<SR_GTYPES_NS::Texture*> textures;

        properties.ForEachProperty<MaterialProperty>([&textures](auto&& pProperty){
            std::visit([&textures](ShaderPropertyVariant&& arg) {
                if (std::holds_alternative<SR_GTYPES_NS::Texture*>(arg)) {
                    if (auto&& value = std::get<SR_GTYPES_NS::Texture*>(arg)) {
                        textures.emplace_back(value);
                    }
                }
            }, pProperty->GetData());
        });

        return textures;
    }

    void MaterialProperty::Use(SR_GTYPES_NS::Shader* pShader) const noexcept {
        SR_TRACY_ZONE;

        auto&& hashId = GetName().GetHash();

        switch (GetShaderVarType()) {
            case ShaderVarType::Int:
                pShader->SetInt(hashId, std::get<int32_t>(GetData()));
                break;
            case ShaderVarType::Float:
                pShader->SetFloat(hashId, std::get<float_t>(GetData()));
                break;
            case ShaderVarType::Vec2:
                pShader->SetVec2(hashId, std::get<SR_MATH_NS::FVector2>(GetData()).template Cast<float_t>());
                break;
            case ShaderVarType::Vec3:
                pShader->SetVec3(hashId, std::get<SR_MATH_NS::FVector3>(GetData()).template Cast<float_t>());
                break;
            case ShaderVarType::Vec4:
                pShader->SetVec4(hashId, std::get<SR_MATH_NS::FVector4>(GetData()).template Cast<float_t>());
                break;
            case ShaderVarType::Sampler2D:
                pShader->SetSampler2D(hashId, std::get<SR_GTYPES_NS::Texture*>(GetData()));
                break;
            default:
                SRAssertOnce(false);
                break;
        }
    }

    bool MaterialProperty::IsSampler() const noexcept {
        return m_type >= ShaderVarType::Sampler2D && m_type <= ShaderVarType::Sampler2DShadow;
    }
}