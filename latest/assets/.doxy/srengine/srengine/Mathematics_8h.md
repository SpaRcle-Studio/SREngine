

# File Mathematics.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**Math**](dir_f20ff43999c2f98e3f122645c07885db.md) **>** [**Mathematics.h**](Mathematics_8h.md)

[Go to the source code of this file](Mathematics_8h_source.md)



* `#include <Utils/stdInclude.h>`
* `#include <glm/glm.hpp>`
* `#include <glm/gtc/type_ptr.hpp>`
* `#include <glm/gtx/string_cast.hpp>`
* `#include <glm/gtc/quaternion.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) <br> |



















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**CMP\_BIG\_EPSILON**](Mathematics_8h.md#define-cmp_big_epsilon)  `(0.001)`<br> |
| define  | [**CMP\_EPSILON**](Mathematics_8h.md#define-cmp_epsilon)  `(0.00001)`<br> |
| define  | [**CMP\_EPSILON2**](Mathematics_8h.md#define-cmp_epsilon2)  `(CMP\_EPSILON \* CMP\_EPSILON)`<br> |
| define  | [**CMP\_NORMALIZE\_TOLERANCE**](Mathematics_8h.md#define-cmp_normalize_tolerance)  `(0.000001)`<br> |
| define  | [**CMP\_POINT\_IN\_PLANE\_EPSILON**](Mathematics_8h.md#define-cmp_point_in_plane_epsilon)  `(0.00001)`<br> |
| define  | [**DEG**](Mathematics_8h.md#define-deg) (x) `(x \* (180.0 / SR\_PI))`<br> |
| define  | [**DEG3**](Mathematics_8h.md#define-deg3) (v) `glm::vec3(DEG(v.x), DEG(v.y), DEG(v.z))`<br> |
| define  | [**Deg180InRad**](Mathematics_8h.md#define-deg180inrad)  `((SR\_MATH\_NS::Unit)M\_PI)`<br> |
| define  | [**Deg90InRad**](Mathematics_8h.md#define-deg90inrad)  `((SR\_MATH\_NS::Unit)RAD(90.0))`<br> |
| define  | [**DegreesToRad**](Mathematics_8h.md#define-degreestorad) (angle) `(angle \* M\_PI / 180)`<br> |
| define  | [**M\_PI**](Mathematics_8h.md#define-m_pi)  `(std::numbers::pi)`<br> |
| define  | [**Math\_E**](Mathematics_8h.md#define-math_e)  `(2.7182818284590452353602874714)`<br> |
| define  | [**Math\_INF**](Mathematics_8h.md#define-math_inf)  `(INFINITY)`<br> |
| define  | [**Math\_LN2**](Mathematics_8h.md#define-math_ln2)  `(0.6931471805599453094172321215)`<br> |
| define  | [**Math\_SQRT12**](Mathematics_8h.md#define-math_sqrt12)  `(0.7071067811865475244008443621048490)`<br> |
| define  | [**Math\_SQRT2**](Mathematics_8h.md#define-math_sqrt2)  `(1.4142135623730950488016887242)`<br> |
| define  | [**Math\_TAU**](Mathematics_8h.md#define-math_tau)  `(6.2831853071795864769252867666)`<br> |
| define  | [**RAD**](Mathematics_8h.md#define-rad) (x) `(x \* (SR\_PI / 180.0))`<br> |
| define  | [**RAD3**](Mathematics_8h.md#define-rad3) (v) `glm::vec3(RAD(v.x), RAD(v.y), RAD(v.z))`<br> |
| define  | [**RadToDegrees**](Mathematics_8h.md#define-radtodegrees) (angle) `(angle \* 180 / M\_PI)`<br> |
| define  | [**SR\_ABS**](Mathematics_8h.md#define-sr_abs) (x) `(SR\_MATH\_NS::Abs(x))`<br> |
| define  | [**SR\_ARC\_COS**](Mathematics_8h.md#define-sr_arc_cos) (x) `std::acos(x)`<br> |
| define  | [**SR\_ARC\_SIN**](Mathematics_8h.md#define-sr_arc_sin) (x) `std::asin(x)`<br> |
| define  | [**SR\_BIG\_EPSILON**](Mathematics_8h.md#define-sr_big_epsilon)  `(0.001)`<br> |
| define  | [**SR\_CLAMP**](Mathematics_8h.md#define-sr_clamp) (x, lower, upper) `(SR\_MIN(upper, SR\_MAX(x, lower)))`<br> |
| define  | [**SR\_COS**](Mathematics_8h.md#define-sr_cos) (x) `std::cos(x)`<br> |
| define  | [**SR\_DEG**](Mathematics_8h.md#define-sr_deg) (x) `(x \* (180.0 / SR\_PI))`<br> |
| define  | [**SR\_DEG\_2\_RAD**](Mathematics_8h.md#define-sr_deg_2_rad)  `(SR\_PI \* 2.f / 360.f)`<br> |
| define  | [**SR\_DOUBLE\_MAX**](Mathematics_8h.md#define-sr_double_max)  `std::numeric\_limits&lt;double\_t&gt;::max()`<br> |
| define  | [**SR\_EARTH\_GRAVITY\_CONST**](Mathematics_8h.md#define-sr_earth_gravity_const)  `(9.81)`<br> |
| define  | [**SR\_EPSILON**](Mathematics_8h.md#define-sr_epsilon)  `(0.00001)`<br> |
| define  | [**SR\_EPSILON\_NORMAL\_SQRT**](Mathematics_8h.md#define-sr_epsilon_normal_sqrt)  `(1e-15)`<br> |
| define  | [**SR\_EQUALS**](Mathematics_8h.md#define-sr_equals) (a, b) `(SR\_MATH\_NS::IsEquals(a, b))`<br> |
| define  | [**SR\_EQUALS\_T**](Mathematics_8h.md#define-sr_equals_t) (a, b, tolerance) `(SR\_MATH\_NS::IsEquals(a, b, tolerance))`<br> |
| define  | [**SR\_FLOAT\_MAX**](Mathematics_8h.md#define-sr_float_max)  `std::numeric\_limits&lt;float\_t&gt;::max()`<br> |
| define  | [**SR\_INF**](Mathematics_8h.md#define-sr_inf)  `std::numeric\_limits&lt;double\_t&gt;::infinity()`<br> |
| define  | [**SR\_INT16\_MAX**](Mathematics_8h.md#define-sr_int16_max)  `std::numeric\_limits&lt;int16\_t&gt;::max()`<br> |
| define  | [**SR\_INT32\_MAX**](Mathematics_8h.md#define-sr_int32_max)  `std::numeric\_limits&lt;int32\_t&gt;::max()`<br> |
| define  | [**SR\_INT32\_MIN**](Mathematics_8h.md#define-sr_int32_min)  `std::numeric\_limits&lt;int32\_t&gt;::min()`<br> |
| define  | [**SR\_INT64\_MAX**](Mathematics_8h.md#define-sr_int64_max)  `std::numeric\_limits&lt;int64\_t&gt;::max()`<br> |
| define  | [**SR\_INT8\_MAX**](Mathematics_8h.md#define-sr_int8_max)  `std::numeric\_limits&lt;int8\_t&gt;::max()`<br> |
| define  | [**SR\_LARGE\_EPSILON**](Mathematics_8h.md#define-sr_large_epsilon)  `(0.00005)`<br> |
| define  | [**SR\_MAX**](Mathematics_8h.md#define-sr_max) (a, b) `(a &gt; b ? a : b)`<br> |
| define  | [**SR\_MIN**](Mathematics_8h.md#define-sr_min) (a, b) `(a &lt; b ? a : b)`<br> |
| define  | [**SR\_NAN**](Mathematics_8h.md#define-sr_nan)  `NAN`<br> |
| define  | [**SR\_PI**](Mathematics_8h.md#define-sr_pi)  `M\_PI`<br> |
| define  | [**SR\_POW**](Mathematics_8h.md#define-sr_pow) (x, n) `std::pow(x, n)`<br> |
| define  | [**SR\_RAD**](Mathematics_8h.md#define-sr_rad) (x) `(x \* (SR\_PI / 180.0))`<br> |
| define  | [**SR\_RAD\_2\_DEG**](Mathematics_8h.md#define-sr_rad_2_deg)  `(1.f / SR\_DEG\_2\_RAD)`<br> |
| define  | [**SR\_SIN**](Mathematics_8h.md#define-sr_sin) (x) `std::sin(x)`<br> |
| define  | [**SR\_SQRT**](Mathematics_8h.md#define-sr_sqrt) (x) `std::sqrt(x)`<br> |
| define  | [**SR\_SQUARE**](Mathematics_8h.md#define-sr_square) (value) `(value \* value)`<br> |
| define  | [**SR\_UINT16\_MAX**](Mathematics_8h.md#define-sr_uint16_max)  `std::numeric\_limits&lt;uint16\_t&gt;::max()`<br> |
| define  | [**SR\_UINT32\_MAX**](Mathematics_8h.md#define-sr_uint32_max)  `std::numeric\_limits&lt;uint32\_t&gt;::max()`<br> |
| define  | [**SR\_UINT64\_MAX**](Mathematics_8h.md#define-sr_uint64_max)  `std::numeric\_limits&lt;uint64\_t&gt;::max()`<br> |
| define  | [**SR\_UINT8\_MAX**](Mathematics_8h.md#define-sr_uint8_max)  `std::numeric\_limits&lt;uint8\_t&gt;::max()`<br> |
| define  | [**SR\_UINTPTR\_MAX**](Mathematics_8h.md#define-sr_uintptr_max)  `std::numeric\_limits&lt;uintptr\_t&gt;::max()`<br> |
| define  | [**UNIT\_EPSILON**](Mathematics_8h.md#define-unit_epsilon)  `(0.00001)`<br> |

## Macro Definition Documentation





### define CMP\_BIG\_EPSILON 

```C++
#define CMP_BIG_EPSILON `(0.001)`
```




<hr>



### define CMP\_EPSILON 

```C++
#define CMP_EPSILON `(0.00001)`
```




<hr>



### define CMP\_EPSILON2 

```C++
#define CMP_EPSILON2 `(CMP_EPSILON * CMP_EPSILON)`
```




<hr>



### define CMP\_NORMALIZE\_TOLERANCE 

```C++
#define CMP_NORMALIZE_TOLERANCE `(0.000001)`
```




<hr>



### define CMP\_POINT\_IN\_PLANE\_EPSILON 

```C++
#define CMP_POINT_IN_PLANE_EPSILON `(0.00001)`
```




<hr>



### define DEG 

```C++
#define DEG (
    x
) `(x * (180.0 / SR_PI))`
```




<hr>



### define DEG3 

```C++
#define DEG3 (
    v
) `glm::vec3(DEG(v.x), DEG(v.y), DEG(v.z))`
```




<hr>



### define Deg180InRad 

```C++
#define Deg180InRad `((SR_MATH_NS::Unit)M_PI)`
```




<hr>



### define Deg90InRad 

```C++
#define Deg90InRad `((SR_MATH_NS::Unit)RAD(90.0))`
```




<hr>



### define DegreesToRad 

```C++
#define DegreesToRad (
    angle
) `(angle * M_PI / 180)`
```




<hr>



### define M\_PI 

```C++
#define M_PI `(std::numbers::pi)`
```




<hr>



### define Math\_E 

```C++
#define Math_E `(2.7182818284590452353602874714)`
```




<hr>



### define Math\_INF 

```C++
#define Math_INF `(INFINITY)`
```




<hr>



### define Math\_LN2 

```C++
#define Math_LN2 `(0.6931471805599453094172321215)`
```




<hr>



### define Math\_SQRT12 

```C++
#define Math_SQRT12 `(0.7071067811865475244008443621048490)`
```




<hr>



### define Math\_SQRT2 

```C++
#define Math_SQRT2 `(1.4142135623730950488016887242)`
```




<hr>



### define Math\_TAU 

```C++
#define Math_TAU `(6.2831853071795864769252867666)`
```




<hr>



### define RAD 

```C++
#define RAD (
    x
) `(x * (SR_PI / 180.0))`
```




<hr>



### define RAD3 

```C++
#define RAD3 (
    v
) `glm::vec3(RAD(v.x), RAD(v.y), RAD(v.z))`
```




<hr>



### define RadToDegrees 

```C++
#define RadToDegrees (
    angle
) `(angle * 180 / M_PI)`
```




<hr>



### define SR\_ABS 

```C++
#define SR_ABS (
    x
) `(SR_MATH_NS::Abs(x))`
```




<hr>



### define SR\_ARC\_COS 

```C++
#define SR_ARC_COS (
    x
) `std::acos(x)`
```




<hr>



### define SR\_ARC\_SIN 

```C++
#define SR_ARC_SIN (
    x
) `std::asin(x)`
```




<hr>



### define SR\_BIG\_EPSILON 

```C++
#define SR_BIG_EPSILON `(0.001)`
```




<hr>



### define SR\_CLAMP 

```C++
#define SR_CLAMP (
    x,
    lower,
    upper
) `(SR_MIN(upper, SR_MAX(x, lower)))`
```




<hr>



### define SR\_COS 

```C++
#define SR_COS (
    x
) `std::cos(x)`
```




<hr>



### define SR\_DEG 

```C++
#define SR_DEG (
    x
) `(x * (180.0 / SR_PI))`
```




<hr>



### define SR\_DEG\_2\_RAD 

```C++
#define SR_DEG_2_RAD `(SR_PI * 2.f / 360.f)`
```




<hr>



### define SR\_DOUBLE\_MAX 

```C++
#define SR_DOUBLE_MAX `std::numeric_limits<double_t>::max()`
```




<hr>



### define SR\_EARTH\_GRAVITY\_CONST 

```C++
#define SR_EARTH_GRAVITY_CONST `(9.81)`
```




<hr>



### define SR\_EPSILON 

```C++
#define SR_EPSILON `(0.00001)`
```




<hr>



### define SR\_EPSILON\_NORMAL\_SQRT 

```C++
#define SR_EPSILON_NORMAL_SQRT `(1e-15)`
```




<hr>



### define SR\_EQUALS 

```C++
#define SR_EQUALS (
    a,
    b
) `(SR_MATH_NS::IsEquals(a, b))`
```




<hr>



### define SR\_EQUALS\_T 

```C++
#define SR_EQUALS_T (
    a,
    b,
    tolerance
) `(SR_MATH_NS::IsEquals(a, b, tolerance))`
```




<hr>



### define SR\_FLOAT\_MAX 

```C++
#define SR_FLOAT_MAX `std::numeric_limits<float_t>::max()`
```




<hr>



### define SR\_INF 

```C++
#define SR_INF `std::numeric_limits<double_t>::infinity()`
```




<hr>



### define SR\_INT16\_MAX 

```C++
#define SR_INT16_MAX `std::numeric_limits<int16_t>::max()`
```




<hr>



### define SR\_INT32\_MAX 

```C++
#define SR_INT32_MAX `std::numeric_limits<int32_t>::max()`
```




<hr>



### define SR\_INT32\_MIN 

```C++
#define SR_INT32_MIN `std::numeric_limits<int32_t>::min()`
```




<hr>



### define SR\_INT64\_MAX 

```C++
#define SR_INT64_MAX `std::numeric_limits<int64_t>::max()`
```




<hr>



### define SR\_INT8\_MAX 

```C++
#define SR_INT8_MAX `std::numeric_limits<int8_t>::max()`
```




<hr>



### define SR\_LARGE\_EPSILON 

```C++
#define SR_LARGE_EPSILON `(0.00005)`
```




<hr>



### define SR\_MAX 

```C++
#define SR_MAX (
    a,
    b
) `(a > b ? a : b)`
```




<hr>



### define SR\_MIN 

```C++
#define SR_MIN (
    a,
    b
) `(a < b ? a : b)`
```




<hr>



### define SR\_NAN 

```C++
#define SR_NAN `NAN`
```




<hr>



### define SR\_PI 

```C++
#define SR_PI `M_PI`
```




<hr>



### define SR\_POW 

```C++
#define SR_POW (
    x,
    n
) `std::pow(x, n)`
```




<hr>



### define SR\_RAD 

```C++
#define SR_RAD (
    x
) `(x * (SR_PI / 180.0))`
```




<hr>



### define SR\_RAD\_2\_DEG 

```C++
#define SR_RAD_2_DEG `(1.f / SR_DEG_2_RAD)`
```




<hr>



### define SR\_SIN 

```C++
#define SR_SIN (
    x
) `std::sin(x)`
```




<hr>



### define SR\_SQRT 

```C++
#define SR_SQRT (
    x
) `std::sqrt(x)`
```




<hr>



### define SR\_SQUARE 

```C++
#define SR_SQUARE (
    value
) `(value * value)`
```




<hr>



### define SR\_UINT16\_MAX 

```C++
#define SR_UINT16_MAX `std::numeric_limits<uint16_t>::max()`
```




<hr>



### define SR\_UINT32\_MAX 

```C++
#define SR_UINT32_MAX `std::numeric_limits<uint32_t>::max()`
```




<hr>



### define SR\_UINT64\_MAX 

```C++
#define SR_UINT64_MAX `std::numeric_limits<uint64_t>::max()`
```




<hr>



### define SR\_UINT8\_MAX 

```C++
#define SR_UINT8_MAX `std::numeric_limits<uint8_t>::max()`
```




<hr>



### define SR\_UINTPTR\_MAX 

```C++
#define SR_UINTPTR_MAX `std::numeric_limits<uintptr_t>::max()`
```




<hr>



### define UNIT\_EPSILON 

```C++
#define UNIT_EPSILON `(0.00001)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Math/Mathematics.h`

