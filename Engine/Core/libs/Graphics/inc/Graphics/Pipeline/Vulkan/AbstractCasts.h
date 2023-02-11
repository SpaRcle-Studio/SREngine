//
// Created by Nikita on 10.06.2021.
//

#ifndef GAMEENGINE_ABSTRACTCASTS_H
#define GAMEENGINE_ABSTRACTCASTS_H

#include <Utils/Debug.h>
#include <EvoVulkan/Memory/Allocator.h>
#include <Graphics/Types/Descriptors.h>

namespace Framework::Graphics::VulkanTools {
    static SR_FORCE_INLINE VkFormat AttributeToVkFormat(const Vertices::Attribute& attr) {
        switch (attr) {
            case Vertices::Attribute::FLOAT_R32G32B32A32: return VK_FORMAT_R32G32B32A32_SFLOAT;
            case Vertices::Attribute::FLOAT_R32G32B32:    return VK_FORMAT_R32G32B32_SFLOAT;
            case Vertices::Attribute::FLOAT_R32G32:       return VK_FORMAT_R32G32_SFLOAT;
            default:                                      return VK_FORMAT_UNDEFINED;
        }
    }

    static SR_FORCE_INLINE VkFilter AbstractTextureFilterToVkFilter(const TextureFilter& filter) {
        switch (filter) {
            case TextureFilter::NEAREST: return VK_FILTER_NEAREST;
            case TextureFilter::LINEAR:  return VK_FILTER_LINEAR;

            case TextureFilter::NEAREST_MIPMAP_NEAREST:
            case TextureFilter::LINEAR_MIPMAP_NEAREST:
            case TextureFilter::NEAREST_MIPMAP_LINEAR:
            case TextureFilter::LINEAR_MIPMAP_LINEAR:
            case TextureFilter::Unknown:
            default:
                return VK_FILTER_MAX_ENUM;
        }
    }

    static SR_FORCE_INLINE std::vector<VkVertexInputBindingDescription> AbstractVertexDescriptionsToVk(const std::vector<SR_VERTEX_DESCRIPTION>& descriptions) {
        auto vkDescriptions = std::vector<VkVertexInputBindingDescription>();

        for (uint32_t i = 0; i < descriptions.size(); i++)
            vkDescriptions.push_back(EvoVulkan::Tools::Initializers::VertexInputBindingDescription(i, descriptions[i], VK_VERTEX_INPUT_RATE_VERTEX));

        return vkDescriptions;
    }

    static SR_FORCE_INLINE VkShaderStageFlagBits VkShaderShaderTypeToStage(ShaderStage type) {
        switch (type) {
            case ShaderStage::Fragment: return VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT;
            case ShaderStage::Vertex:   return VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT;
            default:
                SR_ERROR("VulkanTools::VkShaderShaderTypeToStage() : unknown type!");
                return VkShaderStageFlagBits::VK_SHADER_STAGE_FLAG_BITS_MAX_ENUM;
        }
    }

    static SR_FORCE_INLINE ShaderStage VkShaderStageToShaderType(VkShaderStageFlagBits stage) {
        switch (stage) {
            case VkShaderStageFlagBits::VK_SHADER_STAGE_FRAGMENT_BIT: return ShaderStage::Fragment;
            case VkShaderStageFlagBits::VK_SHADER_STAGE_VERTEX_BIT:   return ShaderStage::Vertex;
            default:
                SR_ERROR("VulkanTools::VkShaderStageToShaderType() : unknown stage!");
                return ShaderStage::Unknown;
        }
    }

    static SR_FORCE_INLINE std::vector<VkVertexInputAttributeDescription> AbstractAttributesToVkAttributes(
            const std::vector<std::pair<Vertices::Attribute, size_t>>& attributes)
    {
        auto vkDescrs = std::vector<VkVertexInputAttributeDescription>();

        for (uint32_t i = 0; i < attributes.size(); i++) {
            auto format = AttributeToVkFormat(attributes[i].first);
            if (format == VK_FORMAT_UNDEFINED) {
                SR_ERROR("VulkanTools::AbstractDescriptionsToVkDescriptions() : unknown attribute!");
                return { };
            }

            vkDescrs.emplace_back(EvoVulkan::Tools::Initializers::VertexInputAttributeDescription(0, i, format, attributes[i].second));
        }

        return vkDescrs;
    }

    static SR_FORCE_INLINE std::vector<std::pair<std::string, ShaderStage>> VkModulesToAbstractModules(
            const std::vector<std::pair<std::string, VkShaderStageFlagBits>>& modules)
    {
        auto abstract = std::vector<std::pair<std::string, ShaderStage>>();
        for (const auto& a : modules)
            abstract.emplace_back(std::pair(a.first, VkShaderStageToShaderType(a.second)));
        return abstract;
    }

