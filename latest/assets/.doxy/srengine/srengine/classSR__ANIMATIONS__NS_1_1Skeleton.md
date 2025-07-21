

# Class SR\_ANIMATIONS\_NS::Skeleton



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**Skeleton**](classSR__ANIMATIONS__NS_1_1Skeleton.md)








Inherits the following classes: [SR\_UTILS\_NS::Component](classSR__UTILS__NS_1_1Component.md),  [SR\_HTYPES\_NS::IRawMeshHolder](classSR__HTYPES__NS_1_1IRawMeshHolder.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Skeleton**](classSR__ANIMATIONS__NS_1_1Skeleton.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; RenderScene &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |


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
|  [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* | [**AddBone**](#function-addbone) ([**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* pParent, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name, bool recalculate) <br> |
| virtual SR\_NODISCARD bool | [**ExecuteInEditMode**](#function-executeineditmode) () override const<br> |
|  SR\_NODISCARD [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* | [**GetBone**](#function-getbone) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SR\_NODISCARD [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* | [**GetBoneByIndex**](#function-getbonebyindex) (uint16\_t index) const<br> |
|  SR\_NODISCARD uint64\_t | [**GetBoneIndex**](#function-getboneindex) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SR\_NODISCARD const std::vector&lt; [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* &gt; & | [**GetBones**](#function-getbones) () noexcept const<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) &gt; & | [**GetMatrices**](#function-getmatrices) () noexcept<br> |
|  const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrixByIndex**](#function-getmatrixbyindex) (uint16\_t index) noexcept<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) &gt; & | [**GetOffsets**](#function-getoffsets) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetOffsetsSSBO**](#function-getoffsetsssbo) () noexcept const<br> |
|  SR\_NODISCARD const ska::flat\_hash\_map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), uint16\_t &gt; & | [**GetOptimizedBones**](#function-getoptimizedbones) () noexcept const<br> |
|  SR\_NODISCARD const [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* | [**GetRootBone**](#function-getrootbone-12) () noexcept const<br> |
|  SR\_NODISCARD [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* | [**GetRootBone**](#function-getrootbone-22) () noexcept<br> |
|  SR\_NODISCARD bool | [**IsDebugEnabled**](#function-isdebugenabled) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDirtyMatrices**](#function-isdirtymatrices) () noexcept const<br> |
| virtual void | [**OnAttached**](#function-onattached) () override<br>_Вызывается после добавления компонента к игровому объекту_  |
| virtual void | [**OnDestroy**](#function-ondestroy) () override<br>_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._  |
|  void | [**OnPostLoad**](#function-onpostload) () override<br> |
| virtual void | [**OnRawMeshChanged**](#function-onrawmeshchanged) () override<br> |
|  bool | [**ReCalculateSkeleton**](#function-recalculateskeleton) () <br> |
|  void | [**SetDebugEnabled**](#function-setdebugenabled) (bool enabled) <br> |
|  SR\_NODISCARD [**Bone**](structSR__ANIMATIONS__NS_1_1Bone.md) \* | [**TryGetBone**](#function-trygetbone) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
| virtual void | [**Update**](#function-update) (float\_t dt) override<br> |
|   | [**~Skeleton**](#function-skeleton) () override<br> |


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




### typedef Ptr 

```C++
using SR_ANIMATIONS_NS::Skeleton::Ptr =  SR_HTYPES_NS::SharedPtr<Skeleton>;
```




<hr>



### typedef RenderScenePtr 

```C++
using SR_ANIMATIONS_NS::Skeleton::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<RenderScene>;
```




<hr>
## Public Functions Documentation




### function AddBone 

```C++
Bone * SR_ANIMATIONS_NS::Skeleton::AddBone (
    Bone * pParent,
    SR_UTILS_NS::StringAtom name,
    bool recalculate
) 
```




<hr>



### function ExecuteInEditMode 

```C++
inline virtual SR_NODISCARD bool SR_ANIMATIONS_NS::Skeleton::ExecuteInEditMode () override const
```



Implements [*SR\_UTILS\_NS::Component::ExecuteInEditMode*](classSR__UTILS__NS_1_1Component.md#function-executeineditmode)


<hr>



### function GetBone 

```C++
SR_NODISCARD Bone * SR_ANIMATIONS_NS::Skeleton::GetBone (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function GetBoneByIndex 

```C++
SR_NODISCARD Bone * SR_ANIMATIONS_NS::Skeleton::GetBoneByIndex (
    uint16_t index
) const
```




<hr>



### function GetBoneIndex 

```C++
SR_NODISCARD uint64_t SR_ANIMATIONS_NS::Skeleton::GetBoneIndex (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function GetBones 

```C++
inline SR_NODISCARD const std::vector< Bone * > & SR_ANIMATIONS_NS::Skeleton::GetBones () noexcept const
```




<hr>



### function GetMatrices 

```C++
SR_NODISCARD const std::vector< SR_MATH_NS::Matrix4x4 > & SR_ANIMATIONS_NS::Skeleton::GetMatrices () noexcept
```




<hr>



### function GetMatrixByIndex 

```C++
const SR_MATH_NS::Matrix4x4 & SR_ANIMATIONS_NS::Skeleton::GetMatrixByIndex (
    uint16_t index
) noexcept
```




<hr>



### function GetOffsets 

```C++
SR_NODISCARD const std::vector< SR_MATH_NS::Matrix4x4 > & SR_ANIMATIONS_NS::Skeleton::GetOffsets () noexcept const
```




<hr>



### function GetOffsetsSSBO 

```C++
SR_NODISCARD int32_t SR_ANIMATIONS_NS::Skeleton::GetOffsetsSSBO () noexcept const
```




<hr>



### function GetOptimizedBones 

```C++
SR_NODISCARD const ska::flat_hash_map< SR_UTILS_NS::StringAtom , uint16_t > & SR_ANIMATIONS_NS::Skeleton::GetOptimizedBones () noexcept const
```




<hr>



### function GetRootBone [1/2]

```C++
inline SR_NODISCARD const Bone * SR_ANIMATIONS_NS::Skeleton::GetRootBone () noexcept const
```




<hr>



### function GetRootBone [2/2]

```C++
inline SR_NODISCARD Bone * SR_ANIMATIONS_NS::Skeleton::GetRootBone () noexcept
```




<hr>



### function IsDebugEnabled 

```C++
inline SR_NODISCARD bool SR_ANIMATIONS_NS::Skeleton::IsDebugEnabled () noexcept const
```




<hr>



### function IsDirtyMatrices 

```C++
inline SR_NODISCARD bool SR_ANIMATIONS_NS::Skeleton::IsDirtyMatrices () noexcept const
```




<hr>



### function OnAttached 

_Вызывается после добавления компонента к игровому объекту_ 
```C++
virtual void SR_ANIMATIONS_NS::Skeleton::OnAttached () override
```



Implements [*SR\_UTILS\_NS::Component::OnAttached*](classSR__UTILS__NS_1_1Component.md#function-onattached)


<hr>



### function OnDestroy 

_Вызывается когда компонент убирается с объекта, либо объект уничтожается. Может произойти отложенно._ 
```C++
virtual void SR_ANIMATIONS_NS::Skeleton::OnDestroy () override
```



Implements [*SR\_UTILS\_NS::Component::OnDestroy*](classSR__UTILS__NS_1_1Component.md#function-ondestroy)


<hr>



### function OnPostLoad 

```C++
void SR_ANIMATIONS_NS::Skeleton::OnPostLoad () override
```




<hr>



### function OnRawMeshChanged 

```C++
virtual void SR_ANIMATIONS_NS::Skeleton::OnRawMeshChanged () override
```



Implements [*SR\_HTYPES\_NS::IRawMeshHolder::OnRawMeshChanged*](classSR__HTYPES__NS_1_1IRawMeshHolder.md#function-onrawmeshchanged)


<hr>



### function ReCalculateSkeleton 

```C++
bool SR_ANIMATIONS_NS::Skeleton::ReCalculateSkeleton () 
```




<hr>



### function SetDebugEnabled 

```C++
inline void SR_ANIMATIONS_NS::Skeleton::SetDebugEnabled (
    bool enabled
) 
```




<hr>



### function TryGetBone 

```C++
SR_NODISCARD Bone * SR_ANIMATIONS_NS::Skeleton::TryGetBone (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function Update 

```C++
virtual void SR_ANIMATIONS_NS::Skeleton::Update (
    float_t dt
) override
```



Implements [*SR\_UTILS\_NS::Component::Update*](classSR__UTILS__NS_1_1Component.md#function-update)


<hr>



### function ~Skeleton 

```C++
SR_ANIMATIONS_NS::Skeleton::~Skeleton () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/Skeleton.h`

