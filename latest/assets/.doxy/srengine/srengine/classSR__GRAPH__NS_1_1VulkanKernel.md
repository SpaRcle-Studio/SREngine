

# Class SR\_GRAPH\_NS::VulkanKernel



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**VulkanKernel**](classSR__GRAPH__NS_1_1VulkanKernel.md)








Inherits the following classes: EvoVulkan::Core::VulkanKernel


































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**BuildCmdBuffers**](#function-buildcmdbuffers) () override<br> |
|  bool | [**Destroy**](#function-destroy) () override<br> |
|  SR\_NODISCARD bool | [**IsRayTracingRequired**](#function-israytracingrequired) () noexcept override const<br> |
|  SR\_NODISCARD bool | [**IsWindowValid**](#function-iswindowvalid) () override const<br> |
|  bool | [**OnComplete**](#function-oncomplete) () override<br> |
|  bool | [**OnResize**](#function-onresize) () override<br> |
|  void | [**PollWindowEvents**](#function-pollwindowevents) () override<br> |
|  void | [**SetGUIEnabled**](#function-setguienabled) (bool enabled) override<br> |
|   | [**VulkanKernel**](#function-vulkankernel) (PipelinePtr pPipeline) <br> |
|   | [**~VulkanKernel**](#function-vulkankernel) () override<br> |




























## Public Functions Documentation




### function BuildCmdBuffers 

```C++
inline bool SR_GRAPH_NS::VulkanKernel::BuildCmdBuffers () override
```




<hr>



### function Destroy 

```C++
inline bool SR_GRAPH_NS::VulkanKernel::Destroy () override
```




<hr>



### function IsRayTracingRequired 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanKernel::IsRayTracingRequired () noexcept override const
```




<hr>



### function IsWindowValid 

```C++
SR_NODISCARD bool SR_GRAPH_NS::VulkanKernel::IsWindowValid () override const
```




<hr>



### function OnComplete 

```C++
inline bool SR_GRAPH_NS::VulkanKernel::OnComplete () override
```




<hr>



### function OnResize 

```C++
bool SR_GRAPH_NS::VulkanKernel::OnResize () override
```




<hr>



### function PollWindowEvents 

```C++
void SR_GRAPH_NS::VulkanKernel::PollWindowEvents () override
```




<hr>



### function SetGUIEnabled 

```C++
void SR_GRAPH_NS::VulkanKernel::SetGUIEnabled (
    bool enabled
) override
```




<hr>



### function VulkanKernel 

```C++
explicit SR_GRAPH_NS::VulkanKernel::VulkanKernel (
    PipelinePtr pPipeline
) 
```




<hr>



### function ~VulkanKernel 

```C++
SR_GRAPH_NS::VulkanKernel::~VulkanKernel () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/Vulkan/VulkanKernel.h`

