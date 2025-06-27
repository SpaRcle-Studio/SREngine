

# Class SR\_HTYPES\_NS::RawMesh



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md)








Inherits the following classes: IResource


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ComputeConvexHull**](#function-computeconvexhull) () <br> |
|  SR\_NODISCARD std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**GetAnimationNames**](#function-getanimationnames) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetAnimationsCount**](#function-getanimationscount) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetAssociatedPath**](#function-getassociatedpath) () override const<br> |
|  SR\_NODISCARD uint32\_t | [**GetBoneIndex**](#function-getboneindex) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetBoneOffset**](#function-getboneoffset) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) &gt; & | [**GetBoneOffsets**](#function-getboneoffsets) () const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetBoneTransform**](#function-getbonetransform-12) (uint32\_t index) const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetBoneTransform**](#function-getbonetransform-22) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD const ska::flat\_hash\_map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), uint32\_t &gt; & | [**GetBones**](#function-getbones) (uint32\_t id) const<br> |
|  SR\_NODISCARD std::string\_view | [**GetGeometryName**](#function-getgeometryname) (uint32\_t id) const<br> |
|  SR\_NODISCARD const [**SR\_HTYPES\_NS::FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md)&lt; uint32\_t &gt; & | [**GetIndices**](#function-getindices) (uint32\_t id) const<br> |
|  SR\_NODISCARD uint32\_t | [**GetIndicesCount**](#function-getindicescount) (uint32\_t id) const<br> |
|  SR\_NODISCARD int32\_t | [**GetMeshId**](#function-getmeshid) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD uint32\_t | [**GetMeshesCount**](#function-getmeshescount) () const<br> |
|  SR\_NODISCARD const ska::flat\_hash\_map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), uint16\_t &gt; & | [**GetOptimizedBones**](#function-getoptimizedbones) () const<br> |
|  SR\_NODISCARD float\_t | [**GetScaleFactor**](#function-getscalefactor) () const<br> |
|  SR\_NODISCARD std::vector&lt; [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) &gt; | [**GetVertices**](#function-getvertices) (uint32\_t id) const<br> |
|  SR\_NODISCARD uint32\_t | [**GetVerticesCount**](#function-getverticescount) (uint32\_t id) const<br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**InitializeResourcePath**](#function-initializeresourcepath) () override const<br> |
|  SR\_NODISCARD bool | [**IsAllowedToRevive**](#function-isallowedtorevive) () override const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* | [**Load**](#function-load-13) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, [**RawMeshParams**](structSR__HTYPES__NS_1_1RawMeshParams.md) params) <br> |
|  [**RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* | [**Load**](#function-load-23) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |






















## Protected Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Load**](#function-load-33) () override<br> |
|  bool | [**Unload**](#function-unload) () override<br> |




## Public Functions Documentation




### function ComputeConvexHull 

```C++
void SR_HTYPES_NS::RawMesh::ComputeConvexHull () 
```




<hr>



### function GetAnimationNames 

```C++
SR_NODISCARD std::vector< SR_UTILS_NS::StringAtom > SR_HTYPES_NS::RawMesh::GetAnimationNames () const
```




<hr>



### function GetAnimationsCount 

```C++
SR_NODISCARD uint32_t SR_HTYPES_NS::RawMesh::GetAnimationsCount () const
```




<hr>



### function GetAssociatedPath 

```C++
SR_NODISCARD SR_UTILS_NS::Path SR_HTYPES_NS::RawMesh::GetAssociatedPath () override const
```




<hr>



### function GetBoneIndex 

```C++
SR_NODISCARD uint32_t SR_HTYPES_NS::RawMesh::GetBoneIndex (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function GetBoneOffset 

```C++
SR_NODISCARD const SR_MATH_NS::Matrix4x4 & SR_HTYPES_NS::RawMesh::GetBoneOffset (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function GetBoneOffsets 

```C++
SR_NODISCARD const std::vector< SR_MATH_NS::Matrix4x4 > & SR_HTYPES_NS::RawMesh::GetBoneOffsets () const
```




<hr>



### function GetBoneTransform [1/2]

```C++
SR_NODISCARD const SR_MATH_NS::Matrix4x4 & SR_HTYPES_NS::RawMesh::GetBoneTransform (
    uint32_t index
) const
```




<hr>



### function GetBoneTransform [2/2]

```C++
SR_NODISCARD const SR_MATH_NS::Matrix4x4 & SR_HTYPES_NS::RawMesh::GetBoneTransform (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function GetBones 

```C++
SR_NODISCARD const ska::flat_hash_map< SR_UTILS_NS::StringAtom , uint32_t > & SR_HTYPES_NS::RawMesh::GetBones (
    uint32_t id
) const
```




<hr>



### function GetGeometryName 

```C++
SR_NODISCARD std::string_view SR_HTYPES_NS::RawMesh::GetGeometryName (
    uint32_t id
) const
```




<hr>



### function GetIndices 

```C++
SR_NODISCARD const SR_HTYPES_NS::FastMemoryArray < uint32_t > & SR_HTYPES_NS::RawMesh::GetIndices (
    uint32_t id
) const
```




<hr>



### function GetIndicesCount 

```C++
SR_NODISCARD uint32_t SR_HTYPES_NS::RawMesh::GetIndicesCount (
    uint32_t id
) const
```




<hr>



### function GetMeshId 

```C++
SR_NODISCARD int32_t SR_HTYPES_NS::RawMesh::GetMeshId (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function GetMeshesCount 

```C++
SR_NODISCARD uint32_t SR_HTYPES_NS::RawMesh::GetMeshesCount () const
```




<hr>



### function GetOptimizedBones 

```C++
SR_NODISCARD const ska::flat_hash_map< SR_UTILS_NS::StringAtom , uint16_t > & SR_HTYPES_NS::RawMesh::GetOptimizedBones () const
```




<hr>



### function GetScaleFactor 

```C++
SR_NODISCARD float_t SR_HTYPES_NS::RawMesh::GetScaleFactor () const
```




<hr>



### function GetVertices 

```C++
SR_NODISCARD std::vector< SR_UTILS_NS::Vertex > SR_HTYPES_NS::RawMesh::GetVertices (
    uint32_t id
) const
```




<hr>



### function GetVerticesCount 

```C++
SR_NODISCARD uint32_t SR_HTYPES_NS::RawMesh::GetVerticesCount (
    uint32_t id
) const
```




<hr>



### function InitializeResourcePath 

```C++
SR_UTILS_NS::Path SR_HTYPES_NS::RawMesh::InitializeResourcePath () override const
```




<hr>



### function IsAllowedToRevive 

```C++
SR_NODISCARD bool SR_HTYPES_NS::RawMesh::IsAllowedToRevive () override const
```




<hr>
## Public Static Functions Documentation




### function Load [1/3]

```C++
static RawMesh * SR_HTYPES_NS::RawMesh::Load (
    const SR_UTILS_NS::Path & path,
    RawMeshParams params
) 
```




<hr>



### function Load [2/3]

```C++
static RawMesh * SR_HTYPES_NS::RawMesh::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>
## Protected Functions Documentation




### function Load [3/3]

```C++
bool SR_HTYPES_NS::RawMesh::Load () override
```




<hr>



### function Unload 

```C++
bool SR_HTYPES_NS::RawMesh::Unload () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/RawMesh.h`

