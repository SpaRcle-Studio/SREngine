

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
|  void | [**DeInitGraphicsResource**](#function-deinitgraphicsresource) ([**SR\_UTILS\_NS::PassKey**](classSR__UTILS__NS_1_1PassKey.md)&lt; [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt;) <br> |
|  SR\_NODISCARD const PipelinePtr & | [**GetPipeline**](#function-getpipeline) () noexcept const<br> |
|  SR\_NODISCARD const [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) & | [**GetRenderContext**](#function-getrendercontext) () noexcept const<br> |
|   | [**IGraphicsResource**](#function-igraphicsresource-22) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |
|  SR\_NODISCARD bool | [**IsGraphicsResourceRegistered**](#function-isgraphicsresourceregistered) () noexcept const<br> |
|  void | [**RegisterGraphicsResource**](#function-registergraphicsresource) () <br> |
|  [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) & | [**operator=**](#function-operator) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**FreeVMemory**](#function-freevmemory) () <br> |
|   | [**IGraphicsResource**](#function-igraphicsresource-12) () = default<br> |
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
void SR_GRAPH_NS::Memory::IGraphicsResource::DeInitGraphicsResource (
    SR_UTILS_NS::PassKey < RenderContext >
) 
```




<hr>



### function GetPipeline 

```C++
inline SR_NODISCARD const PipelinePtr & SR_GRAPH_NS::Memory::IGraphicsResource::GetPipeline () noexcept const
```




<hr>



### function GetRenderContext 

```C++
inline SR_NODISCARD const RenderContextPtr & SR_GRAPH_NS::Memory::IGraphicsResource::GetRenderContext () noexcept const
```




<hr>



### function IGraphicsResource [2/2]

```C++
SR_GRAPH_NS::Memory::IGraphicsResource::IGraphicsResource (
    const IGraphicsResource &
) = delete
```




<hr>



### function IsGraphicsResourceRegistered 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::Memory::IGraphicsResource::IsGraphicsResourceRegistered () noexcept const
```




<hr>



### function RegisterGraphicsResource 

```C++
void SR_GRAPH_NS::Memory::IGraphicsResource::RegisterGraphicsResource () 
```




<hr>



### function operator= 

```C++
IGraphicsResource & SR_GRAPH_NS::Memory::IGraphicsResource::operator= (
    const IGraphicsResource &
) = delete
```




<hr>
## Protected Functions Documentation




### function FreeVMemory 

```C++
inline virtual void SR_GRAPH_NS::Memory::IGraphicsResource::FreeVMemory () 
```




<hr>



### function IGraphicsResource [1/2]

```C++
SR_GRAPH_NS::Memory::IGraphicsResource::IGraphicsResource () = default
```




<hr>



### function ~IGraphicsResource 

```C++
virtual SR_GRAPH_NS::Memory::IGraphicsResource::~IGraphicsResource () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Memory/IGraphicsResource.h`

