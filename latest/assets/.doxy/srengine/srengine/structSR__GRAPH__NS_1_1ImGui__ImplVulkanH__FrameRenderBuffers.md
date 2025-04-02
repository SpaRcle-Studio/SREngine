

# Struct SR\_GRAPH\_NS::ImGui\_ImplVulkanH\_FrameRenderBuffers



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ImGui\_ImplVulkanH\_FrameRenderBuffers**](structSR__GRAPH__NS_1_1ImGui__ImplVulkanH__FrameRenderBuffers.md)



[More...](#detailed-description)

* `#include <ImGuiInternal.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  VkBuffer | [**IndexBuffer**](#variable-indexbuffer)  <br> |
|  VkDeviceMemory | [**IndexBufferMemory**](#variable-indexbuffermemory)  <br> |
|  VkDeviceSize | [**IndexBufferSize**](#variable-indexbuffersize)  <br> |
|  VkBuffer | [**VertexBuffer**](#variable-vertexbuffer)  <br> |
|  VkDeviceMemory | [**VertexBufferMemory**](#variable-vertexbuffermemory)  <br> |
|  VkDeviceSize | [**VertexBufferSize**](#variable-vertexbuffersize)  <br> |












































## Detailed Description


Reusable buffers used for rendering 1 current in-flight frame, for ImGui\_ImplVulkan\_RenderDrawData() [Please zero-clear before use!] 


    
## Public Attributes Documentation




### variable IndexBuffer 

```C++
VkBuffer SR_GRAPH_NS::ImGui_ImplVulkanH_FrameRenderBuffers::IndexBuffer;
```




<hr>



### variable IndexBufferMemory 

```C++
VkDeviceMemory SR_GRAPH_NS::ImGui_ImplVulkanH_FrameRenderBuffers::IndexBufferMemory;
```




<hr>



### variable IndexBufferSize 

```C++
VkDeviceSize SR_GRAPH_NS::ImGui_ImplVulkanH_FrameRenderBuffers::IndexBufferSize;
```




<hr>



### variable VertexBuffer 

```C++
VkBuffer SR_GRAPH_NS::ImGui_ImplVulkanH_FrameRenderBuffers::VertexBuffer;
```




<hr>



### variable VertexBufferMemory 

```C++
VkDeviceMemory SR_GRAPH_NS::ImGui_ImplVulkanH_FrameRenderBuffers::VertexBufferMemory;
```




<hr>



### variable VertexBufferSize 

```C++
VkDeviceSize SR_GRAPH_NS::ImGui_ImplVulkanH_FrameRenderBuffers::VertexBufferSize;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Overlay/ImGuiInternal.h`

