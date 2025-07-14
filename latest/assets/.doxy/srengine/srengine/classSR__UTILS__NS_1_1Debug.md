

# Class SR\_UTILS\_NS::Debug



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Debug**](classSR__UTILS__NS_1_1Debug.md)



_@scriptableClass_ 

* `#include <Debug.h>`



Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Level**](#enum-level)  <br> |
| enum  | [**Theme**](#enum-theme)  <br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Assert**](#function-assert) (const std::string & msg) <br> |
|  bool | [**AssertOnceCheck**](#function-assertoncecheck) (const std::string & msg) <br> |
|  void | [**DeInitialize**](#function-deinitialize) () <br> |
|   | [**Debug**](#function-debug) () <br> |
|  void | [**Error**](#function-error) (const std::string & msg) <br> |
|  SR\_NODISCARD Level | [**GetLevel**](#function-getlevel) () <br> |
|  void | [**Graph**](#function-graph) (const std::string & msg) <br> |
|  void | [**Info**](#function-info) (const std::string & msg) <br> |
|  void | [**Initialize**](#function-initialize) (const std::string & log\_path, bool ShowUsedMemory, Theme colorTheme=Theme::Light) <br> |
|  SR\_NODISCARD bool | [**IsInitialized**](#function-isinitialized) () const<br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](#function-issingletoncanbedestroyed) () override const<br> |
|  void | [**Log**](#function-log) (const std::string & msg) <br> |
|  void | [**MakeCrash**](#function-makecrash) () <br> |
|  void | [**Print**](#function-print) (std::string msg, DebugLogType type) <br> |
|  void | [**Script**](#function-script) (const std::string & msg) <br> |
|  void | [**ScriptError**](#function-scripterror) (const std::string & msg) <br> |
|  void | [**ScriptLog**](#function-scriptlog) (const std::string & msg) <br> |
|  void | [**SetLevel**](#function-setlevel) (Level level) <br> |
|  void | [**Shader**](#function-shader) (const std::string & msg) <br> |
|  void | [**Success**](#function-success) (const std::string & msg) <br> |
|  void | [**System**](#function-system) (const std::string & msg) <br> |
|  void | [**TestPrint**](#function-testprint) () <br> |
|  void | [**Vulkan**](#function-vulkan) (const std::string & msg) <br> |
|  void | [**VulkanError**](#function-vulkanerror) (const std::string & msg) <br> |
|  void | [**VulkanLog**](#function-vulkanlog) (const std::string & msg) <br> |
|  void | [**Warn**](#function-warn) (const std::string & msg) <br> |
|   | [**~Debug**](#function-debug) () override<br> |




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










## Public Types Documentation




### enum Level 

```C++
enum SR_UTILS_NS::Debug::Level {
    None = 0,
    Low = 1,
    Medium = 2,
    High = 3,
    Full = 4
};
```




<hr>



### enum Theme 

```C++
enum SR_UTILS_NS::Debug::Theme {
    Dark,
    Light
};
```




<hr>
## Public Functions Documentation




### function Assert 

```C++
bool SR_UTILS_NS::Debug::Assert (
    const std::string & msg
) 
```




<hr>



### function AssertOnceCheck 

```C++
bool SR_UTILS_NS::Debug::AssertOnceCheck (
    const std::string & msg
) 
```




<hr>



### function DeInitialize 

```C++
void SR_UTILS_NS::Debug::DeInitialize () 
```




<hr>



### function Debug 

```C++
SR_UTILS_NS::Debug::Debug () 
```




<hr>



### function Error 

```C++
void SR_UTILS_NS::Debug::Error (
    const std::string & msg
) 
```




<hr>



### function GetLevel 

```C++
SR_NODISCARD Level SR_UTILS_NS::Debug::GetLevel () 
```




<hr>



### function Graph 

```C++
void SR_UTILS_NS::Debug::Graph (
    const std::string & msg
) 
```




<hr>



### function Info 

```C++
void SR_UTILS_NS::Debug::Info (
    const std::string & msg
) 
```




<hr>



### function Initialize 

```C++
void SR_UTILS_NS::Debug::Initialize (
    const std::string & log_path,
    bool ShowUsedMemory,
    Theme colorTheme=Theme::Light
) 
```




<hr>



### function IsInitialized 

```C++
SR_NODISCARD bool SR_UTILS_NS::Debug::IsInitialized () const
```




<hr>



### function IsSingletonCanBeDestroyed 

```C++
inline virtual bool SR_UTILS_NS::Debug::IsSingletonCanBeDestroyed () override const
```



Implements [*SR\_UTILS\_NS::SingletonBase::IsSingletonCanBeDestroyed*](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed)


<hr>



### function Log 

```C++
void SR_UTILS_NS::Debug::Log (
    const std::string & msg
) 
```




<hr>



### function MakeCrash 

```C++
void SR_UTILS_NS::Debug::MakeCrash () 
```




<hr>



### function Print 

```C++
void SR_UTILS_NS::Debug::Print (
    std::string msg,
    DebugLogType type
) 
```




<hr>



### function Script 

```C++
void SR_UTILS_NS::Debug::Script (
    const std::string & msg
) 
```




<hr>



### function ScriptError 

```C++
void SR_UTILS_NS::Debug::ScriptError (
    const std::string & msg
) 
```




<hr>



### function ScriptLog 

```C++
void SR_UTILS_NS::Debug::ScriptLog (
    const std::string & msg
) 
```




<hr>



### function SetLevel 

```C++
void SR_UTILS_NS::Debug::SetLevel (
    Level level
) 
```




<hr>



### function Shader 

```C++
void SR_UTILS_NS::Debug::Shader (
    const std::string & msg
) 
```




<hr>



### function Success 

```C++
void SR_UTILS_NS::Debug::Success (
    const std::string & msg
) 
```




<hr>



### function System 

```C++
void SR_UTILS_NS::Debug::System (
    const std::string & msg
) 
```




<hr>



### function TestPrint 

```C++
void SR_UTILS_NS::Debug::TestPrint () 
```




<hr>



### function Vulkan 

```C++
void SR_UTILS_NS::Debug::Vulkan (
    const std::string & msg
) 
```




<hr>



### function VulkanError 

```C++
void SR_UTILS_NS::Debug::VulkanError (
    const std::string & msg
) 
```




<hr>



### function VulkanLog 

```C++
void SR_UTILS_NS::Debug::VulkanLog (
    const std::string & msg
) 
```




<hr>



### function Warn 

```C++
void SR_UTILS_NS::Debug::Warn (
    const std::string & msg
) 
```




<hr>



### function ~Debug 

```C++
SR_UTILS_NS::Debug::~Debug () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Debug.h`