    static SR_FORCE_INLINE VkPrimitiveTopology AbstractPrimitiveTopologyToVk(PrimitiveTopology primitiveTopology) {
        switch (primitiveTopology) {
            case PrimitiveTopology::PointList: return VK_PRIMITIVE_TOPOLOGY_POINT_LIST;
            case PrimitiveTopology::LineList: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST;
            case PrimitiveTopology::LineStrip: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP;
            case PrimitiveTopology::TriangleList: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
            case PrimitiveTopology::TriangleStrip: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP;
            case PrimitiveTopology::TriangleFan: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN;
            case PrimitiveTopology::LineListWithAdjacency: return VK_PRIMITIVE_TOPOLOGY_LINE_LIST_WITH_ADJACENCY;
            case PrimitiveTopology::LineStripWithAdjacency: return VK_PRIMITIVE_TOPOLOGY_LINE_STRIP_WITH_ADJACENCY;
            case PrimitiveTopology::TriangleListWithAdjacency: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST_WITH_ADJACENCY;
            case PrimitiveTopology::TriangleStripWithAdjacency: return VK_PRIMITIVE_TOPOLOGY_TRIANGLE_STRIP_WITH_ADJACENCY;
            case PrimitiveTopology::PathList: return VK_PRIMITIVE_TOPOLOGY_PATCH_LIST;
            case PrimitiveTopology::Unknown:
                break;
        }
        return VkPrimitiveTopology::VK_PRIMITIVE_TOPOLOGY_MAX_ENUM;
    }

    static SR_FORCE_INLINE VkPolygonMode AbstractPolygonModeToVk(PolygonMode polygonMode) {
        switch (polygonMode) {
            case PolygonMode::Fill:  return VK_POLYGON_MODE_FILL;
            case PolygonMode::Line:  return VK_POLYGON_MODE_LINE;
            case PolygonMode::Point: return VK_POLYGON_MODE_POINT;
            case PolygonMode::Unknown:
                break;
        }
        return VkPolygonMode::VK_POLYGON_MODE_MAX_ENUM;
    }

    static SR_FORCE_INLINE VkCullModeFlagBits AbstractCullModeToVk(CullMode cullMode) {
        switch (cullMode) {
            case CullMode::None:         return VK_CULL_MODE_NONE;
            case CullMode::Front:        return VK_CULL_MODE_FRONT_BIT;
            case CullMode::Back:         return VK_CULL_MODE_BACK_BIT;
            case CullMode::FrontAndBack: return VK_CULL_MODE_FRONT_AND_BACK;
            case CullMode::Unknown:
                break;
        }
        return VkCullModeFlagBits::VK_CULL_MODE_FLAG_BITS_MAX_ENUM;
    }

    static SR_FORCE_INLINE VkCompareOp AbstractDepthOpToVk(DepthCompare depthCompare) {
        switch (depthCompare) {
            case DepthCompare::Never:          return VK_COMPARE_OP_NEVER;
            case DepthCompare::Less:           return VK_COMPARE_OP_LESS;
            case DepthCompare::Equal:          return VK_COMPARE_OP_EQUAL;
            case DepthCompare::LessOrEqual:    return VK_COMPARE_OP_LESS_OR_EQUAL;
            case DepthCompare::Greater:        return VK_COMPARE_OP_GREATER;
            case DepthCompare::NotEqual:       return VK_COMPARE_OP_NOT_EQUAL;
            case DepthCompare::GreaterOrEqual: return VK_COMPARE_OP_GREATER_OR_EQUAL;
            case DepthCompare::Always:         return VK_COMPARE_OP_ALWAYS;
            case DepthCompare::Unknown:
                break;
        }
        return VkCompareOp::VK_COMPARE_OP_MAX_ENUM;
    }

    static SR_FORCE_INLINE VkDescriptorType CastAbsDescriptorTypeToVk(const DescriptorType& descriptorType) {
        switch (descriptorType) {
            case DescriptorType::Uniform:
                return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
            case DescriptorType::CombinedImage:
                return VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
            default: {
                SR_ERROR("VulkanTools::CastAbsDescriptorTypeToVk() : unknown type!");
                return VK_DESCRIPTOR_TYPE_MAX_ENUM;
            }
        }
    }

    static SR_FORCE_INLINE std::set<VkDescriptorType> CastAbsDescriptorTypeToVk(const std::set<DescriptorType>& descriptorTypes) {
        std::set<VkDescriptorType> vk = {};
        for (const auto& type : descriptorTypes) {
            switch (type) {
                case DescriptorType::Uniform: {
                    vk.insert(VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER);
                    break;
                }
                case DescriptorType::CombinedImage: {
                    vk.insert(VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER);
                    break;
                }
                default: {
                    SR_ERROR("VulkanTools::CastAbsDescriptorTypeToVk() : unknown type!");
                    return {};
                }
            }
        }
        return vk;
    }

