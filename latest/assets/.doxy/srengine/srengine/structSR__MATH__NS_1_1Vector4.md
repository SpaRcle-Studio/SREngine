

# Struct SR\_MATH\_NS::Vector4

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Vector4**](structSR__MATH__NS_1_1Vector4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef T | [**ValueType**](#typedef-valuetype)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Vector4**](#variable-vector4)  <br> |
|  T | [**a**](#variable-a)  <br> |
|  T | [**b**](#variable-b)  <br> |
|  T | [**coord**](#variable-coord)   = `{ 0 }`<br> |
|  T | [**g**](#variable-g)  <br> |
|  T | [**r**](#variable-r)  <br> |
|  T | [**w**](#variable-w)  <br> |
|  T | [**x**](#variable-x)  <br> |
|  T | [**y**](#variable-y)  <br> |
|  T | [**z**](#variable-z)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; SR\_FASTCALL | [**Cast**](#function-cast) () noexcept const<br> |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Clamp**](#function-clamp) (U \_max, Y \_min) const<br> |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Cross**](#function-cross) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & v) const<br> |
|  SR\_NODISCARD Unit | [**DistanceToPlane**](#function-distancetoplane) (const SR\_MATH\_NS::FVector3 & point) const<br> |
|  SR\_NODISCARD T | [**Dot**](#function-dot) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; & v) const<br> |
|  SR\_NODISCARD T | [**Dot3**](#function-dot3) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; & v) const<br> |
|  SR\_NODISCARD bool | [**IsFinite**](#function-isfinite) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T | [**Length**](#function-length) () const<br> |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**Normalize**](#function-normalize) () const<br> |
|  SR\_NODISCARD T | [**SqrMagnitude**](#function-sqrmagnitude) () const<br> |
|  SR\_NODISCARD glm::vec4 | [**ToGLM**](#function-toglm) () const<br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](#function-vector4-15) () <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](#function-vector4-25) (T scalar) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](#function-vector4-35) (const glm::vec4 & vec4) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](#function-vector4-45) (T \_x, T \_y, T \_z, T \_w) <br> |
|  SR\_FAST\_CONSTRUCTOR | [**Vector4**](#function-vector4-55) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; & v, T w) <br> |
|  SR\_NODISCARD constexpr [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**XY**](#function-xy) () noexcept const<br> |
|  SR\_NODISCARD constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XYZ**](#function-xyz) () noexcept const<br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](#function-operator) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator%=**](#function-operator_1) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator\***](#function-operator_2) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator\***](#function-operator_3) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator\*=**](#function-operator_4) (U p\_scalar) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator\*=**](#function-operator_5) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator+**](#function-operator_6) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator-**](#function-operator_7) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator-**](#function-operator_8) () const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) | [**operator/**](#function-operator_9) (const U & v) const<br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator/=**](#function-operator_10) (U p\_scalar) <br> |
|  SR\_FORCE\_INLINE [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & | [**operator/=**](#function-operator_11) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](#function-operator_12) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md) & v) const<br> |
|  SR\_FORCE\_INLINE const T & | [**operator[]**](#function-operator_13) (int32\_t axis) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator[]**](#function-operator_14) (int32\_t axis) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitW**](#function-unitw) () <br> |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitX**](#function-unitx) () <br> |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitY**](#function-unity) () <br> |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; T &gt; | [**UnitZ**](#function-unitz) () <br> |


























## Public Types Documentation




### typedef ValueType 

```C++
using SR_MATH_NS::Vector4< T >::ValueType =  T;
```




<hr>
## Public Attributes Documentation




### variable Vector4 

```C++
union SR_MATH_NS::Vector4 SR_MATH_NS::Vector4< T >;
```




<hr>



### variable a 

```C++
T SR_MATH_NS::Vector4< T >::a;
```




<hr>



### variable b 

```C++
T SR_MATH_NS::Vector4< T >::b;
```




<hr>



### variable coord 

```C++
T SR_MATH_NS::Vector4< T >::coord[4];
```




<hr>



### variable g 

```C++
T SR_MATH_NS::Vector4< T >::g;
```




<hr>



### variable r 

```C++
T SR_MATH_NS::Vector4< T >::r;
```




<hr>



### variable w 

```C++
T SR_MATH_NS::Vector4< T >::w;
```




<hr>



### variable x 

```C++
T SR_MATH_NS::Vector4< T >::x;
```




<hr>



### variable y 

```C++
T SR_MATH_NS::Vector4< T >::y;
```




<hr>



### variable z 

```C++
T SR_MATH_NS::Vector4< T >::z;
```




<hr>
## Public Functions Documentation




### function Cast 

```C++
template<typename U>
inline SR_NODISCARD Vector4 < U > SR_FASTCALL SR_MATH_NS::Vector4::Cast () noexcept const
```




<hr>



### function Clamp 

```C++
template<typename U, typename Y>
inline SR_NODISCARD Vector4 SR_MATH_NS::Vector4::Clamp (
    U _max,
    Y _min
) const
```




<hr>



### function Cross 

```C++
inline SR_NODISCARD Vector4 SR_MATH_NS::Vector4::Cross (
    const Vector4 & v
) const
```




<hr>



### function DistanceToPlane 

```C++
inline SR_NODISCARD Unit SR_MATH_NS::Vector4::DistanceToPlane (
    const SR_MATH_NS::FVector3 & point
) const
```




<hr>



### function Dot 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector4::Dot (
    const Vector4 < T > & v
) const
```




<hr>



### function Dot3 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector4::Dot3 (
    const Vector3 < T > & v
) const
```




<hr>



### function IsFinite 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector4::IsFinite () noexcept const
```




<hr>



### function Length 

```C++
inline SR_NODISCARD SR_FORCE_INLINE T SR_MATH_NS::Vector4::Length () const
```




<hr>



### function Normalize 

```C++
inline SR_NODISCARD Vector4 SR_MATH_NS::Vector4::Normalize () const
```




<hr>



### function SqrMagnitude 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector4::SqrMagnitude () const
```




<hr>



### function ToGLM 

```C++
inline SR_NODISCARD glm::vec4 SR_MATH_NS::Vector4::ToGLM () const
```




<hr>



### function Vector4 [1/5]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector4::Vector4 () 
```




<hr>



### function Vector4 [2/5]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector4::Vector4 (
    T scalar
) 
```




<hr>



### function Vector4 [3/5]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector4::Vector4 (
    const glm::vec4 & vec4
) 
```




<hr>



### function Vector4 [4/5]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector4::Vector4 (
    T _x,
    T _y,
    T _z,
    T _w
) 
```




<hr>



### function Vector4 [5/5]

```C++
inline SR_FAST_CONSTRUCTOR SR_MATH_NS::Vector4::Vector4 (
    const Vector3 < T > & v,
    T w
) 
```




<hr>



### function XY 

```C++
inline SR_NODISCARD constexpr Vector2 < T > SR_MATH_NS::Vector4::XY () noexcept const
```




<hr>



### function XYZ 

```C++
inline SR_NODISCARD constexpr Vector3 < T > SR_MATH_NS::Vector4::XYZ () noexcept const
```




<hr>



### function operator!= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector4::operator!= (
    const Vector4 & v
) const
```




<hr>



### function operator%= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 & SR_MATH_NS::Vector4::operator%= (
    const Vector4 < U > & p_v
) 
```




<hr>



### function operator\* 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 SR_MATH_NS::Vector4::operator* (
    const Vector4 < U > & p_v
) const
```




<hr>



### function operator\* 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 SR_MATH_NS::Vector4::operator* (
    U p_scalar
) const
```




<hr>



### function operator\*= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 & SR_MATH_NS::Vector4::operator*= (
    U p_scalar
) 
```




<hr>



### function operator\*= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 & SR_MATH_NS::Vector4::operator*= (
    const Vector4 < U > & p_v
) 
```




<hr>



### function operator+ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 SR_MATH_NS::Vector4::operator+ (
    const Vector4 < U > & v
) const
```




<hr>



### function operator- 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 SR_MATH_NS::Vector4::operator- (
    const Vector4 < U > & p_v
) const
```




<hr>



### function operator- 

```C++
inline SR_FORCE_INLINE Vector4 SR_MATH_NS::Vector4::operator- () const
```




<hr>



### function operator/ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 SR_MATH_NS::Vector4::operator/ (
    const U & v
) const
```




<hr>



### function operator/= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 & SR_MATH_NS::Vector4::operator/= (
    U p_scalar
) 
```




<hr>



### function operator/= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector4 & SR_MATH_NS::Vector4::operator/= (
    const Vector4 < U > & p_v
) 
```




<hr>



### function operator== 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector4::operator== (
    const Vector4 & v
) const
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE const T & SR_MATH_NS::Vector4::operator[] (
    int32_t axis
) const
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE T & SR_MATH_NS::Vector4::operator[] (
    int32_t axis
) 
```




<hr>
## Public Static Functions Documentation




### function UnitW 

```C++
static inline Vector4 < T > SR_MATH_NS::Vector4::UnitW () 
```




<hr>



### function UnitX 

```C++
static inline Vector4 < T > SR_MATH_NS::Vector4::UnitX () 
```




<hr>



### function UnitY 

```C++
static inline Vector4 < T > SR_MATH_NS::Vector4::UnitY () 
```




<hr>



### function UnitZ 

```C++
static inline Vector4 < T > SR_MATH_NS::Vector4::UnitZ () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector4.h`

