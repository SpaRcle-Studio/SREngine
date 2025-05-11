

# Struct SR\_GRAPH\_NS::RenderQueue::MeshInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) **>** [**MeshInfo**](structSR__GRAPH__NS_1_1RenderQueue_1_1MeshInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**hasVBO**](#variable-hasvbo)   = `false`<br> |
|  MeshPtr | [**pMesh**](#variable-pmesh)   = `nullptr`<br> |
|  int64\_t | [**priority**](#variable-priority)   = `0`<br> |
|  [**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) | [**shaderUseInfo**](#variable-shaderuseinfo)   = `{}`<br> |
|  QueueStateFlags | [**state**](#variable-state)   = `QUEUE\_STATE\_ERROR`<br> |
|  VBO | [**vbo**](#variable-vbo)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator==**](#function-operator) (const [**MeshInfo**](structSR__GRAPH__NS_1_1RenderQueue_1_1MeshInfo.md) & other) noexcept const<br> |




























## Public Attributes Documentation




### variable hasVBO 

```C++
bool SR_GRAPH_NS::RenderQueue::MeshInfo::hasVBO;
```




<hr>



### variable pMesh 

```C++
MeshPtr SR_GRAPH_NS::RenderQueue::MeshInfo::pMesh;
```




<hr>



### variable priority 

```C++
int64_t SR_GRAPH_NS::RenderQueue::MeshInfo::priority;
```




<hr>



### variable shaderUseInfo 

```C++
ShaderUseInfo SR_GRAPH_NS::RenderQueue::MeshInfo::shaderUseInfo;
```




<hr>



### variable state 

```C++
QueueStateFlags SR_GRAPH_NS::RenderQueue::MeshInfo::state;
```




<hr>



### variable vbo 

```C++
VBO SR_GRAPH_NS::RenderQueue::MeshInfo::vbo;
```




<hr>
## Public Functions Documentation




### function operator== 

```C++
inline bool SR_GRAPH_NS::RenderQueue::MeshInfo::operator== (
    const MeshInfo & other
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderQueue.h`

