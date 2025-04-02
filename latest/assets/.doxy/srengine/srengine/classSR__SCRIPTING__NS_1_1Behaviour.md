

# Class SR\_SCRIPTING\_NS::Behaviour



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**Behaviour**](classSR__SCRIPTING__NS_1_1Behaviour.md)



[More...](#detailed-description)

* `#include <Behaviour.h>`



Inherits the following classes: [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)
















## Public Types inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) &gt; | [**GameObjectPtr**](classSR__UTILS__NS_1_1Component.md#typedef-gameobjectptr)  <br> |
| typedef [**Component**](classSR__UTILS__NS_1_1Component.md) | [**OriginType**](classSR__UTILS__NS_1_1Component.md#typedef-origintype)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Component**](classSR__UTILS__NS_1_1Component.md) &gt; | [**Ptr**](classSR__UTILS__NS_1_1Component.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**SceneObjectPtr**](classSR__UTILS__NS_1_1Component.md#typedef-sceneobjectptr)  <br> |
| typedef [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**ScenePtr**](classSR__UTILS__NS_1_1Component.md#typedef-sceneptr)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**IRawBehaviour**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md) \* | [**GetRawBehaviour**](#function-getrawbehaviour) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetRawBehaviourPath**](#function-getrawbehaviourpath) () noexcept const<br> |
|  bool | [**Load**](#function-load) ([**SR\_UTILS\_NS::IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer) override<br> |
|  void | [**OnBehaviourChanged**](#function-onbehaviourchanged) () <br> |
|  void | [**Reload**](#function-reload) () <br> |
|  void | [**Save**](#function-save) ([**SR\_UTILS\_NS::ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer) override const<br> |
|  void | [**SetRawBehaviour**](#function-setrawbehaviour) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |


## Public Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Awake**](classSR__UTILS__NS_1_1Component.md#function-awake) () <br> |
|  SR\_NODISCARD [**Component**](classSR__UTILS__NS_1_1Component.md) \* | [**BaseComponent**](classSR__UTILS__NS_1_1Component.md#function-basecomponent) () noexcept<br> |
|  void | [**CheckActivity**](classSR__UTILS__NS_1_1Component.md#function-checkactivity) () <br> |
|  SR\_NODISCARD Component::Ptr | [**CloneComponent**](classSR__UTILS__NS_1_1Component.md#function-clonecomponent) () const<br> |
|  void | [**Detach**](classSR__UTILS__NS_1_1Component.md#function-detach) () <br> |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**ExecuteInEditMode**](classSR__UTILS__NS_1_1Component.md#function-executeineditmode) () const<br> |
| virtual void | [**FixedUpdate**](classSR__UTILS__NS_1_1Component.md#function-fixedupdate) () <br> |
| virtual SR\_NODISCARD Math::FVector3 | [**GetBarycenter**](classSR__UTILS__NS_1_1Component.md#function-getbarycenter) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**GetComponentProperties**](classSR__UTILS__NS_1_1Component.md#function-getcomponentproperties-12) () noexcept<br> |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) & | [**GetComponentProperties**](classSR__UTILS__NS_1_1Component.md#function-getcomponentproperties-22) () noexcept const<br> |
|  SR\_NODISCARD GameObjectPtr | [**GetGameObject**](classSR__UTILS__NS_1_1Component.md#function-getgameobject) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetIndexInSceneUpdater**](classSR__UTILS__NS_1_1Component.md#function-getindexinsceneupdater) () noexcept const<br> |
|  SR\_NODISCARD [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* | [**GetParent**](classSR__UTILS__NS_1_1Component.md#function-getparent) () const<br> |
|  SR\_NODISCARD SceneObjectPtr | [**GetRoot**](classSR__UTILS__NS_1_1Component.md#function-getroot) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](classSR__UTILS__NS_1_1Component.md#function-getscene) () const<br> |
|  SR\_NODISCARD SceneObjectPtr | [**GetSceneObject**](classSR__UTILS__NS_1_1Component.md#function-getsceneobject) () const<br> |
|  SR\_NODISCARD [**Transform**](classSR__UTILS__NS_1_1Transform.md) \* | [**GetTransform**](classSR__UTILS__NS_1_1Component.md#function-gettransform) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasParent**](classSR__UTILS__NS_1_1Component.md#function-hasparent) () const<br> |
|  SR\_NODISCARD bool | [**HasScene**](classSR__UTILS__NS_1_1Component.md#function-hasscene) () const<br> |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**IsActive**](classSR__UTILS__NS_1_1Component.md#function-isactive) () noexcept const<br>_Активен и компонент и его родительский объект_  |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**IsAttached**](classSR__UTILS__NS_1_1Component.md#function-isattached) () noexcept const<br> |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**IsAwake**](classSR__UTILS__NS_1_1Component.md#function-isawake) () noexcept const<br> |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**IsComponentLoaded**](classSR__UTILS__NS_1_1Component.md#function-iscomponentloaded) () noexcept const<br> |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**IsComponentValid**](classSR__UTILS__NS_1_1Component.md#function-iscomponentvalid) () noexcept const<br> |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**IsEnabled**](classSR__UTILS__NS_1_1Component.md#function-isenabled) () noexcept const<br>_Активен сам компонент, независимо от объекта_  |
|  SR\_NODISCARD bool | [**IsPausedMode**](classSR__UTILS__NS_1_1Component.md#function-ispausedmode) () const<br>_На паузе ли сцена (если запущена)_  |
|  SR\_NODISCARD bool | [**IsPlayingMode**](classSR__UTILS__NS_1_1Component.md#function-isplayingmode) () const<br>_Запущена ли сцена_  |
| virtual SR\_NODISCARD virtual SR\_FORCE\_INLINE bool | [**IsStarted**](classSR__UTILS__NS_1_1Component.md#function-isstarted) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsUpdatable**](classSR__UTILS__NS_1_1Component.md#function-isupdatable) () noexcept const<br>_Активен и компонент и его родительский объект_  |
| virtual void | [**LateUpdate**](classSR__UTILS__NS_1_1Component.md#function-lateupdate) () <br> |
| virtual void | [**OnAttached**](classSR__UTILS__NS_1_1Component.md#function-onattached) () <br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnBeforeLayerChanged**](classSR__UTILS__NS_1_1Component.md#function-onbeforelayerchanged) () <br> |
| virtual void | [**OnCollisionEnter**](classSR__UTILS__NS_1_1Component.md#function-oncollisionenter) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnCollisionExit**](classSR__UTILS__NS_1_1Component.md#function-oncollisionexit) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnCollisionStay**](classSR__UTILS__NS_1_1Component.md#function-oncollisionstay) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnDestroy**](classSR__UTILS__NS_1_1Component.md#function-ondestroy) () <br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDetached**](classSR__UTILS__NS_1_1Component.md#function-ondetached) () <br>_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._  |
| virtual void | [**OnDisable**](classSR__UTILS__NS_1_1Component.md#function-ondisable) () <br> |
| virtual void | [**OnEnable**](classSR__UTILS__NS_1_1Component.md#function-onenable) () <br> |
| virtual void | [**OnLayerChanged**](classSR__UTILS__NS_1_1Component.md#function-onlayerchanged) () <br> |
| virtual void | [**OnLoaded**](classSR__UTILS__NS_1_1Component.md#function-onloaded) () <br>_Вызывается при загрузке компонента на игровой объект_  |
| virtual void | [**OnMatrixDirty**](classSR__UTILS__NS_1_1Component.md#function-onmatrixdirty) () <br> |
| virtual void | [**OnPriorityChanged**](classSR__UTILS__NS_1_1Component.md#function-onprioritychanged) () <br> |
| virtual void | [**OnTransformSet**](classSR__UTILS__NS_1_1Component.md#function-ontransformset) () <br> |
| virtual void | [**OnTriggerEnter**](classSR__UTILS__NS_1_1Component.md#function-ontriggerenter) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnTriggerExit**](classSR__UTILS__NS_1_1Component.md#function-ontriggerexit) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
| virtual void | [**OnTriggerStay**](classSR__UTILS__NS_1_1Component.md#function-ontriggerstay) (const [**CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) <br> |
|  void | [**SetEnabled**](classSR__UTILS__NS_1_1Component.md#function-setenabled) (bool value) <br> |
|  void | [**SetIndexIdSceneUpdater**](classSR__UTILS__NS_1_1Component.md#function-setindexidsceneupdater) (int32\_t index) <br> |
| virtual void | [**Start**](classSR__UTILS__NS_1_1Component.md#function-start) () <br> |
|  SR\_NODISCARD [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* | [**TryGetParent**](classSR__UTILS__NS_1_1Component.md#function-trygetparent) () const<br> |
|  SR\_NODISCARD ScenePtr | [**TryGetScene**](classSR__UTILS__NS_1_1Component.md#function-trygetscene) () const<br> |
| virtual void | [**Update**](classSR__UTILS__NS_1_1Component.md#function-update) (float\_t dt) <br> |
|   | [**~Component**](classSR__UTILS__NS_1_1Component.md#function-component) () override<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**IRawBehaviour**](classSR__SCRIPTING__NS_1_1IRawBehaviour.md) \* | [**m\_rawBehaviour**](#variable-m_rawbehaviour)   = `nullptr`<br> |


## Protected Attributes inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  int32\_t | [**m\_indexInSceneUpdater**](classSR__UTILS__NS_1_1Component.md#variable-m_indexinsceneupdater)   = `SR\_ID\_INVALID`<br> |
|  bool | [**m\_isActive**](classSR__UTILS__NS_1_1Component.md#variable-m_isactive)   = `false`<br> |
|  bool | [**m\_isAttached**](classSR__UTILS__NS_1_1Component.md#variable-m_isattached)   = `false`<br> |
|  bool | [**m\_isAwake**](classSR__UTILS__NS_1_1Component.md#variable-m_isawake)   = `false`<br> |
|  bool | [**m\_isComponentLoaded**](classSR__UTILS__NS_1_1Component.md#variable-m_iscomponentloaded)   = `false`<br> |
|  bool | [**m\_isEnabled**](classSR__UTILS__NS_1_1Component.md#variable-m_isenabled)   = `true`<br> |
|  bool | [**m\_isStarted**](classSR__UTILS__NS_1_1Component.md#variable-m_isstarted)   = `false`<br> |
|  [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* | [**m\_parent**](classSR__UTILS__NS_1_1Component.md#variable-m_parent)   = `nullptr`<br> |
|  [**SR\_UTILS\_NS::PropertyContainer**](classSR__UTILS__NS_1_1PropertyContainer.md) | [**m\_properties**](classSR__UTILS__NS_1_1Component.md#variable-m_properties)  <br> |
|  [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**m\_scene**](classSR__UTILS__NS_1_1Component.md#variable-m_scene)   = `nullptr`<br> |
|  SceneObjectPtr | [**m\_sceneObject**](classSR__UTILS__NS_1_1Component.md#variable-m_sceneobject)   = `nullptr`<br> |






























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Awake**](#function-awake) () override<br> |
| virtual void | [**FixedUpdate**](#function-fixedupdate) () override<br> |
| virtual void | [**OnAttached**](#function-onattached) () override<br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnCollisionEnter**](#function-oncollisionenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnCollisionExit**](#function-oncollisionexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnCollisionStay**](#function-oncollisionstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnDestroy**](#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDetached**](#function-ondetached) () override<br>_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._  |
| virtual void | [**OnDisable**](#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](#function-onenable) () override<br> |
| virtual void | [**OnTransformSet**](#function-ontransformset) () override<br> |
| virtual void | [**OnTriggerEnter**](#function-ontriggerenter) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnTriggerExit**](#function-ontriggerexit) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**OnTriggerStay**](#function-ontriggerstay) (const [**SR\_UTILS\_NS::CollisionData**](structSR__UTILS__NS_1_1CollisionData.md) & data) override<br> |
| virtual void | [**Start**](#function-start) () override<br> |
| virtual void | [**Update**](#function-update) (float\_t dt) override<br> |


## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |






## Detailed Description



 


    
## Public Functions Documentation




### function GetRawBehaviour 

```C++
inline SR_NODISCARD IRawBehaviour * SR_SCRIPTING_NS::Behaviour::GetRawBehaviour () noexcept const
```




<hr>



### function GetRawBehaviourPath 

```C++
SR_NODISCARD SR_UTILS_NS::Path SR_SCRIPTING_NS::Behaviour::GetRawBehaviourPath () noexcept const
```




<hr>



### function Load 

```C++
bool SR_SCRIPTING_NS::Behaviour::Load (
    SR_UTILS_NS::IDeserializer & deserializer
) override
```




<hr>



### function OnBehaviourChanged 

```C++
void SR_SCRIPTING_NS::Behaviour::OnBehaviourChanged () 
```




<hr>



### function Reload 

```C++
void SR_SCRIPTING_NS::Behaviour::Reload () 
```




<hr>



### function Save 

```C++
void SR_SCRIPTING_NS::Behaviour::Save (
    SR_UTILS_NS::ISerializer & serializer
) override const
```




<hr>



### function SetRawBehaviour 

```C++
void SR_SCRIPTING_NS::Behaviour::SetRawBehaviour (
    const SR_UTILS_NS::Path & path
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_rawBehaviour 

```C++
IRawBehaviour* SR_SCRIPTING_NS::Behaviour::m_rawBehaviour;
```




<hr>
## Protected Functions Documentation




### function Awake 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::Awake () override
```



Implements [*SR\_UTILS\_NS::Component::Awake*](classSR__UTILS__NS_1_1Component.md#function-awake)


<hr>



### function FixedUpdate 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::FixedUpdate () override
```



Implements [*SR\_UTILS\_NS::Component::FixedUpdate*](classSR__UTILS__NS_1_1Component.md#function-fixedupdate)


<hr>



### function OnAttached 

_Вызывается после добавления компонента к игровому объекту_ 
```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnAttached () override
```



Implements [*SR\_UTILS\_NS::Component::OnAttached*](classSR__UTILS__NS_1_1Component.md#function-onattached)


<hr>



### function OnCollisionEnter 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnCollisionEnter (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_UTILS\_NS::Component::OnCollisionEnter*](classSR__UTILS__NS_1_1Component.md#function-oncollisionenter)


<hr>



### function OnCollisionExit 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnCollisionExit (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_UTILS\_NS::Component::OnCollisionExit*](classSR__UTILS__NS_1_1Component.md#function-oncollisionexit)


<hr>



### function OnCollisionStay 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnCollisionStay (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_UTILS\_NS::Component::OnCollisionStay*](classSR__UTILS__NS_1_1Component.md#function-oncollisionstay)


<hr>



### function OnDestroy 

_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._ 
```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnDestroy () override
```



Implements [*SR\_UTILS\_NS::Component::OnDestroy*](classSR__UTILS__NS_1_1Component.md#function-ondestroy)


<hr>



### function OnDetached 

_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._ 
```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnDetached () override
```



Implements [*SR\_UTILS\_NS::Component::OnDetached*](classSR__UTILS__NS_1_1Component.md#function-ondetached)


<hr>



### function OnDisable 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnDisable () override
```



Implements [*SR\_UTILS\_NS::Component::OnDisable*](classSR__UTILS__NS_1_1Component.md#function-ondisable)


<hr>



### function OnEnable 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnEnable () override
```



Implements [*SR\_UTILS\_NS::Component::OnEnable*](classSR__UTILS__NS_1_1Component.md#function-onenable)


<hr>



### function OnTransformSet 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnTransformSet () override
```



Implements [*SR\_UTILS\_NS::Component::OnTransformSet*](classSR__UTILS__NS_1_1Component.md#function-ontransformset)


<hr>



### function OnTriggerEnter 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnTriggerEnter (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_UTILS\_NS::Component::OnTriggerEnter*](classSR__UTILS__NS_1_1Component.md#function-ontriggerenter)


<hr>



### function OnTriggerExit 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnTriggerExit (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_UTILS\_NS::Component::OnTriggerExit*](classSR__UTILS__NS_1_1Component.md#function-ontriggerexit)


<hr>



### function OnTriggerStay 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::OnTriggerStay (
    const SR_UTILS_NS::CollisionData & data
) override
```



Implements [*SR\_UTILS\_NS::Component::OnTriggerStay*](classSR__UTILS__NS_1_1Component.md#function-ontriggerstay)


<hr>



### function Start 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::Start () override
```



Implements [*SR\_UTILS\_NS::Component::Start*](classSR__UTILS__NS_1_1Component.md#function-start)


<hr>



### function Update 

```C++
virtual void SR_SCRIPTING_NS::Behaviour::Update (
    float_t dt
) override
```



Implements [*SR\_UTILS\_NS::Component::Update*](classSR__UTILS__NS_1_1Component.md#function-update)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Scripting/inc/Scripting/Base/Behaviour.h`

