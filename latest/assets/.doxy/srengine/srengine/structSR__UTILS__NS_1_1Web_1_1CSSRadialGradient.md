

# Struct SR\_UTILS\_NS::Web::CSSRadialGradient



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSRadialGradient**](structSR__UTILS__NS_1_1Web_1_1CSSRadialGradient.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**Shape**](#enum-shape)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**CSSSizeValue**](structSR__UTILS__NS_1_1Web_1_1CSSSizeValue.md) | [**at**](#variable-at)  <br> |
|  std::vector&lt; [**CSSGradientColor**](structSR__UTILS__NS_1_1Web_1_1CSSGradientColor.md) &gt; | [**colors**](#variable-colors)  <br> |
|  enum SR\_UTILS\_NS::Web::CSSRadialGradient::Shape | [**shape**](#variable-shape)   = `Shape::Circle`<br> |
|  CSSGradientSide | [**side**](#variable-side)   = `CSSGradientSide::ClosestSide`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**CSSRadialGradient**](structSR__UTILS__NS_1_1Web_1_1CSSRadialGradient.md) | [**Parse**](#function-parse) (std::string\_view data) <br> |


























## Public Types Documentation




### enum Shape 

```C++
enum SR_UTILS_NS::Web::CSSRadialGradient::Shape {
    Circle,
    Ellipse
};
```




<hr>
## Public Attributes Documentation




### variable at 

```C++
CSSSizeValue SR_UTILS_NS::Web::CSSRadialGradient::at;
```




<hr>



### variable colors 

```C++
std::vector<CSSGradientColor> SR_UTILS_NS::Web::CSSRadialGradient::colors;
```




<hr>



### variable shape 

```C++
enum SR_UTILS_NS::Web::CSSRadialGradient::Shape SR_UTILS_NS::Web::CSSRadialGradient::shape;
```




<hr>



### variable side 

```C++
CSSGradientSide SR_UTILS_NS::Web::CSSRadialGradient::side;
```




<hr>
## Public Functions Documentation




### function ToString 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Web::CSSRadialGradient::ToString () const
```




<hr>
## Public Static Functions Documentation




### function Parse 

```C++
static SR_NODISCARD CSSRadialGradient SR_UTILS_NS::Web::CSSRadialGradient::Parse (
    std::string_view data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Web/CSS/CSSColor.h`

