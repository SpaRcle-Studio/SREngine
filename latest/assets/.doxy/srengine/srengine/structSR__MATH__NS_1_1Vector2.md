

# Struct SR\_MATH\_NS::Vector2

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Vector2**](structSR__MATH__NS_1_1Vector2.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef T | [**ValueType**](#typedef-valuetype)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**Vector2**](#variable-vector2)  <br> |
|  T | [**bottom**](#variable-bottom)  <br> |
|  T | [**coord**](#variable-coord)   = `{ 0 }`<br> |
|  T | [**top**](#variable-top)  <br> |
|  T | [**x**](#variable-x)  <br> |
|  T | [**y**](#variable-y)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**Abs**](#function-abs) () const<br> |
|  SR\_NODISCARD Unit | [**Aspect**](#function-aspect) () const<br> |
|  SR\_NODISCARD Unit | [**AspectInv**](#function-aspectinv) () const<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; SR\_FASTCALL | [**Cast**](#function-cast) () noexcept const<br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains) (U value) const<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**DeSingular**](#function-desingular) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & segment) const<br> |
|  SR\_NODISCARD T | [**Distance**](#function-distance) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & vec) noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**Empty**](#function-empty) () const<br> |
|  SR\_NODISCARD bool | [**HasNegative**](#function-hasnegative) () const<br> |
|  SR\_NODISCARD bool | [**HasPositive**](#function-haspositive) () const<br> |
|  SR\_NODISCARD bool | [**HasZero**](#function-haszero) () const<br> |
|  SR\_NODISCARD bool | [**IsFinite**](#function-isfinite) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsNull**](#function-isnull) () const<br> |
|  SR\_NODISCARD T | [**Length**](#function-length) () noexcept const<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**Singular**](#function-singular) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & segment) const<br> |
|  SR\_NODISCARD T | [**Sum**](#function-sum) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE glm::vec2 | [**ToGLM**](#function-toglm) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  SR\_FORCE\_INLINE | [**Vector2**](#function-vector2-14) () <br> |
|  SR\_FORCE\_INLINE | [**Vector2**](#function-vector2-24) (T p\_x, T p\_y) <br> |
|  SR\_FORCE\_INLINE | [**Vector2**](#function-vector2-34) (T p) <br> |
|  SR\_FORCE\_INLINE | [**Vector2**](#function-vector2-44) (const glm::vec2 & vec2) <br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](#function-operator) (T p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](#function-operator_1) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator\***](#function-operator_2) (const U & scalar) noexcept const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator\***](#function-operator_3) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator\*=**](#function-operator_4) (const U & value) <br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator\*=**](#function-operator_5) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & value) <br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator+**](#function-operator_6) () const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator+**](#function-operator_7) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & | [**operator+=**](#function-operator_8) ([**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; v) <br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator-**](#function-operator_9) () const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator-**](#function-operator_10) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & | [**operator-=**](#function-operator_11) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator/**](#function-operator_12) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) | [**operator/**](#function-operator_13) (const U & v) const<br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & | [**operator/=**](#function-operator_14) (U p\_scalar) <br> |
|  SR\_FORCE\_INLINE [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & | [**operator/=**](#function-operator_15) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;**](#function-operator_16) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;**](#function-operator_17) (T p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;=**](#function-operator_18) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;=**](#function-operator_19) (T p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](#function-operator_20) (T p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](#function-operator_21) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;**](#function-operator_22) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;**](#function-operator_23) (T p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;=**](#function-operator_24) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;=**](#function-operator_25) (T p\_scalar) const<br> |
|  SR\_FORCE\_INLINE const T & | [**operator[]**](#function-operator_26) (int p\_axis) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator[]**](#function-operator_27) (int p\_axis) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**One**](#function-one) () <br> |
|  [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**Zero**](#function-zero) () <br> |


























## Public Types Documentation




### typedef ValueType 

```C++
using SR_MATH_NS::Vector2< T >::ValueType =  T;
```




<hr>
## Public Attributes Documentation




### variable Vector2 

```C++
union SR_MATH_NS::Vector2 SR_MATH_NS::Vector2< T >;
```




<hr>



### variable bottom 

```C++
T SR_MATH_NS::Vector2< T >::bottom;
```




<hr>



### variable coord 

```C++
T SR_MATH_NS::Vector2< T >::coord[2];
```




<hr>



### variable top 

```C++
T SR_MATH_NS::Vector2< T >::top;
```




<hr>



### variable x 

```C++
T SR_MATH_NS::Vector2< T >::x;
```




<hr>



### variable y 

```C++
T SR_MATH_NS::Vector2< T >::y;
```




<hr>
## Public Functions Documentation




### function Abs 

```C++
inline SR_NODISCARD Vector2 SR_MATH_NS::Vector2::Abs () const
```




<hr>



### function Aspect 

```C++
inline SR_NODISCARD Unit SR_MATH_NS::Vector2::Aspect () const
```




<hr>



### function AspectInv 

```C++
inline SR_NODISCARD Unit SR_MATH_NS::Vector2::AspectInv () const
```




<hr>



### function Cast 

```C++
template<typename U>
inline SR_NODISCARD Vector2 < U > SR_FASTCALL SR_MATH_NS::Vector2::Cast () noexcept const
```




<hr>



### function Contains 

```C++
template<typename U>
inline SR_NODISCARD bool SR_MATH_NS::Vector2::Contains (
    U value
) const
```




<hr>



### function DeSingular 

```C++
inline SR_NODISCARD Vector2 SR_MATH_NS::Vector2::DeSingular (
    const Vector2 & segment
) const
```




<hr>



### function Distance 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector2::Distance (
    const Vector2 & vec
) noexcept const
```




<hr>



### function Empty 

```C++
inline SR_NODISCARD SR_FORCE_INLINE bool SR_MATH_NS::Vector2::Empty () const
```




<hr>



### function HasNegative 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector2::HasNegative () const
```




<hr>



### function HasPositive 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector2::HasPositive () const
```




<hr>



### function HasZero 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector2::HasZero () const
```




<hr>



### function IsFinite 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector2::IsFinite () noexcept const
```




<hr>



### function IsNull 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector2::IsNull () const
```




<hr>



### function Length 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector2::Length () noexcept const
```




<hr>



### function Singular 

```C++
inline SR_NODISCARD Vector2 SR_MATH_NS::Vector2::Singular (
    const Vector2 & segment
) const
```




<hr>



### function Sum 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector2::Sum () const
```




<hr>



### function ToGLM 

```C++
inline SR_NODISCARD SR_FORCE_INLINE glm::vec2 SR_MATH_NS::Vector2::ToGLM () noexcept const
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD std::string SR_MATH_NS::Vector2::ToString () const
```




<hr>



### function Vector2 [1/4]

```C++
inline SR_FORCE_INLINE SR_MATH_NS::Vector2::Vector2 () 
```




<hr>



### function Vector2 [2/4]

```C++
inline SR_FORCE_INLINE SR_MATH_NS::Vector2::Vector2 (
    T p_x,
    T p_y
) 
```




<hr>



### function Vector2 [3/4]

```C++
inline SR_FORCE_INLINE SR_MATH_NS::Vector2::Vector2 (
    T p
) 
```




<hr>



### function Vector2 [4/4]

```C++
inline SR_FORCE_INLINE SR_MATH_NS::Vector2::Vector2 (
    const glm::vec2 & vec2
) 
```




<hr>



### function operator!= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator!= (
    T p_scalar
) const
```




<hr>



### function operator!= 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator!= (
    const Vector2 < U > & p_v
) const
```




<hr>



### function operator\* 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator* (
    const U & scalar
) noexcept const
```




<hr>



### function operator\* 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator* (
    const Vector2 < U > & p_v
) const
```




<hr>



### function operator\*= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator*= (
    const U & value
) 
```




<hr>



### function operator\*= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator*= (
    const Vector2 < U > & value
) 
```




<hr>



### function operator+ 

```C++
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator+ () const
```




<hr>



### function operator+ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator+ (
    const Vector2 < U > & p_v
) const
```




<hr>



### function operator+= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 & SR_MATH_NS::Vector2::operator+= (
    Vector2 < U > v
) 
```




<hr>



### function operator- 

```C++
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator- () const
```




<hr>



### function operator- 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator- (
    const Vector2 < U > & p_v
) const
```




<hr>



### function operator-= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 & SR_MATH_NS::Vector2::operator-= (
    const Vector2 < U > & p_v
) 
```




<hr>



### function operator/ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator/ (
    const Vector2 < U > & p_v
) const
```




<hr>



### function operator/ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 SR_MATH_NS::Vector2::operator/ (
    const U & v
) const
```




<hr>



### function operator/= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 & SR_MATH_NS::Vector2::operator/= (
    U p_scalar
) 
```




<hr>



### function operator/= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector2 & SR_MATH_NS::Vector2::operator/= (
    const Vector2 < U > & p_v
) 
```




<hr>



### function operator&lt; 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator< (
    const Vector2 & p_v
) const
```




<hr>



### function operator&lt; 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator< (
    T p_scalar
) const
```




<hr>



### function operator&lt;= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator<= (
    const Vector2 & p_v
) const
```




<hr>



### function operator&lt;= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator<= (
    T p_scalar
) const
```




<hr>



### function operator== 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator== (
    T p_scalar
) const
```




<hr>



### function operator== 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator== (
    const Vector2 < U > & p_v
) const
```




<hr>



### function operator&gt; 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator> (
    const Vector2 & p_v
) const
```




<hr>



### function operator&gt; 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator> (
    T p_scalar
) const
```




<hr>



### function operator&gt;= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator>= (
    const Vector2 & p_v
) const
```




<hr>



### function operator&gt;= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector2::operator>= (
    T p_scalar
) const
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE const T & SR_MATH_NS::Vector2::operator[] (
    int p_axis
) const
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE T & SR_MATH_NS::Vector2::operator[] (
    int p_axis
) 
```




<hr>
## Public Static Functions Documentation




### function One 

```C++
static inline Vector2 < T > SR_MATH_NS::Vector2::One () 
```




<hr>



### function Zero 

```C++
static inline Vector2 < T > SR_MATH_NS::Vector2::Zero () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector2.h`

