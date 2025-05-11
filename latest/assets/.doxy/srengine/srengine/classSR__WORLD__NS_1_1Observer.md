

# Class SR\_WORLD\_NS::Observer



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**Observer**](classSR__WORLD__NS_1_1Observer.md)








Inherits the following classes: NonCopyable


















## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::IVector3 | [**m\_chunk**](#variable-m_chunk)  <br> |
|  SR\_MATH\_NS::IVector2 | [**m\_chunkSize**](#variable-m_chunksize)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_lastChunk**](#variable-m_lastchunk)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_lastRegion**](#variable-m_lastregion)  <br> |
|  [**Offset**](structSR__WORLD__NS_1_1Offset.md) | [**m\_offset**](#variable-m_offset)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_region**](#variable-m_region)  <br> |
|  int32\_t | [**m\_regionWidth**](#variable-m_regionwidth)  <br> |
|  ScenePtr | [**m\_scene**](#variable-m_scene)  <br> |
|  int32\_t | [**m\_scope**](#variable-m_scope)  <br> |
|  int32\_t | [**m\_shiftDistance**](#variable-m_shiftdistance)  <br> |
|  GameObjectPtr | [**m\_target**](#variable-m_target)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_targetPosition**](#variable-m_targetposition)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::IVector3 | [**GetChunk**](#function-getchunk) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**GetChunkSize**](#function-getchunksize) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector3 | [**GetRegion**](#function-getregion) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetRegionSize**](#function-getregionsize) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetScope**](#function-getscope) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasTarget**](#function-hastarget) () noexcept const<br> |
|  [**Offset**](structSR__WORLD__NS_1_1Offset.md) | [**MathNeighbour**](#function-mathneighbour) (const Math::IVector3 & offset) const<br> |
|  void | [**MoveRegion**](#function-moveregion) (const Math::IVector3 & value) <br> |
|   | [**Observer**](#function-observer) (const ScenePtr & scene) <br> |
|  void | [**SetChunk**](#function-setchunk) (Math::IVector3 chunk) <br> |
|  void | [**SetScope**](#function-setscope) (int32\_t value) <br> |
|  void | [**SetShiftDist**](#function-setshiftdist) (int32\_t value) <br> |
|  void | [**SetTarget**](#function-settarget) (const GameObjectPtr & target) <br> |
|  void | [**SetWorldMetrics**](#function-setworldmetrics) (const Math::IVector2 & chunkSize, int32\_t regionWidth) <br> |
|  Math::IVector3 | [**WorldPosToChunkPos**](#function-worldpostochunkpos) (const Math::FVector3 & position) <br> |
|   | [**~Observer**](#function-observer) () override<br> |




























## Public Attributes Documentation




### variable m\_chunk 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::Observer::m_chunk;
```




<hr>



### variable m\_chunkSize 

```C++
SR_MATH_NS::IVector2 SR_WORLD_NS::Observer::m_chunkSize;
```




<hr>



### variable m\_lastChunk 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::Observer::m_lastChunk;
```




<hr>



### variable m\_lastRegion 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::Observer::m_lastRegion;
```




<hr>



### variable m\_offset 

```C++
Offset SR_WORLD_NS::Observer::m_offset;
```




<hr>



### variable m\_region 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::Observer::m_region;
```




<hr>



### variable m\_regionWidth 

```C++
int32_t SR_WORLD_NS::Observer::m_regionWidth;
```




<hr>



### variable m\_scene 

```C++
ScenePtr SR_WORLD_NS::Observer::m_scene;
```




<hr>



### variable m\_scope 

```C++
int32_t SR_WORLD_NS::Observer::m_scope;
```




<hr>



### variable m\_shiftDistance 

```C++
int32_t SR_WORLD_NS::Observer::m_shiftDistance;
```




<hr>



### variable m\_target 

```C++
GameObjectPtr SR_WORLD_NS::Observer::m_target;
```




<hr>



### variable m\_targetPosition 

```C++
SR_MATH_NS::FVector3 SR_WORLD_NS::Observer::m_targetPosition;
```




<hr>
## Public Functions Documentation




### function GetChunk 

```C++
inline SR_NODISCARD SR_MATH_NS::IVector3 SR_WORLD_NS::Observer::GetChunk () noexcept const
```




<hr>



### function GetChunkSize 

```C++
inline SR_NODISCARD SR_MATH_NS::IVector2 SR_WORLD_NS::Observer::GetChunkSize () noexcept const
```




<hr>



### function GetRegion 

```C++
inline SR_NODISCARD SR_MATH_NS::IVector3 SR_WORLD_NS::Observer::GetRegion () noexcept const
```




<hr>



### function GetRegionSize 

```C++
inline SR_NODISCARD int32_t SR_WORLD_NS::Observer::GetRegionSize () noexcept const
```




<hr>



### function GetScope 

```C++
inline SR_NODISCARD int32_t SR_WORLD_NS::Observer::GetScope () noexcept const
```




<hr>



### function HasTarget 

```C++
inline SR_NODISCARD bool SR_WORLD_NS::Observer::HasTarget () noexcept const
```




<hr>



### function MathNeighbour 

```C++
Offset SR_WORLD_NS::Observer::MathNeighbour (
    const Math::IVector3 & offset
) const
```




<hr>



### function MoveRegion 

```C++
void SR_WORLD_NS::Observer::MoveRegion (
    const Math::IVector3 & value
) 
```




<hr>



### function Observer 

```C++
explicit SR_WORLD_NS::Observer::Observer (
    const ScenePtr & scene
) 
```




<hr>



### function SetChunk 

```C++
void SR_WORLD_NS::Observer::SetChunk (
    Math::IVector3 chunk
) 
```




<hr>



### function SetScope 

```C++
inline void SR_WORLD_NS::Observer::SetScope (
    int32_t value
) 
```




<hr>



### function SetShiftDist 

```C++
inline void SR_WORLD_NS::Observer::SetShiftDist (
    int32_t value
) 
```




<hr>



### function SetTarget 

```C++
void SR_WORLD_NS::Observer::SetTarget (
    const GameObjectPtr & target
) 
```




<hr>



### function SetWorldMetrics 

```C++
void SR_WORLD_NS::Observer::SetWorldMetrics (
    const Math::IVector2 & chunkSize,
    int32_t regionWidth
) 
```




<hr>



### function WorldPosToChunkPos 

```C++
Math::IVector3 SR_WORLD_NS::Observer::WorldPosToChunkPos (
    const Math::FVector3 & position
) 
```




<hr>



### function ~Observer 

```C++
SR_WORLD_NS::Observer::~Observer () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/World/Observer.h`

