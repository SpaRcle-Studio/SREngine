

# Class SR\_CORE\_GUI\_NS::EditorGizmo



[**ClassList**](annotated.md) **>** [**SR\_CORE\_GUI\_NS**](namespaceSR__CORE__GUI__NS.md) **>** [**EditorGizmo**](classSR__CORE__GUI__NS_1_1EditorGizmo.md)








Inherits the following classes: [SR\_GRAPH\_UI\_NS::Gizmo](classSR__GRAPH__UI__NS_1_1Gizmo.md)


















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
| virtual void | [**BeginGizmo**](#function-begingizmo) () override<br> |
| virtual void | [**EndGizmo**](#function-endgizmo) () override<br> |
| virtual SR\_NODISCARD SR\_FORCE\_INLINE bool | [**ExecuteInEditMode**](#function-executeineditmode) () override const<br> |
| virtual SR\_NODISCARD [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**GetGizmoMatrix**](#function-getgizmomatrix) () override const<br> |
| virtual SR\_NODISCARD SR\_GRAPH\_UI\_NS::GizmoMode | [**GetMode**](#function-getmode) () override const<br> |
| virtual SR\_NODISCARD bool | [**IsGizmoAvailable**](#function-isgizmoavailable) () override const<br> |
| virtual SR\_NODISCARD bool | [**IsHandledAnotherObject**](#function-ishandledanotherobject) () override const<br> |
| virtual void | [**OnGizmoRotated**](#function-ongizmorotated) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & delta) override<br> |
| virtual void | [**OnGizmoScaled**](#function-ongizmoscaled) (const SR\_MATH\_NS::FVector3 & delta) override<br> |
| virtual void | [**OnGizmoTranslated**](#function-ongizmotranslated) (const SR\_MATH\_NS::FVector3 & delta) override<br> |
| virtual void | [**PrepareGizmo**](#function-preparegizmo) () override<br> |
|  void | [**SetHierarchy**](#function-sethierarchy) ([**Hierarchy**](classSR__CORE__GUI__NS_1_1Hierarchy.md) \* pHierarchy) <br> |


## Public Functions inherited from SR_GRAPH_UI_NS::Gizmo

See [SR\_GRAPH\_UI\_NS::Gizmo](classSR__GRAPH__UI__NS_1_1Gizmo.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**FixedUpdate**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-fixedupdate) () override<br> |
| virtual SR\_NODISCARD GizmoMode | [**GetMode**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getmode) () const<br> |
| virtual SR\_NODISCARD GizmoOperation | [**GetOperation**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getoperation) () const<br> |
|  SR\_NODISCARD bool | [**IsGizmo2DSpace**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-isgizmo2dspace) () const<br> |
|  SR\_NODISCARD bool | [**IsGizmoActive**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-isgizmoactive) () const<br> |
|  SR\_NODISCARD bool | [**IsGizmoEnabled**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-isgizmoenabled) () const<br> |
|  SR\_NODISCARD bool | [**IsGizmoHovered**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-isgizmohovered) () const<br> |
| virtual void | [**OnAttached**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-onattached) () override<br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnDestroy**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-onenable) () override<br> |
|  void | [**SetMode**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-setmode) (GizmoMode mode) <br> |
|  void | [**SetOperation**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-setoperation) (GizmoOperation operation) <br> |


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
|  SR\_NODISCARD const SceneObjectPtr & | [**GetSceneObject**](classSR__UTILS__NS_1_1Component.md#function-getsceneobject) () const<br> |
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




























































## Protected Functions inherited from SR_GRAPH_UI_NS::Gizmo

See [SR\_GRAPH\_UI\_NS::Gizmo](classSR__GRAPH__UI__NS_1_1Gizmo.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**BeginGizmo**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-begingizmo) () <br> |
| virtual void | [**EndGizmo**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-endgizmo) () <br> |
| virtual SR\_NODISCARD SR\_FORCE\_INLINE bool | [**ExecuteInEditMode**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-executeineditmode) () override const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::Axis | [**GetAxis**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getaxis) () const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**GetColorByOperation**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getcolorbyoperation) (GizmoOperation operation) const<br> |
|  SR\_NODISCARD GameObjectPtr | [**GetGameObjectByOperation**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getgameobjectbyoperation) (GizmoMeshLoadMode mode, GizmoOperation operation) const<br> |
| virtual SR\_NODISCARD [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**GetGizmoMatrix**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getgizmomatrix) () const<br> |
| virtual SR\_NODISCARD bool | [**IsGizmoAvailable**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-isgizmoavailable) () const<br> |
| virtual SR\_NODISCARD bool | [**IsHandledAnotherObject**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ishandledanotherobject) () const<br> |
|  SR\_NODISCARD bool | [**IsLocal**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-islocal) () const<br> |
|  void | [**LoadGizmo**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-loadgizmo) () <br> |
|  void | [**LoadMesh**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-loadmesh) (GizmoOperation operation, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) path, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, GizmoMeshLoadMode mode) <br> |
| virtual void | [**OnGizmoRotated**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ongizmorotated) (const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & delta) <br> |
| virtual void | [**OnGizmoScaled**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ongizmoscaled) (const SR\_MATH\_NS::FVector3 & delta) <br> |
| virtual void | [**OnGizmoTranslated**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ongizmotranslated) (const SR\_MATH\_NS::FVector3 & delta) <br> |
| virtual void | [**PrepareGizmo**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-preparegizmo) () <br> |
|  void | [**ProcessGizmo**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-processgizmo) (const SR\_MATH\_NS::FPoint & mousePos) <br> |
|  void | [**ReleaseGizmo**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-releasegizmo) () <br> |
|  void | [**UpdateGizmoTransform**](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-updategizmotransform) () <br> |




## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |










## Public Functions Documentation




### function BeginGizmo 

```C++
virtual void SR_CORE_GUI_NS::EditorGizmo::BeginGizmo () override
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::BeginGizmo*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-begingizmo)


<hr>



### function EndGizmo 

```C++
virtual void SR_CORE_GUI_NS::EditorGizmo::EndGizmo () override
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::EndGizmo*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-endgizmo)


<hr>



### function ExecuteInEditMode 

```C++
inline virtual SR_NODISCARD SR_FORCE_INLINE bool SR_CORE_GUI_NS::EditorGizmo::ExecuteInEditMode () override const
```



Implements [*SR\_UTILS\_NS::Component::ExecuteInEditMode*](classSR__UTILS__NS_1_1Component.md#function-executeineditmode)


<hr>



### function GetGizmoMatrix 

```C++
virtual SR_NODISCARD SR_MATH_NS::Matrix4x4 SR_CORE_GUI_NS::EditorGizmo::GetGizmoMatrix () override const
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::GetGizmoMatrix*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getgizmomatrix)


<hr>



### function GetMode 

```C++
virtual SR_NODISCARD SR_GRAPH_UI_NS::GizmoMode SR_CORE_GUI_NS::EditorGizmo::GetMode () override const
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::GetMode*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-getmode)


<hr>



### function IsGizmoAvailable 

```C++
virtual SR_NODISCARD bool SR_CORE_GUI_NS::EditorGizmo::IsGizmoAvailable () override const
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::IsGizmoAvailable*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-isgizmoavailable)


<hr>



### function IsHandledAnotherObject 

```C++
inline virtual SR_NODISCARD bool SR_CORE_GUI_NS::EditorGizmo::IsHandledAnotherObject () override const
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::IsHandledAnotherObject*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ishandledanotherobject)


<hr>



### function OnGizmoRotated 

```C++
virtual void SR_CORE_GUI_NS::EditorGizmo::OnGizmoRotated (
    const SR_MATH_NS::Quaternion & delta
) override
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::OnGizmoRotated*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ongizmorotated)


<hr>



### function OnGizmoScaled 

```C++
virtual void SR_CORE_GUI_NS::EditorGizmo::OnGizmoScaled (
    const SR_MATH_NS::FVector3 & delta
) override
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::OnGizmoScaled*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ongizmoscaled)


<hr>



### function OnGizmoTranslated 

```C++
virtual void SR_CORE_GUI_NS::EditorGizmo::OnGizmoTranslated (
    const SR_MATH_NS::FVector3 & delta
) override
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::OnGizmoTranslated*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-ongizmotranslated)


<hr>



### function PrepareGizmo 

```C++
virtual void SR_CORE_GUI_NS::EditorGizmo::PrepareGizmo () override
```



Implements [*SR\_GRAPH\_UI\_NS::Gizmo::PrepareGizmo*](classSR__GRAPH__UI__NS_1_1Gizmo.md#function-preparegizmo)


<hr>



### function SetHierarchy 

```C++
inline void SR_CORE_GUI_NS::EditorGizmo::SetHierarchy (
    Hierarchy * pHierarchy
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/GUI/EditorGizmo.h`

