

# Class SR\_GRAPH\_GUI\_NS::Widget



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_GUI\_NS**](namespaceSR__GRAPH__GUI__NS.md) **>** [**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md),  [SR\_UTILS\_NS::InputHandler](classSR__UTILS__NS_1_1InputHandler.md)


Inherited by the following classes: [SR\_CORE\_GUI\_NS::About](classSR__CORE__GUI__NS_1_1About.md),  [SR\_CORE\_GUI\_NS::AnimatorEditor](classSR__CORE__GUI__NS_1_1AnimatorEditor.md),  [SR\_CORE\_GUI\_NS::EngineSettings](classSR__CORE__GUI__NS_1_1EngineSettings.md),  [SR\_CORE\_GUI\_NS::Inspector](classSR__CORE__GUI__NS_1_1Inspector.md),  [SR\_CORE\_GUI\_NS::PhysicsMaterialEditor](classSR__CORE__GUI__NS_1_1PhysicsMaterialEditor.md),  [SR\_CORE\_GUI\_NS::SceneViewer](classSR__CORE__GUI__NS_1_1SceneViewer.md),  [SR\_CORE\_GUI\_NS::SoundDebug](classSR__CORE__GUI__NS_1_1SoundDebug.md),  [SR\_CORE\_GUI\_NS::WorldEdit](classSR__CORE__GUI__NS_1_1WorldEdit.md),  [SR\_CORE\_NS::GUI::EngineStatistics](classSR__CORE__NS_1_1GUI_1_1EngineStatistics.md),  [SR\_CORE\_NS::GUI::FileBrowser](classSR__CORE__NS_1_1GUI_1_1FileBrowser.md),  [SR\_GRAPH\_GUI\_NS::NodeWidget](classSR__GRAPH__GUI__NS_1_1NodeWidget.md),  [SR\_GRAPH\_GUI\_NS::WidgetContainer](classSR__GRAPH__GUI__NS_1_1WidgetContainer.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef RenderContext \* | [**ContextPtr**](#typedef-contextptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; RenderScene &gt; | [**RenderScenePtr**](#typedef-rendersceneptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**SR\_WORLD\_NS::Scene**](classSR__WORLD__NS_1_1Scene.md) &gt; | [**ScenePtr**](#typedef-sceneptr)  <br> |




































































































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddSubWidget**](#function-addsubwidget) ([**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md) \* pWidget) <br> |
| virtual void | [**Close**](#function-close) () <br> |
|  void | [**DrawAsSubWindow**](#function-drawassubwindow) () <br> |
| virtual void | [**FixedUpdate**](#function-fixedupdate) () <br> |
|  SR\_NODISCARD ContextPtr | [**GetContext**](#function-getcontext) () const<br> |
|  SR\_NODISCARD WidgetManager \* | [**GetManager**](#function-getmanager) () const<br> |
|  SR\_NODISCARD const std::string & | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD RenderScenePtr | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetStrongStorage**](#function-getstrongstorage) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) & | [**GetWeakStorage**](#function-getweakstorage) () const<br> |
| virtual void | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsFocused**](#function-isfocused) () const<br> |
|  SR\_NODISCARD bool | [**IsHovered**](#function-ishovered) () const<br> |
|  SR\_NODISCARD bool | [**IsOpen**](#function-isopen) () const<br> |
| virtual void | [**OnKeyDown**](#function-onkeydown) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* pData) override<br> |
| virtual void | [**OnKeyPress**](#function-onkeypress) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* pData) override<br> |
| virtual void | [**OnKeyUp**](#function-onkeyup) (const [**SR\_UTILS\_NS::KeyboardInputData**](classSR__UTILS__NS_1_1KeyboardInputData.md) \* pData) override<br> |
| virtual void | [**Open**](#function-open) () <br> |
| virtual bool | [**OpenFile**](#function-openfile) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  void | [**SetManager**](#function-setmanager) (WidgetManager \* pManager) <br> |
| virtual void | [**SetScene**](#function-setscene) (const ScenePtr & scene) <br> |
| virtual void | [**SetSize**](#function-setsize) (const SR\_MATH\_NS::IVector2 & size) <br> |
| virtual void | [**Update**](#function-update) (float\_t dt) <br> |
|   | [**Widget**](#function-widget-12) () = default<br> |
|   | [**Widget**](#function-widget-22) (std::string name, SR\_MATH\_NS::IVector2 size=SR\_MATH\_NS::IVector2MAX) <br> |
|   | [**~Widget**](#function-widget) () override<br> |


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
|  std::vector&lt; [**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md) \* &gt; | [**m\_subWidgets**](#variable-m_subwidgets)  <br> |
|  WidgetFlagBits | [**m\_widgetFlags**](#variable-m_widgetflags)   = `WIDGET\_FLAG\_NONE`<br> |
















































































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddFlags**](#function-addflags) (WindowFlags flags) <br> |
|  void | [**CheckFocused**](#function-checkfocused) () <br> |
|  void | [**CheckHovered**](#function-checkhovered) () <br> |
| virtual void | [**Draw**](#function-draw) () = 0<br> |
| virtual void | [**OnClose**](#function-onclose) () <br> |
| virtual void | [**OnOpen**](#function-onopen) () <br> |
|  void | [**ResetStrongStorage**](#function-resetstrongstorage) () <br> |
|  void | [**ResetWeakStorage**](#function-resetweakstorage) () <br> |
|  void | [**SetCenter**](#function-setcenter) (bool value) <br> |
|  void | [**SetFlags**](#function-setflags) (WindowFlags flags) <br> |
|  void | [**SetName**](#function-setname) (const std::string & name) <br> |
|  void | [**TextCenter**](#function-textcenter) (const std::string & text) const<br> |


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












## Public Types Documentation




### typedef ContextPtr 

```C++
using SR_GRAPH_GUI_NS::Widget::ContextPtr =  RenderContext*;
```




<hr>



### typedef RenderScenePtr 

```C++
using SR_GRAPH_GUI_NS::Widget::RenderScenePtr =  SR_HTYPES_NS::SharedPtr<RenderScene>;
```




<hr>



### typedef ScenePtr 

```C++
using SR_GRAPH_GUI_NS::Widget::ScenePtr =  SR_HTYPES_NS::SharedPtr<SR_WORLD_NS::Scene>;
```




<hr>
## Public Functions Documentation




### function AddSubWidget 

```C++
void SR_GRAPH_GUI_NS::Widget::AddSubWidget (
    Widget * pWidget
) 
```




<hr>



### function Close 

```C++
virtual void SR_GRAPH_GUI_NS::Widget::Close () 
```




<hr>



### function DrawAsSubWindow 

```C++
void SR_GRAPH_GUI_NS::Widget::DrawAsSubWindow () 
```




<hr>



### function FixedUpdate 

```C++
inline virtual void SR_GRAPH_GUI_NS::Widget::FixedUpdate () 
```




<hr>



### function GetContext 

```C++
SR_NODISCARD ContextPtr SR_GRAPH_GUI_NS::Widget::GetContext () const
```




<hr>



### function GetManager 

```C++
inline SR_NODISCARD WidgetManager * SR_GRAPH_GUI_NS::Widget::GetManager () const
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD const std::string & SR_GRAPH_GUI_NS::Widget::GetName () const
```




<hr>



### function GetRenderScene 

```C++
SR_NODISCARD RenderScenePtr SR_GRAPH_GUI_NS::Widget::GetRenderScene () const
```




<hr>



### function GetStrongStorage 

```C++
inline SR_NODISCARD SR_HTYPES_NS::DataStorage & SR_GRAPH_GUI_NS::Widget::GetStrongStorage () const
```




<hr>



### function GetWeakStorage 

```C++
inline SR_NODISCARD SR_HTYPES_NS::DataStorage & SR_GRAPH_GUI_NS::Widget::GetWeakStorage () const
```




<hr>



### function Init 

```C++
inline virtual void SR_GRAPH_GUI_NS::Widget::Init () 
```




<hr>



### function IsFocused 

```C++
inline SR_NODISCARD bool SR_GRAPH_GUI_NS::Widget::IsFocused () const
```




<hr>



### function IsHovered 

```C++
inline SR_NODISCARD bool SR_GRAPH_GUI_NS::Widget::IsHovered () const
```




<hr>



### function IsOpen 

```C++
inline SR_NODISCARD bool SR_GRAPH_GUI_NS::Widget::IsOpen () const
```




<hr>



### function OnKeyDown 

```C++
virtual void SR_GRAPH_GUI_NS::Widget::OnKeyDown (
    const SR_UTILS_NS::KeyboardInputData * pData
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnKeyDown*](classSR__UTILS__NS_1_1InputHandler.md#function-onkeydown)


<hr>



### function OnKeyPress 

```C++
virtual void SR_GRAPH_GUI_NS::Widget::OnKeyPress (
    const SR_UTILS_NS::KeyboardInputData * pData
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnKeyPress*](classSR__UTILS__NS_1_1InputHandler.md#function-onkeypress)


<hr>



### function OnKeyUp 

```C++
virtual void SR_GRAPH_GUI_NS::Widget::OnKeyUp (
    const SR_UTILS_NS::KeyboardInputData * pData
) override
```



Implements [*SR\_UTILS\_NS::InputHandler::OnKeyUp*](classSR__UTILS__NS_1_1InputHandler.md#function-onkeyup)


<hr>



### function Open 

```C++
virtual void SR_GRAPH_GUI_NS::Widget::Open () 
```




<hr>



### function OpenFile 

```C++
inline virtual bool SR_GRAPH_GUI_NS::Widget::OpenFile (
    const SR_UTILS_NS::Path & path
) 
```




<hr>



### function SetManager 

```C++
void SR_GRAPH_GUI_NS::Widget::SetManager (
    WidgetManager * pManager
) 
```




<hr>



### function SetScene 

```C++
inline virtual void SR_GRAPH_GUI_NS::Widget::SetScene (
    const ScenePtr & scene
) 
```




<hr>



### function SetSize 

```C++
inline virtual void SR_GRAPH_GUI_NS::Widget::SetSize (
    const SR_MATH_NS::IVector2 & size
) 
```




<hr>



### function Update 

```C++
inline virtual void SR_GRAPH_GUI_NS::Widget::Update (
    float_t dt
) 
```




<hr>



### function Widget [1/2]

```C++
SR_GRAPH_GUI_NS::Widget::Widget () = default
```




<hr>



### function Widget [2/2]

```C++
inline explicit SR_GRAPH_GUI_NS::Widget::Widget (
    std::string name,
    SR_MATH_NS::IVector2 size=SR_MATH_NS::IVector2MAX
) 
```




<hr>



### function ~Widget 

```C++
SR_GRAPH_GUI_NS::Widget::~Widget () override
```




<hr>
## Protected Attributes Documentation




### variable m\_mutex 

```C++
std::recursive_mutex SR_GRAPH_GUI_NS::Widget::m_mutex;
```




<hr>



### variable m\_subWidgets 

```C++
std::vector<Widget*> SR_GRAPH_GUI_NS::Widget::m_subWidgets;
```




<hr>



### variable m\_widgetFlags 

```C++
WidgetFlagBits SR_GRAPH_GUI_NS::Widget::m_widgetFlags;
```




<hr>
## Protected Functions Documentation




### function AddFlags 

```C++
inline void SR_GRAPH_GUI_NS::Widget::AddFlags (
    WindowFlags flags
) 
```




<hr>



### function CheckFocused 

```C++
void SR_GRAPH_GUI_NS::Widget::CheckFocused () 
```




<hr>



### function CheckHovered 

```C++
void SR_GRAPH_GUI_NS::Widget::CheckHovered () 
```




<hr>



### function Draw 

```C++
virtual void SR_GRAPH_GUI_NS::Widget::Draw () = 0
```




<hr>



### function OnClose 

```C++
inline virtual void SR_GRAPH_GUI_NS::Widget::OnClose () 
```




<hr>



### function OnOpen 

```C++
inline virtual void SR_GRAPH_GUI_NS::Widget::OnOpen () 
```




<hr>



### function ResetStrongStorage 

```C++
void SR_GRAPH_GUI_NS::Widget::ResetStrongStorage () 
```




<hr>



### function ResetWeakStorage 

```C++
void SR_GRAPH_GUI_NS::Widget::ResetWeakStorage () 
```




<hr>



### function SetCenter 

```C++
inline void SR_GRAPH_GUI_NS::Widget::SetCenter (
    bool value
) 
```




<hr>



### function SetFlags 

```C++
inline void SR_GRAPH_GUI_NS::Widget::SetFlags (
    WindowFlags flags
) 
```




<hr>



### function SetName 

```C++
inline void SR_GRAPH_GUI_NS::Widget::SetName (
    const std::string & name
) 
```




<hr>



### function TextCenter 

```C++
void SR_GRAPH_GUI_NS::Widget::TextCenter (
    const std::string & text
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Widget.h`

