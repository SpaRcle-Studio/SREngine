

# Struct SR\_MATH\_NS::Vector3

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Vector3**](structSR__MATH__NS_1_1Vector3.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef T | [**ValueType**](#typedef-valuetype)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Vector3**](#variable-vector3)  <br> |
|  T | [**coord**](#variable-coord)   = `{ 0 }`<br> |
|  T | [**x**](#variable-x)  <br> |
|  T | [**y**](#variable-y)  <br> |
|  T | [**z**](#variable-z)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Abs**](#function-abs) () const<br> |
|  SR\_NODISCARD T | [**Angle**](#function-angle-12) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & to) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Angle**](#function-angle-22) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & vector3) <br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**AngleAxis**](#function-angleaxis) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & target, const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & axis=Vector3::UnitZ()) const<br> |
|  SR\_NODISCARD T | [**AngleCoefficient**](#function-anglecoefficient) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & vector3) const<br> |
|  SR\_NODISCARD T | [**AngleCoefficientEuler**](#function-anglecoefficienteuler) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & vector3) const<br> |
|  SR\_NODISCARD T | [**AngleCoefficientRadians**](#function-anglecoefficientradians) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & vector3) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; SR\_FASTCALL | [**Cast**](#function-cast) () noexcept const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**Clamp**](#function-clamp) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; & upper, const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; & lover) const<br> |
|  SR\_NODISCARD bool | [**ContainsNaN**](#function-containsnan) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Cos**](#function-cos) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Cross**](#function-cross-12) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_b) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**DeSingular**](#function-desingular) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & segment) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Degrees**](#function-degrees) () noexcept const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Direction**](#function-direction) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & point) const<br> |
|  SR\_NODISCARD T SR\_FASTCALL | [**Distance**](#function-distance) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & point) const<br> |
|  SR\_NODISCARD T | [**Dot**](#function-dot-12) ([**Vector3**](structSR__MATH__NS_1_1Vector3.md) p\_b) const<br> |
|  SR\_NODISCARD bool | [**Empty**](#function-empty) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**FixEulerAngles**](#function-fixeulerangles) () const<br> |
|  SR\_NODISCARD bool | [**HasZero**](#function-haszero) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Inverse**](#function-inverse) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) SR\_FASTCALL | [**InverseAxis**](#function-inverseaxis) (Axis axis) const<br> |
|  SR\_NODISCARD bool | [**IsEquals**](#function-isequals) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & value, Unit tolerance) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsEqualsLikely**](#function-isequalslikely) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & value, Unit tolerance) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFinite**](#function-isfinite) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsInfinity**](#function-isinfinity) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T | [**Length**](#function-length) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) SR\_FASTCALL | [**Lerp**](#function-lerp) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & vector3, Unit t) noexcept const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Limits**](#function-limits) (int lim) const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**LookAt**](#function-lookat) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & target) const<br> |
|  SR\_NODISCARD T | [**Max**](#function-max) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Max3**](#function-max3) () const<br> |
|  SR\_NODISCARD T | [**Min**](#function-min) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Min3**](#function-min3) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Normalize**](#function-normalize) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Normalized**](#function-normalized) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**ProjectOnPlane**](#function-projectonplane) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & planeNormal) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Radians**](#function-radians) () noexcept const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Replace**](#function-replace) (int from, int to) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**Rotate**](#function-rotate) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Round**](#function-round) () const<br> |
|  SR\_NODISCARD T | [**SignedAngle**](#function-signedangle) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & to, const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & axis) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Sin**](#function-sin) () const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Singular**](#function-singular) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & segment) const<br> |
|  SR\_NODISCARD T | [**SqrMagnitude**](#function-sqrmagnitude) () const<br> |
|  SR\_NODISCARD T | [**SquaredNorm**](#function-squarednorm) () noexcept const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) SR\_FASTCALL | [**Swap**](#function-swap) (Axis axis) const<br> |
|  SR\_NODISCARD glm::vec3 | [**ToGLM**](#function-toglm) () noexcept const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**ToQuat**](#function-toquat) () const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  constexpr SR\_FORCE\_INLINE | [**Vector3**](#function-vector3-18) () <br> |
|  constexpr SR\_FORCE\_INLINE | [**Vector3**](#function-vector3-28) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & vec) <br> |
|  constexpr SR\_FORCE\_INLINE | [**Vector3**](#function-vector3-38) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & vec, U value) <br> |
|  SR\_FORCE\_INLINE constexpr | [**Vector3**](#function-vector3-48) (const float \* vec) <br> |
|  SR\_FORCE\_INLINE constexpr | [**Vector3**](#function-vector3-58) (const uint8\_t \* axis) <br> |
|  SR\_FORCE\_INLINE constexpr | [**Vector3**](#function-vector3-68) (T p\_x, T p\_y, T p\_z) <br> |
|  SR\_FORCE\_INLINE constexpr | [**Vector3**](#function-vector3-78) (T p) <br> |
|   | [**Vector3**](#function-vector3-88) (const glm::vec3 & v) <br> |
|  SR\_NODISCARD T | [**X**](#function-x) () noexcept const<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**XY**](#function-xy-13) () const<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**XZ**](#function-xz-13) () const<br> |
|  SR\_NODISCARD T | [**Y**](#function-y) () noexcept const<br> |
|  SR\_NODISCARD [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; T &gt; | [**YZ**](#function-yz-13) () const<br> |
|  SR\_NODISCARD T | [**Z**](#function-z) () noexcept const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**ZeroAxis**](#function-zeroaxis) (Axis axis) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](#function-operator) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator!=**](#function-operator_1) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator%**](#function-operator_2) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator%=**](#function-operator_3) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator\***](#function-operator_4) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator\***](#function-operator_5) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator\*=**](#function-operator_6) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator\*=**](#function-operator_7) (U p\_scalar) <br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) SR\_FASTCALL | [**operator+**](#function-operator_8) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) noexcept const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator+**](#function-operator_9) () const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator+=**](#function-operator_10) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator-**](#function-operator_11) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator-**](#function-operator_12) () const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator-=**](#function-operator_13) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator/**](#function-operator_14) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**operator/**](#function-operator_15) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator/=**](#function-operator_16) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; U &gt; & p\_v) <br> |
|  SR\_FORCE\_INLINE [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator/=**](#function-operator_17) (U p\_scalar) <br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;**](#function-operator_18) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;**](#function-operator_19) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;=**](#function-operator_20) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&lt;=**](#function-operator_21) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](#function-operator_22) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator==**](#function-operator_23) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;**](#function-operator_24) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;**](#function-operator_25) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;=**](#function-operator_26) (U p\_scalar) const<br> |
|  SR\_FORCE\_INLINE bool | [**operator&gt;=**](#function-operator_27) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_v) const<br> |
|  SR\_FORCE\_INLINE constexpr const T & | [**operator[]**](#function-operator_28) (int p\_axis) const<br> |
|  SR\_FORCE\_INLINE constexpr T & | [**operator[]**](#function-operator_29) (int p\_axis) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**AxisByIndex**](#function-axisbyindex) (uint8\_t axis) <br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md) | [**Cross**](#function-cross-22) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_a, const [**Vector3**](structSR__MATH__NS_1_1Vector3.md) & p\_b) <br> |
|  T | [**Dot**](#function-dot-22) ([**Vector3**](structSR__MATH__NS_1_1Vector3.md) lhs, [**Vector3**](structSR__MATH__NS_1_1Vector3.md) rhs) <br> |
|  T | [**FixAxis**](#function-fixaxis) (T axis) <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**Forward**](#function-forward) () <br> |
|  Unit | [**Magnitude**](#function-magnitude) ([**Vector3**](structSR__MATH__NS_1_1Vector3.md) vec) <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**One**](#function-one) () <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**Right**](#function-right) () <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**UnitX**](#function-unitx) () <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**UnitY**](#function-unity) () <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**UnitZ**](#function-unitz) () <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**Up**](#function-up) () <br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XY**](#function-xy-23) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & v, U value) <br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XY**](#function-xy-33) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & v) <br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XZ**](#function-xz-23) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & v, U value) <br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**XZ**](#function-xz-33) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & v) <br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**YZ**](#function-yz-23) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & v, U value) <br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**YZ**](#function-yz-33) (const [**Vector2**](structSR__MATH__NS_1_1Vector2.md)&lt; U &gt; & v) <br> |
|  constexpr [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**Zero**](#function-zero) () <br> |


























## Public Types Documentation




### typedef ValueType 

```C++
using SR_MATH_NS::Vector3< T >::ValueType =  T;
```




<hr>
## Public Attributes Documentation




### variable Vector3 

```C++
union SR_MATH_NS::Vector3 SR_MATH_NS::Vector3< T >;
```




<hr>



### variable coord 

```C++
T SR_MATH_NS::Vector3< T >::coord[3];
```




<hr>



### variable x 

```C++
T SR_MATH_NS::Vector3< T >::x;
```




<hr>



### variable y 

```C++
T SR_MATH_NS::Vector3< T >::y;
```




<hr>



### variable z 

```C++
T SR_MATH_NS::Vector3< T >::z;
```




<hr>
## Public Functions Documentation




### function Abs 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Abs () const
```




<hr>



### function Angle [1/2]

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::Angle (
    const Vector3 & to
) const
```




<hr>



### function Angle [2/2]

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Angle (
    const Vector3 & vector3
) 
```




<hr>



### function AngleAxis 

```C++
inline SR_NODISCARD Quaternion SR_MATH_NS::Vector3::AngleAxis (
    const Vector3 & target,
    const Vector3 & axis=Vector3::UnitZ()
) const
```




<hr>



### function AngleCoefficient 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::AngleCoefficient (
    const Vector3 & vector3
) const
```




<hr>



### function AngleCoefficientEuler 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::AngleCoefficientEuler (
    const Vector3 & vector3
) const
```




<hr>



### function AngleCoefficientRadians 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::AngleCoefficientRadians (
    const Vector3 & vector3
) const
```




<hr>



### function Cast 

```C++
template<typename U>
inline SR_NODISCARD Vector3 < U > SR_FASTCALL SR_MATH_NS::Vector3::Cast () noexcept const
```




<hr>



### function Clamp 

```C++
inline SR_NODISCARD Vector3 < T > SR_MATH_NS::Vector3::Clamp (
    const Vector3 < T > & upper,
    const Vector3 < T > & lover
) const
```




<hr>



### function ContainsNaN 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector3::ContainsNaN () const
```




<hr>



### function Cos 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Cos () const
```




<hr>



### function Cross [1/2]

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Cross (
    const Vector3 & p_b
) const
```




<hr>



### function DeSingular 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::DeSingular (
    const Vector3 & segment
) const
```




<hr>



### function Degrees 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Degrees () noexcept const
```




<hr>



### function Direction 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Direction (
    const Vector3 & point
) const
```




<hr>



### function Distance 

```C++
inline SR_NODISCARD T SR_FASTCALL SR_MATH_NS::Vector3::Distance (
    const Vector3 & point
) const
```




<hr>



### function Dot [1/2]

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::Dot (
    Vector3 p_b
) const
```




<hr>



### function Empty 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector3::Empty () const
```




<hr>



### function FixEulerAngles 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::FixEulerAngles () const
```




<hr>



### function HasZero 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector3::HasZero () const
```




<hr>



### function Inverse 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Inverse () const
```




<hr>



### function InverseAxis 

```C++
inline SR_NODISCARD Vector3 SR_FASTCALL SR_MATH_NS::Vector3::InverseAxis (
    Axis axis
) const
```




<hr>



### function IsEquals 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector3::IsEquals (
    const Vector3 & value,
    Unit tolerance
) noexcept const
```




<hr>



### function IsEqualsLikely 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector3::IsEqualsLikely (
    const Vector3 & value,
    Unit tolerance
) noexcept const
```




<hr>



### function IsFinite 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector3::IsFinite () noexcept const
```




<hr>



### function IsInfinity 

```C++
inline SR_NODISCARD bool SR_MATH_NS::Vector3::IsInfinity () const
```




<hr>



### function Length 

```C++
inline SR_NODISCARD SR_FORCE_INLINE T SR_MATH_NS::Vector3::Length () const
```




<hr>



### function Lerp 

```C++
inline SR_NODISCARD SR_FORCE_INLINE Vector3 SR_FASTCALL SR_MATH_NS::Vector3::Lerp (
    const Vector3 & vector3,
    Unit t
) noexcept const
```




<hr>



### function Limits 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Limits (
    int lim
) const
```




<hr>



### function LookAt 

```C++
inline SR_NODISCARD Quaternion SR_MATH_NS::Vector3::LookAt (
    const Vector3 & target
) const
```




<hr>



### function Max 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::Max () const
```




<hr>



### function Max3 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Max3 () const
```




<hr>



### function Min 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::Min () const
```




<hr>



### function Min3 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Min3 () const
```




<hr>



### function Normalize 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Normalize () const
```




<hr>



### function Normalized 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Normalized () const
```




<hr>



### function ProjectOnPlane 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::ProjectOnPlane (
    const Vector3 & planeNormal
) const
```




<hr>



### function Radians 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Radians () noexcept const
```




<hr>



### function Replace 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Replace (
    int from,
    int to
) const
```




<hr>



### function Rotate 

```C++
SR_NODISCARD Vector3 < T > SR_MATH_NS::Vector3::Rotate (
    const Quaternion & q
) const
```




<hr>



### function Round 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Round () const
```




<hr>



### function SignedAngle 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::SignedAngle (
    const Vector3 & to,
    const Vector3 & axis
) const
```




<hr>



### function Sin 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Sin () const
```




<hr>



### function Singular 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::Singular (
    const Vector3 & segment
) const
```




<hr>



### function SqrMagnitude 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::SqrMagnitude () const
```




<hr>



### function SquaredNorm 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::SquaredNorm () noexcept const
```




<hr>



### function Swap 

```C++
inline SR_NODISCARD Vector3 SR_FASTCALL SR_MATH_NS::Vector3::Swap (
    Axis axis
) const
```




<hr>



### function ToGLM 

```C++
inline SR_NODISCARD glm::vec3 SR_MATH_NS::Vector3::ToGLM () noexcept const
```




<hr>



### function ToQuat 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Vector3::ToQuat () const
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD std::string SR_MATH_NS::Vector3::ToString () const
```




<hr>



### function Vector3 [1/8]

```C++
inline constexpr SR_FORCE_INLINE SR_MATH_NS::Vector3::Vector3 () 
```




<hr>



### function Vector3 [2/8]

```C++
template<typename U>
inline explicit constexpr SR_FORCE_INLINE SR_MATH_NS::Vector3::Vector3 (
    const Vector3 < U > & vec
) 
```




<hr>



### function Vector3 [3/8]

```C++
template<typename U>
inline explicit constexpr SR_FORCE_INLINE SR_MATH_NS::Vector3::Vector3 (
    const Vector2 < U > & vec,
    U value
) 
```




<hr>



### function Vector3 [4/8]

```C++
inline explicit SR_FORCE_INLINE constexpr SR_MATH_NS::Vector3::Vector3 (
    const float * vec
) 
```




<hr>



### function Vector3 [5/8]

```C++
inline explicit SR_FORCE_INLINE constexpr SR_MATH_NS::Vector3::Vector3 (
    const uint8_t * axis
) 
```




<hr>



### function Vector3 [6/8]

```C++
inline SR_FORCE_INLINE constexpr SR_MATH_NS::Vector3::Vector3 (
    T p_x,
    T p_y,
    T p_z
) 
```




<hr>



### function Vector3 [7/8]

```C++
inline SR_FORCE_INLINE constexpr SR_MATH_NS::Vector3::Vector3 (
    T p
) 
```




<hr>



### function Vector3 [8/8]

```C++
inline SR_MATH_NS::Vector3::Vector3 (
    const glm::vec3 & v
) 
```




<hr>



### function X 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::X () noexcept const
```




<hr>



### function XY [1/3]

```C++
inline SR_NODISCARD Vector2 < T > SR_MATH_NS::Vector3::XY () const
```




<hr>



### function XZ [1/3]

```C++
inline SR_NODISCARD Vector2 < T > SR_MATH_NS::Vector3::XZ () const
```




<hr>



### function Y 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::Y () noexcept const
```




<hr>



### function YZ [1/3]

```C++
inline SR_NODISCARD Vector2 < T > SR_MATH_NS::Vector3::YZ () const
```




<hr>



### function Z 

```C++
inline SR_NODISCARD T SR_MATH_NS::Vector3::Z () noexcept const
```




<hr>



### function ZeroAxis 

```C++
inline SR_NODISCARD Vector3 SR_MATH_NS::Vector3::ZeroAxis (
    Axis axis
) const
```




<hr>



### function operator!= 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator!= (
    U p_scalar
) const
```




<hr>



### function operator!= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator!= (
    const Vector3 & p_v
) const
```




<hr>



### function operator% 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator% (
    const Vector3 < U > & p_v
) const
```




<hr>



### function operator%= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 & SR_MATH_NS::Vector3::operator%= (
    const Vector3 < U > & p_v
) 
```




<hr>



### function operator\* 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator* (
    const Vector3 < U > & p_v
) const
```




<hr>



### function operator\* 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator* (
    U p_scalar
) const
```




<hr>



### function operator\*= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 & SR_MATH_NS::Vector3::operator*= (
    const Vector3 < U > & p_v
) 
```




<hr>



### function operator\*= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 & SR_MATH_NS::Vector3::operator*= (
    U p_scalar
) 
```




<hr>



### function operator+ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 SR_FASTCALL SR_MATH_NS::Vector3::operator+ (
    const Vector3 < U > & p_v
) noexcept const
```




<hr>



### function operator+ 

```C++
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator+ () const
```




<hr>



### function operator+= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 & SR_MATH_NS::Vector3::operator+= (
    const Vector3 < U > & p_v
) 
```




<hr>



### function operator- 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator- (
    const Vector3 < U > & p_v
) const
```




<hr>



### function operator- 

```C++
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator- () const
```




<hr>



### function operator-= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 & SR_MATH_NS::Vector3::operator-= (
    const Vector3 < U > & p_v
) 
```




<hr>



### function operator/ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator/ (
    const Vector3 < U > & p_v
) const
```




<hr>



### function operator/ 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 SR_MATH_NS::Vector3::operator/ (
    U p_scalar
) const
```




<hr>



### function operator/= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 & SR_MATH_NS::Vector3::operator/= (
    const Vector3 < U > & p_v
) 
```




<hr>



### function operator/= 

```C++
template<typename U>
inline SR_FORCE_INLINE Vector3 & SR_MATH_NS::Vector3::operator/= (
    U p_scalar
) 
```




<hr>



### function operator&lt; 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator< (
    U p_scalar
) const
```




<hr>



### function operator&lt; 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator< (
    const Vector3 & p_v
) const
```




<hr>



### function operator&lt;= 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator<= (
    U p_scalar
) const
```




<hr>



### function operator&lt;= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator<= (
    const Vector3 & p_v
) const
```




<hr>



### function operator== 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator== (
    U p_scalar
) const
```




<hr>



### function operator== 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator== (
    const Vector3 & p_v
) const
```




<hr>



### function operator&gt; 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator> (
    U p_scalar
) const
```




<hr>



### function operator&gt; 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator> (
    const Vector3 & p_v
) const
```




<hr>



### function operator&gt;= 

```C++
template<typename U>
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator>= (
    U p_scalar
) const
```




<hr>



### function operator&gt;= 

```C++
inline SR_FORCE_INLINE bool SR_MATH_NS::Vector3::operator>= (
    const Vector3 & p_v
) const
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE constexpr const T & SR_MATH_NS::Vector3::operator[] (
    int p_axis
) const
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE constexpr T & SR_MATH_NS::Vector3::operator[] (
    int p_axis
) 
```




<hr>
## Public Static Functions Documentation




### function AxisByIndex 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::AxisByIndex (
    uint8_t axis
) 
```




<hr>



### function Cross [2/2]

```C++
static inline Vector3 SR_MATH_NS::Vector3::Cross (
    const Vector3 & p_a,
    const Vector3 & p_b
) 
```




<hr>



### function Dot [2/2]

```C++
static inline T SR_MATH_NS::Vector3::Dot (
    Vector3 lhs,
    Vector3 rhs
) 
```




<hr>



### function FixAxis 

```C++
static inline T SR_MATH_NS::Vector3::FixAxis (
    T axis
) 
```




<hr>



### function Forward 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::Forward () 
```




<hr>



### function Magnitude 

```C++
static inline Unit SR_MATH_NS::Vector3::Magnitude (
    Vector3 vec
) 
```




<hr>



### function One 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::One () 
```




<hr>



### function Right 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::Right () 
```




<hr>



### function UnitX 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::UnitX () 
```




<hr>



### function UnitY 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::UnitY () 
```




<hr>



### function UnitZ 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::UnitZ () 
```




<hr>



### function Up 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::Up () 
```




<hr>



### function XY [2/3]

```C++
template<typename U>
static inline Vector3 < T > SR_MATH_NS::Vector3::XY (
    const Vector2 < U > & v,
    U value
) 
```




<hr>



### function XY [3/3]

```C++
template<typename U>
static inline Vector3 < T > SR_MATH_NS::Vector3::XY (
    const Vector2 < U > & v
) 
```




<hr>



### function XZ [2/3]

```C++
template<typename U>
static inline Vector3 < T > SR_MATH_NS::Vector3::XZ (
    const Vector2 < U > & v,
    U value
) 
```




<hr>



### function XZ [3/3]

```C++
template<typename U>
static inline Vector3 < T > SR_MATH_NS::Vector3::XZ (
    const Vector2 < U > & v
) 
```




<hr>



### function YZ [2/3]

```C++
template<typename U>
static inline Vector3 < T > SR_MATH_NS::Vector3::YZ (
    const Vector2 < U > & v,
    U value
) 
```




<hr>



### function YZ [3/3]

```C++
template<typename U>
static inline Vector3 < T > SR_MATH_NS::Vector3::YZ (
    const Vector2 < U > & v
) 
```




<hr>



### function Zero 

```C++
static inline constexpr Vector3 < T > SR_MATH_NS::Vector3::Zero () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector3.h`

