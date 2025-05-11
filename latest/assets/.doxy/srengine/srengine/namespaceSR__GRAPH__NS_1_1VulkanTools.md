

# Namespace SR\_GRAPH\_NS::VulkanTools



[**Namespace List**](namespaces.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**VulkanTools**](namespaceSR__GRAPH__NS_1_1VulkanTools.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**MemoryManager**](classSR__GRAPH__NS_1_1VulkanTools_1_1MemoryManager.md) <br> |
| struct | [**VulkanFrameBufferAllocInfo**](structSR__GRAPH__NS_1_1VulkanTools_1_1VulkanFrameBufferAllocInfo.md) <br> |
























## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE std::vector&lt; VkVertexInputAttributeDescription &gt; | [**AbstractAttributesToVkAttributes**](#function-abstractattributestovkattributes) (const std::vector&lt; std::pair&lt; Vertices::Attribute, size\_t &gt; &gt; & attributes) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkCullModeFlagBits | [**AbstractCullModeToVk**](#function-abstractcullmodetovk) (CullMode cullMode) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkCompareOp | [**AbstractDepthOpToVk**](#function-abstractdepthoptovk) (DepthCompare depthCompare) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkImageAspectFlags | [**AbstractImageAspectToVkAspect**](#function-abstractimageaspecttovkaspect) (const ImageAspect & aspect) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkPolygonMode | [**AbstractPolygonModeToVk**](#function-abstractpolygonmodetovk) (PolygonMode polygonMode) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkPrimitiveTopology | [**AbstractPrimitiveTopologyToVk**](#function-abstractprimitivetopologytovk) (PrimitiveTopology primitiveTopology) <br> |
|  SR\_MAYBE\_UNUSED std::vector&lt; VkPushConstantRange &gt; | [**AbstractPushConstantToVkPushConstants**](#function-abstractpushconstanttovkpushconstants) (const [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) & createInfo) <br> |
|  SR\_MAYBE\_UNUSED VkShaderStageFlagBits | [**AbstractShaderToVkShader**](#function-abstractshadertovkshader) (ShaderStage stage) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkFormat | [**AbstractTextureCompToVkFormat**](#function-abstracttexturecomptovkformat) (const TextureCompression & comp, VkFormat format) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkFilter | [**AbstractTextureFilterToVkFilter**](#function-abstracttexturefiltertovkfilter) (const TextureFilter & filter) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkFormat | [**AbstractTextureFormatToVkFormat**](#function-abstracttextureformattovkformat) (const ImageFormat & format) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE std::vector&lt; VkVertexInputBindingDescription &gt; | [**AbstractVertexDescriptionsToVk**](#function-abstractvertexdescriptionstovk) (const std::vector&lt; SR\_VERTEX\_DESCRIPTION &gt; & descriptions) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkFormat | [**AttributeToVkFormat**](#function-attributetovkformat) (const Vertices::Attribute & attr) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkDescriptorType | [**CastAbsDescriptorTypeToVk**](#function-castabsdescriptortypetovk) (const DescriptorType & descriptorType) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE std::vector&lt; uint64\_t &gt; | [**CastAbsDescriptorTypeToVk**](#function-castabsdescriptortypetovk) (std::vector&lt; uint64\_t &gt; descriptorTypes) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE const std::vector&lt; uint64\_t &gt; & | [**ReferenceCastAbsDescriptorTypeToVk**](#function-referencecastabsdescriptortypetovk) (const std::vector&lt; DescriptorType &gt; & descriptorTypes) <br> |
|  SR\_MAYBE\_UNUSED std::optional&lt; std::vector&lt; VkDescriptorSetLayoutBinding &gt; &gt; | [**UniformsToDescriptorLayoutBindings**](#function-uniformstodescriptorlayoutbindings) (const UBOInfo & uniforms) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE std::vector&lt; std::pair&lt; std::string, ShaderStage &gt; &gt; | [**VkModulesToAbstractModules**](#function-vkmodulestoabstractmodules) (const std::vector&lt; std::pair&lt; std::string, VkShaderStageFlagBits &gt; &gt; & modules) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE VkShaderStageFlagBits | [**VkShaderShaderTypeToStage**](#function-vkshadershadertypetostage) (ShaderStage type) <br> |
|  SR\_MAYBE\_UNUSED SR\_FORCE\_INLINE ShaderStage | [**VkShaderStageToShaderType**](#function-vkshaderstagetoshadertype) (VkShaderStageFlagBits stage) <br> |


























## Public Static Functions Documentation




### function AbstractAttributesToVkAttributes 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE std::vector< VkVertexInputAttributeDescription > SR_GRAPH_NS::VulkanTools::AbstractAttributesToVkAttributes (
    const std::vector< std::pair< Vertices::Attribute, size_t > > & attributes
) 
```




<hr>



### function AbstractCullModeToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkCullModeFlagBits SR_GRAPH_NS::VulkanTools::AbstractCullModeToVk (
    CullMode cullMode
) 
```




<hr>



### function AbstractDepthOpToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkCompareOp SR_GRAPH_NS::VulkanTools::AbstractDepthOpToVk (
    DepthCompare depthCompare
) 
```




<hr>



### function AbstractImageAspectToVkAspect 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkImageAspectFlags SR_GRAPH_NS::VulkanTools::AbstractImageAspectToVkAspect (
    const ImageAspect & aspect
) 
```




<hr>



### function AbstractPolygonModeToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkPolygonMode SR_GRAPH_NS::VulkanTools::AbstractPolygonModeToVk (
    PolygonMode polygonMode
) 
```




<hr>



### function AbstractPrimitiveTopologyToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkPrimitiveTopology SR_GRAPH_NS::VulkanTools::AbstractPrimitiveTopologyToVk (
    PrimitiveTopology primitiveTopology
) 
```




<hr>



### function AbstractPushConstantToVkPushConstants 

```C++
static SR_MAYBE_UNUSED std::vector< VkPushConstantRange > SR_GRAPH_NS::VulkanTools::AbstractPushConstantToVkPushConstants (
    const SRShaderCreateInfo & createInfo
) 
```




<hr>



### function AbstractShaderToVkShader 

```C++
static SR_MAYBE_UNUSED VkShaderStageFlagBits SR_GRAPH_NS::VulkanTools::AbstractShaderToVkShader (
    ShaderStage stage
) 
```




<hr>



### function AbstractTextureCompToVkFormat 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkFormat SR_GRAPH_NS::VulkanTools::AbstractTextureCompToVkFormat (
    const TextureCompression & comp,
    VkFormat format
) 
```




<hr>



### function AbstractTextureFilterToVkFilter 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkFilter SR_GRAPH_NS::VulkanTools::AbstractTextureFilterToVkFilter (
    const TextureFilter & filter
) 
```




