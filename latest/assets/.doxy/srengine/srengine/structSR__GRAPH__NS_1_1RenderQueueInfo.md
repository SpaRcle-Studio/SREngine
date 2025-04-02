

# Struct SR\_GRAPH\_NS::RenderQueueInfo



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) \* | [**pRenderQueue**](#variable-prenderqueue)  <br> |
|  [**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) | [**shaderUseInfo**](#variable-shaderuseinfo)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**RenderQueueInfo**](#function-renderqueueinfo-12) () = default<br> |
|   | [**RenderQueueInfo**](#function-renderqueueinfo-22) ([**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) \* pRenderQueue, const [**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) & shaderUseInfo) <br> |
|  bool | [**operator==**](#function-operator) (const [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) & other) const<br> |




























## Public Attributes Documentation




### variable pRenderQueue 

```C++
RenderQueue* SR_GRAPH_NS::RenderQueueInfo::pRenderQueue;
```




<hr>



### variable shaderUseInfo 

```C++
ShaderUseInfo SR_GRAPH_NS::RenderQueueInfo::shaderUseInfo;
```




<hr>
## Public Functions Documentation




### function RenderQueueInfo [1/2]

```C++
SR_GRAPH_NS::RenderQueueInfo::RenderQueueInfo () = default
```




<hr>



### function RenderQueueInfo [2/2]

```C++
inline SR_GRAPH_NS::RenderQueueInfo::RenderQueueInfo (
    RenderQueue * pRenderQueue,
    const ShaderUseInfo & shaderUseInfo
) 
```




<hr>



### function operator== 

```C++
inline bool SR_GRAPH_NS::RenderQueueInfo::operator== (
    const RenderQueueInfo & other
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Render/RenderQueue.h`

