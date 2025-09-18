

# Class SR\_UTILS\_NS::Component



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Component**](classSR__UTILS__NS_1_1Component.md)








Inherits the following classes: Entity


Inherited by the following classes: [SR\_ANIMATIONS\_NS::Animator](classSR__ANIMATIONS__NS_1_1Animator.md),  [SR\_ANIMATIONS\_NS::BoneComponent](classSR__ANIMATIONS__NS_1_1BoneComponent.md),  [SR\_ANIMATIONS\_NS::Skeleton](classSR__ANIMATIONS__NS_1_1Skeleton.md),  [SR\_AUDIO\_NS::AudioListener](classSR__AUDIO__NS_1_1AudioListener.md),  [SR\_AUDIO\_NS::AudioSource](classSR__AUDIO__NS_1_1AudioSource.md),  [SR\_GRAPH\_UI\_NS::Canvas](classSR__GRAPH__UI__NS_1_1Canvas.md),  [SR\_GTYPES\_NS::Camera](classSR__GTYPES__NS_1_1Camera.md),  [SR\_GTYPES\_NS::IRenderComponent](classSR__GTYPES__NS_1_1IRenderComponent.md),  [SR\_GTYPES\_NS::RenderTechniqueComponent](classSR__GTYPES__NS_1_1RenderTechniqueComponent.md),  [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md),  [SR\_PTYPES\_NS::Rigidbody](classSR__PTYPES__NS_1_1Rigidbody.md),  [SR\_PTYPES\_NS::Vehicle](classSR__PTYPES__NS_1_1Vehicle.md),  [SR\_SCRIPTING\_NS::Behaviour](classSR__SCRIPTING__NS_1_1Behaviour.md),  [SR\_UTILS\_NS::CameraFlyMover](classSR__UTILS__NS_1_1CameraFlyMover.md),  [SR\_UTILS\_NS::DebugLogComponent](classSR__UTILS__NS_1_1DebugLogComponent.md),  [SR\_UTILS\_NS::LockPositionComponent](classSR__UTILS__NS_1_1LockPositionComponent.md),  [SR\_UTILS\_NS::LookAtComponent](classSR__UTILS__NS_1_1LookAtComponent.md),  [SR\_UTILS\_NS::Tests::ReflectionTestComponent](classSR__UTILS__NS_1_1Tests_1_1ReflectionTestComponent.md),  [SR\_UTILS\_NS::UI::UIModifierComponent](classSR__UTILS__NS_1_1UI_1_1UIModifierComponent.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) &gt; | [**GameObjectPtr**](#typedef-gameobjectptr)  <br> |
| typedef [**Component**](classSR__UTILS__NS_1_1Component.md) | [**OriginType**](#typedef-origintype)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Component**](classSR__UTILS__NS_1_1Component.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**SceneObjectPtr**](#typedef-sceneobjectptr)  <br> |
| typedef [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**ScenePtr**](#typedef-sceneptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Awake**](#function-awake) () <br> |
|  SR\_NODISCARD [**Component**](classSR__UTILS__NS_1_1Component.md) \* | [**BaseComponent**](#function-basecomponent) () noexcept<br> |
|  void | [**CheckActivity**](#function-checkactivity) () <br> |
|  SR\_NODISCARD Component::Ptr | [**CloneComponent**](#function-clonecomponent) () const<br> |
|   | [**Component**](#function-component) () <br> |
|  void | [**Detach**](#function-detach) () <br> |
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](#function-executeineditmode) () const<br> |
| virtual void | [**FixedUpdate**](#function-fixedupdate) () <br> |
| virtual SR\_NODISCARD Math::FVector3 | [**GetBarycenter**](#function-getbarycenter) () const<br> |
|  SR\_NODISCARD GameObjectPtr | [**GetGameObject**](#function-getgameobject) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetIndexInSceneUpdater**](#function-getindexinsceneupdater) () noexcept const<br> |
|  SR\_NODISCARD [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* | [**GetParent**](#function-getparent) () const<br> |
|  SR\_NODISCARD SceneObjectPtr | [**GetRoot**](#function-getroot) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](#function-getscene) () const<br> |
|  SR\_NODISCARD const SceneObjectPtr & | [**GetSceneObject**](#function-getsceneobject) () const<br> |
|  SR\_NODISCARD [**Transform**](classSR__UTILS__NS_1_1Transform.md) \* | [**GetTransform**](#function-gettransform) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasParent**](#function-hasparent) () const<br> |
|  SR\_NODISCARD bool | [**HasScene**](#function-hasscene) () const<br> |
| virtual SR\_NODISCARD bool | [**IsActive**](#function-isactive) () noexcept const<br>_Активен и компонент и его родительский объект_  |
|  SR\_NODISCARD bool | [**IsAttached**](#function-isattached) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsAwake**](#function-isawake) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsComponentLoaded**](#function-iscomponentloaded) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsComponentValid**](#function-iscomponentvalid) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEnabled**](#function-isenabled) () noexcept const<br>_Активен сам компонент, независимо от объекта_  |
|  SR\_NODISCARD bool | [**IsPausedMode**](#function-ispausedmode) () const<br>_На паузе ли сцена (если запущена)_  |
|  SR\_NODISCARD bool | [**IsPlayingMode**](#function-isplayingmode) () const<br>_Запущена ли сцена_  |
| virtual SR\_NODISCARD bool | [**IsStarted**](#function-isstarted) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsUpdatable**](#function-isupdatable) () noexcept const<br>_Активен и компонент и его родительский объект_  |
| virtual void | [**LateUpdate**](#function-lateupdate) () <br> |
| virtual void | [**OnAttached**](#function-onattached) () <br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnBeforeLayerChanged**](#function-onbeforelayerchanged) () <br> |
| virtual void | [**OnCollisionEnter**](#function-oncollisionenter) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnCollisionExit**](#function-oncollisionexit) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnCollisionStay**](#function-oncollisionstay) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnDestroy**](#function-ondestroy) () <br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDetached**](#function-ondetached) () <br>_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._  |
| virtual void | [**OnDisable**](#function-ondisable) () <br> |
| virtual void | [**OnEnable**](#function-onenable) () <br> |
| virtual void | [**OnLayerChanged**](#function-onlayerchanged) () <br> |
| virtual void | [**OnLoaded**](#function-onloaded) () <br>_Вызывается при загрузке компонента на игровой объект_  |
| virtual void | [**OnMatrixDirty**](#function-onmatrixdirty) () <br> |
| virtual void | [**OnPriorityChanged**](#function-onprioritychanged) () <br> |
| virtual void | [**OnTriggerEnter**](#function-ontriggerenter) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnTriggerExit**](#function-ontriggerexit) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnTriggerStay**](#function-ontriggerstay) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
|  void | [**SetEnabled**](#function-setenabled) (bool value) <br> |
|  void | [**SetIndexIdSceneUpdater**](#function-setindexidsceneupdater) (int32\_t index) <br> |
| virtual void | [**Start**](#function-start) () <br> |
|  SR\_NODISCARD [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* | [**TryGetParent**](#function-trygetparent) () const<br> |
|  SR\_NODISCARD ScenePtr | [**TryGetScene**](#function-trygetscene) () const<br> |
| virtual void | [**Update**](#function-update) (float\_t dt) <br> |
|   | [**~Component**](#function-component) () override<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int32\_t | [**m\_indexInSceneUpdater**](#variable-m_indexinsceneupdater)   = `SR\_ID\_INVALID`<br> |
|  bool | [**m\_isActive**](#variable-m_isactive)   = `false`<br> |
|  bool | [**m\_isAttached**](#variable-m_isattached)   = `false`<br> |
|  bool | [**m\_isAwake**](#variable-m_isawake)   = `false`<br> |
|  bool | [**m\_isComponentLoaded**](#variable-m_iscomponentloaded)   = `false`<br> |
|  bool | [**m\_isEnabled**](#variable-m_isenabled)   = `true`<br> |
|  bool | [**m\_isStarted**](#variable-m_isstarted)   = `false`<br> |
|  [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* | [**m\_parent**](#variable-m_parent)   = `nullptr`<br> |
|  [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**m\_scene**](#variable-m_scene)   = `nullptr`<br> |
|  SceneObjectPtr | [**m\_sceneObject**](#variable-m_sceneobject)   = `nullptr`<br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |




## Public Types Documentation




### typedef GameObjectPtr 

```C++
using SR_UTILS_NS::Component::GameObjectPtr =  SR_HTYPES_NS::SharedPtr<GameObject>;
```




<hr>



### typedef OriginType 

```C++
using SR_UTILS_NS::Component::OriginType =  Component;
```




<hr>



### typedef Ptr 

```C++
using SR_UTILS_NS::Component::Ptr =  SR_HTYPES_NS::SharedPtr<Component>;
```




<hr>



### typedef SceneObjectPtr 

```C++
using SR_UTILS_NS::Component::SceneObjectPtr =  SR_HTYPES_NS::SharedPtr<SceneObject>;
```




<hr>



### typedef ScenePtr 

```C++
using SR_UTILS_NS::Component::ScenePtr =  SR_WORLD_NS::Scene*;
```




<hr>
## Public Functions Documentation




### function Awake 

```C++
virtual void SR_UTILS_NS::Component::Awake () 
```




<hr>



### function BaseComponent 

```C++
SR_NODISCARD Component * SR_UTILS_NS::Component::BaseComponent () noexcept
```




<hr>



### function CheckActivity 

```C++
void SR_UTILS_NS::Component::CheckActivity () 
```




<hr>



### function CloneComponent 

```C++
SR_NODISCARD Component::Ptr SR_UTILS_NS::Component::CloneComponent () const
```




<hr>



### function Component 

```C++
SR_UTILS_NS::Component::Component () 
```




<hr>



### function Detach 

```C++
void SR_UTILS_NS::Component::Detach () 
```




<hr>



### function ExecuteInEditMode 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::Component::ExecuteInEditMode () const
```




<hr>



### function FixedUpdate 

```C++
virtual void SR_UTILS_NS::Component::FixedUpdate () 
```




<hr>



### function GetBarycenter 

```C++
virtual SR_NODISCARD Math::FVector3 SR_UTILS_NS::Component::GetBarycenter () const
```




<hr>



### function GetGameObject 

```C++
SR_NODISCARD GameObjectPtr SR_UTILS_NS::Component::GetGameObject () const
```




<hr>



### function GetIndexInSceneUpdater 

```C++
SR_NODISCARD int32_t SR_UTILS_NS::Component::GetIndexInSceneUpdater () noexcept const
```




<hr>



### function GetParent 

```C++
SR_NODISCARD IComponentable * SR_UTILS_NS::Component::GetParent () const
```




<hr>



### function GetRoot 

```C++
SR_NODISCARD SceneObjectPtr SR_UTILS_NS::Component::GetRoot () const
```




<hr>



### function GetScene 

```C++
SR_NODISCARD ScenePtr SR_UTILS_NS::Component::GetScene () const
```




<hr>



### function GetSceneObject 

```C++
SR_NODISCARD const SceneObjectPtr & SR_UTILS_NS::Component::GetSceneObject () const
```




<hr>



### function GetTransform 

```C++
SR_NODISCARD Transform * SR_UTILS_NS::Component::GetTransform () noexcept const
```




<hr>



### function HasParent 

```C++
SR_NODISCARD bool SR_UTILS_NS::Component::HasParent () const
```




<hr>



### function HasScene 

```C++
SR_NODISCARD bool SR_UTILS_NS::Component::HasScene () const
```




<hr>



### function IsActive 

_Активен и компонент и его родительский объект_ 
```C++
virtual SR_NODISCARD bool SR_UTILS_NS::Component::IsActive () noexcept const
```




<hr>



### function IsAttached 

```C++
SR_NODISCARD bool SR_UTILS_NS::Component::IsAttached () noexcept const
```




<hr>



### function IsAwake 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::Component::IsAwake () noexcept const
```




<hr>



### function IsComponentLoaded 

```C++
SR_NODISCARD bool SR_UTILS_NS::Component::IsComponentLoaded () noexcept const
```




<hr>



### function IsComponentValid 

```C++
SR_NODISCARD bool SR_UTILS_NS::Component::IsComponentValid () noexcept const
```




<hr>



### function IsEnabled 

_Активен сам компонент, независимо от объекта_ 
```C++
virtual SR_NODISCARD bool SR_UTILS_NS::Component::IsEnabled () noexcept const
```




<hr>



### function IsPausedMode 

_На паузе ли сцена (если запущена)_ 
```C++
SR_NODISCARD bool SR_UTILS_NS::Component::IsPausedMode () const
```




<hr>



### function IsPlayingMode 

_Запущена ли сцена_ 
```C++
SR_NODISCARD bool SR_UTILS_NS::Component::IsPlayingMode () const
```




<hr>



### function IsStarted 

```C++
virtual SR_NODISCARD bool SR_UTILS_NS::Component::IsStarted () noexcept const
```




<hr>



### function IsUpdatable 

_Активен и компонент и его родительский объект_ 
```C++
virtual SR_NODISCARD bool SR_UTILS_NS::Component::IsUpdatable () noexcept const
```




<hr>



### function LateUpdate 

```C++
virtual void SR_UTILS_NS::Component::LateUpdate () 
```




<hr>



### function OnAttached 

_Вызывается после добавления компонента к игровому объекту_ 
```C++
virtual void SR_UTILS_NS::Component::OnAttached () 
```




<hr>



### function OnBeforeLayerChanged 

```C++
virtual void SR_UTILS_NS::Component::OnBeforeLayerChanged () 
```




<hr>



### function OnCollisionEnter 

```C++
virtual void SR_UTILS_NS::Component::OnCollisionEnter (
    const CollisionData & data
) 
```




<hr>



### function OnCollisionExit 

```C++
virtual void SR_UTILS_NS::Component::OnCollisionExit (
    const CollisionData & data
) 
```




<hr>



### function OnCollisionStay 

```C++
virtual void SR_UTILS_NS::Component::OnCollisionStay (
    const CollisionData & data
) 
```




<hr>



### function OnDestroy 

_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._ 
```C++
virtual void SR_UTILS_NS::Component::OnDestroy () 
```




<hr>



### function OnDetached 

_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._ 
```C++
virtual void SR_UTILS_NS::Component::OnDetached () 
```




<hr>



### function OnDisable 

```C++
virtual void SR_UTILS_NS::Component::OnDisable () 
```




<hr>



### function OnEnable 

```C++
virtual void SR_UTILS_NS::Component::OnEnable () 
```




<hr>



### function OnLayerChanged 

```C++
virtual void SR_UTILS_NS::Component::OnLayerChanged () 
```




<hr>



### function OnLoaded 

_Вызывается при загрузке компонента на игровой объект_ 
```C++
virtual void SR_UTILS_NS::Component::OnLoaded () 
```




<hr>



### function OnMatrixDirty 

```C++
virtual void SR_UTILS_NS::Component::OnMatrixDirty () 
```




<hr>



### function OnPriorityChanged 

```C++
virtual void SR_UTILS_NS::Component::OnPriorityChanged () 
```




<hr>



### function OnTriggerEnter 

```C++
virtual void SR_UTILS_NS::Component::OnTriggerEnter (
    const CollisionData & data
) 
```




<hr>



### function OnTriggerExit 

```C++
virtual void SR_UTILS_NS::Component::OnTriggerExit (
    const CollisionData & data
) 
```




<hr>



### function OnTriggerStay 

```C++
virtual void SR_UTILS_NS::Component::OnTriggerStay (
    const CollisionData & data
) 
```




<hr>



### function SetEnabled 

```C++
void SR_UTILS_NS::Component::SetEnabled (
    bool value
) 
```




<hr>



### function SetIndexIdSceneUpdater 

```C++
void SR_UTILS_NS::Component::SetIndexIdSceneUpdater (
    int32_t index
) 
```




<hr>



### function Start 

```C++
virtual void SR_UTILS_NS::Component::Start () 
```




<hr>



### function TryGetParent 

```C++
SR_NODISCARD IComponentable * SR_UTILS_NS::Component::TryGetParent () const
```




<hr>



### function TryGetScene 

```C++
SR_NODISCARD ScenePtr SR_UTILS_NS::Component::TryGetScene () const
```




<hr>



### function Update 

```C++
virtual void SR_UTILS_NS::Component::Update (
    float_t dt
) 
```




<hr>



### function ~Component 

```C++
SR_UTILS_NS::Component::~Component () override
```




<hr>
## Protected Attributes Documentation




### variable m\_indexInSceneUpdater 

```C++
int32_t SR_UTILS_NS::Component::m_indexInSceneUpdater;
```




<hr>



### variable m\_isActive 

```C++
bool SR_UTILS_NS::Component::m_isActive;
```




<hr>



### variable m\_isAttached 

```C++
bool SR_UTILS_NS::Component::m_isAttached;
```




<hr>



### variable m\_isAwake 

```C++
bool SR_UTILS_NS::Component::m_isAwake;
```




<hr>



### variable m\_isComponentLoaded 

```C++
bool SR_UTILS_NS::Component::m_isComponentLoaded;
```




<hr>



### variable m\_isEnabled 

```C++
bool SR_UTILS_NS::Component::m_isEnabled;
```




<hr>



### variable m\_isStarted 

```C++
bool SR_UTILS_NS::Component::m_isStarted;
```




<hr>



### variable m\_parent 

```C++
IComponentable* SR_UTILS_NS::Component::m_parent;
```




<hr>



### variable m\_scene 

```C++
SR_WORLD_NS::Scene* SR_UTILS_NS::Component::m_scene;
```




<hr>



### variable m\_sceneObject 

```C++
SceneObjectPtr SR_UTILS_NS::Component::m_sceneObject;
```




<hr>
## Protected Functions Documentation




### function SetParent 

```C++
void SR_UTILS_NS::Component::SetParent (
    IComponentable * pParent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/ECS/Component.h`

