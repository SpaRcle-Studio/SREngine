

# Class SR\_HTYPES\_NS::IRawMeshHolder



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**IRawMeshHolder**](classSR__HTYPES__NS_1_1IRawMeshHolder.md)



_Этот класс предоставляет удобный интерфейс для работы с RwMesh._ 

* `#include <IRawMeshHolder.h>`





Inherited by the following classes: [SR\_ANIMATIONS\_NS::Skeleton](classSR__ANIMATIONS__NS_1_1Skeleton.md),  [SR\_GTYPES\_NS::DebugWireframeMesh](classSR__GTYPES__NS_1_1DebugWireframeMesh.md),  [SR\_GTYPES\_NS::Mesh3D](classSR__GTYPES__NS_1_1Mesh3D.md),  [SR\_GTYPES\_NS::SkinnedMesh](classSR__GTYPES__NS_1_1SkinnedMesh.md),  [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef int32\_t | [**MeshIndex**](#typedef-meshindex)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) &gt; | [**RawMeshPtr**](#typedef-rawmeshptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string\_view | [**GetGeometryName**](#function-getgeometryname) () noexcept const<br> |
|  SR\_NODISCARD MeshIndex | [**GetMeshId**](#function-getmeshid) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetMeshPath**](#function-getmeshpath) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**GetMeshStringPath**](#function-getmeshstringpath) () noexcept const<br> |
|  SR\_NODISCARD const RawMeshPtr & | [**GetRawMesh**](#function-getrawmesh) () noexcept const<br> |
|  SR\_NODISCARD std::vector&lt; [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) &gt; | [**GetVertices**](#function-getvertices) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsValidMeshId**](#function-isvalidmeshid) () noexcept const<br> |
| virtual void | [**OnRawMeshChanged**](#function-onrawmeshchanged) () <br> |
|  void | [**SetMeshId**](#function-setmeshid) (MeshIndex meshIndex, bool forceReload=false) <br> |
|  void | [**SetRawMesh**](#function-setrawmesh-12) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetRawMesh**](#function-setrawmesh-22) (RawMeshPtr pRawMesh) <br> |
| virtual  | [**~IRawMeshHolder**](#function-irawmeshholder) () <br> |




























## Public Types Documentation




### typedef MeshIndex 

```C++
using SR_HTYPES_NS::IRawMeshHolder::MeshIndex =  int32_t;
```




<hr>



### typedef RawMeshPtr 

```C++
using SR_HTYPES_NS::IRawMeshHolder::RawMeshPtr =  SR_HTYPES_NS::SharedPtr<SR_HTYPES_NS::RawMesh>;
```




<hr>
## Public Functions Documentation




### function GetGeometryName 

```C++
SR_NODISCARD std::string_view SR_HTYPES_NS::IRawMeshHolder::GetGeometryName () noexcept const
```




<hr>



### function GetMeshId 

```C++
inline SR_NODISCARD MeshIndex SR_HTYPES_NS::IRawMeshHolder::GetMeshId () noexcept const
```




<hr>



### function GetMeshPath 

```C++
SR_NODISCARD SR_UTILS_NS::Path SR_HTYPES_NS::IRawMeshHolder::GetMeshPath () noexcept const
```




<hr>



### function GetMeshStringPath 

```C++
SR_NODISCARD std::string SR_HTYPES_NS::IRawMeshHolder::GetMeshStringPath () noexcept const
```




<hr>



### function GetRawMesh 

```C++
inline SR_NODISCARD const RawMeshPtr & SR_HTYPES_NS::IRawMeshHolder::GetRawMesh () noexcept const
```




<hr>



### function GetVertices 

```C++
SR_NODISCARD std::vector< SR_UTILS_NS::Vertex > SR_HTYPES_NS::IRawMeshHolder::GetVertices () noexcept const
```




<hr>



### function IsValidMeshId 

```C++
SR_NODISCARD bool SR_HTYPES_NS::IRawMeshHolder::IsValidMeshId () noexcept const
```




<hr>



### function OnRawMeshChanged 

```C++
inline virtual void SR_HTYPES_NS::IRawMeshHolder::OnRawMeshChanged () 
```




<hr>



### function SetMeshId 

```C++
void SR_HTYPES_NS::IRawMeshHolder::SetMeshId (
    MeshIndex meshIndex,
    bool forceReload=false
) 
```




<hr>



### function SetRawMesh [1/2]

```C++
void SR_HTYPES_NS::IRawMeshHolder::SetRawMesh (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function SetRawMesh [2/2]

```C++
void SR_HTYPES_NS::IRawMeshHolder::SetRawMesh (
    RawMeshPtr pRawMesh
) 
```




<hr>



### function ~IRawMeshHolder 

```C++
virtual SR_HTYPES_NS::IRawMeshHolder::~IRawMeshHolder () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/IRawMeshHolder.h`

