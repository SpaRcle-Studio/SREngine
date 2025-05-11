

# Class SR\_CORE\_NS::VisualChunk



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**VisualChunk**](classSR__CORE__NS_1_1VisualChunk.md)








Inherits the following classes: [SR\_WORLD\_NS::Chunk](classSR__WORLD__NS_1_1Chunk.md)
















## Public Types inherited from SR_WORLD_NS::Chunk

See [SR\_WORLD\_NS::Chunk](classSR__WORLD__NS_1_1Chunk.md)

| Type | Name |
| ---: | :--- |
| typedef std::function&lt; [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \*(SRChunkAllocArgs)&gt; | [**Allocator**](classSR__WORLD__NS_1_1Chunk.md#typedef-allocator)  <br> |
| enum  | [**LoadState**](classSR__WORLD__NS_1_1Chunk.md#enum-loadstate)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**VisualChunk**](#function-visualchunk) (SRChunkAllocArgs) <br> |
|   | [**~VisualChunk**](#function-visualchunk) () override<br> |


## Public Functions inherited from SR_WORLD_NS::Chunk

See [SR\_WORLD\_NS::Chunk](classSR__WORLD__NS_1_1Chunk.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**Access**](classSR__WORLD__NS_1_1Chunk.md#function-access) (float\_t dt) <br> |
| virtual bool | [**ApplyOffset**](classSR__WORLD__NS_1_1Chunk.md#function-applyoffset) () <br> |
| virtual bool | [**Belongs**](classSR__WORLD__NS_1_1Chunk.md#function-belongs-12) (const Math::FVector3 & point) <br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector3 | [**GetPosition**](classSR__WORLD__NS_1_1Chunk.md#function-getposition) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](classSR__WORLD__NS_1_1Chunk.md#function-getscene) () const<br> |
|  SR\_NODISCARD LoadState | [**GetState**](classSR__WORLD__NS_1_1Chunk.md#function-getstate) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetWorldPosition**](classSR__WORLD__NS_1_1Chunk.md#function-getworldposition) (SR\_MATH\_NS::Axis center=SR\_MATH\_NS::Axis::None) const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](classSR__WORLD__NS_1_1Chunk.md#function-isalive) () const<br> |
|  SR\_NODISCARD bool | [**IsPreLoaded**](classSR__WORLD__NS_1_1Chunk.md#function-ispreloaded) () const<br> |
| virtual bool | [**Load**](classSR__WORLD__NS_1_1Chunk.md#function-load) () <br> |
| virtual void | [**OnEnter**](classSR__WORLD__NS_1_1Chunk.md#function-onenter) () <br> |
| virtual void | [**OnExit**](classSR__WORLD__NS_1_1Chunk.md#function-onexit) () <br> |
| virtual bool | [**PreLoad**](classSR__WORLD__NS_1_1Chunk.md#function-preload) ([**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) \* pMarshal) <br> |
| virtual void | [**Reload**](classSR__WORLD__NS_1_1Chunk.md#function-reload) () <br> |
|  SR\_NODISCARD SR\_HTYPES\_NS::Marshal::Ptr | [**Save**](classSR__WORLD__NS_1_1Chunk.md#function-save) ([**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* pContext) const<br> |
| virtual bool | [**Unload**](classSR__WORLD__NS_1_1Chunk.md#function-unload) () <br> |
| virtual void | [**Update**](classSR__WORLD__NS_1_1Chunk.md#function-update) (float\_t dt) <br> |
|   | [**~Chunk**](classSR__WORLD__NS_1_1Chunk.md#function-chunk) () override<br> |




## Public Static Functions inherited from SR_WORLD_NS::Chunk

See [SR\_WORLD\_NS::Chunk](classSR__WORLD__NS_1_1Chunk.md)

| Type | Name |
| ---: | :--- |
|  [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**Allocate**](classSR__WORLD__NS_1_1Chunk.md#function-allocate) (SRChunkAllocArgs) <br> |
|  bool | [**Belongs**](classSR__WORLD__NS_1_1Chunk.md#function-belongs-22) (const Math::IVector3 & position, const Math::IVector2 & size, const Math::FVector3 & point) <br> |
|  void | [**SetAllocator**](classSR__WORLD__NS_1_1Chunk.md#function-setallocator) (const Allocator & allocator) <br> |












## Protected Attributes inherited from SR_WORLD_NS::Chunk

See [SR\_WORLD\_NS::Chunk](classSR__WORLD__NS_1_1Chunk.md)

| Type | Name |
| ---: | :--- |
|  float\_t | [**m\_lifetime**](classSR__WORLD__NS_1_1Chunk.md#variable-m_lifetime)  <br> |
|  LoadState | [**m\_loadState**](classSR__WORLD__NS_1_1Chunk.md#variable-m_loadstate)  <br> |
|  [**Observer**](classSR__WORLD__NS_1_1Observer.md) \* | [**m\_observer**](classSR__WORLD__NS_1_1Chunk.md#variable-m_observer)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_position**](classSR__WORLD__NS_1_1Chunk.md#variable-m_position)  <br> |
|  std::list&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; GameObject &gt; &gt; | [**m\_preloaded**](classSR__WORLD__NS_1_1Chunk.md#variable-m_preloaded)  <br> |
|  [**Region**](classSR__WORLD__NS_1_1Region.md) \* | [**m\_region**](classSR__WORLD__NS_1_1Chunk.md#variable-m_region)  <br> |
|  SR\_MATH\_NS::IVector3 | [**m\_regionPosition**](classSR__WORLD__NS_1_1Chunk.md#variable-m_regionposition)  <br> |
|  SR\_MATH\_NS::IVector2 | [**m\_size**](classSR__WORLD__NS_1_1Chunk.md#variable-m_size)  <br> |
































## Protected Functions inherited from SR_WORLD_NS::Chunk

See [SR\_WORLD\_NS::Chunk](classSR__WORLD__NS_1_1Chunk.md)

| Type | Name |
| ---: | :--- |
|   | [**Chunk**](classSR__WORLD__NS_1_1Chunk.md#function-chunk) (SRChunkAllocArgs) <br> |






## Public Functions Documentation




### function VisualChunk 

```C++
explicit SR_CORE_NS::VisualChunk::VisualChunk (
    SRChunkAllocArgs
) 
```




<hr>



### function ~VisualChunk 

```C++
SR_CORE_NS::VisualChunk::~VisualChunk () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/World/VisualChunk.h`

