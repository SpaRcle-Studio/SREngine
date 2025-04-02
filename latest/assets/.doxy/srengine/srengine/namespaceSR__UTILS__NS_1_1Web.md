

# Namespace SR\_UTILS\_NS::Web



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Web**](namespaceSR__UTILS__NS_1_1Web.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**CSS**](classSR__UTILS__NS_1_1Web_1_1CSS.md) <br> |
| struct | [**CSSColor**](structSR__UTILS__NS_1_1Web_1_1CSSColor.md) <br> |
| struct | [**CSSDirection**](structSR__UTILS__NS_1_1Web_1_1CSSDirection.md) <br> |
| struct | [**CSSGradientColor**](structSR__UTILS__NS_1_1Web_1_1CSSGradientColor.md) <br> |
| struct | [**CSSLinearGradient**](structSR__UTILS__NS_1_1Web_1_1CSSLinearGradient.md) <br> |
| class | [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md) &lt;class T&gt;<br> |
| class | [**CSSOptionalEnum**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnum.md) &lt;typename T&gt;<br> |
| class | [**CSSOptionalEnumContainer**](classSR__UTILS__NS_1_1Web_1_1CSSOptionalEnumContainer.md) &lt;typename T&gt;<br> |
| class | [**CSSParser**](classSR__UTILS__NS_1_1Web_1_1CSSParser.md) <br> |
| struct | [**CSSParserContext**](structSR__UTILS__NS_1_1Web_1_1CSSParserContext.md) <br> |
| struct | [**CSSRGBAColor**](structSR__UTILS__NS_1_1Web_1_1CSSRGBAColor.md) <br> |
| struct | [**CSSRadialGradient**](structSR__UTILS__NS_1_1Web_1_1CSSRadialGradient.md) <br> |
| struct | [**CSSSizeValue**](structSR__UTILS__NS_1_1Web_1_1CSSSizeValue.md) <br> |
| struct | [**CSSStyle**](structSR__UTILS__NS_1_1Web_1_1CSSStyle.md) <br> |
| class | [**HTMLContainerInterface**](classSR__UTILS__NS_1_1Web_1_1HTMLContainerInterface.md) <br> |
| class | [**HTMLPage**](classSR__UTILS__NS_1_1Web_1_1HTMLPage.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**CSSBoxSizing**](#enum-cssboxsizing)  <br> |
| enum uint8\_t | [**CSSDisplay**](#enum-cssdisplay)  <br> |
| enum uint8\_t | [**CSSGradientSide**](#enum-cssgradientside)  <br> |
| typedef [**CSSOptional**](classSR__UTILS__NS_1_1Web_1_1CSSOptional.md)&lt; [**CSSSizeValue**](structSR__UTILS__NS_1_1Web_1_1CSSSizeValue.md) &gt; | [**CSSOptionalSizeValue**](#typedef-cssoptionalsizevalue)  <br> |
| enum uint8\_t | [**CSSPosition**](#enum-cssposition)  <br> |
| enum  | [**HTMLTag**](#enum-htmltag)  <br> |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC CSSBoxSizing | [**DEFAULT\_CSS\_BOX\_SIZING**](#variable-default_css_box_sizing)   = `CSSBoxSizing::ContentBox`<br> |
|  SR\_INLINE\_STATIC const [**CSSColor**](structSR__UTILS__NS_1_1Web_1_1CSSColor.md) | [**DEFAULT\_CSS\_COLOR**](#variable-default_css_color)   = `[**CSSColor**](structSR__UTILS__NS_1_1Web_1_1CSSColor.md)()`<br> |
|  SR\_INLINE\_STATIC CSSDisplay | [**DEFAULT\_CSS\_DISPLAY**](#variable-default_css_display)   = `CSSDisplay::Inline`<br> |
|  SR\_INLINE\_STATIC CSSDisplay | [**DEFAULT\_CSS\_DISPLAY\_BODY**](#variable-default_css_display_body)   = `CSSDisplay::Block`<br> |
|  SR\_INLINE\_STATIC CSSPosition | [**DEFAULT\_CSS\_POSITION**](#variable-default_css_position)   = `CSSPosition::Static`<br> |
|  SR\_INLINE\_STATIC [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**UndefinedTag**](#variable-undefinedtag)   = `"undef"\_atom`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD HTMLTag | [**MyHTMLTagToHTMLTag**](#function-myhtmltagtohtmltag) (size\_t tag) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**CSSBoxSizingToString**](#function-cssboxsizingtostring) (CSSBoxSizing boxSizing) <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**CSSDisplayToString**](#function-cssdisplaytostring) (CSSDisplay display) <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**CSSPositionToString**](#function-csspositiontostring) (CSSPosition position) <br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**HTMLTagToStringAtom**](#function-htmltagtostringatom) (HTMLTag tag) <br> |
|  SR\_NODISCARD HTMLTag | [**StringAtomToHTMLTag**](#function-stringatomtohtmltag) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & tag) <br> |
|  CSSBoxSizing | [**StringToCSSBoxSizing**](#function-stringtocssboxsizing) (const std::string\_view str) <br> |
|  CSSDisplay | [**StringToCSSDisplay**](#function-stringtocssdisplay) (const std::string\_view str) <br> |
|  CSSPosition | [**StringToCSSPosition**](#function-stringtocssposition) (const std::string\_view str) <br> |


























## Public Types Documentation




### enum CSSBoxSizing 

```C++
enum SR_UTILS_NS::Web::CSSBoxSizing {
    ContentBox,
    BorderBox,
    Inherit
};
```




<hr>



### enum CSSDisplay 

```C++
enum SR_UTILS_NS::Web::CSSDisplay {
    Block,
    Inline,
    RunIn,
    Flow,
    FlowRoot,
    Table,
    Flex,
    Grid,
    Ruby,
    BlockFlow,
    InlineTable,
    FlexRunIn,
    ListItem,
    ListItemBlock,
    ListItemInline,
    ListItemFlow,
    ListItemFlowRoot,
    ListItemBlockFlow,
    ListItemBlockFlowRoot,
    FlowListItemBlock,
    TableRowGroup,
    TableHeaderGroup,
    TableFooterGroup,
    TableRow,
    TableCell,
    TableColumnGroup,
    TableColumn,
    TableCaption,
    RubyBase,
    RubyText,
    RubyBaseContainer,
    RubyTextContainer,
    Contents,
    None,
    InlineBlock,
    InlineFlex,
    InlineGrid,
    Inherit,
    Initial,
    Unset,
    SIZE
};
```




<hr>



### enum CSSGradientSide 

```C++
enum SR_UTILS_NS::Web::CSSGradientSide {
    ClosestSide,
    ClosestCorner,
    FarthestSide,
    FarthestCorner
};
```




<hr>



### typedef CSSOptionalSizeValue 

```C++
using SR_UTILS_NS::Web::CSSOptionalSizeValue =  CSSOptional<CSSSizeValue>;
```




<hr>



### enum CSSPosition 

```C++
enum SR_UTILS_NS::Web::CSSPosition {
    Absolute,
    Relative,
    Fixed,
    Static,
    Sticky
};
```




<hr>



### enum HTMLTag 

```C++
enum SR_UTILS_NS::Web::HTMLTag {
    Undefined,
    Div,
    Span,
    P,
    H1,
    H2,
    H3,
    H4,
    H5,
    H6,
    A,
    Img,
    Input,
    Button,
    Form,
    Label,
    Select,
    Option,
    Textarea,
    Table,
    Tr,
    Td,
    Th,
    Thead,
    Tbody,
    Tfoot,
    Ul,
    Ol,
    Li,
    Dl,
    Dt,
    Dd,
    Br,
    Hr,
    Meta,
    Link,
    Style,
    Script,
    Title,
    Head,
    Body,
    Html,
    Text,
    Header,
    MAX_SIZE
};
```




<hr>
## Public Attributes Documentation




### variable DEFAULT\_CSS\_BOX\_SIZING 

```C++
SR_INLINE_STATIC CSSBoxSizing SR_UTILS_NS::Web::DEFAULT_CSS_BOX_SIZING;
```




<hr>



### variable DEFAULT\_CSS\_COLOR 

```C++
SR_INLINE_STATIC const CSSColor SR_UTILS_NS::Web::DEFAULT_CSS_COLOR;
```




<hr>



### variable DEFAULT\_CSS\_DISPLAY 

```C++
SR_INLINE_STATIC CSSDisplay SR_UTILS_NS::Web::DEFAULT_CSS_DISPLAY;
```




<hr>



### variable DEFAULT\_CSS\_DISPLAY\_BODY 

```C++
SR_INLINE_STATIC CSSDisplay SR_UTILS_NS::Web::DEFAULT_CSS_DISPLAY_BODY;
```




<hr>



### variable DEFAULT\_CSS\_POSITION 

```C++
SR_INLINE_STATIC CSSPosition SR_UTILS_NS::Web::DEFAULT_CSS_POSITION;
```




<hr>



### variable UndefinedTag 

```C++
SR_INLINE_STATIC SR_UTILS_NS::StringAtom SR_UTILS_NS::Web::UndefinedTag;
```




<hr>
## Public Functions Documentation




### function MyHTMLTagToHTMLTag 

```C++
SR_NODISCARD HTMLTag SR_UTILS_NS::Web::MyHTMLTagToHTMLTag (
    size_t tag
) 
```




<hr>
## Public Static Functions Documentation




### function CSSBoxSizingToString 

```C++
static SR_UTILS_NS::StringAtom SR_UTILS_NS::Web::CSSBoxSizingToString (
    CSSBoxSizing boxSizing
) 
```




<hr>



### function CSSDisplayToString 

```C++
static SR_UTILS_NS::StringAtom SR_UTILS_NS::Web::CSSDisplayToString (
    CSSDisplay display
) 
```




<hr>



### function CSSPositionToString 

```C++
static SR_UTILS_NS::StringAtom SR_UTILS_NS::Web::CSSPositionToString (
    CSSPosition position
) 
```




<hr>



### function HTMLTagToStringAtom 

```C++
static SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::Web::HTMLTagToStringAtom (
    HTMLTag tag
) 
```




<hr>



### function StringAtomToHTMLTag 

```C++
static SR_NODISCARD HTMLTag SR_UTILS_NS::Web::StringAtomToHTMLTag (
    const SR_UTILS_NS::StringAtom & tag
) 
```




<hr>



### function StringToCSSBoxSizing 

```C++
static CSSBoxSizing SR_UTILS_NS::Web::StringToCSSBoxSizing (
    const std::string_view str
) 
```




<hr>



### function StringToCSSDisplay 

```C++
static CSSDisplay SR_UTILS_NS::Web::StringToCSSDisplay (
    const std::string_view str
) 
```




<hr>



### function StringToCSSPosition 

```C++
static CSSPosition SR_UTILS_NS::Web::StringToCSSPosition (
    const std::string_view str
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Web/CSS/CSS.h`

