

# Class SR\_GRAPH\_NS::SortedOpaqueMeshQueue



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**SortedOpaqueMeshQueue**](classSR__GRAPH__NS_1_1SortedOpaqueMeshQueue.md)








Inherits the following classes: [SR\_GRAPH\_NS::SortedMeshQueue](classSR__GRAPH__NS_1_1SortedMeshQueue.md)
















## Public Types inherited from SR_GRAPH_NS::SortedMeshQueue

See [SR\_GRAPH\_NS::SortedMeshQueue](classSR__GRAPH__NS_1_1SortedMeshQueue.md)

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; MeshPtr &gt;::const\_iterator | [**ConstIterator**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#typedef-constiterator)  <br> |
| typedef std::vector&lt; MeshPtr &gt;::iterator | [**Iterator**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#typedef-iterator)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#typedef-meshptr)  <br> |
| typedef std::vector&lt; MeshPtr &gt;::const\_reverse\_iterator | [**ReverseConstIterator**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#typedef-reverseconstiterator)  <br> |
| typedef std::vector&lt; MeshPtr &gt;::reverse\_iterator | [**ReverseIterator**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#typedef-reverseiterator)  <br> |
| typedef [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#typedef-shaderptr)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**~SortedOpaqueMeshQueue**](#function-sortedopaquemeshqueue) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::SortedMeshQueue

See [SR\_GRAPH\_NS::SortedMeshQueue](classSR__GRAPH__NS_1_1SortedMeshQueue.md)

| Type | Name |
| ---: | :--- |
|  bool | [**Add**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-add) (MeshPtr pMesh) <br> |
|  void | [**Clear**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-clear) () <br> |
|  SR\_NODISCARD const std::vector&lt; MeshPtr &gt; & | [**GetQueue**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-getqueue) () const<br> |
|  bool | [**Remove**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-remove) (MeshPtr pMesh) <br> |
|  void | [**SetTarget**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-settarget) (const SR\_MATH\_NS::FVector3 & target) <br> |
|  bool | [**Sort**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-sort) () <br>_return - the queue order has been changed_  |
|   | [**SortedMeshQueue**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-sortedmeshqueue) () <br> |
|  SR\_NODISCARD Iterator | [**begin**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-begin-12) () noexcept<br> |
|  SR\_NODISCARD ConstIterator | [**begin**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-begin-22) () noexcept const<br> |
|  SR\_NODISCARD bool | [**empty**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-empty) () noexcept const<br> |
|  SR\_NODISCARD Iterator | [**end**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-end-12) () noexcept<br> |
|  SR\_NODISCARD ConstIterator | [**end**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-end-22) () noexcept const<br> |
|   | [**~SortedMeshQueue**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-sortedmeshqueue) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






















## Protected Attributes inherited from SR_GRAPH_NS::SortedMeshQueue

See [SR\_GRAPH\_NS::SortedMeshQueue](classSR__GRAPH__NS_1_1SortedMeshQueue.md)

| Type | Name |
| ---: | :--- |
|  MeshPtr \* | [**m\_data**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#variable-m_data)   = `nullptr`<br> |
|  bool | [**m\_dirty**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#variable-m_dirty)   = `false`<br> |
|  std::vector&lt; MeshPtr &gt; | [**m\_queue**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#variable-m_queue)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_target**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#variable-m_target)  <br> |
















































## Protected Functions inherited from SR_GRAPH_NS::SortedMeshQueue

See [SR\_GRAPH\_NS::SortedMeshQueue](classSR__GRAPH__NS_1_1SortedMeshQueue.md)

| Type | Name |
| ---: | :--- |
|  void | [**SortInternal**](classSR__GRAPH__NS_1_1SortedMeshQueue.md#function-sortinternal) (uint32\_t lowestIndex, uint32\_t higherIndex) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function ~SortedOpaqueMeshQueue 

```C++
SR_GRAPH_NS::SortedOpaqueMeshQueue::~SortedOpaqueMeshQueue () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Render/SortedMeshQueue.h`

