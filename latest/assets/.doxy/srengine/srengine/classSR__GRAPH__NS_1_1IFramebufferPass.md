

# Class SR\_GRAPH\_NS::IFramebufferPass



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**IFramebufferPass**](classSR__GRAPH__NS_1_1IFramebufferPass.md)










Inherited by the following classes: [SR\_GRAPH\_NS::FramebufferPass](classSR__GRAPH__NS_1_1FramebufferPass.md),  [SR\_GRAPH\_NS::OffScreenMeshDrawerPass](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md),  [SR\_GRAPH\_NS::SSAOPass](classSR__GRAPH__NS_1_1SSAOPass.md),  [SR\_GRAPH\_NS::ShaderOverridePass](classSR__GRAPH__NS_1_1ShaderOverridePass.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &gt; | [**ClearColors**](#typedef-clearcolors)  <br> |
| typedef std::list&lt; ImageFormat &gt; | [**ColorFormats**](#typedef-colorformats)  <br> |
| typedef [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**FramebufferPtr**](#typedef-framebufferptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD ClearColors | [**GetClearColors**](#function-getclearcolors) () noexcept const<br> |
|  SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetClearDepth**](#function-getcleardepth) () noexcept const<br> |
|  SR\_NODISCARD FramebufferPtr | [**GetFramebuffer**](#function-getframebuffer) () noexcept const<br> |
|  SR\_NODISCARD uint8\_t | [**GetLayersCount**](#function-getlayerscount) () noexcept const<br> |
|   | [**IFramebufferPass**](#function-iframebufferpass) () <br> |
|  SR\_NODISCARD bool | [**IsDirectional**](#function-isdirectional) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFrameBufferRendered**](#function-isframebufferrendered) () noexcept const<br> |
| virtual  | [**~IFramebufferPass**](#function-iframebufferpass) () = default<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**m\_isFrameBufferRendered**](#variable-m_isframebufferrendered)   = `false`<br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* | [**GetFrameBufferRenderTechnique**](#function-getframebufferrendertechnique) () const = 0<br> |
|  void | [**LoadFramebufferSettings**](#function-loadframebuffersettings) (const SR\_XML\_NS::Node & passNode) <br> |
|  bool | [**RenderFrameBuffer**](#function-renderframebuffer-12) (const PipelinePtr & pPipeline) <br> |
| virtual void | [**RenderFrameBufferInner**](#function-renderframebufferinner) () <br> |
|  void | [**UpdateFrameBuffer**](#function-updateframebuffer) (const PipelinePtr & pPipeline) <br> |
| virtual void | [**UpdateFrameBufferInner**](#function-updateframebufferinner) () <br> |




## Public Types Documentation




### typedef ClearColors 

```C++
using SR_GRAPH_NS::IFramebufferPass::ClearColors =  std::vector<SR_MATH_NS::FColor>;
```




<hr>



### typedef ColorFormats 

```C++
using SR_GRAPH_NS::IFramebufferPass::ColorFormats =  std::list<ImageFormat>;
```




<hr>



### typedef FramebufferPtr 

```C++
using SR_GRAPH_NS::IFramebufferPass::FramebufferPtr =  SR_GTYPES_NS::Framebuffer*;
```




<hr>
## Public Functions Documentation




### function GetClearColors 

```C++
inline SR_NODISCARD ClearColors SR_GRAPH_NS::IFramebufferPass::GetClearColors () noexcept const
```




<hr>



### function GetClearDepth 

```C++
inline SR_NODISCARD std::optional< float_t > SR_GRAPH_NS::IFramebufferPass::GetClearDepth () noexcept const
```




<hr>



### function GetFramebuffer 

```C++
SR_NODISCARD FramebufferPtr SR_GRAPH_NS::IFramebufferPass::GetFramebuffer () noexcept const
```




<hr>



### function GetLayersCount 

```C++
SR_NODISCARD uint8_t SR_GRAPH_NS::IFramebufferPass::GetLayersCount () noexcept const
```




<hr>



### function IFramebufferPass 

```C++
SR_GRAPH_NS::IFramebufferPass::IFramebufferPass () 
```




<hr>



### function IsDirectional 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::IFramebufferPass::IsDirectional () noexcept const
```




<hr>



### function IsFrameBufferRendered 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::IFramebufferPass::IsFrameBufferRendered () noexcept const
```




<hr>



### function ~IFramebufferPass 

```C++
virtual SR_GRAPH_NS::IFramebufferPass::~IFramebufferPass () = default
```




<hr>
## Protected Attributes Documentation




### variable m\_isFrameBufferRendered 

```C++
bool SR_GRAPH_NS::IFramebufferPass::m_isFrameBufferRendered;
```




<hr>
## Protected Functions Documentation




### function GetFrameBufferRenderTechnique 

```C++
virtual SR_NODISCARD IRenderTechnique * SR_GRAPH_NS::IFramebufferPass::GetFrameBufferRenderTechnique () const = 0
```




<hr>



### function LoadFramebufferSettings 

```C++
void SR_GRAPH_NS::IFramebufferPass::LoadFramebufferSettings (
    const SR_XML_NS::Node & passNode
) 
```




<hr>



### function RenderFrameBuffer [1/2]

```C++
bool SR_GRAPH_NS::IFramebufferPass::RenderFrameBuffer (
    const PipelinePtr & pPipeline
) 
```




<hr>



### function RenderFrameBufferInner 

```C++
inline virtual void SR_GRAPH_NS::IFramebufferPass::RenderFrameBufferInner () 
```




<hr>



### function UpdateFrameBuffer 

```C++
void SR_GRAPH_NS::IFramebufferPass::UpdateFrameBuffer (
    const PipelinePtr & pPipeline
) 
```




<hr>



### function UpdateFrameBufferInner 

```C++
inline virtual void SR_GRAPH_NS::IFramebufferPass::UpdateFrameBufferInner () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Pass/IFramebufferPass.h`

