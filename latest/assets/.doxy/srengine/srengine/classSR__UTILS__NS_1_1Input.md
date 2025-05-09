

# Class SR\_UTILS\_NS::Input



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Input**](classSR__UTILS__NS_1_1Input.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md),  [SR\_UTILS\_NS::SubscriptionHolder](classSR__UTILS__NS_1_1SubscriptionHolder.md)


















































































































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Check**](#function-check) () <br> |
|  void | [**ForceUnlockCursor**](#function-forceunlockcursor) () <br> |
|  bool | [**GetKey**](#function-getkey) (KeyCode key) <br> |
|  bool | [**GetKeyDown**](#function-getkeydown) (KeyCode key) <br> |
|  bool | [**GetKeyUp**](#function-getkeyup) (KeyCode key) <br> |
|  bool | [**GetMouse**](#function-getmouse) (MouseCode code) <br> |
|  bool | [**GetMouseDown**](#function-getmousedown) (MouseCode code) <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetMouseDrag**](#function-getmousedrag) () <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetMousePos**](#function-getmousepos) () const<br> |
|  bool | [**GetMouseUp**](#function-getmouseup) (MouseCode code) <br> |
|  int32\_t | [**GetMouseWheel**](#function-getmousewheel) () <br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetPrevMousePos**](#function-getprevmousepos) () const<br> |
|  SR\_NODISCARD bool | [**IsMouseMoved**](#function-ismousemoved) () const<br> |
|  void | [**LockCursor**](#function-lockcursor) () <br> |
|  void | [**Reload**](#function-reload) () <br> |
|  void | [**ResetMouse**](#function-resetmouse) () <br> |
|  void | [**SetCursorLockCallback**](#function-setcursorlockcallback) (CursorLockCallback && callback) <br> |
|  void | [**SetCursorVisible**](#function-setcursorvisible) (bool isVisible) <br> |
|  void | [**SetMouseScroll**](#function-setmousescroll) (double\_t xOffset, double\_t yOffset) <br> |
|  void | [**UnlockCursor**](#function-unlockcursor) () <br> |




## Public Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|   | [**~SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Functions inherited from SR_UTILS_NS::SubscriptionHolder

See [SR\_UTILS\_NS::SubscriptionHolder](classSR__UTILS__NS_1_1SubscriptionHolder.md)

| Type | Name |
| ---: | :--- |
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-12) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) <br> |
|  void | [**Broadcast**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-broadcast-22) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) & message) <br> |
|  SR\_NODISCARD bool | [**HasSubscriptions**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-hassubscriptions) () noexcept const<br> |
|  SR\_NODISCARD [**Subscription**](classSR__UTILS__NS_1_1Subscription.md) | [**Subscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscribe) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**SubscriptionMessage**](classSR__UTILS__NS_1_1SubscriptionMessage.md) &)&gt; && callback) <br> |
|   | [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder-13) () <br> |
|   | [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder-23) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & other) = delete<br> |
|   | [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder-33) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) && other) = delete<br> |
|  void | [**Unsubscribe**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-unsubscribe) (const [**SubscriptionInternalInfo**](classSR__UTILS__NS_1_1SubscriptionInternalInfo.md) \* pSubscription) <br> |
|  [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & | [**operator=**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-operator) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & other) = delete<br> |
|  [**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) & | [**operator=**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-operator_1) ([**SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md) && other) = delete<br> |
| virtual  | [**~SubscriptionHolder**](classSR__UTILS__NS_1_1SubscriptionHolder.md#function-subscriptionholder) () <br> |




## Public Static Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](classSR__UTILS__NS_1_1Singleton.md#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](classSR__UTILS__NS_1_1Singleton.md#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br> |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](classSR__UTILS__NS_1_1Singleton.md#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](classSR__UTILS__NS_1_1Singleton.md#function-unlocksingleton) () noexcept<br> |
































## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |












































































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**~Input**](#function-input) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::Singleton

See [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () <br> |
|   | [**~Singleton**](classSR__UTILS__NS_1_1Singleton.md#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () <br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |














## Public Functions Documentation




### function Check 

```C++
void SR_UTILS_NS::Input::Check () 
```




<hr>



### function ForceUnlockCursor 

```C++
void SR_UTILS_NS::Input::ForceUnlockCursor () 
```




<hr>



### function GetKey 

```C++
bool SR_UTILS_NS::Input::GetKey (
    KeyCode key
) 
```




<hr>



### function GetKeyDown 

```C++
bool SR_UTILS_NS::Input::GetKeyDown (
    KeyCode key
) 
```




<hr>



### function GetKeyUp 

```C++
bool SR_UTILS_NS::Input::GetKeyUp (
    KeyCode key
) 
```




<hr>



### function GetMouse 

```C++
bool SR_UTILS_NS::Input::GetMouse (
    MouseCode code
) 
```




<hr>



### function GetMouseDown 

```C++
bool SR_UTILS_NS::Input::GetMouseDown (
    MouseCode code
) 
```




<hr>



### function GetMouseDrag 

```C++
SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::Input::GetMouseDrag () 
```




<hr>



### function GetMousePos 

```C++
SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::Input::GetMousePos () const
```




<hr>



### function GetMouseUp 

```C++
bool SR_UTILS_NS::Input::GetMouseUp (
    MouseCode code
) 
```




<hr>



### function GetMouseWheel 

```C++
int32_t SR_UTILS_NS::Input::GetMouseWheel () 
```




<hr>



### function GetPrevMousePos 

```C++
SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::Input::GetPrevMousePos () const
```




<hr>



### function IsMouseMoved 

```C++
SR_NODISCARD bool SR_UTILS_NS::Input::IsMouseMoved () const
```




<hr>



### function LockCursor 

```C++
void SR_UTILS_NS::Input::LockCursor () 
```




<hr>



### function Reload 

```C++
void SR_UTILS_NS::Input::Reload () 
```




<hr>



### function ResetMouse 

```C++
void SR_UTILS_NS::Input::ResetMouse () 
```




<hr>



### function SetCursorLockCallback 

```C++
void SR_UTILS_NS::Input::SetCursorLockCallback (
    CursorLockCallback && callback
) 
```




<hr>



### function SetCursorVisible 

```C++
void SR_UTILS_NS::Input::SetCursorVisible (
    bool isVisible
) 
```




<hr>



### function SetMouseScroll 

```C++
void SR_UTILS_NS::Input::SetMouseScroll (
    double_t xOffset,
    double_t yOffset
) 
```




<hr>



### function UnlockCursor 

```C++
void SR_UTILS_NS::Input::UnlockCursor () 
```




<hr>
## Protected Functions Documentation




### function ~Input 

```C++
SR_UTILS_NS::Input::~Input () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Input/InputSystem.h`

