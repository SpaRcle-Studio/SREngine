

# Class SR\_UTILS\_NS::Web::CSSOptional

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)








Inherits the following classes: T


Inherited by the following classes: [SR\_UTILS\_NS::Web::CSSOptionalEnum](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md),  [SR\_UTILS\_NS::Web::CSSOptionalEnum](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CSSOptional**](#function-cssoptional-13) () = default<br> |
|   | [**CSSOptional**](#function-cssoptional-23) (const T & value) <br> |
|   | [**CSSOptional**](#function-cssoptional-33) (const T && value) <br> |
|  SR\_NODISCARD bool | [**IsDefault**](#function-isdefault) () const<br> |
|  void | [**SetAsDefault**](#function-setasdefault) () <br> |
|  SR\_NODISCARD | [**operator T**](#function-operator-t) () const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator) (const [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) & other) const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator_1) (const T & other) const<br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_2) (const [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) & other) const<br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_3) (const T & other) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**CreateDefault**](#function-createdefault) (Y value) <br> |






















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**OnChanged**](#function-onchanged) () <br> |




## Public Functions Documentation




### function CSSOptional [1/3]

```C++
SR_UTILS_NS::Web::CSSOptional::CSSOptional () = default
```




<hr>



### function CSSOptional [2/3]

```C++
inline SR_UTILS_NS::Web::CSSOptional::CSSOptional (
    const T & value
) 
```




<hr>



### function CSSOptional [3/3]

```C++
inline SR_UTILS_NS::Web::CSSOptional::CSSOptional (
    const T && value
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>



### function IsDefault 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptional::IsDefault () const
```




<hr>



### function SetAsDefault 

```C++
inline void SR_UTILS_NS::Web::CSSOptional::SetAsDefault () 
```




<hr>



### function operator T 

```C++
inline SR_NODISCARD SR_UTILS_NS::Web::CSSOptional::operator T () const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptional::operator!= (
    const CSSOptional & other
) const
```




<hr>



### function operator!= 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptional::operator!= (
    const T & other
) const
```




<hr>



### function operator== 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptional::operator== (
    const CSSOptional & other
) const
```




<hr>



### function operator== 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Web::CSSOptional::operator== (
    const T & other
) const
```




<hr>
## Public Static Functions Documentation




### function CreateDefault 

```C++
template<typename Y>
static inline CSSOptional SR_UTILS_NS::Web::CSSOptional::CreateDefault (
    Y value
) 
```



NOLINT(google-explicit-constructor) 


        

<hr>
## Protected Functions Documentation




### function OnChanged 

```C++
inline void SR_UTILS_NS::Web::CSSOptional::OnChanged () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Web/CSS/CSSOptional.h`

