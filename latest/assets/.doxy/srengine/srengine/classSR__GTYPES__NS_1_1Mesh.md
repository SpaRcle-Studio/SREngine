

# Class SR\_GTYPES\_NS::Mesh



[**ClassList**](annotated.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) **>** [**Mesh**](classSR__GTYPES__NS_1_1Mesh.md)








Inherits the following classes: [SR\_GTYPES\_NS::IRenderComponent](classSR__GTYPES__NS_1_1IRenderComponent.md),  Memory::IGraphicsResource


Inherited by the following classes: [SR\_GTYPES\_NS::DebugLine](classSR__GTYPES__NS_1_1DebugLine.md),  [SR\_GTYPES\_NS::IndexedMesh](classSR__GTYPES__NS_1_1IndexedMesh.md),  [SR\_GTYPES\_NS::Sprite](classSR__GTYPES__NS_1_1Sprite.md),  [SR\_GTYPES\_NS::Text](classSR__GTYPES__NS_1_1Text.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; BaseMaterial &gt; | [**MaterialPtr**](#typedef-materialptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Mesh**](classSR__GTYPES__NS_1_1Mesh.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SortedVector**](classSR__HTYPES__NS_1_1SortedVector.md)&lt; [**SR\_GRAPH\_NS::RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md), [**SR\_GRAPH\_NS::RenderQueuePredicate**](structSR__GRAPH__NS_1_1RenderQueuePredicate.md) &gt; | [**RenderQueues**](#typedef-renderqueues)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; RenderScene &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |
| typedef [**Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](#typedef-shaderptr)  <br> |


## Public Types inherited from SR_GTYPES_NS::IRenderComponent

See [SR\_GTYPES\_NS::IRenderComponent](classSR__GTYPES__NS_1_1IRenderComponent.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Camera**](classSR__GTYPES__NS_1_1Camera.md) &gt; | [**CameraPtr**](classSR__GTYPES__NS_1_1IRenderComponent.md#typedef-cameraptr)  <br> |
| typedef RenderScene \* | [**RenderScenePtr**](classSR__GTYPES__NS_1_1IRenderComponent.md#typedef-rendersceneptr)  <br> |


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
| virtual bool | [**BindMesh**](#function-bindmesh) () <br> |
|  bool | [**DestroyMesh**](#function-destroymesh) () <br> |
| virtual void | [**Draw**](#function-draw) () <br> |
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](#function-executeineditmode) () override const<br> |
| virtual SR\_NODISCARD FrustumCullingType | [**GetFrustumCullingType**](#function-getfrustumcullingtype) () noexcept const<br> |
| virtual SR\_NODISCARD int32\_t | [**GetIBO**](#function-getibo) () <br> |
| virtual SR\_NODISCARD uint32\_t | [**GetIndicesCount**](#function-getindicescount) () const = 0<br> |
|  SR\_NODISCARD const MaterialPtr & | [**GetMaterial**](#function-getmaterial) () noexcept const<br> |
| virtual SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](#function-getmatrix) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetMeshIdentifier**](#function-getmeshidentifier) () const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetMeshLayer**](#function-getmeshlayer) () const<br> |
|  SR\_NODISCARD const MeshRegistrationInfo & | [**GetMeshRegistrationInfo**](#function-getmeshregistrationinfo) () noexcept const<br> |
| virtual SR\_NODISCARD MeshType | [**GetMeshType**](#function-getmeshtype) () noexcept const = 0<br> |
|  SR\_NODISCARD RenderQueues & | [**GetRenderQueues**](#function-getrenderqueues) () noexcept<br> |
|  SR\_NODISCARD [**ShaderPtr**](classSR__GTYPES__NS_1_1Shader.md) | [**GetShader**](#function-getshader) () const<br> |
| virtual SR\_NODISCARD int64\_t | [**GetSortingPriority**](#function-getsortingpriority) () const<br> |
| virtual SR\_NODISCARD int32\_t | [**GetVBO**](#function-getvbo) () <br> |
| virtual SR\_NODISCARD uint32\_t | [**GetVerticesCount**](#function-getverticescount) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetVirtualUBO**](#function-getvirtualubo) () const<br> |
| virtual SR\_NODISCARD bool | [**HasSortingPriority**](#function-hassortingpriority) () const<br> |
| virtual SR\_NODISCARD bool | [**IsActive**](#function-isactive) () noexcept override const<br>_Активен и компонент и его родительский объект_  |
| virtual SR\_NODISCARD bool | [**IsCalculatable**](#function-iscalculatable) () const<br> |
| virtual SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsFlatMesh**](#function-isflatmesh) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsMeshRegistered**](#function-ismeshregistered) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsSupportVBO**](#function-issupportvbo) () const = 0<br> |
|  SR\_NODISCARD bool | [**IsUniformsDirty**](#function-isuniformsdirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsUniqueMesh**](#function-isuniquemesh) () const<br> |
|  SR\_NODISCARD bool | [**IsWaitReRegister**](#function-iswaitreregister) () noexcept const<br> |
|  void | [**MarkMaterialDirty**](#function-markmaterialdirty) () <br> |
|  void | [**MarkUniformsDirty**](#function-markuniformsdirty) (bool force=false) <br> |
|   | [**Mesh**](#function-mesh) () <br> |
| virtual void | [**OnDestroy**](#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](#function-onenable) () override<br> |
| virtual void | [**OnLayerChanged**](#function-onlayerchanged) () override<br> |
| virtual void | [**OnMatrixDirty**](#function-onmatrixdirty) () override<br> |
| virtual void | [**OnPriorityChanged**](#function-onprioritychanged) () override<br> |
|  void | [**OnReRegistered**](#function-onreregistered) () <br> |
| virtual bool | [**OnResourceReloaded**](#function-onresourcereloaded) ([**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  void | [**ReRegisterMesh**](#function-reregistermesh) () <br> |
|  void | [**SetErrorsClean**](#function-seterrorsclean) () <br> |
|  void | [**SetMaterial**](#function-setmaterial-12) (const MaterialPtr & pMaterial) <br> |
|  void | [**SetMaterial**](#function-setmaterial-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
| virtual void | [**SetMatrix**](#function-setmatrix) (const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & matrix) <br> |
|  void | [**SetMeshRegistrationInfo**](#function-setmeshregistrationinfo) (const std::optional&lt; MeshRegistrationInfo &gt; & info) <br> |
|  void | [**SetUniformsClean**](#function-setuniformsclean) () <br> |
|  void | [**UnRegisterMesh**](#function-unregistermesh) () <br> |
| virtual void | [**UseMaterial**](#function-usematerial) () <br> |
| virtual void | [**UseModelMatrix**](#function-usemodelmatrix) () <br> |
| virtual void | [**UseSSBO**](#function-usessbo) () <br> |
| virtual void | [**UseSamplers**](#function-usesamplers) () <br> |
|   | [**~Mesh**](#function-mesh) () override<br> |


## Public Functions inherited from SR_GTYPES_NS::IRenderComponent

See [SR\_GTYPES\_NS::IRenderComponent](classSR__GTYPES__NS_1_1IRenderComponent.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD CameraPtr | [**GetCamera**](classSR__GTYPES__NS_1_1IRenderComponent.md#function-getcamera) () const<br> |
|  SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](classSR__GTYPES__NS_1_1IRenderComponent.md#function-getrenderscene) () const<br> |
| virtual void | [**OnDisable**](classSR__GTYPES__NS_1_1IRenderComponent.md#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](classSR__GTYPES__NS_1_1IRenderComponent.md#function-onenable) () override<br> |
|  SR\_NODISCARD RenderScenePtr | [**TryGetRenderScene**](classSR__GTYPES__NS_1_1IRenderComponent.md#function-trygetrenderscene) () const<br> |


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
|  SR\_NODISCARD SceneObjectPtr | [**GetSceneObject**](classSR__UTILS__NS_1_1Component.md#function-getsceneobject) () const<br> |
|  SR\_NODISCARD [**Transform**](classSR__UTILS__NS_1_1Transform.md) \* | [**GetTransform**](classSR__UTILS__NS_1_1Component.md#function-gettransform) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasParent**](classSR__UTILS__NS_1_1Component.md#function-hasparent) () const<br> |
|  SR\_NODISCARD bool | [**HasScene**](classSR__UTILS__NS_1_1Component.md#function-hasscene) () const<br> |
| virtual SR\_NODISCARD bool | [**IsActive**](classSR__UTILS__NS_1_1Component.md#function-isactive) () noexcept const<br>_Активен и компонент и его родительский объект_  |
| virtual SR\_NODISCARD bool | [**IsAttached**](classSR__UTILS__NS_1_1Component.md#function-isattached) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsAwake**](classSR__UTILS__NS_1_1Component.md#function-isawake) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsComponentLoaded**](classSR__UTILS__NS_1_1Component.md#function-iscomponentloaded) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsComponentValid**](classSR__UTILS__NS_1_1Component.md#function-iscomponentvalid) () noexcept const<br> |
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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  std::vector&lt; Mesh::Ptr &gt; | [**Load**](#function-load-13) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type) <br> |
|  Mesh::Ptr | [**Load**](#function-load-23) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type, uint32\_t id) <br> |
|  Mesh::Ptr | [**Load**](#function-load-33) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  Mesh::Ptr | [**TryLoad**](#function-tryload-12) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, MeshType type, uint32\_t id) <br> |
|  Mesh::Ptr | [**TryLoad**](#function-tryload-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type, uint32\_t id) <br> |


















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**SR\_GRAPH\_NS::DescriptorManager**](classSR__GRAPH__NS_1_1DescriptorManager.md) & | [**m\_descriptorManager**](#variable-m_descriptormanager)  <br> |
|  bool | [**m\_dirtyMaterial**](#variable-m_dirtymaterial)   = `false`<br> |
|  FrustumCullingType | [**m\_frustumCullingType**](#variable-m_frustumcullingtype)   = `FrustumCullingType::Sphere`<br> |
|  bool | [**m\_hasErrors**](#variable-m_haserrors)   = `false`<br> |
|  bool | [**m\_isUniformsDirty**](#variable-m_isuniformsdirty)   = `false`<br> |
|  bool | [**m\_isWaitReRegister**](#variable-m_iswaitreregister)   = `false`<br> |
|  MaterialPtr | [**m\_material**](#variable-m_material)  <br> |
|  RenderQueues | [**m\_renderQueues**](#variable-m_renderqueues)  <br> |
|  Memory::UBOManager & | [**m\_uboManager**](#variable-m_ubomanager)  <br> |
|  int32\_t | [**m\_virtualDescriptor**](#variable-m_virtualdescriptor)   = `SR\_ID\_INVALID`<br> |
|  int32\_t | [**m\_virtualUBO**](#variable-m_virtualubo)   = `SR\_ID\_INVALID`<br> |


## Protected Attributes inherited from SR_GTYPES_NS::IRenderComponent

See [SR\_GTYPES\_NS::IRenderComponent](classSR__GTYPES__NS_1_1IRenderComponent.md)

| Type | Name |
| ---: | :--- |
|  RenderScenePtr | [**m\_renderScene**](classSR__GTYPES__NS_1_1IRenderComponent.md#variable-m_renderscene)   = `nullptr`<br> |


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
| virtual bool | [**Calculate**](#function-calculate) () <br> |
|  void | [**FreeVideoMemory**](#function-freevideomemory) () override<br> |




## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |








## Public Types Documentation




### typedef MaterialPtr 

```C++
using SR_GTYPES_NS::Mesh::MaterialPtr =  SR_HTYPES_NS::SharedPtr<BaseMaterial>;
```




<hr>



### typedef Ptr 

```C++
using SR_GTYPES_NS::Mesh::Ptr =  SR_HTYPES_NS::SharedPtr<Mesh>;
```




<hr>



### typedef RenderQueues 

```C++
using SR_GTYPES_NS::Mesh::RenderQueues =  SR_HTYPES_NS::SortedVector<SR_GRAPH_NS::RenderQueueInfo, SR_GRAPH_NS::RenderQueuePredicate>;
```




<hr>



### typedef RenderScenePtr 

```C++
using SR_GTYPES_NS::Mesh::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<RenderScene>;
```




<hr>



### typedef ShaderPtr 

```C++
using SR_GTYPES_NS::Mesh::ShaderPtr =  Shader*;
```




<hr>
## Public Functions Documentation




### function BindMesh 

```C++
virtual bool SR_GTYPES_NS::Mesh::BindMesh () 
```




<hr>



### function DestroyMesh 

```C++
bool SR_GTYPES_NS::Mesh::DestroyMesh () 
```




<hr>



### function Draw 

```C++
virtual void SR_GTYPES_NS::Mesh::Draw () 
```




<hr>



### function ExecuteInEditMode 

```C++
inline virtual SR_NODISCARD bool SR_GTYPES_NS::Mesh::ExecuteInEditMode () override const
```



Implements [*SR\_UTILS\_NS::Component::ExecuteInEditMode*](classSR__UTILS__NS_1_1Component.md#function-executeineditmode)


<hr>



### function GetFrustumCullingType 

```C++
inline virtual SR_NODISCARD FrustumCullingType SR_GTYPES_NS::Mesh::GetFrustumCullingType () noexcept const
```




<hr>



### function GetIBO 

```C++
inline virtual SR_NODISCARD int32_t SR_GTYPES_NS::Mesh::GetIBO () 
```




<hr>



### function GetIndicesCount 

```C++
virtual SR_NODISCARD uint32_t SR_GTYPES_NS::Mesh::GetIndicesCount () const = 0
```




<hr>



### function GetMaterial 

```C++
inline SR_NODISCARD const MaterialPtr & SR_GTYPES_NS::Mesh::GetMaterial () noexcept const
```




<hr>



### function GetMatrix 

```C++
virtual SR_NODISCARD const SR_MATH_NS::Matrix4x4 & SR_GTYPES_NS::Mesh::GetMatrix () const
```




<hr>



### function GetMeshIdentifier 

```C++
virtual SR_NODISCARD std::string SR_GTYPES_NS::Mesh::GetMeshIdentifier () const
```




<hr>



### function GetMeshLayer 

```C++
virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_GTYPES_NS::Mesh::GetMeshLayer () const
```




<hr>



### function GetMeshRegistrationInfo 

```C++
inline SR_NODISCARD const MeshRegistrationInfo & SR_GTYPES_NS::Mesh::GetMeshRegistrationInfo () noexcept const
```




<hr>



### function GetMeshType 

```C++
virtual SR_NODISCARD MeshType SR_GTYPES_NS::Mesh::GetMeshType () noexcept const = 0
```




<hr>



### function GetRenderQueues 

```C++
inline SR_NODISCARD RenderQueues & SR_GTYPES_NS::Mesh::GetRenderQueues () noexcept
```




<hr>



### function GetShader 

```C++
SR_NODISCARD ShaderPtr SR_GTYPES_NS::Mesh::GetShader () const
```




<hr>



### function GetSortingPriority 

```C++
virtual SR_NODISCARD int64_t SR_GTYPES_NS::Mesh::GetSortingPriority () const
```




<hr>



### function GetVBO 

```C++
inline virtual SR_NODISCARD int32_t SR_GTYPES_NS::Mesh::GetVBO () 
```




<hr>



### function GetVerticesCount 

```C++
inline virtual SR_NODISCARD uint32_t SR_GTYPES_NS::Mesh::GetVerticesCount () const
```




<hr>



### function GetVirtualUBO 

```C++
inline SR_NODISCARD int32_t SR_GTYPES_NS::Mesh::GetVirtualUBO () const
```




<hr>



### function HasSortingPriority 

```C++
virtual SR_NODISCARD bool SR_GTYPES_NS::Mesh::HasSortingPriority () const
```




<hr>



### function IsActive 

_Активен и компонент и его родительский объект_ 
```C++
virtual SR_NODISCARD bool SR_GTYPES_NS::Mesh::IsActive () noexcept override const
```



Implements [*SR\_UTILS\_NS::Component::IsActive*](classSR__UTILS__NS_1_1Component.md#function-isactive)


<hr>



### function IsCalculatable 

```C++
virtual SR_NODISCARD bool SR_GTYPES_NS::Mesh::IsCalculatable () const
```




<hr>



### function IsFlatMesh 

```C++
inline virtual SR_NODISCARD SR_FORCE_INLINE bool SR_GTYPES_NS::Mesh::IsFlatMesh () noexcept const
```




<hr>



### function IsMeshRegistered 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Mesh::IsMeshRegistered () noexcept const
```




<hr>



### function IsSupportVBO 

```C++
virtual SR_NODISCARD bool SR_GTYPES_NS::Mesh::IsSupportVBO () const = 0
```




<hr>



### function IsUniformsDirty 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Mesh::IsUniformsDirty () noexcept const
```




<hr>



### function IsUniqueMesh 

```C++
inline virtual SR_NODISCARD bool SR_GTYPES_NS::Mesh::IsUniqueMesh () const
```




<hr>



### function IsWaitReRegister 

```C++
inline SR_NODISCARD bool SR_GTYPES_NS::Mesh::IsWaitReRegister () noexcept const
```




<hr>



### function MarkMaterialDirty 

```C++
void SR_GTYPES_NS::Mesh::MarkMaterialDirty () 
```




<hr>



### function MarkUniformsDirty 

```C++
void SR_GTYPES_NS::Mesh::MarkUniformsDirty (
    bool force=false
) 
```




<hr>



### function Mesh 

```C++
SR_GTYPES_NS::Mesh::Mesh () 
```




<hr>



### function OnDestroy 

_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._ 
```C++
virtual void SR_GTYPES_NS::Mesh::OnDestroy () override
```



Implements [*SR\_UTILS\_NS::Component::OnDestroy*](classSR__UTILS__NS_1_1Component.md#function-ondestroy)


<hr>



### function OnDisable 

```C++
virtual void SR_GTYPES_NS::Mesh::OnDisable () override
```



Implements [*SR\_GTYPES\_NS::IRenderComponent::OnDisable*](classSR__GTYPES__NS_1_1IRenderComponent.md#function-ondisable)


<hr>



### function OnEnable 

```C++
virtual void SR_GTYPES_NS::Mesh::OnEnable () override
```



Implements [*SR\_GTYPES\_NS::IRenderComponent::OnEnable*](classSR__GTYPES__NS_1_1IRenderComponent.md#function-onenable)


<hr>



### function OnLayerChanged 

```C++
virtual void SR_GTYPES_NS::Mesh::OnLayerChanged () override
```



Implements [*SR\_UTILS\_NS::Component::OnLayerChanged*](classSR__UTILS__NS_1_1Component.md#function-onlayerchanged)


<hr>



### function OnMatrixDirty 

```C++
virtual void SR_GTYPES_NS::Mesh::OnMatrixDirty () override
```



Implements [*SR\_UTILS\_NS::Component::OnMatrixDirty*](classSR__UTILS__NS_1_1Component.md#function-onmatrixdirty)


<hr>



### function OnPriorityChanged 

```C++
virtual void SR_GTYPES_NS::Mesh::OnPriorityChanged () override
```



Implements [*SR\_UTILS\_NS::Component::OnPriorityChanged*](classSR__UTILS__NS_1_1Component.md#function-onprioritychanged)


<hr>



### function OnReRegistered 

```C++
void SR_GTYPES_NS::Mesh::OnReRegistered () 
```




<hr>



### function OnResourceReloaded 

```C++
virtual bool SR_GTYPES_NS::Mesh::OnResourceReloaded (
    SR_UTILS_NS::IResource * pResource
) 
```




<hr>



### function ReRegisterMesh 

```C++
void SR_GTYPES_NS::Mesh::ReRegisterMesh () 
```




<hr>



### function SetErrorsClean 

```C++
inline void SR_GTYPES_NS::Mesh::SetErrorsClean () 
```




<hr>



### function SetMaterial [1/2]

```C++
void SR_GTYPES_NS::Mesh::SetMaterial (
    const MaterialPtr & pMaterial
) 
```




<hr>



### function SetMaterial [2/2]

```C++
void SR_GTYPES_NS::Mesh::SetMaterial (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function SetMatrix 

```C++
virtual void SR_GTYPES_NS::Mesh::SetMatrix (
    const SR_MATH_NS::Matrix4x4 & matrix
) 
```




<hr>



### function SetMeshRegistrationInfo 

```C++
inline void SR_GTYPES_NS::Mesh::SetMeshRegistrationInfo (
    const std::optional< MeshRegistrationInfo > & info
) 
```




<hr>



### function SetUniformsClean 

```C++
inline void SR_GTYPES_NS::Mesh::SetUniformsClean () 
```




<hr>



### function UnRegisterMesh 

```C++
void SR_GTYPES_NS::Mesh::UnRegisterMesh () 
```




<hr>



### function UseMaterial 

```C++
virtual void SR_GTYPES_NS::Mesh::UseMaterial () 
```




<hr>



### function UseModelMatrix 

```C++
inline virtual void SR_GTYPES_NS::Mesh::UseModelMatrix () 
```




<hr>



### function UseSSBO 

```C++
inline virtual void SR_GTYPES_NS::Mesh::UseSSBO () 
```




<hr>



### function UseSamplers 

```C++
virtual void SR_GTYPES_NS::Mesh::UseSamplers () 
```




<hr>



### function ~Mesh 

```C++
SR_GTYPES_NS::Mesh::~Mesh () override
```




<hr>
## Public Static Functions Documentation




### function Load [1/3]

```C++
static std::vector< Mesh::Ptr > SR_GTYPES_NS::Mesh::Load (
    const SR_UTILS_NS::Path & path,
    MeshType type
) 
```




<hr>



### function Load [2/3]

```C++
static Mesh::Ptr SR_GTYPES_NS::Mesh::Load (
    const SR_UTILS_NS::Path & path,
    MeshType type,
    uint32_t id
) 
```




<hr>



### function Load [3/3]

```C++
static Mesh::Ptr SR_GTYPES_NS::Mesh::Load (
    const SR_UTILS_NS::Path & path,
    MeshType type,
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function TryLoad [1/2]

```C++
static Mesh::Ptr SR_GTYPES_NS::Mesh::TryLoad (
    SR_HTYPES_NS::RawMesh * pRawMesh,
    MeshType type,
    uint32_t id
) 
```




<hr>



### function TryLoad [2/2]

```C++
static Mesh::Ptr SR_GTYPES_NS::Mesh::TryLoad (
    const SR_UTILS_NS::Path & path,
    MeshType type,
    uint32_t id
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_descriptorManager 

```C++
SR_GRAPH_NS::DescriptorManager& SR_GTYPES_NS::Mesh::m_descriptorManager;
```




<hr>



### variable m\_dirtyMaterial 

```C++
bool SR_GTYPES_NS::Mesh::m_dirtyMaterial;
```




<hr>



### variable m\_frustumCullingType 

```C++
FrustumCullingType SR_GTYPES_NS::Mesh::m_frustumCullingType;
```




<hr>



### variable m\_hasErrors 

```C++
bool SR_GTYPES_NS::Mesh::m_hasErrors;
```




<hr>



### variable m\_isUniformsDirty 

```C++
bool SR_GTYPES_NS::Mesh::m_isUniformsDirty;
```




<hr>



### variable m\_isWaitReRegister 

```C++
bool SR_GTYPES_NS::Mesh::m_isWaitReRegister;
```




<hr>



### variable m\_material 

```C++
MaterialPtr SR_GTYPES_NS::Mesh::m_material;
```




<hr>



### variable m\_renderQueues 

```C++
RenderQueues SR_GTYPES_NS::Mesh::m_renderQueues;
```




<hr>



### variable m\_uboManager 

```C++
Memory::UBOManager& SR_GTYPES_NS::Mesh::m_uboManager;
```




<hr>



### variable m\_virtualDescriptor 

```C++
int32_t SR_GTYPES_NS::Mesh::m_virtualDescriptor;
```




<hr>



### variable m\_virtualUBO 

```C++
int32_t SR_GTYPES_NS::Mesh::m_virtualUBO;
```




<hr>
## Protected Functions Documentation




### function Calculate 

```C++
virtual bool SR_GTYPES_NS::Mesh::Calculate () 
```




<hr>



### function FreeVideoMemory 

```C++
void SR_GTYPES_NS::Mesh::FreeVideoMemory () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Types/Mesh.h`

