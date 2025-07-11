

# Class SR\_CORE\_NS::World



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**World**](classSR__CORE__NS_1_1World.md)








Inherits the following classes: [SR\_WORLD\_NS::Scene](classSR__WORLD__NS_1_1Scene.md)
















## Public Types inherited from SR_WORLD_NS::Scene

See [SR\_WORLD\_NS::Scene](classSR__WORLD__NS_1_1Scene.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; GameObject &gt; | [**GameObjectPtr**](classSR__WORLD__NS_1_1Scene.md#typedef-gameobjectptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**Ptr**](classSR__WORLD__NS_1_1Scene.md#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SceneLogic**](classSR__WORLD__NS_1_1SceneLogic.md) &gt; | [**SceneLogicPtr**](classSR__WORLD__NS_1_1Scene.md#typedef-scenelogicptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; SceneObject &gt; | [**SceneObjectPtr**](classSR__WORLD__NS_1_1Scene.md#typedef-sceneobjectptr)  <br> |
| typedef std::vector&lt; SceneObjectPtr &gt; | [**SceneObjects**](classSR__WORLD__NS_1_1Scene.md#typedef-sceneobjects)  <br> |
| typedef [**SR\_UTILS\_NS::IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) | [**Super**](classSR__WORLD__NS_1_1Scene.md#typedef-super)  <br> |


## Public Types inherited from SR_UTILS_NS::IComponentable

See [SR\_UTILS\_NS::IComponentable](classSR__UTILS__NS_1_1IComponentable.md)

| Type | Name |
| ---: | :--- |
| typedef [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) | [**OriginType**](classSR__UTILS__NS_1_1IComponentable.md#typedef-origintype)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) &gt; | [**Ptr**](classSR__UTILS__NS_1_1IComponentable.md#typedef-ptr)  <br> |
| typedef [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**ScenePtr**](classSR__UTILS__NS_1_1IComponentable.md#typedef-sceneptr)  <br> |










## Public Attributes inherited from SR_WORLD_NS::Scene

See [SR\_WORLD\_NS::Scene](classSR__WORLD__NS_1_1Scene.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC const std::string | [**NewPrefabPath**](classSR__WORLD__NS_1_1Scene.md#variable-newprefabpath)   = `"Scenes/New-cache-prefab"`<br>_NOLINT._  |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC const std::string | [**NewScenePath**](classSR__WORLD__NS_1_1Scene.md#variable-newscenepath)   = `"Scenes/New-cache-scene"`<br>_NOLINT._  |
|  SR\_MAYBE\_UNUSED SR\_INLINE\_STATIC const std::string | [**RuntimeScenePath**](classSR__WORLD__NS_1_1Scene.md#variable-runtimescenepath)   = `"Scenes/Runtime-cache-scene"`<br> |














































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_UTILS\_NS::SceneObject::Ptr | [**Instance**](#function-instance) (const [**SR\_HTYPES\_NS::RawMesh**](classSR__HTYPES__NS_1_1RawMesh.md) \* rawMesh) override<br> |
|   | [**World**](#function-world) () = default<br> |


## Public Functions inherited from SR_WORLD_NS::Scene

See [SR\_WORLD\_NS::Scene](classSR__WORLD__NS_1_1Scene.md)

| Type | Name |
| ---: | :--- |
|  bool | [**Destroy**](classSR__WORLD__NS_1_1Scene.md#function-destroy) () <br> |
|  SceneObjectPtr | [**Find**](classSR__WORLD__NS_1_1Scene.md#function-find-14) (const std::string & name) <br> |
|  SceneObjectPtr | [**Find**](classSR__WORLD__NS_1_1Scene.md#function-find-24) (const char \* name) <br> |
|  SceneObjectPtr | [**Find**](classSR__WORLD__NS_1_1Scene.md#function-find-34) (uint64\_t hashName) <br> |
|  SceneObjectPtr | [**Find**](classSR__WORLD__NS_1_1Scene.md#function-find-44) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SceneObjectPtr | [**FindByComponent**](classSR__WORLD__NS_1_1Scene.md#function-findbycomponent) (const std::string & name) <br> |
| virtual GameObjectPtr | [**FindOrInstanceGameObject**](classSR__WORLD__NS_1_1Scene.md#function-findorinstancegameobject) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SR\_NODISCARD Path | [**GetAbsPath**](classSR__WORLD__NS_1_1Scene.md#function-getabspath-12) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetDataStorage**](classSR__WORLD__NS_1_1Scene.md#function-getdatastorage-12) () <br> |
|  SR\_NODISCARD const [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetDataStorage**](classSR__WORLD__NS_1_1Scene.md#function-getdatastorage-22) () const<br> |
|  SR\_NODISCARD const SR\_UTILS\_NS::EntityController::Ptr & | [**GetEntityController**](classSR__WORLD__NS_1_1Scene.md#function-getentitycontroller) () const<br> |
|  SR\_NODISCARD SceneLogicPtr | [**GetLogicBase**](classSR__WORLD__NS_1_1Scene.md#function-getlogicbase) () const<br> |
|  SR\_NODISCARD std::string | [**GetName**](classSR__WORLD__NS_1_1Scene.md#function-getname) () const<br> |
|  SR\_NODISCARD Path | [**GetPath**](classSR__WORLD__NS_1_1Scene.md#function-getpath) () const<br> |
|  SceneObjects & | [**GetRootSceneObjects**](classSR__WORLD__NS_1_1Scene.md#function-getrootsceneobjects) () <br> |
| virtual IComponentable::ScenePtr | [**GetScene**](classSR__WORLD__NS_1_1Scene.md#function-getscene) () override const<br> |
|  SR\_NODISCARD SR\_INLINE [**SceneUpdater**](classSR__WORLD__NS_1_1SceneUpdater.md) \* | [**GetSceneUpdater**](classSR__WORLD__NS_1_1Scene.md#function-getsceneupdater) () const<br> |
|  void | [**Init**](classSR__WORLD__NS_1_1Scene.md#function-init) () <br> |
| virtual SceneObjectPtr | [**Instance**](classSR__WORLD__NS_1_1Scene.md#function-instance) (const Types::RawMesh \* rawMesh) <br> |
| virtual SceneObjectPtr | [**InstanceFromFile**](classSR__WORLD__NS_1_1Scene.md#function-instancefromfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
| virtual GameObjectPtr | [**InstanceGameObject**](classSR__WORLD__NS_1_1Scene.md#function-instancegameobject) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
| virtual SR\_NODISCARD bool | [**IsPausedMode**](classSR__WORLD__NS_1_1Scene.md#function-ispausedmode) () const<br>_На паузе ли сцена (если запущена)_  |
| virtual SR\_NODISCARD bool | [**IsPlayingMode**](classSR__WORLD__NS_1_1Scene.md#function-isplayingmode) () const<br>_Запущена ли сцена_  |
| virtual SR\_NODISCARD bool | [**IsPrefab**](classSR__WORLD__NS_1_1Scene.md#function-isprefab) () noexcept override const<br> |
|  void | [**OnChanged**](classSR__WORLD__NS_1_1Scene.md#function-onchanged) () <br> |
|  void | [**OnPostLoad**](classSR__WORLD__NS_1_1Scene.md#function-onpostload) () override<br> |
|  void | [**Prepare**](classSR__WORLD__NS_1_1Scene.md#function-prepare) () <br> |
|  void | [**RegisterSceneObject**](classSR__WORLD__NS_1_1Scene.md#function-registersceneobject) (const SceneObjectPtr & pSO) <br> |
|  bool | [**Reload**](classSR__WORLD__NS_1_1Scene.md#function-reload) () <br> |
|  bool | [**Remove**](classSR__WORLD__NS_1_1Scene.md#function-remove-12) (const SceneObjectPtr & gameObject) <br> |
|  void | [**Remove**](classSR__WORLD__NS_1_1Scene.md#function-remove-22) (const Component::Ptr & pComponent) <br> |
|  bool | [**SaveScene**](classSR__WORLD__NS_1_1Scene.md#function-savescene) () <br> |
|  bool | [**SaveSceneAt**](classSR__WORLD__NS_1_1Scene.md#function-savesceneat) (const Path & path) <br> |
|   | [**Scene**](classSR__WORLD__NS_1_1Scene.md#function-scene) () <br>_NOLINT._  |
| virtual bool | [**SetDirty**](classSR__WORLD__NS_1_1Scene.md#function-setdirty) (bool dirty) override<br> |
|  void | [**SetPath**](classSR__WORLD__NS_1_1Scene.md#function-setpath) (const Path & path) <br> |
|   | [**~Scene**](classSR__WORLD__NS_1_1Scene.md#function-scene) () override<br> |


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




## Public Static Functions inherited from SR_WORLD_NS::Scene

See [SR\_WORLD\_NS::Scene](classSR__WORLD__NS_1_1Scene.md)

| Type | Name |
| ---: | :--- |
|  Scene::Ptr | [**CreateEmptyScene**](classSR__WORLD__NS_1_1Scene.md#function-createemptyscene) () <br> |
|  Path | [**GetAbsPath**](classSR__WORLD__NS_1_1Scene.md#function-getabspath-22) (const Path & path) <br> |
|  bool | [**IsExists**](classSR__WORLD__NS_1_1Scene.md#function-isexists) (const Path & path) <br> |
|  Scene::Ptr | [**LoadScene**](classSR__WORLD__NS_1_1Scene.md#function-loadscene) (const Path & path) <br> |
|  Scene::Ptr | [**NewScene**](classSR__WORLD__NS_1_1Scene.md#function-newscene) (const Path & path, SceneLogicType type) <br> |




















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








## Public Functions Documentation




### function Instance 

```C++
SR_UTILS_NS::SceneObject::Ptr SR_CORE_NS::World::Instance (
    const SR_HTYPES_NS::RawMesh * rawMesh
) override
```




<hr>



### function World 

```C++
SR_CORE_NS::World::World () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/World/World.h`

