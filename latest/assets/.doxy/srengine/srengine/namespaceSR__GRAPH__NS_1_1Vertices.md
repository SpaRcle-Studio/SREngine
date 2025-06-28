

# Namespace SR\_GRAPH\_NS::Vertices



[**Namespace List**](namespaces.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Vertices**](namespaceSR__GRAPH__NS_1_1Vertices.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**SimpleVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SimpleVertex.md) <br> |
| struct | [**SkinnedMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SkinnedMeshVertex.md) <br> |
| struct | [**StaticMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1StaticMeshVertex.md) <br> |
| struct | [**StaticMeshVertexAligned**](structSR__GRAPH__NS_1_1Vertices_1_1StaticMeshVertexAligned.md) <br> |
| struct | [**UIVertex**](structSR__GRAPH__NS_1_1Vertices_1_1UIVertex.md) <br> |
| struct | [**VertexInfo**](structSR__GRAPH__NS_1_1Vertices_1_1VertexInfo.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Attribute**](#enum-attribute)  <br> |
| typedef std::vector&lt; [**SimpleVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SimpleVertex.md) &gt; | [**SimpleVertices**](#typedef-simplevertices)  <br> |
| typedef std::vector&lt; [**SkinnedMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SkinnedMeshVertex.md) &gt; | [**SkinnedMeshVertices**](#typedef-skinnedmeshvertices)  <br> |
| typedef std::vector&lt; [**StaticMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1StaticMeshVertex.md) &gt; | [**StaticMeshVertices**](#typedef-staticmeshvertices)  <br> |
| typedef std::vector&lt; [**UIVertex**](structSR__GRAPH__NS_1_1Vertices_1_1UIVertex.md) &gt; | [**UIVertices**](#typedef-uivertices)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**Barycenter**](#function-barycenter) (const std::vector&lt; V &gt; & vertices) <br> |
|   | [**SR\_ENUM\_NS\_CLASS**](#function-sr_enum_ns_class) (VertexType, Unknown, None, [**StaticMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1StaticMeshVertex.md), [**SkinnedMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SkinnedMeshVertex.md), [**SimpleVertex**](structSR__GRAPH__NS_1_1Vertices_1_1SimpleVertex.md), [**UIVertex**](structSR__GRAPH__NS_1_1Vertices_1_1UIVertex.md)) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; T &gt; | [**CastVertices**](#function-castvertices) (const [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) \* pData, uint32\_t count) <br> |
|  std::vector&lt; T &gt; | [**CastVertices**](#function-castvertices) (const std::vector&lt; [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) &gt; & raw) <br> |
|  SR\_MAYBE\_UNUSED [**VertexInfo**](structSR__GRAPH__NS_1_1Vertices_1_1VertexInfo.md) | [**GetVertexInfo**](#function-getvertexinfo) (VertexType type) <br> |
|  std::string | [**ToString**](#function-tostring) (const glm::vec3 & vec3) <br> |
|  std::string | [**ToString**](#function-tostring) (const glm::vec2 & vec2) <br> |
|  SR\_MAYBE\_UNUSED std::string | [**ToString**](#function-tostring) (const std::vector&lt; uint32\_t &gt; & indices) <br> |
|  SR\_MAYBE\_UNUSED std::string | [**ToString**](#function-tostring) (const std::vector&lt; [**StaticMeshVertex**](structSR__GRAPH__NS_1_1Vertices_1_1StaticMeshVertex.md) &gt; & vertices) <br> |


























## Public Types Documentation




### enum Attribute 

```C++
enum SR_GRAPH_NS::Vertices::Attribute {
    Unknown = 0,
    FLOAT_R32G32B32A32 = 1 << 0,
    FLOAT_R32G32B32 = 1 << 1,
    FLOAT_R32G32 = 1 << 2,
    INT_R32G32B32A32 = 1 << 3,
    INT_R32G32B32 = 1 << 4,
    INT_R32G32 = 1 << 5,
    UINT_R32 = 1 << 6,
    INT_R32 = 1 << 7
};
```




<hr>



### typedef SimpleVertices 

```C++
typedef std::vector<SimpleVertex> SR_GRAPH_NS::Vertices::SimpleVertices;
```




<hr>



### typedef SkinnedMeshVertices 

```C++
typedef std::vector<SkinnedMeshVertex> SR_GRAPH_NS::Vertices::SkinnedMeshVertices;
```




<hr>



### typedef StaticMeshVertices 

```C++
typedef std::vector<StaticMeshVertex> SR_GRAPH_NS::Vertices::StaticMeshVertices;
```




<hr>



### typedef UIVertices 

```C++
typedef std::vector<UIVertex> SR_GRAPH_NS::Vertices::UIVertices;
```




<hr>
## Public Functions Documentation




### function Barycenter 

```C++
template<typename V>
SR_MATH_NS::FVector3 SR_GRAPH_NS::Vertices::Barycenter (
    const std::vector< V > & vertices
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS 

```C++
SR_GRAPH_NS::Vertices::SR_ENUM_NS_CLASS (
    VertexType,
    Unknown,
    None,
    StaticMeshVertex,
    SkinnedMeshVertex,
    SimpleVertex,
    UIVertex
) 
```




<hr>
## Public Static Functions Documentation




### function CastVertices 

```C++
template<typename T>
static std::vector< T > SR_GRAPH_NS::Vertices::CastVertices (
    const SR_UTILS_NS::Vertex * pData,
    uint32_t count
) 
```




<hr>



### function CastVertices 

```C++
template<typename T>
static std::vector< T > SR_GRAPH_NS::Vertices::CastVertices (
    const std::vector< SR_UTILS_NS::Vertex > & raw
) 
```




<hr>



### function GetVertexInfo 

```C++
static SR_MAYBE_UNUSED VertexInfo SR_GRAPH_NS::Vertices::GetVertexInfo (
    VertexType type
) 
```




<hr>



### function ToString 

```C++
static std::string SR_GRAPH_NS::Vertices::ToString (
    const glm::vec3 & vec3
) 
```




<hr>



### function ToString 

```C++
static std::string SR_GRAPH_NS::Vertices::ToString (
    const glm::vec2 & vec2
) 
```




<hr>



### function ToString 

```C++
static SR_MAYBE_UNUSED std::string SR_GRAPH_NS::Vertices::ToString (
    const std::vector< uint32_t > & indices
) 
```




<hr>



### function ToString 

```C++
static SR_MAYBE_UNUSED std::string SR_GRAPH_NS::Vertices::ToString (
    const std::vector< StaticMeshVertex > & vertices
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Types/Vertices.h`

