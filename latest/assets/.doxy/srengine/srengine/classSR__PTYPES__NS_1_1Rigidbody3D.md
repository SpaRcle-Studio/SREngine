

# Class SR\_PTYPES\_NS::Rigidbody3D



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**Rigidbody3D**](classSR__PTYPES__NS_1_1Rigidbody3D.md)








Inherits the following classes: [SR\_PTYPES\_NS::Rigidbody](classSR__PTYPES__NS_1_1Rigidbody.md)


Inherited by the following classes: [SR\_PTYPES\_NS::Bullet3Rigidbody3D](classSR__PTYPES__NS_1_1Bullet3Rigidbody3D.md)














## Public Types inherited from SR_PTYPES_NS::Rigidbody

See [SR\_PTYPES\_NS::Rigidbody](classSR__PTYPES__NS_1_1Rigidbody.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) &gt; | [**Ptr**](classSR__PTYPES__NS_1_1Rigidbody.md#typedef-ptr)  <br> |


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
|  void | [**AddAngularVelocity**](#function-addangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
|  void | [**AddLinearVelocity**](#function-addlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
|  SR\_NODISCARD SR\_MATH\_NS::BVector3 | [**GetAngularLock**](#function-getangularlock) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetAngularVelocity**](#function-getangularvelocity) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::BVector3 | [**GetLinearLock**](#function-getlinearlock) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetLinearVelocity**](#function-getlinearvelocity) () const<br> |
| virtual SR\_NODISCARD SR\_UTILS\_NS::Measurement | [**GetMeasurement**](#function-getmeasurement) () override const<br> |
|  void | [**SetAngularLock**](#function-setangularlock) (const SR\_MATH\_NS::BVector3 & lock) <br> |
|  void | [**SetAngularVelocity**](#function-setangularvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |
|  void | [**SetLinearLock**](#function-setlinearlock) (const SR\_MATH\_NS::BVector3 & lock) <br> |
|  void | [**SetLinearVelocity**](#function-setlinearvelocity) (const SR\_MATH\_NS::FVector3 & velocity) <br> |


## Public Functions inherited from SR_PTYPES_NS::Rigidbody

See [SR\_PTYPES\_NS::Rigidbody](classSR__PTYPES__NS_1_1Rigidbody.md)

| Type | Name |
| ---: | :--- |
|  void | [**ClearForces**](classSR__PTYPES__NS_1_1Rigidbody.md#function-clearforces) () <br> |
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](classSR__PTYPES__NS_1_1Rigidbody.md#function-executeineditmode) () override const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenter**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getcenter) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenterDirection**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getcenterdirection) () noexcept const<br> |
|  SR\_NODISCARD const CollisionShape::Ptr & | [**GetCollisionShape**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getcollisionshape) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](classSR__PTYPES__NS_1_1Rigidbody.md#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD T \* | [**GetLibrary**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getlibrary) () const<br> |
|  SR\_NODISCARD float\_t | [**GetMass**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getmass) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_UTILS\_NS::Measurement | [**GetMeasurement**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getmeasurement) () const = 0<br> |
|  SR\_NODISCARD [**PhysicsMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterial.md) \* | [**GetPhysicsMaterial**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getphysicsmaterial) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**GetRotation**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getrotation) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetScale**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getscale) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetTranslation**](classSR__PTYPES__NS_1_1Rigidbody.md#function-gettranslation) () noexcept const<br> |
|  SR\_NODISCARD ShapeType | [**GetType**](classSR__PTYPES__NS_1_1Rigidbody.md#function-gettype) () noexcept const<br> |
|  bool | [**InitBody**](classSR__PTYPES__NS_1_1Rigidbody.md#function-initbody) () <br> |
|  SR\_NODISCARD bool | [**IsBodyDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#function-isbodydirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDebugEnabled**](classSR__PTYPES__NS_1_1Rigidbody.md#function-isdebugenabled) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsMatrixDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#function-ismatrixdirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#function-isshapedirty) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeSupported**](classSR__PTYPES__NS_1_1Rigidbody.md#function-isshapesupported) (ShapeType type) const<br> |
|  SR\_NODISCARD bool | [**IsStatic**](classSR__PTYPES__NS_1_1Rigidbody.md#function-isstatic) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsTrigger**](classSR__PTYPES__NS_1_1Rigidbody.md#function-istrigger) () noexcept const<br> |
|   | [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md#function-rigidbody) () <br> |
| virtual void | [**SetCenter**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setcenter) (const SR\_MATH\_NS::FVector3 & center) <br> |
| virtual void | [**SetIsStatic**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setisstatic) (bool value) <br> |
| virtual void | [**SetIsTrigger**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setistrigger) (bool value) <br> |
|  void | [**SetMass**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setmass) (float\_t mass) <br> |
|  void | [**SetMaterial**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setmaterial-12) ([**PhysicsMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterial.md) \* pMaterial) <br> |
|  void | [**SetMaterial**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setmaterial-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetMatrixDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setmatrixdirty) (const bool value=true) <br> |
|  void | [**SetShapeDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setshapedirty) (const bool value=true) <br> |
| virtual void | [**SetType**](classSR__PTYPES__NS_1_1Rigidbody.md#function-settype) (ShapeType type) <br> |
|  void | [**Synchronize**](classSR__PTYPES__NS_1_1Rigidbody.md#function-synchronize) () <br> |
|  void | [**UpdateInertia**](classSR__PTYPES__NS_1_1Rigidbody.md#function-updateinertia) () <br> |
|  bool | [**UpdateMatrix**](classSR__PTYPES__NS_1_1Rigidbody.md#function-updatematrix) (bool force=false) <br> |
|  SR\_NODISCARD RBUpdShapeRes | [**UpdateShape**](classSR__PTYPES__NS_1_1Rigidbody.md#function-updateshape) () <br> |
|   | [**~Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md#function-rigidbody) () override<br> |


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










## Protected Types inherited from SR_PTYPES_NS::Rigidbody

See [SR\_PTYPES\_NS::Rigidbody](classSR__PTYPES__NS_1_1Rigidbody.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](classSR__PTYPES__NS_1_1Rigidbody.md#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](classSR__PTYPES__NS_1_1Rigidbody.md#typedef-physicssceneptr)  <br> |
| typedef [**SR\_UTILS\_NS::Component**](classSR__UTILS__NS_1_1Component.md) | [**Super**](classSR__PTYPES__NS_1_1Rigidbody.md#typedef-super)  <br> |










## Protected Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::BVector3 | [**m\_angularLock**](#variable-m_angularlock)  <br> |
|  SR\_MATH\_NS::BVector3 | [**m\_linearLock**](#variable-m_linearlock)  <br> |


## Protected Attributes inherited from SR_PTYPES_NS::Rigidbody

See [SR\_PTYPES\_NS::Rigidbody](classSR__PTYPES__NS_1_1Rigidbody.md)

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**m\_center**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_center)  <br> |
|  [**RigidbodyImpl**](classSR__PTYPES__NS_1_1RigidbodyImpl.md) \* | [**m\_impl**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_impl)   = `nullptr`<br> |
|  bool | [**m\_isBodyDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_isbodydirty)   = `true`<br> |
|  bool | [**m\_isMatrixDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_ismatrixdirty)   = `false`<br> |
|  bool | [**m\_isShapeDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_isshapedirty)   = `false`<br> |
|  bool | [**m\_isStatic**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_isstatic)   = `false`<br> |
|  bool | [**m\_isTrigger**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_istrigger)   = `false`<br> |
|  LibraryPtr | [**m\_library**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_library)   = `nullptr`<br> |
|  float\_t | [**m\_mass**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_mass)   = `1.f`<br> |
|  [**SR\_PTYPES\_NS::PhysicsMaterial**](classSR__PTYPES__NS_1_1PhysicsMaterial.md) \* | [**m\_material**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_material)   = `nullptr`<br> |
|  PhysicsScenePtr | [**m\_physicsScene**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_physicsscene)  <br> |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**m\_rotation**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_rotation)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_scale**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_scale)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  CollisionShape::Ptr | [**m\_shape**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_shape)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_translation**](classSR__PTYPES__NS_1_1Rigidbody.md#variable-m_translation)  <br> |


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














































## Protected Functions inherited from SR_PTYPES_NS::Rigidbody

See [SR\_PTYPES\_NS::Rigidbody](classSR__PTYPES__NS_1_1Rigidbody.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD T \* | [**GetImpl**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getimpl) () const<br> |
|  SR\_NODISCARD const PhysicsScenePtr & | [**GetPhysicsScene**](classSR__PTYPES__NS_1_1Rigidbody.md#function-getphysicsscene) () const<br> |
| virtual void | [**OnAttached**](classSR__PTYPES__NS_1_1Rigidbody.md#function-onattached) () override<br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnDestroy**](classSR__PTYPES__NS_1_1Rigidbody.md#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](classSR__PTYPES__NS_1_1Rigidbody.md#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](classSR__PTYPES__NS_1_1Rigidbody.md#function-onenable) () override<br> |
| virtual void | [**OnMatrixDirty**](classSR__PTYPES__NS_1_1Rigidbody.md#function-onmatrixdirty) () override<br> |
|  void | [**SetShape**](classSR__PTYPES__NS_1_1Rigidbody.md#function-setshape) (const CollisionShape::Ptr & pShape) <br> |
| virtual void | [**Update**](classSR__PTYPES__NS_1_1Rigidbody.md#function-update) (float\_t dt) override<br> |
|  bool | [**UpdateShapeInternal**](classSR__PTYPES__NS_1_1Rigidbody.md#function-updateshapeinternal) () <br> |


## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |








## Public Functions Documentation




### function AddAngularVelocity 

```C++
void SR_PTYPES_NS::Rigidbody3D::AddAngularVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>



### function AddLinearVelocity 

```C++
void SR_PTYPES_NS::Rigidbody3D::AddLinearVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>



### function GetAngularLock 

```C++
inline SR_NODISCARD SR_MATH_NS::BVector3 SR_PTYPES_NS::Rigidbody3D::GetAngularLock () noexcept const
```




<hr>



### function GetAngularVelocity 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody3D::GetAngularVelocity () const
```




<hr>



### function GetLinearLock 

```C++
inline SR_NODISCARD SR_MATH_NS::BVector3 SR_PTYPES_NS::Rigidbody3D::GetLinearLock () noexcept const
```




<hr>



### function GetLinearVelocity 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Rigidbody3D::GetLinearVelocity () const
```




<hr>



### function GetMeasurement 

```C++
virtual SR_NODISCARD SR_UTILS_NS::Measurement SR_PTYPES_NS::Rigidbody3D::GetMeasurement () override const
```



Implements [*SR\_PTYPES\_NS::Rigidbody::GetMeasurement*](classSR__PTYPES__NS_1_1Rigidbody.md#function-getmeasurement)


<hr>



### function SetAngularLock 

```C++
void SR_PTYPES_NS::Rigidbody3D::SetAngularLock (
    const SR_MATH_NS::BVector3 & lock
) 
```




<hr>



### function SetAngularVelocity 

```C++
void SR_PTYPES_NS::Rigidbody3D::SetAngularVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>



### function SetLinearLock 

```C++
void SR_PTYPES_NS::Rigidbody3D::SetLinearLock (
    const SR_MATH_NS::BVector3 & lock
) 
```




<hr>



### function SetLinearVelocity 

```C++
void SR_PTYPES_NS::Rigidbody3D::SetLinearVelocity (
    const SR_MATH_NS::FVector3 & velocity
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_angularLock 

```C++
SR_MATH_NS::BVector3 SR_PTYPES_NS::Rigidbody3D::m_angularLock;
```




<hr>



### variable m\_linearLock 

```C++
SR_MATH_NS::BVector3 SR_PTYPES_NS::Rigidbody3D::m_linearLock;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Physics/inc/Physics/3D/Rigidbody3D.h`

