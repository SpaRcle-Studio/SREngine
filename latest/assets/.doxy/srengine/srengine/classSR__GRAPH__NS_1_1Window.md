

# Class SR\_GRAPH\_NS::Window



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Window**](classSR__GRAPH__NS_1_1Window.md)








Inherits the following classes: [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(void)&gt; | [**CloseCallback**](#typedef-closecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(void)&gt; | [**DrawCallback**](#typedef-drawcallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(bool)&gt; | [**FocusCallback**](#typedef-focuscallback)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Window**](classSR__GRAPH__NS_1_1Window.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
| typedef [**SR\_HTYPES\_NS::SafePtr**](classSR__HTYPES__NS_1_1SafePtr.md)&lt; [**RenderContext**](classSR__GRAPH__NS_1_1RenderContext.md) &gt; | [**RenderContextPtr**](#typedef-rendercontextptr)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const SR\_MATH\_NS::UVector2 &)&gt; | [**ResizeCallback**](#typedef-resizecallback)  <br> |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(double\_t xOffset, double\_t yOffset)&gt; | [**ScrollCallback**](#typedef-scrollcallback)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Window**](classSR__GRAPH__NS_1_1Window.md) &gt; | [**Super**](#typedef-super)  <br> |
| typedef void \* | [**WindowHandle**](#typedef-windowhandle)  <br> |


## Public Types inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
| typedef [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-ptr)  <br> |
| typedef T | [**SharedPointerType**](classSR__HTYPES__NS_1_1SharedPtr.md#typedef-sharedpointertype)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**ClientToScreen**](#function-clienttoscreen) (const SR\_MATH\_NS::IVector2 & pos) const<br> |
|  void | [**Close**](#function-close) () <br> |
|  SR\_NODISCARD [**BasicWindowImpl**](classSR__GRAPH__NS_1_1BasicWindowImpl.md) \* | [**GetBaseWindow**](#function-getbasewindow) () noexcept const<br> |
|  SR\_NODISCARD WindowHandle | [**GetHandle**](#function-gethandle) () const<br> |
|  SR\_NODISCARD T \* | [**GetImplementation**](#function-getimplementation) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**GetPosition**](#function-getposition) () const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::UVector2 | [**GetSize**](#function-getsize) () const<br> |
|  bool | [**Initialize**](#function-initialize) (const std::string & name, const SR\_MATH\_NS::UVector2 & size) <br> |
|  SR\_NODISCARD bool | [**IsFullScreen**](#function-isfullscreen) () const<br> |
|  SR\_NODISCARD bool | [**IsMaximized**](#function-ismaximized) () const<br> |
|  SR\_NODISCARD bool | [**IsValid**](#function-isvalid) () const<br> |
|  SR\_NODISCARD bool | [**IsVisible**](#function-isvisible) () const<br> |
|  SR\_NODISCARD bool | [**IsWindowCollapsed**](#function-iswindowcollapsed) () const<br> |
|  SR\_NODISCARD bool | [**IsWindowFocus**](#function-iswindowfocus) () const<br> |
|  bool | [**Open**](#function-open) () <br> |
|  void | [**PollEvents**](#function-pollevents) () <br> |
|  SR\_NODISCARD SR\_MATH\_NS::IVector2 | [**ScreenToClient**](#function-screentoclient) (const SR\_MATH\_NS::IVector2 & pos) const<br> |
|  void | [**SetCloseCallback**](#function-setclosecallback) (const CloseCallback & callback) <br> |
|  void | [**SetDrawCallback**](#function-setdrawcallback) (const DrawCallback & callback) <br> |
|  void | [**SetFocusCallback**](#function-setfocuscallback) (const FocusCallback & callback) <br> |
|  void | [**SetFullScreen**](#function-setfullscreen) (bool value) <br> |
|  void | [**SetResizeCallback**](#function-setresizecallback) (const ResizeCallback & callback) <br> |
|  void | [**SetScrollCallback**](#function-setscrollcallback) (const ScrollCallback & callback) <br> |
|   | [**Window**](#function-window) () <br> |
|   | [**~Window**](#function-window) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-12) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T \*ptr)&gt; & freeFun) <br> |
|  bool | [**AutoFree**](classSR__HTYPES__NS_1_1SharedPtr.md#function-autofree-22) () <br> |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-decrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**DynamicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-dynamiccast) () const<br> |
|  SR\_NODISCARD const T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-12) () const<br> |
|  SR\_NODISCARD T \* | [**Get**](classSR__HTYPES__NS_1_1SharedPtr.md#function-get-22) () <br> |
|  SR\_NODISCARD const void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-12) () const<br> |
|  SR\_NODISCARD void \* | [**GetRawPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getrawptr-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getsrclass) () override const<br>_NOLINT(modernize-use-nodiscard)_  |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetThis**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getthis) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE const T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-12) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE T &SR\_FASTCALL | [**GetUncheckedRef**](classSR__HTYPES__NS_1_1SharedPtr.md#function-getuncheckedref-22) () <br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtr.md#function-incrementpointer) () override<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**PolymorphicCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-polymorphiccast) () const<br> |
|  SR\_NODISCARD bool | [**RecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-recursivelockifvalid) () noexcept const<br> |
|  U | [**ReinterpretCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reinterpretcast) () <br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtr.md#function-reset) () override<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtr.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) override<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-15) () = default<br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-25) (const T \* constPtr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-35) (const T \* constPtr, SR\_UTILS\_NS::SharedPtrPolicy policy) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-45) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) const & ptr) <br> |
|   | [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr-55) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md) && ptr) noexcept<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; U &gt; | [**StaticCast**](classSR__HTYPES__NS_1_1SharedPtr.md#function-staticcast) () const<br> |
|  SR\_NODISCARD bool | [**TryRecursiveLockIfValid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-tryrecursivelockifvalid) () noexcept const<br> |
|  void | [**Unlock**](classSR__HTYPES__NS_1_1SharedPtr.md#function-unlock) () noexcept const<br> |
|  bool | [**Valid**](classSR__HTYPES__NS_1_1SharedPtr.md#function-valid) () const<br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE | [**operator bool**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator-bool) () noexcept const<br> |
|  SR\_INLINE bool | [**operator!=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|  SR\_FORCE\_INLINE T & | [**operator\***](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_1) () const<br> |
|  SR\_FORCE\_INLINE T \* | [**operator-&gt;**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_2) () const<br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_3) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_4) (T \* ptr) <br> |
|  [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & | [**operator=**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_5) ([**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; && ptr) noexcept<br> |
|  SR\_INLINE bool | [**operator==**](classSR__HTYPES__NS_1_1SharedPtr.md#function-operator_6) (const [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; & right) const<br> |
|   | [**~SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md#function-sharedptr) () override<br> |


## Public Functions inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
| virtual void | [**DecrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-decrementpointer) () = 0<br> |
|  const [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-12) () const<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**GetPtrData**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getptrdata-22) () <br>_NOLINT(modernize-use-nodiscard)_  |
| virtual SR\_NODISCARD SRClass \* | [**GetSRClass**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-getsrclass) () const = 0<br> |
| virtual void | [**IncrementPointer**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-incrementpointer) () = 0<br> |
| virtual void | [**Reset**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-reset) () = 0<br> |
| virtual void | [**SetPointerFromBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-setpointerfrombase) ([**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* pBase) = 0<br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-12) () <br> |
|   | [**SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase-22) ([**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* data) <br> |
| virtual  | [**~SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md#function-sharedptrbase) () <br> |




## Public Static Functions inherited from SR_HTYPES_NS::SharedPtr

See [SR\_HTYPES\_NS::SharedPtr](classSR__HTYPES__NS_1_1SharedPtr.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; R &gt; | [**MakeShared**](classSR__HTYPES__NS_1_1SharedPtr.md#function-makeshared) (Args &&... args) <br> |




















## Protected Attributes inherited from SR_HTYPES_NS::SharedPtrBase

See [SR\_HTYPES\_NS::SharedPtrBase](classSR__HTYPES__NS_1_1SharedPtrBase.md)

| Type | Name |
| ---: | :--- |
|  bool | [**m\_basicManually**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_basicmanually)   = `false`<br> |
|  [**SharedPtrDynamicData**](structSR__HTYPES__NS_1_1SharedPtrDynamicData.md) \* | [**m\_data**](classSR__HTYPES__NS_1_1SharedPtrBase.md#variable-m_data)   = `nullptr`<br> |
























































## Public Types Documentation




### typedef CloseCallback 

```C++
using SR_GRAPH_NS::Window::CloseCallback =  SR_HTYPES_NS::Function<void(void)>;
```




<hr>



### typedef DrawCallback 

```C++
using SR_GRAPH_NS::Window::DrawCallback =  SR_HTYPES_NS::Function<void(void)>;
```




<hr>



### typedef FocusCallback 

```C++
using SR_GRAPH_NS::Window::FocusCallback =  SR_HTYPES_NS::Function<void(bool)>;
```




<hr>



### typedef Ptr 

```C++
using SR_GRAPH_NS::Window::Ptr =  SR_HTYPES_NS::SharedPtr<Window>;
```




<hr>



### typedef RenderContextPtr 

```C++
using SR_GRAPH_NS::Window::RenderContextPtr =  SR_HTYPES_NS::SafePtr<RenderContext>;
```




<hr>



### typedef ResizeCallback 

```C++
using SR_GRAPH_NS::Window::ResizeCallback =  SR_HTYPES_NS::Function<void(const SR_MATH_NS::UVector2&)>;
```




<hr>



### typedef ScrollCallback 

```C++
using SR_GRAPH_NS::Window::ScrollCallback =  SR_HTYPES_NS::Function<void(double_t xOffset, double_t yOffset)>;
```




<hr>



### typedef Super 

```C++
using SR_GRAPH_NS::Window::Super =  SR_HTYPES_NS::SharedPtr<Window>;
```




<hr>



### typedef WindowHandle 

```C++
using SR_GRAPH_NS::Window::WindowHandle =  void*;
```




<hr>
## Public Functions Documentation




### function ClientToScreen 

```C++
SR_NODISCARD SR_MATH_NS::IVector2 SR_GRAPH_NS::Window::ClientToScreen (
    const SR_MATH_NS::IVector2 & pos
) const
```




<hr>



### function Close 

```C++
void SR_GRAPH_NS::Window::Close () 
```




<hr>



### function GetBaseWindow 

```C++
inline SR_NODISCARD BasicWindowImpl * SR_GRAPH_NS::Window::GetBaseWindow () noexcept const
```




<hr>



### function GetHandle 

```C++
SR_NODISCARD WindowHandle SR_GRAPH_NS::Window::GetHandle () const
```




<hr>



### function GetImplementation 

```C++
template<typename T>
inline SR_NODISCARD T * SR_GRAPH_NS::Window::GetImplementation () const
```




<hr>



### function GetPosition 

```C++
SR_NODISCARD SR_MATH_NS::IVector2 SR_GRAPH_NS::Window::GetPosition () const
```




<hr>



### function GetSize 

```C++
SR_NODISCARD SR_MATH_NS::UVector2 SR_GRAPH_NS::Window::GetSize () const
```




<hr>



### function Initialize 

```C++
bool SR_GRAPH_NS::Window::Initialize (
    const std::string & name,
    const SR_MATH_NS::UVector2 & size
) 
```




<hr>



### function IsFullScreen 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Window::IsFullScreen () const
```




<hr>



### function IsMaximized 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Window::IsMaximized () const
```




<hr>



### function IsValid 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Window::IsValid () const
```




<hr>



### function IsVisible 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Window::IsVisible () const
```




<hr>



### function IsWindowCollapsed 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Window::IsWindowCollapsed () const
```




<hr>



### function IsWindowFocus 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Window::IsWindowFocus () const
```




<hr>



### function Open 

```C++
bool SR_GRAPH_NS::Window::Open () 
```




<hr>



### function PollEvents 

```C++
void SR_GRAPH_NS::Window::PollEvents () 
```




<hr>



### function ScreenToClient 

```C++
SR_NODISCARD SR_MATH_NS::IVector2 SR_GRAPH_NS::Window::ScreenToClient (
    const SR_MATH_NS::IVector2 & pos
) const
```




<hr>



### function SetCloseCallback 

```C++
void SR_GRAPH_NS::Window::SetCloseCallback (
    const CloseCallback & callback
) 
```




<hr>



### function SetDrawCallback 

```C++
void SR_GRAPH_NS::Window::SetDrawCallback (
    const DrawCallback & callback
) 
```




<hr>



### function SetFocusCallback 

```C++
void SR_GRAPH_NS::Window::SetFocusCallback (
    const FocusCallback & callback
) 
```




<hr>



### function SetFullScreen 

```C++
void SR_GRAPH_NS::Window::SetFullScreen (
    bool value
) 
```




<hr>



### function SetResizeCallback 

```C++
void SR_GRAPH_NS::Window::SetResizeCallback (
    const ResizeCallback & callback
) 
```




<hr>



### function SetScrollCallback 

```C++
void SR_GRAPH_NS::Window::SetScrollCallback (
    const ScrollCallback & callback
) 
```




<hr>



### function Window 

```C++
SR_GRAPH_NS::Window::Window () 
```




<hr>



### function ~Window 

```C++
SR_GRAPH_NS::Window::~Window () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Window/Window.h`

