

# Struct SR\_GRAPH\_NS::RenderQueueInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**dirtyUniformsFrames**](#variable-dirtyuniformsframes)  <br> |
|  bool | [**inUpdateQueue**](#variable-inupdatequeue)   = `false`<br> |
|  [**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) \* | [**pRenderQueue**](#variable-prenderqueue)  <br> |
|  [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**pShader**](#variable-pshader)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator==**](#function-operator) (const [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) & other) const<br> |




























## Public Attributes Documentation




### variable dirtyUniformsFrames 

```C++
bool SR_GRAPH_NS::RenderQueueInfo::dirtyUniformsFrames[3];
```




<hr>



### variable inUpdateQueue 

```C++
bool SR_GRAPH_NS::RenderQueueInfo::inUpdateQueue;
```




<hr>



### variable pRenderQueue 

```C++
RenderQueue* SR_GRAPH_NS::RenderQueueInfo::pRenderQueue;
```




<hr>



### variable pShader 

```C++
SR_GTYPES_NS::Shader* SR_GRAPH_NS::RenderQueueInfo::pShader;
```




<hr>
## Public Functions Documentation




### function operator== 

```C++
inline bool SR_GRAPH_NS::RenderQueueInfo::operator== (
    const RenderQueueInfo & other
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderQueue.h`

