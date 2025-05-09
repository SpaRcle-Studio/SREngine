

# Class SR\_GRAPH\_NS::MeshCluster



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**MeshCluster**](classSR__GRAPH__NS_1_1MeshCluster.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_GRAPH\_NS::DebugMeshCluster](classSR__GRAPH__NS_1_1DebugMeshCluster.md),  [SR\_GRAPH\_NS::OpaqueMeshCluster](classSR__GRAPH__NS_1_1OpaqueMeshCluster.md),  [SR\_GRAPH\_NS::TransparentMeshCluster](classSR__GRAPH__NS_1_1TransparentMeshCluster.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(MeshPtr)&gt; | [**ClusterCallback**](#typedef-clustercallback)  <br> |
| typedef ska::flat\_hash\_map&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \*, [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) &gt;::const\_iterator | [**ConstIterator**](#typedef-constiterator)  <br> |
| typedef ska::flat\_hash\_map&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \*, [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) &gt;::iterator | [**Iterator**](#typedef-iterator)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](#typedef-meshptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool SR\_FASTCALL | [**Add**](#function-add) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* mesh) noexcept<br> |
|  SR\_NODISCARD bool SR\_FASTCALL | [**Empty**](#function-empty) () noexcept const<br> |
|   | [**MeshCluster**](#function-meshcluster) () <br> |
|  void | [**OnResourceReloaded**](#function-onresourcereloaded) ([**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  bool | [**Update**](#function-update) () <br> |
|  SR\_NODISCARD Iterator | [**begin**](#function-begin-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**begin**](#function-begin-22) () const<br> |
|  SR\_NODISCARD Iterator | [**end**](#function-end-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**end**](#function-end-22) () const<br> |
|  Iterator | [**erase**](#function-erase) (const Iterator & iterator) <br> |
|   | [**~MeshCluster**](#function-meshcluster) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  ska::flat\_hash\_map&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \*, [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) &gt; | [**m\_subClusters**](#variable-m_subclusters)  <br> |
































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual bool SR\_FASTCALL | [**ChangeCluster**](#function-changecluster) (MeshPtr pMesh) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef ClusterCallback 

```C++
using SR_GRAPH_NS::MeshCluster::ClusterCallback =  SR_HTYPES_NS::Function<void(MeshPtr)>;
```




<hr>



### typedef ConstIterator 

```C++
using SR_GRAPH_NS::MeshCluster::ConstIterator =  ska::flat_hash_map<SR_GTYPES_NS::Shader*, ShadedMeshSubCluster>::const_iterator;
```




<hr>



### typedef Iterator 

```C++
using SR_GRAPH_NS::MeshCluster::Iterator =  ska::flat_hash_map<SR_GTYPES_NS::Shader*, ShadedMeshSubCluster>::iterator;
```




<hr>



### typedef MeshPtr 

```C++
using SR_GRAPH_NS::MeshCluster::MeshPtr =  SR_GTYPES_NS::Mesh*;
```




<hr>
## Public Functions Documentation




### function Add 

```C++
bool SR_FASTCALL SR_GRAPH_NS::MeshCluster::Add (
    SR_GTYPES_NS::Mesh * mesh
) noexcept
```




<hr>



### function Empty 

```C++
SR_NODISCARD bool SR_FASTCALL SR_GRAPH_NS::MeshCluster::Empty () noexcept const
```




<hr>



### function MeshCluster 

```C++
SR_GRAPH_NS::MeshCluster::MeshCluster () 
```




<hr>



### function OnResourceReloaded 

```C++
void SR_GRAPH_NS::MeshCluster::OnResourceReloaded (
    SR_UTILS_NS::IResource * pResource
) 
```




<hr>



### function Update 

```C++
bool SR_GRAPH_NS::MeshCluster::Update () 
```




<hr>



### function begin [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::MeshCluster::begin () 
```




<hr>



### function begin [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::MeshCluster::begin () const
```




<hr>



### function end [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::MeshCluster::end () 
```




<hr>



### function end [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::MeshCluster::end () const
```




<hr>



### function erase 

```C++
inline Iterator SR_GRAPH_NS::MeshCluster::erase (
    const Iterator & iterator
) 
```




<hr>



### function ~MeshCluster 

```C++
inline SR_GRAPH_NS::MeshCluster::~MeshCluster () override
```




<hr>
## Protected Attributes Documentation




### variable m\_subClusters 

```C++
ska::flat_hash_map<SR_GTYPES_NS::Shader*, ShadedMeshSubCluster> SR_GRAPH_NS::MeshCluster::m_subClusters;
```




<hr>
## Protected Functions Documentation




### function ChangeCluster 

```C++
inline virtual bool SR_FASTCALL SR_GRAPH_NS::MeshCluster::ChangeCluster (
    MeshPtr pMesh
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Render/MeshCluster.h`

