

# Class SR\_GRAPH\_NS::FlatMeshCluster



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FlatMeshCluster**](classSR__GRAPH__NS_1_1FlatMeshCluster.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; MeshPtr &gt;::const\_iterator | [**ConstIterator**](#typedef-constiterator)  <br> |
| typedef std::vector&lt; MeshPtr &gt;::iterator | [**Iterator**](#typedef-iterator)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](#typedef-meshptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Add**](#function-add) (const MeshPtr & pMesh) <br> |
|  SR\_NODISCARD bool SR\_FASTCALL | [**Empty**](#function-empty) () noexcept const<br> |
|   | [**FlatMeshCluster**](#function-flatmeshcluster) ([**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* pRenderScene) <br> |
|  void | [**MarkDirty**](#function-markdirty) () <br> |
|  void | [**OnResourceReloaded**](#function-onresourcereloaded) ([**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  void | [**Randomize**](#function-randomize) () <br> |
|  void | [**Remove**](#function-remove) (const MeshPtr & pMesh) <br> |
|  void | [**Sort**](#function-sort) () <br> |
|  bool | [**Update**](#function-update) () <br> |
|  SR\_NODISCARD Iterator | [**begin**](#function-begin-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**begin**](#function-begin-22) () const<br> |
|  SR\_NODISCARD Iterator | [**end**](#function-end-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**end**](#function-end-22) () const<br> |
|   | [**~FlatMeshCluster**](#function-flatmeshcluster) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Types Documentation




### typedef ConstIterator 

```C++
using SR_GRAPH_NS::FlatMeshCluster::ConstIterator =  std::vector<MeshPtr>::const_iterator;
```




<hr>



### typedef Iterator 

```C++
using SR_GRAPH_NS::FlatMeshCluster::Iterator =  std::vector<MeshPtr>::iterator;
```




<hr>



### typedef MeshPtr 

```C++
using SR_GRAPH_NS::FlatMeshCluster::MeshPtr =  SR_GTYPES_NS::Mesh*;
```




<hr>
## Public Functions Documentation




### function Add 

```C++
void SR_GRAPH_NS::FlatMeshCluster::Add (
    const MeshPtr & pMesh
) 
```




<hr>



### function Empty 

```C++
inline SR_NODISCARD bool SR_FASTCALL SR_GRAPH_NS::FlatMeshCluster::Empty () noexcept const
```




<hr>



### function FlatMeshCluster 

```C++
SR_GRAPH_NS::FlatMeshCluster::FlatMeshCluster (
    RenderScene * pRenderScene
) 
```




<hr>



### function MarkDirty 

```C++
void SR_GRAPH_NS::FlatMeshCluster::MarkDirty () 
```




<hr>



### function OnResourceReloaded 

```C++
void SR_GRAPH_NS::FlatMeshCluster::OnResourceReloaded (
    SR_UTILS_NS::IResource * pResource
) 
```




<hr>



### function Randomize 

```C++
void SR_GRAPH_NS::FlatMeshCluster::Randomize () 
```




<hr>



### function Remove 

```C++
void SR_GRAPH_NS::FlatMeshCluster::Remove (
    const MeshPtr & pMesh
) 
```




<hr>



### function Sort 

```C++
void SR_GRAPH_NS::FlatMeshCluster::Sort () 
```




<hr>



### function Update 

```C++
bool SR_GRAPH_NS::FlatMeshCluster::Update () 
```




<hr>



### function begin [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::FlatMeshCluster::begin () 
```




<hr>



### function begin [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::FlatMeshCluster::begin () const
```




<hr>



### function end [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::FlatMeshCluster::end () 
```




<hr>



### function end [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::FlatMeshCluster::end () const
```




<hr>



### function ~FlatMeshCluster 

```C++
SR_GRAPH_NS::FlatMeshCluster::~FlatMeshCluster () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Render/FlatCluster.h`

