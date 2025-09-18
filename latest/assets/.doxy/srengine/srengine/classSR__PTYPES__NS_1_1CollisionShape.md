

# Class SR\_PTYPES\_NS::CollisionShape



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md)








Inherits the following classes: [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md),  [SR\_HTYPES\_NS::IRawMeshHolder](classSR__HTYPES__NS_1_1IRawMeshHolder.md)


Inherited by the following classes: [SR\_PTYPES\_NS::Bullet3CollisionShape](classSR__PTYPES__NS_1_1Bullet3CollisionShape.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](#typedef-physicssceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) &gt; | [**GameObjectPtr**](classSR__UTILS__NS_1_1Component.md#typedef-gameobjectptr)  <br> |
| typedef [**Component**](classSR__UTILS__NS_1_1Component.md) | [**OriginType**](classSR__UTILS__NS_1_1Component.md#typedef-origintype)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Component**](classSR__UTILS__NS_1_1Component.md) &gt; | [**Ptr**](classSR__UTILS__NS_1_1Component.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**SceneObjectPtr**](classSR__UTILS__NS_1_1Component.md#typedef-sceneobjectptr)  <br> |
| typedef [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**ScenePtr**](classSR__UTILS__NS_1_1Component.md#typedef-sceneptr)  <br> |


## Public Types inherited from SR_HTYPES_NS::IRawMeshHolder

See [SR\_HTYPES\_NS::IRawMeshHolder](classSR__HTYPES__NS_1_1IRawMeshHolder.md)

| Type | Name |
| ---: | :--- |
| typedef int32\_t | [**MeshIndex**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#typedef-meshindex)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) &gt; | [**RawMeshPtr**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#typedef-rawmeshptr)  <br> |
























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](#function-calculatelocalinertia) (float\_t mass) const<br> |
| virtual bool | [**ExecuteInEditMode**](#function-executeineditmode) () override const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetBounds**](#function-getbounds) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenter**](#function-getcenter) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenterDirection**](#function-getcenterdirection) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetHeight**](#function-getheight) () const<br> |
|  SR\_NODISCARD PhysicsMaterial::Ptr | [**GetPhysicsMaterial**](#function-getphysicsmaterial) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetPlaneSize**](#function-getplanesize) () const<br> |
|  SR\_NODISCARD float\_t | [**GetRadius**](#function-getradius) () const<br> |
|  SR\_NODISCARD [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**GetRigidbody**](#function-getrigidbody) () const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & | [**GetRotation**](#function-getrotation) () noexcept const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector3 & | [**GetScale**](#function-getscale) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetSize**](#function-getsize) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector3 & | [**GetTranslation**](#function-gettranslation) () noexcept const<br> |
|  SR\_NODISCARD ShapeType | [**GetType**](#function-gettype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasGeometry**](#function-hasgeometry) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeValid**](#function-isshapevalid) () noexcept const<br> |
| virtual void | [**OnDetached**](#function-ondetached) () override<br>_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._  |
| virtual void | [**OnDisable**](#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](#function-onenable) () override<br> |
| virtual void | [**OnMatrixDirty**](#function-onmatrixdirty) () override<br> |
| virtual void | [**OnRawMeshChanged**](#function-onrawmeshchanged) () override<br> |
|  void | [**OnRigidbodyDetached**](#function-onrigidbodydetached) () <br> |
|  void | [**RemoveDebugShape**](#function-removedebugshape) () <br> |
|  void | [**SetBounds**](#function-setbounds) (const SR\_MATH\_NS::FVector3 & bounds) <br> |
| virtual void | [**SetCenter**](#function-setcenter) (const SR\_MATH\_NS::FVector3 & center) <br> |
|  void | [**SetHeight**](#function-setheight) (float\_t height) <br> |
|  void | [**SetPlaneSize**](#function-setplanesize) (const SR\_MATH\_NS::FVector2 & size) <br> |
|  void | [**SetRadius**](#function-setradius) (float\_t radius) <br> |
|  void | [**SetRigidbody**](#function-setrigidbody) ([**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* pRigidbody) <br> |
|  void | [**SetSize**](#function-setsize) (const SR\_MATH\_NS::FVector3 & size) <br> |
|  void | [**SetType**](#function-settype) (ShapeType type) <br> |
| virtual void | [**Update**](#function-update) (float\_t dt) override<br> |
|  void | [**UpdateDebugShape**](#function-updatedebugshape) () <br> |
|  bool | [**UpdateMatrix**](#function-updatematrix) () <br> |
|  bool | [**UpdateShape**](#function-updateshape) () <br> |
|   | [**~CollisionShape**](#function-collisionshape) () override<br> |


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


## Public Functions inherited from SR_HTYPES_NS::IRawMeshHolder

See [SR\_HTYPES\_NS::IRawMeshHolder](classSR__HTYPES__NS_1_1IRawMeshHolder.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string\_view | [**GetGeometryName**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getgeometryname) () noexcept const<br> |
|  SR\_NODISCARD MeshIndex | [**GetMeshId**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getmeshid) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**GetMeshPath**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getmeshpath) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**GetMeshStringPath**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getmeshstringpath) () noexcept const<br> |
|  SR\_NODISCARD const RawMeshPtr & | [**GetRawMesh**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getrawmesh) () noexcept const<br> |
|  SR\_NODISCARD std::vector&lt; [**SR\_UTILS\_NS::Vertex**](structSR__UTILS__NS_1_1Vertex.md) &gt; | [**GetVertices**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-getvertices) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsValidMeshId**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-isvalidmeshid) () noexcept const<br> |
| virtual void | [**OnRawMeshChanged**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-onrawmeshchanged) () <br> |
|  void | [**SetMeshId**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-setmeshid) (MeshIndex meshIndex, bool forceReload=false) <br> |
|  void | [**SetRawMesh**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-setrawmesh-12) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetRawMesh**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-setrawmesh-22) (RawMeshPtr pRawMesh) <br> |
| virtual  | [**~IRawMeshHolder**](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-irawmeshholder) () <br> |




















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**m\_bounds**](#variable-m_bounds)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_center**](#variable-m_center)  <br> |
|  [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**m\_currentRigidbody**](#variable-m_currentrigidbody)   = `nullptr`<br> |
|  uint64\_t | [**m\_debugId**](#variable-m_debugid)   = `SR\_ID\_INVALID`<br> |
|  [**CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md) \* | [**m\_impl**](#variable-m_impl)   = `nullptr`<br> |
|  bool | [**m\_isShapeDirty**](#variable-m_isshapedirty)   = `true`<br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**m\_material**](#variable-m_material)  <br> |
|  SR\_PTYPES\_NS::PhysicsMaterial::Ptr | [**m\_materialData**](#variable-m_materialdata)  <br> |
|  [**SR\_UTILS\_NS::EntityRef**](classSR__UTILS__NS_1_1EntityRef.md)&lt; [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) &gt; | [**m\_rigidbody**](#variable-m_rigidbody)  <br> |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**m\_rotation**](#variable-m_rotation)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_scale**](#variable-m_scale)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_translation**](#variable-m_translation)  <br>_decomposed matrix_  |
|  ShapeType | [**m\_type**](#variable-m_type)   = `ShapeType::Unknown`<br> |


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
















































## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |










## Public Types Documentation




### typedef LibraryPtr 

```C++
using SR_PTYPES_NS::CollisionShape::LibraryPtr =  SR_PHYSICS_NS::LibraryImpl*;
```




<hr>



### typedef PhysicsScenePtr 

```C++
using SR_PTYPES_NS::CollisionShape::PhysicsScenePtr =  SR_HTYPES_NS::SafePtr<PhysicsScene>;
```




<hr>



### typedef Ptr 

```C++
using SR_PTYPES_NS::CollisionShape::Ptr =  SR_HTYPES_NS::SharedPtr<CollisionShape>;
```




<hr>
## Public Functions Documentation




### function CalculateLocalInertia 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::CalculateLocalInertia (
    float_t mass
) const
```




<hr>



### function ExecuteInEditMode 

```C++
inline virtual bool SR_PTYPES_NS::CollisionShape::ExecuteInEditMode () override const
```



Implements [*SR\_UTILS\_NS::Component::ExecuteInEditMode*](classSR__UTILS__NS_1_1Component.md#function-executeineditmode)


<hr>



### function GetBounds 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::GetBounds () const
```




<hr>



### function GetCenter 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::GetCenter () noexcept const
```




<hr>



### function GetCenterDirection 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::GetCenterDirection () noexcept const
```




<hr>



### function GetHandle 

```C++
SR_NODISCARD void * SR_PTYPES_NS::CollisionShape::GetHandle () noexcept const
```




<hr>



### function GetHeight 

```C++
SR_NODISCARD float_t SR_PTYPES_NS::CollisionShape::GetHeight () const
```




<hr>



### function GetPhysicsMaterial 

```C++
inline SR_NODISCARD PhysicsMaterial::Ptr SR_PTYPES_NS::CollisionShape::GetPhysicsMaterial () noexcept const
```




<hr>



### function GetPlaneSize 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector2 SR_PTYPES_NS::CollisionShape::GetPlaneSize () const
```




<hr>



### function GetRadius 

```C++
SR_NODISCARD float_t SR_PTYPES_NS::CollisionShape::GetRadius () const
```




<hr>



### function GetRigidbody 

```C++
SR_NODISCARD Rigidbody * SR_PTYPES_NS::CollisionShape::GetRigidbody () const
```




<hr>



### function GetRotation 

```C++
inline SR_NODISCARD const SR_MATH_NS::Quaternion & SR_PTYPES_NS::CollisionShape::GetRotation () noexcept const
```




<hr>



### function GetScale 

```C++
inline SR_NODISCARD const SR_MATH_NS::FVector3 & SR_PTYPES_NS::CollisionShape::GetScale () noexcept const
```




<hr>



### function GetSize 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::GetSize () const
```




<hr>



### function GetTranslation 

```C++
inline SR_NODISCARD const SR_MATH_NS::FVector3 & SR_PTYPES_NS::CollisionShape::GetTranslation () noexcept const
```




<hr>



### function GetType 

```C++
SR_NODISCARD ShapeType SR_PTYPES_NS::CollisionShape::GetType () noexcept const
```




<hr>



### function HasGeometry 

```C++
SR_NODISCARD bool SR_PTYPES_NS::CollisionShape::HasGeometry () noexcept const
```




<hr>



### function IsShapeValid 

```C++
SR_NODISCARD bool SR_PTYPES_NS::CollisionShape::IsShapeValid () noexcept const
```




<hr>



### function OnDetached 

_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._ 
```C++
virtual void SR_PTYPES_NS::CollisionShape::OnDetached () override
```



Implements [*SR\_UTILS\_NS::Component::OnDetached*](classSR__UTILS__NS_1_1Component.md#function-ondetached)


<hr>



### function OnDisable 

```C++
virtual void SR_PTYPES_NS::CollisionShape::OnDisable () override
```



Implements [*SR\_UTILS\_NS::Component::OnDisable*](classSR__UTILS__NS_1_1Component.md#function-ondisable)


<hr>



### function OnEnable 

```C++
virtual void SR_PTYPES_NS::CollisionShape::OnEnable () override
```



Implements [*SR\_UTILS\_NS::Component::OnEnable*](classSR__UTILS__NS_1_1Component.md#function-onenable)


<hr>



### function OnMatrixDirty 

```C++
virtual void SR_PTYPES_NS::CollisionShape::OnMatrixDirty () override
```



Implements [*SR\_UTILS\_NS::Component::OnMatrixDirty*](classSR__UTILS__NS_1_1Component.md#function-onmatrixdirty)


<hr>



### function OnRawMeshChanged 

```C++
virtual void SR_PTYPES_NS::CollisionShape::OnRawMeshChanged () override
```



Implements [*SR\_HTYPES\_NS::IRawMeshHolder::OnRawMeshChanged*](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-onrawmeshchanged)


<hr>



### function OnRigidbodyDetached 

```C++
void SR_PTYPES_NS::CollisionShape::OnRigidbodyDetached () 
```




<hr>



### function RemoveDebugShape 

```C++
void SR_PTYPES_NS::CollisionShape::RemoveDebugShape () 
```




<hr>



### function SetBounds 

```C++
void SR_PTYPES_NS::CollisionShape::SetBounds (
    const SR_MATH_NS::FVector3 & bounds
) 
```




<hr>



### function SetCenter 

```C++
virtual void SR_PTYPES_NS::CollisionShape::SetCenter (
    const SR_MATH_NS::FVector3 & center
) 
```




<hr>



### function SetHeight 

```C++
void SR_PTYPES_NS::CollisionShape::SetHeight (
    float_t height
) 
```




<hr>



### function SetPlaneSize 

```C++
void SR_PTYPES_NS::CollisionShape::SetPlaneSize (
    const SR_MATH_NS::FVector2 & size
) 
```




<hr>



### function SetRadius 

```C++
void SR_PTYPES_NS::CollisionShape::SetRadius (
    float_t radius
) 
```




<hr>



### function SetRigidbody 

```C++
void SR_PTYPES_NS::CollisionShape::SetRigidbody (
    Rigidbody * pRigidbody
) 
```




<hr>



### function SetSize 

```C++
void SR_PTYPES_NS::CollisionShape::SetSize (
    const SR_MATH_NS::FVector3 & size
) 
```




<hr>



### function SetType 

```C++
void SR_PTYPES_NS::CollisionShape::SetType (
    ShapeType type
) 
```




<hr>



### function Update 

```C++
virtual void SR_PTYPES_NS::CollisionShape::Update (
    float_t dt
) override
```



Implements [*SR\_UTILS\_NS::Component::Update*](classSR__UTILS__NS_1_1Component.md#function-update)


<hr>



### function UpdateDebugShape 

```C++
void SR_PTYPES_NS::CollisionShape::UpdateDebugShape () 
```




<hr>



### function UpdateMatrix 

```C++
bool SR_PTYPES_NS::CollisionShape::UpdateMatrix () 
```




<hr>



### function UpdateShape 

```C++
bool SR_PTYPES_NS::CollisionShape::UpdateShape () 
```




<hr>



### function ~CollisionShape 

```C++
SR_PTYPES_NS::CollisionShape::~CollisionShape () override
```




<hr>
## Protected Attributes Documentation




### variable m\_bounds 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::m_bounds;
```




<hr>



### variable m\_center 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::m_center;
```




<hr>



### variable m\_currentRigidbody 

```C++
Rigidbody* SR_PTYPES_NS::CollisionShape::m_currentRigidbody;
```




<hr>



### variable m\_debugId 

```C++
uint64_t SR_PTYPES_NS::CollisionShape::m_debugId;
```




<hr>



### variable m\_impl 

```C++
CollisionShapeImpl* SR_PTYPES_NS::CollisionShape::m_impl;
```




<hr>



### variable m\_isShapeDirty 

```C++
bool SR_PTYPES_NS::CollisionShape::m_isShapeDirty;
```




<hr>



### variable m\_material 

```C++
SR_UTILS_NS::Path SR_PTYPES_NS::CollisionShape::m_material;
```




<hr>



### variable m\_materialData 

```C++
SR_PTYPES_NS::PhysicsMaterial::Ptr SR_PTYPES_NS::CollisionShape::m_materialData;
```




<hr>



### variable m\_rigidbody 

```C++
SR_UTILS_NS::EntityRef<Rigidbody> SR_PTYPES_NS::CollisionShape::m_rigidbody;
```




<hr>



### variable m\_rotation 

```C++
SR_MATH_NS::Quaternion SR_PTYPES_NS::CollisionShape::m_rotation;
```




<hr>



### variable m\_scale 

```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::m_scale;
```




<hr>



### variable m\_translation 

_decomposed matrix_ 
```C++
SR_MATH_NS::FVector3 SR_PTYPES_NS::CollisionShape::m_translation;
```




<hr>



### variable m\_type 

```C++
ShapeType SR_PTYPES_NS::CollisionShape::m_type;
```




<hr>## Friends Documentation





### friend PhysicsScene 

```C++
class SR_PTYPES_NS::CollisionShape::PhysicsScene (
    SR_PHYSICS_NS::PhysicsScene
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/CollisionShape.h`

