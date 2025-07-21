

# Class SR\_AUDIO\_NS::AudioSource



[**ClassList**](annotated.md) **>** [**SR\_AUDIO\_NS**](namespaceSR__AUDIO__NS.md) **>** [**AudioSource**](classSR__AUDIO__NS_1_1AudioSource.md)








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
|   | [**AudioSource**](#function-audiosource) () <br> |
|  SR\_NODISCARD float\_t | [**GetConeInnerAngle**](#function-getconeinnerangle) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetDirection**](#function-getdirection) () const<br> |
|  SR\_NODISCARD bool | [**GetLoop**](#function-getloop) () const<br> |
|  SR\_NODISCARD float\_t | [**GetMaxDistance**](#function-getmaxdistance) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetPath**](#function-getpath) () const<br> |
|  SR\_NODISCARD float\_t | [**GetPitch**](#function-getpitch) () const<br> |
|  SR\_NODISCARD float\_t | [**GetReferenceDistance**](#function-getreferencedistance) () const<br> |
|  SR\_NODISCARD float\_t | [**GetRolloffFactor**](#function-getrollofffactor) () const<br> |
|  SR\_NODISCARD SpatializeMode | [**GetSpatialize**](#function-getspatialize) () const<br> |
|  SR\_NODISCARD float\_t | [**GetVolume**](#function-getvolume) () const<br> |
| virtual void | [**OnMatrixDirty**](#function-onmatrixdirty) () override<br> |
|  void | [**SetConeInnerAngle**](#function-setconeinnerangle) (float\_t Angle) <br> |
|  void | [**SetDirection**](#function-setdirection) (const SR\_MATH\_NS::FVector3 & direction) <br> |
|  void | [**SetLoop**](#function-setloop) (bool loop) <br> |
|  void | [**SetMaxDistance**](#function-setmaxdistance) (float\_t maxDistance) <br> |
|  void | [**SetPath**](#function-setpath) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetPitch**](#function-setpitch) (float\_t pitch) <br> |
|  void | [**SetReferenceDistance**](#function-setreferencedistance) (float\_t referenceDistance) <br> |
|  void | [**SetRolloffFactor**](#function-setrollofffactor) (float\_t rolloffFactor) <br> |
|  void | [**SetSpatialize**](#function-setspatialize) (SpatializeMode spatialize) <br> |
|  void | [**SetVolume**](#function-setvolume) (float\_t volume) <br> |


## Public Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**Awake**](classSR__UTILS__NS_1_1Component.md#function-awake) () <br> |
|  SR\_NODISCARD [**Component**](classSR__UTILS__NS_1_1Component.md) \* | [**BaseComponent**](classSR__UTILS__NS_1_1Component.md#function-basecomponent) () noexcept<br> |
|  void | [**CheckActivity**](classSR__UTILS__NS_1_1Component.md#function-checkactivity) () <br> |
|  SR\_NODISCARD Component::Ptr | [**CloneComponent**](classSR__UTILS__NS_1_1Component.md#function-clonecomponent) () const<br> |
|   | [**Component**](classSR__UTILS__NS_1_1Component.md#function-component) () <br> |
|  void | [**Detach**](classSR__UTILS__NS_1_1Component.md#function-detach) () <br> |
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](classSR__UTILS__NS_1_1Component.md#function-executeineditmode) () const<br> |
| virtual void | [**FixedUpdate**](classSR__UTILS__NS_1_1Component.md#function-fixedupdate) () <br> |
| virtual SR\_NODISCARD Math::FVector3 | [**GetBarycenter**](classSR__UTILS__NS_1_1Component.md#function-getbarycenter) () const<br> |
|  SR\_NODISCARD GameObjectPtr | [**GetGameObject**](classSR__UTILS__NS_1_1Component.md#function-getgameobject) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetIndexInSceneUpdater**](classSR__UTILS__NS_1_1Component.md#function-getindexinsceneupdater) () noexcept const<br> |
|  SR\_NODISCARD [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* | [**GetParent**](classSR__UTILS__NS_1_1Component.md#function-getparent) () const<br> |
|  SR\_NODISCARD SceneObjectPtr | [**GetRoot**](classSR__UTILS__NS_1_1Component.md#function-getroot) () const<br> |
|  SR\_NODISCARD ScenePtr | [**GetScene**](classSR__UTILS__NS_1_1Component.md#function-getscene) () const<br> |
|  SR\_NODISCARD const SceneObjectPtr & | [**GetSceneObject**](classSR__UTILS__NS_1_1Component.md#function-getsceneobject) () const<br> |
|  SR\_NODISCARD [**Transform**](classSR__UTILS__NS_1_1Transform.md) \* | [**GetTransform**](classSR__UTILS__NS_1_1Component.md#function-gettransform) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasParent**](classSR__UTILS__NS_1_1Component.md#function-hasparent) () const<br> |
|  SR\_NODISCARD bool | [**HasScene**](classSR__UTILS__NS_1_1Component.md#function-hasscene) () const<br> |
| virtual SR\_NODISCARD bool | [**IsActive**](classSR__UTILS__NS_1_1Component.md#function-isactive) () noexcept const<br>_Активен и компонент и его родительский объект_  |
|  SR\_NODISCARD bool | [**IsAttached**](classSR__UTILS__NS_1_1Component.md#function-isattached) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsAwake**](classSR__UTILS__NS_1_1Component.md#function-isawake) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsComponentLoaded**](classSR__UTILS__NS_1_1Component.md#function-iscomponentloaded) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsComponentValid**](classSR__UTILS__NS_1_1Component.md#function-iscomponentvalid) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEnabled**](classSR__UTILS__NS_1_1Component.md#function-isenabled) () noexcept const<br>_Активен сам компонент, независимо от объекта_  |
|  SR\_NODISCARD bool | [**IsPausedMode**](classSR__UTILS__NS_1_1Component.md#function-ispausedmode) () const<br>_На паузе ли сцена (если запущена)_  |
|  SR\_NODISCARD bool | [**IsPlayingMode**](classSR__UTILS__NS_1_1Component.md#function-isplayingmode) () const<br>_Запущена ли сцена_  |
| virtual SR\_NODISCARD bool | [**IsStarted**](classSR__UTILS__NS_1_1Component.md#function-isstarted) () noexcept const<br> |
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
|  [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**m\_scene**](classSR__UTILS__NS_1_1Component.md#variable-m_scene)   = `nullptr`<br> |
|  SceneObjectPtr | [**m\_sceneObject**](classSR__UTILS__NS_1_1Component.md#variable-m_sceneobject)   = `nullptr`<br> |






























## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnDestroy**](#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](#function-onenable) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |






## Public Functions Documentation




### function AudioSource 

```C++
SR_AUDIO_NS::AudioSource::AudioSource () 
```




<hr>



### function GetConeInnerAngle 

```C++
SR_NODISCARD float_t SR_AUDIO_NS::AudioSource::GetConeInnerAngle () const
```




<hr>



### function GetDirection 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_AUDIO_NS::AudioSource::GetDirection () const
```




<hr>



### function GetLoop 

```C++
SR_NODISCARD bool SR_AUDIO_NS::AudioSource::GetLoop () const
```




<hr>



### function GetMaxDistance 

```C++
SR_NODISCARD float_t SR_AUDIO_NS::AudioSource::GetMaxDistance () const
```




<hr>



### function GetPath 

```C++
SR_NODISCARD SR_UTILS_NS::Path SR_AUDIO_NS::AudioSource::GetPath () const
```




<hr>



### function GetPitch 

```C++
SR_NODISCARD float_t SR_AUDIO_NS::AudioSource::GetPitch () const
```




<hr>



### function GetReferenceDistance 

```C++
SR_NODISCARD float_t SR_AUDIO_NS::AudioSource::GetReferenceDistance () const
```




<hr>



### function GetRolloffFactor 

```C++
SR_NODISCARD float_t SR_AUDIO_NS::AudioSource::GetRolloffFactor () const
```




<hr>



### function GetSpatialize 

```C++
SR_NODISCARD SpatializeMode SR_AUDIO_NS::AudioSource::GetSpatialize () const
```




<hr>



### function GetVolume 

```C++
SR_NODISCARD float_t SR_AUDIO_NS::AudioSource::GetVolume () const
```




<hr>



### function OnMatrixDirty 

```C++
virtual void SR_AUDIO_NS::AudioSource::OnMatrixDirty () override
```



Implements [*SR\_UTILS\_NS::Component::OnMatrixDirty*](classSR__UTILS__NS_1_1Component.md#function-onmatrixdirty)


<hr>



### function SetConeInnerAngle 

```C++
void SR_AUDIO_NS::AudioSource::SetConeInnerAngle (
    float_t Angle
) 
```




<hr>



### function SetDirection 

```C++
void SR_AUDIO_NS::AudioSource::SetDirection (
    const SR_MATH_NS::FVector3 & direction
) 
```




<hr>



### function SetLoop 

```C++
void SR_AUDIO_NS::AudioSource::SetLoop (
    bool loop
) 
```




<hr>



### function SetMaxDistance 

```C++
void SR_AUDIO_NS::AudioSource::SetMaxDistance (
    float_t maxDistance
) 
```




<hr>



### function SetPath 

```C++
void SR_AUDIO_NS::AudioSource::SetPath (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function SetPitch 

```C++
void SR_AUDIO_NS::AudioSource::SetPitch (
    float_t pitch
) 
```




<hr>



### function SetReferenceDistance 

```C++
void SR_AUDIO_NS::AudioSource::SetReferenceDistance (
    float_t referenceDistance
) 
```




<hr>



### function SetRolloffFactor 

```C++
void SR_AUDIO_NS::AudioSource::SetRolloffFactor (
    float_t rolloffFactor
) 
```




<hr>



### function SetSpatialize 

```C++
void SR_AUDIO_NS::AudioSource::SetSpatialize (
    SpatializeMode spatialize
) 
```




<hr>



### function SetVolume 

```C++
void SR_AUDIO_NS::AudioSource::SetVolume (
    float_t volume
) 
```




<hr>
## Protected Functions Documentation




### function OnDestroy 

_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._ 
```C++
virtual void SR_AUDIO_NS::AudioSource::OnDestroy () override
```



Implements [*SR\_UTILS\_NS::Component::OnDestroy*](classSR__UTILS__NS_1_1Component.md#function-ondestroy)


<hr>



### function OnDisable 

```C++
virtual void SR_AUDIO_NS::AudioSource::OnDisable () override
```



Implements [*SR\_UTILS\_NS::Component::OnDisable*](classSR__UTILS__NS_1_1Component.md#function-ondisable)


<hr>



### function OnEnable 

```C++
virtual void SR_AUDIO_NS::AudioSource::OnEnable () override
```



Implements [*SR\_UTILS\_NS::Component::OnEnable*](classSR__UTILS__NS_1_1Component.md#function-onenable)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Audio/inc/Audio/Types/AudioSource.h`

