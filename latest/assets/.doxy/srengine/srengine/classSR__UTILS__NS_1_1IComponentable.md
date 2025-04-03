

# Class SR\_UTILS\_NS::IComponentable



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md)








Inherits the following classes: Entity


Inherited by the following classes: [SR\_WORLD\_NS::Scene](classSR__WORLD__NS_1_1Scene.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) | [**OriginType**](#typedef-origintype)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**IComponentable**](classSR__UTILS__NS_1_1IComponentable.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) \* | [**ScenePtr**](#typedef-sceneptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual bool | [**AddComponent**](#function-addcomponent-12) (const Component::Ptr & pComponent) <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**AddComponent**](#function-addcomponent-22) () <br> |
| virtual void | [**Awake**](#function-awake) (bool force, bool isPaused) noexcept<br> |
| virtual void | [**CheckActivity**](#function-checkactivity) (bool force) noexcept<br> |
| virtual bool | [**ContainsComponent**](#function-containscomponent) (const std::string & name) <br> |
| virtual void | [**ForEachComponent**](#function-foreachcomponent-12) (const std::function&lt; bool(const Component::Ptr &)&gt; & fun) const<br> |
| virtual void | [**ForEachComponent**](#function-foreachcomponent-22) (const std::function&lt; bool(Component::Ptr &)&gt; & fun) <br> |
| virtual Component::Ptr | [**GetComponent**](#function-getcomponent-13) (const std::string & name) <br> |
| virtual Component::Ptr | [**GetComponent**](#function-getcomponent-23) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetComponent**](#function-getcomponent-33) () <br> |
|  SR\_NODISCARD int32\_t | [**GetComponentIndex**](#function-getcomponentindex) (const Component::Ptr & pComponent) const<br> |
|  SR\_NODISCARD const std::vector&lt; Component::Ptr &gt; & | [**GetComponents**](#function-getcomponents) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetComponentsCount**](#function-getcomponentscount) () noexcept const<br> |
| virtual Component::Ptr | [**GetOrCreateComponent**](#function-getorcreatecomponent-12) (const std::string & name) <br> |
| virtual Component::Ptr | [**GetOrCreateComponent**](#function-getorcreatecomponent-22) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
| virtual SR\_NODISCARD ScenePtr | [**GetScene**](#function-getscene) () const<br> |
|  SR\_NODISCARD bool | [**HasComponent**](#function-hascomponent) (const Component::Ptr & pComponent) const<br> |
| virtual SR\_NODISCARD bool | [**IsActive**](#function-isactive) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsDestroyed**](#function-isdestroyed) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDirty**](#function-isdirty) () noexcept const<br> |
| virtual SR\_NODISCARD bool | [**IsPrefab**](#function-isprefab) () noexcept const<br> |
| virtual bool | [**MoveComponent**](#function-movecomponent) (const Component::Ptr & pComponent, int32\_t offset) <br> |
| virtual void | [**OnMatrixDirty**](#function-onmatrixdirty) () <br> |
|  void | [**OnPostLoad**](#function-onpostload) () override<br> |
| virtual void | [**OnPriorityChanged**](#function-onprioritychanged) () <br> |
| virtual bool | [**PostLoad**](#function-postload) (bool force) <br>_Вызывает OnAttached у компонентов загруженных через LoadComponent._  |
| virtual bool | [**RemoveComponent**](#function-removecomponent) (const Component::Ptr & pComponent) <br> |
|  void | [**RemoveComponents**](#function-removecomponents) () <br> |
| virtual bool | [**SetDirty**](#function-setdirty) (bool dirty) <br> |
| virtual void | [**Start**](#function-start) (bool force) noexcept<br> |
|   | [**~IComponentable**](#function-icomponentable) () override<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; Component::Ptr &gt; | [**m\_components**](#variable-m_components)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**DestroyComponent**](#function-destroycomponent) (const Component::Ptr & pComponent) <br> |




## Public Types Documentation




### typedef OriginType 

```C++
using SR_UTILS_NS::IComponentable::OriginType =  IComponentable;
```




<hr>



### typedef Ptr 

```C++
using SR_UTILS_NS::IComponentable::Ptr =  SR_HTYPES_NS::SharedPtr<IComponentable>;
```




<hr>



### typedef ScenePtr 

```C++
using SR_UTILS_NS::IComponentable::ScenePtr =  SR_WORLD_NS::Scene*;
```




<hr>
## Public Functions Documentation




### function AddComponent [1/2]

```C++
virtual bool SR_UTILS_NS::IComponentable::AddComponent (
    const Component::Ptr & pComponent
) 
```




<hr>



### function AddComponent [2/2]

```C++
template<typename T>
inline SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::IComponentable::AddComponent () 
```




<hr>



### function Awake 

```C++
virtual void SR_UTILS_NS::IComponentable::Awake (
    bool force,
    bool isPaused
) noexcept
```




<hr>



### function CheckActivity 

```C++
virtual void SR_UTILS_NS::IComponentable::CheckActivity (
    bool force
) noexcept
```




<hr>



### function ContainsComponent 

```C++
virtual bool SR_UTILS_NS::IComponentable::ContainsComponent (
    const std::string & name
) 
```




<hr>



### function ForEachComponent [1/2]

```C++
virtual void SR_UTILS_NS::IComponentable::ForEachComponent (
    const std::function< bool(const Component::Ptr &)> & fun
) const
```




<hr>



### function ForEachComponent [2/2]

```C++
virtual void SR_UTILS_NS::IComponentable::ForEachComponent (
    const std::function< bool(Component::Ptr &)> & fun
) 
```




<hr>



### function GetComponent [1/3]

```C++
virtual Component::Ptr SR_UTILS_NS::IComponentable::GetComponent (
    const std::string & name
) 
```




<hr>



### function GetComponent [2/3]

```C++
virtual Component::Ptr SR_UTILS_NS::IComponentable::GetComponent (
    StringAtom name
) 
```




<hr>



### function GetComponent [3/3]

```C++
template<typename T>
inline SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::IComponentable::GetComponent () 
```




<hr>



### function GetComponentIndex 

```C++
SR_NODISCARD int32_t SR_UTILS_NS::IComponentable::GetComponentIndex (
    const Component::Ptr & pComponent
) const
```




<hr>



### function GetComponents 

```C++
inline SR_NODISCARD const std::vector< Component::Ptr > & SR_UTILS_NS::IComponentable::GetComponents () noexcept const
```




<hr>



### function GetComponentsCount 

```C++
inline SR_NODISCARD uint32_t SR_UTILS_NS::IComponentable::GetComponentsCount () noexcept const
```




<hr>



### function GetOrCreateComponent [1/2]

```C++
virtual Component::Ptr SR_UTILS_NS::IComponentable::GetOrCreateComponent (
    const std::string & name
) 
```




<hr>



### function GetOrCreateComponent [2/2]

```C++
virtual Component::Ptr SR_UTILS_NS::IComponentable::GetOrCreateComponent (
    StringAtom name
) 
```




<hr>



### function GetScene 

```C++
virtual SR_NODISCARD ScenePtr SR_UTILS_NS::IComponentable::GetScene () const
```




<hr>



### function HasComponent 

```C++
SR_NODISCARD bool SR_UTILS_NS::IComponentable::HasComponent (
    const Component::Ptr & pComponent
) const
```




<hr>



### function IsActive 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IComponentable::IsActive () noexcept const
```




<hr>



### function IsDestroyed 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IComponentable::IsDestroyed () noexcept const
```




<hr>



### function IsDirty 

```C++
SR_NODISCARD bool SR_UTILS_NS::IComponentable::IsDirty () noexcept const
```




<hr>



### function IsPrefab 

```C++
inline virtual SR_NODISCARD bool SR_UTILS_NS::IComponentable::IsPrefab () noexcept const
```




<hr>



### function MoveComponent 

```C++
virtual bool SR_UTILS_NS::IComponentable::MoveComponent (
    const Component::Ptr & pComponent,
    int32_t offset
) 
```




<hr>



### function OnMatrixDirty 

```C++
virtual void SR_UTILS_NS::IComponentable::OnMatrixDirty () 
```




<hr>



### function OnPostLoad 

```C++
void SR_UTILS_NS::IComponentable::OnPostLoad () override
```




<hr>



### function OnPriorityChanged 

```C++
virtual void SR_UTILS_NS::IComponentable::OnPriorityChanged () 
```




<hr>



### function PostLoad 

_Вызывает OnAttached у компонентов загруженных через LoadComponent._ 
```C++
virtual bool SR_UTILS_NS::IComponentable::PostLoad (
    bool force
) 
```




<hr>



### function RemoveComponent 

```C++
virtual bool SR_UTILS_NS::IComponentable::RemoveComponent (
    const Component::Ptr & pComponent
) 
```




<hr>



### function RemoveComponents 

```C++
void SR_UTILS_NS::IComponentable::RemoveComponents () 
```




<hr>



### function SetDirty 

```C++
virtual bool SR_UTILS_NS::IComponentable::SetDirty (
    bool dirty
) 
```




<hr>



### function Start 

```C++
virtual void SR_UTILS_NS::IComponentable::Start (
    bool force
) noexcept
```




<hr>



### function ~IComponentable 

```C++
SR_UTILS_NS::IComponentable::~IComponentable () override
```




<hr>
## Protected Attributes Documentation




### variable m\_components 

```C++
std::vector<Component::Ptr> SR_UTILS_NS::IComponentable::m_components;
```




<hr>
## Protected Functions Documentation




### function DestroyComponent 

```C++
void SR_UTILS_NS::IComponentable::DestroyComponent (
    const Component::Ptr & pComponent
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/ECS/IComponentable.h`

