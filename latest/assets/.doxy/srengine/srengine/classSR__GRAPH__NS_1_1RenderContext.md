

# Class SR\_GRAPH\_NS::RenderContext



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md)



[More...](#detailed-description)

* `#include <RenderContext.h>`



Inherits the following classes: [SR\_HTYPES\_NS::SafePtr](classSR__HTYPES__NS_1_1SafePtr.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Close**](#function-close) () <br> |
|  RenderScenePtr | [**CreateScene**](#function-createscene) (const SR\_WORLD\_NS::Scene::Ptr & scene) <br> |
|  SR\_NODISCARD FramebufferPtr | [**FindFramebuffer**](#function-findframebuffer-12) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD FramebufferPtr | [**FindFramebuffer**](#function-findframebuffer-22) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, CameraPtr pCamera) const<br> |
|  void | [**GarbageCollect**](#function-garbagecollect) () <br> |
|  SR\_NODISCARD ShaderPtr | [**GetCurrentShader**](#function-getcurrentshader) () noexcept const<br> |
|  SR\_NODISCARD MaterialPtr | [**GetDefaultMaterial**](#function-getdefaultmaterial) () const<br> |
|  SR\_NODISCARD TexturePtr | [**GetDefaultTexture**](#function-getdefaulttexture) () const<br> |
|  SR\_NODISCARD MaterialPtr | [**GetDefaultUIMaterial**](#function-getdefaultuimaterial) () const<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Framebuffer**](classSR__GTYPES__NS_1_1Framebuffer.md) &gt; &gt; & | [**GetFramebuffers**](#function-getframebuffers) () noexcept const<br> |
|  SR\_NODISCARD TexturePtr | [**GetNoneTexture**](#function-getnonetexture) () const<br> |
|  SR\_NODISCARD const RenderContext::PipelinePtr & | [**GetPipeline**](#function-getpipeline-12) () const<br> |
|  SR\_NODISCARD RenderContext::PipelinePtr & | [**GetPipeline**](#function-getpipeline-22) () <br> |
|  SR\_NODISCARD PipelineType | [**GetPipelineType**](#function-getpipelinetype) () const<br> |
|  SR\_NODISCARD const std::vector&lt; IRenderTechnique::Ptr &gt; & | [**GetRenderTechniques**](#function-getrendertechniques) () noexcept const<br> |
|  SR\_NODISCARD const RenderScenes & | [**GetScenes**](#function-getscenes) () noexcept const<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* &gt; & | [**GetShaders**](#function-getshaders) () noexcept const<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_GTYPES\_NS::Skybox**](classSR__GTYPES__NS_1_1Skybox.md) \* &gt; & | [**GetSkyboxes**](#function-getskyboxes) () noexcept const<br> |
|  SR\_NODISCARD const std::vector&lt; TexturePtr &gt; & | [**GetTextures**](#function-gettextures) () noexcept const<br> |
|  SR\_NODISCARD WindowPtr | [**GetWindow**](#function-getwindow) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::UVector2 | [**GetWindowSize**](#function-getwindowsize) () const<br> |
|  bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () const<br> |
|  SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () const<br> |
|  SR\_NODISCARD bool | [**IsOptimizedRenderUpdateEnabled**](#function-isoptimizedrenderupdateenabled) () noexcept const<br> |
|  void | [**OnMultiSampleChanged**](#function-onmultisamplechanged) () <br> |
|  void | [**OnResize**](#function-onresize) (const SR\_MATH\_NS::UVector2 & size) <br> |
|  void | [**PrepareFrame**](#function-prepareframe) () <br> |
|  void | [**Register**](#function-register-16) (FramebufferPtr pFrameBuffer) <br> |
|  void | [**Register**](#function-register-26) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) <br> |
|  void | [**Register**](#function-register-36) ([**SR\_GTYPES\_NS::Texture**](classSR__GTYPES__NS_1_1Texture.md) \* pTexture) <br> |
|  void | [**Register**](#function-register-46) ([**IRenderTechnique**](classSR__GRAPH__NS_1_1IRenderTechnique.md) \* pTechnique) <br> |
|  void | [**Register**](#function-register-56) (MaterialPtr pMaterial) <br> |
|  void | [**Register**](#function-register-66) (SkyboxPtr pSkybox) <br> |
|   | [**RenderContext**](#function-rendercontext) () <br> |
|  bool | [**SetCurrentShader**](#function-setcurrentshader) (ShaderPtr pShader) <br> |
|  void | [**SetDirty**](#function-setdirty) () <br> |
|  void | [**SetOptimizedRenderUpdateEnabled**](#function-setoptimizedrenderupdateenabled) (bool enabled) noexcept<br> |
|  void | [**SwitchWindow**](#function-switchwindow) (WindowPtr pWindow) <br> |
|  bool | [**Update**](#function-update-12) () noexcept<br> |
| virtual  | [**~RenderContext**](#function-rendercontext) () <br> |


## Public Functions inherited from SR_HTYPES_NS::SafePtr

See [SR\_HTYPES\_NS::SafePtr](classSR__HTYPES__NS_1_1SafePtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SafePtr.md#function-autofree-12) (const std::function&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SafePtr.md#function-autofree-22) () <br> |
|  bool | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-14) (const std::function&lt; void(T \*ptr)&gt; & func) <br> |
|  U | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-24) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  bool | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-34) (const std::function&lt; void(T \*)&gt; & func) <br> |
|  U | [**Do**](classSR__HTYPES__NS_1_1SafePtr.md#function-do-44) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SafePtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SafePtr.md#function-get) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE [**SafePtrDynamicData**](structSR__HTYPES__NS_1_1SafePtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SafePtr.md#function-getptrdata) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-getrawptr) () const<br> |
|  SR\_NODISCARD [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SafePtr.md#function-getthis) () <br> |
|  SR\_NODISCARD uint32\_t | [**GetUseCount**](classSR__HTYPES__NS_1_1SafePtr.md#function-getusecount) () const<br> |
|  SR\_NODISCARD bool | [**IsLocked**](classSR__HTYPES__NS_1_1SafePtr.md#function-islocked) () const<br> |
|  void | [**Lock**](classSR__HTYPES__NS_1_1SafePtr.md#function-lock) () const<br> |
|  SR\_NODISCARD bool | [**LockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-lockifvalid) () const<br> |
|  void | [**RecursiveLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-recursivelock) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-recursivelockifvalid) () const<br> |
|  void | [**RemoveAllLocks**](classSR__HTYPES__NS_1_1SafePtr.md#function-removealllocks) () <br> |
|  void | [**Replace**](classSR__HTYPES__NS_1_1SafePtr.md#function-replace) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndCopyLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-replaceandcopylock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|  void | [**ReplaceAndLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-replaceandlock) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) & ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-13) (const T \* ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-23) ([**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md) const & ptr) <br> |
|   | [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr-33) () <br> |
|  U | [**TryDo**](classSR__HTYPES__NS_1_1SafePtr.md#function-trydo-12) (const std::function&lt; U(T \*ptr)&gt; & func, U \_default) <br> |
|  U | [**TryDo**](classSR__HTYPES__NS_1_1SafePtr.md#function-trydo-22) (const std::function&lt; U(T \*)&gt; & func, U \_default) <br> |
|  bool | [**TryLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-trylock) () const<br> |
|  SR\_NODISCARD bool | [**TryLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-trylockifvalid) () const<br> |
|  bool | [**TryRecursiveLock**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryrecursivelock) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryrecursivelockifvalid) () const<br> |
|  bool | [**TryUnlock**](classSR__HTYPES__NS_1_1SafePtr.md#function-tryunlock) () const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SafePtr.md#function-unlock) () const<br> |
|  SR\_NODISCARD bool | [**Valid**](classSR__HTYPES__NS_1_1SafePtr.md#function-valid) () const<br> |
|   | [**operator bool**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator-bool) () noexcept const<br>_не должен быть виртуальным_  |
|  SR\_NODISCARD SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|  T & | [**operator\***](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_1) () const<br> |
|  T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_2) () const<br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_3) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & ptr) <br> |
|  [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_4) (T \* ptr) <br> |
|  SR\_NODISCARD SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SafePtr.md#function-operator_5) (const [**SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; T &gt; & right) noexcept const<br> |
|   | [**~SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md#function-safeptr) () <br> |






















































## Detailed Description


Здесь хранятся все контекстные ресурсы. Исключение - меши, потому что они могут быть в нескольких экземплярах. Управлением памяти мешей занимается [**MeshCluster**](classSR__GRAPH__NS_1_1MeshCluster.md), который у каждой [**RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) свой. 


    
## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_NS::RenderContext::Ptr =  SR_HTYPES_NS::SafePtr<RenderContext>;
```




<hr>
## Public Functions Documentation




### function Close 

```C++
void SR_GRAPH_NS::RenderContext::Close () 
```




<hr>



### function CreateScene 

```C++
RenderScenePtr SR_GRAPH_NS::RenderContext::CreateScene (
    const SR_WORLD_NS::Scene::Ptr & scene
) 
```




<hr>



### function FindFramebuffer [1/2]

```C++
SR_NODISCARD FramebufferPtr SR_GRAPH_NS::RenderContext::FindFramebuffer (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function FindFramebuffer [2/2]

```C++
SR_NODISCARD FramebufferPtr SR_GRAPH_NS::RenderContext::FindFramebuffer (
    SR_UTILS_NS::StringAtom name,
    CameraPtr pCamera
) const
```




<hr>



### function GarbageCollect 

```C++
inline void SR_GRAPH_NS::RenderContext::GarbageCollect () 
```




<hr>



### function GetCurrentShader 

```C++
SR_NODISCARD ShaderPtr SR_GRAPH_NS::RenderContext::GetCurrentShader () noexcept const
```




<hr>



### function GetDefaultMaterial 

```C++
SR_NODISCARD MaterialPtr SR_GRAPH_NS::RenderContext::GetDefaultMaterial () const
```




<hr>



### function GetDefaultTexture 

```C++
SR_NODISCARD TexturePtr SR_GRAPH_NS::RenderContext::GetDefaultTexture () const
```




<hr>



### function GetDefaultUIMaterial 

```C++
inline SR_NODISCARD MaterialPtr SR_GRAPH_NS::RenderContext::GetDefaultUIMaterial () const
```




<hr>



### function GetFramebuffers 

```C++
SR_NODISCARD const std::vector< SR_HTYPES_NS::SharedPtr < SR_GTYPES_NS::Framebuffer > > & SR_GRAPH_NS::RenderContext::GetFramebuffers () noexcept const
```




<hr>



### function GetNoneTexture 

```C++
SR_NODISCARD TexturePtr SR_GRAPH_NS::RenderContext::GetNoneTexture () const
```




<hr>



### function GetPipeline [1/2]

```C++
SR_NODISCARD const RenderContext::PipelinePtr & SR_GRAPH_NS::RenderContext::GetPipeline () const
```




<hr>



### function GetPipeline [2/2]

```C++
SR_NODISCARD RenderContext::PipelinePtr & SR_GRAPH_NS::RenderContext::GetPipeline () 
```




<hr>



### function GetPipelineType 

```C++
SR_NODISCARD PipelineType SR_GRAPH_NS::RenderContext::GetPipelineType () const
```




<hr>



### function GetRenderTechniques 

```C++
SR_NODISCARD const std::vector< IRenderTechnique::Ptr > & SR_GRAPH_NS::RenderContext::GetRenderTechniques () noexcept const
```




<hr>



### function GetScenes 

```C++
inline SR_NODISCARD const RenderScenes & SR_GRAPH_NS::RenderContext::GetScenes () noexcept const
```




<hr>



### function GetShaders 

```C++
SR_NODISCARD const std::vector< SR_GTYPES_NS::Shader * > & SR_GRAPH_NS::RenderContext::GetShaders () noexcept const
```




<hr>



### function GetSkyboxes 

```C++
SR_NODISCARD const std::vector< SR_GTYPES_NS::Skybox * > & SR_GRAPH_NS::RenderContext::GetSkyboxes () noexcept const
```




<hr>



### function GetTextures 

```C++
SR_NODISCARD const std::vector< TexturePtr > & SR_GRAPH_NS::RenderContext::GetTextures () noexcept const
```




<hr>



### function GetWindow 

```C++
SR_NODISCARD WindowPtr SR_GRAPH_NS::RenderContext::GetWindow () const
```




<hr>



### function GetWindowSize 

```C++
SR_NODISCARD SR_MATH_NS::UVector2 SR_GRAPH_NS::RenderContext::GetWindowSize () const
```




<hr>



### function Init 

```C++
bool SR_GRAPH_NS::RenderContext::Init () 
```




<hr>



### function IsDirty 

```C++
SR_NODISCARD bool SR_GRAPH_NS::RenderContext::IsDirty () const
```




<hr>



### function IsEmpty 

```C++
SR_NODISCARD bool SR_GRAPH_NS::RenderContext::IsEmpty () const
```




<hr>



### function IsOptimizedRenderUpdateEnabled 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::RenderContext::IsOptimizedRenderUpdateEnabled () noexcept const
```




<hr>



### function OnMultiSampleChanged 

```C++
void SR_GRAPH_NS::RenderContext::OnMultiSampleChanged () 
```




<hr>



### function OnResize 

```C++
void SR_GRAPH_NS::RenderContext::OnResize (
    const SR_MATH_NS::UVector2 & size
) 
```




<hr>



### function PrepareFrame 

```C++
void SR_GRAPH_NS::RenderContext::PrepareFrame () 
```




<hr>



### function Register [1/6]

```C++
void SR_GRAPH_NS::RenderContext::Register (
    FramebufferPtr pFrameBuffer
) 
```




<hr>



### function Register [2/6]

```C++
void SR_GRAPH_NS::RenderContext::Register (
    SR_GTYPES_NS::Shader * pShader
) 
```




<hr>



### function Register [3/6]

```C++
void SR_GRAPH_NS::RenderContext::Register (
    SR_GTYPES_NS::Texture * pTexture
) 
```




<hr>



### function Register [4/6]

```C++
void SR_GRAPH_NS::RenderContext::Register (
    IRenderTechnique * pTechnique
) 
```




<hr>



### function Register [5/6]

```C++
void SR_GRAPH_NS::RenderContext::Register (
    MaterialPtr pMaterial
) 
```




<hr>



### function Register [6/6]

```C++
void SR_GRAPH_NS::RenderContext::Register (
    SkyboxPtr pSkybox
) 
```




<hr>



### function RenderContext 

```C++
SR_GRAPH_NS::RenderContext::RenderContext () 
```




<hr>



### function SetCurrentShader 

```C++
bool SR_GRAPH_NS::RenderContext::SetCurrentShader (
    ShaderPtr pShader
) 
```




<hr>



### function SetDirty 

```C++
void SR_GRAPH_NS::RenderContext::SetDirty () 
```




<hr>



### function SetOptimizedRenderUpdateEnabled 

```C++
inline void SR_GRAPH_NS::RenderContext::SetOptimizedRenderUpdateEnabled (
    bool enabled
) noexcept
```




<hr>



### function SwitchWindow 

```C++
void SR_GRAPH_NS::RenderContext::SwitchWindow (
    WindowPtr pWindow
) 
```




<hr>



### function Update [1/2]

```C++
bool SR_GRAPH_NS::RenderContext::Update () noexcept
```




<hr>



### function ~RenderContext 

```C++
virtual SR_GRAPH_NS::RenderContext::~RenderContext () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Render/RenderContext.h`

