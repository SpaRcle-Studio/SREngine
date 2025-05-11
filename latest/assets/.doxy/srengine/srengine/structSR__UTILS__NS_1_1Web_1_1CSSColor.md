

# Struct SR\_UTILS\_NS::Web::CSSColor



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSColor**](structSR__UTILS__NS_1_1Web_1_1CSSColor.md)



[More...](#detailed-description)

* `#include <CSSColor.h>`

















## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**ColorType**](#enum-colortype)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**CSSRGBAColor**](structSR__UTILS__NS_1_1Web_1_1CSSRGBAColor.md) | [**color**](#variable-color)  <br> |
|  enum SR\_UTILS\_NS::Web::CSSColor::ColorType | [**colorType**](#variable-colortype)   = `ColorType::RGBA`<br> |
|  [**CSSLinearGradient**](structSR__UTILS__NS_1_1Web_1_1CSSLinearGradient.md) | [**linearGradient**](#variable-lineargradient)  <br> |
|  [**CSSRadialGradient**](structSR__UTILS__NS_1_1Web_1_1CSSRadialGradient.md) | [**radialGradient**](#variable-radialgradient)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**CSSColor**](structSR__UTILS__NS_1_1Web_1_1CSSColor.md) | [**Parse**](#function-parse) (std::string\_view data) <br> |


























## Detailed Description



 


    
## Public Types Documentation




### enum ColorType 

```C++
enum SR_UTILS_NS::Web::CSSColor::ColorType {
    RGBA,
    LinearGradient,
    RadialGradient
};
```




<hr>
## Public Attributes Documentation




### variable color 

```C++
CSSRGBAColor SR_UTILS_NS::Web::CSSColor::color;
```




<hr>



### variable colorType 

```C++
enum SR_UTILS_NS::Web::CSSColor::ColorType SR_UTILS_NS::Web::CSSColor::colorType;
```




<hr>



### variable linearGradient 

```C++
CSSLinearGradient SR_UTILS_NS::Web::CSSColor::linearGradient;
```




<hr>



### variable radialGradient 

```C++
CSSRadialGradient SR_UTILS_NS::Web::CSSColor::radialGradient;
```




<hr>
## Public Functions Documentation




### function ToString 

```C++
inline SR_NODISCARD std::string SR_UTILS_NS::Web::CSSColor::ToString () const
```




<hr>
## Public Static Functions Documentation




### function Parse 

```C++
static SR_NODISCARD CSSColor SR_UTILS_NS::Web::CSSColor::Parse (
    std::string_view data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Web/CSS/CSSColor.h`

