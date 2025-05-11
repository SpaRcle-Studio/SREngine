

# Struct SR\_UTILS\_NS::Web::CSSLinearGradient



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSLinearGradient**](structSR__UTILS__NS_1_1Web_1_1CSSLinearGradient.md)



[More...](#detailed-description)

* `#include <CSSColor.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**CSSGradientColor**](structSR__UTILS__NS_1_1Web_1_1CSSGradientColor.md) &gt; | [**colors**](#variable-colors)  <br> |
|  [**CSSDirection**](structSR__UTILS__NS_1_1Web_1_1CSSDirection.md) | [**direction**](#variable-direction)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**CSSLinearGradient**](structSR__UTILS__NS_1_1Web_1_1CSSLinearGradient.md) | [**Parse**](#function-parse) (std::string\_view data) <br> |


























## Detailed Description



 


    
## Public Attributes Documentation




### variable colors 

```C++
std::vector<CSSGradientColor> SR_UTILS_NS::Web::CSSLinearGradient::colors;
```




<hr>



### variable direction 

```C++
CSSDirection SR_UTILS_NS::Web::CSSLinearGradient::direction;
```




<hr>
## Public Functions Documentation




### function ToString 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Web::CSSLinearGradient::ToString () const
```




<hr>
## Public Static Functions Documentation




### function Parse 

```C++
static SR_NODISCARD CSSLinearGradient SR_UTILS_NS::Web::CSSLinearGradient::Parse (
    std::string_view data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Web/CSS/CSSColor.h`

