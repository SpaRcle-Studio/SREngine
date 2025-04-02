

# Class SR\_MATH\_NS::Matrix3x3



[**ClassList**](annotated.md) **>** [**SR\_MATH\_NS**](namespaceSR__MATH__NS.md) **>** [**Matrix3x3**](classSR__MATH__NS_1_1Matrix3x3.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**elements**](#variable-elements)   = `/* multi line expression */`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  [**FVector3**](structSR__MATH__NS_1_1Vector3.md) | [**GetEulerXYZ**](#function-geteulerxyz) () const<br> |
|  SR\_FORCE\_INLINE void | [**Set**](#function-set) (double xx, double xy, double xz, double yx, double yy, double yz, double zx, double zy, double zz) <br> |
|  SR\_FORCE\_INLINE const [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator[]**](#function-operator) (int axis) const<br> |
|  SR\_FORCE\_INLINE [**FVector3**](structSR__MATH__NS_1_1Vector3.md) & | [**operator[]**](#function-operator_1) (int axis) <br> |




























## Public Attributes Documentation




### variable elements 

```C++
FVector3 SR_MATH_NS::Matrix3x3::elements[3];
```




<hr>
## Public Functions Documentation




### function GetEulerXYZ 

```C++
inline FVector3 SR_MATH_NS::Matrix3x3::GetEulerXYZ () const
```




<hr>



### function Set 

```C++
inline SR_FORCE_INLINE void SR_MATH_NS::Matrix3x3::Set (
    double xx,
    double xy,
    double xz,
    double yx,
    double yy,
    double yz,
    double zx,
    double zy,
    double zz
) 
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE const FVector3 & SR_MATH_NS::Matrix3x3::operator[] (
    int axis
) const
```




<hr>



### function operator[] 

```C++
inline SR_FORCE_INLINE FVector3 & SR_MATH_NS::Matrix3x3::operator[] (
    int axis
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Math/Matrix3x3.h`

