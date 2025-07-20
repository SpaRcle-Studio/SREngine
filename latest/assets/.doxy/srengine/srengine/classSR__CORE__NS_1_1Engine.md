

# Class SR\_CORE\_NS::Engine



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**Engine**](classSR__CORE__NS_1_1Engine.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)
















## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddSceneToQueue**](#function-addscenetoqueue) (const ScenePtr & scene) <br> |
|  void | [**AddWindow**](#function-addwindow) (WindowPtr pWindow) <br> |
|  bool | [**Close**](#function-close) () <br> |
|  bool | [**Create**](#function-create) () <br> |
|  void | [**DestroyEditor**](#function-destroyeditor) () <br> |
|   | [**Engine**](#function-engine) ([**Application**](classSR__CORE__NS_1_1Application.md) \* pApplication) <br> |
|  SR\_NODISCARD bool | [**Execute**](#function-execute) () <br> |
|  void | [**FixedUpdate**](#function-fixedupdate) () <br> |
|  bool | [**FlushScene**](#function-flushscene) () <br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::CmdManager**](classSR__UTILS__NS_1_1CmdManager.md) \* | [**GetCmdManager**](#function-getcmdmanager) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Debug**](classSR__UTILS__NS_1_1Debug.md) & | [**GetDebugger**](#function-getdebugger) () const<br>_@method_  |
|  SR\_NODISCARD [**SR\_CORE\_GUI\_NS::EditorGUI**](classSR__CORE__GUI__NS_1_1EditorGUI.md) \* | [**GetEditor**](#function-geteditor) () const<br> |
|  SR\_NODISCARD [**EngineScene**](structSR__CORE__NS_1_1EngineScene.md) \* | [**GetEngineScene**](#function-getenginescene) () const<br> |
|  SR\_NODISCARD WindowPtr | [**GetMainWindow**](#function-getmainwindow) () const<br> |
|  SR\_NODISCARD PhysicsScenePtr | [**GetPhysicsScene**](#function-getphysicsscene) () const<br> |
|  SR\_NODISCARD RenderContextPtr | [**GetRenderContext**](#function-getrendercontext) () const<br> |
|  SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](#function-getscene) () const<br> |
|  SR\_NODISCARD [**SR\_WORLD\_NS::SceneUpdater**](classSR__WORLD__NS_1_1SceneUpdater.md) \* | [**GetSceneBuilder**](#function-getscenebuilder) () const<br> |
|  SR\_NODISCARD bool | [**HasSceneInQueue**](#function-hassceneinqueue) () const<br> |
|  bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsActive**](#function-isactive) () const<br> |
|  SR\_NODISCARD bool | [**IsApplicationFocused**](#function-isapplicationfocused) () const<br> |
|  SR\_NODISCARD bool | [**IsGameMode**](#function-isgamemode) () const<br> |
|  bool | [**IsNeedReloadResources**](#function-isneedreloadresources) () <br> |
|  SR\_NODISCARD bool | [**IsPaused**](#function-ispaused) () const<br> |
|  SR\_NODISCARD bool | [**IsRun**](#function-isrun) () const<br> |
|  void | [**LoadStartupScene**](#function-loadstartupscene) () <br> |
|  void | [**Reload**](#function-reload) () <br> |
|  bool | [**Run**](#function-run) () <br> |
|  void | [**SetActive**](#function-setactive) (bool isActive) <br> |
|  void | [**SetGameMode**](#function-setgamemode) (bool enabled) <br> |
|  void | [**SetOneFramePauseSkip**](#function-setoneframepauseskip) (bool enabled) <br> |
|  void | [**SetPaused**](#function-setpaused) (bool isPaused) <br> |
|  void | [**SetSpeed**](#function-setspeed) (float\_t speed) <br> |
|   | [**~Engine**](#function-engine) () override<br> |


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
























































## Public Functions Documentation




### function AddSceneToQueue 

```C++
void SR_CORE_NS::Engine::AddSceneToQueue (
    const ScenePtr & scene
) 
```




<hr>



### function AddWindow 

```C++
void SR_CORE_NS::Engine::AddWindow (
    WindowPtr pWindow
) 
```




<hr>



### function Close 

```C++
bool SR_CORE_NS::Engine::Close () 
```




<hr>



### function Create 

```C++
bool SR_CORE_NS::Engine::Create () 
```




<hr>



### function DestroyEditor 

```C++
void SR_CORE_NS::Engine::DestroyEditor () 
```




<hr>



### function Engine 

```C++
explicit SR_CORE_NS::Engine::Engine (
    Application * pApplication
) 
```




<hr>



### function Execute 

```C++
SR_NODISCARD bool SR_CORE_NS::Engine::Execute () 
```




<hr>



### function FixedUpdate 

```C++
void SR_CORE_NS::Engine::FixedUpdate () 
```




<hr>



### function FlushScene 

```C++
bool SR_CORE_NS::Engine::FlushScene () 
```




<hr>



### function GetCmdManager 

```C++
inline SR_NODISCARD SR_UTILS_NS::CmdManager * SR_CORE_NS::Engine::GetCmdManager () const
```




<hr>



### function GetDebugger 

_@method_ 
```C++
SR_NODISCARD SR_UTILS_NS::Debug & SR_CORE_NS::Engine::GetDebugger () const
```




<hr>



### function GetEditor 

```C++
inline SR_NODISCARD SR_CORE_GUI_NS::EditorGUI * SR_CORE_NS::Engine::GetEditor () const
```




<hr>



### function GetEngineScene 

```C++
inline SR_NODISCARD EngineScene * SR_CORE_NS::Engine::GetEngineScene () const
```




<hr>



### function GetMainWindow 

```C++
inline SR_NODISCARD WindowPtr SR_CORE_NS::Engine::GetMainWindow () const
```




<hr>



### function GetPhysicsScene 

```C++
SR_NODISCARD PhysicsScenePtr SR_CORE_NS::Engine::GetPhysicsScene () const
```




<hr>



### function GetRenderContext 

```C++
inline SR_NODISCARD RenderContextPtr SR_CORE_NS::Engine::GetRenderContext () const
```




<hr>



### function GetRenderScene 

```C++
SR_NODISCARD RenderScenePtr SR_CORE_NS::Engine::GetRenderScene () const
```




<hr>



### function GetScene 

```C++
SR_NODISCARD ScenePtr SR_CORE_NS::Engine::GetScene () const
```




<hr>



### function GetSceneBuilder 

```C++
SR_NODISCARD SR_WORLD_NS::SceneUpdater * SR_CORE_NS::Engine::GetSceneBuilder () const
```




<hr>



### function HasSceneInQueue 

```C++
inline SR_NODISCARD bool SR_CORE_NS::Engine::HasSceneInQueue () const
```




<hr>



### function Init 

```C++
bool SR_CORE_NS::Engine::Init () 
```




<hr>



### function IsActive 

```C++
inline SR_NODISCARD bool SR_CORE_NS::Engine::IsActive () const
```




<hr>



### function IsApplicationFocused 

```C++
SR_NODISCARD bool SR_CORE_NS::Engine::IsApplicationFocused () const
```




<hr>



### function IsGameMode 

```C++
inline SR_NODISCARD bool SR_CORE_NS::Engine::IsGameMode () const
```




<hr>



### function IsNeedReloadResources 

```C++
bool SR_CORE_NS::Engine::IsNeedReloadResources () 
```




<hr>



### function IsPaused 

```C++
inline SR_NODISCARD bool SR_CORE_NS::Engine::IsPaused () const
```




<hr>



### function IsRun 

```C++
inline SR_NODISCARD bool SR_CORE_NS::Engine::IsRun () const
```




<hr>



### function LoadStartupScene 

```C++
void SR_CORE_NS::Engine::LoadStartupScene () 
```




<hr>



### function Reload 

```C++
void SR_CORE_NS::Engine::Reload () 
```




<hr>



### function Run 

```C++
bool SR_CORE_NS::Engine::Run () 
```




<hr>



### function SetActive 

```C++
void SR_CORE_NS::Engine::SetActive (
    bool isActive
) 
```




<hr>



### function SetGameMode 

```C++
void SR_CORE_NS::Engine::SetGameMode (
    bool enabled
) 
```




<hr>



### function SetOneFramePauseSkip 

```C++
inline void SR_CORE_NS::Engine::SetOneFramePauseSkip (
    bool enabled
) 
```




<hr>



### function SetPaused 

```C++
void SR_CORE_NS::Engine::SetPaused (
    bool isPaused
) 
```




<hr>



### function SetSpeed 

```C++
void SR_CORE_NS::Engine::SetSpeed (
    float_t speed
) 
```




<hr>



### function ~Engine 

```C++
SR_CORE_NS::Engine::~Engine () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/Engine.h`

