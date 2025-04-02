

# Struct SR\_UTILS\_NS::Vertex



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Vertex**](structSR__UTILS__NS_1_1Vertex.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Vec3**](structSR__UTILS__NS_1_1Vec3.md) | [**bitangent**](#variable-bitangent)  <br> |
|  uint32\_t | [**boneId**](#variable-boneid)   = `0`<br> |
|  [**Vec3**](structSR__UTILS__NS_1_1Vec3.md) | [**normal**](#variable-normal)  <br> |
|  [**Vec3**](structSR__UTILS__NS_1_1Vec3.md) | [**position**](#variable-position)  <br> |
|  [**Vec3**](structSR__UTILS__NS_1_1Vec3.md) | [**tangent**](#variable-tangent)  <br> |
|  [**Vec2**](structSR__UTILS__NS_1_1Vec2.md) | [**uv**](#variable-uv)  <br> |
|  float | [**weight**](#variable-weight)   = `0.f`<br> |
|  struct [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) | [**weights**](#variable-weights)  <br> |
|  uint8\_t | [**weightsNum**](#variable-weightsnum)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Vertex**](#function-vertex-13) () = default<br> |
|   | [**Vertex**](#function-vertex-23) (int32\_t x, int32\_t y, int32\_t z) <br> |
|   | [**Vertex**](#function-vertex-33) ([**Vec3**](structSR__UTILS__NS_1_1Vec3.md) pos, [**Vec2**](structSR__UTILS__NS_1_1Vec2.md) uv, [**Vec3**](structSR__UTILS__NS_1_1Vec3.md) norm, [**Vec3**](structSR__UTILS__NS_1_1Vec3.md) tang, [**Vec3**](structSR__UTILS__NS_1_1Vec3.md) btg) <br> |




























## Public Attributes Documentation




### variable bitangent 

```C++
Vec3 SR_UTILS_NS::Vertex::bitangent;
```




<hr>



### variable boneId 

```C++
uint32_t SR_UTILS_NS::Vertex::boneId;
```




<hr>



### variable normal 

```C++
Vec3 SR_UTILS_NS::Vertex::normal;
```




<hr>



### variable position 

```C++
Vec3 SR_UTILS_NS::Vertex::position;
```




<hr>



### variable tangent 

```C++
Vec3 SR_UTILS_NS::Vertex::tangent;
```




<hr>



### variable uv 

```C++
Vec2 SR_UTILS_NS::Vertex::uv;
```




<hr>



### variable weight 

```C++
float SR_UTILS_NS::Vertex::weight;
```




<hr>



### variable weights 

```C++
struct SR_UTILS_NS::Vertex SR_UTILS_NS::Vertex::weights[SR_MAX_BONES_ON_VERTEX];
```




<hr>



### variable weightsNum 

```C++
uint8_t SR_UTILS_NS::Vertex::weightsNum;
```




<hr>
## Public Functions Documentation




### function Vertex [1/3]

```C++
SR_UTILS_NS::Vertex::Vertex () = default
```




<hr>



### function Vertex [2/3]

```C++
inline SR_UTILS_NS::Vertex::Vertex (
    int32_t x,
    int32_t y,
    int32_t z
) 
```




<hr>



### function Vertex [3/3]

```C++
inline SR_UTILS_NS::Vertex::Vertex (
    Vec3 pos,
    Vec2 uv,
    Vec3 norm,
    Vec3 tang,
    Vec3 btg
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Vertices.h`

