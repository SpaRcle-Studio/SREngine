

# Struct SR\_GRAPH\_NS::Vertices::SkinnedMeshVertex



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Vertices**](namespaceSR__GRAPH__NS_1_1Vertices.md) **>** [**SkinnedMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SkinnedMeshVertex.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  glm::vec3 | [**bitang**](#variable-bitang)  <br> |
|  glm::vec3 | [**norm**](#variable-norm)  <br> |
|  glm::vec3 | [**pos**](#variable-pos)  <br> |
|  glm::vec3 | [**tang**](#variable-tang)  <br> |
|  glm::vec2 | [**uv**](#variable-uv)  <br> |
|  glm::vec2 | [**weights**](#variable-weights)  <br>_x - bone id, y - weight_  |
|  uint32\_t | [**weightsCount**](#variable-weightscount)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  bool | [**operator==**](#function-operator) (const [**SkinnedMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SkinnedMeshVertex.md) & other) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_FORCE\_INLINE std::vector&lt; std::pair&lt; Attribute, size\_t &gt; &gt; | [**GetAttributes**](#function-getattributes) (bool asTypes) <br> |
|  SR\_FORCE\_INLINE SR\_VERTEX\_DESCRIPTION | [**GetDescription**](#function-getdescription) () <br> |
|  SR\_FORCE\_INLINE std::vector&lt; std::string &gt; | [**GetNames**](#function-getnames) () <br> |


























## Public Attributes Documentation




### variable bitang 

```C++
glm::vec3 SR_GRAPH_NS::Vertices::SkinnedMeshVertex::bitang;
```




<hr>



### variable norm 

```C++
glm::vec3 SR_GRAPH_NS::Vertices::SkinnedMeshVertex::norm;
```




<hr>



### variable pos 

```C++
glm::vec3 SR_GRAPH_NS::Vertices::SkinnedMeshVertex::pos;
```




<hr>



### variable tang 

```C++
glm::vec3 SR_GRAPH_NS::Vertices::SkinnedMeshVertex::tang;
```




<hr>



### variable uv 

```C++
glm::vec2 SR_GRAPH_NS::Vertices::SkinnedMeshVertex::uv;
```




<hr>



### variable weights 

_x - bone id, y - weight_ 
```C++
glm::vec2 SR_GRAPH_NS::Vertices::SkinnedMeshVertex::weights[SR_MAX_BONES_ON_VERTEX];
```




<hr>



### variable weightsCount 

```C++
uint32_t SR_GRAPH_NS::Vertices::SkinnedMeshVertex::weightsCount;
```




<hr>
## Public Functions Documentation




### function ToString 

```C++
inline SR_NODISCARD std::string SR_GRAPH_NS::Vertices::SkinnedMeshVertex::ToString () const
```




<hr>



### function operator== 

```C++
inline bool SR_GRAPH_NS::Vertices::SkinnedMeshVertex::operator== (
    const SkinnedMeshVertex & other
) const
```




<hr>
## Public Static Functions Documentation




### function GetAttributes 

```C++
static inline SR_FORCE_INLINE std::vector< std::pair< Attribute, size_t > > SR_GRAPH_NS::Vertices::SkinnedMeshVertex::GetAttributes (
    bool asTypes
) 
```




<hr>



### function GetDescription 

```C++
static inline SR_FORCE_INLINE SR_VERTEX_DESCRIPTION SR_GRAPH_NS::Vertices::SkinnedMeshVertex::GetDescription () 
```




<hr>



### function GetNames 

```C++
static inline SR_FORCE_INLINE std::vector< std::string > SR_GRAPH_NS::Vertices::SkinnedMeshVertex::GetNames () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Types/Vertices.h`

