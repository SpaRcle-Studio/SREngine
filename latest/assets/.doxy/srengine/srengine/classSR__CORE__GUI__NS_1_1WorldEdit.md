

# Class SR\_CORE\_GUI\_NS::WorldEdit



[**ClassList**](annotated.md) **>** [**SR\_CORE\_GUI\_NS**](namespaceSR__CORE__GUI__NS.md) **>** [**WorldEdit**](classSR__CORE__GUI__NS_1_1WorldEdit.md)








Inherits the following classes: [SR\_GRAPH\_GUI\_NS::Widget](classSR__GRAPH__GUI__NS_1_1Widget.md)
















## Public Types inherited from SR_GRAPH_GUI_NS::Widget

See [SR\_GRAPH\_GUI\_NS::Widget](classSR__GRAPH__GUI__NS_1_1Widget.md)

| Type | Name |
| ---: | :--- |
| typedef RenderContext \* | [**ContextPtr**](classSR__GRAPH__GUI__NS_1_1Widget.md#typedef-contextptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; RenderScene &gt; | [**RenderScenePtr**](classSR__GRAPH__GUI__NS_1_1Widget.md#typedef-rendersceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**ScenePtr**](classSR__GRAPH__GUI__NS_1_1Widget.md#typedef-sceneptr)  <br> |






















































































































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**SetScene**](#function-setscene) (const SR\_WORLD\_NS::Scene::Ptr & scene) override<br> |
|   | [**WorldEdit**](#function-worldedit) () <br> |
|   | [**~WorldEdit**](#function-worldedit) () override<br> |


## Public Functions inherited from SR_GRAPH_GUI_NS::Widget

See [SR\_GRAPH\_GUI\_NS::Widget](classSR__GRAPH__GUI__NS_1_1Widget.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddSubWidget**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-addsubwidget) ([**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md) \* pWidget) <br> |
| virtual void | [**Close**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-close) () <br> |
|  void | [**DrawAsSubWindow**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-drawassubwindow) () <br> |
| virtual void | [**FixedUpdate**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-fixedupdate) () <br> |
|  SR\_NODISCARD ContextPtr | [**GetContext**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-getcontext) () const<br> |
|  SR\_NODISCARD WidgetManager \* | [**GetManager**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-getmanager) () const<br> |
|  SR\_NODISCARD const std::string & | [**GetName**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-getname) () const<br> |
|  SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-getrenderscene) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetStrongStorage**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-getstrongstorage) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetWeakStorage**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-getweakstorage) () const<br> |
| virtual void | [**Init**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsFocused**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-isfocused) () const<br> |
|  SR\_NODISCARD bool | [**IsHovered**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-ishovered) () const<br> |
|  SR\_NODISCARD bool | [**IsOpen**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-isopen) () const<br> |
| virtual void | [**OnKeyDown**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-onkeydown) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* pData) override<br> |
| virtual void | [**OnKeyPress**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-onkeypress) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* pData) override<br> |
| virtual void | [**OnKeyUp**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-onkeyup) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* pData) override<br> |
| virtual void | [**Open**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-open) () <br> |
| virtual bool | [**OpenFile**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-openfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetManager**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-setmanager) (WidgetManager \* pManager) <br> |
| virtual void | [**SetScene**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-setscene) (const ScenePtr & scene) <br> |
| virtual void | [**SetSize**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-setsize) (const SR\_MATH\_NS::IVector2 & size) <br> |
| virtual void | [**Update**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-update) (float\_t dt) <br> |
|   | [**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-widget-12) () = default<br> |
|   | [**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-widget-22) (std::string name, SR\_MATH\_NS::IVector2 size=SR\_MATH\_NS::IVector2MAX) <br> |
|   | [**~Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-widget) () override<br> |


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








































## Protected Attributes inherited from SR_GRAPH_GUI_NS::Widget

See [SR\_GRAPH\_GUI\_NS::Widget](classSR__GRAPH__GUI__NS_1_1Widget.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__GRAPH__GUI__NS_1_1Widget.md#variable-m_mutex)  <br> |
|  std::vector&lt; [**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md) \* &gt; | [**m\_subWidgets**](classSR__GRAPH__GUI__NS_1_1Widget.md#variable-m_subwidgets)  <br> |
|  WidgetFlagBits | [**m\_widgetFlags**](classSR__GRAPH__GUI__NS_1_1Widget.md#variable-m_widgetflags)   = `WIDGET\_FLAG\_NONE`<br> |






























































































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**Draw**](#function-draw) () override<br> |


## Protected Functions inherited from SR_GRAPH_GUI_NS::Widget

See [SR\_GRAPH\_GUI\_NS::Widget](classSR__GRAPH__GUI__NS_1_1Widget.md)

| Type | Name |
| ---: | :--- |
|  void | [**AddFlags**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-addflags) (WindowFlags flags) <br> |
|  void | [**CheckFocused**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-checkfocused) () <br> |
|  void | [**CheckHovered**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-checkhovered) () <br> |
| virtual void | [**Draw**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-draw) () = 0<br> |
| virtual void | [**OnClose**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-onclose) () <br> |
| virtual void | [**OnOpen**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-onopen) () <br> |
|  void | [**ResetStrongStorage**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-resetstrongstorage) () <br> |
|  void | [**ResetWeakStorage**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-resetweakstorage) () <br> |
|  void | [**SetCenter**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-setcenter) (bool value) <br> |
|  void | [**SetFlags**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-setflags) (WindowFlags flags) <br> |
|  void | [**SetName**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-setname) (const std::string & name) <br> |
|  void | [**TextCenter**](classSR__GRAPH__GUI__NS_1_1Widget.md#function-textcenter) (const std::string & text) const<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |


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
|   | [**IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () <br> |
| virtual  | [**~IEvent**](classSR__UTILS__NS_1_1IEvent.md#function-ievent) () <br> |














## Public Functions Documentation




### function SetScene 

```C++
void SR_CORE_GUI_NS::WorldEdit::SetScene (
    const SR_WORLD_NS::Scene::Ptr & scene
) override
```




<hr>



### function WorldEdit 

```C++
SR_CORE_GUI_NS::WorldEdit::WorldEdit () 
```




<hr>



### function ~WorldEdit 

```C++
SR_CORE_GUI_NS::WorldEdit::~WorldEdit () override
```




<hr>
## Protected Functions Documentation




### function Draw 

```C++
virtual void SR_CORE_GUI_NS::WorldEdit::Draw () override
```



Implements [*SR\_GRAPH\_GUI\_NS::Widget::Draw*](classSR__GRAPH__GUI__NS_1_1Widget.md#function-draw)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/GUI/WorldEdit.h`

