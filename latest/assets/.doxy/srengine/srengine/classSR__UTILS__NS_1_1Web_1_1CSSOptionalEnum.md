

# Class SR\_UTILS\_NS::Web::CSSOptionalEnum

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md)








Inherits the following classes: [SR\_UTILS\_NS::Web::CSSOptional](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CSSOptionalEnum**](#function-cssoptionalenum-15) () = default<br> |
|   | [**CSSOptionalEnum**](#function-cssoptionalenum-25) (const T & value) <br> |
|   | [**CSSOptionalEnum**](#function-cssoptionalenum-35) (const T && value) <br> |
|   | [**CSSOptionalEnum**](#function-cssoptionalenum-45) (const [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & other) <br> |
|   | [**CSSOptionalEnum**](#function-cssoptionalenum-55) ([**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) && other) noexcept<br> |
|  SR\_NODISCARD | [**operator T**](#function-operator-t) () const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator) (const [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & other) const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator_1) (const T & other) const<br> |
|  [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & | [**operator=**](#function-operator_2) (const [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & other) <br> |
|  [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & | [**operator=**](#function-operator_3) ([**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) && other) noexcept<br> |
|  [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & | [**operator=**](#function-operator_4) (const T & value) <br> |
|  [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & | [**operator=**](#function-operator_5) (const T && value) <br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_6) (const [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) & other) const<br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_7) (const T & other) const<br> |


## Public Functions inherited from SR_UTILS_NS::Web::CSSOptional

See [SR\_UTILS\_NS::Web::CSSOptional](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)

| Type | Name |
| ---: | :--- |
|   | [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-cssoptional-13) () = default<br> |
|   | [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-cssoptional-23) (const T & value) <br> |
|   | [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-cssoptional-33) (const T && value) <br> |
|  SR\_NODISCARD bool | [**IsDefault**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-isdefault) () const<br> |
|  void | [**SetAsDefault**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-setasdefault) () <br> |
|  SR\_NODISCARD | [**operator T**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-operator-t) () const<br> |
|  SR\_NODISCARD bool | [**operator!=**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-operator) (const [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) & other) const<br> |
|  SR\_NODISCARD bool | [**operator!=**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-operator_1) (const T & other) const<br> |
|  SR\_NODISCARD bool | [**operator==**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-operator_2) (const [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) & other) const<br> |
|  SR\_NODISCARD bool | [**operator==**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-operator_3) (const T & other) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) | [**CreateDefault**](#function-createdefault) (Y value) <br> |


## Public Static Functions inherited from SR_UTILS_NS::Web::CSSOptional

See [SR\_UTILS\_NS::Web::CSSOptional](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)

| Type | Name |
| ---: | :--- |
|  [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**CreateDefault**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-createdefault) (Y value) <br> |












































## Protected Functions inherited from SR_UTILS_NS::Web::CSSOptional

See [SR\_UTILS\_NS::Web::CSSOptional](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)

| Type | Name |
| ---: | :--- |
|  void | [**OnChanged**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md#function-onchanged) () <br> |






## Public Functions Documentation




### function CSSOptionalEnum [1/5]

```C++
SR_UTILS_NS::Web::CSSOptionalEnum::CSSOptionalEnum () = default
```




<hr>



### function CSSOptionalEnum [2/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnum::CSSOptionalEnum (
    const T & value
) 
```




<hr>



### function CSSOptionalEnum [3/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnum::CSSOptionalEnum (
    const T && value
) 
```




<hr>



### function CSSOptionalEnum [4/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnum::CSSOptionalEnum (
    const CSSOptionalEnum & other
) 
```




<hr>



### function CSSOptionalEnum [5/5]

```C++
inline SR_UTILS_NS::Web::CSSOptionalEnum::CSSOptionalEnum (
    CSSOptionalEnum && other
) noexcept
```




<hr>



### function operator T 

```C++
inline SR_NODISCARD SR_UTILS_NS::Web::CSSOptionalEnum::operator T () const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptionalEnum::operator!= (
    const CSSOptionalEnum & other
) const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptionalEnum::operator!= (
    const T & other
) const
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnum & SR_UTILS_NS::Web::CSSOptionalEnum::operator= (
    const CSSOptionalEnum & other
) 
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnum & SR_UTILS_NS::Web::CSSOptionalEnum::operator= (
    CSSOptionalEnum && other
) noexcept
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnum & SR_UTILS_NS::Web::CSSOptionalEnum::operator= (
    const T & value
) 
```




<hr>



### function operator= 

```C++
inline CSSOptionalEnum & SR_UTILS_NS::Web::CSSOptionalEnum::operator= (
    const T && value
) 
```




<hr>



### function operator== 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptionalEnum::operator== (
    const CSSOptionalEnum & other
) const
```




<hr>



### function operator== 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptionalEnum::operator== (
    const T & other
) const
```




<hr>
## Public Static Functions Documentation




### function CreateDefault 

```C++
template<typename Y>
static inline CSSOptionalEnum SR_UTILS_NS::Web::CSSOptionalEnum::CreateDefault (
    Y value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Web/CSS/CSSOptional.h`

