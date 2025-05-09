

# Class SR\_GRAPH\_NS::TextBuilder



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**TextBuilder**](classSR__GRAPH__NS_1_1TextBuilder.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Build**](#function-build-12) (const char \* text) <br> |
|  bool | [**Build**](#function-build-22) (StringType text) <br> |
|  SR\_NODISCARD int32\_t | [**CalculateTextWidth**](#function-calculatetextwidth) (const char \* text) <br> |
|  SR\_NODISCARD ImageFormat | [**GetColorFormat**](#function-getcolorformat) () noexcept const<br> |
|  SR\_NODISCARD uint8\_t \* | [**GetData**](#function-getdata) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetFontSize**](#function-getfontsize) () noexcept const<br> |
|  SR\_NODISCARD FontStyle | [**GetFontStyle**](#function-getfontstyle) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetHeight**](#function-getheight) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetSize**](#function-getsize) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetWidth**](#function-getwidth) () noexcept const<br> |
|  void | [**SetDebug**](#function-setdebug) (bool enabled) <br> |
|  void | [**SetFontSize**](#function-setfontsize) (uint32\_t size) <br> |
|  void | [**SetFontStyle**](#function-setfontstyle) (FontStyle style) <br> |
|  void | [**SetKerning**](#function-setkerning) (bool enabled) <br> |
|   | [**TextBuilder**](#function-textbuilder) (FontPtr pFont) <br> |
|   | [**~TextBuilder**](#function-textbuilder) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function Build [1/2]

```C++
bool SR_GRAPH_NS::TextBuilder::Build (
    const char * text
) 
```




<hr>



### function Build [2/2]

```C++
bool SR_GRAPH_NS::TextBuilder::Build (
    StringType text
) 
```




<hr>



### function CalculateTextWidth 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::TextBuilder::CalculateTextWidth (
    const char * text
) 
```




<hr>



### function GetColorFormat 

```C++
SR_NODISCARD ImageFormat SR_GRAPH_NS::TextBuilder::GetColorFormat () noexcept const
```




<hr>



### function GetData 

```C++
inline SR_NODISCARD uint8_t * SR_GRAPH_NS::TextBuilder::GetData () noexcept const
```




<hr>



### function GetFontSize 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::TextBuilder::GetFontSize () noexcept const
```




<hr>



### function GetFontStyle 

```C++
inline SR_NODISCARD FontStyle SR_GRAPH_NS::TextBuilder::GetFontStyle () noexcept const
```




<hr>



### function GetHeight 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::TextBuilder::GetHeight () noexcept const
```




<hr>



### function GetSize 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::TextBuilder::GetSize () noexcept const
```




<hr>



### function GetWidth 

```C++
inline SR_NODISCARD uint32_t SR_GRAPH_NS::TextBuilder::GetWidth () noexcept const
```




<hr>



### function SetDebug 

```C++
void SR_GRAPH_NS::TextBuilder::SetDebug (
    bool enabled
) 
```




<hr>



### function SetFontSize 

```C++
inline void SR_GRAPH_NS::TextBuilder::SetFontSize (
    uint32_t size
) 
```




<hr>



### function SetFontStyle 

```C++
inline void SR_GRAPH_NS::TextBuilder::SetFontStyle (
    FontStyle style
) 
```




<hr>



### function SetKerning 

```C++
void SR_GRAPH_NS::TextBuilder::SetKerning (
    bool enabled
) 
```




<hr>



### function TextBuilder 

```C++
explicit SR_GRAPH_NS::TextBuilder::TextBuilder (
    FontPtr pFont
) 
```




<hr>



### function ~TextBuilder 

```C++
SR_GRAPH_NS::TextBuilder::~TextBuilder () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Font/TextBuilder.h`

