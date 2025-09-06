

# Struct SR\_GRAPH\_NS::PipelineState



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**PipelineState**](structSR__GRAPH__NS_1_1PipelineState.md)



[More...](#detailed-description)

* `#include <PipelineState.h>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**FramebufferPtr**](#typedef-framebufferptr)  <br> |
| typedef [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](#typedef-shaderptr)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  int32\_t | [**FBOId**](#variable-fboid)   = `SR\_ID\_INVALID`<br> |
|  int32\_t | [**IBOId**](#variable-iboid)   = `SR\_ID\_INVALID`<br> |
|  int32\_t | [**SSBOId**](#variable-ssboid)   = `SR\_ID\_INVALID`<br> |
|  int32\_t | [**UBOId**](#variable-uboid)   = `SR\_ID\_INVALID`<br> |
|  int32\_t | [**VBOId**](#variable-vboid)   = `SR\_ID\_INVALID`<br> |
|  uint32\_t | [**allocatedMemory**](#variable-allocatedmemory)   = `0`<br>_Объем выделенной памяти_  |
|  uint32\_t | [**allocations**](#variable-allocations)   = `0`<br>_Сколько было произведено выделений памяти_  |
|  uint32\_t | [**deletions**](#variable-deletions)   = `0`<br>_Сколько было произведено удалений памяти_  |
|  int32\_t | [**descriptorSetId**](#variable-descriptorsetid)   = `SR\_ID\_INVALID`<br> |
|  uint32\_t | [**drawCalls**](#variable-drawcalls)   = `0`<br>_Количество вызовов Draw и подобное_  |
|  int32\_t | [**frameBufferId**](#variable-framebufferid)   = `SR\_ID\_INVALID`<br> |
|  uint32\_t | [**frameBufferLayer**](#variable-framebufferlayer)   = `0`<br> |
|  bool | [**hasRenderData**](#variable-hasrenderdata)   = `false`<br> |
|  uint32\_t | [**operations**](#variable-operations)   = `0`<br>_Количество всех обращений к API в процессе отрисовки_  |
|  FramebufferPtr | [**pFrameBuffer**](#variable-pframebuffer)   = `nullptr`<br> |
|  [**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* | [**pRenderStrategy**](#variable-prenderstrategy)   = `nullptr`<br> |
|  ShaderPtr | [**pShader**](#variable-pshader)   = `nullptr`<br> |
|  int32\_t | [**shaderId**](#variable-shaderid)   = `SR\_ID\_INVALID`<br> |
|  uint32\_t | [**transferredCount**](#variable-transferredcount)   = `0`<br>_Количество обращений по передаче данных_  |
|  uint32\_t | [**transferredMemory**](#variable-transferredmemory)   = `0`<br>_Объем данных, который был передан на видеокарту в процессе отрисовки_  |
|  uint32\_t | [**usedShaders**](#variable-usedshaders)   = `0`<br> |
|  uint32\_t | [**usedTextures**](#variable-usedtextures)   = `0`<br> |
|  uint32\_t | [**vertices**](#variable-vertices)   = `0`<br>_Количество вершин, которые были отрисованы_  |












































## Detailed Description


Состояние графического конвейера Сбрасывается каждый кадр 


    
## Public Types Documentation




### typedef FramebufferPtr 

```C++
using SR_GRAPH_NS::PipelineState::FramebufferPtr =  SR_GTYPES_NS::Framebuffer*;
```




<hr>



### typedef ShaderPtr 

```C++
using SR_GRAPH_NS::PipelineState::ShaderPtr =  SR_GTYPES_NS::Shader*;
```




<hr>
## Public Attributes Documentation




### variable FBOId 

```C++
int32_t SR_GRAPH_NS::PipelineState::FBOId;
```




<hr>



### variable IBOId 

```C++
int32_t SR_GRAPH_NS::PipelineState::IBOId;
```




<hr>



### variable SSBOId 

```C++
int32_t SR_GRAPH_NS::PipelineState::SSBOId;
```




<hr>



### variable UBOId 

```C++
int32_t SR_GRAPH_NS::PipelineState::UBOId;
```




<hr>



### variable VBOId 

```C++
int32_t SR_GRAPH_NS::PipelineState::VBOId;
```




<hr>



### variable allocatedMemory 

_Объем выделенной памяти_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::allocatedMemory;
```




<hr>



### variable allocations 

_Сколько было произведено выделений памяти_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::allocations;
```




<hr>



### variable deletions 

_Сколько было произведено удалений памяти_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::deletions;
```




<hr>



### variable descriptorSetId 

```C++
int32_t SR_GRAPH_NS::PipelineState::descriptorSetId;
```




<hr>



### variable drawCalls 

_Количество вызовов Draw и подобное_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::drawCalls;
```




<hr>



### variable frameBufferId 

```C++
int32_t SR_GRAPH_NS::PipelineState::frameBufferId;
```




<hr>



### variable frameBufferLayer 

```C++
uint32_t SR_GRAPH_NS::PipelineState::frameBufferLayer;
```




<hr>



### variable hasRenderData 

```C++
bool SR_GRAPH_NS::PipelineState::hasRenderData;
```




<hr>



### variable operations 

_Количество всех обращений к API в процессе отрисовки_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::operations;
```




<hr>



### variable pFrameBuffer 

```C++
FramebufferPtr SR_GRAPH_NS::PipelineState::pFrameBuffer;
```




<hr>



### variable pRenderStrategy 

```C++
RenderStrategy* SR_GRAPH_NS::PipelineState::pRenderStrategy;
```




<hr>



### variable pShader 

```C++
ShaderPtr SR_GRAPH_NS::PipelineState::pShader;
```




<hr>



### variable shaderId 

```C++
int32_t SR_GRAPH_NS::PipelineState::shaderId;
```




<hr>



### variable transferredCount 

_Количество обращений по передаче данных_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::transferredCount;
```




<hr>



### variable transferredMemory 

_Объем данных, который был передан на видеокарту в процессе отрисовки_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::transferredMemory;
```




<hr>



### variable usedShaders 

```C++
uint32_t SR_GRAPH_NS::PipelineState::usedShaders;
```




<hr>



### variable usedTextures 

```C++
uint32_t SR_GRAPH_NS::PipelineState::usedTextures;
```




<hr>



### variable vertices 

_Количество вершин, которые были отрисованы_ 
```C++
uint32_t SR_GRAPH_NS::PipelineState::vertices;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/PipelineState.h`

