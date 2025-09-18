

# Class SR\_PTYPES\_NS::Bullet3CollisionShape



[**ClassList**](annotated.md) **>** [**SR\_PTYPES\_NS**](namespaceSR__PTYPES__NS.md) **>** [**Bullet3CollisionShape**](classSR__PTYPES__NS_1_1Bullet3CollisionShape.md)








Inherits the following classes: [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)
















## Public Types inherited from SR_PTYPES_NS::CollisionShape

See [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_PHYSICS\_NS::LibraryImpl**](classSR__PHYSICS__NS_1_1LibraryImpl.md) \* | [**LibraryPtr**](classSR__PTYPES__NS_1_1CollisionShape.md#typedef-libraryptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; PhysicsScene &gt; | [**PhysicsScenePtr**](classSR__PTYPES__NS_1_1CollisionShape.md#typedef-physicssceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md) &gt; | [**Ptr**](classSR__PTYPES__NS_1_1CollisionShape.md#typedef-ptr)  <br> |


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
|   | [**Bullet3CollisionShape**](#function-bullet3collisionshape) (LibraryPtr pLibrary) <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](#function-calculatelocalinertia) (float\_t mass) override const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () noexcept override const<br> |
|  bool | [**UpdateMatrix**](#function-updatematrix) () override<br> |
|  bool | [**UpdateShape**](#function-updateshape) () override<br> |
|   | [**~Bullet3CollisionShape**](#function-bullet3collisionshape) () override<br> |


## Public Functions inherited from SR_PTYPES_NS::CollisionShape

See [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**CalculateLocalInertia**](classSR__PTYPES__NS_1_1CollisionShape.md#function-calculatelocalinertia) (float\_t mass) const<br> |
| virtual bool | [**ExecuteInEditMode**](classSR__PTYPES__NS_1_1CollisionShape.md#function-executeineditmode) () override const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetBounds**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getbounds) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenter**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getcenter) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCenterDirection**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getcenterdirection) () noexcept const<br> |
|  SR\_NODISCARD void \* | [**GetHandle**](classSR__PTYPES__NS_1_1CollisionShape.md#function-gethandle) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetHeight**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getheight) () const<br> |
|  SR\_NODISCARD PhysicsMaterial::Ptr | [**GetPhysicsMaterial**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getphysicsmaterial) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetPlaneSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getplanesize) () const<br> |
|  SR\_NODISCARD float\_t | [**GetRadius**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getradius) () const<br> |
|  SR\_NODISCARD [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**GetRigidbody**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getrigidbody) () const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & | [**GetRotation**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getrotation) () noexcept const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector3 & | [**GetScale**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getscale) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-getsize) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector3 & | [**GetTranslation**](classSR__PTYPES__NS_1_1CollisionShape.md#function-gettranslation) () noexcept const<br> |
|  SR\_NODISCARD ShapeType | [**GetType**](classSR__PTYPES__NS_1_1CollisionShape.md#function-gettype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasGeometry**](classSR__PTYPES__NS_1_1CollisionShape.md#function-hasgeometry) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsShapeValid**](classSR__PTYPES__NS_1_1CollisionShape.md#function-isshapevalid) () noexcept const<br> |
| virtual void | [**OnDetached**](classSR__PTYPES__NS_1_1CollisionShape.md#function-ondetached) () override<br>_Вызывается когда компонент убирается с объекта, но до OnDestroy и только если был OnAttached._  |
| virtual void | [**OnDisable**](classSR__PTYPES__NS_1_1CollisionShape.md#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](classSR__PTYPES__NS_1_1CollisionShape.md#function-onenable) () override<br> |
| virtual void | [**OnMatrixDirty**](classSR__PTYPES__NS_1_1CollisionShape.md#function-onmatrixdirty) () override<br> |
| virtual void | [**OnRawMeshChanged**](classSR__PTYPES__NS_1_1CollisionShape.md#function-onrawmeshchanged) () override<br> |
|  void | [**OnRigidbodyDetached**](classSR__PTYPES__NS_1_1CollisionShape.md#function-onrigidbodydetached) () <br> |
|  void | [**RemoveDebugShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-removedebugshape) () <br> |
|  void | [**SetBounds**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setbounds) (const SR\_MATH\_NS::FVector3 & bounds) <br> |
| virtual void | [**SetCenter**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setcenter) (const SR\_MATH\_NS::FVector3 & center) <br> |
|  void | [**SetHeight**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setheight) (float\_t height) <br> |
|  void | [**SetPlaneSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setplanesize) (const SR\_MATH\_NS::FVector2 & size) <br> |
|  void | [**SetRadius**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setradius) (float\_t radius) <br> |
|  void | [**SetRigidbody**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setrigidbody) ([**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* pRigidbody) <br> |
|  void | [**SetSize**](classSR__PTYPES__NS_1_1CollisionShape.md#function-setsize) (const SR\_MATH\_NS::FVector3 & size) <br> |
|  void | [**SetType**](classSR__PTYPES__NS_1_1CollisionShape.md#function-settype) (ShapeType type) <br> |
| virtual void | [**Update**](classSR__PTYPES__NS_1_1CollisionShape.md#function-update) (float\_t dt) override<br> |
|  void | [**UpdateDebugShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-updatedebugshape) () <br> |
|  bool | [**UpdateMatrix**](classSR__PTYPES__NS_1_1CollisionShape.md#function-updatematrix) () <br> |
|  bool | [**UpdateShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-updateshape) () <br> |
|   | [**~CollisionShape**](classSR__PTYPES__NS_1_1CollisionShape.md#function-collisionshape) () override<br> |


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




























## Protected Attributes inherited from SR_PTYPES_NS::CollisionShape

See [SR\_PTYPES\_NS::CollisionShape](classSR__PTYPES__NS_1_1CollisionShape.md)

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FVector3 | [**m\_bounds**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_bounds)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_center**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_center)  <br> |
|  [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) \* | [**m\_currentRigidbody**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_currentrigidbody)   = `nullptr`<br> |
|  uint64\_t | [**m\_debugId**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_debugid)   = `SR\_ID\_INVALID`<br> |
|  [**CollisionShapeImpl**](classSR__PTYPES__NS_1_1CollisionShapeImpl.md) \* | [**m\_impl**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_impl)   = `nullptr`<br> |
|  bool | [**m\_isShapeDirty**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_isshapedirty)   = `true`<br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**m\_material**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_material)  <br> |
|  SR\_PTYPES\_NS::PhysicsMaterial::Ptr | [**m\_materialData**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_materialdata)  <br> |
|  [**SR\_UTILS\_NS::EntityRef**](classSR__UTILS__NS_1_1EntityRef.md)&lt; [**Rigidbody**](classSR__PTYPES__NS_1_1Rigidbody.md) &gt; | [**m\_rigidbody**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_rigidbody)  <br> |
|  [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) | [**m\_rotation**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_rotation)  <br> |
|  SR\_MATH\_NS::FVector3 | [**m\_scale**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_scale)   = `SR\_MATH\_NS::FVector3::One()`<br> |
|  SR\_MATH\_NS::FVector3 | [**m\_translation**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_translation)  <br>_decomposed matrix_  |
|  ShapeType | [**m\_type**](classSR__PTYPES__NS_1_1CollisionShape.md#variable-m_type)   = `ShapeType::Unknown`<br> |


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












## Public Functions Documentation




### function Bullet3CollisionShape 

```C++
SR_PTYPES_NS::Bullet3CollisionShape::Bullet3CollisionShape (
    LibraryPtr pLibrary
) 
```




<hr>



### function CalculateLocalInertia 

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_PTYPES_NS::Bullet3CollisionShape::CalculateLocalInertia (
    float_t mass
) override const
```




<hr>



### function GetHandle 

```C++
inline SR_NODISCARD void * SR_PTYPES_NS::Bullet3CollisionShape::GetHandle () noexcept override const
```




<hr>



### function UpdateMatrix 

```C++
bool SR_PTYPES_NS::Bullet3CollisionShape::UpdateMatrix () override
```




<hr>



### function UpdateShape 

```C++
bool SR_PTYPES_NS::Bullet3CollisionShape::UpdateShape () override
```




<hr>



### function ~Bullet3CollisionShape 

```C++
SR_PTYPES_NS::Bullet3CollisionShape::~Bullet3CollisionShape () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Physics/inc/Physics/Bullet3/Bullet3CollisionShape.h`

