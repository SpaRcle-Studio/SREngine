

# Class SR\_MATH\_NS::FColor



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**FColor**](classSR__MATH__NS_1_1FColor.md)








Inherits the following classes: [SR\_MATH\_NS::Vector4](structSR__MATH__NS_1_1Vector4.md)
















## Public Types inherited from SR_MATH_NS::Vector4

See [SR\_MATH\_NS::Vector4](structSR__MATH__NS_1_1Vector4.md)

| Type | Name |
| ---: | :--- |
| typedef T | [**ValueType**](structSR__MATH__NS_1_1Vector4.md#typedef-valuetype)  <br> |








## Public Attributes inherited from SR_MATH_NS::Vector4

See [SR\_MATH\_NS::Vector4](structSR__MATH__NS_1_1Vector4.md)

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Vector4**](structSR__MATH__NS_1_1Vector4.md#variable-vector4)  <br> |
|  T | [**a**](structSR__MATH__NS_1_1Vector4.md#variable-a)  <br> |
|  T | [**b**](structSR__MATH__NS_1_1Vector4.md#variable-b)  <br> |
|  T | [**coord**](structSR__MATH__NS_1_1Vector4.md#variable-coord)   = `{ 0 }`<br> |
|  T | [**g**](structSR__MATH__NS_1_1Vector4.md#variable-g)  <br> |
|  T | [**r**](structSR__MATH__NS_1_1Vector4.md#variable-r)  <br> |
|  T | [**w**](structSR__MATH__NS_1_1Vector4.md#variable-w)  <br> |
|  T | [**x**](structSR__MATH__NS_1_1Vector4.md#variable-x)  <br> |
|  T | [**y**](structSR__MATH__NS_1_1Vector4.md#variable-y)  <br> |
|  T | [**z**](structSR__MATH__NS_1_1Vector4.md#variable-z)  <br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-19) () <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-29) (Unit scalar) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-39) (const glm::vec4 & vec4) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-49) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; Unit &gt; & v) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-59) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-69) ([**FColor**](classSR__MATH__NS_1_1FColor.md) && color) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-79) (double\_t \_x, double\_t \_y, double\_t \_z, double\_t \_w) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-89) (float\_t \_x, float\_t \_y, float\_t \_z, float\_t \_w) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**FColor**](#function-fcolor-99) (int32\_t \_x, int32\_t \_y, int32\_t \_z, int32\_t \_w) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator=**](#function-operator) (const [**FColor**](classSR__MATH__NS_1_1FColor.md) & color) <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) & | [**operator=**](#function-operator_1) ([**FColor**](classSR__MATH__NS_1_1FColor.md) && color) <br> |


## Public Functions inherited from SR_MATH_NS::Vector4

See [SR\_MATH\_NS::Vector4](structSR__MATH__NS_1_1Vector4.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; SR\_FASTCALL | [**Cast**](structSR__MATH__NS_1_1Vector4.md#function-cast) () noexcept const<br> |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Clamp**](structSR__MATH__NS_1_1Vector4.md#function-clamp) (U \_max, Y \_min) const<br> |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Cross**](structSR__MATH__NS_1_1Vector4.md#function-cross) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & v) const<br> |
|  SR\_NODISCARD Unit | [**DistanceToPlane**](structSR__MATH__NS_1_1Vector4.md#function-distancetoplane) (const SR\_MATH\_NS::FVector3 & point) const<br> |
|  SR\_NODISCARD T | [**Dot**](structSR__MATH__NS_1_1Vector4.md#function-dot) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; & v) const<br> |
|  SR\_NODISCARD T | [**Dot3**](structSR__MATH__NS_1_1Vector4.md#function-dot3) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; & v) const<br> |
|  SR\_NODISCARD bool | [**IsFinite**](structSR__MATH__NS_1_1Vector4.md#function-isfinite) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T | [**Length**](structSR__MATH__NS_1_1Vector4.md#function-length) () const<br> |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Normalize**](structSR__MATH__NS_1_1Vector4.md#function-normalize) () const<br> |
|  SR\_NODISCARD T | [**SqrMagnitude**](structSR__MATH__NS_1_1Vector4.md#function-sqrmagnitude) () const<br> |
|  SR\_NODISCARD glm::vec4 | [**ToGLM**](structSR__MATH__NS_1_1Vector4.md#function-toglm) () const<br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](structSR__MATH__NS_1_1Vector4.md#function-vector4-15) () <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](structSR__MATH__NS_1_1Vector4.md#function-vector4-25) (T scalar) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](structSR__MATH__NS_1_1Vector4.md#function-vector4-35) (const glm::vec4 & vec4) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](structSR__MATH__NS_1_1Vector4.md#function-vector4-45) (T \_x, T \_y, T \_z, T \_w) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](structSR__MATH__NS_1_1Vector4.md#function-vector4-55) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; & v, T w) <br> |
|  SR\_NODISCARD constexpr [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**XY**](structSR__MATH__NS_1_1Vector4.md#function-xy) () noexcept const<br> |
|  SR\_NODISCARD constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XYZ**](structSR__MATH__NS_1_1Vector4.md#function-xyz) () noexcept const<br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](structSR__MATH__NS_1_1Vector4.md#function-operator) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator%=**](structSR__MATH__NS_1_1Vector4.md#function-operator_1) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator\***](structSR__MATH__NS_1_1Vector4.md#function-operator_2) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator\***](structSR__MATH__NS_1_1Vector4.md#function-operator_3) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator\*=**](structSR__MATH__NS_1_1Vector4.md#function-operator_4) (U p\_scalar) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator\*=**](structSR__MATH__NS_1_1Vector4.md#function-operator_5) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator+**](structSR__MATH__NS_1_1Vector4.md#function-operator_6) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator-**](structSR__MATH__NS_1_1Vector4.md#function-operator_7) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator-**](structSR__MATH__NS_1_1Vector4.md#function-operator_8) () const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator/**](structSR__MATH__NS_1_1Vector4.md#function-operator_9) (const U & v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator/=**](structSR__MATH__NS_1_1Vector4.md#function-operator_10) (U p\_scalar) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator/=**](structSR__MATH__NS_1_1Vector4.md#function-operator_11) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](structSR__MATH__NS_1_1Vector4.md#function-operator_12) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & v) const<br> |
|  SR\_FORCE\_INLINE const T & | [**operator[]**](structSR__MATH__NS_1_1Vector4.md#function-operator_13) (int32\_t axis) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator[]**](structSR__MATH__NS_1_1Vector4.md#function-operator_14) (int32\_t axis) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Alpha**](#function-alpha) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Black**](#function-black) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Blue**](#function-blue) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Cyan**](#function-cyan) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Green**](#function-green) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Magenta**](#function-magenta) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Red**](#function-red) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**White**](#function-white) () <br> |
|  [**FColor**](classSR__MATH__NS_1_1FColor.md) | [**Yellow**](#function-yellow) () <br> |


## Public Static Functions inherited from SR_MATH_NS::Vector4

See [SR\_MATH\_NS::Vector4](structSR__MATH__NS_1_1Vector4.md)

| Type | Name |
| ---: | :--- |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitW**](structSR__MATH__NS_1_1Vector4.md#function-unitw) () <br> |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitX**](structSR__MATH__NS_1_1Vector4.md#function-unitx) () <br> |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitY**](structSR__MATH__NS_1_1Vector4.md#function-unity) () <br> |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitZ**](structSR__MATH__NS_1_1Vector4.md#function-unitz) () <br> |


















































## Public Functions Documentation




### function FColor [1/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor () 
```




<hr>



### function FColor [2/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    Unit scalar
) 
```




<hr>



### function FColor [3/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    const glm::vec4 & vec4
) 
```




<hr>



### function FColor [4/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    const Vector4 < Unit > & v
) 
```




<hr>



### function FColor [5/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    const FColor & color
) 
```




<hr>



### function FColor [6/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    FColor && color
) 
```




<hr>



### function FColor [7/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    double_t _x,
    double_t _y,
    double_t _z,
    double_t _w
) 
```




<hr>



### function FColor [8/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    float_t _x,
    float_t _y,
    float_t _z,
    float_t _w
) 
```




<hr>



### function FColor [9/9]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::FColor::FColor (
    int32_t _x,
    int32_t _y,
    int32_t _z,
    int32_t _w
) 
```




<hr>



### function operator= 

```C++
inline FColor & SR_MATH_NS::FColor::operator= (
    const FColor & color
) 
```




<hr>



### function operator= 

```C++
inline FColor & SR_MATH_NS::FColor::operator= (
    FColor && color
) 
```




<hr>
## Public Static Functions Documentation




### function Alpha 

```C++
static inline FColor SR_MATH_NS::FColor::Alpha () 
```




<hr>



### function Black 

```C++
static inline FColor SR_MATH_NS::FColor::Black () 
```




<hr>



### function Blue 

```C++
static inline FColor SR_MATH_NS::FColor::Blue () 
```




<hr>



### function Cyan 

```C++
static inline FColor SR_MATH_NS::FColor::Cyan () 
```




<hr>



### function Green 

```C++
static inline FColor SR_MATH_NS::FColor::Green () 
```




<hr>



### function Magenta 

```C++
static inline FColor SR_MATH_NS::FColor::Magenta () 
```




<hr>



### function Red 

```C++
static inline FColor SR_MATH_NS::FColor::Red () 
```




<hr>



### function White 

```C++
static inline FColor SR_MATH_NS::FColor::White () 
```




<hr>



### function Yellow 

```C++
static inline FColor SR_MATH_NS::FColor::Yellow () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector4.h`

