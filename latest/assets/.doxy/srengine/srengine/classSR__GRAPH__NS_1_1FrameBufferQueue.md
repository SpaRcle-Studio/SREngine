

# Class SR\_GRAPH\_NS::FrameBufferQueue



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FrameBufferQueue**](classSR__GRAPH__NS_1_1FrameBufferQueue.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddFrameBuffer**](#function-addframebuffer) (FrameBuffer pFrameBuffer, uint32\_t layer) <br> |
|  void | [**AddQueue**](#function-addqueue) (FrameBuffer pFrameBuffer, uint32\_t queueIndex) <br> |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains-12) (FrameBuffer pFrameBuffer) <br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains-22) (FrameBuffer pFrameBuffer, uint32\_t layer) <br> |
|  SR\_NODISCARD const std::vector&lt; std::vector&lt; FrameBuffer &gt; &gt; & | [**GetQueues**](#function-getqueues) () const<br> |
|  SR\_NODISCARD bool | [**IsAllowMultiFrameBuffers**](#function-isallowmultiframebuffers) () const<br> |




























## Public Functions Documentation




### function AddFrameBuffer 

```C++
void SR_GRAPH_NS::FrameBufferQueue::AddFrameBuffer (
    FrameBuffer pFrameBuffer,
    uint32_t layer
) 
```




<hr>



### function AddQueue 

```C++
void SR_GRAPH_NS::FrameBufferQueue::AddQueue (
    FrameBuffer pFrameBuffer,
    uint32_t queueIndex
) 
```




<hr>



### function Clear 

```C++
void SR_GRAPH_NS::FrameBufferQueue::Clear () 
```




<hr>



### function Contains [1/2]

```C++
SR_NODISCARD bool SR_GRAPH_NS::FrameBufferQueue::Contains (
    FrameBuffer pFrameBuffer
) 
```




<hr>



### function Contains [2/2]

```C++
SR_NODISCARD bool SR_GRAPH_NS::FrameBufferQueue::Contains (
    FrameBuffer pFrameBuffer,
    uint32_t layer
) 
```




<hr>



### function GetQueues 

```C++
SR_NODISCARD const std::vector< std::vector< FrameBuffer > > & SR_GRAPH_NS::FrameBufferQueue::GetQueues () const
```




<hr>



### function IsAllowMultiFrameBuffers 

```C++
SR_NODISCARD bool SR_GRAPH_NS::FrameBufferQueue::IsAllowMultiFrameBuffers () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pipeline/FrameBufferQueue.h`

