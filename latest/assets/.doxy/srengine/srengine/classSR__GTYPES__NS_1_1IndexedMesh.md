

# Class SR\_GTYPES\_NS::IndexedMesh



[**ClassList**](annotated.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) **>** [**IndexedMesh**](classSR__GTYPES__NS_1_1IndexedMesh.md)








Inherits the following classes: [SR\_GTYPES\_NS::Mesh](classSR__GTYPES__NS_1_1Mesh.md)


Inherited by the following classes: [SR\_GTYPES\_NS::DebugWireframeMesh](classSR__GTYPES__NS_1_1DebugWireframeMesh.md),  [SR\_GTYPES\_NS::Mesh3D](classSR__GTYPES__NS_1_1Mesh3D.md),  [SR\_GTYPES\_NS::ProceduralMesh](classSR__GTYPES__NS_1_1ProceduralMesh.md),  [SR\_GTYPES\_NS::SkinnedMesh](classSR__GTYPES__NS_1_1SkinnedMesh.md)














## Public Types inherited from SR_GTYPES_NS::Mesh

See [SR\_GTYPES\_NS::Mesh](classSR__GTYPES__NS_1_1Mesh.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; BaseMaterial &gt; | [**MaterialPtr**](classSR__GTYPES__NS_1_1Mesh.md#typedef-materialptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Mesh**](classSR__GTYPES__NS_1_1Mesh.md) &gt; | [**Ptr**](classSR__GTYPES__NS_1_1Mesh.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SortedVector**](classSR__HTYPES__NS_1_1SortedVector.md)&lt; [**SR\_GRAPH\_NS::RenderQueueInfo**](structSR__GRAPH__NS_1_1RenderQueueInfo.md), [**SR\_GRAPH\_NS::RenderQueuePredicate**](structSR__GRAPH__NS_1_1RenderQueuePredicate.md) &gt; | [**RenderQueues**](classSR__GTYPES__NS_1_1Mesh.md#typedef-renderqueues)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; RenderScene &gt; | [**RenderScenePtr**](classSR__GTYPES__NS_1_1Mesh.md#typedef-rendersceneptr)  <br> |
| typedef [**Shader**](classSR__GTYPES__NS_1_1Shader.md) \* | [**ShaderPtr**](classSR__GTYPES__NS_1_1Mesh.md#typedef-shaderptr)  <br> |


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
| virtual bool | [**Calculate**](#function-calculate) () override<br> |
|  bool | [**CalculateIBO**](#function-calculateibo) () <br> |
|  bool | [**CalculateVBO**](#function-calculatevbo-12) (const std::vector&lt; Vertex &gt; & vertices) <br> |
|  bool | [**CalculateVBO**](#function-calculatevbo-22) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; std::vector&lt; Vertex &gt;()&gt; & getter) <br> |
|  bool | [**FreeIBO**](#function-freeibo) () <br> |
|  bool | [**FreeVBO**](#function-freevbo) () <br> |
|  void | [**FreeVideoMemory**](#function-freevideomemory) () override<br> |
| virtual SR\_NODISCARD int32\_t | [**GetIBO**](#function-getibo) () override<br> |
| virtual SR\_NODISCARD std::vector&lt; uint32\_t &gt; | [**GetIndices**](#function-getindices) () const<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetIndicesCount**](#function-getindicescount) () override const<br> |
| virtual SR\_NODISCARD int32\_t | [**GetVBO**](#function-getvbo) () override<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetVerticesCount**](#function-getverticescount) () override const<br> |
| virtual SR\_NODISCARD bool | [**IsSupportVBO**](#function-issupportvbo) () override const<br> |
|   | [**~IndexedMesh**](#function-indexedmesh) () override<br> |


## Public Functions inherited from SR_GTYPES_NS::Mesh

See [SR\_GTYPES\_NS::Mesh](classSR__GTYPES__NS_1_1Mesh.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**BindMesh**](classSR__GTYPES__NS_1_1Mesh.md#function-bindmesh) () <br> |
|  bool | [**DestroyMesh**](classSR__GTYPES__NS_1_1Mesh.md#function-destroymesh) () <br> |
| virtual void | [**Draw**](classSR__GTYPES__NS_1_1Mesh.md#function-draw) () <br> |
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](classSR__GTYPES__NS_1_1Mesh.md#function-executeineditmode) () override const<br> |
| virtual SR\_NODISCARD FrustumCullingType | [**GetFrustumCullingType**](classSR__GTYPES__NS_1_1Mesh.md#function-getfrustumcullingtype) () noexcept const<br> |
| virtual SR\_NODISCARD int32\_t | [**GetIBO**](classSR__GTYPES__NS_1_1Mesh.md#function-getibo) () <br> |
| virtual SR\_NODISCARD uint32\_t | [**GetIndicesCount**](classSR__GTYPES__NS_1_1Mesh.md#function-getindicescount) () const = 0<br> |
|  SR\_NODISCARD const MaterialPtr & | [**GetMaterial**](classSR__GTYPES__NS_1_1Mesh.md#function-getmaterial) () noexcept const<br> |
| virtual SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](classSR__GTYPES__NS_1_1Mesh.md#function-getmatrix) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetMeshIdentifier**](classSR__GTYPES__NS_1_1Mesh.md#function-getmeshidentifier) () const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetMeshLayer**](classSR__GTYPES__NS_1_1Mesh.md#function-getmeshlayer) () const<br> |
|  SR\_NODISCARD const MeshRegistrationInfo & | [**GetMeshRegistrationInfo**](classSR__GTYPES__NS_1_1Mesh.md#function-getmeshregistrationinfo) () noexcept const<br> |
| virtual SR\_NODISCARD MeshType | [**GetMeshType**](classSR__GTYPES__NS_1_1Mesh.md#function-getmeshtype) () noexcept const = 0<br> |
|  SR\_NODISCARD RenderQueues & | [**GetRenderQueues**](classSR__GTYPES__NS_1_1Mesh.md#function-getrenderqueues) () noexcept<br> |
|  SR\_NODISCARD [**ShaderPtr**](classSR__GTYPES__NS_1_1Shader.md) | [**GetShader**](classSR__GTYPES__NS_1_1Mesh.md#function-getshader) () const<br> |
| virtual SR\_NODISCARD int64\_t | [**GetSortingPriority**](classSR__GTYPES__NS_1_1Mesh.md#function-getsortingpriority) () const<br> |
| virtual SR\_NODISCARD int32\_t | [**GetVBO**](classSR__GTYPES__NS_1_1Mesh.md#function-getvbo) () <br> |
| virtual SR\_NODISCARD uint32\_t | [**GetVerticesCount**](classSR__GTYPES__NS_1_1Mesh.md#function-getverticescount) () const<br> |
|  SR\_NODISCARD int32\_t | [**GetVirtualUBO**](classSR__GTYPES__NS_1_1Mesh.md#function-getvirtualubo) () const<br> |
| virtual SR\_NODISCARD bool | [**HasSortingPriority**](classSR__GTYPES__NS_1_1Mesh.md#function-hassortingpriority) () const<br> |
| virtual SR\_NODISCARD bool | [**IsActive**](classSR__GTYPES__NS_1_1Mesh.md#function-isactive) () noexcept override const<br>_Активен и компонент и его родительский объект_  |
| virtual SR\_NODISCARD bool | [**IsCalculatable**](classSR__GTYPES__NS_1_1Mesh.md#function-iscalculatable) () const<br> |
| virtual SR\_NODISCARD SR\_FORCE\_INLINE bool | [**IsFlatMesh**](classSR__GTYPES__NS_1_1Mesh.md#function-isflatmesh) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsMeshRegistered**](classSR__GTYPES__NS_1_1Mesh.md#function-ismeshregistered) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsSupportVBO**](classSR__GTYPES__NS_1_1Mesh.md#function-issupportvbo) () const = 0<br> |
|  SR\_NODISCARD bool | [**IsUniformsDirty**](classSR__GTYPES__NS_1_1Mesh.md#function-isuniformsdirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsUniqueMesh**](classSR__GTYPES__NS_1_1Mesh.md#function-isuniquemesh) () const<br> |
|  SR\_NODISCARD bool | [**IsWaitReRegister**](classSR__GTYPES__NS_1_1Mesh.md#function-iswaitreregister) () noexcept const<br> |
|  void | [**MarkMaterialDirty**](classSR__GTYPES__NS_1_1Mesh.md#function-markmaterialdirty) () <br> |
|  void | [**MarkUniformsDirty**](classSR__GTYPES__NS_1_1Mesh.md#function-markuniformsdirty) (bool force=false) <br> |
|   | [**Mesh**](classSR__GTYPES__NS_1_1Mesh.md#function-mesh) () <br> |
| virtual void | [**OnDestroy**](classSR__GTYPES__NS_1_1Mesh.md#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](classSR__GTYPES__NS_1_1Mesh.md#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](classSR__GTYPES__NS_1_1Mesh.md#function-onenable) () override<br> |
| virtual void | [**OnLayerChanged**](classSR__GTYPES__NS_1_1Mesh.md#function-onlayerchanged) () override<br> |
| virtual void | [**OnMatrixDirty**](classSR__GTYPES__NS_1_1Mesh.md#function-onmatrixdirty) () override<br> |
| virtual void | [**OnPriorityChanged**](classSR__GTYPES__NS_1_1Mesh.md#function-onprioritychanged) () override<br> |
|  void | [**OnReRegistered**](classSR__GTYPES__NS_1_1Mesh.md#function-onreregistered) () <br> |
| virtual bool | [**OnResourceReloaded**](classSR__GTYPES__NS_1_1Mesh.md#function-onresourcereloaded) ([**SR\_UTILS\_NS::IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  void | [**ReRegisterMesh**](classSR__GTYPES__NS_1_1Mesh.md#function-reregistermesh) () <br> |
|  void | [**SetErrorsClean**](classSR__GTYPES__NS_1_1Mesh.md#function-seterrorsclean) () <br> |
|  void | [**SetMaterial**](classSR__GTYPES__NS_1_1Mesh.md#function-setmaterial-12) (const MaterialPtr & pMaterial) <br> |
|  void | [**SetMaterial**](classSR__GTYPES__NS_1_1Mesh.md#function-setmaterial-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
| virtual void | [**SetMatrix**](classSR__GTYPES__NS_1_1Mesh.md#function-setmatrix) (const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & matrix) <br> |
|  void | [**SetMeshRegistrationInfo**](classSR__GTYPES__NS_1_1Mesh.md#function-setmeshregistrationinfo) (const std::optional&lt; MeshRegistrationInfo &gt; & info) <br> |
|  void | [**SetUniformsClean**](classSR__GTYPES__NS_1_1Mesh.md#function-setuniformsclean) () <br> |
|  void | [**UnRegisterMesh**](classSR__GTYPES__NS_1_1Mesh.md#function-unregistermesh) () <br> |
| virtual void | [**UseMaterial**](classSR__GTYPES__NS_1_1Mesh.md#function-usematerial) () <br> |
| virtual void | [**UseModelMatrix**](classSR__GTYPES__NS_1_1Mesh.md#function-usemodelmatrix) () <br> |
| virtual void | [**UseSSBO**](classSR__GTYPES__NS_1_1Mesh.md#function-usessbo) () <br> |
| virtual void | [**UseSamplers**](classSR__GTYPES__NS_1_1Mesh.md#function-usesamplers) () <br> |
|   | [**~Mesh**](classSR__GTYPES__NS_1_1Mesh.md#function-mesh) () override<br> |


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




## Public Static Functions inherited from SR_GTYPES_NS::Mesh

See [SR\_GTYPES\_NS::Mesh](classSR__GTYPES__NS_1_1Mesh.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; Mesh::Ptr &gt; | [**Load**](classSR__GTYPES__NS_1_1Mesh.md#function-load-13) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type) <br> |
|  Mesh::Ptr | [**Load**](classSR__GTYPES__NS_1_1Mesh.md#function-load-23) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type, uint32\_t id) <br> |
|  Mesh::Ptr | [**Load**](classSR__GTYPES__NS_1_1Mesh.md#function-load-33) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  Mesh::Ptr | [**TryLoad**](classSR__GTYPES__NS_1_1Mesh.md#function-tryload-12) ([**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* pRawMesh, MeshType type, uint32\_t id) <br> |
|  Mesh::Ptr | [**TryLoad**](classSR__GTYPES__NS_1_1Mesh.md#function-tryload-22) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path, MeshType type, uint32\_t id) <br> |






















## Protected Attributes

| Type | Name |
| ---: | :--- |
|  int32\_t | [**m\_IBO**](#variable-m_ibo)   = `SR\_ID\_INVALID`<br> |
|  int32\_t | [**m\_VBO**](#variable-m_vbo)   = `SR\_ID\_INVALID`<br> |
|  uint32\_t | [**m\_countIndices**](#variable-m_countindices)   = `0`<br> |
|  uint32\_t | [**m\_countVertices**](#variable-m_countvertices)   = `0`<br> |


## Protected Attributes inherited from SR_GTYPES_NS::Mesh

See [SR\_GTYPES\_NS::Mesh](classSR__GTYPES__NS_1_1Mesh.md)

| Type | Name |
| ---: | :--- |
|  [**SR\_GRAPH\_NS::DescriptorManager**](classSR__GRAPH__NS_1_1DescriptorManager.md) & | [**m\_descriptorManager**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_descriptormanager)  <br> |
|  bool | [**m\_dirtyMaterial**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_dirtymaterial)   = `false`<br> |
|  FrustumCullingType | [**m\_frustumCullingType**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_frustumcullingtype)   = `FrustumCullingType::Sphere`<br> |
|  bool | [**m\_hasErrors**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_haserrors)   = `false`<br> |
|  bool | [**m\_isUniformsDirty**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_isuniformsdirty)   = `false`<br> |
|  bool | [**m\_isWaitReRegister**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_iswaitreregister)   = `false`<br> |
|  MaterialPtr | [**m\_material**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_material)  <br> |
|  RenderQueues | [**m\_renderQueues**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_renderqueues)  <br> |
|  Memory::UBOManager & | [**m\_uboManager**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_ubomanager)  <br> |
|  int32\_t | [**m\_virtualDescriptor**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_virtualdescriptor)   = `SR\_ID\_INVALID`<br> |
|  int32\_t | [**m\_virtualUBO**](classSR__GTYPES__NS_1_1Mesh.md#variable-m_virtualubo)   = `SR\_ID\_INVALID`<br> |


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
|   | [**IndexedMesh**](#function-indexedmesh) () = default<br> |


## Protected Functions inherited from SR_GTYPES_NS::Mesh

See [SR\_GTYPES\_NS::Mesh](classSR__GTYPES__NS_1_1Mesh.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**Calculate**](classSR__GTYPES__NS_1_1Mesh.md#function-calculate) () <br> |
|  void | [**FreeVideoMemory**](classSR__GTYPES__NS_1_1Mesh.md#function-freevideomemory) () override<br> |




## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |










## Public Functions Documentation




### function Calculate 

```C++
virtual bool SR_GTYPES_NS::IndexedMesh::Calculate () override
```



Implements [*SR\_GTYPES\_NS::Mesh::Calculate*](classSR__GTYPES__NS_1_1Mesh.md#function-calculate)


<hr>



### function CalculateIBO 

```C++
bool SR_GTYPES_NS::IndexedMesh::CalculateIBO () 
```




<hr>



### function CalculateVBO [1/2]

```C++
template<Vertices::VertexType type, typename Vertex>
bool SR_GTYPES_NS::IndexedMesh::CalculateVBO (
    const std::vector< Vertex > & vertices
) 
```




<hr>



### function CalculateVBO [2/2]

```C++
template<Vertices::VertexType type, typename Vertex>
bool SR_GTYPES_NS::IndexedMesh::CalculateVBO (
    const SR_HTYPES_NS::Function < std::vector< Vertex >()> & getter
) 
```




 


        

<hr>



### function FreeIBO 

```C++
bool SR_GTYPES_NS::IndexedMesh::FreeIBO () 
```




<hr>



### function FreeVBO 

```C++
bool SR_GTYPES_NS::IndexedMesh::FreeVBO () 
```




<hr>



### function FreeVideoMemory 

```C++
void SR_GTYPES_NS::IndexedMesh::FreeVideoMemory () override
```




<hr>



### function GetIBO 

```C++
virtual SR_NODISCARD int32_t SR_GTYPES_NS::IndexedMesh::GetIBO () override
```



Implements [*SR\_GTYPES\_NS::Mesh::GetIBO*](classSR__GTYPES__NS_1_1Mesh.md#function-getibo)


<hr>



### function GetIndices 

```C++
inline virtual SR_NODISCARD std::vector< uint32_t > SR_GTYPES_NS::IndexedMesh::GetIndices () const
```




<hr>



### function GetIndicesCount 

```C++
inline virtual SR_NODISCARD uint32_t SR_GTYPES_NS::IndexedMesh::GetIndicesCount () override const
```



Implements [*SR\_GTYPES\_NS::Mesh::GetIndicesCount*](classSR__GTYPES__NS_1_1Mesh.md#function-getindicescount)


<hr>



### function GetVBO 

```C++
virtual SR_NODISCARD int32_t SR_GTYPES_NS::IndexedMesh::GetVBO () override
```



Implements [*SR\_GTYPES\_NS::Mesh::GetVBO*](classSR__GTYPES__NS_1_1Mesh.md#function-getvbo)


<hr>



### function GetVerticesCount 

```C++
inline virtual SR_NODISCARD uint32_t SR_GTYPES_NS::IndexedMesh::GetVerticesCount () override const
```



Implements [*SR\_GTYPES\_NS::Mesh::GetVerticesCount*](classSR__GTYPES__NS_1_1Mesh.md#function-getverticescount)


<hr>



### function IsSupportVBO 

```C++
inline virtual SR_NODISCARD bool SR_GTYPES_NS::IndexedMesh::IsSupportVBO () override const
```



Implements [*SR\_GTYPES\_NS::Mesh::IsSupportVBO*](classSR__GTYPES__NS_1_1Mesh.md#function-issupportvbo)


<hr>



### function ~IndexedMesh 

```C++
SR_GTYPES_NS::IndexedMesh::~IndexedMesh () override
```




<hr>
## Protected Attributes Documentation




### variable m\_IBO 

```C++
int32_t SR_GTYPES_NS::IndexedMesh::m_IBO;
```




<hr>



### variable m\_VBO 

```C++
int32_t SR_GTYPES_NS::IndexedMesh::m_VBO;
```




<hr>



### variable m\_countIndices 

```C++
uint32_t SR_GTYPES_NS::IndexedMesh::m_countIndices;
```




<hr>



### variable m\_countVertices 

```C++
uint32_t SR_GTYPES_NS::IndexedMesh::m_countVertices;
```




<hr>
## Protected Functions Documentation




### function IndexedMesh 

```C++
SR_GTYPES_NS::IndexedMesh::IndexedMesh () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Types/Geometry/IndexedMesh.h`

