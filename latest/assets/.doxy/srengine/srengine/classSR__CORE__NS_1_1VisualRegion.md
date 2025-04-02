

# Class SR\_CORE\_NS::VisualRegion



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**VisualRegion**](classSR__CORE__NS_1_1VisualRegion.md)








Inherits the following classes: [SR\_WORLD\_NS::Region](classSR__WORLD__NS_1_1Region.md)
















## Public Types inherited from SR_WORLD_NS::Region

See [SR\_WORLD\_NS::Region](classSR__WORLD__NS_1_1Region.md)

| Type | Name |
| ---: | :--- |
| typedef std::function&lt; [**Region**](classSR__WORLD__NS_1_1Region.md) \*(SRRegionAllocArgs)&gt; | [**Allocator**](classSR__WORLD__NS_1_1Region.md#typedef-allocator)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**VisualRegion**](#function-visualregion) (SRRegionAllocArgs) <br> |
|   | [**~VisualRegion**](#function-visualregion) () override<br> |


## Public Functions inherited from SR_WORLD_NS::Region

See [SR\_WORLD\_NS::Region](classSR__WORLD__NS_1_1Region.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**ApplyOffset**](classSR__WORLD__NS_1_1Region.md#function-applyoffset) () <br> |
|  SR\_NODISCARD [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**At**](classSR__WORLD__NS_1_1Region.md#function-at) (const Math::IVector3 & position) const<br> |
|  SR\_NODISCARD bool | [**ContainsObserver**](classSR__WORLD__NS_1_1Region.md#function-containsobserver) () const<br> |
|  SR\_NODISCARD [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**Find**](classSR__WORLD__NS_1_1Region.md#function-find) (const Math::IVector3 & position) const<br> |
|  [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**GetChunk**](classSR__WORLD__NS_1_1Region.md#function-getchunk-12) (const Math::IVector3 & position) <br> |
|  [**Chunk**](classSR__WORLD__NS_1_1Chunk.md) \* | [**GetChunk**](classSR__WORLD__NS_1_1Region.md#function-getchunk-22) (const Math::FVector3 & position) <br> |
|  SR\_NODISCARD const Chunks & | [**GetChunks**](classSR__WORLD__NS_1_1Region.md#function-getchunks) () noexcept const<br> |
|  SR\_NODISCARD Math::IVector3 | [**GetPosition**](classSR__WORLD__NS_1_1Region.md#function-getposition) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](classSR__WORLD__NS_1_1Region.md#function-getscene) () const<br> |
|  SR\_NODISCARD uint32\_t | [**GetWidth**](classSR__WORLD__NS_1_1Region.md#function-getwidth) () const<br> |
|  SR\_NODISCARD Math::IVector3 | [**GetWorldPosition**](classSR__WORLD__NS_1_1Region.md#function-getworldposition) () const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](classSR__WORLD__NS_1_1Region.md#function-isalive) () const<br> |
|  SR\_NODISCARD bool | [**IsChunkLoaded**](classSR__WORLD__NS_1_1Region.md#function-ischunkloaded) (const SR\_MATH\_NS::IVector3 & chunk) const<br> |
| virtual bool | [**Load**](classSR__WORLD__NS_1_1Region.md#function-load) () <br> |
| virtual void | [**OnEnter**](classSR__WORLD__NS_1_1Region.md#function-onenter) () <br> |
| virtual void | [**OnExit**](classSR__WORLD__NS_1_1Region.md#function-onexit) () <br> |
| virtual bool | [**PostLoad**](classSR__WORLD__NS_1_1Region.md#function-postload) () <br> |
| virtual void | [**Reload**](classSR__WORLD__NS_1_1Region.md#function-reload) () <br> |
|  SR\_NODISCARD SR\_HTYPES\_NS::Marshal::Ptr | [**Save**](classSR__WORLD__NS_1_1Region.md#function-save) ([**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* pContext) const<br> |
| virtual bool | [**Unload**](classSR__WORLD__NS_1_1Region.md#function-unload) (bool force=false) <br> |
| virtual void | [**Update**](classSR__WORLD__NS_1_1Region.md#function-update) (float\_t dt) <br> |
|   | [**~Region**](classSR__WORLD__NS_1_1Region.md#function-region) () override<br> |




## Public Static Functions inherited from SR_WORLD_NS::Region

See [SR\_WORLD\_NS::Region](classSR__WORLD__NS_1_1Region.md)

| Type | Name |
| ---: | :--- |
|  [**Region**](classSR__WORLD__NS_1_1Region.md) \* | [**Allocate**](classSR__WORLD__NS_1_1Region.md#function-allocate) (SRRegionAllocArgs) <br> |
|  void | [**SetAllocator**](classSR__WORLD__NS_1_1Region.md#function-setallocator) (const Allocator & allocator) <br> |












## Protected Attributes inherited from SR_WORLD_NS::Region

See [SR\_WORLD\_NS::Region](classSR__WORLD__NS_1_1Region.md)

| Type | Name |
| ---: | :--- |
|  CachedChunks | [**m\_cached**](classSR__WORLD__NS_1_1Region.md#variable-m_cached)  <br> |
|  Math::IVector2 | [**m\_chunkSize**](classSR__WORLD__NS_1_1Region.md#variable-m_chunksize)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_containsObserver**](classSR__WORLD__NS_1_1Region.md#variable-m_containsobserver)  <br> |
|  Chunks | [**m\_loadedChunks**](classSR__WORLD__NS_1_1Region.md#variable-m_loadedchunks)  <br> |
|  [**Observer**](classSR__WORLD__NS_1_1Observer.md) \* | [**m\_observer**](classSR__WORLD__NS_1_1Region.md#variable-m_observer)   = `nullptr`<br> |
|  Math::IVector3 | [**m\_position**](classSR__WORLD__NS_1_1Region.md#variable-m_position)  <br> |
|  uint32\_t | [**m\_width**](classSR__WORLD__NS_1_1Region.md#variable-m_width)  <br> |
































## Protected Functions inherited from SR_WORLD_NS::Region

See [SR\_WORLD\_NS::Region](classSR__WORLD__NS_1_1Region.md)

| Type | Name |
| ---: | :--- |
|   | [**Region**](classSR__WORLD__NS_1_1Region.md#function-region) (SRRegionAllocArgs) <br> |






## Public Functions Documentation




### function VisualRegion 

```C++
inline explicit SR_CORE_NS::VisualRegion::VisualRegion (
    SRRegionAllocArgs
) 
```




<hr>



### function ~VisualRegion 

```C++
SR_CORE_NS::VisualRegion::~VisualRegion () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/World/VisualRegion.h`

