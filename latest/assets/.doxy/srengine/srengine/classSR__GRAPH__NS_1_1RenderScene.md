

# Class SR\_GRAPH\_NS::RenderScene



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**CameraInfo**](structSR__GRAPH__NS_1_1RenderScene_1_1CameraInfo.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) &gt; | [**CameraPtr**](#typedef-cameraptr)  <br> |
| typedef [**SR\_GTYPES\_NS::Mesh**](classSR__GTYPES__NS_1_1Mesh.md) \* | [**MeshPtr**](#typedef-meshptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](#typedef-pipelineptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**ScenePtr**](#typedef-sceneptr)  <br> |
| typedef [**GUI::WidgetManager**](classSR__GRAPH__NS_1_1GUI_1_1WidgetManager.md) \* | [**WidgetManagerPtr**](#typedef-widgetmanagerptr)  <br> |
| typedef std::vector&lt; [**WidgetManagerPtr**](classSR__GRAPH__NS_1_1GUI_1_1WidgetManager.md) &gt; | [**WidgetManagers**](#typedef-widgetmanagers)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Window**](classSR__GRAPH__NS_1_1Window.md) &gt; | [**WindowPtr**](#typedef-windowptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**AddRenderer**](#function-addrenderer-12) () <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IRenderer**](classSR__GRAPH__NS_1_1IRenderer.md) &gt; | [**AddRenderer**](#function-addrenderer-22) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  void | [**DeInit**](#function-deinit) () <br> |
|  void | [**ForEachTechnique**](#function-foreachtechnique) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \*)&gt; & callback) <br> |
|  SR\_NODISCARD const std::vector&lt; [**CameraInfo**](structSR__GRAPH__NS_1_1RenderScene_1_1CameraInfo.md) &gt; & | [**GetCameras**](#function-getcameras) () <br> |
|  SR\_NODISCARD [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* | [**GetContext**](#function-getcontext) () const<br> |
|  SR\_NODISCARD [**SR\_ANIMATIONS\_NS::Skeleton**](classSR__ANIMATIONS__NS_1_1Skeleton.md) \* | [**GetCurrentSkeleton**](#function-getcurrentskeleton) () const<br> |
|  SR\_NODISCARD CameraPtr | [**GetFirstOffScreenCamera**](#function-getfirstoffscreencamera) () const<br> |
|  SR\_NODISCARD [**LightSystem**](classSR__GRAPH__NS_1_1LightSystem.md) \* | [**GetLightSystem**](#function-getlightsystem) () const<br> |
|  SR\_NODISCARD CameraPtr | [**GetMainCamera**](#function-getmaincamera) () const<br> |
|  SR\_NODISCARD const RenderScene::PipelinePtr & | [**GetPipeline**](#function-getpipeline-12) () const<br> |
|  SR\_NODISCARD RenderScene::PipelinePtr | [**GetPipeline**](#function-getpipeline-22) () <br> |
|  SR\_NODISCARD [**RenderStrategy**](classSR__GRAPH__NS_1_1RenderStrategy.md) \* | [**GetRenderStrategy**](#function-getrenderstrategy) () <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetRenderer**](#function-getrenderer-12) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IRenderer**](classSR__GRAPH__NS_1_1IRenderer.md) &gt; | [**GetRenderer**](#function-getrenderer-22) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::UVector2 | [**GetSurfaceSize**](#function-getsurfacesize) () const<br> |
|  SR\_NODISCARD const WidgetManagers & | [**GetWidgetManagers**](#function-getwidgetmanagers) () const<br> |
|  SR\_NODISCARD WindowPtr | [**GetWindow**](#function-getwindow) () const<br> |
|  void | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () const<br> |
|  SR\_NODISCARD bool | [**IsOverlayEnabled**](#function-isoverlayenabled) () const<br> |
|  void | [**OnResize**](#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
|  void | [**OnResourceReloaded**](#function-onresourcereloaded) ([**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  void | [**ReRegister**](#function-reregister) (const [**MeshRegistrationInfo**](structSR__GRAPH__NS_1_1MeshRegistrationInfo.md) & info) <br> |
|  void | [**Register**](#function-register-13) (const CameraPtr & pCamera) <br> |
|  void | [**Register**](#function-register-23) ([**WidgetManagerPtr**](classSR__GRAPH__NS_1_1GUI_1_1WidgetManager.md) pWidgetManager) <br> |
|  void | [**Register**](#function-register-33) (MeshPtr pMesh) <br> |
|  void | [**Remove**](#function-remove-13) (const CameraPtr & pCamera) <br> |
|  void | [**Remove**](#function-remove-23) ([**WidgetManagerPtr**](classSR__GRAPH__NS_1_1GUI_1_1WidgetManager.md) pWidgetManager) <br> |
|  void | [**Remove**](#function-remove-33) (MeshPtr pMesh) <br> |
|  void | [**Render**](#function-render) () <br> |
|   | [**RenderScene**](#function-renderscene) (const ScenePtr & scene, [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) \* pContext) <br> |
|  void | [**SetCurrentSkeleton**](#function-setcurrentskeleton) ([**SR\_ANIMATIONS\_NS::Skeleton**](classSR__ANIMATIONS__NS_1_1Skeleton.md) \* pSkeleton) <br> |
|  void | [**SetDirty**](#function-setdirty) () <br>_Можно вызывать не синхронно_  |
|  void | [**SetDirtyCameras**](#function-setdirtycameras) () <br> |
|  void | [**SetOverlayEnabled**](#function-setoverlayenabled) (bool enabled) <br> |
|  void | [**SetTechnique**](#function-settechnique-12) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pTechnique) <br> |
|  void | [**SetTechnique**](#function-settechnique-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**Submit**](#function-submit) () <br> |
|  void | [**Synchronize**](#function-synchronize) () <br> |
|   | [**~RenderScene**](#function-renderscene) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
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




## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |




















## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |
























































## Public Types Documentation




### typedef CameraPtr 

```C++
using SR_GRAPH_NS::RenderScene::CameraPtr =  SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Camera>;
```




<hr>



### typedef MeshPtr 

```C++
using SR_GRAPH_NS::RenderScene::MeshPtr =  SR_GTYPES_NS::Mesh*;
```




<hr>



### typedef PipelinePtr 

```C++
using SR_GRAPH_NS::RenderScene::PipelinePtr =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef Ptr 

```C++
using SR_GRAPH_NS::RenderScene::Ptr =  SR_HTYPES_NS::SharedPtr<RenderScene>;
```




<hr>



### typedef ScenePtr 

```C++
using SR_GRAPH_NS::RenderScene::ScenePtr =  SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
```




<hr>



### typedef WidgetManagerPtr 

```C++
using SR_GRAPH_NS::RenderScene::WidgetManagerPtr =  GUI::WidgetManager*;
```




<hr>



### typedef WidgetManagers 

```C++
using SR_GRAPH_NS::RenderScene::WidgetManagers =  std::vector<WidgetManagerPtr>;
```




<hr>



### typedef WindowPtr 

```C++
using SR_GRAPH_NS::RenderScene::WindowPtr =  SR_HTYPES_NS::SharedPtr<Window>;
```




<hr>
## Public Functions Documentation




### function AddRenderer [1/2]

```C++
template<typename T>
inline SR_HTYPES_NS::SharedPtr < T > SR_GRAPH_NS::RenderScene::AddRenderer () 
```




<hr>



### function AddRenderer [2/2]

```C++
SR_HTYPES_NS::SharedPtr < IRenderer > SR_GRAPH_NS::RenderScene::AddRenderer (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function DeInit 

```C++
void SR_GRAPH_NS::RenderScene::DeInit () 
```




<hr>



### function ForEachTechnique 

```C++
void SR_GRAPH_NS::RenderScene::ForEachTechnique (
    const SR_HTYPES_NS::Function < void( IRenderTechnique *)> & callback
) 
```




<hr>



### function GetCameras 

```C++
inline SR_NODISCARD const std::vector< CameraInfo > & SR_GRAPH_NS::RenderScene::GetCameras () 
```




<hr>



### function GetContext 

```C++
SR_NODISCARD RenderContext * SR_GRAPH_NS::RenderScene::GetContext () const
```




<hr>



### function GetCurrentSkeleton 

```C++
inline SR_NODISCARD SR_ANIMATIONS_NS::Skeleton * SR_GRAPH_NS::RenderScene::GetCurrentSkeleton () const
```




<hr>



### function GetFirstOffScreenCamera 

```C++
SR_NODISCARD CameraPtr SR_GRAPH_NS::RenderScene::GetFirstOffScreenCamera () const
```




<hr>



### function GetLightSystem 

```C++
inline SR_NODISCARD LightSystem * SR_GRAPH_NS::RenderScene::GetLightSystem () const
```




<hr>



### function GetMainCamera 

```C++
SR_NODISCARD CameraPtr SR_GRAPH_NS::RenderScene::GetMainCamera () const
```




<hr>



### function GetPipeline [1/2]

```C++
SR_NODISCARD const RenderScene::PipelinePtr & SR_GRAPH_NS::RenderScene::GetPipeline () const
```




<hr>



### function GetPipeline [2/2]

```C++
SR_NODISCARD RenderScene::PipelinePtr SR_GRAPH_NS::RenderScene::GetPipeline () 
```




<hr>



### function GetRenderStrategy 

```C++
inline SR_NODISCARD RenderStrategy * SR_GRAPH_NS::RenderScene::GetRenderStrategy () 
```




<hr>



### function GetRenderer [1/2]

```C++
template<typename T>
inline SR_HTYPES_NS::SharedPtr < T > SR_GRAPH_NS::RenderScene::GetRenderer () const
```




<hr>



### function GetRenderer [2/2]

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < IRenderer > SR_GRAPH_NS::RenderScene::GetRenderer (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function GetSurfaceSize 

```C++
SR_NODISCARD SR_MATH_NS::UVector2 SR_GRAPH_NS::RenderScene::GetSurfaceSize () const
```




<hr>



### function GetWidgetManagers 

```C++
SR_NODISCARD const WidgetManagers & SR_GRAPH_NS::RenderScene::GetWidgetManagers () const
```




<hr>



### function GetWindow 

```C++
SR_NODISCARD WindowPtr SR_GRAPH_NS::RenderScene::GetWindow () const
```




<hr>



### function Init 

```C++
void SR_GRAPH_NS::RenderScene::Init () 
```




<hr>



### function IsDirty 

```C++
SR_NODISCARD bool SR_GRAPH_NS::RenderScene::IsDirty () noexcept const
```




<hr>



### function IsEmpty 

```C++
SR_NODISCARD bool SR_GRAPH_NS::RenderScene::IsEmpty () const
```




<hr>



### function IsOverlayEnabled 

```C++
SR_NODISCARD bool SR_GRAPH_NS::RenderScene::IsOverlayEnabled () const
```




<hr>



### function OnResize 

```C++
void SR_GRAPH_NS::RenderScene::OnResize (
    const SR_MATH_NS::UVector2 & size
) 
```




<hr>



### function OnResourceReloaded 

```C++
void SR_GRAPH_NS::RenderScene::OnResourceReloaded (
    SR_UTILS_NS::IResource * pResource
) 
```




<hr>



### function ReRegister 

```C++
void SR_GRAPH_NS::RenderScene::ReRegister (
    const MeshRegistrationInfo & info
) 
```




<hr>



### function Register [1/3]

```C++
void SR_GRAPH_NS::RenderScene::Register (
    const CameraPtr & pCamera
) 
```




<hr>



### function Register [2/3]

```C++
void SR_GRAPH_NS::RenderScene::Register (
    WidgetManagerPtr pWidgetManager
) 
```




<hr>



### function Register [3/3]

```C++
void SR_GRAPH_NS::RenderScene::Register (
    MeshPtr pMesh
) 
```




<hr>



### function Remove [1/3]

```C++
void SR_GRAPH_NS::RenderScene::Remove (
    const CameraPtr & pCamera
) 
```




<hr>



### function Remove [2/3]

```C++
void SR_GRAPH_NS::RenderScene::Remove (
    WidgetManagerPtr pWidgetManager
) 
```




<hr>



### function Remove [3/3]

```C++
void SR_GRAPH_NS::RenderScene::Remove (
    MeshPtr pMesh
) 
```




<hr>



### function Render 

```C++
void SR_GRAPH_NS::RenderScene::Render () 
```




<hr>



### function RenderScene 

```C++
explicit SR_GRAPH_NS::RenderScene::RenderScene (
    const ScenePtr & scene,
    RenderContext * pContext
) 
```




<hr>



### function SetCurrentSkeleton 

```C++
inline void SR_GRAPH_NS::RenderScene::SetCurrentSkeleton (
    SR_ANIMATIONS_NS::Skeleton * pSkeleton
) 
```




<hr>



### function SetDirty 

_Можно вызывать не синхронно_ 
```C++
void SR_GRAPH_NS::RenderScene::SetDirty () 
```




<hr>



### function SetDirtyCameras 

```C++
void SR_GRAPH_NS::RenderScene::SetDirtyCameras () 
```




<hr>



### function SetOverlayEnabled 

```C++
void SR_GRAPH_NS::RenderScene::SetOverlayEnabled (
    bool enabled
) 
```




<hr>



### function SetTechnique [1/2]

```C++
void SR_GRAPH_NS::RenderScene::SetTechnique (
    IRenderTechnique * pTechnique
) 
```




<hr>



### function SetTechnique [2/2]

```C++
void SR_GRAPH_NS::RenderScene::SetTechnique (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function Submit 

```C++
void SR_GRAPH_NS::RenderScene::Submit () 
```




<hr>



### function Synchronize 

```C++
void SR_GRAPH_NS::RenderScene::Synchronize () 
```




<hr>



### function ~RenderScene 

```C++
SR_GRAPH_NS::RenderScene::~RenderScene () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderScene.h`

