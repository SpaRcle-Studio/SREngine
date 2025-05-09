

# Struct SR\_CORE\_NS::EngineScene



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**EngineScene**](structSR__CORE__NS_1_1EngineScene.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) &gt; | [**CameraPtr**](#typedef-cameraptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**SR\_PHYSICS\_NS::PhysicsScene**](classSR__PHYSICS__NS_1_1PhysicsScene.md) &gt; | [**PhysicsScenePtr**](#typedef-physicssceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_GRAPH\_NS::RenderScene**](classSR__GRAPH__NS_1_1RenderScene.md) &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**ScenePtr**](#typedef-sceneptr)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**m\_accumulateDt**](#variable-m_accumulatedt)   = `false`<br> |
|  float\_t | [**m\_accumulator**](#variable-m_accumulator)   = `1.f`<br> |
|  float\_t | [**m\_speed**](#variable-m_speed)   = `1.f`<br> |
|  float\_t | [**m\_updateFrequency**](#variable-m_updatefrequency)   = `1.f`<br> |
|  [**Engine**](classSR__CORE__NS_1_1Engine.md) \* | [**pEngine**](#variable-pengine)   = `nullptr`<br> |
|  CameraPtr | [**pMainCamera**](#variable-pmaincamera)  <br> |
|  PhysicsScenePtr | [**pPhysicsScene**](#variable-pphysicsscene)  <br> |
|  RenderScenePtr | [**pRenderScene**](#variable-prenderscene)  <br> |
|  ScenePtr | [**pScene**](#variable-pscene)  <br> |
|  [**SR\_WORLD\_NS::SceneUpdater**](classSR__WORLD__NS_1_1SceneUpdater.md) \* | [**pSceneUpdater**](#variable-psceneupdater)   = `nullptr`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EngineScene**](#function-enginescene) (const ScenePtr & scene, [**Engine**](classSR__CORE__NS_1_1Engine.md) \* pEngine) <br> |
|  SR\_NODISCARD CameraPtr | [**GetMainCamera**](#function-getmaincamera) () const<br> |
|  SR\_NODISCARD bool | [**Init**](#function-init) () <br> |
|  void | [**SetActive**](#function-setactive) (bool active) <br> |
|  void | [**SetGameMode**](#function-setgamemode) (bool gameMode) <br> |
|  void | [**SetPaused**](#function-setpaused) (bool pause) <br> |
|  void | [**SetSpeed**](#function-setspeed) (float\_t speed) <br> |
|  void | [**SkipDraw**](#function-skipdraw) () <br> |
|  void | [**Update**](#function-update) (float\_t dt) <br> |
|  void | [**UpdateChunkDebug**](#function-updatechunkdebug) () <br> |
|  void | [**UpdateMainCamera**](#function-updatemaincamera) () <br> |
|   | [**~EngineScene**](#function-enginescene) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef CameraPtr 

```C++
using SR_CORE_NS::EngineScene::CameraPtr =  SR_HTYPES_NS::SharedPtr<SR_GTYPES_NS::Camera>;
```




<hr>



### typedef PhysicsScenePtr 

```C++
using SR_CORE_NS::EngineScene::PhysicsScenePtr =  SR_HTYPES_NS::SafePtr<SR_PHYSICS_NS::PhysicsScene>;
```




<hr>



### typedef RenderScenePtr 

```C++
using SR_CORE_NS::EngineScene::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<SR_GRAPH_NS::RenderScene>;
```




<hr>



### typedef ScenePtr 

```C++
using SR_CORE_NS::EngineScene::ScenePtr =  SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
```




<hr>



### typedef Super 

```C++
using SR_CORE_NS::EngineScene::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Public Attributes Documentation




### variable m\_accumulateDt 

```C++
bool SR_CORE_NS::EngineScene::m_accumulateDt;
```




<hr>



### variable m\_accumulator 

```C++
float_t SR_CORE_NS::EngineScene::m_accumulator;
```




<hr>



### variable m\_speed 

```C++
float_t SR_CORE_NS::EngineScene::m_speed;
```




<hr>



### variable m\_updateFrequency 

```C++
float_t SR_CORE_NS::EngineScene::m_updateFrequency;
```




<hr>



### variable pEngine 

```C++
Engine* SR_CORE_NS::EngineScene::pEngine;
```




<hr>



### variable pMainCamera 

```C++
CameraPtr SR_CORE_NS::EngineScene::pMainCamera;
```




<hr>



### variable pPhysicsScene 

```C++
PhysicsScenePtr SR_CORE_NS::EngineScene::pPhysicsScene;
```




<hr>



### variable pRenderScene 

```C++
RenderScenePtr SR_CORE_NS::EngineScene::pRenderScene;
```




<hr>



### variable pScene 

```C++
ScenePtr SR_CORE_NS::EngineScene::pScene;
```




<hr>



### variable pSceneUpdater 

```C++
SR_WORLD_NS::SceneUpdater* SR_CORE_NS::EngineScene::pSceneUpdater;
```




<hr>
## Public Functions Documentation




### function EngineScene 

```C++
SR_CORE_NS::EngineScene::EngineScene (
    const ScenePtr & scene,
    Engine * pEngine
) 
```




<hr>



### function GetMainCamera 

```C++
inline SR_NODISCARD CameraPtr SR_CORE_NS::EngineScene::GetMainCamera () const
```




<hr>



### function Init 

```C++
SR_NODISCARD bool SR_CORE_NS::EngineScene::Init () 
```




<hr>



### function SetActive 

```C++
void SR_CORE_NS::EngineScene::SetActive (
    bool active
) 
```




<hr>



### function SetGameMode 

```C++
void SR_CORE_NS::EngineScene::SetGameMode (
    bool gameMode
) 
```




<hr>



### function SetPaused 

```C++
void SR_CORE_NS::EngineScene::SetPaused (
    bool pause
) 
```




<hr>



### function SetSpeed 

```C++
void SR_CORE_NS::EngineScene::SetSpeed (
    float_t speed
) 
```




<hr>



### function SkipDraw 

```C++
void SR_CORE_NS::EngineScene::SkipDraw () 
```




<hr>



### function Update 

```C++
void SR_CORE_NS::EngineScene::Update (
    float_t dt
) 
```




<hr>



### function UpdateChunkDebug 

```C++
void SR_CORE_NS::EngineScene::UpdateChunkDebug () 
```




<hr>



### function UpdateMainCamera 

```C++
void SR_CORE_NS::EngineScene::UpdateMainCamera () 
```




<hr>



### function ~EngineScene 

```C++
SR_CORE_NS::EngineScene::~EngineScene () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/World/EngineScene.h`

