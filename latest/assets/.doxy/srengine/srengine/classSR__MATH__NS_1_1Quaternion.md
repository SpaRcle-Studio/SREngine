

# Class SR\_MATH\_NS::Quaternion



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**Quaternion**](#variable-quaternion)  <br> |
|  glm::quat | [**self**](#variable-self)   = `{}`<br> |
|  float\_t | [**w**](#variable-w)  <br> |
|  float\_t | [**x**](#variable-x)  <br> |
|  float\_t | [**y**](#variable-y)  <br> |
|  float\_t | [**z**](#variable-z)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD Unit SR\_FASTCALL | [**Angle**](#function-angle) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) const<br> |
|  SR\_NODISCARD Unit SR\_FASTCALL | [**Distance**](#function-distance) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) const<br> |
|  SR\_NODISCARD [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; | [**EulerAngle**](#function-eulerangle) () const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**Inverse**](#function-inverse) () const<br> |
|  SR\_NODISCARD bool SR\_FASTCALL | [**IsEquals**](#function-isequals) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q, Unit tolerance) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFinite**](#function-isfinite) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsIdentity**](#function-isidentity) () noexcept const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**Normalize**](#function-normalize) () const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**Normalized**](#function-normalized) () const<br> |
|  SR\_NODISCARD Unit | [**Pitch**](#function-pitch) () noexcept const<br> |
|   | [**Quaternion**](#function-quaternion-17) () <br> |
|   | [**Quaternion**](#function-quaternion-27) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & p\_q) <br> |
|   | [**Quaternion**](#function-quaternion-37) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & p\_euler) <br> |
|   | [**Quaternion**](#function-quaternion-47) (const glm::quat & q) <br> |
|   | [**Quaternion**](#function-quaternion-57) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & axis, Unit angle) <br> |
|   | [**Quaternion**](#function-quaternion-67) (const [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & matrix) <br> |
|   | [**Quaternion**](#function-quaternion-77) (T x, T y, T z, T w) <br> |
|  SR\_NODISCARD Unit | [**Roll**](#function-roll) () noexcept const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**Rotate**](#function-rotate) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; T &gt; & v) const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**RotateX**](#function-rotatex) (Unit angle) const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**RotateY**](#function-rotatey) (Unit angle) const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**RotateZ**](#function-rotatez) (Unit angle) const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**Slerp**](#function-slerp) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q, Unit t) const<br> |
|  SR\_NODISCARD Unit | [**SquaredNorm**](#function-squarednorm) () noexcept const<br> |
|  SR\_NODISCARD const glm::quat & | [**ToGLM**](#function-toglm) () noexcept const<br> |
|  SR\_NODISCARD [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**ToMat4x4**](#function-tomat4x4) () const<br> |
|  SR\_NODISCARD glm::mat4 | [**ToMat4x4GLM**](#function-tomat4x4glm) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  SR\_NODISCARD [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; Unit &gt; | [**Vector**](#function-vector) () noexcept const<br> |
|  SR\_NODISCARD T | [**W**](#function-w) () noexcept const<br> |
|  SR\_NODISCARD T | [**X**](#function-x) () noexcept const<br> |
|  SR\_NODISCARD T | [**Y**](#function-y) () noexcept const<br> |
|  SR\_NODISCARD Unit | [**Yaw**](#function-yaw) () noexcept const<br> |
|  SR\_NODISCARD T | [**Z**](#function-z) () noexcept const<br> |
|  bool | [**operator!=**](#function-operator) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) noexcept const<br> |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**operator\***](#function-operator_1) (const double & s) const<br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; | [**operator\***](#function-operator_2) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & v) noexcept const<br> |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**operator\***](#function-operator_3) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rhs) const<br> |
|  void | [**operator\*=**](#function-operator_4) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & p\_q) <br> |
|  void | [**operator\*=**](#function-operator_5) (const double & s) <br> |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**operator+**](#function-operator_6) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q2) const<br> |
|  void | [**operator+=**](#function-operator_7) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & p\_q) <br> |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**operator-**](#function-operator-) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q2) const<br> |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**operator-**](#function-operator-_1) () const<br> |
|  void | [**operator-=**](#function-operator-_2) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & p\_q) <br> |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**operator/**](#function-operator_8) (const double & s) const<br> |
|  [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; | [**operator/**](#function-operator_9) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & v) const<br> |
|  void | [**operator/=**](#function-operator_10) (const double & s) <br> |
|  bool | [**operator==**](#function-operator_11) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) noexcept const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**FromEuler**](#function-fromeuler) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & euler) <br> |
|  [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**Identity**](#function-identity) () <br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**LookAt**](#function-lookat-12) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & direction) <br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**LookAt**](#function-lookat-22) (const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & direction, const [**Vector3**](structSR__MATH__NS_1_1Vector3.md)&lt; Unit &gt; & up) <br> |


























## Public Attributes Documentation




### variable Quaternion 

```C++
union SR_MATH_NS::Quaternion SR_MATH_NS::Quaternion;
```




<hr>



### variable self 

```C++
glm::quat SR_MATH_NS::Quaternion::self;
```




<hr>



### variable w 

```C++
float_t SR_MATH_NS::Quaternion::w;
```




<hr>



### variable x 

```C++
float_t SR_MATH_NS::Quaternion::x;
```




<hr>



### variable y 

```C++
float_t SR_MATH_NS::Quaternion::y;
```




<hr>



### variable z 

```C++
float_t SR_MATH_NS::Quaternion::z;
```




<hr>
## Public Functions Documentation




### function Angle 

```C++
SR_NODISCARD Unit SR_FASTCALL SR_MATH_NS::Quaternion::Angle (
    const Quaternion & q
) const
```




<hr>



### function Distance 

```C++
SR_NODISCARD Unit SR_FASTCALL SR_MATH_NS::Quaternion::Distance (
    const Quaternion & q
) const
```




<hr>



### function EulerAngle 

```C++
SR_NODISCARD Vector3 < T > SR_MATH_NS::Quaternion::EulerAngle () const
```




<hr>



### function Inverse 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::Inverse () const
```




<hr>



### function IsEquals 

```C++
SR_NODISCARD bool SR_FASTCALL SR_MATH_NS::Quaternion::IsEquals (
    const Quaternion & q,
    Unit tolerance
) noexcept const
```




<hr>



### function IsFinite 

```C++
SR_NODISCARD bool SR_MATH_NS::Quaternion::IsFinite () noexcept const
```




<hr>



### function IsIdentity 

```C++
SR_NODISCARD bool SR_MATH_NS::Quaternion::IsIdentity () noexcept const
```




<hr>



### function Normalize 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::Normalize () const
```




<hr>



### function Normalized 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::Normalized () const
```




<hr>



### function Pitch 

```C++
SR_NODISCARD Unit SR_MATH_NS::Quaternion::Pitch () noexcept const
```




<hr>



### function Quaternion [1/7]

```C++
SR_MATH_NS::Quaternion::Quaternion () 
```




<hr>



### function Quaternion [2/7]

```C++
SR_MATH_NS::Quaternion::Quaternion (
    const Quaternion & p_q
) 
```




<hr>



### function Quaternion [3/7]

```C++
SR_MATH_NS::Quaternion::Quaternion (
    const Vector3 < Unit > & p_euler
) 
```




<hr>



### function Quaternion [4/7]

```C++
SR_MATH_NS::Quaternion::Quaternion (
    const glm::quat & q
) 
```




<hr>



### function Quaternion [5/7]

```C++
SR_MATH_NS::Quaternion::Quaternion (
    const Vector3 < Unit > & axis,
    Unit angle
) 
```




<hr>



### function Quaternion [6/7]

```C++
explicit SR_MATH_NS::Quaternion::Quaternion (
    const Matrix4x4 & matrix
) 
```




<hr>



### function Quaternion [7/7]

```C++
explicit SR_MATH_NS::Quaternion::Quaternion (
    T x,
    T y,
    T z,
    T w
) 
```




<hr>



### function Roll 

```C++
SR_NODISCARD Unit SR_MATH_NS::Quaternion::Roll () noexcept const
```




<hr>



### function Rotate 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::Rotate (
    const Vector3 < T > & v
) const
```




<hr>



### function RotateX 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::RotateX (
    Unit angle
) const
```




<hr>



### function RotateY 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::RotateY (
    Unit angle
) const
```




<hr>



### function RotateZ 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::RotateZ (
    Unit angle
) const
```




<hr>



### function Slerp 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::Slerp (
    const Quaternion & q,
    Unit t
) const
```




<hr>



### function SquaredNorm 

```C++
SR_NODISCARD Unit SR_MATH_NS::Quaternion::SquaredNorm () noexcept const
```




<hr>



### function ToGLM 

```C++
SR_NODISCARD const glm::quat & SR_MATH_NS::Quaternion::ToGLM () noexcept const
```




<hr>



### function ToMat4x4 

```C++
SR_NODISCARD Matrix4x4 SR_MATH_NS::Quaternion::ToMat4x4 () const
```




<hr>



### function ToMat4x4GLM 

```C++
SR_NODISCARD glm::mat4 SR_MATH_NS::Quaternion::ToMat4x4GLM () noexcept const
```




<hr>



### function ToString 

```C++
SR_NODISCARD std::string SR_MATH_NS::Quaternion::ToString () const
```




<hr>



### function Vector 

```C++
SR_NODISCARD Vector4 < Unit > SR_MATH_NS::Quaternion::Vector () noexcept const
```




<hr>



### function W 

```C++
SR_NODISCARD T SR_MATH_NS::Quaternion::W () noexcept const
```




<hr>



### function X 

```C++
SR_NODISCARD T SR_MATH_NS::Quaternion::X () noexcept const
```




<hr>



### function Y 

```C++
SR_NODISCARD T SR_MATH_NS::Quaternion::Y () noexcept const
```




<hr>



### function Yaw 

```C++
SR_NODISCARD Unit SR_MATH_NS::Quaternion::Yaw () noexcept const
```




<hr>



### function Z 

```C++
SR_NODISCARD T SR_MATH_NS::Quaternion::Z () noexcept const
```




<hr>



### function operator!= 

```C++
bool SR_MATH_NS::Quaternion::operator!= (
    const Quaternion & q
) noexcept const
```




<hr>



### function operator\* 

```C++
Quaternion SR_MATH_NS::Quaternion::operator* (
    const double & s
) const
```




<hr>



### function operator\* 

```C++
Vector3 < Unit > SR_MATH_NS::Quaternion::operator* (
    const Vector3 < Unit > & v
) noexcept const
```




<hr>



### function operator\* 

```C++
Quaternion SR_MATH_NS::Quaternion::operator* (
    const Quaternion & rhs
) const
```




<hr>



### function operator\*= 

```C++
void SR_MATH_NS::Quaternion::operator*= (
    const Quaternion & p_q
) 
```




<hr>



### function operator\*= 

```C++
void SR_MATH_NS::Quaternion::operator*= (
    const double & s
) 
```




<hr>



### function operator+ 

```C++
Quaternion SR_MATH_NS::Quaternion::operator+ (
    const Quaternion & q2
) const
```




<hr>



### function operator+= 

```C++
void SR_MATH_NS::Quaternion::operator+= (
    const Quaternion & p_q
) 
```




<hr>



### function operator- 

```C++
Quaternion SR_MATH_NS::Quaternion::operator- (
    const Quaternion & q2
) const
```




<hr>



### function operator- 

```C++
Quaternion SR_MATH_NS::Quaternion::operator- () const
```




<hr>



### function operator-= 

```C++
void SR_MATH_NS::Quaternion::operator-= (
    const Quaternion & p_q
) 
```




<hr>



### function operator/ 

```C++
Quaternion SR_MATH_NS::Quaternion::operator/ (
    const double & s
) const
```




<hr>



### function operator/ 

```C++
Vector3 < Unit > SR_MATH_NS::Quaternion::operator/ (
    const Vector3 < Unit > & v
) const
```




<hr>



### function operator/= 

```C++
void SR_MATH_NS::Quaternion::operator/= (
    const double & s
) 
```




<hr>



### function operator== 

```C++
bool SR_MATH_NS::Quaternion::operator== (
    const Quaternion & q
) noexcept const
```




<hr>
## Public Static Functions Documentation




### function FromEuler 

```C++
static Quaternion SR_MATH_NS::Quaternion::FromEuler (
    const Vector3 < Unit > & euler
) 
```




<hr>



### function Identity 

```C++
static Quaternion SR_MATH_NS::Quaternion::Identity () 
```




<hr>



### function LookAt [1/2]

```C++
static SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::LookAt (
    const Vector3 < Unit > & direction
) 
```




<hr>



### function LookAt [2/2]

```C++
static SR_NODISCARD Quaternion SR_MATH_NS::Quaternion::LookAt (
    const Vector3 < Unit > & direction,
    const Vector3 < Unit > & up
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Math/Quaternion.h`

