

# Struct SR\_UTILS\_NS::Web::CSSStyle



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md) **>** [**CSSStyle**](structSR__UTILS__NS_1_1Web_1_1CSSStyle.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**CSSColor**](structSR__UTILS__NS_1_1Web_1_1CSSColor.md) | [**backgroundColor**](#variable-backgroundcolor)   = `DEFAULT\_CSS\_COLOR`<br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**borderBottom**](#variable-borderbottom)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**borderLeft**](#variable-borderleft)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**borderRight**](#variable-borderright)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**borderTop**](#variable-bordertop)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**bottom**](#variable-bottom)  <br> |
|  CSSBoxSizing | [**boxSizing**](#variable-boxsizing)   = `CSSBoxSizing::ContentBox`<br> |
|  [**CSSColor**](structSR__UTILS__NS_1_1Web_1_1CSSColor.md) | [**color**](#variable-color)   = `DEFAULT\_CSS\_COLOR`<br> |
|  [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md)&lt; CSSDisplay &gt; | [**display**](#variable-display)   = `[**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md)&lt;CSSDisplay&gt;::CreateDefault(DEFAULT\_CSS\_DISPLAY)`<br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**height**](#variable-height)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**left**](#variable-left)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**marginBottom**](#variable-marginbottom)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**marginLeft**](#variable-marginleft)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**marginRight**](#variable-marginright)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**marginTop**](#variable-margintop)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**maxHeight**](#variable-maxheight)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**maxWidth**](#variable-maxwidth)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**minHeight**](#variable-minheight)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**minWidth**](#variable-minwidth)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**opacity**](#variable-opacity)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**paddingBottom**](#variable-paddingbottom)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**paddingLeft**](#variable-paddingleft)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**paddingRight**](#variable-paddingright)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**paddingTop**](#variable-paddingtop)  <br> |
|  CSSPosition | [**position**](#variable-position)   = `CSSPosition::Static`<br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**right**](#variable-right)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**top**](#variable-top)  <br> |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**width**](#variable-width)  <br>_content size_  |
|  [**CSSOptionalSizeValue**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) | [**zIndex**](#variable-zindex)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CSSStyle**](#function-cssstyle) () = default<br> |
|  void | [**ParseProperty**](#function-parseproperty) (std::string\_view name, std::string\_view data) <br> |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint16\_t depth=0) const<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**CSSStyle**](structSR__UTILS__NS_1_1Web_1_1CSSStyle.md) | [**Merge**](#function-merge) (const [**CSSStyle**](structSR__UTILS__NS_1_1Web_1_1CSSStyle.md) & main, const [**CSSStyle**](structSR__UTILS__NS_1_1Web_1_1CSSStyle.md) & other) <br> |


























## Public Attributes Documentation




### variable backgroundColor 

```C++
CSSColor SR_UTILS_NS::Web::CSSStyle::backgroundColor;
```




<hr>



### variable borderBottom 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::borderBottom;
```




<hr>



### variable borderLeft 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::borderLeft;
```




<hr>



### variable borderRight 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::borderRight;
```




<hr>



### variable borderTop 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::borderTop;
```




<hr>



### variable bottom 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::bottom;
```




<hr>



### variable boxSizing 

```C++
CSSBoxSizing SR_UTILS_NS::Web::CSSStyle::boxSizing;
```




<hr>



### variable color 

```C++
CSSColor SR_UTILS_NS::Web::CSSStyle::color;
```




<hr>



### variable display 

```C++
CSSOptionalEnum<CSSDisplay> SR_UTILS_NS::Web::CSSStyle::display;
```




<hr>



### variable height 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::height;
```




<hr>



### variable left 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::left;
```




<hr>



### variable marginBottom 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::marginBottom;
```




<hr>



### variable marginLeft 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::marginLeft;
```




<hr>



### variable marginRight 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::marginRight;
```




<hr>



### variable marginTop 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::marginTop;
```




<hr>



### variable maxHeight 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::maxHeight;
```




<hr>



### variable maxWidth 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::maxWidth;
```




<hr>



### variable minHeight 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::minHeight;
```




<hr>



### variable minWidth 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::minWidth;
```




<hr>



### variable opacity 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::opacity;
```



margin-top border-top padding-top m b p p b m
* - - content - - - left left left right right right padding-bottom border-bottom margin-bottom 




        

<hr>



### variable paddingBottom 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::paddingBottom;
```




<hr>



### variable paddingLeft 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::paddingLeft;
```




<hr>



### variable paddingRight 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::paddingRight;
```




<hr>



### variable paddingTop 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::paddingTop;
```




<hr>



### variable position 

```C++
CSSPosition SR_UTILS_NS::Web::CSSStyle::position;
```




<hr>



### variable right 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::right;
```




<hr>



### variable top 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::top;
```




<hr>



### variable width 

_content size_ 
```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::width;
```




<hr>



### variable zIndex 

```C++
CSSOptionalSizeValue SR_UTILS_NS::Web::CSSStyle::zIndex;
```




<hr>
## Public Functions Documentation




### function CSSStyle 

```C++
SR_UTILS_NS::Web::CSSStyle::CSSStyle () = default
```




<hr>



### function ParseProperty 

```C++
void SR_UTILS_NS::Web::CSSStyle::ParseProperty (
    std::string_view name,
    std::string_view data
) 
```




<hr>



### function ToString 

```C++
SR_NODISCARD std::string SR_UTILS_NS::Web::CSSStyle::ToString (
    uint16_t depth=0
) const
```




<hr>
## Public Static Functions Documentation




### function Merge 

```C++
static CSSStyle SR_UTILS_NS::Web::CSSStyle::Merge (
    const CSSStyle & main,
    const CSSStyle & other
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Web/CSS/CSS.h`

