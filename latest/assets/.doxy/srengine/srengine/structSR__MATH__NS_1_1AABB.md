

# Struct SR\_MATH\_NS::AABB



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**AABB**](structSR__MATH__NS_1_1AABB.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  union [**SR\_MATH\_NS::AABB**](structSR__MATH__NS_1_1AABB.md) | [**AABB**](#variable-aabb-12)  <br> |
|  union [**SR\_MATH\_NS::AABB**](structSR__MATH__NS_1_1AABB.md) | [**AABB**](#variable-aabb-22)  <br> |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**max**](#variable-max)   = `[**FVector3**](structSR__MATH__NS_1_1Vector3.md)(0.f, 0.f, 0.f)`<br> |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**min**](#variable-min)   = `[**FVector3**](structSR__MATH__NS_1_1Vector3.md)(0.f, 0.f, 0.f)`<br> |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**position**](#variable-position)  <br>_Alias for min._  |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**size**](#variable-size)  <br>_Alias for max._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AABB**](#function-aabb-12) () <br> |
|   | [**AABB**](#function-aabb-22) (const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & min, const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & max) <br> |
|  SR\_NODISCARD [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**GetCenter**](#function-getcenter) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () noexcept const<br> |




























## Public Attributes Documentation




### variable AABB [1/2]

```C++
union SR_MATH_NS::AABB SR_MATH_NS::AABB;
```




<hr>



### variable AABB [2/2]

```C++
union SR_MATH_NS::AABB SR_MATH_NS::AABB;
```




<hr>



### variable max 

```C++
FVector3 SR_MATH_NS::AABB::max;
```




<hr>



### variable min 

```C++
FVector3 SR_MATH_NS::AABB::min;
```




<hr>



### variable position 

_Alias for min._ 
```C++
FVector3 SR_MATH_NS::AABB::position;
```




<hr>



### variable size 

_Alias for max._ 
```C++
FVector3 SR_MATH_NS::AABB::size;
```




<hr>
## Public Functions Documentation




### function AABB [1/2]

```C++
SR_MATH_NS::AABB::AABB () 
```




<hr>



### function AABB [2/2]

```C++
SR_MATH_NS::AABB::AABB (
    const FVector3 & min,
    const FVector3 & max
) 
```




<hr>



### function GetCenter 

```C++
SR_NODISCARD FVector3 SR_MATH_NS::AABB::GetCenter () noexcept const
```




<hr>



### function IsEmpty 

```C++
SR_NODISCARD bool SR_MATH_NS::AABB::IsEmpty () noexcept const
```




<hr>



### function IsValid 

```C++
SR_NODISCARD bool SR_MATH_NS::AABB::IsValid () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Math/AABB.h`

