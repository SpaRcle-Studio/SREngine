

# Class SR\_GRAPH\_NS::AndroidWindow



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**AndroidWindow**](classSR__GRAPH__NS_1_1AndroidWindow.md)








Inherits the following classes: [SR\_GRAPH\_NS::BasicWindowImpl](classSR__GRAPH__NS_1_1BasicWindowImpl.md)
















## Public Types inherited from SR_GRAPH_NS::BasicWindowImpl

See [SR\_GRAPH\_NS::BasicWindowImpl](classSR__GRAPH__NS_1_1BasicWindowImpl.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*)&gt; | [**CloseCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#typedef-closecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*)&gt; | [**DrawCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#typedef-drawcallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, bool)&gt; | [**FocusCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#typedef-focuscallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, int32\_t, int32\_t)&gt; | [**MoveCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#typedef-movecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, int32\_t, int32\_t)&gt; | [**ResizeCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#typedef-resizecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, double\_t, double\_t)&gt; | [**ScrollCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#typedef-scrollcallback)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#typedef-super)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**AndroidWindow**](#function-androidwindow) () <br> |
|  SR\_NODISCARD ANativeWindow \* | [**GetNativeWindow**](#function-getnativewindow) () const<br> |
| virtual SR\_NODISCARD WindowType | [**GetType**](#function-gettype) () override const<br> |
| virtual bool | [**Initialize**](#function-initialize) (const std::string & name, const SR\_MATH\_NS::IVector2 & position, const SR\_MATH\_NS::UVector2 & size, bool fullScreen, bool resizable) override<br>_Вызывать только в том потоке, в котором будет использоваться окно_  |
| virtual void | [**PollEvents**](#function-pollevents) () override<br> |


## Public Functions inherited from SR_GRAPH_NS::BasicWindowImpl

See [SR\_GRAPH\_NS::BasicWindowImpl](classSR__GRAPH__NS_1_1BasicWindowImpl.md)

| Type | Name |
| ---: | :--- |
|   | [**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-basicwindowimpl) () <br> |
| virtual void | [**Centralize**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-centralize) () <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**ClientToScreen**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-clienttoscreen) (const SR\_MATH\_NS::IVector2 & pos) const<br> |
| virtual void | [**Close**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-close) () <br> |
| virtual void | [**Collapse**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-collapse) () <br> |
| virtual void | [**Expand**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-expand) () <br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-gethandle) () const<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetHeight**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-getheight) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**GetPosition**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-getposition) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**GetScreenResolution**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-getscreenresolution) () const<br> |
| virtual SR\_NODISCARD WindowState | [**GetState**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-getstate) () const<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetSurfaceHeight**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-getsurfaceheight) () const<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetSurfaceWidth**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-getsurfacewidth) () const<br> |
| virtual SR\_NODISCARD WindowType | [**GetType**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-gettype) () const = 0<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetWidth**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-getwidth) () const<br> |
| virtual bool | [**InitGUI**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-initgui) () <br> |
| virtual bool | [**Initialize**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-initialize) (const std::string & name, const SR\_MATH\_NS::IVector2 & position, const SR\_MATH\_NS::UVector2 & size, bool fullScreen, bool resizable) = 0<br>_Вызывать только в том потоке, в котором будет использоваться окно_  |
|  SR\_NODISCARD bool | [**IsClosed**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-isclosed) () const<br> |
| virtual SR\_NODISCARD bool | [**IsCollapsed**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-iscollapsed) () const<br> |
| virtual SR\_NODISCARD bool | [**IsFocused**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-isfocused) () const<br> |
| virtual bool | [**IsFullScreen**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-isfullscreen) () <br> |
| virtual SR\_NODISCARD bool | [**IsHeaderEnabled**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-isheaderenabled) () const<br> |
| virtual SR\_NODISCARD bool | [**IsMaximized**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-ismaximized) () const<br> |
| virtual SR\_NODISCARD bool | [**IsValid**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-isvalid) () const<br> |
| virtual SR\_NODISCARD bool | [**IsVisible**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-isvisible) () const<br> |
| virtual void | [**Maximize**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-maximize) () <br> |
| virtual void | [**Move**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-move) (int32\_t x, int32\_t y) <br> |
| virtual void | [**NextFrameGUI**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-nextframegui) () <br> |
| virtual void | [**PollEvents**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-pollevents) () <br> |
| virtual void | [**Resize**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-resize) (uint32\_t width, uint32\_t height) <br> |
| virtual void | [**Restore**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-restore) () <br> |
|   | [**SR\_ENUM\_CLASS\_T**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-sr_enum_class_t) (WindowType, uint8\_t, Unknown, Auto, Android, Win32, X11, GLFW, SDL) <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**ScreenToClient**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-screentoclient) (const SR\_MATH\_NS::IVector2 & pos) const<br> |
|  void | [**SetCloseCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setclosecallback) (const CloseCallback & callback) <br> |
|  void | [**SetDrawCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setdrawcallback) (const DrawCallback & callback) <br> |
|  void | [**SetFocusCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setfocuscallback) (const FocusCallback & callback) <br> |
| virtual void | [**SetHeaderEnabled**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setheaderenabled) (bool enable) <br> |
| virtual void | [**SetIcon**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-seticon) (const std::string & path) <br> |
|  void | [**SetMoveCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setmovecallback) (const MoveCallback & callback) <br> |
|  void | [**SetResizeCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setresizecallback) (const ResizeCallback & callback) <br> |
|  void | [**SetScrollCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setscrollcallback) (const ScrollCallback & callback) <br> |
| virtual void | [**SetSwapInterval**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-setswapinterval) (int interval) <br> |
| virtual bool | [**StopGUI**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-stopgui) () <br> |
| virtual void | [**SwapBuffers**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-swapbuffers) () const<br> |
|   | [**~BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-basicwindowimpl) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_GRAPH_NS::BasicWindowImpl

