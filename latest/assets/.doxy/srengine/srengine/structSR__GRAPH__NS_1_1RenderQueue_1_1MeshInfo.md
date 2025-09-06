

# Struct SR\_GRAPH\_NS::RenderQueue::MeshInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) **>** [**MeshInfo**](structSR__GRAPH__NS_1_1RenderQueue_1_1MeshInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**pMesh**](#variable-pmesh)   = `nullptr`<br> |
|  [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**pShader**](#variable-pshader)   = `nullptr`<br> |
|  int64\_t | [**priority**](#variable-priority)   = `0`<br> |
|  QueueStateFlags | [**state**](#variable-state)   = `QUEUE\_STATE\_NOT\_RENDERED`<br> |
|  VBO | [**vbo**](#variable-vbo)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator==**](#function-operator) (const [**MeshInfo**](structSR__GRAPH__NS_1_1RenderQueue_1_1MeshInfo.md) & other) noexcept const<br> |




























## Public Attributes Documentation




### variable pMesh 

```C++
SR_GTYPES_NS::Mesh* SR_GRAPH_NS::RenderQueue::MeshInfo::pMesh;
```




<hr>



### variable pShader 

```C++
SR_GTYPES_NS::Shader* SR_GRAPH_NS::RenderQueue::MeshInfo::pShader;
```




<hr>



### variable priority 

```C++
int64_t SR_GRAPH_NS::RenderQueue::MeshInfo::priority;
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

