

# Class SR\_MATH\_NS::Matrix4x4



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Matrix4x4**](#variable-matrix4x4)  <br> |
|  [**SR\_MATH\_NS::Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; float\_t &gt; | [**dir**](#variable-dir)  <br> |
|  float\_t | [**m**](#variable-m)  <br> |
|  float\_t | [**m00**](#variable-m00)  <br> |
|  float\_t | [**m01**](#variable-m01)  <br> |
|  float\_t | [**m02**](#variable-m02)  <br> |
|  float\_t | [**m03**](#variable-m03)  <br> |
|  float\_t | [**m10**](#variable-m10)  <br> |
|  float\_t | [**m11**](#variable-m11)  <br> |
|  float\_t | [**m12**](#variable-m12)  <br> |
|  float\_t | [**m13**](#variable-m13)  <br> |
|  float\_t | [**m20**](#variable-m20)  <br> |
|  float\_t | [**m21**](#variable-m21)  <br> |
|  float\_t | [**m22**](#variable-m22)  <br> |
|  float\_t | [**m23**](#variable-m23)  <br> |
|  float\_t | [**m30**](#variable-m30)  <br> |
|  float\_t | [**m31**](#variable-m31)  <br> |
|  float\_t | [**m32**](#variable-m32)  <br> |
|  float\_t | [**m33**](#variable-m33)  <br> |
|  float\_t | [**mm**](#variable-mm)  <br> |
|  [**SR\_MATH\_NS::Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; float\_t &gt; | [**position**](#variable-position)  <br> |
|  [**SR\_MATH\_NS::Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; float\_t &gt; | [**right**](#variable-right)  <br> |
|  glm::mat4 | [**self**](#variable-self)  <br> |
|  [**SR\_MATH\_NS::Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; float\_t &gt; | [**up**](#variable-up)  <br> |
|  struct [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**v**](#variable-v)  <br> |
|  [**SR\_MATH\_NS::Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; float\_t &gt; | [**value**](#variable-value)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Decompose**](#function-decompose-15) ([**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translation, [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale) const<br> |
|  bool | [**Decompose**](#function-decompose-25) ([**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translation, [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) const<br> |
|  bool | [**Decompose**](#function-decompose-35) ([**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translation, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & eulers, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale) const<br> |
|  bool | [**Decompose**](#function-decompose-45) ([**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translation, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & eulers, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & skew) const<br> |
|  bool | [**Decompose**](#function-decompose-55) ([**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translation, [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rotation, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale, [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & skew) const<br> |
|  SR\_NODISCARD [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**Forward**](#function-forward) () const<br> |
|  SR\_NODISCARD [**FVector4**](structSR__MATH__NS_1_1Vector4.md) | [**GetAxis**](#function-getaxis) (Axis axis) const<br> |
|  SR\_NODISCARD [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**GetEulers**](#function-geteulers) () const<br> |
|  SR\_NODISCARD [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**GetQuat**](#function-getquat) () const<br> |
|  SR\_NODISCARD [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**GetScale**](#function-getscale) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::Unit | [**GetSegmentLengthClipSpace**](#function-getsegmentlengthclipspace) (const SR\_MATH\_NS::FVector3 & start, const SR\_MATH\_NS::FVector3 & end, SR\_MATH\_NS::Unit displayRatio) const<br> |
|  SR\_NODISCARD [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**GetTranslate**](#function-gettranslate) () const<br> |
|  SR\_NODISCARD [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Inverse**](#function-inverse) () const<br> |
|  SR\_NODISCARD bool | [**IsFinite**](#function-isfinite) () const<br> |
|   | [**Matrix4x4**](#function-matrix4x4-110) () noexcept<br> |
|   | [**Matrix4x4**](#function-matrix4x4-210) ([**FVector4**](structSR__MATH__NS_1_1Vector4.md) rows) noexcept<br> |
|   | [**Matrix4x4**](#function-matrix4x4-310) (const Unit & scalar) noexcept<br>_NOLINT._  |
|   | [**Matrix4x4**](#function-matrix4x4-410) (const glm::mat4 & mat) noexcept<br>_NOLINT._  |
|   | [**Matrix4x4**](#function-matrix4x4-510) (glm::mat4 && mat) noexcept<br>_NOLINT._  |
|   | [**Matrix4x4**](#function-matrix4x4-610) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translate, const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rotation) noexcept<br>_NOLINT._  |
|   | [**Matrix4x4**](#function-matrix4x4-710) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translate, const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale) noexcept<br> |
|   | [**Matrix4x4**](#function-matrix4x4-810) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translate, const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rotation, const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale) noexcept<br> |
|   | [**Matrix4x4**](#function-matrix4x4-910) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rotation, const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale) noexcept<br> |
|   | [**Matrix4x4**](#function-matrix4x4-1010) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translate, const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rotation, const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale, const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & skew) noexcept<br> |
|  SR\_NODISCARD [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**OrthogonalNormalize**](#function-orthogonalnormalize) () const<br> |
|  SR\_NODISCARD [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**Right**](#function-right) () const<br> |
|  SR\_NODISCARD [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Rotate**](#function-rotate-12) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & angle) const<br> |
|  SR\_NODISCARD [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Rotate**](#function-rotate-22) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & q) const<br> |
|  SR\_NODISCARD [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**RotateAxis**](#function-rotateaxis) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & axis, const double & angle) const<br> |
|   | [**SR\_DEPRECATED\_EX**](#function-sr_deprecated_ex) ("FromQuaternion") const<br> |
|  SR\_NODISCARD const glm::mat4 & | [**ToGLM**](#function-toglm) () const<br> |
|  SR\_NODISCARD [**FVector4**](structSR__MATH__NS_1_1Vector4.md) | [**TransformPoint**](#function-transformpoint) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & point) const<br> |
|  SR\_NODISCARD [**FVector4**](structSR__MATH__NS_1_1Vector4.md) | [**TransformVector**](#function-transformvector-12) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & point) const<br> |
|  SR\_NODISCARD [**FVector4**](structSR__MATH__NS_1_1Vector4.md) | [**TransformVector**](#function-transformvector-22) (const [**FVector4**](structSR__MATH__NS_1_1Vector4.md) & point) const<br> |
|  SR\_NODISCARD [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Translate**](#function-translate) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & vec3) const<br> |
|  SR\_NODISCARD [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**Up**](#function-up) () const<br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**operator\***](#function-operator) (const [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & mat) const<br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**operator\***](#function-operator_1) (const Unit & scalar) const<br> |
|  [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; | [**operator\***](#function-operator_2) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & vector4) const<br> |
|  void | [**operator\*=**](#function-operator_3) (const [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & right) <br> |
|  void | [**operator\*=**](#function-operator_4) (const Unit & scalar) <br> |
|  void | [**operator\*=**](#function-operator_5) (const [**Vector4**](structSR__MATH__NS_1_1Vector4.md)&lt; U &gt; & vector4) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**operator+**](#function-operator_6) (const [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & mat) const<br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**operator+**](#function-operator_7) ([**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) mat) <br> |
|  void | [**operator+=**](#function-operator_8) (const [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & right) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**operator-**](#function-operator-) ([**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) mat) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**operator/**](#function-operator_9) ([**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) mat) <br> |
|  const SR\_MATH\_NS::FVector4 & | [**operator[]**](#function-operator_10) (int32\_t row) const<br> |
|  SR\_MATH\_NS::FVector4 & | [**operator[]**](#function-operator_11) (int32\_t row) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**CreateOrthographicOffCenter**](#function-createorthographicoffcenter) (Unit left, Unit right, Unit bottom, Unit top, Unit zNear, Unit zFar) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**CreateTRS**](#function-createtrs) (const SR\_MATH\_NS::FVector3 & translation, const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & rotation, const SR\_MATH\_NS::FVector3 & scale) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**CreateViewMat**](#function-createviewmat) (Unit pitch=0, Unit yaw=0, Unit roll=0) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**FromEulers**](#function-fromeulers) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & eulers) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**FromQuaternion**](#function-fromquaternion) (const [**Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & quaternion) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**FromScale**](#function-fromscale) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & scale) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**FromTranslate**](#function-fromtranslate) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & translation) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Identity**](#function-identity) () <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**LookAt**](#function-lookat) (const SR\_MATH\_NS::FVector3 & eye, const SR\_MATH\_NS::FVector3 & center, const SR\_MATH\_NS::FVector3 & up) <br> |
|  void SR\_FASTCALL | [**Multiply**](#function-multiply) ([**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & result, const [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & left, const [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & right) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Ortho**](#function-ortho) (Unit left, Unit right, Unit bottom, Unit top, Unit zNear, Unit zFar) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**Perspective**](#function-perspective) (float\_t FOV, float\_t aspect, float\_t nearValue, float\_t farValue) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**RotationAxis**](#function-rotationaxis-12) (const SR\_MATH\_NS::FVector4 & axis, Unit angle) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**RotationAxis**](#function-rotationaxis-22) (const SR\_MATH\_NS::FVector3 & axis, Unit angle) <br> |
|  [**Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**RotationYawPitchRoll**](#function-rotationyawpitchroll) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & angles) <br> |


























## Public Attributes Documentation




### variable Matrix4x4 

```C++
union SR_MATH_NS::Matrix4x4 SR_MATH_NS::Matrix4x4;
```



NOLINT 


        

<hr>



### variable dir 

```C++
SR_MATH_NS::Vector4<float_t> SR_MATH_NS::Matrix4x4::dir;
```




<hr>



### variable m 

```C++
float_t SR_MATH_NS::Matrix4x4::m[4][4];
```




<hr>



### variable m00 

```C++
float_t SR_MATH_NS::Matrix4x4::m00;
```




<hr>



### variable m01 

```C++
float_t SR_MATH_NS::Matrix4x4::m01;
```




<hr>



### variable m02 

```C++
float_t SR_MATH_NS::Matrix4x4::m02;
```




<hr>



### variable m03 

```C++
float_t SR_MATH_NS::Matrix4x4::m03;
```




<hr>



### variable m10 

```C++
float_t SR_MATH_NS::Matrix4x4::m10;
```




<hr>



### variable m11 

```C++
float_t SR_MATH_NS::Matrix4x4::m11;
```




<hr>



### variable m12 

```C++
float_t SR_MATH_NS::Matrix4x4::m12;
```




<hr>



### variable m13 

```C++
float_t SR_MATH_NS::Matrix4x4::m13;
```




<hr>



### variable m20 

```C++
float_t SR_MATH_NS::Matrix4x4::m20;
```




<hr>



### variable m21 

```C++
float_t SR_MATH_NS::Matrix4x4::m21;
```




<hr>



### variable m22 

```C++
float_t SR_MATH_NS::Matrix4x4::m22;
```




<hr>



### variable m23 

```C++
float_t SR_MATH_NS::Matrix4x4::m23;
```




<hr>



### variable m30 

```C++
float_t SR_MATH_NS::Matrix4x4::m30;
```




<hr>



### variable m31 

```C++
float_t SR_MATH_NS::Matrix4x4::m31;
```




<hr>



### variable m32 

```C++
float_t SR_MATH_NS::Matrix4x4::m32;
```




<hr>



### variable m33 

```C++
float_t SR_MATH_NS::Matrix4x4::m33;
```




<hr>



### variable mm 

```C++
float_t SR_MATH_NS::Matrix4x4::mm[16];
```




<hr>



### variable position 

```C++
SR_MATH_NS::Vector4<float_t> SR_MATH_NS::Matrix4x4::position;
```




<hr>



### variable right 

```C++
SR_MATH_NS::Vector4<float_t> SR_MATH_NS::Matrix4x4::right;
```




<hr>



### variable self 

```C++
glm::mat4 SR_MATH_NS::Matrix4x4::self;
```




<hr>



### variable up 

```C++
SR_MATH_NS::Vector4<float_t> SR_MATH_NS::Matrix4x4::up;
```




<hr>



### variable v 

```C++
struct SR_MATH_NS::Matrix4x4 SR_MATH_NS::Matrix4x4::v;
```




<hr>



### variable value 

```C++
SR_MATH_NS::Vector4<float_t> SR_MATH_NS::Matrix4x4::value[4];
```




<hr>
## Public Functions Documentation




### function Decompose [1/5]

```C++
bool SR_MATH_NS::Matrix4x4::Decompose (
    FVector3 & translation,
    Quaternion & quaternion,
    FVector3 & scale
) const
```




<hr>



### function Decompose [2/5]

```C++
bool SR_MATH_NS::Matrix4x4::Decompose (
    FVector3 & translation,
    Quaternion & quaternion
) const
```




<hr>



### function Decompose [3/5]

```C++
bool SR_MATH_NS::Matrix4x4::Decompose (
    FVector3 & translation,
    FVector3 & eulers,
    FVector3 & scale
) const
```




<hr>



### function Decompose [4/5]

```C++
bool SR_MATH_NS::Matrix4x4::Decompose (
    FVector3 & translation,
    FVector3 & eulers,
    FVector3 & scale,
    FVector3 & skew
) const
```




<hr>



### function Decompose [5/5]

```C++
bool SR_MATH_NS::Matrix4x4::Decompose (
    FVector3 & translation,
    Quaternion & rotation,
    FVector3 & scale,
    FVector3 & skew
) const
```




<hr>



### function Forward 

```C++
SR_NODISCARD FVector3 SR_MATH_NS::Matrix4x4::Forward () const
```




<hr>



### function GetAxis 

```C++
SR_NODISCARD FVector4 SR_MATH_NS::Matrix4x4::GetAxis (
    Axis axis
) const
```




<hr>



### function GetEulers 

```C++
SR_NODISCARD FVector3 SR_MATH_NS::Matrix4x4::GetEulers () const
```




<hr>



### function GetQuat 

```C++
SR_NODISCARD Quaternion SR_MATH_NS::Matrix4x4::GetQuat () const
```




<hr>



### function GetScale 

```C++
SR_NODISCARD FVector3 SR_MATH_NS::Matrix4x4::GetScale () const
```




<hr>



### function GetSegmentLengthClipSpace 

```C++
SR_NODISCARD SR_MATH_NS::Unit SR_MATH_NS::Matrix4x4::GetSegmentLengthClipSpace (
    const SR_MATH_NS::FVector3 & start,
    const SR_MATH_NS::FVector3 & end,
    SR_MATH_NS::Unit displayRatio
) const
```




<hr>



### function GetTranslate 

```C++
SR_NODISCARD FVector3 SR_MATH_NS::Matrix4x4::GetTranslate () const
```




<hr>



### function Inverse 

```C++
SR_NODISCARD Matrix4x4 SR_MATH_NS::Matrix4x4::Inverse () const
```




<hr>



### function IsFinite 

```C++
SR_NODISCARD bool SR_MATH_NS::Matrix4x4::IsFinite () const
```




<hr>



### function Matrix4x4 [1/10]

```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 () noexcept
```




<hr>



### function Matrix4x4 [2/10]

```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    FVector4 rows
) noexcept
```




<hr>



### function Matrix4x4 [3/10]

_NOLINT._ 
```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    const Unit & scalar
) noexcept
```




<hr>



### function Matrix4x4 [4/10]

_NOLINT._ 
```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    const glm::mat4 & mat
) noexcept
```




<hr>



### function Matrix4x4 [5/10]

_NOLINT._ 
```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    glm::mat4 && mat
) noexcept
```




<hr>



### function Matrix4x4 [6/10]

_NOLINT._ 
```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    const FVector3 & translate,
    const Quaternion & rotation
) noexcept
```




<hr>



### function Matrix4x4 [7/10]

```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    const FVector3 & translate,
    const FVector3 & scale
) noexcept
```




<hr>



### function Matrix4x4 [8/10]

```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    const FVector3 & translate,
    const Quaternion & rotation,
    const FVector3 & scale
) noexcept
```




<hr>



### function Matrix4x4 [9/10]

```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    const Quaternion & rotation,
    const FVector3 & scale
) noexcept
```




<hr>



### function Matrix4x4 [10/10]

```C++
SR_MATH_NS::Matrix4x4::Matrix4x4 (
    const FVector3 & translate,
    const Quaternion & rotation,
    const FVector3 & scale,
    const FVector3 & skew
) noexcept
```




<hr>



### function OrthogonalNormalize 

```C++
SR_NODISCARD Matrix4x4 SR_MATH_NS::Matrix4x4::OrthogonalNormalize () const
```




<hr>



### function Right 

```C++
SR_NODISCARD FVector3 SR_MATH_NS::Matrix4x4::Right () const
```




<hr>



### function Rotate [1/2]

```C++
SR_NODISCARD Matrix4x4 SR_MATH_NS::Matrix4x4::Rotate (
    const FVector3 & angle
) const
```




<hr>



### function Rotate [2/2]

```C++
SR_NODISCARD Matrix4x4 SR_MATH_NS::Matrix4x4::Rotate (
    const SR_MATH_NS::Quaternion & q
) const
```




<hr>



### function RotateAxis 

```C++
SR_NODISCARD Matrix4x4 SR_MATH_NS::Matrix4x4::RotateAxis (
    const FVector3 & axis,
    const double & angle
) const
```




<hr>



### function SR\_DEPRECATED\_EX 

```C++
SR_MATH_NS::Matrix4x4::SR_DEPRECATED_EX (
    "FromQuaternion"
) const
```




<hr>



### function ToGLM 

```C++
SR_NODISCARD const glm::mat4 & SR_MATH_NS::Matrix4x4::ToGLM () const
```




<hr>



### function TransformPoint 

```C++
SR_NODISCARD FVector4 SR_MATH_NS::Matrix4x4::TransformPoint (
    const FVector3 & point
) const
```




<hr>



### function TransformVector [1/2]

```C++
SR_NODISCARD FVector4 SR_MATH_NS::Matrix4x4::TransformVector (
    const FVector3 & point
) const
```




<hr>



### function TransformVector [2/2]

```C++
SR_NODISCARD FVector4 SR_MATH_NS::Matrix4x4::TransformVector (
    const FVector4 & point
) const
```




<hr>



### function Translate 

```C++
SR_NODISCARD Matrix4x4 SR_MATH_NS::Matrix4x4::Translate (
    const FVector3 & vec3
) const
```




<hr>



### function Up 

```C++
SR_NODISCARD FVector3 SR_MATH_NS::Matrix4x4::Up () const
```




<hr>



### function operator\* 

```C++
Matrix4x4 SR_MATH_NS::Matrix4x4::operator* (
    const Matrix4x4 & mat
) const
```




<hr>



### function operator\* 

```C++
Matrix4x4 SR_MATH_NS::Matrix4x4::operator* (
    const Unit & scalar
) const
```




<hr>



### function operator\* 

```C++
template<typename U>
Vector4 < U > SR_MATH_NS::Matrix4x4::operator* (
    const Vector4 < U > & vector4
) const
```




<hr>



### function operator\*= 

```C++
void SR_MATH_NS::Matrix4x4::operator*= (
    const Matrix4x4 & right
) 
```




<hr>



### function operator\*= 

```C++
void SR_MATH_NS::Matrix4x4::operator*= (
    const Unit & scalar
) 
```




<hr>



### function operator\*= 

```C++
template<typename U>
void SR_MATH_NS::Matrix4x4::operator*= (
    const Vector4 < U > & vector4
) 
```




<hr>



### function operator+ 

```C++
Matrix4x4 SR_MATH_NS::Matrix4x4::operator+ (
    const Matrix4x4 & mat
) const
```




<hr>



### function operator+ 

```C++
Matrix4x4 SR_MATH_NS::Matrix4x4::operator+ (
    Matrix4x4 mat
) 
```




<hr>



### function operator+= 

```C++
void SR_MATH_NS::Matrix4x4::operator+= (
    const Matrix4x4 & right
) 
```




<hr>



### function operator- 

```C++
Matrix4x4 SR_MATH_NS::Matrix4x4::operator- (
    Matrix4x4 mat
) 
```




<hr>



### function operator/ 

```C++
Matrix4x4 SR_MATH_NS::Matrix4x4::operator/ (
    Matrix4x4 mat
) 
```




<hr>



### function operator[] 

```C++
const SR_MATH_NS::FVector4 & SR_MATH_NS::Matrix4x4::operator[] (
    int32_t row
) const
```




<hr>



### function operator[] 

```C++
SR_MATH_NS::FVector4 & SR_MATH_NS::Matrix4x4::operator[] (
    int32_t row
) 
```




<hr>
## Public Static Functions Documentation




### function CreateOrthographicOffCenter 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::CreateOrthographicOffCenter (
    Unit left,
    Unit right,
    Unit bottom,
    Unit top,
    Unit zNear,
    Unit zFar
) 
```




<hr>



### function CreateTRS 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::CreateTRS (
    const SR_MATH_NS::FVector3 & translation,
    const SR_MATH_NS::Quaternion & rotation,
    const SR_MATH_NS::FVector3 & scale
) 
```




<hr>



### function CreateViewMat 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::CreateViewMat (
    Unit pitch=0,
    Unit yaw=0,
    Unit roll=0
) 
```




<hr>



### function FromEulers 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::FromEulers (
    const FVector3 & eulers
) 
```




<hr>



### function FromQuaternion 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::FromQuaternion (
    const Quaternion & quaternion
) 
```




<hr>



### function FromScale 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::FromScale (
    const FVector3 & scale
) 
```




<hr>



### function FromTranslate 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::FromTranslate (
    const FVector3 & translation
) 
```




<hr>



### function Identity 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::Identity () 
```




<hr>



### function LookAt 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::LookAt (
    const SR_MATH_NS::FVector3 & eye,
    const SR_MATH_NS::FVector3 & center,
    const SR_MATH_NS::FVector3 & up
) 
```




<hr>



### function Multiply 

```C++
static void SR_FASTCALL SR_MATH_NS::Matrix4x4::Multiply (
    Matrix4x4 & result,
    const Matrix4x4 & left,
    const Matrix4x4 & right
) 
```




<hr>



### function Ortho 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::Ortho (
    Unit left,
    Unit right,
    Unit bottom,
    Unit top,
    Unit zNear,
    Unit zFar
) 
```




<hr>



### function Perspective 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::Perspective (
    float_t FOV,
    float_t aspect,
    float_t nearValue,
    float_t farValue
) 
```




<hr>



### function RotationAxis [1/2]

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::RotationAxis (
    const SR_MATH_NS::FVector4 & axis,
    Unit angle
) 
```




<hr>



### function RotationAxis [2/2]

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::RotationAxis (
    const SR_MATH_NS::FVector3 & axis,
    Unit angle
) 
```




<hr>



### function RotationYawPitchRoll 

```C++
static Matrix4x4 SR_MATH_NS::Matrix4x4::RotationYawPitchRoll (
    const FVector3 & angles
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Math/Matrix4x4.h`

