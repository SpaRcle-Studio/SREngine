

# Class SR\_GRAPH\_NS::ClearBuffersPass



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**ClearBuffersPass**](classSR__GRAPH__NS_1_1ClearBuffersPass.md)








Inherits the following classes: [SR\_GRAPH\_NS::BasePass](classSR__GRAPH__NS_1_1BasePass.md)
















## Public Types inherited from SR_GRAPH_NS::BasePass

See [SR\_GRAPH\_NS::BasePass](classSR__GRAPH__NS_1_1BasePass.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**CameraPtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-cameraptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**Context**](classSR__GRAPH__NS_1_1BasePass.md#typedef-context)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-meshptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-pipelineptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) &gt; | [**Ptr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-rendersceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) &gt; | [**ShaderPtr**](classSR__GRAPH__NS_1_1BasePass.md#typedef-shaderptr)  <br> |


## Public Types inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) &gt; | [**Ptr**](classSR__UTILS__NS_1_1ResourceContainer.md#typedef-ptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |






## Public Types inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Hash**](classSR__SRLM__NS_1_1LogicalNode.md#typedef-hash)  <br> |
| typedef std::vector&lt; [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) &gt; | [**Pins**](classSR__SRLM__NS_1_1LogicalNode.md#typedef-pins)  <br> |




















































































































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**Load**](#function-load) (const SR\_XML\_NS::Node & passNode) override<br> |
| virtual bool | [**Render**](#function-render) () override<br>_Вызывается только во время построения_  |


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
|  void | [**AddDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-adddependency) (const ResourceContainer::Ptr & pContainer) <br> |
|  SR\_NODISCARD const std::unordered\_set&lt; ResourceContainer::Ptr &gt; & | [**GetContainerParents**](classSR__UTILS__NS_1_1ResourceContainer.md#function-getcontainerparents) () const<br> |
|  void | [**RemoveDependency**](classSR__UTILS__NS_1_1ResourceContainer.md#function-removedependency) (const ResourceContainer::Ptr & pContainer) <br> |
|   | [**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md#function-resourcecontainer) () <br> |
|   | [**~ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md#function-resourcecontainer) () override<br> |


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
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
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
|  bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_6) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
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
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |


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








## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |






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
























## Protected Attributes inherited from SR_GRAPH_NS::BasePass

See [SR\_GRAPH\_NS::BasePass](classSR__GRAPH__NS_1_1BasePass.md)

| Type | Name |
| ---: | :--- |
|  CameraPtr | [**m\_camera**](classSR__GRAPH__NS_1_1BasePass.md#variable-m_camera)   = `nullptr`<br> |
|  [**DescriptorManager**](classSR__GRAPH__NS_1_1DescriptorManager.md) & | [**m\_descriptorManager**](classSR__GRAPH__NS_1_1BasePass.md#variable-m_descriptormanager)  <br> |
|  [**Memory::UBOManager**](classSR__GRAPH__NS_1_1Memory_1_1UBOManager.md) & | [**m\_uboManager**](classSR__GRAPH__NS_1_1BasePass.md#variable-m_ubomanager)  <br> |






## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |




## Protected Attributes inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
|  Pins | [**m\_inputs**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_inputs)  <br> |
|  [**LogicalMachine**](classSR__SRLM__NS_1_1LogicalMachine.md) \* | [**m\_machine**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_machine)   = `nullptr`<br> |
|  uint32\_t | [**m\_nodeIndex**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_nodeindex)   = `SR\_UINT32\_MAX`<br> |
|  Pins | [**m\_outputs**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_outputs)  <br> |
|  LogicalNodeStatus | [**m\_status**](classSR__SRLM__NS_1_1LogicalNode.md#variable-m_status)   = `LogicalNodeStatus::None`<br> |
























































































































## Protected Functions inherited from SR_UTILS_NS::ResourceContainer

See [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnResourceUpdated**](classSR__UTILS__NS_1_1ResourceContainer.md#function-onresourceupdated) ([**ResourceContainer**](classSR__UTILS__NS_1_1ResourceContainer.md) \* pContainer, int32\_t depth) <br> |
|  void | [**UpdateResources**](classSR__UTILS__NS_1_1ResourceContainer.md#function-updateresources) (int32\_t depth=0) <br> |






## Protected Functions inherited from SR_SRLM_NS::IExecutableNode

See [SR\_SRLM\_NS::IExecutableNode](classSR__SRLM__NS_1_1IExecutableNode.md)

| Type | Name |
| ---: | :--- |
|   | [**IExecutableNode**](classSR__SRLM__NS_1_1IExecutableNode.md#function-iexecutablenode) () = default<br> |




## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |


















## Public Functions Documentation




### function Load 

```C++
virtual bool SR_GRAPH_NS::ClearBuffersPass::Load (
    const SR_XML_NS::Node & passNode
) override
```



Implements [*SR\_GRAPH\_NS::BasePass::Load*](classSR__GRAPH__NS_1_1BasePass.md#function-load)


<hr>



### function Render 

_Вызывается только во время построения_ 
```C++
virtual bool SR_GRAPH_NS::ClearBuffersPass::Render () override
```



Implements [*SR\_GRAPH\_NS::BasePass::Render*](classSR__GRAPH__NS_1_1BasePass.md#function-render)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/FramebufferPass.h`

