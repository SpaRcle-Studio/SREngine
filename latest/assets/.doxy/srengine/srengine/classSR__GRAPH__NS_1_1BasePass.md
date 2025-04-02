

# Class SR\_GRAPH\_NS::BasePass



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md)








Inherits the following classes: [SR\_UTILS\_NS::ResourceContainer](classSR__UTILS__NS_1_1ResourceContainer.md),  [SR\_SRLM\_NS::IExecutableNode](classSR__SRLM__NS_1_1IExecutableNode.md)


Inherited by the following classes: [SR\_GRAPH\_NS::ClearBuffersPass](classSR__GRAPH__NS_1_1ClearBuffersPass.md),  [SR\_GRAPH\_NS::DebugPass](classSR__GRAPH__NS_1_1DebugPass.md),  [SR\_GRAPH\_NS::GroupPass](classSR__GRAPH__NS_1_1GroupPass.md),  [SR\_GRAPH\_NS::IMeshClusterPass](classSR__GRAPH__NS_1_1IMeshClusterPass.md),  [SR\_GRAPH\_NS::MeshDrawerPass](classSR__GRAPH__NS_1_1MeshDrawerPass.md),  [SR\_GRAPH\_NS::PostProcessPass](classSR__GRAPH__NS_1_1PostProcessPass.md),  [SR\_GRAPH\_NS::SkyboxPass](classSR__GRAPH__NS_1_1SkyboxPass.md),  [SR\_GRAPH\_NS::WidgetPass](classSR__GRAPH__NS_1_1WidgetPass.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**CameraPtr**](#typedef-cameraptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**Context**](#typedef-context)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](#typedef-meshptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](#typedef-pipelineptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |
| typedef [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](#typedef-shaderptr)  <br> |








## Public Types inherited from SR_SRLM_NS::LogicalNode

See [SR\_SRLM\_NS::LogicalNode](classSR__SRLM__NS_1_1LogicalNode.md)

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Hash**](classSR__SRLM__NS_1_1LogicalNode.md#typedef-hash)  <br> |
| typedef std::vector&lt; [**NodePin**](structSR__SRLM__NS_1_1LogicalNode_1_1NodePin.md) &gt; | [**Pins**](classSR__SRLM__NS_1_1LogicalNode.md#typedef-pins)  <br> |
















































































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BasePass**](#function-basepass) () <br> |
| virtual void | [**Bind**](#function-bind) () <br>_Вызывается перед PreRender, Render, PostRender, Update._  |
| virtual void | [**DeInit**](#function-deinit) () <br> |
|  SR\_NODISCARD [**Context**](classSR__GRAPH__NS_1_1RenderContext.md) | [**GetContext**](#function-getcontext) () const<br> |
| virtual SR\_NODISCARD std::vector&lt; [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) \* &gt; | [**GetFrameBuffers**](#function-getframebuffers) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* | [**GetParent**](#function-getparent) () const<br> |
|  SR\_NODISCARD PipelinePtr | [**GetPassPipeline**](#function-getpasspipeline) () const<br> |
| virtual SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  SR\_NODISCARD [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* | [**GetTechnique**](#function-gettechnique) () const<br> |
| virtual bool | [**HasPostRender**](#function-haspostrender) () noexcept const<br> |
| virtual bool | [**HasPreRender**](#function-hasprerender) () noexcept const<br> |
| virtual bool | [**HasRender**](#function-hasrender) () noexcept const<br> |
| virtual bool | [**HasUpdate**](#function-hasupdate) () noexcept const<br> |
| virtual bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsInit**](#function-isinit) () const<br> |
| virtual bool | [**Load**](#function-load) (const SR\_XML\_NS::Node & passNode) <br> |
| virtual void SR\_FASTCALL | [**OnMeshAdded**](#function-onmeshadded) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh, bool transparent) <br> |
| virtual void SR\_FASTCALL | [**OnMeshRemoved**](#function-onmeshremoved) ([**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* pMesh, bool transparent) <br> |
| virtual void | [**OnMultisampleChanged**](#function-onmultisamplechanged) () <br> |
| virtual void | [**OnResize**](#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
| virtual bool | [**Overlay**](#function-overlay) () <br>_Вызывается всегда и в самом начале_  |
| virtual bool | [**PostRender**](#function-postrender) () <br>_Вызывается только во время построения_  |
| virtual void | [**PostUpdate**](#function-postupdate) () <br> |
| virtual bool | [**PreRender**](#function-prerender) () <br>_Вызывается только во время построения_  |
| virtual void | [**Prepare**](#function-prepare) () <br>_Вызывается всегда но полсе оверлея_  |
| virtual bool | [**Render**](#function-render) () <br>_Вызывается только во время построения_  |
|  void | [**SetContext**](#function-setcontext) ([**Context**](classSR__GRAPH__NS_1_1RenderContext.md) pContext) <br> |
|  void | [**SetName**](#function-setname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  void | [**SetParent**](#function-setparent) ([**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* pParent) <br> |
| virtual void | [**SetRenderTechnique**](#function-setrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pRenderTechnique) <br> |
| virtual void | [**Update**](#function-update) () <br>_Вызывается постоянно после построения_  |
|   | [**~BasePass**](#function-basepass) () override<br> |


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


















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  CameraPtr | [**m\_camera**](#variable-m_camera)   = `nullptr`<br> |
|  [**DescriptorManager**](classSR__GRAPH__NS_1_1DescriptorManager.md) & | [**m\_descriptorManager**](#variable-m_descriptormanager)  <br> |
|  [**Memory::UBOManager**](classSR__GRAPH__NS_1_1Memory_1_1UBOManager.md) & | [**m\_uboManager**](#variable-m_ubomanager)  <br> |








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














## Public Types Documentation




### typedef CameraPtr 

```C++
using SR_GRAPH_NS::BasePass::CameraPtr =  SR_GTYPES_NS::Camera*;
```




<hr>



### typedef Context 

```C++
using SR_GRAPH_NS::BasePass::Context =  RenderContext*;
```




<hr>



### typedef MeshPtr 

```C++
using SR_GRAPH_NS::BasePass::MeshPtr =  SR_GTYPES_NS::Mesh*;
```




<hr>



### typedef PipelinePtr 

```C++
using SR_GRAPH_NS::BasePass::PipelinePtr =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef RenderScenePtr 

```C++
using SR_GRAPH_NS::BasePass::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<RenderScene>;
```




<hr>



### typedef ShaderPtr 

```C++
using SR_GRAPH_NS::BasePass::ShaderPtr =  SR_GTYPES_NS::Shader*;
```




<hr>
## Public Functions Documentation




### function BasePass 

```C++
SR_GRAPH_NS::BasePass::BasePass () 
```




<hr>



### function Bind 

_Вызывается перед PreRender, Render, PostRender, Update._ 
```C++
inline virtual void SR_GRAPH_NS::BasePass::Bind () 
```




<hr>



### function DeInit 

```C++
virtual void SR_GRAPH_NS::BasePass::DeInit () 
```




<hr>



### function GetContext 

```C++
inline SR_NODISCARD Context SR_GRAPH_NS::BasePass::GetContext () const
```




<hr>



### function GetFrameBuffers 

```C++
inline virtual SR_NODISCARD std::vector< SR_GTYPES_NS::Framebuffer * > SR_GRAPH_NS::BasePass::GetFrameBuffers () const
```




<hr>



### function GetName 

```C++
SR_NODISCARD SR_UTILS_NS::StringAtom SR_GRAPH_NS::BasePass::GetName () const
```




<hr>



### function GetParent 

```C++
inline SR_NODISCARD BasePass * SR_GRAPH_NS::BasePass::GetParent () const
```




<hr>



### function GetPassPipeline 

```C++
inline SR_NODISCARD PipelinePtr SR_GRAPH_NS::BasePass::GetPassPipeline () const
```




<hr>



### function GetRenderScene 

```C++
virtual SR_NODISCARD RenderScenePtr SR_GRAPH_NS::BasePass::GetRenderScene () const
```




<hr>



### function GetTechnique 

```C++
inline SR_NODISCARD IRenderTechnique * SR_GRAPH_NS::BasePass::GetTechnique () const
```




<hr>



### function HasPostRender 

```C++
inline virtual bool SR_GRAPH_NS::BasePass::HasPostRender () noexcept const
```




<hr>



### function HasPreRender 

```C++
inline virtual bool SR_GRAPH_NS::BasePass::HasPreRender () noexcept const
```




<hr>



### function HasRender 

```C++
inline virtual bool SR_GRAPH_NS::BasePass::HasRender () noexcept const
```




<hr>



### function HasUpdate 

```C++
inline virtual bool SR_GRAPH_NS::BasePass::HasUpdate () noexcept const
```




<hr>



### function Init 

```C++
virtual bool SR_GRAPH_NS::BasePass::Init () 
```




<hr>



### function IsInit 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::BasePass::IsInit () const
```




<hr>



### function Load 

```C++
virtual bool SR_GRAPH_NS::BasePass::Load (
    const SR_XML_NS::Node & passNode
) 
```




<hr>



### function OnMeshAdded 

```C++
inline virtual void SR_FASTCALL SR_GRAPH_NS::BasePass::OnMeshAdded (
    SR_GTYPES_NS::Mesh * pMesh,
    bool transparent
) 
```




<hr>



### function OnMeshRemoved 

```C++
inline virtual void SR_FASTCALL SR_GRAPH_NS::BasePass::OnMeshRemoved (
    SR_GTYPES_NS::Mesh * pMesh,
    bool transparent
) 
```




<hr>



### function OnMultisampleChanged 

```C++
inline virtual void SR_GRAPH_NS::BasePass::OnMultisampleChanged () 
```




<hr>



### function OnResize 

```C++
inline virtual void SR_GRAPH_NS::BasePass::OnResize (
    const SR_MATH_NS::UVector2 & size
) 
```




<hr>



### function Overlay 

_Вызывается всегда и в самом начале_ 
```C++
inline virtual bool SR_GRAPH_NS::BasePass::Overlay () 
```




<hr>



### function PostRender 

_Вызывается только во время построения_ 
```C++
inline virtual bool SR_GRAPH_NS::BasePass::PostRender () 
```




<hr>



### function PostUpdate 

```C++
inline virtual void SR_GRAPH_NS::BasePass::PostUpdate () 
```




<hr>



### function PreRender 

_Вызывается только во время построения_ 
```C++
inline virtual bool SR_GRAPH_NS::BasePass::PreRender () 
```




<hr>



### function Prepare 

_Вызывается всегда но полсе оверлея_ 
```C++
inline virtual void SR_GRAPH_NS::BasePass::Prepare () 
```




<hr>



### function Render 

_Вызывается только во время построения_ 
```C++
inline virtual bool SR_GRAPH_NS::BasePass::Render () 
```




<hr>



### function SetContext 

```C++
void SR_GRAPH_NS::BasePass::SetContext (
    Context pContext
) 
```




<hr>



### function SetName 

```C++
void SR_GRAPH_NS::BasePass::SetName (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function SetParent 

```C++
inline void SR_GRAPH_NS::BasePass::SetParent (
    BasePass * pParent
) 
```




<hr>



### function SetRenderTechnique 

```C++
virtual void SR_GRAPH_NS::BasePass::SetRenderTechnique (
    IRenderTechnique * pRenderTechnique
) 
```




<hr>



### function Update 

_Вызывается постоянно после построения_ 
```C++
inline virtual void SR_GRAPH_NS::BasePass::Update () 
```




<hr>



### function ~BasePass 

```C++
SR_GRAPH_NS::BasePass::~BasePass () override
```




<hr>
## Protected Attributes Documentation




### variable m\_camera 

```C++
CameraPtr SR_GRAPH_NS::BasePass::m_camera;
```




<hr>



### variable m\_descriptorManager 

```C++
DescriptorManager& SR_GRAPH_NS::BasePass::m_descriptorManager;
```




<hr>



### variable m\_uboManager 

```C++
Memory::UBOManager& SR_GRAPH_NS::BasePass::m_uboManager;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Pass/BasePass.h`

