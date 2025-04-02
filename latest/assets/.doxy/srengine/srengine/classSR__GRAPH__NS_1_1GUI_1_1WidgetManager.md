

# Class SR\_GRAPH\_NS::GUI::WidgetManager



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**GUI**](namespaceSR__GRAPH__NS_1_1GUI.md) **>** [**WidgetManager**](classSR__GRAPH__NS_1_1GUI_1_1WidgetManager.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md),  [SR\_UTILS\_NS::InputHandler](classSR__UTILS__NS_1_1InputHandler.md)


Inherited by the following classes: [SR\_GRAPH\_NS::GUI::GlobalWidgetManager](classSR__GRAPH__NS_1_1GUI_1_1GlobalWidgetManager.md)
















































































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Draw**](#function-draw) () <br> |
|  SR\_NODISCARD [**ContextPtr**](classSR__GRAPH__NS_1_1RenderContext.md) | [**GetContext**](#function-getcontext) () const<br> |
|  SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  T \* | [**GetWidget**](#function-getwidget) () const<br> |
|  SR\_NODISCARD Widgets & | [**GetWidgets**](#function-getwidgets) () <br> |
|  void | [**HideAll**](#function-hideall) () <br> |
| virtual void | [**OnKeyDown**](#function-onkeydown) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) override<br> |
| virtual void | [**OnKeyPress**](#function-onkeypress) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) override<br> |
| virtual void | [**OnKeyUp**](#function-onkeyup) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) override<br> |
| virtual void | [**OnMouseDown**](#function-onmousedown) (const [**SR\_UTILS\_NS::MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) override<br> |
| virtual void | [**OnMouseMove**](#function-onmousemove) (const [**SR\_UTILS\_NS::MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) override<br> |
| virtual void | [**OnMousePress**](#function-onmousepress) (const [**SR\_UTILS\_NS::MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) override<br> |
| virtual void | [**OnMouseUp**](#function-onmouseup) (const [**SR\_UTILS\_NS::MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) override<br> |
|  bool | [**Register**](#function-register) (Widget \* widget) <br> |
|  bool | [**Remove**](#function-remove) (Widget \* widget) <br> |
|  void | [**SetRenderScene**](#function-setrenderscene) (const RenderScenePtr & renderScene) <br> |
|  void | [**SetScene**](#function-setscene) (const ScenePtr & scene) <br> |
|  void | [**ShowAll**](#function-showall) () <br> |
|   | [**WidgetManager**](#function-widgetmanager) () <br> |
|   | [**~WidgetManager**](#function-widgetmanager) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_UTILS_NS::InputHandler

See [SR\_UTILS\_NS::InputHandler](classSR__UTILS__NS_1_1InputHandler.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**OnKeyDown**](classSR__UTILS__NS_1_1InputHandler.md#function-onkeydown) (const [**KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) <br> |
| virtual void | [**OnKeyPress**](classSR__UTILS__NS_1_1InputHandler.md#function-onkeypress) (const [**KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) <br> |
| virtual void | [**OnKeyUp**](classSR__UTILS__NS_1_1InputHandler.md#function-onkeyup) (const [**KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) <br> |
| virtual void | [**OnMouseDown**](classSR__UTILS__NS_1_1InputHandler.md#function-onmousedown) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |
| virtual void | [**OnMouseMove**](classSR__UTILS__NS_1_1InputHandler.md#function-onmousemove) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |
| virtual void | [**OnMousePress**](classSR__UTILS__NS_1_1InputHandler.md#function-onmousepress) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |
| virtual void | [**OnMouseUp**](classSR__UTILS__NS_1_1InputHandler.md#function-onmouseup) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |


## Public Functions inherited from SR_UTILS_NS::Event

See [SR\_UTILS\_NS::Event](classSR__UTILS__NS_1_1Event.md)

| Type | Name |
| ---: | :--- |
|   | [**Event**](classSR__UTILS__NS_1_1Event.md#function-event) (std::string name) <br> |
| virtual void | [**Trigger**](classSR__UTILS__NS_1_1Event.md#function-trigger) (\_args... a) <br> |
|   | [**~Event**](classSR__UTILS__NS_1_1Event.md#function-event) () override<br> |


## Public Functions inherited from SR_UTILS_NS::IEvent

See [SR\_UTILS\_NS::IEvent](classSR__UTILS__NS_1_1IEvent.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD const std::string & | [**GetEventName**](classSR__UTILS__NS_1_1IEvent.md#function-geteventname) () const = 0<br> |
































## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](#variable-m_mutex)  <br> |


















































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::InputHandler

See [SR\_UTILS\_NS::InputHandler](classSR__UTILS__NS_1_1InputHandler.md)

| Type | Name |
| ---: | :--- |
|   | [**InputHandler**](classSR__UTILS__NS_1_1InputHandler.md#function-inputhandler) () <br> |
|  bool | [**IsKeyPressed**](classSR__UTILS__NS_1_1InputHandler.md#function-iskeypressed) (KeyCode code) <br> |
|   | [**~InputHandler**](classSR__UTILS__NS_1_1InputHandler.md#function-inputhandler) () override<br> |




## Protected Functions inherited from SR_UTILS_NS::IEvent

See [SR\_UTILS\_NS::IEvent](classSR__UTILS__NS_1_1IEvent.md)

| Type | Name |
| ---: | :--- |
|   | [**IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () = default<br> |
| virtual  | [**~IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () = default<br> |












## Public Functions Documentation




### function Draw 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::Draw () 
```




<hr>



### function GetContext 

```C++
SR_NODISCARD ContextPtr SR_GRAPH_NS::GUI::WidgetManager::GetContext () const
```




<hr>



### function GetRenderScene 

```C++
SR_NODISCARD RenderScenePtr SR_GRAPH_NS::GUI::WidgetManager::GetRenderScene () const
```




<hr>



### function GetWidget 

```C++
template<typename T>
inline T * SR_GRAPH_NS::GUI::WidgetManager::GetWidget () const
```




<hr>



### function GetWidgets 

```C++
inline SR_NODISCARD Widgets & SR_GRAPH_NS::GUI::WidgetManager::GetWidgets () 
```




<hr>



### function HideAll 

```C++
void SR_GRAPH_NS::GUI::WidgetManager::HideAll () 
```




<hr>



### function OnKeyDown 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::OnKeyDown (
    const SR_UTILS_NS::KeyboardInputData * data
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnKeyDown*](classSR__UTILS__NS_1_1InputHandler.md#function-onkeydown)


<hr>



### function OnKeyPress 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::OnKeyPress (
    const SR_UTILS_NS::KeyboardInputData * data
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnKeyPress*](classSR__UTILS__NS_1_1InputHandler.md#function-onkeypress)


<hr>



### function OnKeyUp 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::OnKeyUp (
    const SR_UTILS_NS::KeyboardInputData * data
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnKeyUp*](classSR__UTILS__NS_1_1InputHandler.md#function-onkeyup)


<hr>



### function OnMouseDown 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::OnMouseDown (
    const SR_UTILS_NS::MouseInputData * data
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnMouseDown*](classSR__UTILS__NS_1_1InputHandler.md#function-onmousedown)


<hr>



### function OnMouseMove 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::OnMouseMove (
    const SR_UTILS_NS::MouseInputData * data
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnMouseMove*](classSR__UTILS__NS_1_1InputHandler.md#function-onmousemove)


<hr>



### function OnMousePress 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::OnMousePress (
    const SR_UTILS_NS::MouseInputData * data
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnMousePress*](classSR__UTILS__NS_1_1InputHandler.md#function-onmousepress)


<hr>



### function OnMouseUp 

```C++
virtual void SR_GRAPH_NS::GUI::WidgetManager::OnMouseUp (
    const SR_UTILS_NS::MouseInputData * data
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnMouseUp*](classSR__UTILS__NS_1_1InputHandler.md#function-onmouseup)


<hr>



### function Register 

```C++
bool SR_GRAPH_NS::GUI::WidgetManager::Register (
    Widget * widget
) 
```




<hr>



### function Remove 

```C++
bool SR_GRAPH_NS::GUI::WidgetManager::Remove (
    Widget * widget
) 
```




<hr>



### function SetRenderScene 

```C++
void SR_GRAPH_NS::GUI::WidgetManager::SetRenderScene (
    const RenderScenePtr & renderScene
) 
```




<hr>



### function SetScene 

```C++
void SR_GRAPH_NS::GUI::WidgetManager::SetScene (
    const ScenePtr & scene
) 
```




<hr>



### function ShowAll 

```C++
void SR_GRAPH_NS::GUI::WidgetManager::ShowAll () 
```




<hr>



### function WidgetManager 

```C++
SR_GRAPH_NS::GUI::WidgetManager::WidgetManager () 
```




<hr>



### function ~WidgetManager 

```C++
SR_GRAPH_NS::GUI::WidgetManager::~WidgetManager () override
```




<hr>
## Protected Attributes Documentation




### variable m\_mutex 

```C++
std::recursive_mutex SR_GRAPH_NS::GUI::WidgetManager::m_mutex;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/WidgetManager.h`

