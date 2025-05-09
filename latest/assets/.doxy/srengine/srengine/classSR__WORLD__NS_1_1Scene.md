

# Class SR\_WORLD\_NS::Scene



[**ClassList**](annotated.md) **>** [**SR\_WORLD\_NS**](namespaceSR__WORLD__NS.md) **>** [**Scene**](classSR__WORLD__NS_1_1Scene.md)








Inherits the following classes: [SR\_UTILS\_NS::IComponentable](classSR__UTILS__NS_1_1IComponentable.md)


Inherited by the following classes: [SR\_CORE\_NS::World](classSR__CORE__NS_1_1World.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; GameObject &gt; | [**GameObjectPtr**](#typedef-gameobjectptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SceneLogic**](classSR__WORLD__NS_1_1SceneLogic.md) &gt; | [**SceneLogicPtr**](#typedef-scenelogicptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**SceneObjectPtr**](#typedef-sceneobjectptr)  <br> |
| typedef std::vector&lt; SceneObjectPtr &gt; | [**SceneObjects**](#typedef-sceneobjects)  <br> |
| typedef [**SR\_UTILS\_NS::IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) | [**Super**](#typedef-super)  <br> |


## Public Types inherited from SR_UTILS_NS::IComponentable

See [SR\_UTILS\_NS::IComponentable](classSR__UTILS__NS_1_1IComponentable.md)

| Type | Name |
| ---: | :--- |
| typedef [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) | [**OriginType**](classSR__UTILS__NS_1_1IComponentable.md#typedef-origintype)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) &gt; | [**Ptr**](classSR__UTILS__NS_1_1IComponentable.md#typedef-ptr)  <br> |
| typedef [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**ScenePtr**](classSR__UTILS__NS_1_1IComponentable.md#typedef-sceneptr)  <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC const Path | [**NewPrefabPath**](#variable-newprefabpath)   = `"Scenes/New-cache-prefab"`<br>_NOLINT._  |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC const Path | [**NewScenePath**](#variable-newscenepath)   = `"Scenes/New-cache-scene"`<br>_NOLINT._  |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC const Path | [**RuntimeScenePath**](#variable-runtimescenepath)   = `"Scenes/Runtime-cache-scene"`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Destroy**](#function-destroy) () <br> |
|  SceneObjectPtr | [**Find**](#function-find-14) (const std::string & name) <br> |
|  SceneObjectPtr | [**Find**](#function-find-24) (const char \* name) <br> |
|  SceneObjectPtr | [**Find**](#function-find-34) (uint64\_t hashName) <br> |
|  SceneObjectPtr | [**Find**](#function-find-44) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SceneObjectPtr | [**FindByComponent**](#function-findbycomponent) (const std::string & name) <br> |
| virtual GameObjectPtr | [**FindOrInstanceGameObject**](#function-findorinstancegameobject) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SR\_NODISCARD Path | [**GetAbsPath**](#function-getabspath-12) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetDataStorage**](#function-getdatastorage-12) () <br> |
|  SR\_NODISCARD const [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetDataStorage**](#function-getdatastorage-22) () const<br> |
|  SR\_NODISCARD const SR\_UTILS\_NS::EntityController::Ptr & | [**GetEntityController**](#function-getentitycontroller) () const<br> |
|  SR\_NODISCARD SR\_INLINE SceneLogicPtr | [**GetLogicBase**](#function-getlogicbase) () const<br> |
|  SR\_NODISCARD std::string | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD Path | [**GetPath**](#function-getpath) () const<br> |
|  SceneObjects & | [**GetRootSceneObjects**](#function-getrootsceneobjects) () <br> |
| virtual IComponentable::ScenePtr | [**GetScene**](#function-getscene) () override const<br> |
|  SR\_NODISCARD SR\_INLINE [**SceneUpdater**](classSR__WORLD__NS_1_1SceneUpdater.md) \* | [**GetSceneUpdater**](#function-getsceneupdater) () const<br> |
|  void | [**Init**](#function-init) () <br> |
| virtual SceneObjectPtr | [**Instance**](#function-instance) (const Types::RawMesh \* rawMesh) <br> |
| virtual SceneObjectPtr | [**InstanceFromFile**](#function-instancefromfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
| virtual GameObjectPtr | [**InstanceGameObject**](#function-instancegameobject) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
| virtual SR\_NODISCARD bool | [**IsPausedMode**](#function-ispausedmode) () const<br>_На паузе ли сцена (если запущена)_  |
| virtual SR\_NODISCARD bool | [**IsPlayingMode**](#function-isplayingmode) () const<br>_Запущена ли сцена_  |
| virtual SR\_NODISCARD bool | [**IsPrefab**](#function-isprefab) () noexcept override const<br> |
|  void | [**OnChanged**](#function-onchanged) () <br> |
|  void | [**OnPostLoad**](#function-onpostload) () override<br> |
|  void | [**Prepare**](#function-prepare) () <br> |
|  void | [**RegisterSceneObject**](#function-registersceneobject) (const SceneObjectPtr & pSO) <br> |
|  bool | [**Reload**](#function-reload) () <br> |
|  bool | [**Remove**](#function-remove-12) (const SceneObjectPtr & gameObject) <br> |
|  void | [**Remove**](#function-remove-22) (const Component::Ptr & pComponent) <br> |
|  bool | [**SaveScene**](#function-savescene) () <br> |
|  bool | [**SaveSceneAt**](#function-savesceneat) (const Path & path) <br> |
|   | [**Scene**](#function-scene) () <br>_NOLINT._  |
| virtual bool | [**SetDirty**](#function-setdirty) (bool dirty) override<br> |
|  void | [**SetPath**](#function-setpath) (const Path & path) <br> |
|   | [**~Scene**](#function-scene) () override<br> |


## Public Functions inherited from SR_UTILS_NS::IComponentable

See [SR\_UTILS\_NS::IComponentable](classSR__UTILS__NS_1_1IComponentable.md)

| Type | Name |
| ---: | :--- |
| virtual bool | [**AddComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-addcomponent-12) (const Component::Ptr & pComponent) <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**AddComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-addcomponent-22) () <br> |
| virtual void | [**Awake**](classSR__UTILS__NS_1_1IComponentable.md#function-awake) (bool force, bool isPaused) noexcept<br> |
| virtual void | [**CheckActivity**](classSR__UTILS__NS_1_1IComponentable.md#function-checkactivity) (bool force) noexcept<br> |
| virtual bool | [**ContainsComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-containscomponent) (const std::string & name) <br> |
| virtual void | [**ForEachComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-foreachcomponent-12) (const std::function&lt; bool(const Component::Ptr &)&gt; & fun) const<br> |
| virtual void | [**ForEachComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-foreachcomponent-22) (const std::function&lt; bool(Component::Ptr &)&gt; & fun) <br> |
| virtual Component::Ptr | [**GetComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-getcomponent-13) (const std::string & name) <br> |
| virtual Component::Ptr | [**GetComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-getcomponent-23) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-getcomponent-33) () <br> |
|  SR\_NODISCARD int32\_t | [**GetComponentIndex**](classSR__UTILS__NS_1_1IComponentable.md#function-getcomponentindex) (const Component::Ptr & pComponent) const<br> |
|  SR\_NODISCARD const std::vector&lt; Component::Ptr &gt; & | [**GetComponents**](classSR__UTILS__NS_1_1IComponentable.md#function-getcomponents) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetComponentsCount**](classSR__UTILS__NS_1_1IComponentable.md#function-getcomponentscount) () noexcept const<br> |
| virtual Component::Ptr | [**GetOrCreateComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-getorcreatecomponent-12) (const std::string & name) <br> |
| virtual Component::Ptr | [**GetOrCreateComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-getorcreatecomponent-22) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
| virtual SR\_NODISCARD ScenePtr | [**GetScene**](classSR__UTILS__NS_1_1IComponentable.md#function-getscene) () const<br> |
|  SR\_NODISCARD bool | [**HasComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-hascomponent) (const Component::Ptr & pComponent) const<br> |
|   | [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md#function-icomponentable) () = default<br> |
| virtual SR\_NODISCARD bool | [**IsActive**](classSR__UTILS__NS_1_1IComponentable.md#function-isactive) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsDestroyed**](classSR__UTILS__NS_1_1IComponentable.md#function-isdestroyed) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDirty**](classSR__UTILS__NS_1_1IComponentable.md#function-isdirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsPrefab**](classSR__UTILS__NS_1_1IComponentable.md#function-isprefab) () noexcept const<br> |
| virtual bool | [**MoveComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-movecomponent) (const Component::Ptr & pComponent, int32\_t offset) <br> |
| virtual void | [**OnMatrixDirty**](classSR__UTILS__NS_1_1IComponentable.md#function-onmatrixdirty) () <br> |
|  void | [**OnPostLoad**](classSR__UTILS__NS_1_1IComponentable.md#function-onpostload) () override<br> |
| virtual void | [**OnPriorityChanged**](classSR__UTILS__NS_1_1IComponentable.md#function-onprioritychanged) () <br> |
| virtual bool | [**PostLoad**](classSR__UTILS__NS_1_1IComponentable.md#function-postload) (bool force) <br>_Вызывает OnAttached у компонентов загруженных через LoadComponent._  |
| virtual bool | [**RemoveComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-removecomponent) (const Component::Ptr & pComponent) <br> |
|  void | [**RemoveComponents**](classSR__UTILS__NS_1_1IComponentable.md#function-removecomponents) () <br> |
| virtual bool | [**SetDirty**](classSR__UTILS__NS_1_1IComponentable.md#function-setdirty) (bool dirty) <br> |
| virtual void | [**Start**](classSR__UTILS__NS_1_1IComponentable.md#function-start) (bool force) noexcept<br> |
|   | [**~IComponentable**](classSR__UTILS__NS_1_1IComponentable.md#function-icomponentable) () override<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  Scene::Ptr | [**CreateEmptyScene**](#function-createemptyscene) () <br> |
|  Path | [**GetAbsPath**](#function-getabspath-22) (const Path & path) <br> |
|  bool | [**IsExists**](#function-isexists) (const Path & path) <br> |
|  Scene::Ptr | [**LoadScene**](#function-loadscene) (const Path & path) <br> |
|  Scene::Ptr | [**NewScene**](#function-newscene) (const Path & path, SceneLogicType type) <br> |














## Protected Attributes inherited from SR_UTILS_NS::IComponentable

See [SR\_UTILS\_NS::IComponentable](classSR__UTILS__NS_1_1IComponentable.md)

| Type | Name |
| ---: | :--- |
|  std::vector&lt; Component::Ptr &gt; | [**m\_components**](classSR__UTILS__NS_1_1IComponentable.md#variable-m_components)  <br> |
































## Protected Functions inherited from SR_UTILS_NS::IComponentable

See [SR\_UTILS\_NS::IComponentable](classSR__UTILS__NS_1_1IComponentable.md)

| Type | Name |
| ---: | :--- |
|  void | [**DestroyComponent**](classSR__UTILS__NS_1_1IComponentable.md#function-destroycomponent) (const Component::Ptr & pComponent) <br> |






## Public Types Documentation




### typedef GameObjectPtr 

```C++
using SR_WORLD_NS::Scene::GameObjectPtr =  SR_HTYPES_NS::SharedPtr<GameObject>;
```




<hr>



### typedef Ptr 

```C++
using SR_WORLD_NS::Scene::Ptr =  SR_HTYPES_NS::SharedPtr<Scene>;
```




<hr>



### typedef SceneLogicPtr 

```C++
using SR_WORLD_NS::Scene::SceneLogicPtr =  SR_HTYPES_NS::SharedPtr<SceneLogic>;
```




<hr>



### typedef SceneObjectPtr 

```C++
using SR_WORLD_NS::Scene::SceneObjectPtr =  SR_HTYPES_NS::SharedPtr<SceneObject>;
```




<hr>



### typedef SceneObjects 

```C++
using SR_WORLD_NS::Scene::SceneObjects =  std::vector<SceneObjectPtr>;
```




<hr>



### typedef Super 

```C++
using SR_WORLD_NS::Scene::Super =  SR_UTILS_NS::IComponentable;
```




<hr>
## Public Attributes Documentation




### variable NewPrefabPath 

_NOLINT._ 
```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC const Path SR_WORLD_NS::Scene::NewPrefabPath;
```




<hr>



### variable NewScenePath 

_NOLINT._ 
```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC const Path SR_WORLD_NS::Scene::NewScenePath;
```




<hr>



### variable RuntimeScenePath 

```C++
SR_MAYBE_UNUSED SR_INLINE_STATIC const Path SR_WORLD_NS::Scene::RuntimeScenePath;
```




<hr>
## Public Functions Documentation




### function Destroy 

```C++
bool SR_WORLD_NS::Scene::Destroy () 
```




<hr>



### function Find [1/4]

```C++
SceneObjectPtr SR_WORLD_NS::Scene::Find (
    const std::string & name
) 
```




<hr>



### function Find [2/4]

```C++
SceneObjectPtr SR_WORLD_NS::Scene::Find (
    const char * name
) 
```




<hr>



### function Find [3/4]

```C++
SceneObjectPtr SR_WORLD_NS::Scene::Find (
    uint64_t hashName
) 
```




<hr>



### function Find [4/4]

```C++
SceneObjectPtr SR_WORLD_NS::Scene::Find (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function FindByComponent 

```C++
SceneObjectPtr SR_WORLD_NS::Scene::FindByComponent (
    const std::string & name
) 
```




<hr>



### function FindOrInstanceGameObject 

```C++
virtual GameObjectPtr SR_WORLD_NS::Scene::FindOrInstanceGameObject (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function GetAbsPath [1/2]

```C++
SR_NODISCARD Path SR_WORLD_NS::Scene::GetAbsPath () const
```




<hr>



### function GetDataStorage [1/2]

```C++
SR_NODISCARD SR_HTYPES_NS::DataStorage & SR_WORLD_NS::Scene::GetDataStorage () 
```




<hr>



### function GetDataStorage [2/2]

```C++
SR_NODISCARD const SR_HTYPES_NS::DataStorage & SR_WORLD_NS::Scene::GetDataStorage () const
```




<hr>



### function GetEntityController 

```C++
inline SR_NODISCARD const SR_UTILS_NS::EntityController::Ptr & SR_WORLD_NS::Scene::GetEntityController () const
```




<hr>



### function GetLogicBase 

```C++
inline SR_NODISCARD SR_INLINE SceneLogicPtr SR_WORLD_NS::Scene::GetLogicBase () const
```




<hr>



### function GetName 

```C++
SR_NODISCARD std::string SR_WORLD_NS::Scene::GetName () const
```




<hr>



### function GetPath 

```C++
inline SR_NODISCARD Path SR_WORLD_NS::Scene::GetPath () const
```




<hr>



### function GetRootSceneObjects 

```C++
SceneObjects & SR_WORLD_NS::Scene::GetRootSceneObjects () 
```




<hr>



### function GetScene 

```C++
inline virtual IComponentable::ScenePtr SR_WORLD_NS::Scene::GetScene () override const
```



Implements [*SR\_UTILS\_NS::IComponentable::GetScene*](classSR__UTILS__NS_1_1IComponentable.md#function-getscene)


<hr>



### function GetSceneUpdater 

```C++
inline SR_NODISCARD SR_INLINE SceneUpdater * SR_WORLD_NS::Scene::GetSceneUpdater () const
```




<hr>



### function Init 

```C++
void SR_WORLD_NS::Scene::Init () 
```




<hr>



### function Instance 

```C++
virtual SceneObjectPtr SR_WORLD_NS::Scene::Instance (
    const Types::RawMesh * rawMesh
) 
```




<hr>



### function InstanceFromFile 

```C++
virtual SceneObjectPtr SR_WORLD_NS::Scene::InstanceFromFile (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function InstanceGameObject 

```C++
virtual GameObjectPtr SR_WORLD_NS::Scene::InstanceGameObject (
    SR_UTILS_NS::StringAtom name
) 
```




<hr>



### function IsPausedMode 

_На паузе ли сцена (если запущена)_ 
```C++
inline virtual SR_NODISCARD bool SR_WORLD_NS::Scene::IsPausedMode () const
```




<hr>



### function IsPlayingMode 

_Запущена ли сцена_ 
```C++
inline virtual SR_NODISCARD bool SR_WORLD_NS::Scene::IsPlayingMode () const
```




<hr>



### function IsPrefab 

```C++
virtual SR_NODISCARD bool SR_WORLD_NS::Scene::IsPrefab () noexcept override const
```



Implements [*SR\_UTILS\_NS::IComponentable::IsPrefab*](classSR__UTILS__NS_1_1IComponentable.md#function-isprefab)


<hr>



### function OnChanged 

```C++
void SR_WORLD_NS::Scene::OnChanged () 
```




<hr>



### function OnPostLoad 

```C++
void SR_WORLD_NS::Scene::OnPostLoad () override
```




<hr>



### function Prepare 

```C++
void SR_WORLD_NS::Scene::Prepare () 
```




<hr>



### function RegisterSceneObject 

```C++
void SR_WORLD_NS::Scene::RegisterSceneObject (
    const SceneObjectPtr & pSO
) 
```




<hr>



### function Reload 

```C++
bool SR_WORLD_NS::Scene::Reload () 
```




<hr>



### function Remove [1/2]

```C++
bool SR_WORLD_NS::Scene::Remove (
    const SceneObjectPtr & gameObject
) 
```




<hr>



### function Remove [2/2]

```C++
void SR_WORLD_NS::Scene::Remove (
    const Component::Ptr & pComponent
) 
```




<hr>



### function SaveScene 

```C++
bool SR_WORLD_NS::Scene::SaveScene () 
```




<hr>



### function SaveSceneAt 

```C++
bool SR_WORLD_NS::Scene::SaveSceneAt (
    const Path & path
) 
```




<hr>



### function Scene 

_NOLINT._ 
```C++
SR_WORLD_NS::Scene::Scene () 
```




<hr>



### function SetDirty 

```C++
virtual bool SR_WORLD_NS::Scene::SetDirty (
    bool dirty
) override
```



Implements [*SR\_UTILS\_NS::IComponentable::SetDirty*](classSR__UTILS__NS_1_1IComponentable.md#function-setdirty)


<hr>



### function SetPath 

```C++
void SR_WORLD_NS::Scene::SetPath (
    const Path & path
) 
```




<hr>



### function ~Scene 

```C++
SR_WORLD_NS::Scene::~Scene () override
```




<hr>
## Public Static Functions Documentation




### function CreateEmptyScene 

```C++
static Scene::Ptr SR_WORLD_NS::Scene::CreateEmptyScene () 
```




<hr>



### function GetAbsPath [2/2]

```C++
static Path SR_WORLD_NS::Scene::GetAbsPath (
    const Path & path
) 
```




<hr>



### function IsExists 

```C++
static bool SR_WORLD_NS::Scene::IsExists (
    const Path & path
) 
```




<hr>



### function LoadScene 

```C++
static Scene::Ptr SR_WORLD_NS::Scene::LoadScene (
    const Path & path
) 
```




<hr>



### function NewScene 

```C++
static Scene::Ptr SR_WORLD_NS::Scene::NewScene (
    const Path & path,
    SceneLogicType type
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/World/Scene.h`

