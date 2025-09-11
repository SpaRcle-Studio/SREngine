

# Class SR\_CORE\_GUI\_NS::EditorCamera



[**ClassList**](annotated.md) **>** [**SR\_CORE\_GUI\_NS**](namespaceSR__CORE__GUI__NS.md) **>** [**EditorCamera**](classSR__CORE__GUI__NS_1_1EditorCamera.md)








Inherits the following classes: [SR\_GTYPES\_NS::Camera](classSR__GTYPES__NS_1_1Camera.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**EditorCamera**](classSR__CORE__GUI__NS_1_1EditorCamera.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_GTYPES_NS::Camera

See [SR\_GTYPES\_NS::Camera](classSR__GTYPES__NS_1_1Camera.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Camera**](classSR__GTYPES__NS_1_1Camera.md) &gt; | [**Ptr**](classSR__GTYPES__NS_1_1Camera.md#typedef-ptr)  <br> |


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
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](#function-executeineditmode) () override const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FPoint | [**GetMousePos**](#function-getmousepos) () override const<br> |
|  void | [**SetSceneViewer**](#function-setsceneviewer) ([**SceneViewer**](classSR__CORE__GUI__NS_1_1SceneViewer.md) \* pSceneViewer) <br> |


## Public Functions inherited from SR_GTYPES_NS::Camera

See [SR\_GTYPES\_NS::Camera](classSR__GTYPES__NS_1_1Camera.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD float\_t | [**CalculateScreenFactor**](classSR__GTYPES__NS_1_1Camera.md#function-calculatescreenfactor-12) (const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & modelMatrix, float\_t sizeClipSpace, bool orthogonal) const<br> |
|  SR\_NODISCARD float\_t | [**CalculateScreenFactor**](classSR__GTYPES__NS_1_1Camera.md#function-calculatescreenfactor-22) (const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & modelMatrix, const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & viewMatrix, float\_t sizeClipSpace, bool orthogonal) const<br> |
|   | [**Camera**](classSR__GTYPES__NS_1_1Camera.md#function-camera) () <br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetAspect**](classSR__GTYPES__NS_1_1Camera.md#function-getaspect) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCameraDir**](classSR__GTYPES__NS_1_1Camera.md#function-getcameradir) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetCameraEye**](classSR__GTYPES__NS_1_1Camera.md#function-getcameraeye) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetFOV**](classSR__GTYPES__NS_1_1Camera.md#function-getfov) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetFar**](classSR__GTYPES__NS_1_1Camera.md#function-getfar) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE glm::vec3 | [**GetGLPosition**](classSR__GTYPES__NS_1_1Camera.md#function-getglposition) () const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**GetImGuizmoView**](classSR__GTYPES__NS_1_1Camera.md#function-getimguizmoview) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FPoint | [**GetMousePos**](classSR__GTYPES__NS_1_1Camera.md#function-getmousepos) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetNear**](classSR__GTYPES__NS_1_1Camera.md#function-getnear) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetOrthogonal**](classSR__GTYPES__NS_1_1Camera.md#function-getorthogonal) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const SR\_MATH\_NS::FVector3 & | [**GetPosition**](classSR__GTYPES__NS_1_1Camera.md#function-getposition) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE int32\_t | [**GetPriority**](classSR__GTYPES__NS_1_1Camera.md#function-getpriority) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetProjection**](classSR__GTYPES__NS_1_1Camera.md#function-getprojection) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetProjectionNoFOV**](classSR__GTYPES__NS_1_1Camera.md#function-getprojectionnofov) () noexcept const<br> |
|  SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](classSR__GTYPES__NS_1_1Camera.md#function-getrenderscene) () const<br> |
|  SR\_NODISCARD IRenderTechnique \* | [**GetRenderTechnique**](classSR__GTYPES__NS_1_1Camera.md#function-getrendertechnique) () <br> |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetRenderTechniquePath**](classSR__GTYPES__NS_1_1Camera.md#function-getrendertechniquepath) () <br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & | [**GetRotation**](classSR__GTYPES__NS_1_1Camera.md#function-getrotation) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Ray**](structSR__MATH__NS_1_1Ray.md) | [**GetScreenRay**](classSR__GTYPES__NS_1_1Camera.md#function-getscreenray-12) (const SR\_MATH\_NS::FPoint & screenPos, bool orthogonal) const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Ray**](structSR__MATH__NS_1_1Ray.md) | [**GetScreenRay**](classSR__GTYPES__NS_1_1Camera.md#function-getscreenray-22) (float\_t x, float\_t y, bool orthogonal) const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE SR\_MATH\_NS::UVector2 | [**GetSize**](classSR__GTYPES__NS_1_1Camera.md#function-getsize) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetView**](classSR__GTYPES__NS_1_1Camera.md#function-getview) () noexcept const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector3 & | [**GetViewDirection**](classSR__GTYPES__NS_1_1Camera.md#function-getviewdirection-12) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetViewDirection**](classSR__GTYPES__NS_1_1Camera.md#function-getviewdirection-22) (const SR\_MATH\_NS::FVector3 & pos) noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetViewPosition**](classSR__GTYPES__NS_1_1Camera.md#function-getviewposition) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetViewTranslate**](classSR__GTYPES__NS_1_1Camera.md#function-getviewtranslate) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const SR\_MATH\_NS::UVector2 & | [**GetViewportSize**](classSR__GTYPES__NS_1_1Camera.md#function-getviewportsize) () const<br> |
|  SR\_NODISCARD bool | [**IsEditorCamera**](classSR__GTYPES__NS_1_1Camera.md#function-iseditorcamera) () const<br> |
| virtual void | [**OnAttached**](classSR__GTYPES__NS_1_1Camera.md#function-onattached) () override<br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnMatrixDirty**](classSR__GTYPES__NS_1_1Camera.md#function-onmatrixdirty) () override<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**ScreenToWorldPoint**](classSR__GTYPES__NS_1_1Camera.md#function-screentoworldpoint-13) (const SR\_MATH\_NS::FVector3 & screenPos) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**ScreenToWorldPoint**](classSR__GTYPES__NS_1_1Camera.md#function-screentoworldpoint-23) (const SR\_MATH\_NS::FVector2 & screenPos) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**ScreenToWorldPoint**](classSR__GTYPES__NS_1_1Camera.md#function-screentoworldpoint-33) (const SR\_MATH\_NS::FVector2 & screenPos, float\_t depth) const<br> |
|  void | [**SetCameraType**](classSR__GTYPES__NS_1_1Camera.md#function-setcameratype) (CameraType type) <br> |
|  void | [**SetFOV**](classSR__GTYPES__NS_1_1Camera.md#function-setfov) (float\_t value) <br> |
|  void | [**SetFar**](classSR__GTYPES__NS_1_1Camera.md#function-setfar) (float\_t value) <br> |
|  void | [**SetNear**](classSR__GTYPES__NS_1_1Camera.md#function-setnear) (float\_t value) <br> |
|  void | [**SetPriority**](classSR__GTYPES__NS_1_1Camera.md#function-setpriority) (int32\_t priority) <br> |
|  void | [**SetRenderTechnique**](classSR__GTYPES__NS_1_1Camera.md#function-setrendertechnique) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
| virtual void | [**Start**](classSR__GTYPES__NS_1_1Camera.md#function-start) () override<br> |
|  SR\_NODISCARD RenderScenePtr | [**TryGetRenderScene**](classSR__GTYPES__NS_1_1Camera.md#function-trygetrenderscene) () const<br> |
| virtual void | [**Update**](classSR__GTYPES__NS_1_1Camera.md#function-update) (float\_t dt) override<br> |
|  void | [**UpdateProjection**](classSR__GTYPES__NS_1_1Camera.md#function-updateprojection-12) (uint32\_t w, uint32\_t h) <br> |
|   | [**~Camera**](classSR__GTYPES__NS_1_1Camera.md#function-camera) () override<br> |


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














































## Protected Functions inherited from SR_GTYPES_NS::Camera

See [SR\_GTYPES\_NS::Camera](classSR__GTYPES__NS_1_1Camera.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnDestroy**](classSR__GTYPES__NS_1_1Camera.md#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](classSR__GTYPES__NS_1_1Camera.md#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](classSR__GTYPES__NS_1_1Camera.md#function-onenable) () override<br> |
|  void | [**UpdateProjection**](classSR__GTYPES__NS_1_1Camera.md#function-updateprojection-22) () <br> |
|  void | [**UpdateView**](classSR__GTYPES__NS_1_1Camera.md#function-updateview) () noexcept<br> |


## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |








## Public Types Documentation




### typedef Ptr 

```C++
using SR_CORE_GUI_NS::EditorCamera::Ptr =  SR_HTYPES_NS::SharedPtr<EditorCamera>;
```




<hr>
## Public Functions Documentation




### function ExecuteInEditMode 

```C++
inline virtual SR_NODISCARD bool SR_CORE_GUI_NS::EditorCamera::ExecuteInEditMode () override const
```



Implements [*SR\_UTILS\_NS::Component::ExecuteInEditMode*](classSR__UTILS__NS_1_1Component.md#function-executeineditmode)


<hr>



### function GetMousePos 

```C++
virtual SR_NODISCARD SR_MATH_NS::FPoint SR_CORE_GUI_NS::EditorCamera::GetMousePos () override const
```



Implements [*SR\_GTYPES\_NS::Camera::GetMousePos*](classSR__GTYPES__NS_1_1Camera.md#function-getmousepos)


<hr>



### function SetSceneViewer 

```C++
inline void SR_CORE_GUI_NS::EditorCamera::SetSceneViewer (
    SceneViewer * pSceneViewer
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/GUI/EditorCamera.h`

