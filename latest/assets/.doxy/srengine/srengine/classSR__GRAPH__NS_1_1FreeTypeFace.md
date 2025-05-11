

# Class SR\_GRAPH\_NS::FreeTypeFace



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FreeTypeFace**](classSR__GRAPH__NS_1_1FreeTypeFace.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**CalculateBox**](#function-calculatebox) (uint32\_t codePoint, [**FreeTypeDrawContext**](classSR__GRAPH__NS_1_1FreeTypeDrawContext.md) \* pContext, FT\_Int32 loadFlags, FT\_Render\_Mode renderMode) <br> |
|  SR\_NODISCARD bool | [**DrawCodePoint**](#function-drawcodepoint) ([**FreeTypeDrawContext**](classSR__GRAPH__NS_1_1FreeTypeDrawContext.md) \* context, uint32\_t codePoint, FT\_Int32 loadFlags, FT\_Render\_Mode renderMode) <br> |
|   | [**FreeTypeFace**](#function-freetypeface) (FT\_Face face) <br> |
|   | [**~FreeTypeFace**](#function-freetypeface) () override<br> |


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




### function CalculateBox 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::FreeTypeFace::CalculateBox (
    uint32_t codePoint,
    FreeTypeDrawContext * pContext,
    FT_Int32 loadFlags,
    FT_Render_Mode renderMode
) 
```




<hr>



### function DrawCodePoint 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::FreeTypeFace::DrawCodePoint (
    FreeTypeDrawContext * context,
    uint32_t codePoint,
    FT_Int32 loadFlags,
    FT_Render_Mode renderMode
) 
```




<hr>



### function FreeTypeFace 

```C++
inline explicit SR_GRAPH_NS::FreeTypeFace::FreeTypeFace (
    FT_Face face
) 
```




<hr>



### function ~FreeTypeFace 

```C++
SR_GRAPH_NS::FreeTypeFace::~FreeTypeFace () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Font/FreeTypeFace.h`