    static SR_FORCE_INLINE VkFormat AbstractTextureFormatToVkFormat(const ColorFormat& format) {
        switch (format) {
            case ColorFormat::RGBA8_UNORM: return VK_FORMAT_R8G8B8A8_UNORM;
            case ColorFormat::BGRA8_UNORM: return VK_FORMAT_B8G8R8A8_UNORM;
            case ColorFormat::RGBA16_UNORM: return VK_FORMAT_R16G16B16A16_UNORM;
            case ColorFormat::RGBA16_SFLOAT: return VK_FORMAT_R16G16B16A16_SFLOAT;

            case ColorFormat::RGB8_UNORM: return VK_FORMAT_R8G8B8_UNORM;
            case ColorFormat::RGB16_UNORM: return VK_FORMAT_R16G16B16_UNORM;

            case ColorFormat::RGBA8_SRGB: return VK_FORMAT_R8G8B8A8_SRGB;

            case ColorFormat::R8_UNORM: return VK_FORMAT_R8_UNORM;
            case ColorFormat::R16_UNORM: return VK_FORMAT_R16_UNORM;
            case ColorFormat::R32_SFLOAT: return VK_FORMAT_R32_SFLOAT;
            case ColorFormat::R64_SFLOAT: return VK_FORMAT_R64_SFLOAT;

            case ColorFormat::R8_UINT: return VK_FORMAT_R8_UINT;
            case ColorFormat::R16_UINT: return VK_FORMAT_R16_UINT;
            case ColorFormat::R32_UINT: return VK_FORMAT_R32_UINT;
            case ColorFormat::R64_UINT: return VK_FORMAT_R64_UINT;

            case ColorFormat::RG8_UNORM: return VK_FORMAT_R8G8_UNORM;

            case ColorFormat::Unknown:
            default:
                break;
        }
        return VkFormat::VK_FORMAT_MAX_ENUM;
    }

    static SR_FORCE_INLINE VkFormat AbstractTextureCompToVkFormat(const TextureCompression& comp, VkFormat format) {
        switch (comp) {
            case TextureCompression::None: return format;
            case TextureCompression::BC1:
                switch (format) {
                    case VK_FORMAT_R16G16B16A16_UNORM:
                    case VK_FORMAT_R8G8B8A8_UNORM:
                        return VK_FORMAT_BC1_RGBA_UNORM_BLOCK;
                    case VK_FORMAT_R8G8B8_UNORM:
                        return VK_FORMAT_BC1_RGB_UNORM_BLOCK;

                    case VK_FORMAT_R8G8B8A8_SRGB:
                        return VK_FORMAT_BC1_RGBA_SRGB_BLOCK;
                    case VK_FORMAT_R8G8B8_SRGB:
                        return VK_FORMAT_BC1_RGB_SRGB_BLOCK;

                    default:
                        return VK_FORMAT_MAX_ENUM;
                }
            case TextureCompression::BC2:
                switch (format) {
                    case VK_FORMAT_R16G16B16A16_UNORM:
                    case VK_FORMAT_R8G8B8A8_UNORM:
                    case VK_FORMAT_R8G8B8_UNORM:
                        return VK_FORMAT_BC2_UNORM_BLOCK;

                    case VK_FORMAT_R8G8B8A8_SRGB:
                    case VK_FORMAT_R8G8B8_SRGB:
                        return VK_FORMAT_BC2_SRGB_BLOCK;

                    default:
                        return VK_FORMAT_MAX_ENUM;
                }
            case TextureCompression::BC3:
                switch (format) {
                    case VK_FORMAT_R16G16B16A16_UNORM:
                    case VK_FORMAT_R8G8B8A8_UNORM:
                    case VK_FORMAT_R8G8B8_UNORM:
                        return VK_FORMAT_BC3_UNORM_BLOCK;

                    case VK_FORMAT_R8G8B8A8_SRGB:
                    case VK_FORMAT_R8G8B8_SRGB:
                        return VK_FORMAT_BC3_SRGB_BLOCK;

                    default:
                        return VK_FORMAT_MAX_ENUM;
                }
            case TextureCompression::BC4:
                switch (format) {
                    case VK_FORMAT_R16G16B16A16_UNORM:
                    case VK_FORMAT_R8G8B8A8_UNORM:
                    case VK_FORMAT_R8G8B8_UNORM:
                        return VK_FORMAT_BC4_UNORM_BLOCK;

                    default:
                        return VK_FORMAT_MAX_ENUM;
                }
            case TextureCompression::BC5:
                switch (format) {
                    case VK_FORMAT_R16G16B16A16_UNORM:
                    case VK_FORMAT_R8G8B8A8_UNORM:
                    case VK_FORMAT_R8G8B8_UNORM:
                        return VK_FORMAT_BC5_UNORM_BLOCK;

                    default:
                        return VK_FORMAT_MAX_ENUM;
                }
            case TextureCompression::BC6:
                return VK_FORMAT_MAX_ENUM;
            case TextureCompression::BC7:
                switch (format) {
                    case VK_FORMAT_R16G16B16A16_UNORM:
                    case VK_FORMAT_R8G8B8A8_UNORM:
                    case VK_FORMAT_R8G8B8_UNORM:
                        return VK_FORMAT_BC7_UNORM_BLOCK;

                    case VK_FORMAT_R8G8B8A8_SRGB:
                    case VK_FORMAT_R8G8B8_SRGB:
                        return VK_FORMAT_BC7_SRGB_BLOCK;

                    default:
                        return VK_FORMAT_MAX_ENUM;
                }
        }

        return VkFormat::VK_FORMAT_MAX_ENUM;
    }
}

#endif //GAMEENGINE_ABSTRACTCASTS_H
