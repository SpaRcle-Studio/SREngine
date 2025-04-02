

# Class SR\_GRAPH\_NS::IColorBufferPass



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**IColorBufferPass**](classSR__GRAPH__NS_1_1IColorBufferPass.md)










Inherited by the following classes: [SR\_GRAPH\_NS::ColorBufferPass](classSR__GRAPH__NS_1_1ColorBufferPass.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**GetColor**](#function-getcolor) (float\_t x, float\_t y) const<br> |
| virtual SR\_NODISCARD [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**GetColorFrameBuffer**](#function-getcolorframebuffer) () noexcept const = 0<br> |
|  SR\_NODISCARD uint32\_t | [**GetColorIndex**](#function-getcolorindex) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetIndex**](#function-getindex) (float\_t x, float\_t y) const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**GetMesh**](#function-getmesh-12) (float\_t x, float\_t y) const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**GetMesh**](#function-getmesh-22) (SR\_MATH\_NS::FVector2 pos) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetMeshColor**](#function-getmeshcolor) () noexcept const<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearTable**](#function-cleartable) () <br> |
|  void | [**IncrementColorIndex**](#function-incrementcolorindex) () noexcept<br> |
|  void | [**ResetColorIndex**](#function-resetcolorindex) () noexcept<br> |
|  void | [**SetColorMultiplier**](#function-setcolormultiplier) (uint32\_t multiplier) <br> |
|  void | [**SetMeshIndex**](#function-setmeshindex) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh) <br> |




## Public Functions Documentation




### function GetColor 

```C++
SR_NODISCARD SR_MATH_NS::FColor SR_GRAPH_NS::IColorBufferPass::GetColor (
    float_t x,
    float_t y
) const
```




<hr>



### function GetColorFrameBuffer 

```C++
virtual SR_NODISCARD SR_GTYPES_NS::Framebuffer * SR_GRAPH_NS::IColorBufferPass::GetColorFrameBuffer () noexcept const = 0
```




<hr>



### function GetColorIndex 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::IColorBufferPass::GetColorIndex () noexcept const
```




<hr>



### function GetIndex 

```C++
SR_NODISCARD uint32_t SR_GRAPH_NS::IColorBufferPass::GetIndex (
    float_t x,
    float_t y
) const
```




<hr>



### function GetMesh [1/2]

```C++
SR_NODISCARD SR_GTYPES_NS::Mesh * SR_GRAPH_NS::IColorBufferPass::GetMesh (
    float_t x,
    float_t y
) const
```




<hr>



### function GetMesh [2/2]

```C++
SR_NODISCARD SR_GTYPES_NS::Mesh * SR_GRAPH_NS::IColorBufferPass::GetMesh (
    SR_MATH_NS::FVector2 pos
) const
```




<hr>



### function GetMeshColor 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_GRAPH_NS::IColorBufferPass::GetMeshColor () noexcept const
```




<hr>
## Protected Functions Documentation




### function ClearTable 

```C++
void SR_GRAPH_NS::IColorBufferPass::ClearTable () 
```




<hr>



### function IncrementColorIndex 

```C++
void SR_GRAPH_NS::IColorBufferPass::IncrementColorIndex () noexcept
```




<hr>



### function ResetColorIndex 

```C++
inline void SR_GRAPH_NS::IColorBufferPass::ResetColorIndex () noexcept
```




<hr>



### function SetColorMultiplier 

```C++
inline void SR_GRAPH_NS::IColorBufferPass::SetColorMultiplier (
    uint32_t multiplier
) 
```




<hr>



### function SetMeshIndex 

```C++
void SR_GRAPH_NS::IColorBufferPass::SetMeshIndex (
    SR_GTYPES_NS::Mesh * pMesh
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Pass/IColorBufferPass.h`

