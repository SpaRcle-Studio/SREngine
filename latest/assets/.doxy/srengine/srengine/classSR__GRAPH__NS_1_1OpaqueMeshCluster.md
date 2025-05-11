

# Class SR\_GRAPH\_NS::OpaqueMeshCluster



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**OpaqueMeshCluster**](classSR__GRAPH__NS_1_1OpaqueMeshCluster.md)








Inherits the following classes: [SR\_GRAPH\_NS::MeshCluster](classSR__GRAPH__NS_1_1MeshCluster.md)
















## Public Types inherited from SR_GRAPH_NS::MeshCluster

See [SR\_GRAPH\_NS::MeshCluster](classSR__GRAPH__NS_1_1MeshCluster.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(MeshPtr)&gt; | [**ClusterCallback**](classSR__GRAPH__NS_1_1MeshCluster.md#typedef-clustercallback)  <br> |
| typedef ska::flat\_hash\_map&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \*, [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) &gt;::const\_iterator | [**ConstIterator**](classSR__GRAPH__NS_1_1MeshCluster.md#typedef-constiterator)  <br> |
| typedef ska::flat\_hash\_map&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \*, [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) &gt;::iterator | [**Iterator**](classSR__GRAPH__NS_1_1MeshCluster.md#typedef-iterator)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](classSR__GRAPH__NS_1_1MeshCluster.md#typedef-meshptr)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**OpaqueMeshCluster**](#function-opaquemeshcluster) ([**TransparentMeshCluster**](classSR__GRAPH__NS_1_1TransparentMeshCluster.md) \* pTransparentCluster) <br> |
|   | [**~OpaqueMeshCluster**](#function-opaquemeshcluster) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::MeshCluster

See [SR\_GRAPH\_NS::MeshCluster](classSR__GRAPH__NS_1_1MeshCluster.md)

| Type | Name |
| ---: | :--- |
|  bool SR\_FASTCALL | [**Add**](classSR__GRAPH__NS_1_1MeshCluster.md#function-add) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* mesh) noexcept<br> |
|  SR\_NODISCARD bool SR\_FASTCALL | [**Empty**](classSR__GRAPH__NS_1_1MeshCluster.md#function-empty) () noexcept const<br> |
|   | [**MeshCluster**](classSR__GRAPH__NS_1_1MeshCluster.md#function-meshcluster) () <br> |
|  void | [**OnResourceReloaded**](classSR__GRAPH__NS_1_1MeshCluster.md#function-onresourcereloaded) ([**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  bool | [**Update**](classSR__GRAPH__NS_1_1MeshCluster.md#function-update) () <br> |
|  SR\_NODISCARD Iterator | [**begin**](classSR__GRAPH__NS_1_1MeshCluster.md#function-begin-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**begin**](classSR__GRAPH__NS_1_1MeshCluster.md#function-begin-22) () const<br> |
|  SR\_NODISCARD Iterator | [**end**](classSR__GRAPH__NS_1_1MeshCluster.md#function-end-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**end**](classSR__GRAPH__NS_1_1MeshCluster.md#function-end-22) () const<br> |
|  Iterator | [**erase**](classSR__GRAPH__NS_1_1MeshCluster.md#function-erase) (const Iterator & iterator) <br> |
|   | [**~MeshCluster**](classSR__GRAPH__NS_1_1MeshCluster.md#function-meshcluster) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






















## Protected Attributes inherited from SR_GRAPH_NS::MeshCluster

See [SR\_GRAPH\_NS::MeshCluster](classSR__GRAPH__NS_1_1MeshCluster.md)

| Type | Name |
| ---: | :--- |
|  ska::flat\_hash\_map&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \*, [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) &gt; | [**m\_subClusters**](classSR__GRAPH__NS_1_1MeshCluster.md#variable-m_subclusters)  <br> |
















































## Protected Functions inherited from SR_GRAPH_NS::MeshCluster

See [SR\_GRAPH\_NS::MeshCluster](classSR__GRAPH__NS_1_1MeshCluster.md)

| Type | Name |
| ---: | :--- |
| virtual bool SR\_FASTCALL | [**ChangeCluster**](classSR__GRAPH__NS_1_1MeshCluster.md#function-changecluster) (MeshPtr pMesh) <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function OpaqueMeshCluster 

```C++
inline explicit SR_GRAPH_NS::OpaqueMeshCluster::OpaqueMeshCluster (
    TransparentMeshCluster * pTransparentCluster
) 
```




<hr>



### function ~OpaqueMeshCluster 

```C++
SR_GRAPH_NS::OpaqueMeshCluster::~OpaqueMeshCluster () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/MeshCluster.h`

