

# Class SR\_GRAPH\_NS::FileRenderTechnique



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**FileRenderTechnique**](classSR__GRAPH__NS_1_1FileRenderTechnique.md)








Inherits the following classes: [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FileRenderTechnique**](classSR__GRAPH__NS_1_1FileRenderTechnique.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
| typedef Types::Camera \* | [**CameraPtr**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-cameraptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) &gt; | [**Ptr**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-rendersceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) &gt; | [**Super**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-super)  <br> |


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
|   | [**FileRenderTechnique**](#function-filerendertechnique) () = default<br> |
|   | [**~FileRenderTechnique**](#function-filerendertechnique) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* | [**FindPass**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-findpass) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  void | [**ForEachPass**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-foreachpass) (const std::function&lt; void([**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) &)&gt; & func) <br> |
| virtual void | [**FreeVMemory**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-freevmemory) () override<br> |
|  SR\_NODISCARD const CameraPtr & | [**GetCamera**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getcamera) () noexcept const<br> |
|  SR\_NODISCARD const FrameBufferController::Ptr & | [**GetFrameBufferController**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getframebuffercontroller) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD const std::vector&lt; FrameBufferController::Ptr &gt; & | [**GetFrameBufferControllers**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getframebuffercontrollers) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getname) () noexcept const<br> |
|  SR\_NODISCARD const RenderTechniqueQueues & | [**GetQueues**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getqueues) () const<br> |
|  SR\_NODISCARD const RenderScenePtr & | [**GetRenderScene**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getrenderscene) () noexcept const<br> |
|  SR\_NODISCARD const [**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) & | [**GetRenderTechniqueData**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getrendertechniquedata-12) () noexcept const<br> |
|  SR\_NODISCARD [**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) & | [**GetRenderTechniqueData**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getrendertechniquedata-22) () noexcept<br> |
|   | [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-irendertechnique) () <br> |
|  SR\_NODISCARD bool | [**IsEmpty**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-isempty) () const<br> |
|  SR\_NODISCARD bool | [**IsTechniqueDead**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-istechniquedead) () const<br> |
|  void | [**KillTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-killtechnique) () <br> |
|  void | [**OnHierarchyChanged**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-onhierarchychanged) () <br> |
|  void | [**OnMultisampleChanged**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-onmultisamplechanged) () <br> |
|  void | [**OnResize**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
|  bool | [**Overlay**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-overlay) () <br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-14) (const SR\_MATH\_NS::FPoint & pos) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-24) (float\_t x, float\_t y) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-34) (float\_t x, float\_t y, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) passName) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-44) (float\_t x, float\_t y, const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & passFilter) const<br> |
|  void | [**PostUpdate**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-postupdate) () <br> |
|  void | [**PrepareFrame**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-prepareframe) () <br> |
|  void | [**PrepareRender**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-preparerender) () <br> |
|  bool | [**Render**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-render) () <br> |
|  void | [**SetCamera**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-setcamera) (CameraPtr pCamera) <br> |
|  void | [**SetDirty**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-setdirty) () <br> |
|  void | [**SetRenderScene**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-setrenderscene) (const RenderScenePtr & pRScene) <br> |
|  void | [**SetRenderTechniqueData**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-setrendertechniquedata) ([**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) && data) <br> |
|  void | [**Update**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-update) () <br> |
|   | [**~IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-irendertechnique) () override<br> |


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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  FileRenderTechnique::Ptr | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |






## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |


























## Protected Attributes inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
|  CameraPtr | [**m\_camera**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_camera)   = `nullptr`<br> |
|  [**RenderTechniqueData**](structSR__GRAPH__NS_1_1RenderTechniqueData.md) | [**m\_data**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_data)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_dirty**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_dirty)   = `true`<br> |
|  std::atomic&lt; bool &gt; | [**m\_hasErrors**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_haserrors)   = `false`<br> |
|  std::atomic&lt; bool &gt; | [**m\_isDead**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_isdead)   = `false`<br> |
|  bool | [**m\_modulesApplied**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_modulesapplied)   = `false`<br> |
|  RenderScenePtr | [**m\_renderScene**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_renderscene)  <br> |
|  std::optional&lt; SR\_MATH\_NS::UVector2 &gt; | [**m\_surfaceSize**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_surfacesize)  <br> |






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




### typedef Ptr 

```C++
using SR_GRAPH_NS::FileRenderTechnique::Ptr =  SR_HTYPES_NS::SharedPtr<FileRenderTechnique>;
```




<hr>
## Public Functions Documentation




### function FileRenderTechnique 

```C++
SR_GRAPH_NS::FileRenderTechnique::FileRenderTechnique () = default
```




<hr>



### function ~FileRenderTechnique 

```C++
SR_GRAPH_NS::FileRenderTechnique::~FileRenderTechnique () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static FileRenderTechnique::Ptr SR_GRAPH_NS::FileRenderTechnique::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderTechnique.h`

