

# Struct SR\_GRAPH\_NS::Vertices::SimpleVertex



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Vertices**](namespaceSR__GRAPH__NS_1_1Vertices.md) **>** [**SimpleVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SimpleVertex.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  glm::vec3 | [**pos**](#variable-pos)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**operator==**](#function-operator) (const [**SimpleVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SimpleVertex.md) & other) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_FORCE\_INLINE std::vector&lt; std::pair&lt; Attribute, size\_t &gt; &gt; | [**GetAttributes**](#function-getattributes) (bool asTypes) <br> |
|  SR\_FORCE\_INLINE SR\_VERTEX\_DESCRIPTION | [**GetDescription**](#function-getdescription) () <br> |
|  SR\_FORCE\_INLINE std::vector&lt; std::string &gt; | [**GetNames**](#function-getnames) () <br> |


























## Public Attributes Documentation




### variable pos 

```C++
glm::vec3 SR_GRAPH_NS::Vertices::SimpleVertex::pos;
```




<hr>
## Public Functions Documentation




### function operator== 

```C++
inline bool SR_GRAPH_NS::Vertices::SimpleVertex::operator== (
    const SimpleVertex & other
) const
```




<hr>
## Public Static Functions Documentation




### function GetAttributes 

```C++
static inline SR_FORCE_INLINE std::vector< std::pair< Attribute, size_t > > SR_GRAPH_NS::Vertices::SimpleVertex::GetAttributes (
    bool asTypes
) 
```




<hr>



### function GetDescription 

```C++
static inline SR_FORCE_INLINE SR_VERTEX_DESCRIPTION SR_GRAPH_NS::Vertices::SimpleVertex::GetDescription () 
```




<hr>



### function GetNames 

```C++
static inline SR_FORCE_INLINE std::vector< std::string > SR_GRAPH_NS::Vertices::SimpleVertex::GetNames () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Types/Vertices.h`

