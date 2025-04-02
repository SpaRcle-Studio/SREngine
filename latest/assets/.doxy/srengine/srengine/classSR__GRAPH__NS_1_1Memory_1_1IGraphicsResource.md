

# Class SR\_GRAPH\_NS::Memory::IGraphicsResource



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)



_Не наследуемся от NonCopyable, чтобы не возникло конфликтов с IResource._ 

* `#include <IGraphicsResource.h>`





Inherited by the following classes: [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](#typedef-pipelineptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**RenderContextPtr**](#typedef-rendercontextptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**DeInitGraphicsResource**](#function-deinitgraphicsresource) () <br> |
| virtual void | [**FreeVideoMemory**](#function-freevideomemory) () <br> |
|  SR\_NODISCARD PipelinePtr | [**GetPipeline**](#function-getpipeline) () noexcept const<br> |
|  SR\_NODISCARD [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) | [**GetRenderContext**](#function-getrendercontext) () noexcept const<br> |
|   | [**IGraphicsResource**](#function-igraphicsresource-22) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsCalculated**](#function-iscalculated) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsGraphicsResourceRegistered**](#function-isgraphicsresourceregistered) () const<br> |
|  void | [**MarkPipelineUnBuild**](#function-markpipelineunbuild) () <br> |
|  void | [**SetRenderContext**](#function-setrendercontext) (const [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) & renderContext) <br> |
|  [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) & | [**operator=**](#function-operator) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**m\_isCalculated**](#variable-m_iscalculated)   = `false`<br> |
|  PipelinePtr | [**m\_pipeline**](#variable-m_pipeline)  <br> |
|  [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) | [**m\_renderContext**](#variable-m_rendercontext)   = `nullptr`<br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  constexpr | [**IGraphicsResource**](#function-igraphicsresource-12) () = default<br> |
| virtual  | [**~IGraphicsResource**](#function-igraphicsresource) () <br> |




## Public Types Documentation




### typedef PipelinePtr 

```C++
using SR_GRAPH_NS::Memory::IGraphicsResource::PipelinePtr =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef RenderContextPtr 

```C++
using SR_GRAPH_NS::Memory::IGraphicsResource::RenderContextPtr =  RenderContext*;
```




<hr>
## Public Functions Documentation




### function DeInitGraphicsResource 

```C++
virtual void SR_GRAPH_NS::Memory::IGraphicsResource::DeInitGraphicsResource () 
```



данный метод можно вызывать только из контекста рендера, в котором он был инициализирован. Либо из кластера если это меш 


        

<hr>



### function FreeVideoMemory 

```C++
inline virtual void SR_GRAPH_NS::Memory::IGraphicsResource::FreeVideoMemory () 
```




<hr>



### function GetPipeline 

```C++
inline SR_NODISCARD PipelinePtr SR_GRAPH_NS::Memory::IGraphicsResource::GetPipeline () noexcept const
```




<hr>



### function GetRenderContext 

```C++
inline SR_NODISCARD RenderContextPtr SR_GRAPH_NS::Memory::IGraphicsResource::GetRenderContext () noexcept const
```




<hr>



### function IGraphicsResource [2/2]

```C++
SR_GRAPH_NS::Memory::IGraphicsResource::IGraphicsResource (
    const IGraphicsResource &
) = delete
```




<hr>



### function IsCalculated 

```C++
inline SR_NODISCARD SR_FORCE_INLINE bool SR_GRAPH_NS::Memory::IGraphicsResource::IsCalculated () const
```




<hr>



### function IsGraphicsResourceRegistered 

```C++
inline SR_NODISCARD SR_FORCE_INLINE bool SR_GRAPH_NS::Memory::IGraphicsResource::IsGraphicsResourceRegistered () const
```




<hr>



### function MarkPipelineUnBuild 

```C++
void SR_GRAPH_NS::Memory::IGraphicsResource::MarkPipelineUnBuild () 
```




<hr>



### function SetRenderContext 

```C++
void SR_GRAPH_NS::Memory::IGraphicsResource::SetRenderContext (
    const RenderContextPtr & renderContext
) 
```




<hr>



### function operator= 

```C++
IGraphicsResource & SR_GRAPH_NS::Memory::IGraphicsResource::operator= (
    const IGraphicsResource &
) = delete
```




<hr>
## Protected Attributes Documentation




### variable m\_isCalculated 

```C++
bool SR_GRAPH_NS::Memory::IGraphicsResource::m_isCalculated;
```




<hr>



### variable m\_pipeline 

```C++
PipelinePtr SR_GRAPH_NS::Memory::IGraphicsResource::m_pipeline;
```




<hr>



### variable m\_renderContext 

```C++
RenderContextPtr SR_GRAPH_NS::Memory::IGraphicsResource::m_renderContext;
```




<hr>
## Protected Functions Documentation




### function IGraphicsResource [1/2]

```C++
constexpr SR_GRAPH_NS::Memory::IGraphicsResource::IGraphicsResource () = default
```




<hr>



### function ~IGraphicsResource 

```C++
virtual SR_GRAPH_NS::Memory::IGraphicsResource::~IGraphicsResource () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Memory/IGraphicsResource.h`

