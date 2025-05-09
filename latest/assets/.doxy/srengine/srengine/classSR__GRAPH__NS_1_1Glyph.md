

# Class SR\_GRAPH\_NS::Glyph



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Glyph**](classSR__GRAPH__NS_1_1Glyph.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; [**Glyph**](classSR__GRAPH__NS_1_1Glyph.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD FT\_Glyph | [**GetGlyph**](#function-getglyph) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetHeight**](#function-getheight) () noexcept const<br> |
|  SR\_NODISCARD [**GlyphMetrics**](structSR__GRAPH__NS_1_1GlyphMetrics.md) & | [**GetMetrics**](#function-getmetrics) () noexcept<br> |
|  SR\_NODISCARD uint32\_t | [**GetPixelSize**](#function-getpixelsize) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetPosX**](#function-getposx) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetPosY**](#function-getposy) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetSize**](#function-getsize) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetWidth**](#function-getwidth) () noexcept const<br> |
|   | [**Glyph**](#function-glyph) (FT\_Glyph pGlyph, FT\_Render\_Mode renderMode) <br> |
|   | [**~Glyph**](#function-glyph) () override<br> |


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






## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::Glyph::Ptr =  std::shared_ptr<Glyph>;
```




<hr>



### typedef Super 

```C++
using SR_GRAPH_NS::Glyph::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Public Functions Documentation




### function GetGlyph 

```C++
SR_NODISCARD FT_Glyph SR_GRAPH_NS::Glyph::GetGlyph () noexcept const
```




<hr>



### function GetHeight 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::Glyph::GetHeight () noexcept const
```




<hr>



### function GetMetrics 

```C++
SR_NODISCARD GlyphMetrics & SR_GRAPH_NS::Glyph::GetMetrics () noexcept
```




<hr>



### function GetPixelSize 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::Glyph::GetPixelSize () noexcept const
```




<hr>



### function GetPosX 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::Glyph::GetPosX () noexcept const
```




<hr>



### function GetPosY 

```C++
SR_NODISCARD int32_t SR_GRAPH_NS::Glyph::GetPosY () noexcept const
```




<hr>



### function GetSize 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::Glyph::GetSize () noexcept const
```




<hr>



### function GetWidth 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::Glyph::GetWidth () noexcept const
```




<hr>



### function Glyph 

```C++
SR_GRAPH_NS::Glyph::Glyph (
    FT_Glyph pGlyph,
    FT_Render_Mode renderMode
) 
```




<hr>



### function ~Glyph 

```C++
SR_GRAPH_NS::Glyph::~Glyph () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Font/Glyph.h`

