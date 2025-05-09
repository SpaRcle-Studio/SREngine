

# Class SR\_UTILS\_NS::InputHandler



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**InputHandler**](classSR__UTILS__NS_1_1InputHandler.md)








Inherits the following classes: [SR\_UTILS\_NS::Event](classSR__UTILS__NS_1_1Event.md)


Inherited by the following classes: [SR\_GRAPH\_GUI\_NS::Widget](classSR__GRAPH__GUI__NS_1_1Widget.md),  [SR\_GRAPH\_GUI\_NS::WidgetContainerElement](classSR__GRAPH__GUI__NS_1_1WidgetContainerElement.md),  [SR\_GRAPH\_NS::GUI::WidgetManager](classSR__GRAPH__NS_1_1GUI_1_1WidgetManager.md)








































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnKeyDown**](#function-onkeydown) (const [**KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) <br> |
| virtual void | [**OnKeyPress**](#function-onkeypress) (const [**KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) <br> |
| virtual void | [**OnKeyUp**](#function-onkeyup) (const [**KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* data) <br> |
| virtual void | [**OnMouseDown**](#function-onmousedown) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |
| virtual void | [**OnMouseMove**](#function-onmousemove) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |
| virtual void | [**OnMousePress**](#function-onmousepress) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |
| virtual void | [**OnMouseUp**](#function-onmouseup) (const [**MouseInputData**](classSR__UTILS__NS_1_1MouseInputData.md) \* data) <br> |


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




































































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**InputHandler**](#function-inputhandler) () <br> |
|  bool | [**IsKeyPressed**](#function-iskeypressed) (KeyCode code) <br> |
|   | [**~InputHandler**](#function-inputhandler) () override<br> |




## Protected Functions inherited from SR_UTILS_NS::IEvent

See [SR\_UTILS\_NS::IEvent](classSR__UTILS__NS_1_1IEvent.md)

| Type | Name |
| ---: | :--- |
|   | [**IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () <br> |
| virtual  | [**~IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () <br> |








## Public Functions Documentation




### function OnKeyDown 

```C++
virtual void SR_UTILS_NS::InputHandler::OnKeyDown (
    const KeyboardInputData * data
) 
```




<hr>



### function OnKeyPress 

```C++
virtual void SR_UTILS_NS::InputHandler::OnKeyPress (
    const KeyboardInputData * data
) 
```




<hr>



### function OnKeyUp 

```C++
virtual void SR_UTILS_NS::InputHandler::OnKeyUp (
    const KeyboardInputData * data
) 
```




<hr>



### function OnMouseDown 

```C++
virtual void SR_UTILS_NS::InputHandler::OnMouseDown (
    const MouseInputData * data
) 
```




<hr>



### function OnMouseMove 

```C++
virtual void SR_UTILS_NS::InputHandler::OnMouseMove (
    const MouseInputData * data
) 
```




<hr>



### function OnMousePress 

```C++
virtual void SR_UTILS_NS::InputHandler::OnMousePress (
    const MouseInputData * data
) 
```




<hr>



### function OnMouseUp 

```C++
virtual void SR_UTILS_NS::InputHandler::OnMouseUp (
    const MouseInputData * data
) 
```




<hr>
## Protected Functions Documentation




### function InputHandler 

```C++
SR_UTILS_NS::InputHandler::InputHandler () 
```




<hr>



### function IsKeyPressed 

```C++
bool SR_UTILS_NS::InputHandler::IsKeyPressed (
    KeyCode code
) 
```




<hr>



### function ~InputHandler 

```C++
SR_UTILS_NS::InputHandler::~InputHandler () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Input/InputHandler.h`

