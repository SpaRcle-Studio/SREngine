

# Class SR\_WORLD\_NS::Region



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**Region**](classSR__WORLD__NS_1_1Region.md)








Inherits the following classes: NonCopyable


Inherited by the following classes: [SR\_CORE\_NS::VisualRegion](classSR__CORE__NS_1_1VisualRegion.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::function&lt; [**Region**](classSR__WORLD__NS_1_1Region.md) \*(SRRegionAllocArgs)&gt; | [**Allocator**](#typedef-allocator)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**ApplyOffset**](#function-applyoffset) () <br> |
|  SR\_NODISCARD [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**At**](#function-at) (const Math::IVector3 & position) const<br> |
|  SR\_NODISCARD bool | [**ContainsObserver**](#function-containsobserver) () const<br> |
|  SR\_NODISCARD [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**Find**](#function-find) (const Math::IVector3 & position) const<br> |
|  [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**GetChunk**](#function-getchunk-12) (const Math::IVector3 & position) <br> |
|  [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**GetChunk**](#function-getchunk-22) (const Math::FVector3 & position) <br> |
|  SR\_NODISCARD const Chunks & | [**GetChunks**](#function-getchunks) () noexcept const<br> |
|  SR\_NODISCARD Math::IVector3 | [**GetPosition**](#function-getposition) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](#function-getscene) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetWidth**](#function-getwidth) () const<br> |
|  SR\_NODISCARD Math::IVector3 | [**GetWorldPosition**](#function-getworldposition) () const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](#function-isalive) () const<br> |
|  SR\_NODISCARD bool | [**IsChunkLoaded**](#function-ischunkloaded) (const SR\_MATH\_NS::IVector3 & chunk) const<br> |
| virtual bool | [**Load**](#function-load) () <br> |
| virtual void | [**OnEnter**](#function-onenter) () <br> |
| virtual void | [**OnExit**](#function-onexit) () <br> |
| virtual bool | [**PostLoad**](#function-postload) () <br> |
| virtual void | [**Reload**](#function-reload) () <br> |
|  SR\_NODISCARD SR\_HTYPES\_NS::Marshal::Ptr | [**Save**](#function-save) ([**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* pContext) const<br> |
| virtual bool | [**Unload**](#function-unload) (bool force=false) <br> |
| virtual void | [**Update**](#function-update) (float\_t dt) <br> |
|   | [**~Region**](#function-region) () override<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Region**](classSR__WORLD__NS_1_1Region.md) \* | [**Allocate**](#function-allocate) (SRRegionAllocArgs) <br> |
|  void | [**SetAllocator**](#function-setallocator) (const Allocator & allocator) <br> |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  CachedChunks | [**m\_cached**](#variable-m_cached)  <br> |
|  Math::IVector2 | [**m\_chunkSize**](#variable-m_chunksize)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_containsObserver**](#variable-m_containsobserver)  <br> |
|  Chunks | [**m\_loadedChunks**](#variable-m_loadedchunks)  <br> |
|  [**Observer**](classSR__WORLD__NS_1_1Observer.md) \* | [**m\_observer**](#variable-m_observer)   = `nullptr`<br> |
|  Math::IVector3 | [**m\_position**](#variable-m_position)  <br> |
|  uint32\_t | [**m\_width**](#variable-m_width)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Region**](#function-region) (SRRegionAllocArgs) <br> |




## Public Types Documentation




### typedef Allocator 

```C++
typedef std::function<Region*(SRRegionAllocArgs)> SR_WORLD_NS::Region::Allocator;
```




<hr>
## Public Functions Documentation




### function ApplyOffset 

```C++
virtual void SR_WORLD_NS::Region::ApplyOffset () 
```




<hr>



### function At 

```C++
SR_NODISCARD Chunk * SR_WORLD_NS::Region::At (
    const Math::IVector3 & position
) const
```




<hr>



### function ContainsObserver 

```C++
inline SR_NODISCARD bool SR_WORLD_NS::Region::ContainsObserver () const
```




<hr>



### function Find 

```C++
SR_NODISCARD Chunk * SR_WORLD_NS::Region::Find (
    const Math::IVector3 & position
) const
```




<hr>



### function GetChunk [1/2]

```C++
Chunk * SR_WORLD_NS::Region::GetChunk (
    const Math::IVector3 & position
) 
```




<hr>



### function GetChunk [2/2]

```C++
Chunk * SR_WORLD_NS::Region::GetChunk (
    const Math::FVector3 & position
) 
```




<hr>



### function GetChunks 

```C++
inline SR_NODISCARD const Chunks & SR_WORLD_NS::Region::GetChunks () noexcept const
```




<hr>



### function GetPosition 

```C++
inline SR_NODISCARD Math::IVector3 SR_WORLD_NS::Region::GetPosition () const
```




<hr>



### function GetScene 

```C++
SR_NODISCARD ScenePtr SR_WORLD_NS::Region::GetScene () const
```




<hr>



### function GetWidth 

```C++
inline SR_NODISCARD uint32_t SR_WORLD_NS::Region::GetWidth () const
```




<hr>



### function GetWorldPosition 

```C++
SR_NODISCARD Math::IVector3 SR_WORLD_NS::Region::GetWorldPosition () const
```




<hr>



### function IsAlive 

```C++
inline SR_NODISCARD bool SR_WORLD_NS::Region::IsAlive () const
```




<hr>



### function IsChunkLoaded 

```C++
SR_NODISCARD bool SR_WORLD_NS::Region::IsChunkLoaded (
    const SR_MATH_NS::IVector3 & chunk
) const
```




<hr>



### function Load 

```C++
virtual bool SR_WORLD_NS::Region::Load () 
```




<hr>



### function OnEnter 

```C++
virtual void SR_WORLD_NS::Region::OnEnter () 
```




<hr>



### function OnExit 

```C++
virtual void SR_WORLD_NS::Region::OnExit () 
```




<hr>



### function PostLoad 

```C++
virtual bool SR_WORLD_NS::Region::PostLoad () 
```




<hr>



### function Reload 

```C++
virtual void SR_WORLD_NS::Region::Reload () 
```




<hr>



### function Save 

```C++
SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr SR_WORLD_NS::Region::Save (
    SR_HTYPES_NS::DataStorage * pContext
) const
```




<hr>



### function Unload 

```C++
virtual bool SR_WORLD_NS::Region::Unload (
    bool force=false
) 
```




<hr>



### function Update 

```C++
virtual void SR_WORLD_NS::Region::Update (
    float_t dt
) 
```




<hr>



### function ~Region 

```C++
SR_WORLD_NS::Region::~Region () override
```




<hr>
## Public Static Functions Documentation




### function Allocate 

```C++
static Region * SR_WORLD_NS::Region::Allocate (
    SRRegionAllocArgs
) 
```




<hr>



### function SetAllocator 

```C++
static void SR_WORLD_NS::Region::SetAllocator (
    const Allocator & allocator
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_cached 

```C++
CachedChunks SR_WORLD_NS::Region::m_cached;
```




<hr>



### variable m\_chunkSize 

```C++
Math::IVector2 SR_WORLD_NS::Region::m_chunkSize;
```




<hr>



### variable m\_containsObserver 

```C++
std::atomic<bool> SR_WORLD_NS::Region::m_containsObserver;
```




<hr>



### variable m\_loadedChunks 

```C++
Chunks SR_WORLD_NS::Region::m_loadedChunks;
```




<hr>



### variable m\_observer 

```C++
Observer* SR_WORLD_NS::Region::m_observer;
```




<hr>



### variable m\_position 

```C++
Math::IVector3 SR_WORLD_NS::Region::m_position;
```




<hr>



### variable m\_width 

```C++
uint32_t SR_WORLD_NS::Region::m_width;
```




<hr>
## Protected Functions Documentation




### function Region 

```C++
inline explicit SR_WORLD_NS::Region::Region (
    SRRegionAllocArgs
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/World/Region.h`

