

# Struct SR\_GRAPH\_NS::Vertices::UIVertex



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Vertices**](namespaceSR__GRAPH__NS_1_1Vertices.md) **>** [**UIVertex**](structSR__GRAPH__NS_1_1Vertices_1_1UIVertex.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  glm::vec3 | [**pos**](#variable-pos)  <br> |
|  glm::vec2 | [**uv**](#variable-uv)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  bool | [**operator==**](#function-operator) (const [**UIVertex**](structSR__GRAPH__NS_1_1Vertices_1_1UIVertex.md) & other) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_FORCE\_INLINE std::vector&lt; std::pair&lt; Attribute, size\_t &gt; &gt; | [**GetAttributes**](#function-getattributes) (bool asTypes) <br> |
|  constexpr SR\_FORCE\_INLINE SR\_VERTEX\_DESCRIPTION | [**GetDescription**](#function-getdescription) () <br> |
|  SR\_FORCE\_INLINE std::vector&lt; std::string &gt; | [**GetNames**](#function-getnames) () <br> |


























## Public Attributes Documentation




### variable pos 

```C++
glm::vec3 SR_GRAPH_NS::Vertices::UIVertex::pos;
```




<hr>



### variable uv 

```C++
glm::vec2 SR_GRAPH_NS::Vertices::UIVertex::uv;
```




<hr>
## Public Functions Documentation




### function ToString 

```C++
inline SR_NODISCARD std::string SR_GRAPH_NS::Vertices::UIVertex::ToString () const
```




<hr>



### function operator== 

```C++
inline bool SR_GRAPH_NS::Vertices::UIVertex::operator== (
    const UIVertex & other
) const
```




<hr>
## Public Static Functions Documentation




### function GetAttributes 

```C++
static inline SR_FORCE_INLINE std::vector< std::pair< Attribute, size_t > > SR_GRAPH_NS::Vertices::UIVertex::GetAttributes (
    bool asTypes
) 
```




<hr>



### function GetDescription 

```C++
static inline constexpr SR_FORCE_INLINE SR_VERTEX_DESCRIPTION SR_GRAPH_NS::Vertices::UIVertex::GetDescription () 
```




<hr>



### function GetNames 

```C++
static inline SR_FORCE_INLINE std::vector< std::string > SR_GRAPH_NS::Vertices::UIVertex::GetNames () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Types/Vertices.h`

