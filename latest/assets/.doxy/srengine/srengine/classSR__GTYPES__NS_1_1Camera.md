

# Class SR\_GTYPES\_NS::Camera



[**ClassList**](annotated.md) **>** [**SR\_GTYPES\_NS**](namespaceSR__GTYPES__NS.md) **>** [**Camera**](classSR__GTYPES__NS_1_1Camera.md)








Inherits the following classes: [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)


Inherited by the following classes: [SR\_CORE\_GUI\_NS::EditorCamera](classSR__CORE__GUI__NS_1_1EditorCamera.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Camera**](classSR__GTYPES__NS_1_1Camera.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


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
|  SR\_NODISCARD float\_t | [**CalculateScreenFactor**](#function-calculatescreenfactor-12) (const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & modelMatrix, float\_t sizeClipSpace, bool orthogonal) const<br> |
|  SR\_NODISCARD float\_t | [**CalculateScreenFactor**](#function-calculatescreenfactor-22) (const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & modelMatrix, const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & viewMatrix, float\_t sizeClipSpace, bool orthogonal) const<br> |
|   | [**Camera**](#function-camera) () <br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetAspect**](#function-getaspect) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE SR\_MATH\_NS::FVector3 | [**GetCameraDir**](#function-getcameradir) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE SR\_MATH\_NS::FVector3 | [**GetCameraEye**](#function-getcameraeye) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetFOV**](#function-getfov) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetFar**](#function-getfar) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE glm::vec3 | [**GetGLPosition**](#function-getglposition) () const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**GetImGuizmoView**](#function-getimguizmoview) () noexcept const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::FPoint | [**GetMousePos**](#function-getmousepos) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE float\_t | [**GetNear**](#function-getnear) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetOrthogonal**](#function-getorthogonal) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const SR\_MATH\_NS::FVector3 & | [**GetPosition**](#function-getposition) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE int32\_t | [**GetPriority**](#function-getpriority) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetProjection**](#function-getprojection) () noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetProjectionNoFOV**](#function-getprojectionnofov) () noexcept const<br> |
|  SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  SR\_NODISCARD IRenderTechnique \* | [**GetRenderTechnique**](#function-getrendertechnique) () <br> |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetRenderTechniquePath**](#function-getrendertechniquepath) () <br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Quaternion**](classSR__MATH__NS_1_1Quaternion.md) & | [**GetRotation**](#function-getrotation) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Ray**](structSR__MATH__NS_1_1Ray.md) | [**GetScreenRay**](#function-getscreenray-12) (const SR\_MATH\_NS::FPoint & screenPos, bool orthogonal) const<br> |
|  SR\_NODISCARD [**SR\_MATH\_NS::Ray**](structSR__MATH__NS_1_1Ray.md) | [**GetScreenRay**](#function-getscreenray-22) (float\_t x, float\_t y, bool orthogonal) const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE SR\_MATH\_NS::UVector2 | [**GetSize**](#function-getsize) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetView**](#function-getview) () noexcept const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector3 & | [**GetViewDirection**](#function-getviewdirection-12) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetViewDirection**](#function-getviewdirection-22) (const SR\_MATH\_NS::FVector3 & pos) noexcept const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE SR\_MATH\_NS::FVector3 | [**GetViewPosition**](#function-getviewposition) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetViewTranslate**](#function-getviewtranslate) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsEditorCamera**](#function-iseditorcamera) () noexcept const<br> |
| virtual void | [**OnAttached**](#function-onattached) () override<br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnMatrixDirty**](#function-onmatrixdirty) () override<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**ScreenToWorldPoint**](#function-screentoworldpoint-13) (const SR\_MATH\_NS::FVector3 & screenPos) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**ScreenToWorldPoint**](#function-screentoworldpoint-23) (const SR\_MATH\_NS::FVector2 & screenPos) const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**ScreenToWorldPoint**](#function-screentoworldpoint-33) (const SR\_MATH\_NS::FVector2 & screenPos, float\_t depth) const<br> |
|  void | [**SetFOV**](#function-setfov) (float\_t value) <br> |
|  void | [**SetFar**](#function-setfar) (float\_t value) <br> |
|  void | [**SetNear**](#function-setnear) (float\_t value) <br> |
|  void | [**SetPriority**](#function-setpriority) (int32\_t priority) <br> |
|  void | [**SetRenderTechnique**](#function-setrendertechnique) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
| virtual void | [**Start**](#function-start) () override<br> |
|  SR\_NODISCARD RenderScenePtr | [**TryGetRenderScene**](#function-trygetrenderscene) () const<br> |
| virtual void | [**Update**](#function-update) (float\_t dt) override<br> |
|  void | [**UpdateProjection**](#function-updateprojection-12) (uint32\_t w, uint32\_t h) <br> |
|   | [**~Camera**](#function-camera) () override<br> |


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
| virtual void | [**OnDestroy**](#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
| virtual void | [**OnDisable**](#function-ondisable) () override<br> |
| virtual void | [**OnEnable**](#function-onenable) () override<br> |
|  void | [**UpdateProjection**](#function-updateprojection-22) () <br> |
|  void | [**UpdateView**](#function-updateview) () noexcept<br> |


## Protected Functions inherited from SR_UTILS_NS::Component

See [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md)

| Type | Name |
| ---: | :--- |
|  void | [**SetParent**](classSR__UTILS__NS_1_1Component.md#function-setparent) ([**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) \* pParent) <br> |






## Public Types Documentation




### typedef Ptr 

```C++
using SR_GTYPES_NS::Camera::Ptr =  SR_HTYPES_NS::SharedPtr<Camera>;
```




<hr>
## Public Functions Documentation




### function CalculateScreenFactor [1/2]

```C++
SR_NODISCARD float_t SR_GTYPES_NS::Camera::CalculateScreenFactor (
    const SR_MATH_NS::Matrix4x4 & modelMatrix,
    float_t sizeClipSpace,
    bool orthogonal
) const
```




<hr>



### function CalculateScreenFactor [2/2]

```C++
SR_NODISCARD float_t SR_GTYPES_NS::Camera::CalculateScreenFactor (
    const SR_MATH_NS::Matrix4x4 & modelMatrix,
    const SR_MATH_NS::Matrix4x4 & viewMatrix,
    float_t sizeClipSpace,
    bool orthogonal
) const
```




<hr>



### function Camera 

```C++
SR_GTYPES_NS::Camera::Camera () 
```




<hr>



### function GetAspect 

```C++
inline SR_NODISCARD SR_FORCE_INLINE float_t SR_GTYPES_NS::Camera::GetAspect () const
```




<hr>



### function GetCameraDir 

```C++
SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::FVector3 SR_GTYPES_NS::Camera::GetCameraDir () const
```




<hr>



### function GetCameraEye 

```C++
SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::FVector3 SR_GTYPES_NS::Camera::GetCameraEye () const
```




<hr>



### function GetFOV 

```C++
inline SR_NODISCARD SR_FORCE_INLINE float_t SR_GTYPES_NS::Camera::GetFOV () const
```




<hr>



### function GetFar 

```C++
inline SR_NODISCARD SR_FORCE_INLINE float_t SR_GTYPES_NS::Camera::GetFar () const
```




<hr>



### function GetGLPosition 

```C++
inline SR_NODISCARD SR_FORCE_INLINE glm::vec3 SR_GTYPES_NS::Camera::GetGLPosition () const
```




<hr>



### function GetImGuizmoView 

```C++
SR_NODISCARD SR_MATH_NS::Matrix4x4 SR_GTYPES_NS::Camera::GetImGuizmoView () noexcept const
```




<hr>



### function GetMousePos 

```C++
virtual SR_NODISCARD SR_MATH_NS::FPoint SR_GTYPES_NS::Camera::GetMousePos () const
```




<hr>



### function GetNear 

```C++
inline SR_NODISCARD SR_FORCE_INLINE float_t SR_GTYPES_NS::Camera::GetNear () const
```




<hr>



### function GetOrthogonal 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4 & SR_GTYPES_NS::Camera::GetOrthogonal () noexcept const
```




<hr>



### function GetPosition 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::FVector3 & SR_GTYPES_NS::Camera::GetPosition () const
```




<hr>



### function GetPriority 

```C++
inline SR_NODISCARD SR_FORCE_INLINE int32_t SR_GTYPES_NS::Camera::GetPriority () const
```




<hr>



### function GetProjection 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4 & SR_GTYPES_NS::Camera::GetProjection () noexcept const
```




<hr>



### function GetProjectionNoFOV 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4 & SR_GTYPES_NS::Camera::GetProjectionNoFOV () noexcept const
```




<hr>



### function GetRenderScene 

```C++
SR_NODISCARD RenderScenePtr SR_GTYPES_NS::Camera::GetRenderScene () const
```




<hr>



### function GetRenderTechnique 

```C++
SR_NODISCARD IRenderTechnique * SR_GTYPES_NS::Camera::GetRenderTechnique () 
```




<hr>



### function GetRenderTechniquePath 

```C++
SR_NODISCARD const SR_UTILS_NS::Path & SR_GTYPES_NS::Camera::GetRenderTechniquePath () 
```




<hr>



### function GetRotation 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Quaternion & SR_GTYPES_NS::Camera::GetRotation () noexcept const
```




<hr>



### function GetScreenRay [1/2]

```C++
SR_NODISCARD SR_MATH_NS::Ray SR_GTYPES_NS::Camera::GetScreenRay (
    const SR_MATH_NS::FPoint & screenPos,
    bool orthogonal
) const
```




<hr>



### function GetScreenRay [2/2]

```C++
SR_NODISCARD SR_MATH_NS::Ray SR_GTYPES_NS::Camera::GetScreenRay (
    float_t x,
    float_t y,
    bool orthogonal
) const
```




<hr>



### function GetSize 

```C++
inline SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::UVector2 SR_GTYPES_NS::Camera::GetSize () const
```




<hr>



### function GetView 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4 & SR_GTYPES_NS::Camera::GetView () noexcept const
```




<hr>



### function GetViewDirection [1/2]

```C++
SR_NODISCARD const SR_MATH_NS::FVector3 & SR_GTYPES_NS::Camera::GetViewDirection () const
```




<hr>



### function GetViewDirection [2/2]

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_GTYPES_NS::Camera::GetViewDirection (
    const SR_MATH_NS::FVector3 & pos
) noexcept const
```




<hr>



### function GetViewPosition 

```C++
SR_NODISCARD SR_FORCE_INLINE SR_MATH_NS::FVector3 SR_GTYPES_NS::Camera::GetViewPosition () const
```




<hr>



### function GetViewTranslate 

```C++
inline SR_NODISCARD SR_FORCE_INLINE const SR_MATH_NS::Matrix4x4 & SR_GTYPES_NS::Camera::GetViewTranslate () noexcept const
```




<hr>



### function IsEditorCamera 

```C++
inline virtual SR_NODISCARD bool SR_GTYPES_NS::Camera::IsEditorCamera () noexcept const
```




<hr>



### function OnAttached 

_Вызывается после добавления компонента к игровому объекту_ 
```C++
virtual void SR_GTYPES_NS::Camera::OnAttached () override
```



Implements [*SR\_UTILS\_NS::Component::OnAttached*](classSR__UTILS__NS_1_1Component.md#function-onattached)


<hr>



### function OnMatrixDirty 

```C++
virtual void SR_GTYPES_NS::Camera::OnMatrixDirty () override
```



Implements [*SR\_UTILS\_NS::Component::OnMatrixDirty*](classSR__UTILS__NS_1_1Component.md#function-onmatrixdirty)


<hr>



### function ScreenToWorldPoint [1/3]

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_GTYPES_NS::Camera::ScreenToWorldPoint (
    const SR_MATH_NS::FVector3 & screenPos
) const
```




<hr>



### function ScreenToWorldPoint [2/3]

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_GTYPES_NS::Camera::ScreenToWorldPoint (
    const SR_MATH_NS::FVector2 & screenPos
) const
```




<hr>



### function ScreenToWorldPoint [3/3]

```C++
SR_NODISCARD SR_MATH_NS::FVector3 SR_GTYPES_NS::Camera::ScreenToWorldPoint (
    const SR_MATH_NS::FVector2 & screenPos,
    float_t depth
) const
```




<hr>



### function SetFOV 

```C++
void SR_GTYPES_NS::Camera::SetFOV (
    float_t value
) 
```




<hr>



### function SetFar 

```C++
void SR_GTYPES_NS::Camera::SetFar (
    float_t value
) 
```




<hr>



### function SetNear 

```C++
void SR_GTYPES_NS::Camera::SetNear (
    float_t value
) 
```




<hr>



### function SetPriority 

```C++
void SR_GTYPES_NS::Camera::SetPriority (
    int32_t priority
) 
```




<hr>



### function SetRenderTechnique 

```C++
void SR_GTYPES_NS::Camera::SetRenderTechnique (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function Start 

```C++
virtual void SR_GTYPES_NS::Camera::Start () override
```



Implements [*SR\_UTILS\_NS::Component::Start*](classSR__UTILS__NS_1_1Component.md#function-start)


<hr>



### function TryGetRenderScene 

```C++
SR_NODISCARD RenderScenePtr SR_GTYPES_NS::Camera::TryGetRenderScene () const
```




<hr>



### function Update 

```C++
virtual void SR_GTYPES_NS::Camera::Update (
    float_t dt
) override
```



Implements [*SR\_UTILS\_NS::Component::Update*](classSR__UTILS__NS_1_1Component.md#function-update)


<hr>



### function UpdateProjection [1/2]

```C++
void SR_GTYPES_NS::Camera::UpdateProjection (
    uint32_t w,
    uint32_t h
) 
```




<hr>



### function ~Camera 

```C++
SR_GTYPES_NS::Camera::~Camera () override
```




<hr>
## Protected Functions Documentation




### function OnDestroy 

_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._ 
```C++
virtual void SR_GTYPES_NS::Camera::OnDestroy () override
```



Implements [*SR\_UTILS\_NS::Component::OnDestroy*](classSR__UTILS__NS_1_1Component.md#function-ondestroy)


<hr>



### function OnDisable 

```C++
virtual void SR_GTYPES_NS::Camera::OnDisable () override
```



Implements [*SR\_UTILS\_NS::Component::OnDisable*](classSR__UTILS__NS_1_1Component.md#function-ondisable)


<hr>



### function OnEnable 

```C++
virtual void SR_GTYPES_NS::Camera::OnEnable () override
```



Implements [*SR\_UTILS\_NS::Component::OnEnable*](classSR__UTILS__NS_1_1Component.md#function-onenable)


<hr>



### function UpdateProjection [2/2]

```C++
void SR_GTYPES_NS::Camera::UpdateProjection () 
```




<hr>



### function UpdateView 

```C++
void SR_GTYPES_NS::Camera::UpdateView () noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Types/Camera.h`

