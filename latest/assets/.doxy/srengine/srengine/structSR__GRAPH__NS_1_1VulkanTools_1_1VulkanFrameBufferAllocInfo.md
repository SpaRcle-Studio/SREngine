

# Struct SR\_GRAPH\_NS::VulkanTools::VulkanFrameBufferAllocInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**VulkanTools**](namespaceSR__GRAPH__NS_1_1VulkanTools.md) **>** [**VulkanFrameBufferAllocInfo**](structSR__GRAPH__NS_1_1VulkanTools_1_1VulkanFrameBufferAllocInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32\_t | [**FBO**](#variable-fbo)   = `SR\_ID\_INVALID`<br> |
|  EvoVulkan::Complexes::FrameBufferFeatures | [**features**](#variable-features)  <br> |
|  uint8\_t | [**frame**](#variable-frame)   = `0`<br> |
|  uint32\_t | [**height**](#variable-height)   = `0`<br> |
|  std::vector&lt; VkFormat &gt; | [**inputColorAttachments**](#variable-inputcolorattachments)  <br> |
|  uint32\_t | [**layersCount**](#variable-layerscount)   = `0`<br> |
|  uint8\_t | [**maxFrames**](#variable-maxframes)   = `0`<br> |
|  std::vector&lt; int32\_t &gt; | [**oldColorAttachments**](#variable-oldcolorattachments)  <br> |
|  [**DepthLayer**](structSR__GRAPH__NS_1_1DepthLayer.md) \* | [**pDepth**](#variable-pdepth)   = `nullptr`<br> |
|  std::vector&lt; int32\_t &gt; \* | [**pOutputColorAttachments**](#variable-poutputcolorattachments)   = `nullptr`<br> |
|  uint8\_t | [**sampleCount**](#variable-samplecount)   = `0`<br> |
|  uint32\_t | [**width**](#variable-width)   = `0`<br> |












































## Public Attributes Documentation




### variable FBO 

```C++
int32_t SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::FBO;
```




<hr>



### variable features 

```C++
EvoVulkan::Complexes::FrameBufferFeatures SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::features;
```




<hr>



### variable frame 

```C++
uint8_t SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::frame;
```




<hr>



### variable height 

```C++
uint32_t SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::height;
```




<hr>



### variable inputColorAttachments 

```C++
std::vector<VkFormat> SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::inputColorAttachments;
```




<hr>



### variable layersCount 

```C++
uint32_t SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::layersCount;
```




<hr>



### variable maxFrames 

```C++
uint8_t SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::maxFrames;
```




<hr>



### variable oldColorAttachments 

```C++
std::vector<int32_t> SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::oldColorAttachments;
```




<hr>



### variable pDepth 

```C++
DepthLayer* SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::pDepth;
```




<hr>



### variable pOutputColorAttachments 

```C++
std::vector<int32_t>* SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::pOutputColorAttachments;
```




<hr>



### variable sampleCount 

```C++
uint8_t SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::sampleCount;
```




<hr>



### variable width 

```C++
uint32_t SR_GRAPH_NS::VulkanTools::VulkanFrameBufferAllocInfo::width;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/Vulkan/VulkanMemory.h`

