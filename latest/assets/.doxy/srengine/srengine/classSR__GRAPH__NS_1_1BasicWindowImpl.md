

# Class SR\_GRAPH\_NS::BasicWindowImpl



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_GRAPH\_NS::AndroidWindow](classSR__GRAPH__NS_1_1AndroidWindow.md),  [SR\_GRAPH\_NS::GLFWWindow](classSR__GRAPH__NS_1_1GLFWWindow.md),  [SR\_GRAPH\_NS::Win32Window](classSR__GRAPH__NS_1_1Win32Window.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*)&gt; | [**CloseCallback**](#typedef-closecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*)&gt; | [**DrawCallback**](#typedef-drawcallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, bool)&gt; | [**FocusCallback**](#typedef-focuscallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, int32\_t, int32\_t)&gt; | [**MoveCallback**](#typedef-movecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, int32\_t, int32\_t)&gt; | [**ResizeCallback**](#typedef-resizecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \*, double\_t, double\_t)&gt; | [**ScrollCallback**](#typedef-scrollcallback)  <br> |
| typedef [**SR\_UTILS\_NS::NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) | [**Super**](#typedef-super)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BasicWindowImpl**](#function-basicwindowimpl) () <br> |
| virtual void | [**Centralize**](#function-centralize) () <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**ClientToScreen**](#function-clienttoscreen) (const SR\_MATH\_NS::IVector2 & pos) const<br> |
| virtual void | [**Close**](#function-close) () <br> |
| virtual void | [**Collapse**](#function-collapse) () <br> |
| virtual void | [**Expand**](#function-expand) () <br> |
| virtual SR\_NODISCARD void \* | [**GetHandle**](#function-gethandle) () const<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetHeight**](#function-getheight) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**GetPosition**](#function-getposition) () const<br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**GetScreenResolution**](#function-getscreenresolution) () const<br> |
| virtual SR\_NODISCARD WindowState | [**GetState**](#function-getstate) () const<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetSurfaceHeight**](#function-getsurfaceheight) () const<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetSurfaceWidth**](#function-getsurfacewidth) () const<br> |
| virtual SR\_NODISCARD WindowType | [**GetType**](#function-gettype) () const = 0<br> |
| virtual SR\_NODISCARD uint32\_t | [**GetWidth**](#function-getwidth) () const<br> |
| virtual bool | [**InitGUI**](#function-initgui) () <br> |
| virtual bool | [**Initialize**](#function-initialize) (const std::string & name, const SR\_MATH\_NS::IVector2 & position, const SR\_MATH\_NS::UVector2 & size, bool fullScreen, bool resizable) = 0<br>_Вызывать только в том потоке, в котором будет использоваться окно_  |
|  SR\_NODISCARD bool | [**IsClosed**](#function-isclosed) () const<br> |
| virtual SR\_NODISCARD bool | [**IsCollapsed**](#function-iscollapsed) () const<br> |
| virtual SR\_NODISCARD bool | [**IsFocused**](#function-isfocused) () const<br> |
| virtual bool | [**IsFullScreen**](#function-isfullscreen) () <br> |
| virtual SR\_NODISCARD bool | [**IsHeaderEnabled**](#function-isheaderenabled) () const<br> |
| virtual SR\_NODISCARD bool | [**IsMaximized**](#function-ismaximized) () const<br> |
| virtual SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
| virtual SR\_NODISCARD bool | [**IsVisible**](#function-isvisible) () const<br> |
| virtual void | [**Maximize**](#function-maximize) () <br> |
| virtual void | [**Move**](#function-move) (int32\_t x, int32\_t y) <br> |
| virtual void | [**NextFrameGUI**](#function-nextframegui) () <br> |
| virtual void | [**PollEvents**](#function-pollevents) () <br> |
| virtual void | [**Resize**](#function-resize) (uint32\_t width, uint32\_t height) <br> |
| virtual void | [**Restore**](#function-restore) () <br> |
|   | [**SR\_ENUM\_CLASS\_T**](#function-sr_enum_class_t) (WindowType, uint8\_t, Unknown, Auto, Android, Win32, X11, GLFW, SDL) <br> |
| virtual SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**ScreenToClient**](#function-screentoclient) (const SR\_MATH\_NS::IVector2 & pos) const<br> |
|  void | [**SetCloseCallback**](#function-setclosecallback) (const CloseCallback & callback) <br> |
|  void | [**SetDrawCallback**](#function-setdrawcallback) (const DrawCallback & callback) <br> |
|  void | [**SetFocusCallback**](#function-setfocuscallback) (const FocusCallback & callback) <br> |
| virtual void | [**SetHeaderEnabled**](#function-setheaderenabled) (bool enable) <br> |
| virtual void | [**SetIcon**](#function-seticon) (const std::string & path) <br> |
|  void | [**SetMoveCallback**](#function-setmovecallback) (const MoveCallback & callback) <br> |
|  void | [**SetResizeCallback**](#function-setresizecallback) (const ResizeCallback & callback) <br> |
|  void | [**SetScrollCallback**](#function-setscrollcallback) (const ScrollCallback & callback) <br> |
| virtual void | [**SetSwapInterval**](#function-setswapinterval) (int interval) <br> |
| virtual bool | [**StopGUI**](#function-stopgui) () <br> |
| virtual void | [**SwapBuffers**](#function-swapbuffers) () const<br> |
|   | [**~BasicWindowImpl**](#function-basicwindowimpl) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \* | [**CreatePlatformWindow**](#function-createplatformwindow) (WindowType type) <br> |












## Protected Attributes

| Type | Name |
| ---: | :--- |
|  CloseCallback | [**m\_closeCallback**](#variable-m_closecallback)  <br> |
|  bool | [**m\_collapsed**](#variable-m_collapsed)   = `false`<br> |
|  DrawCallback | [**m\_drawCallback**](#variable-m_drawcallback)  <br> |
|  FocusCallback | [**m\_focusCallback**](#variable-m_focuscallback)  <br> |
|  bool | [**m\_headerEnabled**](#variable-m_headerenabled)   = `true`<br> |
|  bool | [**m\_isClosed**](#variable-m_isclosed)   = `false`<br> |
|  bool | [**m\_isFocused**](#variable-m_isfocused)   = `false`<br> |
|  bool | [**m\_isResizable**](#variable-m_isresizable)   = `false`<br> |
|  bool | [**m\_isValid**](#variable-m_isvalid)   = `false`<br> |
|  bool | [**m\_maximize**](#variable-m_maximize)   = `false`<br> |
|  MoveCallback | [**m\_moveCallback**](#variable-m_movecallback)  <br> |
|  SR\_MATH\_NS::IVector2 | [**m\_position**](#variable-m_position)  <br> |
|  ResizeCallback | [**m\_resizeCallback**](#variable-m_resizecallback)  <br> |
|  ScrollCallback | [**m\_scrollCallback**](#variable-m_scrollcallback)  <br> |
|  SR\_MATH\_NS::UVector2 | [**m\_size**](#variable-m_size)  <br> |
|  WindowState | [**m\_state**](#variable-m_state)   = `WindowState::Default`<br> |
|  SR\_MATH\_NS::UVector2 | [**m\_surfaceSize**](#variable-m_surfacesize)  <br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef CloseCallback 

```C++
using SR_GRAPH_NS::BasicWindowImpl::CloseCallback =  SR_HTYPES_NS::Function<void(BasicWindowImpl*)>;
```




<hr>



### typedef DrawCallback 

```C++
using SR_GRAPH_NS::BasicWindowImpl::DrawCallback =  SR_HTYPES_NS::Function<void(BasicWindowImpl*)>;
```




<hr>



### typedef FocusCallback 

```C++
using SR_GRAPH_NS::BasicWindowImpl::FocusCallback =  SR_HTYPES_NS::Function<void(BasicWindowImpl*, bool)>;
```




<hr>



### typedef MoveCallback 

```C++
using SR_GRAPH_NS::BasicWindowImpl::MoveCallback =  SR_HTYPES_NS::Function<void(BasicWindowImpl*, int32_t, int32_t)>;
```




<hr>



### typedef ResizeCallback 

```C++
using SR_GRAPH_NS::BasicWindowImpl::ResizeCallback =  SR_HTYPES_NS::Function<void(BasicWindowImpl*, int32_t, int32_t)>;
```




<hr>



### typedef ScrollCallback 

```C++
using SR_GRAPH_NS::BasicWindowImpl::ScrollCallback =  SR_HTYPES_NS::Function<void(BasicWindowImpl*, double_t, double_t)>;
```




<hr>



### typedef Super 

```C++
using SR_GRAPH_NS::BasicWindowImpl::Super =  SR_UTILS_NS::NonCopyable;
```




<hr>
## Public Functions Documentation




### function BasicWindowImpl 

```C++
inline explicit SR_GRAPH_NS::BasicWindowImpl::BasicWindowImpl () 
```




<hr>



### function Centralize 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Centralize () 
```




<hr>



### function ClientToScreen 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::IVector2 SR_GRAPH_NS::BasicWindowImpl::ClientToScreen (
    const SR_MATH_NS::IVector2 & pos
) const
```




<hr>



### function Close 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Close () 
```




<hr>



### function Collapse 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Collapse () 
```




<hr>



### function Expand 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Expand () 
```




<hr>



### function GetHandle 

```C++
virtual SR_NODISCARD void * SR_GRAPH_NS::BasicWindowImpl::GetHandle () const
```




<hr>



### function GetHeight 

```C++
inline virtual SR_NODISCARD uint32_t SR_GRAPH_NS::BasicWindowImpl::GetHeight () const
```




<hr>



### function GetPosition 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::IVector2 SR_GRAPH_NS::BasicWindowImpl::GetPosition () const
```




<hr>



### function GetScreenResolution 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::IVector2 SR_GRAPH_NS::BasicWindowImpl::GetScreenResolution () const
```




<hr>



### function GetState 

```C++
inline virtual SR_NODISCARD WindowState SR_GRAPH_NS::BasicWindowImpl::GetState () const
```




<hr>



### function GetSurfaceHeight 

```C++
inline virtual SR_NODISCARD uint32_t SR_GRAPH_NS::BasicWindowImpl::GetSurfaceHeight () const
```




<hr>



### function GetSurfaceWidth 

```C++
inline virtual SR_NODISCARD uint32_t SR_GRAPH_NS::BasicWindowImpl::GetSurfaceWidth () const
```




<hr>



### function GetType 

```C++
virtual SR_NODISCARD WindowType SR_GRAPH_NS::BasicWindowImpl::GetType () const = 0
```




<hr>



### function GetWidth 

```C++
inline virtual SR_NODISCARD uint32_t SR_GRAPH_NS::BasicWindowImpl::GetWidth () const
```




<hr>



### function InitGUI 

```C++
inline virtual bool SR_GRAPH_NS::BasicWindowImpl::InitGUI () 
```




<hr>



### function Initialize 

_Вызывать только в том потоке, в котором будет использоваться окно_ 
```C++
virtual bool SR_GRAPH_NS::BasicWindowImpl::Initialize (
    const std::string & name,
    const SR_MATH_NS::IVector2 & position,
    const SR_MATH_NS::UVector2 & size,
    bool fullScreen,
    bool resizable
) = 0
```




<hr>



### function IsClosed 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::BasicWindowImpl::IsClosed () const
```




<hr>



### function IsCollapsed 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::BasicWindowImpl::IsCollapsed () const
```




<hr>



### function IsFocused 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::BasicWindowImpl::IsFocused () const
```




<hr>



### function IsFullScreen 

```C++
inline virtual bool SR_GRAPH_NS::BasicWindowImpl::IsFullScreen () 
```




<hr>



### function IsHeaderEnabled 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::BasicWindowImpl::IsHeaderEnabled () const
```




<hr>



### function IsMaximized 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::BasicWindowImpl::IsMaximized () const
```




<hr>



### function IsValid 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::BasicWindowImpl::IsValid () const
```




<hr>



### function IsVisible 

```C++
inline virtual SR_NODISCARD bool SR_GRAPH_NS::BasicWindowImpl::IsVisible () const
```




<hr>



### function Maximize 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Maximize () 
```




<hr>



### function Move 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Move (
    int32_t x,
    int32_t y
) 
```




<hr>



### function NextFrameGUI 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::NextFrameGUI () 
```




<hr>



### function PollEvents 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::PollEvents () 
```




<hr>



### function Resize 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Resize (
    uint32_t width,
    uint32_t height
) 
```




<hr>



### function Restore 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::Restore () 
```




<hr>



### function SR\_ENUM\_CLASS\_T 

```C++
SR_GRAPH_NS::BasicWindowImpl::SR_ENUM_CLASS_T (
    WindowType,
    uint8_t,
    Unknown,
    Auto,
    Android,
    Win32,
    X11,
    GLFW,
    SDL
) 
```




<hr>



### function ScreenToClient 

```C++
inline virtual SR_NODISCARD SR_MATH_NS::IVector2 SR_GRAPH_NS::BasicWindowImpl::ScreenToClient (
    const SR_MATH_NS::IVector2 & pos
) const
```




<hr>



### function SetCloseCallback 

```C++
void SR_GRAPH_NS::BasicWindowImpl::SetCloseCallback (
    const CloseCallback & callback
) 
```




<hr>



### function SetDrawCallback 

```C++
void SR_GRAPH_NS::BasicWindowImpl::SetDrawCallback (
    const DrawCallback & callback
) 
```




<hr>



### function SetFocusCallback 

```C++
void SR_GRAPH_NS::BasicWindowImpl::SetFocusCallback (
    const FocusCallback & callback
) 
```




<hr>



### function SetHeaderEnabled 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::SetHeaderEnabled (
    bool enable
) 
```




<hr>



### function SetIcon 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::SetIcon (
    const std::string & path
) 
```




<hr>



### function SetMoveCallback 

```C++
void SR_GRAPH_NS::BasicWindowImpl::SetMoveCallback (
    const MoveCallback & callback
) 
```




<hr>



### function SetResizeCallback 

```C++
void SR_GRAPH_NS::BasicWindowImpl::SetResizeCallback (
    const ResizeCallback & callback
) 
```




<hr>



### function SetScrollCallback 

```C++
void SR_GRAPH_NS::BasicWindowImpl::SetScrollCallback (
    const ScrollCallback & callback
) 
```




<hr>



### function SetSwapInterval 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::SetSwapInterval (
    int interval
) 
```




<hr>



### function StopGUI 

```C++
inline virtual bool SR_GRAPH_NS::BasicWindowImpl::StopGUI () 
```




<hr>



### function SwapBuffers 

```C++
inline virtual void SR_GRAPH_NS::BasicWindowImpl::SwapBuffers () const
```




<hr>



### function ~BasicWindowImpl 

```C++
SR_GRAPH_NS::BasicWindowImpl::~BasicWindowImpl () override
```




<hr>
## Public Static Functions Documentation




### function CreatePlatformWindow 

```C++
static BasicWindowImpl * SR_GRAPH_NS::BasicWindowImpl::CreatePlatformWindow (
    WindowType type
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_closeCallback 

```C++
CloseCallback SR_GRAPH_NS::BasicWindowImpl::m_closeCallback;
```




<hr>



### variable m\_collapsed 

```C++
bool SR_GRAPH_NS::BasicWindowImpl::m_collapsed;
```




<hr>



### variable m\_drawCallback 

```C++
DrawCallback SR_GRAPH_NS::BasicWindowImpl::m_drawCallback;
```




<hr>



### variable m\_focusCallback 

```C++
FocusCallback SR_GRAPH_NS::BasicWindowImpl::m_focusCallback;
```




<hr>



### variable m\_headerEnabled 

```C++
bool SR_GRAPH_NS::BasicWindowImpl::m_headerEnabled;
```




<hr>



### variable m\_isClosed 

```C++
bool SR_GRAPH_NS::BasicWindowImpl::m_isClosed;
```




<hr>



### variable m\_isFocused 

```C++
bool SR_GRAPH_NS::BasicWindowImpl::m_isFocused;
```




<hr>



### variable m\_isResizable 

```C++
bool SR_GRAPH_NS::BasicWindowImpl::m_isResizable;
```




<hr>



### variable m\_isValid 

```C++
bool SR_GRAPH_NS::BasicWindowImpl::m_isValid;
```




<hr>



### variable m\_maximize 

```C++
bool SR_GRAPH_NS::BasicWindowImpl::m_maximize;
```




<hr>



### variable m\_moveCallback 

```C++
MoveCallback SR_GRAPH_NS::BasicWindowImpl::m_moveCallback;
```




<hr>



### variable m\_position 

```C++
SR_MATH_NS::IVector2 SR_GRAPH_NS::BasicWindowImpl::m_position;
```




<hr>



### variable m\_resizeCallback 

```C++
ResizeCallback SR_GRAPH_NS::BasicWindowImpl::m_resizeCallback;
```




<hr>



### variable m\_scrollCallback 

```C++
ScrollCallback SR_GRAPH_NS::BasicWindowImpl::m_scrollCallback;
```




<hr>



### variable m\_size 

```C++
SR_MATH_NS::UVector2 SR_GRAPH_NS::BasicWindowImpl::m_size;
```




<hr>



### variable m\_state 

```C++
WindowState SR_GRAPH_NS::BasicWindowImpl::m_state;
```




<hr>



### variable m\_surfaceSize 

```C++
SR_MATH_NS::UVector2 SR_GRAPH_NS::BasicWindowImpl::m_surfaceSize;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Window/BasicWindowImpl.h`

