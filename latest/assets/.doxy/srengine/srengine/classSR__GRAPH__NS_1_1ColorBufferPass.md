

# Class SR\_GRAPH\_NS::ColorBufferPass



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ColorBufferPass**](classSR__GRAPH__NS_1_1ColorBufferPass.md)








Inherits the following classes: [SR\_GRAPH\_NS::OffScreenMeshDrawerPass](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md),  [SR\_GRAPH\_NS::IColorBufferPass](classSR__GRAPH__NS_1_1IColorBufferPass.md)


















## Public Types inherited from SR_GRAPH_NS::IFramebufferPass

See [SR\_GRAPH\_NS::IFramebufferPass](classSR__GRAPH__NS_1_1IFramebufferPass.md)

| Type | Name |
| ---: | :--- |
| typedef std::vector&lt; [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) &gt; | [**ClearColors**](classSR__GRAPH__NS_1_1IFramebufferPass.md#typedef-clearcolors)  <br> |
| typedef std::list&lt; ImageFormat &gt; | [**ColorFormats**](classSR__GRAPH__NS_1_1IFramebufferPass.md#typedef-colorformats)  <br> |
| typedef [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**FramebufferPtr**](classSR__GRAPH__NS_1_1IFramebufferPass.md#typedef-framebufferptr)  <br> |


## Public Types inherited from SR_GRAPH_NS::MeshDrawerPass

See [SR\_GRAPH\_NS::MeshDrawerPass](classSR__GRAPH__NS_1_1MeshDrawerPass.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderQueue**](classSR__GRAPH__NS_1_1RenderQueue.md) &gt; | [**RenderQueuePtr**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#typedef-renderqueueptr)  <br> |


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




























































































































































































































































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**GetColorFrameBuffer**](#function-getcolorframebuffer) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedUseMaterials**](#function-isneedusematerials) () noexcept override const<br> |
| virtual bool | [**Load**](#function-load) (const SR\_XML\_NS::Node & passNode) override<br> |
| virtual bool | [**Render**](#function-render) () override<br>_Вызывается только во время построения_  |
| virtual void | [**UseConstants**](#function-useconstants) ([**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) info) override<br> |


## Public Functions inherited from SR_GRAPH_NS::OffScreenMeshDrawerPass

See [SR\_GRAPH\_NS::OffScreenMeshDrawerPass](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* | [**GetFrameBufferRenderTechnique**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-getframebufferrendertechnique) () override const<br> |
| virtual SR\_NODISCARD std::vector&lt; [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* &gt; | [**GetFrameBuffers**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-getframebuffers) () override const<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetMeshDrawerFBOLayers**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-getmeshdrawerfbolayers) () noexcept override const<br> |
| virtual bool | [**Init**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-init) () override<br> |
| virtual bool | [**Load**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-load) (const SR\_XML\_NS::Node & passNode) override<br> |
| virtual void | [**OnResize**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-onresize) (const SR\_MATH\_NS::UVector2 & size) override<br> |
| virtual bool | [**Render**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-render) () override<br>_Вызывается только во время построения_  |
| virtual void | [**Update**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-update) () override<br>_Вызывается постоянно после построения_  |


## Public Functions inherited from SR_GRAPH_NS::IFramebufferPass

See [SR\_GRAPH\_NS::IFramebufferPass](classSR__GRAPH__NS_1_1IFramebufferPass.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD ClearColors | [**GetClearColors**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-getclearcolors) () noexcept const<br> |
|  SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetClearDepth**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-getcleardepth) () noexcept const<br> |
|  SR\_NODISCARD FramebufferPtr | [**GetFramebuffer**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-getframebuffer) () noexcept const<br> |
|  SR\_NODISCARD uint8\_t | [**GetLayersCount**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-getlayerscount) () noexcept const<br> |
|   | [**IFramebufferPass**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-iframebufferpass) () <br> |
|  SR\_NODISCARD bool | [**IsDirectional**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-isdirectional) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsFrameBufferRendered**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-isframebufferrendered) () noexcept const<br> |
| virtual  | [**~IFramebufferPass**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-iframebufferpass) () = default<br> |


## Public Functions inherited from SR_GRAPH_NS::MeshDrawerPass

See [SR\_GRAPH\_NS::MeshDrawerPass](classSR__GRAPH__NS_1_1MeshDrawerPass.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DeInit**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-deinit) () override<br> |
| virtual SR\_NODISCARD uint8\_t | [**GetMeshDrawerFBOLayers**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-getmeshdrawerfbolayers) () noexcept const<br> |
|  SR\_NODISCARD const std::vector&lt; RenderQueuePtr &gt; & | [**GetRenderQueues**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-getrenderqueues) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**HasPostRender**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-haspostrender) () noexcept override const<br> |
| virtual SR\_NODISCARD bool | [**HasPreRender**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-hasprerender) () noexcept override const<br> |
| virtual bool | [**Init**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-init) () override<br> |
| virtual SR\_NODISCARD bool | [**IsLayerAllowed**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-islayerallowed) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) layer) override const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedUpdate**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-isneedupdate) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsNeedUseMaterials**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-isneedusematerials) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsPriorityAllowed**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-ispriorityallowed) (int64\_t priority) override const<br> |
| virtual bool | [**Load**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-load) (const SR\_XML\_NS::Node & passNode) override<br> |
|   | [**MeshDrawerPass**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-meshdrawerpass) () <br> |
| virtual void | [**Prepare**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-prepare) () override<br>_Вызывается всегда но полсе оверлея_  |
| virtual bool | [**Render**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-render) () override<br>_Вызывается только во время построения_  |
| virtual SR\_NODISCARD [**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) | [**ReplaceShader**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-replaceshader) (ShaderPtr pShader) override const<br> |
| virtual void | [**Update**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-update) () override<br>_Вызывается постоянно после построения_  |
| virtual void | [**UseConstants**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-useconstants) ([**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) info) <br> |
| virtual void | [**UseSharedUniforms**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-useshareduniforms) ([**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) info) <br> |
| virtual void | [**UseUniforms**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-useuniforms) ([**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) info, MeshPtr pMesh) <br> |
|   | [**~MeshDrawerPass**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-meshdrawerpass) () override<br> |


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


## Public Functions inherited from SR_GRAPH_NS::ISamplersPass

See [SR\_GRAPH\_NS::ISamplersPass](classSR__GRAPH__NS_1_1ISamplersPass.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD bool | [**HasSamplers**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-hassamplers) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSamplersDirty**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-issamplersdirty) () noexcept const<br> |
|  void | [**LoadSamplersPass**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-loadsamplerspass) (const SR\_XML\_NS::Node & passNode) <br> |
| virtual void | [**UseSamplers**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-usesamplers) ([**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) info) <br> |
| virtual  | [**~ISamplersPass**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-isamplerspass) () <br> |


## Public Functions inherited from SR_GRAPH_NS::LayerFilterPredicate

See [SR\_GRAPH\_NS::LayerFilterPredicate](classSR__GRAPH__NS_1_1LayerFilterPredicate.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsLayerAllowed**](classSR__GRAPH__NS_1_1LayerFilterPredicate.md#function-islayerallowed) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) layer) const = 0<br> |
| virtual  | [**~LayerFilterPredicate**](classSR__GRAPH__NS_1_1LayerFilterPredicate.md#function-layerfilterpredicate) () = default<br> |


## Public Functions inherited from SR_GRAPH_NS::ShaderReplacePredicate

See [SR\_GRAPH\_NS::ShaderReplacePredicate](classSR__GRAPH__NS_1_1ShaderReplacePredicate.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**SR\_GRAPH\_NS::ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) | [**ReplaceShader**](classSR__GRAPH__NS_1_1ShaderReplacePredicate.md#function-replaceshader) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) const = 0<br> |
| virtual  | [**~ShaderReplacePredicate**](classSR__GRAPH__NS_1_1ShaderReplacePredicate.md#function-shaderreplacepredicate) () = default<br> |


## Public Functions inherited from SR_GRAPH_NS::PriorityFilterPredicate

See [SR\_GRAPH\_NS::PriorityFilterPredicate](classSR__GRAPH__NS_1_1PriorityFilterPredicate.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD bool | [**IsPriorityAllowed**](classSR__GRAPH__NS_1_1PriorityFilterPredicate.md#function-ispriorityallowed) (int64\_t priority) const = 0<br> |
| virtual  | [**~PriorityFilterPredicate**](classSR__GRAPH__NS_1_1PriorityFilterPredicate.md#function-priorityfilterpredicate) () = default<br> |


## Public Functions inherited from SR_GRAPH_NS::IColorBufferPass

See [SR\_GRAPH\_NS::IColorBufferPass](classSR__GRAPH__NS_1_1IColorBufferPass.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**GetColor**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getcolor) (float\_t x, float\_t y) const<br> |
| virtual SR\_NODISCARD [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* | [**GetColorFrameBuffer**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getcolorframebuffer) () noexcept const = 0<br> |
|  SR\_NODISCARD uint32\_t | [**GetColorIndex**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getcolorindex) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetIndex**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getindex) (float\_t x, float\_t y) const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**GetMesh**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getmesh-12) (float\_t x, float\_t y) const<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**GetMesh**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getmesh-22) (SR\_MATH\_NS::FVector2 pos) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetMeshColor**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getmeshcolor) () noexcept const<br> |


















## Public Static Functions inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**LogicalNode**](classSR__SRLM__NS_1_1LogicalNode.md) \* | [**LoadXml**](classSR__SRLM__NS_1_1LogicalNode.md#function-loadxml) (const SR\_XML\_NS::Node & xmlNode) <br> |




























## Protected Types inherited from SR_SRLM_NS::IExecutableNode

See [SR\_SRLM\_NS::IExecutableNode](classSR__SRLM__NS_1_1IExecutableNode.md)

| Type | Name |
| ---: | :--- |
| typedef [**IExecutableNode**](classSR__SRLM__NS_1_1IExecutableNode.md) | [**Base**](classSR__SRLM__NS_1_1IExecutableNode.md#typedef-base)  <br> |


















































## Protected Attributes inherited from SR_GRAPH_NS::IFramebufferPass

See [SR\_GRAPH\_NS::IFramebufferPass](classSR__GRAPH__NS_1_1IFramebufferPass.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_isFrameBufferRendered**](classSR__GRAPH__NS_1_1IFramebufferPass.md#variable-m_isframebufferrendered)   = `false`<br> |




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
































































































































































































































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD RenderQueuePtr | [**AllocateRenderQueue**](#function-allocaterenderqueue) () override<br> |
| virtual void | [**UseUniforms**](#function-useuniforms) ([**ShaderUseInfo**](structSR__GRAPH__NS_1_1ShaderUseInfo.md) info, MeshPtr pMesh) override<br> |


## Protected Functions inherited from SR_GRAPH_NS::OffScreenMeshDrawerPass

See [SR\_GRAPH\_NS::OffScreenMeshDrawerPass](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**RenderFrameBufferInner**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-renderframebufferinner) () override<br> |
| virtual void | [**UpdateFrameBufferInner**](classSR__GRAPH__NS_1_1OffScreenMeshDrawerPass.md#function-updateframebufferinner) () override<br> |


## Protected Functions inherited from SR_GRAPH_NS::IFramebufferPass

See [SR\_GRAPH\_NS::IFramebufferPass](classSR__GRAPH__NS_1_1IFramebufferPass.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* | [**GetFrameBufferRenderTechnique**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-getframebufferrendertechnique) () const = 0<br> |
|  void | [**LoadFramebufferSettings**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-loadframebuffersettings) (const SR\_XML\_NS::Node & passNode) <br> |
|  bool | [**RenderFrameBuffer**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-renderframebuffer-12) (const PipelinePtr & pPipeline) <br> |
| virtual void | [**RenderFrameBufferInner**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-renderframebufferinner) () <br> |
|  void | [**UpdateFrameBuffer**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-updateframebuffer) (const PipelinePtr & pPipeline) <br> |
| virtual void | [**UpdateFrameBufferInner**](classSR__GRAPH__NS_1_1IFramebufferPass.md#function-updateframebufferinner) () <br> |


## Protected Functions inherited from SR_GRAPH_NS::MeshDrawerPass

See [SR\_GRAPH\_NS::MeshDrawerPass](classSR__GRAPH__NS_1_1MeshDrawerPass.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD RenderQueuePtr | [**AllocateRenderQueue**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-allocaterenderqueue) () <br> |
|  SR\_NODISCARD [**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* | [**GetRenderStrategy**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-getrenderstrategy) () const<br> |
| virtual void | [**OnMultisampleChanged**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-onmultisamplechanged) () override<br> |
| virtual void | [**OnResize**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-onresize) (const SR\_MATH\_NS::UVector2 & size) override<br> |
| virtual void | [**OnSamplersChanged**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-onsamplerschanged) () override<br> |
| virtual void | [**SetRenderTechnique**](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-setrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pRenderTechnique) override<br> |




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


## Protected Functions inherited from SR_GRAPH_NS::ISamplersPass

See [SR\_GRAPH\_NS::ISamplersPass](classSR__GRAPH__NS_1_1ISamplersPass.md)

| Type | Name |
| ---: | :--- |
|  void | [**MarkSamplersDirty**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-marksamplersdirty) () <br> |
| virtual void | [**OnSamplersChanged**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-onsamplerschanged) () <br> |
|  void | [**PrepareSamplers**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-preparesamplers) () <br> |
|  void | [**SetISamplerRenderTechnique**](classSR__GRAPH__NS_1_1ISamplersPass.md#function-setisamplerrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pTechnique) <br> |








## Protected Functions inherited from SR_GRAPH_NS::IColorBufferPass

See [SR\_GRAPH\_NS::IColorBufferPass](classSR__GRAPH__NS_1_1IColorBufferPass.md)

| Type | Name |
| ---: | :--- |
|  void | [**ClearTable**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-cleartable) () <br> |
|  void | [**IncrementColorIndex**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-incrementcolorindex) () noexcept<br> |
|  void | [**ResetColorIndex**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-resetcolorindex) () noexcept<br> |
|  void | [**SetColorMultiplier**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-setcolormultiplier) (uint32\_t multiplier) <br> |
|  void | [**SetMeshIndex**](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-setmeshindex) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh) <br> |
































## Public Functions Documentation




### function GetColorFrameBuffer 

```C++
virtual SR_NODISCARD SR_GTYPES_NS::Framebuffer * SR_GRAPH_NS::ColorBufferPass::GetColorFrameBuffer () noexcept override const
```



Implements [*SR\_GRAPH\_NS::IColorBufferPass::GetColorFrameBuffer*](classSR__GRAPH__NS_1_1IColorBufferPass.md#function-getcolorframebuffer)


<hr>



### function IsNeedUseMaterials 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::ColorBufferPass::IsNeedUseMaterials () noexcept override const
```



Implements [*SR\_GRAPH\_NS::MeshDrawerPass::IsNeedUseMaterials*](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-isneedusematerials)


<hr>



### function Load 

```C++
virtual bool SR_GRAPH_NS::ColorBufferPass::Load (
    const SR_XML_NS::Node & passNode
) override
```



Implements [*SR\_GRAPH\_NS::BasePass::Load*](classSR__GRAPH__NS_1_1BasePass.md#function-load)


<hr>



### function Render 

_Вызывается только во время построения_ 
```C++
virtual bool SR_GRAPH_NS::ColorBufferPass::Render () override
```



Implements [*SR\_GRAPH\_NS::BasePass::Render*](classSR__GRAPH__NS_1_1BasePass.md#function-render)


<hr>



### function UseConstants 

```C++
virtual void SR_GRAPH_NS::ColorBufferPass::UseConstants (
    ShaderUseInfo info
) override
```



Implements [*SR\_GRAPH\_NS::MeshDrawerPass::UseConstants*](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-useconstants)


<hr>
## Protected Functions Documentation




### function AllocateRenderQueue 

```C++
virtual SR_NODISCARD RenderQueuePtr SR_GRAPH_NS::ColorBufferPass::AllocateRenderQueue () override
```



Implements [*SR\_GRAPH\_NS::MeshDrawerPass::AllocateRenderQueue*](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-allocaterenderqueue)


<hr>



### function UseUniforms 

```C++
virtual void SR_GRAPH_NS::ColorBufferPass::UseUniforms (
    ShaderUseInfo info,
    MeshPtr pMesh
) override
```



Implements [*SR\_GRAPH\_NS::MeshDrawerPass::UseUniforms*](classSR__GRAPH__NS_1_1MeshDrawerPass.md#function-useuniforms)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Pass/ColorBufferPass.h`

