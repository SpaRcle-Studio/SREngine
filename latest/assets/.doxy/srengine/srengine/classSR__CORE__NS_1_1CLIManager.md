

# Class SR\_CORE\_NS::CLIManager



[**ClassList**](annotated.md) **>** [**SR\_CORE\_NS**](namespaceSR__CORE__NS.md) **>** [**CLIManager**](classSR__CORE__NS_1_1CLIManager.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD CLIFlags | [**GetFlags**](#function-getflags) () const<br> |
|  std::optional&lt; std::string &gt; | [**GetOptionValue**](#function-getoptionvalue) (CLIOptions option) <br> |
|  SR\_NODISCARD const std::map&lt; CLIOptions, std::optional&lt; std::string &gt; &gt; & | [**GetOptions**](#function-getoptions) () const<br> |
|  void | [**Init**](#function-init) (int argc, char \*\* argv) <br> |
|  bool | [**IsFlagPresent**](#function-isflagpresent) (CLIFlags flag) const<br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](#function-issingletoncanbedestroyed) () override const<br> |




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
|  SR\_MAYBE\_UNUSED T & | [**Instance**](classSR__UTILS__NS_1_1Singleton.md#function-instance) () noexcept<br>_TODO: (Multi-threading) Refactor Singleton::Instance()._  |
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
|   | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md#function-singletonbase) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |










## Public Functions Documentation




### function GetFlags 

```C++
inline SR_NODISCARD CLIFlags SR_CORE_NS::CLIManager::GetFlags () const
```




<hr>



### function GetOptionValue 

```C++
std::optional< std::string > SR_CORE_NS::CLIManager::GetOptionValue (
    CLIOptions option
) 
```




<hr>



### function GetOptions 

```C++
inline SR_NODISCARD const std::map< CLIOptions, std::optional< std::string > > & SR_CORE_NS::CLIManager::GetOptions () const
```




<hr>



### function Init 

```C++
void SR_CORE_NS::CLIManager::Init (
    int argc,
    char ** argv
) 
```




<hr>



### function IsFlagPresent 

```C++
inline bool SR_CORE_NS::CLIManager::IsFlagPresent (
    CLIFlags flag
) const
```




<hr>



### function IsSingletonCanBeDestroyed 

```C++
inline virtual bool SR_CORE_NS::CLIManager::IsSingletonCanBeDestroyed () override const
```



Implements [*SR\_UTILS\_NS::SingletonBase::IsSingletonCanBeDestroyed*](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/CLIManager.h`

