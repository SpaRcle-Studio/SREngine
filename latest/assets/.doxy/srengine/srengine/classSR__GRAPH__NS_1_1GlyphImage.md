

# Class SR\_GRAPH\_NS::GlyphImage



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**GlyphImage**](classSR__GRAPH__NS_1_1GlyphImage.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::shared\_ptr&lt; [**GlyphImage**](classSR__GRAPH__NS_1_1GlyphImage.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Debug**](#function-debug) (uint8\_t \* pTarget, int32\_t top, uint32\_t sizeX) <br> |
|  SR\_NODISCARD uint8\_t \* | [**GetData**](#function-getdata) () const<br> |
|   | [**GlyphImage**](#function-glyphimage) () = default<br> |
|  void | [**InsertTo**](#function-insertto) (uint8\_t \* pTarget, int32\_t top, uint32\_t sizeX) <br> |
|   | [**~GlyphImage**](#function-glyphimage) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD GlyphImage::Ptr | [**Create**](#function-create) (const Glyph::Ptr & pGlyph, bool needInit) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::GlyphImage::Ptr =  std::shared_ptr<GlyphImage>;
```




<hr>
## Public Functions Documentation




### function Debug 

```C++
void SR_GRAPH_NS::GlyphImage::Debug (
    uint8_t * pTarget,
    int32_t top,
    uint32_t sizeX
) 
```




<hr>



### function GetData 

```C++
inline SR_NODISCARD uint8_t * SR_GRAPH_NS::GlyphImage::GetData () const
```




<hr>



### function GlyphImage 

```C++
SR_GRAPH_NS::GlyphImage::GlyphImage () = default
```




<hr>



### function InsertTo 

```C++
void SR_GRAPH_NS::GlyphImage::InsertTo (
    uint8_t * pTarget,
    int32_t top,
    uint32_t sizeX
) 
```




<hr>



### function ~GlyphImage 

```C++
SR_GRAPH_NS::GlyphImage::~GlyphImage () override
```




<hr>
## Public Static Functions Documentation




### function Create 

```C++
static SR_NODISCARD GlyphImage::Ptr SR_GRAPH_NS::GlyphImage::Create (
    const Glyph::Ptr & pGlyph,
    bool needInit
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Font/Glyph.h`

