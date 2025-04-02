

# Class SR\_GRAPH\_NS::ScriptableRenderTechnique



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ScriptableRenderTechnique**](classSR__GRAPH__NS_1_1ScriptableRenderTechnique.md)








Inherits the following classes: [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md),  [SR\_SRLM\_NS::LogicalMachine](classSR__SRLM__NS_1_1LogicalMachine.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**ScriptableRenderTechnique**](classSR__GRAPH__NS_1_1ScriptableRenderTechnique.md) \* | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
| typedef Types::Camera \* | [**CameraPtr**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-cameraptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**Context**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-context)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FrameBufferController**](classSR__GRAPH__NS_1_1FrameBufferController.md) &gt; | [**FrameBufferControllerPtr**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-framebuffercontrollerptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-rendersceneptr)  <br> |
| typedef [**Memory::IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) | [**Super**](classSR__GRAPH__NS_1_1IRenderTechnique.md#typedef-super)  <br> |


## Public Types inherited from SR_GRAPH_NS::Memory::IGraphicsResource

See [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#typedef-pipelineptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**RenderContextPtr**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#typedef-rendercontextptr)  <br> |




## Public Types inherited from SR_GRAPH_NS::BasePass

See [SR\_GRAPH\_NS::BasePass](classSR__GRAPH__NS_1_1BasePass.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**CameraPtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-cameraptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**Context**](classSR__GRAPH__NS_1_1BasePass.md#typedef-context)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-meshptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-pipelineptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-rendersceneptr)  <br> |
| typedef [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-shaderptr)  <br> |








## Public Types inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Hash**](classSR__SRLM__NS_1_1LogicalNode.md#typedef-hash)  <br> |
| typedef std::vector&lt; [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) &gt; | [**Pins**](classSR__SRLM__NS_1_1LogicalNode.md#typedef-pins)  <br> |






## Public Types inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**LoadState**](classSR__UTILS__NS_1_1IResource.md#enum-loadstate)  <br> |
| typedef [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**Ptr**](classSR__UTILS__NS_1_1IResource.md#typedef-ptr)  <br> |
| enum uint8\_t | [**RemoveUPResult**](classSR__UTILS__NS_1_1IResource.md#enum-removeupresult)  <br> |


























































## Public Attributes inherited from SR_SRLM_NS::LogicalMachine

See [SR\_SRLM\_NS::LogicalMachine](classSR__SRLM__NS_1_1LogicalMachine.md)

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC uint16\_t | [**VERSION**](classSR__SRLM__NS_1_1LogicalMachine.md#variable-version)   = `1000`<br> |


## Public Attributes inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**RELOAD\_BEGIN\_EVENT**](classSR__UTILS__NS_1_1IResource.md#variable-reload_begin_event)   = `"ReloadBegin"`<br> |
|  SR\_INLINE\_STATIC const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**RELOAD\_DONE\_EVENT**](classSR__UTILS__NS_1_1IResource.md#variable-reload_done_event)   = `"ReloadDone"`<br> |










## Public Static Attributes inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
|  SR\_INLINE const std::string | [**DEFAULT\_RENDER\_TECHNIQUE**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-default_render_technique)   = `"Engine/Configs/MainRenderTechnique.xml"`<br> |
















































































































































































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**UpdateMachine**](#function-updatemachine) (float\_t dt) override<br> |


## Public Functions inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**FreeVideoMemory**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-freevideomemory) () override<br> |
|  SR\_NODISCARD CameraPtr | [**GetCamera**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getcamera) () noexcept const<br> |
|  SR\_NODISCARD FrameBufferControllerPtr | [**GetFrameBufferController**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getframebuffercontroller) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD const PassQueues & | [**GetQueues**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getqueues) () const<br> |
| virtual SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getrenderscene) () override const<br> |
|   | [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-irendertechnique) () <br> |
| virtual bool | [**Init**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-init) () override<br> |
|  SR\_NODISCARD bool | [**IsEmpty**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-isempty) () const<br> |
| virtual void | [**OnMultisampleChanged**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-onmultisamplechanged) () override<br> |
| virtual void | [**OnResize**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-onresize) (const SR\_MATH\_NS::UVector2 & size) override<br> |
| virtual bool | [**Overlay**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-overlay) () override<br>_Вызывается всегда и в самом начале_  |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-14) (const SR\_MATH\_NS::FPoint & pos) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-24) (float\_t x, float\_t y) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-34) (float\_t x, float\_t y, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) passName) const<br> |
|  [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**PickMeshAt**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-pickmeshat-44) (float\_t x, float\_t y, const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & passFilter) const<br> |
| virtual void | [**Prepare**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-prepare) () override<br>_Вызывается всегда но полсе оверлея_  |
| virtual bool | [**Render**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-render) () override<br>_Вызывается только во время построения_  |
|  void | [**SetCamera**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-setcamera) (CameraPtr pCamera) <br> |
|  void | [**SetRenderScene**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-setrenderscene) (const RenderScenePtr & pRScene) <br> |
| virtual void | [**Update**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-update) () override<br>_Вызывается постоянно после построения_  |
|   | [**~IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-irendertechnique) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::Memory::IGraphicsResource

See [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DeInitGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-deinitgraphicsresource) () <br> |
| virtual void | [**FreeVideoMemory**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-freevideomemory) () <br> |
|  SR\_NODISCARD PipelinePtr | [**GetPipeline**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-getpipeline) () noexcept const<br> |
|  SR\_NODISCARD [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) | [**GetRenderContext**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-getrendercontext) () noexcept const<br> |
|   | [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-igraphicsresource-22) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsCalculated**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-iscalculated) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsGraphicsResourceRegistered**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-isgraphicsresourceregistered) () const<br> |
|  void | [**MarkPipelineUnBuild**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-markpipelineunbuild) () <br> |
|  void | [**SetRenderContext**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-setrendercontext) (const [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) & renderContext) <br> |
|  [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) & | [**operator=**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-operator) (const [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md) &) = delete<br> |


