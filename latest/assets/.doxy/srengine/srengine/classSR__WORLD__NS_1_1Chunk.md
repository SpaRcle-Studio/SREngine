

# Class SR\_WORLD\_NS::Chunk



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**Chunk**](classSR__WORLD__NS_1_1Chunk.md)








Inherits the following classes: NonCopyable


Inherited by the following classes: [SR\_CORE\_NS::VisualChunk](classSR__CORE__NS_1_1VisualChunk.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::function&lt; [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \*(SRChunkAllocArgs)&gt; | [**Allocator**](#typedef-allocator)  <br> |
| enum  | [**LoadState**](#enum-loadstate)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**Access**](#function-access) (float\_t dt) <br> |
| virtual bool | [**ApplyOffset**](#function-applyoffset) () <br> |
| virtual bool | [**Belongs**](#function-belongs-12) (const Math::FVector3 & point) <br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector3 | [**GetPosition**](#function-getposition) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](#function-getscene) () const<br> |
|  SR\_NODISCARD LoadState | [**GetState**](#function-getstate) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetWorldPosition**](#function-getworldposition) (SR\_MATH\_NS::Axis center=SR\_MATH\_NS::Axis::None) const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](#function-isalive) () const<br> |
|  SR\_NODISCARD bool | [**IsPreLoaded**](#function-ispreloaded) () const<br> |
| virtual bool | [**Load**](#function-load) () <br> |
| virtual void | [**OnEnter**](#function-onenter) () <br> |
| virtual void | [**OnExit**](#function-onexit) () <br> |
| virtual bool | [**PreLoad**](#function-preload) ([**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) \* pMarshal) <br> |
| virtual void | [**Reload**](#function-reload) () <br> |
|  SR\_NODISCARD SR\_HTYPES\_NS::Marshal::Ptr | [**Save**](#function-save) ([**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* pContext) const<br> |
| virtual bool | [**Unload**](#function-unload) () <br> |
| virtual void | [**Update**](#function-update) (float\_t dt) <br> |
|   | [**~Chunk**](#function-chunk) () override<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**Allocate**](#function-allocate) (SRChunkAllocArgs) <br> |
|  bool | [**Belongs**](#function-belongs-22) (const Math::IVector3 & position, const Math::IVector2 & size, const Math::FVector3 & point) <br> |
|  void | [**SetAllocator**](#function-setallocator) (const Allocator & allocator) <br> |






## Protected Attributes

| Type | Name |
| ---: | :--- |
|  float\_t | [**m\_lifetime**](#variable-m_lifetime)  <br> |
|  LoadState | [**m\_loadState**](#variable-m_loadstate)  <br> |
|  [**Observer**](classSR__WORLD__NS_1_1Observer.md) \* | [**m\_observer**](#variable-m_observer)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_position**](#variable-m_position)  <br> |
|  std::list&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; GameObject &gt; &gt; | [**m\_preloaded**](#variable-m_preloaded)  <br> |
|  [**Region**](classSR__WORLD__NS_1_1Region.md) \* | [**m\_region**](#variable-m_region)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_regionPosition**](#variable-m_regionposition)  <br> |
|  SR\_MATH\_NS::IVector2 | [**m\_size**](#variable-m_size)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Chunk**](#function-chunk) (SRChunkAllocArgs) <br> |




## Public Types Documentation




### typedef Allocator 

```C++
typedef std::function<Chunk*(SRChunkAllocArgs)> SR_WORLD_NS::Chunk::Allocator;
```




<hr>



### enum LoadState 

```C++
enum SR_WORLD_NS::Chunk::LoadState {
    PreLoaded,
    Loaded,
    Unload,
    Preload
};
```




<hr>
## Public Functions Documentation




### function Access 

```C++
virtual bool SR_WORLD_NS::Chunk::Access (
    float_t dt
) 
```




<hr>



### function ApplyOffset 

```C++
virtual bool SR_WORLD_NS::Chunk::ApplyOffset () 
```




<hr>



### function Belongs [1/2]

```C++
virtual bool SR_WORLD_NS::Chunk::Belongs (
    const Math::FVector3 & point
) 
```




<hr>



### function GetPosition 

```C++
inline SR_NODISCARD SR_MATH_NS::IVector3 SR_WORLD_NS::Chunk::GetPosition () const
```




<hr>



### function GetScene 

```C++
SR_NODISCARD ScenePtr SR_WORLD_NS::Chunk::GetScene () const
```




<hr>



### function GetState 

```C++
inline SR_NODISCARD LoadState SR_WORLD_NS::Chunk::GetState () const
```




<hr>



### function GetWorldPosition 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_WORLD_NS::Chunk::GetWorldPosition (
    SR_MATH_NS::Axis center=SR_MATH_NS::Axis::None
) const
```




<hr>



### function IsAlive 

```C++
inline SR_NODISCARD bool SR_WORLD_NS::Chunk::IsAlive () const
```




<hr>



### function IsPreLoaded 

```C++
inline SR_NODISCARD bool SR_WORLD_NS::Chunk::IsPreLoaded () const
```




<hr>



### function Load 

```C++
virtual bool SR_WORLD_NS::Chunk::Load () 
```




<hr>



### function OnEnter 

```C++
virtual void SR_WORLD_NS::Chunk::OnEnter () 
```




<hr>



### function OnExit 

```C++
virtual void SR_WORLD_NS::Chunk::OnExit () 
```




<hr>



### function PreLoad 

```C++
virtual bool SR_WORLD_NS::Chunk::PreLoad (
    SR_HTYPES_NS::Marshal * pMarshal
) 
```




<hr>



### function Reload 

```C++
virtual void SR_WORLD_NS::Chunk::Reload () 
```




<hr>



### function Save 

```C++
SR_NODISCARD SR_HTYPES_NS::Marshal::Ptr SR_WORLD_NS::Chunk::Save (
    SR_HTYPES_NS::DataStorage * pContext
) const
```




<hr>



### function Unload 

```C++
virtual bool SR_WORLD_NS::Chunk::Unload () 
```




<hr>



### function Update 

```C++
virtual void SR_WORLD_NS::Chunk::Update (
    float_t dt
) 
```




<hr>



### function ~Chunk 

```C++
SR_WORLD_NS::Chunk::~Chunk () override
```




<hr>
## Public Static Functions Documentation




### function Allocate 

```C++
static Chunk * SR_WORLD_NS::Chunk::Allocate (
    SRChunkAllocArgs
) 
```




<hr>



### function Belongs [2/2]

```C++
static bool SR_WORLD_NS::Chunk::Belongs (
    const Math::IVector3 & position,
    const Math::IVector2 & size,
    const Math::FVector3 & point
) 
```




<hr>



### function SetAllocator 

```C++
static void SR_WORLD_NS::Chunk::SetAllocator (
    const Allocator & allocator
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_lifetime 

```C++
float_t SR_WORLD_NS::Chunk::m_lifetime;
```




<hr>



### variable m\_loadState 

```C++
LoadState SR_WORLD_NS::Chunk::m_loadState;
```




<hr>



### variable m\_observer 

```C++
Observer* SR_WORLD_NS::Chunk::m_observer;
```




<hr>



### variable m\_position 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::Chunk::m_position;
```




<hr>



### variable m\_preloaded 

```C++
std::list<SR_HTYPES_NS::SharedPtr<GameObject> > SR_WORLD_NS::Chunk::m_preloaded;
```




<hr>



### variable m\_region 

```C++
Region* SR_WORLD_NS::Chunk::m_region;
```




<hr>



### variable m\_regionPosition 

```C++
SR_MATH_NS::IVector3 SR_WORLD_NS::Chunk::m_regionPosition;
```




<hr>



### variable m\_size 

```C++
SR_MATH_NS::IVector2 SR_WORLD_NS::Chunk::m_size;
```




<hr>
## Protected Functions Documentation




### function Chunk 

```C++
SR_WORLD_NS::Chunk::Chunk (
    SRChunkAllocArgs
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/World/Chunk.h`

