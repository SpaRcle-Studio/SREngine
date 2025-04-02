

# Struct SR\_MATH\_NS::Ray



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Ray**](structSR__MATH__NS_1_1Ray.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**direction**](#variable-direction)  <br> |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**origin**](#variable-origin)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD Unit | [**ComputeAngleOnPlan**](#function-computeangleonplan) (const SR\_MATH\_NS::FVector4 & plan, const SR\_MATH\_NS::FVector3 & position, const SR\_MATH\_NS::FVector3 & sourceRotationVector) noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Direction3D**](#function-direction3d) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**IntersectPlane**](#function-intersectplane) (const SR\_MATH\_NS::FVector4 & plan) noexcept const<br> |
|  SR\_NODISCARD Unit | [**IntersectPlaneDistance**](#function-intersectplanedistance) (const SR\_MATH\_NS::FVector4 & plane) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**Origin3D**](#function-origin3d) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**RotationVector**](#function-rotationvector) (const SR\_MATH\_NS::FVector4 & plan, const SR\_MATH\_NS::FVector3 & position) noexcept const<br> |




























## Public Attributes Documentation




### variable direction 

```C++
FVector3 SR_MATH_NS::Ray::direction;
```




<hr>



### variable origin 

```C++
FVector3 SR_MATH_NS::Ray::origin;
```




<hr>
## Public Functions Documentation




### function ComputeAngleOnPlan 

```C++
inline SR_NODISCARD Unit SR_MATH_NS::Ray::ComputeAngleOnPlan (
    const SR_MATH_NS::FVector4 & plan,
    const SR_MATH_NS::FVector3 & position,
    const SR_MATH_NS::FVector3 & sourceRotationVector
) noexcept const
```




<hr>



### function Direction3D 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_MATH_NS::Ray::Direction3D () const
```




<hr>



### function IntersectPlane 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_MATH_NS::Ray::IntersectPlane (
    const SR_MATH_NS::FVector4 & plan
) noexcept const
```




<hr>



### function IntersectPlaneDistance 

```C++
inline SR_NODISCARD Unit SR_MATH_NS::Ray::IntersectPlaneDistance (
    const SR_MATH_NS::FVector4 & plane
) const
```




<hr>



### function Origin3D 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_MATH_NS::Ray::Origin3D () const
```




<hr>



### function RotationVector 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_MATH_NS::Ray::RotationVector (
    const SR_MATH_NS::FVector4 & plan,
    const SR_MATH_NS::FVector3 & position
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Vector4.h`

