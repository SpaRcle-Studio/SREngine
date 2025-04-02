

# Class SR\_CORE\_GUI\_NS::Hierarchy



[**ClassList**](annotated.md) **>** [**SR\_CORE\_GUI\_NS**](namespaceSR__CORE__GUI__NS.md) **>** [**Hierarchy**](classSR__CORE__GUI__NS_1_1Hierarchy.md)








Inherits the following classes: SR_GRAPH_NS::GUI::Widget


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearSelected**](#function-clearselected) () <br> |
|  SR\_NODISCARD const std::set&lt; SR\_UTILS\_NS::SceneObject::Ptr &gt; & | [**GetSelected**](#function-getselected) () const<br> |
|   | [**Hierarchy**](#function-hierarchy) () <br> |
|  void | [**OnKeyDown**](#function-onkeydown) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) override<br> |
|  void | [**OnKeyUp**](#function-onkeyup) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) override<br> |
|  void | [**SelectGameObject**](#function-selectgameobject) (const SR\_UTILS\_NS::SceneObject::Ptr & ptr) <br> |
|  void | [**SetScene**](#function-setscene) (const SR\_WORLD\_NS::Scene::Ptr & scene) override<br> |
|  void | [**SetSelectedImpl**](#function-setselectedimpl) (const std::set&lt; SR\_UTILS\_NS::SceneObject::Ptr &gt; & changeSelected) <br> |
|  void | [**Update**](#function-update) (float\_t dt) override<br> |
|   | [**~Hierarchy**](#function-hierarchy) () override<br> |




























## Public Functions Documentation




### function ClearSelected 

```C++
void SR_CORE_GUI_NS::Hierarchy::ClearSelected () 
```




<hr>



### function GetSelected 

```C++
SR_NODISCARD const std::set< SR_UTILS_NS::SceneObject::Ptr > & SR_CORE_GUI_NS::Hierarchy::GetSelected () const
```




<hr>



### function Hierarchy 

```C++
SR_CORE_GUI_NS::Hierarchy::Hierarchy () 
```




<hr>



### function OnKeyDown 

```C++
void SR_CORE_GUI_NS::Hierarchy::OnKeyDown (
    const SR_UTILS_NS::KeyboardInputData * data
) override
```




<hr>



### function OnKeyUp 

```C++
void SR_CORE_GUI_NS::Hierarchy::OnKeyUp (
    const SR_UTILS_NS::KeyboardInputData * data
) override
```




<hr>



### function SelectGameObject 

```C++
void SR_CORE_GUI_NS::Hierarchy::SelectGameObject (
    const SR_UTILS_NS::SceneObject::Ptr & ptr
) 
```




<hr>



### function SetScene 

```C++
void SR_CORE_GUI_NS::Hierarchy::SetScene (
    const SR_WORLD_NS::Scene::Ptr & scene
) override
```




<hr>



### function SetSelectedImpl 

```C++
void SR_CORE_GUI_NS::Hierarchy::SetSelectedImpl (
    const std::set< SR_UTILS_NS::SceneObject::Ptr > & changeSelected
) 
```




<hr>



### function Update 

```C++
void SR_CORE_GUI_NS::Hierarchy::Update (
    float_t dt
) override
```




<hr>



### function ~Hierarchy 

```C++
SR_CORE_GUI_NS::Hierarchy::~Hierarchy () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/GUI/Hierarchy.h`

