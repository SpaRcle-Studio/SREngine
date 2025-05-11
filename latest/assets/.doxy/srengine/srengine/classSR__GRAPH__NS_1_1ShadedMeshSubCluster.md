

# Class SR\_GRAPH\_NS::ShadedMeshSubCluster



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef MeshGroups::const\_iterator | [**ConstIterator**](#typedef-constiterator)  <br> |
| typedef MeshGroups::iterator | [**Iterator**](#typedef-iterator)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool SR\_FASTCALL | [**Empty**](#function-empty) () noexcept const<br> |
|  SR\_NODISCARD SR\_SRSL\_NS::ShaderType | [**GetShaderType**](#function-getshadertype) () noexcept const<br> |
|  void | [**OnResourceReloaded**](#function-onresourcereloaded) ([**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|   | [**ShadedMeshSubCluster**](#function-shadedmeshsubcluster-13) () = default<br> |
|   | [**ShadedMeshSubCluster**](#function-shadedmeshsubcluster-23) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |
|   | [**ShadedMeshSubCluster**](#function-shadedmeshsubcluster-33) ([**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) && ref) noexcept<br> |
|  SR\_NODISCARD Iterator | [**begin**](#function-begin-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**begin**](#function-begin-22) () const<br> |
|  SR\_NODISCARD Iterator | [**end**](#function-end-12) () <br> |
|  SR\_NODISCARD ConstIterator | [**end**](#function-end-22) () const<br> |
|  Iterator | [**erase**](#function-erase) (const Iterator & iterator) <br> |
|  [**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) & | [**operator=**](#function-operator) ([**ShadedMeshSubCluster**](classSR__GRAPH__NS_1_1ShadedMeshSubCluster.md) && ref) noexcept<br> |
|   | [**~ShadedMeshSubCluster**](#function-shadedmeshsubcluster) () override<br> |


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
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef ConstIterator 

```C++
using SR_GRAPH_NS::ShadedMeshSubCluster::ConstIterator =  MeshGroups::const_iterator;
```




<hr>



### typedef Iterator 

```C++
using SR_GRAPH_NS::ShadedMeshSubCluster::Iterator =  MeshGroups::iterator;
```




<hr>



### typedef Super 

```C++
using SR_GRAPH_NS::ShadedMeshSubCluster::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Public Functions Documentation




### function Empty 

```C++
SR_NODISCARD bool SR_FASTCALL SR_GRAPH_NS::ShadedMeshSubCluster::Empty () noexcept const
```




<hr>



### function GetShaderType 

```C++
SR_NODISCARD SR_SRSL_NS::ShaderType SR_GRAPH_NS::ShadedMeshSubCluster::GetShaderType () noexcept const
```




<hr>



### function OnResourceReloaded 

```C++
void SR_GRAPH_NS::ShadedMeshSubCluster::OnResourceReloaded (
    SR_UTILS_NS::IResource * pResource
) 
```




<hr>



### function ShadedMeshSubCluster [1/3]

```C++
SR_GRAPH_NS::ShadedMeshSubCluster::ShadedMeshSubCluster () = default
```




<hr>



### function ShadedMeshSubCluster [2/3]

```C++
explicit SR_GRAPH_NS::ShadedMeshSubCluster::ShadedMeshSubCluster (
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>



### function ShadedMeshSubCluster [3/3]

```C++
inline SR_GRAPH_NS::ShadedMeshSubCluster::ShadedMeshSubCluster (
    ShadedMeshSubCluster && ref
) noexcept
```




<hr>



### function begin [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::ShadedMeshSubCluster::begin () 
```




<hr>



### function begin [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::ShadedMeshSubCluster::begin () const
```




<hr>



### function end [1/2]

```C++
inline SR_NODISCARD Iterator SR_GRAPH_NS::ShadedMeshSubCluster::end () 
```




<hr>



### function end [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_GRAPH_NS::ShadedMeshSubCluster::end () const
```




<hr>



### function erase 

```C++
inline Iterator SR_GRAPH_NS::ShadedMeshSubCluster::erase (
    const Iterator & iterator
) 
```




<hr>



### function operator= 

```C++
inline ShadedMeshSubCluster & SR_GRAPH_NS::ShadedMeshSubCluster::operator= (
    ShadedMeshSubCluster && ref
) noexcept
```




<hr>



### function ~ShadedMeshSubCluster 

```C++
SR_GRAPH_NS::ShadedMeshSubCluster::~ShadedMeshSubCluster () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/MeshCluster.h`

