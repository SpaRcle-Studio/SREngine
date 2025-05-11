

# Struct SR\_GRAPH\_NS::RenderQueuePredicate



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderQueuePredicate**](structSR__GRAPH__NS_1_1RenderQueuePredicate.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) | [**Element**](#typedef-element)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**operator()**](#function-operator()) (const [**Element**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) & left, const [**Element**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) & right) noexcept const<br> |




























## Public Types Documentation




### typedef Element 

```C++
using SR_GRAPH_NS::RenderQueuePredicate::Element =  RenderQueueInfo;
```




<hr>
## Public Functions Documentation




### function operator() 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::RenderQueuePredicate::operator() (
    const Element & left,
    const Element & right
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderQueue.h`

