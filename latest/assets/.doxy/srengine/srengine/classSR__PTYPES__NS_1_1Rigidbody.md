

# Class SR\_PTYPES\_NS::Rigidbody



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md)



[More...](#detailed-description)

* `#include <Rigidbody.h>`



Inherits the following classes: [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)


Inherited by the following classes: [SR\_PTYPES\_NS::Rigidbody2D](classSR__PTYPES__NS_1_1Rigidbody2D.md),  [SR\_PTYPES\_NS::Rigidbody3D](classSR__PTYPES__NS_1_1Rigidbody3D.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


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
|  void | [**ClearForces**](#function-clearforces) () <br> |
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](#function-executeineditmode) () override const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenter**](#function-getcenter) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenterDirection**](#function-getcenterdirection) () noexcept const<br> |
|  SR\_NODISCARD const CollisionShape::Ptr & | [**GetCollisionShape**](#function-getcollisionshape) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD T \* | [**GetLibrary**](#function-getlibrary) () const<br> |
|  SR\_NODISCARD float\_t | [**GetMass**](#function-getmass) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_UTILS\_NS::Measurement | [**GetMeasurement**](#function-getmeasurement) () const = 0<br> |
|  SR\_NODISCARD PhysicsMaterial::Ptr | [**GetPhysicsMaterial**](#function-getphysicsmaterial) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**GetRotation**](#function-getrotation) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetScale**](#function-getscale) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetTranslation**](#function-gettranslation) () noexcept const<br> |
|  SR\_NODISCARD ShapeType | [**GetType**](#function-gettype) () noexcept const<br> |
|  bool | [**InitBody**](#function-initbody) () <br> |
|  SR\_NODISCARD bool | [**IsBodyDirty**](#function-isbodydirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDebugEnabled**](#function-isdebugenabled) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsMatrixDirty**](#function-ismatrixdirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeDirty**](#function-isshapedirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeSupported**](#function-isshapesupported) (ShapeType type) const<br> |
|  SR\_NODISCARD bool | [**IsStatic**](#function-isstatic) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsTrigger**](#function-istrigger) () noexcept const<br> |
|   | [**Rigidbody**](#function-rigidbody) () <br> |
| virtual void | [**SetCenter**](#function-setcenter) (const SR\_MATH\_NS::FVector3 & center) <br> |
| virtual void | [**SetIsStatic**](#function-setisstatic) (bool value) <br> |
| virtual void | [**SetIsTrigger**](#function-setistrigger) (bool value) <br> |
|  void | [**SetMass**](#function-setmass) (float\_t mass) <br> |
|  void | [**SetMaterial**](#function-setmaterial-12) (const PhysicsMaterial::Ptr & pMaterial) <br> |
|  void | [**SetMaterial**](#function-setmaterial-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetMatrixDirty**](#function-setmatrixdirty) (const bool value=true) <br> |
|  void | [**SetShapeDirty**](#function-setshapedirty) (const bool value=true) <br> |
| virtual void | [**SetType**](#function-settype) (ShapeType type) <br> |
|  void | [**Synchronize**](#function-synchronize) () <br> |
|  void | [**UpdateInertia**](#function-updateinertia) () <br> |
|  bool | [**UpdateMatrix**](#function-updatematrix) (bool force=false) <br> |
|  SR\_NODISCARD RBUpdShapeRes | [**UpdateShape**](#function-updateshape) () <br> |
|   | [**~Rigidbody**](#function-rigidbody) () override<br> |


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






## Protected Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](#typedef-physicssceneptr)  <br> |
| typedef [**SR\_UTILS\_NS::Component**](classSR__UTILS__NS_1_1Component.md) | [**Super**](#typedef-super)  <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**m\_center**](#variable-m_center)  <br> |
|  [**RigidbodyImpl**](classSR__PTYPES__NS_1_1RigidbodyImpl.md) \* | [**m\_impl**](#variable-m_impl)   = `nullptr`<br> |
|  bool | [**m\_isBodyDirty**](#variable-m_isbodydirty)   = `true`<br> |
|  bool | [**m\_isMatrixDirty**](#variable-m_ismatrixdirty)   = `false`<br> |
|  bool | [**m\_isShapeDirty**](#variable-m_isshapedirty)   = `false`<br> |
|  bool | [**m\_isStatic**](#variable-m_isstatic)   = `false`<br> |
|  bool | [**m\_isTrigger**](#variable-m_istrigger)   = `false`<br> |
|  LibraryPtr | [**m\_library**](#variable-m_library)   = `nullptr`<br> |
|  float\_t | [**m\_mass**](#variable-m_mass)   = `1.f`<br> |
|  SR\_PTYPES\_NS::PhysicsMaterial::Ptr | [**m\_material**](#variable-m_material)   = `nullptr`<br> |
|  PhysicsScenePtr | [**m\_physicsScene**](#variable-m_physicsscene)  <br> |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**m\_rotation**](#variable-m_rotation)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_scale**](#variable-m_scale)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  CollisionShape::Ptr | [**m\_shape**](#variable-m_shape)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_translation**](#variable-m_translation)  <br> |


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
|  SR\_NODISCARD T \* | [**GetImpl**](#function-getimpl) () const<br> |
|  SR\_NODISCARD const PhysicsScenePtr & | [**GetPhysicsScene**](#function-getphysicsscene) () const<br> |
| virtual void | [**OnAttached**](#function-onattached) () override<br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnDestroy**](#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](#function-onenable) () override<br> |
| virtual void | [**OnMatrixDirty**](#function-onmatrixdirty) () override<br> |
|  void | [**SetShape**](#function-setshape) (const CollisionShape::Ptr & pShape) <br> |
| virtual void | [**Update**](#function-update) (float\_t dt) override<br> |
|  bool | [**UpdateShapeInternal**](#function-updateshapeinternal) () <br> |


## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |






## Detailed Description



 


    
## Public Types Documentation




### typedef Ptr 

```C++
using SR_PTYPES_NS::Rigidbody::Ptr =  SR_HTYPES_NS::SharedPtr<Rigidbody>;
```




<hr>
## Public Functions Documentation




### function ClearForces 

```C++
void SR_PTYPES_NS::Rigidbody::ClearForces () 
```




<hr>



### function ExecuteInEditMode 

```C++
inline virtual SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::ExecuteInEditMode () override const
```



Implements [*SR\_UTILS\_NS::Component::ExecuteInEditMode*](classSR__UTILS__NS_1_1Component.md#function-executeineditmode)


<hr>



### function GetCenter 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody::GetCenter () noexcept const
```




<hr>



### function GetCenterDirection 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody::GetCenterDirection () noexcept const
```




<hr>



### function GetCollisionShape 

```C++
SR_NODISCARD const CollisionShape::Ptr & SR_PTYPES_NS::Rigidbody::GetCollisionShape () noexcept const
```




<hr>



### function GetHandle 

```C++
SR_NODISCARD void * SR_PTYPES_NS::Rigidbody::GetHandle () noexcept const
```




<hr>



### function GetLibrary 

```C++
template<typename T>
inline SR_NODISCARD T * SR_PTYPES_NS::Rigidbody::GetLibrary () const
```




<hr>



### function GetMass 

```C++
SR_NODISCARD float_t SR_PTYPES_NS::Rigidbody::GetMass () noexcept const
```




<hr>



### function GetMeasurement 

```C++
virtual SR_NODISCARD SR_UTILS_NS::Measurement SR_PTYPES_NS::Rigidbody::GetMeasurement () const = 0
```




<hr>



### function GetPhysicsMaterial 

```C++
inline SR_NODISCARD PhysicsMaterial::Ptr SR_PTYPES_NS::Rigidbody::GetPhysicsMaterial () noexcept const
```




<hr>



### function GetRotation 

```C++
inline SR_NODISCARD SR_MATH_NS::Quaternion SR_PTYPES_NS::Rigidbody::GetRotation () noexcept const
```




<hr>



### function GetScale 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody::GetScale () noexcept const
```




<hr>



### function GetTranslation 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody::GetTranslation () noexcept const
```




<hr>



### function GetType 

```C++
SR_NODISCARD ShapeType SR_PTYPES_NS::Rigidbody::GetType () noexcept const
```




<hr>



### function InitBody 

```C++
bool SR_PTYPES_NS::Rigidbody::InitBody () 
```




<hr>



### function IsBodyDirty 

```C++
inline SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::IsBodyDirty () noexcept const
```




<hr>



### function IsDebugEnabled 

```C++
SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::IsDebugEnabled () noexcept const
```




<hr>



### function IsMatrixDirty 

```C++
inline SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::IsMatrixDirty () noexcept const
```




<hr>



### function IsShapeDirty 

```C++
inline SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::IsShapeDirty () noexcept const
```




<hr>



### function IsShapeSupported 

```C++
SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::IsShapeSupported (
    ShapeType type
) const
```




<hr>



### function IsStatic 

```C++
SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::IsStatic () noexcept const
```




<hr>



### function IsTrigger 

```C++
inline SR_NODISCARD bool SR_PTYPES_NS::Rigidbody::IsTrigger () noexcept const
```




<hr>



### function Rigidbody 

```C++
SR_PTYPES_NS::Rigidbody::Rigidbody () 
```




<hr>



### function SetCenter 

```C++
virtual void SR_PTYPES_NS::Rigidbody::SetCenter (
    const SR_MATH_NS::FVector3 & center
) 
```




<hr>



### function SetIsStatic 

```C++
virtual void SR_PTYPES_NS::Rigidbody::SetIsStatic (
    bool value
) 
```




<hr>



### function SetIsTrigger 

```C++
virtual void SR_PTYPES_NS::Rigidbody::SetIsTrigger (
    bool value
) 
```




<hr>



### function SetMass 

```C++
void SR_PTYPES_NS::Rigidbody::SetMass (
    float_t mass
) 
```




<hr>



### function SetMaterial [1/2]

```C++
void SR_PTYPES_NS::Rigidbody::SetMaterial (
    const PhysicsMaterial::Ptr & pMaterial
) 
```




<hr>



### function SetMaterial [2/2]

```C++
void SR_PTYPES_NS::Rigidbody::SetMaterial (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function SetMatrixDirty 

```C++
inline void SR_PTYPES_NS::Rigidbody::SetMatrixDirty (
    const bool value=true
) 
```




<hr>



### function SetShapeDirty 

```C++
inline void SR_PTYPES_NS::Rigidbody::SetShapeDirty (
    const bool value=true
) 
```




<hr>



### function SetType 

```C++
virtual void SR_PTYPES_NS::Rigidbody::SetType (
    ShapeType type
) 
```




<hr>



### function Synchronize 

```C++
void SR_PTYPES_NS::Rigidbody::Synchronize () 
```




<hr>



### function UpdateInertia 

```C++
void SR_PTYPES_NS::Rigidbody::UpdateInertia () 
```




<hr>



### function UpdateMatrix 

```C++
bool SR_PTYPES_NS::Rigidbody::UpdateMatrix (
    bool force=false
) 
```




<hr>



### function UpdateShape 

```C++
SR_NODISCARD RBUpdShapeRes SR_PTYPES_NS::Rigidbody::UpdateShape () 
```




<hr>



### function ~Rigidbody 

```C++
SR_PTYPES_NS::Rigidbody::~Rigidbody () override
```




<hr>
## Protected Types Documentation




### typedef LibraryPtr 

```C++
using SR_PTYPES_NS::Rigidbody::LibraryPtr =  SR_PHYSICS_NS::LibraryImpl*;
```




<hr>



### typedef PhysicsScenePtr 

```C++
using SR_PTYPES_NS::Rigidbody::PhysicsScenePtr =  SR_HTYPES_NS::SafePtr<PhysicsScene>;
```




<hr>



### typedef Super 

```C++
using SR_PTYPES_NS::Rigidbody::Super =  SR_UTILS_NS::Component;
```




<hr>
## Protected Attributes Documentation




### variable m\_center 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody::m_center;
```




<hr>



### variable m\_impl 

```C++
RigidbodyImpl* SR_PTYPES_NS::Rigidbody::m_impl;
```




<hr>



### variable m\_isBodyDirty 

```C++
bool SR_PTYPES_NS::Rigidbody::m_isBodyDirty;
```




<hr>



### variable m\_isMatrixDirty 

```C++
bool SR_PTYPES_NS::Rigidbody::m_isMatrixDirty;
```




<hr>



### variable m\_isShapeDirty 

```C++
bool SR_PTYPES_NS::Rigidbody::m_isShapeDirty;
```




<hr>



### variable m\_isStatic 

```C++
bool SR_PTYPES_NS::Rigidbody::m_isStatic;
```




<hr>



### variable m\_isTrigger 

```C++
bool SR_PTYPES_NS::Rigidbody::m_isTrigger;
```




<hr>



### variable m\_library 

```C++
LibraryPtr SR_PTYPES_NS::Rigidbody::m_library;
```




<hr>



### variable m\_mass 

```C++
float_t SR_PTYPES_NS::Rigidbody::m_mass;
```




<hr>



### variable m\_material 

```C++
SR_PTYPES_NS::PhysicsMaterial::Ptr SR_PTYPES_NS::Rigidbody::m_material;
```




<hr>



### variable m\_physicsScene 

```C++
PhysicsScenePtr SR_PTYPES_NS::Rigidbody::m_physicsScene;
```




<hr>



### variable m\_rotation 

```C++
SR_MATH_NS::Quaternion SR_PTYPES_NS::Rigidbody::m_rotation;
```




<hr>



### variable m\_scale 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody::m_scale;
```




<hr>



### variable m\_shape 

```C++
CollisionShape::Ptr SR_PTYPES_NS::Rigidbody::m_shape;
```




<hr>



### variable m\_translation 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody::m_translation;
```




<hr>
## Protected Functions Documentation




### function GetImpl 

```C++
template<typename T>
inline SR_NODISCARD T * SR_PTYPES_NS::Rigidbody::GetImpl () const
```




<hr>



### function GetPhysicsScene 

```C++
SR_NODISCARD const PhysicsScenePtr & SR_PTYPES_NS::Rigidbody::GetPhysicsScene () const
```




<hr>



### function OnAttached 

_Вызывается после добавления компонента к игровому объекту_ 
```C++
virtual void SR_PTYPES_NS::Rigidbody::OnAttached () override
```



Implements [*SR\_UTILS\_NS::Component::OnAttached*](classSR__UTILS__NS_1_1Component.md#function-onattached)


<hr>



### function OnDestroy 

_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._ 
```C++
virtual void SR_PTYPES_NS::Rigidbody::OnDestroy () override
```



Implements [*SR\_UTILS\_NS::Component::OnDestroy*](classSR__UTILS__NS_1_1Component.md#function-ondestroy)


<hr>



### function OnDisable 

```C++
virtual void SR_PTYPES_NS::Rigidbody::OnDisable () override
```



Implements [*SR\_UTILS\_NS::Component::OnDisable*](classSR__UTILS__NS_1_1Component.md#function-ondisable)


<hr>



### function OnEnable 

```C++
virtual void SR_PTYPES_NS::Rigidbody::OnEnable () override
```



Implements [*SR\_UTILS\_NS::Component::OnEnable*](classSR__UTILS__NS_1_1Component.md#function-onenable)


<hr>



### function OnMatrixDirty 

```C++
virtual void SR_PTYPES_NS::Rigidbody::OnMatrixDirty () override
```



Implements [*SR\_UTILS\_NS::Component::OnMatrixDirty*](classSR__UTILS__NS_1_1Component.md#function-onmatrixdirty)


<hr>



### function SetShape 

```C++
void SR_PTYPES_NS::Rigidbody::SetShape (
    const CollisionShape::Ptr & pShape
) 
```




<hr>



### function Update 

```C++
virtual void SR_PTYPES_NS::Rigidbody::Update (
    float_t dt
) override
```



Implements [*SR\_UTILS\_NS::Component::Update*](classSR__UTILS__NS_1_1Component.md#function-update)


<hr>



### function UpdateShapeInternal 

```C++
bool SR_PTYPES_NS::Rigidbody::UpdateShapeInternal () 
```




<hr>## Friends Documentation





### friend PhysicsScene 

```C++
class SR_PTYPES_NS::Rigidbody::PhysicsScene (
    SR_PHYSICS_NS::PhysicsScene
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/Rigidbody.h`