<hr>



### function AbstractTextureFormatToVkFormat 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkFormat SR_GRAPH_NS::VulkanTools::AbstractTextureFormatToVkFormat (
    const ImageFormat & format
) 
```




<hr>



### function AbstractVertexDescriptionsToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE std::vector< VkVertexInputBindingDescription > SR_GRAPH_NS::VulkanTools::AbstractVertexDescriptionsToVk (
    const std::vector< SR_VERTEX_DESCRIPTION > & descriptions
) 
```




<hr>



### function AttributeToVkFormat 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkFormat SR_GRAPH_NS::VulkanTools::AttributeToVkFormat (
    const Vertices::Attribute & attr
) 
```




<hr>



### function CastAbsDescriptorTypeToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkDescriptorType SR_GRAPH_NS::VulkanTools::CastAbsDescriptorTypeToVk (
    const DescriptorType & descriptorType
) 
```




<hr>



### function CastAbsDescriptorTypeToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE std::vector< uint64_t > SR_GRAPH_NS::VulkanTools::CastAbsDescriptorTypeToVk (
    std::vector< uint64_t > descriptorTypes
) 
```




<hr>



### function ReferenceCastAbsDescriptorTypeToVk 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE const std::vector< uint64_t > & SR_GRAPH_NS::VulkanTools::ReferenceCastAbsDescriptorTypeToVk (
    const std::vector< DescriptorType > & descriptorTypes
) 
```




<hr>



### function UniformsToDescriptorLayoutBindings 

```C++
static SR_MAYBE_UNUSED std::optional< std::vector< VkDescriptorSetLayoutBinding > > SR_GRAPH_NS::VulkanTools::UniformsToDescriptorLayoutBindings (
    const UBOInfo & uniforms
) 
```




<hr>



### function VkModulesToAbstractModules 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE std::vector< std::pair< std::string, ShaderStage > > SR_GRAPH_NS::VulkanTools::VkModulesToAbstractModules (
    const std::vector< std::pair< std::string, VkShaderStageFlagBits > > & modules
) 
```




<hr>



### function VkShaderShaderTypeToStage 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE VkShaderStageFlagBits SR_GRAPH_NS::VulkanTools::VkShaderShaderTypeToStage (
    ShaderStage type
) 
```




<hr>



### function VkShaderStageToShaderType 

```C++
static SR_MAYBE_UNUSED SR_FORCE_INLINE ShaderStage SR_GRAPH_NS::VulkanTools::VkShaderStageToShaderType (
    VkShaderStageFlagBits stage
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/Vulkan/AbstractCasts.h`

