

# Struct SR\_UTILS\_NS::Web::CSSRGBAColor



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSRGBAColor**](structSR__UTILS__NS_1_1Web_1_1CSSRGBAColor.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  uint8\_t | [**a**](#variable-a)   = `0`<br> |
|  uint8\_t | [**b**](#variable-b)   = `0`<br> |
|  uint8\_t | [**g**](#variable-g)   = `0`<br> |
|  uint8\_t | [**r**](#variable-r)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**ToFColor**](#function-tofcolor) () const<br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**CSSRGBAColor**](structSR__UTILS__NS_1_1Web_1_1CSSRGBAColor.md) | [**Parse**](#function-parse) (std::string\_view data) <br> |


























## Public Attributes Documentation




### variable a 

```C++
uint8_t SR_UTILS_NS::Web::CSSRGBAColor::a;
```




<hr>



### variable b 

```C++
uint8_t SR_UTILS_NS::Web::CSSRGBAColor::b;
```




<hr>



### variable g 

```C++
uint8_t SR_UTILS_NS::Web::CSSRGBAColor::g;
```




<hr>



### variable r 

```C++
uint8_t SR_UTILS_NS::Web::CSSRGBAColor::r;
```




<hr>
## Public Functions Documentation




### function ToFColor 

```C++
inline SR_NODISCARD SR_MATH_NS::FColor SR_UTILS_NS::Web::CSSRGBAColor::ToFColor () const
```




<hr>



### function ToString 

```C++
inline SR_NODISCARD std::string SR_UTILS_NS::Web::CSSRGBAColor::ToString () const
```




<hr>
## Public Static Functions Documentation




### function Parse 

```C++
static SR_NODISCARD CSSRGBAColor SR_UTILS_NS::Web::CSSRGBAColor::Parse (
    std::string_view data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Web/CSS/CSSColor.h`

