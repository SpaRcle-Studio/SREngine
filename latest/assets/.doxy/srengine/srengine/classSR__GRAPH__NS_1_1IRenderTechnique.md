

# Class SR\_GRAPH\_NS::IRenderTechnique



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md)








Inherits the following classes: [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md),  [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)


Inherited by the following classes: [SR\_GRAPH\_NS::FileRenderTechnique](classSR__GRAPH__NS_1_1FileRenderTechnique.md),  [SR\_GRAPH\_NS::ScriptableRenderTechnique](classSR__GRAPH__NS_1_1ScriptableRenderTechnique.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef Types::Camera \* | [**CameraPtr**](#typedef-cameraptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) &gt; | [**Super**](#typedef-super)  <br> |


## Public Types inherited from SR_GRAPH_NS::Memory::IGraphicsResource

See [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#typedef-pipelineptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**RenderContextPtr**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#typedef-rendercontextptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* | [**FindPass**](#function-findpass) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  void | [**ForEachPass**](#function-foreachpass) (const std::function&lt; void([**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) &)&gt; & func) <br> |
| virtual void | [**FreeVMemory**](#function-freevmemory) () override<br> |
|  SR\_NODISCARD const CameraPtr & | [**GetCamera**](#function-getcamera) () noexcept const<br> |
|  SR\_NODISCARD const FrameBufferController::Ptr & | [**GetFrameBufferController**](#function-getframebuffercontroller) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD const std::vector&lt; FrameBufferController::Ptr &gt; & | [**GetFrameBufferControllers**](#function-getframebuffercontrollers) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () noexcept const<br> |
|  SR\_NODISCARD const RenderTechniqueQueues & | [**GetQueues**](#function-getqueues) () const<br> |
|  SR\_NODISCARD const RenderScenePtr & | [**GetRenderScene**](#function-getrenderscene) () noexcept const<br> |
|  SR\_NODISCARD const [**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) & | [**GetRenderTechniqueData**](#function-getrendertechniquedata-12) () noexcept const<br> |
|  SR\_NODISCARD [**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) & | [**GetRenderTechniqueData**](#function-getrendertechniquedata-22) () noexcept<br> |
|   | [**IRenderTechnique**](#function-irendertechnique) () <br> |
|  SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () const<br> |
|  SR\_NODISCARD bool | [**IsTechniqueDead**](#function-istechniquedead) () const<br> |
|  void | [**KillTechnique**](#function-killtechnique) () <br> |
|  void | [**OnHierarchyChanged**](#function-onhierarchychanged) () <br> |
|  void | [**OnMultisampleChanged**](#function-onmultisamplechanged) () <br> |
|  void | [**OnResize**](#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
|  bool | [**Overlay**](#function-overlay) () <br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](#function-pickmeshat-14) (const SR\_MATH\_NS::FPoint & pos) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](#function-pickmeshat-24) (float\_t x, float\_t y) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](#function-pickmeshat-34) (float\_t x, float\_t y, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) passName) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](#function-pickmeshat-44) (float\_t x, float\_t y, const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & passFilter) const<br> |
|  void | [**PostUpdate**](#function-postupdate) () <br> |
|  void | [**PrepareFrame**](#function-prepareframe) () <br> |
|  void | [**PrepareRender**](#function-preparerender) () <br> |
|  bool | [**Render**](#function-render) () <br> |
|  void | [**SetCamera**](#function-setcamera) (CameraPtr pCamera) <br> |
|  void | [**SetDirty**](#function-setdirty) () <br> |
|  void | [**SetRenderScene**](#function-setrenderscene) (const RenderScenePtr & pRScene) <br> |
|  void | [**SetRenderTechniqueData**](#function-setrendertechniquedata) ([**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) && data) <br> |
|  void | [**Update**](#function-update) () <br> |
|   | [**~IRenderTechnique**](#function-irendertechnique) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::Memory::IGraphicsResource

See [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)

| Type | Name |
| ---: | :--- |
|  void | [**DeInitGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-deinitgraphicsresource) ([**SR\_UTILS\_NS::PassKey**](classSR__UTILS__NS_1_1PassKey.md)&lt; [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt;) <br> |
|  SR\_NODISCARD const PipelinePtr & | [**GetPipeline**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-getpipeline) () noexcept const<br> |
|  SR\_NODISCARD const [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) & | [**GetRenderContext**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-getrendercontext) () noexcept const<br> |
|   | [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-igraphicsresource-22) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |
|  SR\_NODISCARD bool | [**IsGraphicsResourceRegistered**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-isgraphicsresourceregistered) () noexcept const<br> |
|  void | [**RegisterGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-registergraphicsresource) () <br> |
|  [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) & | [**operator=**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-operator) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |


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






## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |




















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  CameraPtr | [**m\_camera**](#variable-m_camera)   = `nullptr`<br> |
|  [**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) | [**m\_data**](#variable-m_data)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_dirty**](#variable-m_dirty)   = `true`<br> |
|  std::atomic&lt; bool &gt; | [**m\_hasErrors**](#variable-m_haserrors)   = `false`<br> |
|  std::atomic&lt; bool &gt; | [**m\_isDead**](#variable-m_isdead)   = `false`<br> |
|  bool | [**m\_modulesApplied**](#variable-m_modulesapplied)   = `false`<br> |
|  RenderScenePtr | [**m\_renderScene**](#variable-m_renderscene)  <br> |
|  std::optional&lt; SR\_MATH\_NS::UVector2 &gt; | [**m\_surfaceSize**](#variable-m_surfacesize)  <br> |






## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |




























































## Protected Functions inherited from SR_GRAPH_NS::Memory::IGraphicsResource

See [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**FreeVMemory**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-freevmemory) () <br> |
|   | [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-igraphicsresource-12) () = default<br> |
| virtual  | [**~IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-igraphicsresource) () <br> |














## Public Types Documentation




### typedef CameraPtr 

```C++
using SR_GRAPH_NS::IRenderTechnique::CameraPtr =  Types::Camera*;
```




<hr>



### typedef Ptr 

```C++
using SR_GRAPH_NS::IRenderTechnique::Ptr =  SR_HTYPES_NS::SharedPtr<IRenderTechnique>;
```




<hr>



### typedef RenderScenePtr 

```C++
using SR_GRAPH_NS::IRenderTechnique::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<RenderScene>;
```




<hr>



### typedef Super 

```C++
using SR_GRAPH_NS::IRenderTechnique::Super =  SR_HTYPES_NS::SharedPtr<IRenderTechnique>;
```




<hr>
## Public Functions Documentation




### function FindPass 

```C++
SR_NODISCARD BasePass * SR_GRAPH_NS::IRenderTechnique::FindPass (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function ForEachPass 

```C++
void SR_GRAPH_NS::IRenderTechnique::ForEachPass (
    const std::function< void( BasePass &)> & func
) 
```




<hr>



### function FreeVMemory 

```C++
virtual void SR_GRAPH_NS::IRenderTechnique::FreeVMemory () override
```



Implements [*SR\_GRAPH\_NS::Memory::IGraphicsResource::FreeVMemory*](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-freevmemory)


<hr>



### function GetCamera 

```C++
inline SR_NODISCARD const CameraPtr & SR_GRAPH_NS::IRenderTechnique::GetCamera () noexcept const
```




<hr>



### function GetFrameBufferController 

```C++
SR_NODISCARD const FrameBufferController::Ptr & SR_GRAPH_NS::IRenderTechnique::GetFrameBufferController (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function GetFrameBufferControllers 

```C++
SR_NODISCARD const std::vector< FrameBufferController::Ptr > & SR_GRAPH_NS::IRenderTechnique::GetFrameBufferControllers () const
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_GRAPH_NS::IRenderTechnique::GetName () noexcept const
```




<hr>



### function GetQueues 

```C++
inline SR_NODISCARD const RenderTechniqueQueues & SR_GRAPH_NS::IRenderTechnique::GetQueues () const
```




<hr>



### function GetRenderScene 

```C++
inline SR_NODISCARD const RenderScenePtr & SR_GRAPH_NS::IRenderTechnique::GetRenderScene () noexcept const
```




<hr>



### function GetRenderTechniqueData [1/2]

```C++
inline SR_NODISCARD const RenderTechniqueData & SR_GRAPH_NS::IRenderTechnique::GetRenderTechniqueData () noexcept const
```




<hr>



### function GetRenderTechniqueData [2/2]

```C++
inline SR_NODISCARD RenderTechniqueData & SR_GRAPH_NS::IRenderTechnique::GetRenderTechniqueData () noexcept
```




<hr>



### function IRenderTechnique 

```C++
SR_GRAPH_NS::IRenderTechnique::IRenderTechnique () 
```




<hr>



### function IsEmpty 

```C++
SR_NODISCARD bool SR_GRAPH_NS::IRenderTechnique::IsEmpty () const
```




<hr>



### function IsTechniqueDead 

```C++
SR_NODISCARD bool SR_GRAPH_NS::IRenderTechnique::IsTechniqueDead () const
```




<hr>



### function KillTechnique 

```C++
void SR_GRAPH_NS::IRenderTechnique::KillTechnique () 
```




<hr>



### function OnHierarchyChanged 

```C++
void SR_GRAPH_NS::IRenderTechnique::OnHierarchyChanged () 
```




<hr>



### function OnMultisampleChanged 

```C++
void SR_GRAPH_NS::IRenderTechnique::OnMultisampleChanged () 
```




<hr>



### function OnResize 

```C++
void SR_GRAPH_NS::IRenderTechnique::OnResize (
    const SR_MATH_NS::UVector2 & size
) 
```




<hr>



### function Overlay 

```C++
bool SR_GRAPH_NS::IRenderTechnique::Overlay () 
```




<hr>



### function PickMeshAt [1/4]

```C++
SR_GTYPES_NS::Mesh * SR_GRAPH_NS::IRenderTechnique::PickMeshAt (
    const SR_MATH_NS::FPoint & pos
) const
```




<hr>



### function PickMeshAt [2/4]

```C++
SR_GTYPES_NS::Mesh * SR_GRAPH_NS::IRenderTechnique::PickMeshAt (
    float_t x,
    float_t y
) const
```




<hr>



### function PickMeshAt [3/4]

```C++
SR_GTYPES_NS::Mesh * SR_GRAPH_NS::IRenderTechnique::PickMeshAt (
    float_t x,
    float_t y,
    SR_UTILS_NS::StringAtom passName
) const
```




<hr>



### function PickMeshAt [4/4]

```C++
SR_GTYPES_NS::Mesh * SR_GRAPH_NS::IRenderTechnique::PickMeshAt (
    float_t x,
    float_t y,
    const std::vector< SR_UTILS_NS::StringAtom > & passFilter
) const
```




<hr>



### function PostUpdate 

```C++
void SR_GRAPH_NS::IRenderTechnique::PostUpdate () 
```




<hr>



### function PrepareFrame 

```C++
void SR_GRAPH_NS::IRenderTechnique::PrepareFrame () 
```




<hr>



### function PrepareRender 

```C++
void SR_GRAPH_NS::IRenderTechnique::PrepareRender () 
```




<hr>



### function Render 

```C++
bool SR_GRAPH_NS::IRenderTechnique::Render () 
```




<hr>



### function SetCamera 

```C++
void SR_GRAPH_NS::IRenderTechnique::SetCamera (
    CameraPtr pCamera
) 
```




<hr>



### function SetDirty 

```C++
void SR_GRAPH_NS::IRenderTechnique::SetDirty () 
```




<hr>



### function SetRenderScene 

```C++
void SR_GRAPH_NS::IRenderTechnique::SetRenderScene (
    const RenderScenePtr & pRScene
) 
```




<hr>



### function SetRenderTechniqueData 

```C++
void SR_GRAPH_NS::IRenderTechnique::SetRenderTechniqueData (
    RenderTechniqueData && data
) 
```




<hr>



### function Update 

```C++
void SR_GRAPH_NS::IRenderTechnique::Update () 
```




<hr>



### function ~IRenderTechnique 

```C++
SR_GRAPH_NS::IRenderTechnique::~IRenderTechnique () override
```




<hr>
## Protected Attributes Documentation




### variable m\_camera 

```C++
CameraPtr SR_GRAPH_NS::IRenderTechnique::m_camera;
```




<hr>



### variable m\_data 

```C++
RenderTechniqueData SR_GRAPH_NS::IRenderTechnique::m_data;
```




<hr>



### variable m\_dirty 

```C++
std::atomic<bool> SR_GRAPH_NS::IRenderTechnique::m_dirty;
```




<hr>



### variable m\_hasErrors 

```C++
std::atomic<bool> SR_GRAPH_NS::IRenderTechnique::m_hasErrors;
```




<hr>



### variable m\_isDead 

```C++
std::atomic<bool> SR_GRAPH_NS::IRenderTechnique::m_isDead;
```




<hr>



### variable m\_modulesApplied 

```C++
bool SR_GRAPH_NS::IRenderTechnique::m_modulesApplied;
```




<hr>



### variable m\_renderScene 

```C++
RenderScenePtr SR_GRAPH_NS::IRenderTechnique::m_renderScene;
```




<hr>



### variable m\_surfaceSize 

```C++
std::optional<SR_MATH_NS::UVector2> SR_GRAPH_NS::IRenderTechnique::m_surfaceSize;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/IRenderTechnique.h`

