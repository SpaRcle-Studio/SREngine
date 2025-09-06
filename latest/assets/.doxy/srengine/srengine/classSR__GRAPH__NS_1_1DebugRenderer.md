

# Class SR\_GRAPH\_NS::DebugRenderer



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**DebugRenderer**](classSR__GRAPH__NS_1_1DebugRenderer.md)








Inherits the following classes: [SR\_GRAPH\_NS::IRenderer](classSR__GRAPH__NS_1_1IRenderer.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**DebugTimedObject**](structSR__GRAPH__NS_1_1DebugRenderer_1_1DebugTimedObject.md) <br> |
| struct | [**DrawInfo**](structSR__GRAPH__NS_1_1DebugRenderer_1_1DrawInfo.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum int32\_t | [**DrawType**](#enum-drawtype)  <br> |


## Public Types inherited from SR_GRAPH_NS::IRenderer

See [SR\_GRAPH\_NS::IRenderer](classSR__GRAPH__NS_1_1IRenderer.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IRenderer**](classSR__GRAPH__NS_1_1IRenderer.md) &gt; | [**Ptr**](classSR__GRAPH__NS_1_1IRenderer.md#typedef-ptr)  <br> |




## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |






























































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Clear**](#function-clear) () override<br> |
| virtual void | [**DeInit**](#function-deinit) () override<br> |
|  SR\_NODISCARD uint64\_t | [**GetEmptyIdsPoolSize**](#function-getemptyidspoolsize) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**Memory::BakedMesh**](classSR__GRAPH__NS_1_1Memory_1_1BakedMesh.md) & | [**GetMeshUnchecked**](#function-getmeshunchecked) (uint32\_t index) noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetTimedObjectPoolSize**](#function-gettimedobjectpoolsize) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::ObjectPool**](classSR__HTYPES__NS_1_1ObjectPool.md)&lt; [**DebugTimedObject**](structSR__GRAPH__NS_1_1DebugRenderer_1_1DebugTimedObject.md) &gt; & | [**GetTimedObjects**](#function-gettimedobjects) () noexcept<br> |
| virtual void | [**Init**](#function-init) () override<br> |
| virtual SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () noexcept override const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsMeshValid**](#function-ismeshvalid) (uint32\_t index) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsRenderSceneChanged**](#function-isrenderscenechanged) () noexcept const<br> |
| virtual void | [**Prepare**](#function-prepare) () override<br> |
|  void | [**ResetChangedFlags**](#function-resetchangedflags) () noexcept<br> |
|   | [**~DebugRenderer**](#function-debugrenderer) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::IRenderer

See [SR\_GRAPH\_NS::IRenderer](classSR__GRAPH__NS_1_1IRenderer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Clear**](classSR__GRAPH__NS_1_1IRenderer.md#function-clear) () <br> |
| virtual void | [**DeInit**](classSR__GRAPH__NS_1_1IRenderer.md#function-deinit) () <br> |
|  SR\_NODISCARD [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* | [**GetRenderScene**](classSR__GRAPH__NS_1_1IRenderer.md#function-getrenderscene) () noexcept const<br> |
|   | [**IRenderer**](classSR__GRAPH__NS_1_1IRenderer.md#function-irenderer) () <br> |
| virtual void | [**Init**](classSR__GRAPH__NS_1_1IRenderer.md#function-init) () <br> |
| virtual bool | [**IsEmpty**](classSR__GRAPH__NS_1_1IRenderer.md#function-isempty) () noexcept const<br> |
| virtual void | [**PostUpdate**](classSR__GRAPH__NS_1_1IRenderer.md#function-postupdate) () <br> |
| virtual void | [**Prepare**](classSR__GRAPH__NS_1_1IRenderer.md#function-prepare) () <br> |
|  void | [**SetRenderScene**](classSR__GRAPH__NS_1_1IRenderer.md#function-setrenderscene) ([**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) \* pRenderScene) noexcept<br> |


## Public Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](classSR__UTILS__NS_1_1SRClass.md#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](classSR__UTILS__NS_1_1SRClass.md#function-srclass) () = default<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br> |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-incrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**PolymorphicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-polymorphiccast) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-recursivelockifvalid) () noexcept const<br> |
|  U | [**ReinterpretCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reinterpretcast) () <br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reset) () override<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtr.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) override<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-15) () = default<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-25) (const T \* constPtr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-35) (const T \* constPtr, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-45) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) const & ptr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-55) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) && ptr) noexcept<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**StaticCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-staticcast) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-tryrecursivelockifvalid) () noexcept const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SharedPtr.md#function-unlock) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|   | [**~SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-decrementpointer) () = 0<br> |
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-incrementpointer) () = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () <br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-valid) () const = 0<br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |






## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |


## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |


























## Protected Attributes inherited from SR_GRAPH_NS::IRenderer

See [SR\_GRAPH\_NS::IRenderer](classSR__GRAPH__NS_1_1IRenderer.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__GRAPH__NS_1_1IRenderer.md#variable-m_mutex)  <br> |






## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |




























































































## Public Types Documentation




### enum DrawType 

```C++
enum SR_GRAPH_NS::DebugRenderer::DrawType {
    None = -2,
    Line = -1,
    Mesh = 0,
    Cube = Mesh,
    Sphere,
    Cylinder,
    CustomMesh
};
```




<hr>
## Public Functions Documentation




### function Clear 

```C++
virtual void SR_GRAPH_NS::DebugRenderer::Clear () override
```



Implements [*SR\_GRAPH\_NS::IRenderer::Clear*](classSR__GRAPH__NS_1_1IRenderer.md#function-clear)


<hr>



### function DeInit 

```C++
virtual void SR_GRAPH_NS::DebugRenderer::DeInit () override
```



Implements [*SR\_GRAPH\_NS::IRenderer::DeInit*](classSR__GRAPH__NS_1_1IRenderer.md#function-deinit)


<hr>



### function GetEmptyIdsPoolSize 

```C++
inline SR_NODISCARD uint64_t SR_GRAPH_NS::DebugRenderer::GetEmptyIdsPoolSize () noexcept const
```




<hr>



### function GetMeshUnchecked 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const Memory::BakedMesh & SR_GRAPH_NS::DebugRenderer::GetMeshUnchecked (
    uint32_t index
) noexcept const
```




<hr>



### function GetTimedObjectPoolSize 

```C++
inline SR_NODISCARD uint64_t SR_GRAPH_NS::DebugRenderer::GetTimedObjectPoolSize () noexcept const
```




<hr>



### function GetTimedObjects 

```C++
inline SR_NODISCARD SR_HTYPES_NS::ObjectPool < DebugTimedObject > & SR_GRAPH_NS::DebugRenderer::GetTimedObjects () noexcept
```




<hr>



### function Init 

```C++
virtual void SR_GRAPH_NS::DebugRenderer::Init () override
```



Implements [*SR\_GRAPH\_NS::IRenderer::Init*](classSR__GRAPH__NS_1_1IRenderer.md#function-init)


<hr>



### function IsEmpty 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::DebugRenderer::IsEmpty () noexcept override const
```



Implements [*SR\_GRAPH\_NS::IRenderer::IsEmpty*](classSR__GRAPH__NS_1_1IRenderer.md#function-isempty)


<hr>



### function IsMeshValid 

```C++
inline SR_NODISCARD SR_FORCE_INLINE bool SR_GRAPH_NS::DebugRenderer::IsMeshValid (
    uint32_t index
) noexcept const
```




<hr>



### function IsRenderSceneChanged 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::DebugRenderer::IsRenderSceneChanged () noexcept const
```




<hr>



### function Prepare 

```C++
virtual void SR_GRAPH_NS::DebugRenderer::Prepare () override
```



Implements [*SR\_GRAPH\_NS::IRenderer::Prepare*](classSR__GRAPH__NS_1_1IRenderer.md#function-prepare)


<hr>



### function ResetChangedFlags 

```C++
void SR_GRAPH_NS::DebugRenderer::ResetChangedFlags () noexcept
```




<hr>



### function ~DebugRenderer 

```C++
SR_GRAPH_NS::DebugRenderer::~DebugRenderer () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/DebugRenderer.h`

