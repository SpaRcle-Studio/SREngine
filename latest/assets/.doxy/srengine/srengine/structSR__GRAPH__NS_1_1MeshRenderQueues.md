

# Struct SR\_GRAPH\_NS::MeshRenderQueues



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**MeshRenderQueues**](structSR__GRAPH__NS_1_1MeshRenderQueues.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  uint8\_t | [**count**](#variable-count)   = `0`<br> |
|  uint8\_t | [**maxCount**](#variable-maxcount)   = `0`<br> |
|  [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) | [**queues**](#variable-queues)  <br> |


## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr size\_t | [**MaxQueues**](#variable-maxqueues)   = `64`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) \* | [**Add**](#function-add) ([**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) \* pQueue) <br> |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) \* | [**Find**](#function-find) ([**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) \* pQueue) <br> |
|  [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) | [**Remove**](#function-remove) ([**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) \* pQueue) <br> |
|  SR\_NODISCARD [**RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md) \* | [**data**](#function-data) () <br> |
|  SR\_NODISCARD size\_t | [**size**](#function-size) () const<br> |




























## Public Attributes Documentation




### variable count 

```C++
uint8_t SR_GRAPH_NS::MeshRenderQueues::count;
```




<hr>



### variable maxCount 

```C++
uint8_t SR_GRAPH_NS::MeshRenderQueues::maxCount;
```




<hr>



### variable queues 

```C++
RenderQueueInfo SR_GRAPH_NS::MeshRenderQueues::queues[MaxQueues];
```




<hr>
## Public Static Attributes Documentation




### variable MaxQueues 

```C++
constexpr size_t SR_GRAPH_NS::MeshRenderQueues::MaxQueues;
```




<hr>
## Public Functions Documentation




### function Add 

```C++
inline SR_NODISCARD RenderQueueInfo * SR_GRAPH_NS::MeshRenderQueues::Add (
    RenderQueue * pQueue
) 
```




<hr>



### function Clear 

```C++
inline void SR_GRAPH_NS::MeshRenderQueues::Clear () 
```




<hr>



### function Find 

```C++
inline SR_NODISCARD RenderQueueInfo * SR_GRAPH_NS::MeshRenderQueues::Find (
    RenderQueue * pQueue
) 
```




<hr>



### function Remove 

```C++
inline RenderQueueInfo SR_GRAPH_NS::MeshRenderQueues::Remove (
    RenderQueue * pQueue
) 
```




<hr>



### function data 

```C++
inline SR_NODISCARD RenderQueueInfo * SR_GRAPH_NS::MeshRenderQueues::data () 
```




<hr>



### function size 

```C++
inline SR_NODISCARD size_t SR_GRAPH_NS::MeshRenderQueues::size () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderQueue.h`

