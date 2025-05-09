

# Class SR\_GRAPH\_NS::SortedMeshQueue



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SortedMeshQueue**](classSR__GRAPH__NS_1_1SortedMeshQueue.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_GRAPH\_NS::SortedOpaqueMeshQueue](classSR__GRAPH__NS_1_1SortedOpaqueMeshQueue.md),  [SR\_GRAPH\_NS::SortedTransparentMeshQueue](classSR__GRAPH__NS_1_1SortedTransparentMeshQueue.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; MeshPtr &gt;::const\_iterator | [**ConstIterator**](#typedef-constiterator)  <br> |
| typedef std::vector&lt; MeshPtr &gt;::iterator | [**Iterator**](#typedef-iterator)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](#typedef-meshptr)  <br> |
| typedef std::vector&lt; MeshPtr &gt;::const\_reverse\_iterator | [**ReverseConstIterator**](#typedef-reverseconstiterator)  <br> |
| typedef std::vector&lt; MeshPtr &gt;::reverse\_iterator | [**ReverseIterator**](#typedef-reverseiterator)  <br> |
| typedef [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](#typedef-shaderptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Add**](#function-add) (MeshPtr pMesh) <br> |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD const std::vector&lt; MeshPtr &gt; & | [**GetQueue**](#function-getqueue) () const<br> |
|  bool | [**Remove**](#function-remove) (MeshPtr pMesh) <br> |
|  void | [**SetTarget**](#function-settarget) (const SR\_MATH\_NS::FVector3 & target) <br> |
|  bool | [**Sort**](#function-sort) () <br>_return - the queue order has been changed_  |
|   | [**SortedMeshQueue**](#function-sortedmeshqueue) () <br> |
|  SR\_NODISCARD Iterator | [**begin**](#function-begin-12) () noexcept<br> |
|  SR\_NODISCARD ConstIterator | [**begin**](#function-begin-22) () noexcept const<br> |
|  SR\_NODISCARD bool | [**empty**](#function-empty) () noexcept const<br> |
|  SR\_NODISCARD Iterator | [**end**](#function-end-12) () noexcept<br> |
|  SR\_NODISCARD ConstIterator | [**end**](#function-end-22) () noexcept const<br> |
|   | [**~SortedMeshQueue**](#function-sortedmeshqueue) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  MeshPtr \* | [**m\_data**](#variable-m_data)   = `nullptr`<br> |
|  bool | [**m\_dirty**](#variable-m_dirty)   = `false`<br> |
|  std::vector&lt; MeshPtr &gt; | [**m\_queue**](#variable-m_queue)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_target**](#variable-m_target)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**SortInternal**](#function-sortinternal) (uint32\_t lowestIndex, uint32\_t higherIndex) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef ConstIterator 

```C++
using SR_GRAPH_NS::SortedMeshQueue::ConstIterator =  std::vector<MeshPtr>::const_iterator;
```




<hr>



### typedef Iterator 

```C++
using SR_GRAPH_NS::SortedMeshQueue::Iterator =  std::vector<MeshPtr>::iterator;
```




<hr>



### typedef MeshPtr 

```C++
using SR_GRAPH_NS::SortedMeshQueue::MeshPtr =  SR_GTYPES_NS::Mesh*;
```




<hr>



### typedef ReverseConstIterator 

```C++
using SR_GRAPH_NS::SortedMeshQueue::ReverseConstIterator =  std::vector<MeshPtr>::const_reverse_iterator;
```




<hr>



### typedef ReverseIterator 

```C++
using SR_GRAPH_NS::SortedMeshQueue::ReverseIterator =  std::vector<MeshPtr>::reverse_iterator;
```




<hr>



### typedef ShaderPtr 

```C++
using SR_GRAPH_NS::SortedMeshQueue::ShaderPtr =  SR_GTYPES_NS::Shader*;
```




<hr>
## Public Functions Documentation




### function Add 

```C++
bool SR_GRAPH_NS::SortedMeshQueue::Add (
    MeshPtr pMesh
) 
```




<hr>



### function Clear 

```C++
void SR_GRAPH_NS::SortedMeshQueue::Clear () 
```




<hr>



### function GetQueue 

```C++
inline SR_NODISCARD const std::vector< MeshPtr > & SR_GRAPH_NS::SortedMeshQueue::GetQueue () const
```




<hr>



### function Remove 

```C++
bool SR_GRAPH_NS::SortedMeshQueue::Remove (
    MeshPtr pMesh
) 
```




<hr>



### function SetTarget 

```C++
void SR_GRAPH_NS::SortedMeshQueue::SetTarget (
    const SR_MATH_NS::FVector3 & target
) 
```




<hr>



### function Sort 

_return - the queue order has been changed_ 
```C++
bool SR_GRAPH_NS::SortedMeshQueue::Sort () 
```




<hr>



### function SortedMeshQueue 

```C++
SR_GRAPH_NS::SortedMeshQueue::SortedMeshQueue () 
```




<hr>



### function begin [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::SortedMeshQueue::begin () noexcept
```




<hr>



### function begin [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::SortedMeshQueue::begin () noexcept const
```




<hr>



### function empty 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::SortedMeshQueue::empty () noexcept const
```




<hr>



### function end [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::SortedMeshQueue::end () noexcept
```




<hr>



### function end [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::SortedMeshQueue::end () noexcept const
```




<hr>



### function ~SortedMeshQueue 

```C++
SR_GRAPH_NS::SortedMeshQueue::~SortedMeshQueue () override
```




<hr>
## Protected Attributes Documentation




### variable m\_data 

```C++
MeshPtr* SR_GRAPH_NS::SortedMeshQueue::m_data;
```




<hr>



### variable m\_dirty 

```C++
bool SR_GRAPH_NS::SortedMeshQueue::m_dirty;
```




<hr>



### variable m\_queue 

```C++
std::vector<MeshPtr> SR_GRAPH_NS::SortedMeshQueue::m_queue;
```




<hr>



### variable m\_target 

```C++
SR_MATH_NS::FVector3 SR_GRAPH_NS::SortedMeshQueue::m_target;
```




<hr>
## Protected Functions Documentation




### function SortInternal 

```C++
void SR_GRAPH_NS::SortedMeshQueue::SortInternal (
    uint32_t lowestIndex,
    uint32_t higherIndex
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Render/SortedMeshQueue.h`