## Public Functions inherited from SR_GRAPH_NS::GroupPass

See [SR\_GRAPH\_NS::GroupPass](classSR__GRAPH__NS_1_1GroupPass.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DeInit**](classSR__GRAPH__NS_1_1GroupPass.md#function-deinit) () override<br> |
|  SR\_NODISCARD [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* | [**FindPass**](classSR__GRAPH__NS_1_1GroupPass.md#function-findpass-13) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD T \* | [**FindPass**](classSR__GRAPH__NS_1_1GroupPass.md#function-findpass-23) () const<br> |
|  T \* | [**FindPass**](classSR__GRAPH__NS_1_1GroupPass.md#function-findpass-33) () const<br> |
|  bool | [**ForEachPass**](classSR__GRAPH__NS_1_1GroupPass.md#function-foreachpass) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool([**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \*)&gt; & callback) const<br> |
| virtual bool | [**Init**](classSR__GRAPH__NS_1_1GroupPass.md#function-init) () override<br> |
| virtual bool | [**Load**](classSR__GRAPH__NS_1_1GroupPass.md#function-load) (const SR\_XML\_NS::Node & passNode) override<br> |
| virtual void SR\_FASTCALL | [**OnMeshAdded**](classSR__GRAPH__NS_1_1GroupPass.md#function-onmeshadded) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh, bool transparent) override<br> |
| virtual void SR\_FASTCALL | [**OnMeshRemoved**](classSR__GRAPH__NS_1_1GroupPass.md#function-onmeshremoved) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh, bool transparent) override<br> |
| virtual void | [**OnMultisampleChanged**](classSR__GRAPH__NS_1_1GroupPass.md#function-onmultisamplechanged) () override<br> |
| virtual void | [**OnResize**](classSR__GRAPH__NS_1_1GroupPass.md#function-onresize) (const SR\_MATH\_NS::UVector2 & size) override<br> |
| virtual bool | [**Overlay**](classSR__GRAPH__NS_1_1GroupPass.md#function-overlay) () override<br>_Вызывается всегда и в самом начале_  |
| virtual bool | [**PostRender**](classSR__GRAPH__NS_1_1GroupPass.md#function-postrender) () override<br>_Вызывается только во время построения_  |
| virtual void | [**PostUpdate**](classSR__GRAPH__NS_1_1GroupPass.md#function-postupdate) () override<br> |
| virtual bool | [**PreRender**](classSR__GRAPH__NS_1_1GroupPass.md#function-prerender) () override<br>_Вызывается только во время построения_  |
| virtual void | [**Prepare**](classSR__GRAPH__NS_1_1GroupPass.md#function-prepare) () override<br>_Вызывается всегда но полсе оверлея_  |
| virtual bool | [**Render**](classSR__GRAPH__NS_1_1GroupPass.md#function-render) () override<br>_Вызывается только во время построения_  |
| virtual void | [**SetRenderTechnique**](classSR__GRAPH__NS_1_1GroupPass.md#function-setrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pRenderTechnique) override<br> |
| virtual void | [**Update**](classSR__GRAPH__NS_1_1GroupPass.md#function-update) () override<br>_Вызывается постоянно после построения_  |
|   | [**~GroupPass**](classSR__GRAPH__NS_1_1GroupPass.md#function-grouppass) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::BasePass

See [SR\_GRAPH\_NS::BasePass](classSR__GRAPH__NS_1_1BasePass.md)

| Type | Name |
| ---: | :--- |
|   | [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md#function-basepass) () <br> |
| virtual void | [**Bind**](classSR__GRAPH__NS_1_1BasePass.md#function-bind) () <br>_Вызывается перед PreRender, Render, PostRender, Update._  |
| virtual void | [**DeInit**](classSR__GRAPH__NS_1_1BasePass.md#function-deinit) () <br> |
|  SR\_NODISCARD [**Context**](classSR__GRAPH__NS_1_1RenderContext.md) | [**GetContext**](classSR__GRAPH__NS_1_1BasePass.md#function-getcontext) () const<br> |
| virtual SR\_NODISCARD std::vector&lt; [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* &gt; | [**GetFrameBuffers**](classSR__GRAPH__NS_1_1BasePass.md#function-getframebuffers) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](classSR__GRAPH__NS_1_1BasePass.md#function-getname) () const<br> |
|  SR\_NODISCARD [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* | [**GetParent**](classSR__GRAPH__NS_1_1BasePass.md#function-getparent) () const<br> |
|  SR\_NODISCARD PipelinePtr | [**GetPassPipeline**](classSR__GRAPH__NS_1_1BasePass.md#function-getpasspipeline) () const<br> |
| virtual SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](classSR__GRAPH__NS_1_1BasePass.md#function-getrenderscene) () const<br> |
|  SR\_NODISCARD [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* | [**GetTechnique**](classSR__GRAPH__NS_1_1BasePass.md#function-gettechnique) () const<br> |
| virtual bool | [**HasPostRender**](classSR__GRAPH__NS_1_1BasePass.md#function-haspostrender) () noexcept const<br> |
| virtual bool | [**HasPreRender**](classSR__GRAPH__NS_1_1BasePass.md#function-hasprerender) () noexcept const<br> |
| virtual bool | [**HasRender**](classSR__GRAPH__NS_1_1BasePass.md#function-hasrender) () noexcept const<br> |
| virtual bool | [**HasUpdate**](classSR__GRAPH__NS_1_1BasePass.md#function-hasupdate) () noexcept const<br> |
| virtual bool | [**Init**](classSR__GRAPH__NS_1_1BasePass.md#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsInit**](classSR__GRAPH__NS_1_1BasePass.md#function-isinit) () const<br> |
| virtual bool | [**Load**](classSR__GRAPH__NS_1_1BasePass.md#function-load) (const SR\_XML\_NS::Node & passNode) <br> |
| virtual void SR\_FASTCALL | [**OnMeshAdded**](classSR__GRAPH__NS_1_1BasePass.md#function-onmeshadded) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh, bool transparent) <br> |
| virtual void SR\_FASTCALL | [**OnMeshRemoved**](classSR__GRAPH__NS_1_1BasePass.md#function-onmeshremoved) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh, bool transparent) <br> |
| virtual void | [**OnMultisampleChanged**](classSR__GRAPH__NS_1_1BasePass.md#function-onmultisamplechanged) () <br> |
| virtual void | [**OnResize**](classSR__GRAPH__NS_1_1BasePass.md#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
| virtual bool | [**Overlay**](classSR__GRAPH__NS_1_1BasePass.md#function-overlay) () <br>_Вызывается всегда и в самом начале_  |
| virtual bool | [**PostRender**](classSR__GRAPH__NS_1_1BasePass.md#function-postrender) () <br>_Вызывается только во время построения_  |
| virtual void | [**PostUpdate**](classSR__GRAPH__NS_1_1BasePass.md#function-postupdate) () <br> |
| virtual bool | [**PreRender**](classSR__GRAPH__NS_1_1BasePass.md#function-prerender) () <br>_Вызывается только во время построения_  |
| virtual void | [**Prepare**](classSR__GRAPH__NS_1_1BasePass.md#function-prepare) () <br>_Вызывается всегда но полсе оверлея_  |
| virtual bool | [**Render**](classSR__GRAPH__NS_1_1BasePass.md#function-render) () <br>_Вызывается только во время построения_  |
|  void | [**SetContext**](classSR__GRAPH__NS_1_1BasePass.md#function-setcontext) ([**Context**](classSR__GRAPH__NS_1_1RenderContext.md) pContext) <br> |
|  void | [**SetName**](classSR__GRAPH__NS_1_1BasePass.md#function-setname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  void | [**SetParent**](classSR__GRAPH__NS_1_1BasePass.md#function-setparent) ([**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* pParent) <br> |
| virtual void | [**SetRenderTechnique**](classSR__GRAPH__NS_1_1BasePass.md#function-setrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pRenderTechnique) <br> |
| virtual void | [**Update**](classSR__GRAPH__NS_1_1BasePass.md#function-update) () <br>_Вызывается постоянно после построения_  |
|   | [**~BasePass**](classSR__GRAPH__NS_1_1BasePass.md#function-basepass) () override<br> |


## Public Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-adddependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |
|  SR\_NODISCARD const std::unordered\_set&lt; [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* &gt; & | [**GetContainerParents**](classSR__UTILS__NS_1_1ResourceContainer.md#function-getcontainerparents) () const<br> |
|  void | [**RemoveDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-removedependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_SRLM_NS::IExecutableNode

See [SR\_SRLM\_NS::IExecutableNode](classSR__SRLM__NS_1_1IExecutableNode.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD LogicalNodeType | [**GetType**](classSR__SRLM__NS_1_1IExecutableNode.md#function-gettype) () noexcept const<br> |


## Public Functions inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddInputConnection**](classSR__SRLM__NS_1_1LogicalNode.md#function-addinputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t nodePinIndex, uint32\_t pinIndex) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddInputData**](classSR__SRLM__NS_1_1LogicalNode.md#function-addinputdata-12) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData, uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddInputData**](classSR__SRLM__NS_1_1LogicalNode.md#function-addinputdata-22) (uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  void | [**AddOutputConnection**](classSR__SRLM__NS_1_1LogicalNode.md#function-addoutputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t nodePinIndex, uint32\_t pinIndex) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddOutputData**](classSR__SRLM__NS_1_1LogicalNode.md#function-addoutputdata-12) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData, uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) & | [**AddOutputData**](classSR__SRLM__NS_1_1LogicalNode.md#function-addoutputdata-22) (uint64\_t hashName=SR\_UINT64\_MAX) <br> |
|  SR\_NODISCARD const [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**CalcInput**](classSR__SRLM__NS_1_1LogicalNode.md#function-calcinput) (uint32\_t index) <br> |
|  void | [**ClearLogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md#function-clearlogicalnode) () <br> |
| virtual void | [**Execute**](classSR__SRLM__NS_1_1LogicalNode.md#function-execute) (float\_t dt) <br> |
|  SR\_NODISCARD [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* | [**GetBaseLogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md#function-getbaselogicalnode) () noexcept<br> |
|  SR\_NODISCARD Pins & | [**GetInputs**](classSR__SRLM__NS_1_1LogicalNode.md#function-getinputs) () <br> |
| virtual SR\_NODISCARD uint64\_t | [**GetNodeHashName**](classSR__SRLM__NS_1_1LogicalNode.md#function-getnodehashname) () noexcept const = 0<br> |
|  SR\_NODISCARD uint32\_t | [**GetNodeIndex**](classSR__SRLM__NS_1_1LogicalNode.md#function-getnodeindex) () noexcept const<br> |
| virtual SR\_NODISCARD std::string | [**GetNodeName**](classSR__SRLM__NS_1_1LogicalNode.md#function-getnodename) () noexcept const = 0<br> |
| virtual SR\_NODISCARD const [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**GetOutput**](classSR__SRLM__NS_1_1LogicalNode.md#function-getoutput) (uint32\_t index) <br> |
|  SR\_NODISCARD Pins & | [**GetOutputs**](classSR__SRLM__NS_1_1LogicalNode.md#function-getoutputs) () <br> |
|  SR\_NODISCARD LogicalNodeStatus | [**GetStatus**](classSR__SRLM__NS_1_1LogicalNode.md#function-getstatus) () noexcept const<br> |
| virtual SR\_NODISCARD LogicalNodeType | [**GetType**](classSR__SRLM__NS_1_1LogicalNode.md#function-gettype) () noexcept const = 0<br> |
|  SR\_NODISCARD bool | [**HasErrors**](classSR__SRLM__NS_1_1LogicalNode.md#function-haserrors) () const<br> |
| virtual void | [**InitNode**](classSR__SRLM__NS_1_1LogicalNode.md#function-initnode) () <br> |
| virtual void | [**InitValues**](classSR__SRLM__NS_1_1LogicalNode.md#function-initvalues) () <br> |
| virtual SR\_NODISCARD bool | [**IsDirty**](classSR__SRLM__NS_1_1LogicalNode.md#function-isdirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEntryPoint**](classSR__SRLM__NS_1_1LogicalNode.md#function-isentrypoint) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedPostRepeat**](classSR__SRLM__NS_1_1LogicalNode.md#function-isneedpostrepeat) () const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedRepeat**](classSR__SRLM__NS_1_1LogicalNode.md#function-isneedrepeat) () const<br> |
|  SR\_NODISCARD bool | [**IsSuccessfullyCompleted**](classSR__SRLM__NS_1_1LogicalNode.md#function-issuccessfullycompleted) () noexcept const<br> |
| virtual void | [**MarkDirty**](classSR__SRLM__NS_1_1LogicalNode.md#function-markdirty) () <br> |
|  void | [**RemoveInput**](classSR__SRLM__NS_1_1LogicalNode.md#function-removeinput) (uint32\_t index) <br> |
|  void | [**RemoveInputConnection**](classSR__SRLM__NS_1_1LogicalNode.md#function-removeinputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t pinIndex) <br> |
|  void | [**RemoveOutput**](classSR__SRLM__NS_1_1LogicalNode.md#function-removeoutput) (uint32\_t index) <br> |
|  void | [**RemoveOutputConnection**](classSR__SRLM__NS_1_1LogicalNode.md#function-removeoutputconnection) ([**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* pNode, uint32\_t pinIndex) <br> |
| virtual void | [**Reset**](classSR__SRLM__NS_1_1LogicalNode.md#function-reset) () <br> |
|  void | [**ResetInputFlows**](classSR__SRLM__NS_1_1LogicalNode.md#function-resetinputflows) () <br> |
|  void | [**ResetOutputFlows**](classSR__SRLM__NS_1_1LogicalNode.md#function-resetoutputflows) () <br> |
|  void | [**ResetStatus**](classSR__SRLM__NS_1_1LogicalNode.md#function-resetstatus) () <br> |
| virtual void | [**SaveXml**](classSR__SRLM__NS_1_1LogicalNode.md#function-savexml) (SR\_XML\_NS::Node & xmlNode) <br> |
| virtual void | [**SetInput**](classSR__SRLM__NS_1_1LogicalNode.md#function-setinput) (const [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pInput, uint32\_t index) <br> |
|  void | [**SetMachine**](classSR__SRLM__NS_1_1LogicalNode.md#function-setmachine) ([**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md) \* pMachine) <br> |
|  void | [**SetNodeIndex**](classSR__SRLM__NS_1_1LogicalNode.md#function-setnodeindex) (uint32\_t index) <br> |
|   | [**~LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md#function-logicalnode) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_SRLM_NS::LogicalMachine

See [SR\_SRLM\_NS::LogicalMachine](classSR__SRLM__NS_1_1LogicalMachine.md)

| Type | Name |
| ---: | :--- |
|  bool | [**Init**](classSR__SRLM__NS_1_1LogicalMachine.md#function-init) () <br> |
|  [**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md) \* | [**Load**](classSR__SRLM__NS_1_1LogicalMachine.md#function-load-13) (const Path & rawPath) <br> |
|   | [**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md#function-logicalmachine) () <br> |
| virtual void | [**UpdateMachine**](classSR__SRLM__NS_1_1LogicalMachine.md#function-updatemachine) (float\_t dt) <br> |
|   | [**~LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md#function-logicalmachine) () override<br> |


## Public Functions inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddUsePoint**](classSR__UTILS__NS_1_1IResource.md#function-addusepoint) () <br> |
| virtual void | [**CheckResourceUsage**](classSR__UTILS__NS_1_1IResource.md#function-checkresourceusage) () <br> |
| virtual SR\_NODISCARD [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**CopyResource**](classSR__UTILS__NS_1_1IResource.md#function-copyresource) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* destination) const<br> |
| virtual void | [**DeleteResource**](classSR__UTILS__NS_1_1IResource.md#function-deleteresource) () <br> |
| virtual bool | [**Destroy**](classSR__UTILS__NS_1_1IResource.md#function-destroy) () <br> |
|  bool | [**Execute**](classSR__UTILS__NS_1_1IResource.md#function-execute) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; & fun) const<br> |
|  bool | [**ForceDestroy**](classSR__UTILS__NS_1_1IResource.md#function-forcedestroy) () <br> |
| virtual SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetAssociatedPath**](classSR__UTILS__NS_1_1IResource.md#function-getassociatedpath) () const<br> |
|  SR\_NODISCARD uint16\_t | [**GetCountUses**](classSR__UTILS__NS_1_1IResource.md#function-getcountuses) () noexcept const<br> |
| virtual SR\_NODISCARD uint64\_t | [**GetFileHash**](classSR__UTILS__NS_1_1IResource.md#function-getfilehash) () const<br> |
|  SR\_NODISCARD uint64\_t | [**GetLifetime**](classSR__UTILS__NS_1_1IResource.md#function-getlifetime) () noexcept const<br> |
|  SR\_NODISCARD uint16\_t | [**GetReloadCount**](classSR__UTILS__NS_1_1IResource.md#function-getreloadcount) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetResourceHash**](classSR__UTILS__NS_1_1IResource.md#function-getresourcehash) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetResourceHashName**](classSR__UTILS__NS_1_1IResource.md#function-getresourcehashname) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetResourceId**](classSR__UTILS__NS_1_1IResource.md#function-getresourceid) () noexcept const<br> |
|  SR\_NODISCARD ResourceInfoWeakPtr | [**GetResourceInfo**](classSR__UTILS__NS_1_1IResource.md#function-getresourceinfo) () noexcept const<br> |
|  SR\_NODISCARD LoadState | [**GetResourceLoadState**](classSR__UTILS__NS_1_1IResource.md#function-getresourceloadstate) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetResourceName**](classSR__UTILS__NS_1_1IResource.md#function-getresourcename) () const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetResourcePath**](classSR__UTILS__NS_1_1IResource.md#function-getresourcepath) () const<br> |
| virtual SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**InitializeResourcePath**](classSR__UTILS__NS_1_1IResource.md#function-initializeresourcepath) () const<br> |
|  SR\_NODISCARD bool | [**IsAlive**](classSR__UTILS__NS_1_1IResource.md#function-isalive) () const<br> |
| virtual SR\_NODISCARD bool | [**IsAllowedToRevive**](classSR__UTILS__NS_1_1IResource.md#function-isallowedtorevive) () const<br> |
|  SR\_NODISCARD bool | [**IsDestroyed**](classSR__UTILS__NS_1_1IResource.md#function-isdestroyed) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsFileResource**](classSR__UTILS__NS_1_1IResource.md#function-isfileresource) () noexcept const<br>_является ли ресурс файловым_  |
|  SR\_NODISCARD bool | [**IsForceDestroyed**](classSR__UTILS__NS_1_1IResource.md#function-isforcedestroyed) () const<br> |
|  SR\_NODISCARD bool | [**IsLoaded**](classSR__UTILS__NS_1_1IResource.md#function-isloaded) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsRegistered**](classSR__UTILS__NS_1_1IResource.md#function-isregistered) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResourceFromMemory**](classSR__UTILS__NS_1_1IResource.md#function-isresourcefrommemory) () noexcept const<br> |
|  bool | [**IsResourceType**](classSR__UTILS__NS_1_1IResource.md#function-isresourcetype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsResourceWillBeDeleted**](classSR__UTILS__NS_1_1IResource.md#function-isresourcewillbedeleted) () const<br> |
|  bool | [**Kill**](classSR__UTILS__NS_1_1IResource.md#function-kill) () <br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1IResource.md#function-load) () <br> |
| virtual void | [**OnReloadDone**](classSR__UTILS__NS_1_1IResource.md#function-onreloaddone) () <br> |
| virtual void | [**OnResourceRegistered**](classSR__UTILS__NS_1_1IResource.md#function-onresourceregistered) () <br> |
| virtual bool | [**Reload**](classSR__UTILS__NS_1_1IResource.md#function-reload) () <br> |
| virtual RemoveUPResult | [**RemoveUsePoint**](classSR__UTILS__NS_1_1IResource.md#function-removeusepoint) () <br> |
| virtual void | [**ReviveResource**](classSR__UTILS__NS_1_1IResource.md#function-reviveresource) () <br> |
|  void | [**SetId**](classSR__UTILS__NS_1_1IResource.md#function-setid) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, bool autoRegister=true) <br> |
|  void | [**SetLifetime**](classSR__UTILS__NS_1_1IResource.md#function-setlifetime) (int64\_t lifeTime) <br> |
|  void | [**SetResourceHash**](classSR__UTILS__NS_1_1IResource.md#function-setresourcehash) (uint64\_t hash) <br> |
|  void | [**SignalWatch**](classSR__UTILS__NS_1_1IResource.md#function-signalwatch) () <br> |
| virtual void | [**StartWatch**](classSR__UTILS__NS_1_1IResource.md#function-startwatch) () <br> |
| virtual void | [**StopWatch**](classSR__UTILS__NS_1_1IResource.md#function-stopwatch) () <br> |
| virtual bool | [**Unload**](classSR__UTILS__NS_1_1IResource.md#function-unload) () <br> |
|  void | [**UpdateResourceLifeTime**](classSR__UTILS__NS_1_1IResource.md#function-updateresourcelifetime) () <br> |


## Public Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-adddependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |
|  SR\_NODISCARD const std::unordered\_set&lt; [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* &gt; & | [**GetContainerParents**](classSR__UTILS__NS_1_1ResourceContainer.md#function-getcontainerparents) () const<br> |
|  void | [**RemoveDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-removedependency) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_UTILS_NS::SubscriptionHolder

See [SR\_UTILS\_NS::SubscriptionHolder](classSR__UTILS__NS_1_1SubscriptionHolder.md)

| Type | Name |
| ---: | :--- |
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-12) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) <br> |
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-22) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) & message) <br> |
|  SR\_NODISCARD bool | [**HasSubscriptions**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-hassubscriptions) () noexcept const<br> |
|  SR\_NODISCARD [**Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**Subscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscribe) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) &)&gt; && callback) <br> |
|  void | [**Unsubscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-unsubscribe) (const [**SubscriptionInternalInfo**](classSR__UTILS__NS_1_1SubscriptionInternalInfo.md) \* pSubscription) <br> |
| virtual  | [**~SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**ScriptableRenderTechnique::Ptr**](classSR__GRAPH__NS_1_1ScriptableRenderTechnique.md) | [**Load**](#function-load) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
















## Public Static Functions inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* | [**LoadXml**](classSR__SRLM__NS_1_1LogicalNode.md#function-loadxml) (const SR\_XML\_NS::Node & xmlNode) <br> |




## Public Static Functions inherited from SR_SRLM_NS::LogicalMachine

See [SR\_SRLM\_NS::LogicalMachine](classSR__SRLM__NS_1_1LogicalMachine.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md) \* | [**Load**](classSR__SRLM__NS_1_1LogicalMachine.md#function-load-23) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & rawPath) <br> |
























## Protected Types inherited from SR_SRLM_NS::IExecutableNode

See [SR\_SRLM\_NS::IExecutableNode](classSR__SRLM__NS_1_1IExecutableNode.md)

| Type | Name |
| ---: | :--- |
| typedef [**IExecutableNode**](classSR__SRLM__NS_1_1IExecutableNode.md) | [**Base**](classSR__SRLM__NS_1_1IExecutableNode.md#typedef-base)  <br> |
















































## Protected Attributes inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
|  std::atomic&lt; bool &gt; | [**m\_dirty**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_dirty)   = `false`<br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), FrameBufferControllerPtr &gt; | [**m\_frameBufferControllers**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_framebuffercontrollers)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_hasErrors**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_haserrors)   = `false`<br> |
|  PassQueues | [**m\_queues**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_queues)  <br> |
|  RenderScenePtr | [**m\_renderScene**](classSR__GRAPH__NS_1_1IRenderTechnique.md#variable-m_renderscene)  <br> |


## Protected Attributes inherited from SR_GRAPH_NS::Memory::IGraphicsResource

See [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_isCalculated**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#variable-m_iscalculated)   = `false`<br> |
|  PipelinePtr | [**m\_pipeline**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#variable-m_pipeline)  <br> |
|  [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) | [**m\_renderContext**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#variable-m_rendercontext)   = `nullptr`<br> |


## Protected Attributes inherited from SR_GRAPH_NS::GroupPass

See [SR\_GRAPH\_NS::GroupPass](classSR__GRAPH__NS_1_1GroupPass.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* &gt; | [**m\_passes**](classSR__GRAPH__NS_1_1GroupPass.md#variable-m_passes)  <br> |


## Protected Attributes inherited from SR_GRAPH_NS::BasePass

See [SR\_GRAPH\_NS::BasePass](classSR__GRAPH__NS_1_1BasePass.md)

| Type | Name |
| ---: | :--- |
|  CameraPtr | [**m\_camera**](classSR__GRAPH__NS_1_1BasePass.md#variable-m_camera)   = `nullptr`<br> |
|  [**DescriptorManager**](classSR__GRAPH__NS_1_1DescriptorManager.md) & | [**m\_descriptorManager**](classSR__GRAPH__NS_1_1BasePass.md#variable-m_descriptormanager)  <br> |
|  [**Memory::UBOManager**](classSR__GRAPH__NS_1_1Memory_1_1UBOManager.md) & | [**m\_uboManager**](classSR__GRAPH__NS_1_1BasePass.md#variable-m_ubomanager)  <br> |








## Protected Attributes inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
|  Pins | [**m\_inputs**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_inputs)  <br> |
|  [**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md) \* | [**m\_machine**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_machine)   = `nullptr`<br> |
|  uint32\_t | [**m\_nodeIndex**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_nodeindex)   = `SR\_UINT32\_MAX`<br> |
|  Pins | [**m\_outputs**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_outputs)  <br> |
|  LogicalNodeStatus | [**m\_status**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_status)   = `LogicalNodeStatus::None`<br> |






## Protected Attributes inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|  std::atomic&lt; uint16\_t &gt; | [**m\_countUses**](classSR__UTILS__NS_1_1IResource.md#variable-m_countuses)   = `0`<br>_не рекомендуется вручную обращаться к счетчику при наследовании_  |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUnUseStackTraces**](classSR__UTILS__NS_1_1IResource.md#variable-m_debugunusestacktraces)  <br> |
|  std::list&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**m\_debugUseStackTraces**](classSR__UTILS__NS_1_1IResource.md#variable-m_debugusestacktraces)  <br> |
|  std::atomic&lt; bool &gt; | [**m\_isFromMemory**](classSR__UTILS__NS_1_1IResource.md#variable-m_isfrommemory)   = `false`<br> |
|  std::atomic&lt; LoadState &gt; | [**m\_loadState**](classSR__UTILS__NS_1_1IResource.md#variable-m_loadstate)   = `LoadState::Unknown`<br> |
|  const uint64\_t | [**m\_resourceHashName**](classSR__UTILS__NS_1_1IResource.md#variable-m_resourcehashname)   = `0`<br> |
|  std::list&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**FileWatcher**](classSR__UTILS__NS_1_1FileWatcher.md) &gt; &gt; | [**m\_watchers**](classSR__UTILS__NS_1_1IResource.md#variable-m_watchers)  <br> |




























































































































































































































## Protected Functions inherited from SR_GRAPH_NS::IRenderTechnique

See [SR\_GRAPH\_NS::IRenderTechnique](classSR__GRAPH__NS_1_1IRenderTechnique.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**Build**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-build) () <br> |
|  void | [**DeInitPasses**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-deinitpasses) () <br> |
| virtual SR\_NODISCARD uint64\_t | [**GetNodeHashName**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getnodehashname) () noexcept override const<br> |
| virtual SR\_NODISCARD std::string | [**GetNodeName**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-getnodename) () noexcept override const<br> |
|  void | [**ReleaseFrameBufferControllers**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-releaseframebuffercontrollers) () <br> |
|  void | [**SetDirty**](classSR__GRAPH__NS_1_1IRenderTechnique.md#function-setdirty) () <br> |


## Protected Functions inherited from SR_GRAPH_NS::Memory::IGraphicsResource

See [SR\_GRAPH\_NS::Memory::IGraphicsResource](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-igraphicsresource-12) () = default<br> |
| virtual  | [**~IGraphicsResource**](classSR__GRAPH__NS_1_1Memory_1_1IGraphicsResource.md#function-igraphicsresource) () <br> |






## Protected Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnResourceUpdated**](classSR__UTILS__NS_1_1ResourceContainer.md#function-onresourceupdated) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer, int32\_t depth) <br> |
|  void | [**UpdateResources**](classSR__UTILS__NS_1_1ResourceContainer.md#function-updateresources) (int32\_t depth=0) <br> |
|   | [**~ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md#function-resourcecontainer) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |


## Protected Functions inherited from SR_SRLM_NS::IExecutableNode

See [SR\_SRLM\_NS::IExecutableNode](classSR__SRLM__NS_1_1IExecutableNode.md)

| Type | Name |
| ---: | :--- |
|   | [**IExecutableNode**](classSR__SRLM__NS_1_1IExecutableNode.md#function-iexecutablenode) () = default<br> |




## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |




## Protected Functions inherited from SR_UTILS_NS::IResource

See [SR\_UTILS\_NS::IResource](classSR__UTILS__NS_1_1IResource.md)

| Type | Name |
| ---: | :--- |
|   | [**IResource**](classSR__UTILS__NS_1_1IResource.md#function-iresource) (uint64\_t hashName) <br> |
|   | [**~IResource**](classSR__UTILS__NS_1_1IResource.md#function-iresource) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnResourceUpdated**](classSR__UTILS__NS_1_1ResourceContainer.md#function-onresourceupdated) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer, int32\_t depth) <br> |
|  void | [**UpdateResources**](classSR__UTILS__NS_1_1ResourceContainer.md#function-updateresources) (int32\_t depth=0) <br> |
|   | [**~ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md#function-resourcecontainer) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |


































## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::ScriptableRenderTechnique::Ptr =  ScriptableRenderTechnique*;
```




<hr>
## Public Functions Documentation




### function UpdateMachine 

```C++
virtual void SR_GRAPH_NS::ScriptableRenderTechnique::UpdateMachine (
    float_t dt
) override
```



Implements [*SR\_SRLM\_NS::LogicalMachine::UpdateMachine*](classSR__SRLM__NS_1_1LogicalMachine.md#function-updatemachine)


<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD ScriptableRenderTechnique::Ptr SR_GRAPH_NS::ScriptableRenderTechnique::Load (
    const SR_UTILS_NS::Path & path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Render/ScriptableRenderTechnique.h`

