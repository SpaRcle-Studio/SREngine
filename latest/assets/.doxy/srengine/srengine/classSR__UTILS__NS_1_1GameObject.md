

# Class SR\_UTILS\_NS::GameObject



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**GameObject**](classSR__UTILS__NS_1_1GameObject.md)



_@scriptableClass_ 

* `#include <GameObject.h>`



Inherits the following classes: SceneObject














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**GameObject**](classSR__UTILS__NS_1_1GameObject.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD GameObject::Ptr | [**CreateChild**](#function-createchild) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|   | [**GameObject**](#function-gameobject) () = default<br> |
|  SR\_NODISCARD GameObject::Ptr | [**GetOrCreateChild**](#function-getorcreatechild) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Transform**](classSR__UTILS__NS_1_1Transform.md) &gt; | [**GetParentTransform**](#function-getparenttransform) () noexcept const<br> |
|  SR\_NODISCARD SceneObjectType | [**GetSceneObjectType**](#function-getsceneobjecttype) () noexcept override const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Transform**](classSR__UTILS__NS_1_1Transform.md) &gt; | [**GetTransform**](#function-gettransform) () noexcept const<br> |
|  void | [**OnAttached**](#function-onattached) () override<br> |
|  void | [**SetTransform**](#function-settransform) (const [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Transform**](classSR__UTILS__NS_1_1Transform.md) &gt; & pTransform) <br> |
|   | [**~GameObject**](#function-gameobject) () override<br> |
























## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**OnHierarchyChanged**](#function-onhierarchychanged) () override<br> |




## Public Types Documentation




### typedef Ptr 

```C++
using SR_UTILS_NS::GameObject::Ptr =  SR_HTYPES_NS::SharedPtr<GameObject>;
```




<hr>
## Public Functions Documentation




### function CreateChild 

```C++
SR_NODISCARD GameObject::Ptr SR_UTILS_NS::GameObject::CreateChild (
    StringAtom name
) 
```




<hr>



### function GameObject 

```C++
SR_UTILS_NS::GameObject::GameObject () = default
```




<hr>



### function GetOrCreateChild 

```C++
SR_NODISCARD GameObject::Ptr SR_UTILS_NS::GameObject::GetOrCreateChild (
    StringAtom name
) 
```




<hr>



### function GetParentTransform 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < Transform > SR_UTILS_NS::GameObject::GetParentTransform () noexcept const
```




<hr>



### function GetSceneObjectType 

```C++
inline SR_NODISCARD SceneObjectType SR_UTILS_NS::GameObject::GetSceneObjectType () noexcept override const
```




<hr>



### function GetTransform 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtr < Transform > SR_UTILS_NS::GameObject::GetTransform () noexcept const
```




<hr>



### function OnAttached 

```C++
void SR_UTILS_NS::GameObject::OnAttached () override
```




<hr>



### function SetTransform 

```C++
void SR_UTILS_NS::GameObject::SetTransform (
    const SR_HTYPES_NS::SharedPtr < Transform > & pTransform
) 
```




<hr>



### function ~GameObject 

```C++
SR_UTILS_NS::GameObject::~GameObject () override
```




<hr>
## Protected Functions Documentation




### function OnHierarchyChanged 

```C++
void SR_UTILS_NS::GameObject::OnHierarchyChanged () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/ECS/GameObject.h`

