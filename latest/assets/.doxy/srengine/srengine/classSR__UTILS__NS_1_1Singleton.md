

# Class SR\_UTILS\_NS::Singleton

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)








Inherits the following classes: [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)


Inherited by the following classes: [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md),  [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md),  [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md),  [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md)










































































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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySingleton**](#function-destroysingleton) () <br> |
|  SR\_MAYBE\_UNUSED std::recursive\_mutex & | [**GetMutex**](#function-getmutex) () noexcept<br> |
|  SR\_MAYBE\_UNUSED T & | [**Instance**](#function-instance) () noexcept<br>_TODO: (Multi-threading) Refactor Singleton::Instance()._  |
|  SR\_MAYBE\_UNUSED bool | [**IsSingletonInitialized**](#function-issingletoninitialized) () noexcept<br> |
|  SR\_MAYBE\_UNUSED void | [**LockSingleton**](#function-locksingleton) () noexcept<br> |
|  SR\_MAYBE\_UNUSED static SR\_NODISCARD [**SR\_HTYPES\_NS::SingletonRecursiveLockGuard**](classSR__HTYPES__NS_1_1SingletonRecursiveLockGuard.md)&lt; [**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* &gt; | [**ScopeLockSingleton**](#function-scopelocksingleton) () <br> |
|  SR\_MAYBE\_UNUSED void | [**UnlockSingleton**](#function-unlocksingleton) () noexcept<br> |




















## Protected Attributes inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
|  std::recursive\_mutex | [**m\_mutex**](classSR__UTILS__NS_1_1SingletonBase.md#variable-m_mutex)  <br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**Singleton**](#function-singleton) () <br> |
|   | [**~Singleton**](#function-singleton) () override<br> |


## Protected Functions inherited from SR_UTILS_NS::SingletonBase

See [SR\_UTILS\_NS::SingletonBase](classSR__UTILS__NS_1_1SingletonBase.md)

| Type | Name |
| ---: | :--- |
| virtual [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSingletonName**](classSR__UTILS__NS_1_1SingletonBase.md#function-getsingletonname) () noexcept const = 0<br> |
| virtual void | [**InitSingleton**](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton) () <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed) () const<br> |
| virtual void | [**OnSingletonDestroy**](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy) () <br> |
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Public Static Functions Documentation




### function DestroySingleton 

```C++
static inline SR_MAYBE_UNUSED void SR_UTILS_NS::Singleton::DestroySingleton () 
```




<hr>



### function GetMutex 

```C++
static inline SR_MAYBE_UNUSED std::recursive_mutex & SR_UTILS_NS::Singleton::GetMutex () noexcept
```




<hr>



### function Instance 

_TODO: (Multi-threading) Refactor Singleton::Instance()._ 
```C++
static inline SR_MAYBE_UNUSED T & SR_UTILS_NS::Singleton::Instance () noexcept
```




<hr>



### function IsSingletonInitialized 

```C++
static inline SR_MAYBE_UNUSED bool SR_UTILS_NS::Singleton::IsSingletonInitialized () noexcept
```




<hr>



### function LockSingleton 

```C++
static inline SR_MAYBE_UNUSED void SR_UTILS_NS::Singleton::LockSingleton () noexcept
```




<hr>



### function ScopeLockSingleton 

```C++
static inline SR_MAYBE_UNUSED static SR_NODISCARD SR_HTYPES_NS::SingletonRecursiveLockGuard < Singleton < T > * > SR_UTILS_NS::Singleton::ScopeLockSingleton () 
```




<hr>



### function UnlockSingleton 

```C++
static inline SR_MAYBE_UNUSED void SR_UTILS_NS::Singleton::UnlockSingleton () noexcept
```




<hr>
## Protected Functions Documentation




### function Singleton 

```C++
inline SR_UTILS_NS::Singleton::Singleton () 
```




<hr>



### function ~Singleton 

```C++
SR_UTILS_NS::Singleton::~Singleton () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Singleton.h`