See [SR\_GRAPH\_NS::BasicWindowImpl](classSR__GRAPH__NS_1_1BasicWindowImpl.md)

| Type | Name |
| ---: | :--- |
|  [**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \* | [**CreatePlatformWindow**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-createplatformwindow) (WindowType type) <br> |


















## Protected Attributes inherited from SR_GRAPH_NS::BasicWindowImpl

See [SR\_GRAPH\_NS::BasicWindowImpl](classSR__GRAPH__NS_1_1BasicWindowImpl.md)

| Type | Name |
| ---: | :--- |
|  CloseCallback | [**m\_closeCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_closecallback)  <br> |
|  bool | [**m\_collapsed**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_collapsed)   = `false`<br> |
|  DrawCallback | [**m\_drawCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_drawcallback)  <br> |
|  FocusCallback | [**m\_focusCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_focuscallback)  <br> |
|  bool | [**m\_headerEnabled**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_headerenabled)   = `true`<br> |
|  bool | [**m\_isClosed**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_isclosed)   = `false`<br> |
|  bool | [**m\_isFocused**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_isfocused)   = `false`<br> |
|  bool | [**m\_isResizable**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_isresizable)   = `false`<br> |
|  bool | [**m\_isValid**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_isvalid)   = `false`<br> |
|  bool | [**m\_maximize**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_maximize)   = `false`<br> |
|  MoveCallback | [**m\_moveCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_movecallback)  <br> |
|  SR\_MATH\_NS::IVector2 | [**m\_position**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_position)  <br> |
|  ResizeCallback | [**m\_resizeCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_resizecallback)  <br> |
|  ScrollCallback | [**m\_scrollCallback**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_scrollcallback)  <br> |
|  SR\_MATH\_NS::UVector2 | [**m\_size**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_size)  <br> |
|  WindowState | [**m\_state**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_state)   = `WindowState::Default`<br> |
|  SR\_MATH\_NS::UVector2 | [**m\_surfaceSize**](classSR__GRAPH__NS_1_1BasicWindowImpl.md#variable-m_surfacesize)  <br> |


















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function AndroidWindow 

```C++
inline explicit SR_GRAPH_NS::AndroidWindow::AndroidWindow () 
```




<hr>



### function GetNativeWindow 

```C++
SR_NODISCARD ANativeWindow * SR_GRAPH_NS::AndroidWindow::GetNativeWindow () const
```




<hr>



### function GetType 

```C++
inline virtual SR_NODISCARD WindowType SR_GRAPH_NS::AndroidWindow::GetType () override const
```



Implements [*SR\_GRAPH\_NS::BasicWindowImpl::GetType*](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-gettype)


<hr>



### function Initialize 

_Вызывать только в том потоке, в котором будет использоваться окно_ 
```C++
virtual bool SR_GRAPH_NS::AndroidWindow::Initialize (
    const std::string & name,
    const SR_MATH_NS::IVector2 & position,
    const SR_MATH_NS::UVector2 & size,
    bool fullScreen,
    bool resizable
) override
```



Implements [*SR\_GRAPH\_NS::BasicWindowImpl::Initialize*](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-initialize)


<hr>



### function PollEvents 

```C++
virtual void SR_GRAPH_NS::AndroidWindow::PollEvents () override
```



Implements [*SR\_GRAPH\_NS::BasicWindowImpl::PollEvents*](classSR__GRAPH__NS_1_1BasicWindowImpl.md#function-pollevents)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Window/AndroidWindow.h`

