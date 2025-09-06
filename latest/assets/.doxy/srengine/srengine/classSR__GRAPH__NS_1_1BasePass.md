

# Class SR\_GRAPH\_NS::BasePass



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md)



_@abstract_ 

* `#include <BasePass.h>`



Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md),  [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)


Inherited by the following classes: [SR\_GRAPH\_NS::ClearBuffersPass](classSR__GRAPH__NS_1_1ClearBuffersPass.md),  [SR\_GRAPH\_NS::DebugPass](classSR__GRAPH__NS_1_1DebugPass.md),  [SR\_GRAPH\_NS::GroupPass](classSR__GRAPH__NS_1_1GroupPass.md),  [SR\_GRAPH\_NS::MeshDrawerPass](classSR__GRAPH__NS_1_1MeshDrawerPass.md),  [SR\_GRAPH\_NS::PostProcessPass](classSR__GRAPH__NS_1_1PostProcessPass.md),  [SR\_GRAPH\_NS::SkyboxPass](classSR__GRAPH__NS_1_1SkyboxPass.md),  [SR\_GRAPH\_NS::WidgetPass](classSR__GRAPH__NS_1_1WidgetPass.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**CameraPtr**](#typedef-cameraptr)  <br> |
| typedef std::vector&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) &gt; &gt; | [**FrameBuffers**](#typedef-framebuffers)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](#typedef-meshptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](#typedef-pipelineptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**RenderContextPtr**](#typedef-rendercontextptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) &gt; | [**ShaderPtr**](#typedef-shaderptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |




## Public Types inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
| typedef [**Serializable**](classSR__UTILS__NS_1_1Serializable.md) | [**OriginType**](classSR__UTILS__NS_1_1Serializable.md#typedef-origintype)  <br> |






























































































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BasePass**](#function-basepass) () <br> |
| virtual void | [**Bind**](#function-bind) () <br>_Вызывается перед PreRender, Render, PostRender, Update._  |
| virtual void | [**DeInit**](#function-deinit) () <br> |
| virtual SR\_NODISCARD [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* | [**FindPass**](#function-findpass) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
| virtual void | [**ForEachPass**](#function-foreachpass) (const std::function&lt; void([**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) &)&gt; & func) <br> |
|  SR\_NODISCARD const CameraPtr & | [**GetCamera**](#function-getcamera) () const<br> |
|  SR\_NODISCARD [**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* | [**GetParent**](#function-getparent) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetPassName**](#function-getpassname) () const<br> |
|  SR\_NODISCARD const PipelinePtr & | [**GetPipeline**](#function-getpipeline) () const<br> |
|  SR\_NODISCARD const [**RenderContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) & | [**GetRenderContext**](#function-getrendercontext) () const<br> |
|  SR\_NODISCARD const RenderScenePtr & | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  SR\_NODISCARD [**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* | [**GetTechnique**](#function-gettechnique) () const<br> |
| virtual bool | [**HasPostRender**](#function-haspostrender) () noexcept const<br> |
| virtual bool | [**HasPreRender**](#function-hasprerender) () noexcept const<br> |
| virtual bool | [**HasRender**](#function-hasrender) () noexcept const<br> |
| virtual bool | [**HasUpdate**](#function-hasupdate) () noexcept const<br> |
| virtual bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsActive**](#function-isactive) () const<br> |
|  SR\_NODISCARD bool | [**IsInit**](#function-isinit) () const<br> |
| virtual void | [**OnMultisampleChanged**](#function-onmultisamplechanged) () <br> |
| virtual void | [**OnResize**](#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
| virtual bool | [**Overlay**](#function-overlay) () <br>_Вызывается всегда и в самом начале_  |
| virtual bool | [**PostRender**](#function-postrender) () <br>_Вызывается только во время построения_  |
| virtual void | [**PostUpdate**](#function-postupdate) () <br> |
| virtual bool | [**PreRender**](#function-prerender) () <br>_Вызывается только во время построения_  |
| virtual void | [**Prepare**](#function-prepare) () <br>_Вызывается всегда но полсе оверлея_  |
| virtual bool | [**Render**](#function-render) () <br>_Вызывается только во время построения_  |
| virtual void | [**SetParent**](#function-setparent) ([**BasePass**](classSR__GRAPH__NS_1_1BasePass.md) \* pParent) <br> |
| virtual void | [**SetRenderTechnique**](#function-setrendertechnique) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pRenderTechnique) <br> |
| virtual void | [**Update**](#function-update) () <br>_Вызывается постоянно после построения_  |
| virtual void | [**UseSamplers**](#function-usesamplers) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |
| virtual void | [**UseUniformsFromAnotherPass**](#function-useuniformsfromanotherpass) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |
|   | [**~BasePass**](#function-basepass) () override<br> |


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


## Public Functions inherited from SR_UTILS_NS::Serializable

See [SR\_UTILS\_NS::Serializable](classSR__UTILS__NS_1_1Serializable.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-addserializationflags) (SerializationFlags flags) noexcept<br> |
|  SR\_NODISCARD bool | [**HasSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-hasserializationflags) (SerializationFlags flags) noexcept const<br> |
| virtual bool | [**Load**](classSR__UTILS__NS_1_1Serializable.md#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer) <br> |
| virtual void | [**OnPostLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpostload) () <br> |
| virtual void | [**OnPostSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpostsave) () <br> |
| virtual void | [**OnPreLoad**](classSR__UTILS__NS_1_1Serializable.md#function-onpreload) () <br> |
| virtual void | [**OnPreSave**](classSR__UTILS__NS_1_1Serializable.md#function-onpresave) () <br> |
|  void | [**RemoveSerializationFlags**](classSR__UTILS__NS_1_1Serializable.md#function-removeserializationflags) (SerializationFlags flags) noexcept<br> |
| virtual void | [**Save**](classSR__UTILS__NS_1_1Serializable.md#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer) const<br> |
| virtual void | [**VerifyAfterLoad**](classSR__UTILS__NS_1_1Serializable.md#function-verifyafterload) (SerializableVerifyContext & context) noexcept const<br> |


## Public Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  void | [**CloneTo**](classSR__UTILS__NS_1_1SRClass.md#function-cloneto) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) & clone) const<br> |
| virtual SR\_NODISCARD const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMeta**](classSR__UTILS__NS_1_1SRClass.md#function-getmeta) () noexcept const = 0<br> |
| virtual  | [**~SRClass**](classSR__UTILS__NS_1_1SRClass.md#function-srclass) () = default<br> |




## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |






## Public Static Functions inherited from SR_UTILS_NS::SRClass

See [SR\_UTILS\_NS::SRClass](classSR__UTILS__NS_1_1SRClass.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**AllocateStatic**](classSR__UTILS__NS_1_1SRClass.md#function-allocatestatic) () noexcept<br> |
|  SR\_NODISCARD std::span&lt; const [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* &gt; | [**GetBaseMetas**](classSR__UTILS__NS_1_1SRClass.md#function-getbasemetas) () noexcept<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetClassStaticName**](classSR__UTILS__NS_1_1SRClass.md#function-getclassstaticname) () noexcept<br> |
|  const [**SR\_UTILS\_NS::SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) \* | [**GetMetaStatic**](classSR__UTILS__NS_1_1SRClass.md#function-getmetastatic) () noexcept<br> |
|  bool | [**RegisterPropertiesCodegen**](classSR__UTILS__NS_1_1SRClass.md#function-registerpropertiescodegen) () <br> |






















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**DescriptorManager**](classSR__GRAPH__NS_1_1DescriptorManager.md) & | [**m\_descriptorManager**](#variable-m_descriptormanager)  <br> |
|  [**Memory::UBOManager**](classSR__GRAPH__NS_1_1Memory_1_1UBOManager.md) & | [**m\_uboManager**](#variable-m_ubomanager)  <br> |




## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |
































































































## Public Types Documentation




### typedef CameraPtr 

```C++
using SR_GRAPH_NS::BasePass::CameraPtr =  SR_GTYPES_NS::Camera*;
```




<hr>



### typedef FrameBuffers 

```C++
using SR_GRAPH_NS::BasePass::FrameBuffers =  std::vector<SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Framebuffer> >;
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



### typedef Ptr 

```C++
using SR_GRAPH_NS::BasePass::Ptr =  SR_HTYPES_NS::SharedPtr<BasePass>;
```




<hr>



### typedef RenderContextPtr 

```C++
using SR_GRAPH_NS::BasePass::RenderContextPtr =  RenderContext*;
```




<hr>



### typedef RenderScenePtr 

```C++
using SR_GRAPH_NS::BasePass::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<RenderScene>;
```




<hr>



### typedef ShaderPtr 

```C++
using SR_GRAPH_NS::BasePass::ShaderPtr =  SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Shader>;
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



### function FindPass 

```C++
virtual SR_NODISCARD BasePass * SR_GRAPH_NS::BasePass::FindPass (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function ForEachPass 

```C++
virtual void SR_GRAPH_NS::BasePass::ForEachPass (
    const std::function< void( BasePass &)> & func
) 
```




<hr>



### function GetCamera 

```C++
SR_NODISCARD const CameraPtr & SR_GRAPH_NS::BasePass::GetCamera () const
```




<hr>



### function GetParent 

```C++
inline SR_NODISCARD BasePass * SR_GRAPH_NS::BasePass::GetParent () const
```




<hr>



### function GetPassName 

```C++
SR_NODISCARD SR_UTILS_NS::StringAtom SR_GRAPH_NS::BasePass::GetPassName () const
```




<hr>



### function GetPipeline 

```C++
SR_NODISCARD const PipelinePtr & SR_GRAPH_NS::BasePass::GetPipeline () const
```




<hr>



### function GetRenderContext 

```C++
SR_NODISCARD const RenderContextPtr & SR_GRAPH_NS::BasePass::GetRenderContext () const
```




<hr>



### function GetRenderScene 

```C++
SR_NODISCARD const RenderScenePtr & SR_GRAPH_NS::BasePass::GetRenderScene () const
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



### function IsActive 

```C++
SR_NODISCARD bool SR_GRAPH_NS::BasePass::IsActive () const
```




<hr>



### function IsInit 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::BasePass::IsInit () const
```




<hr>



### function OnMultisampleChanged 

```C++
virtual void SR_GRAPH_NS::BasePass::OnMultisampleChanged () 
```




<hr>



### function OnResize 

```C++
virtual void SR_GRAPH_NS::BasePass::OnResize (
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
virtual void SR_GRAPH_NS::BasePass::Prepare () 
```




<hr>



### function Render 

_Вызывается только во время построения_ 
```C++
inline virtual bool SR_GRAPH_NS::BasePass::Render () 
```




<hr>



### function SetParent 

```C++
inline virtual void SR_GRAPH_NS::BasePass::SetParent (
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



### function UseSamplers 

```C++
virtual void SR_GRAPH_NS::BasePass::UseSamplers (
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>



### function UseUniformsFromAnotherPass 

```C++
inline virtual void SR_GRAPH_NS::BasePass::UseUniformsFromAnotherPass (
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>



### function ~BasePass 

```C++
SR_GRAPH_NS::BasePass::~BasePass () override
```




<hr>
## Protected Attributes Documentation




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
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Pass/BasePass.h`

