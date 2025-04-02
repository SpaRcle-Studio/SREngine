

# Class SR\_UTILS\_NS::TagManager



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**TagManager**](classSR__UTILS__NS_1_1TagManager.md)








Inherits the following classes: [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md)


































## Public Attributes

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**UNTAGGED**](#variable-untagged)   = `"Untagged"`<br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetDefaultTag**](#function-getdefaulttag) () const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetTagByIndex**](#function-gettagbyindex) (uint16\_t index) const<br> |
|  SR\_NODISCARD uint16\_t | [**GetTagIndex**](#function-gettagindex) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) tag) const<br> |
|  SR\_NODISCARD const std::vector&lt; [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & | [**GetTags**](#function-gettags) () const<br> |






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




## Public Static Functions inherited from SR_UTILS_NS::GlobalSettings

See [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md)

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**DestroySettings**](classSR__UTILS__NS_1_1GlobalSettings.md#function-destroysettings) () <br> |


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










































































## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**ClearSettings**](#function-clearsettings) () override<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**InitializeResourcePath**](#function-initializeresourcepath) () override const<br> |
|  bool | [**LoadSettings**](#function-loadsettings) (const SR\_XML\_NS::Node & node) override<br> |
|  void | [**RegisterTag**](#function-registertag) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) tag) <br> |


## Protected Functions inherited from SR_UTILS_NS::GlobalSettings

See [SR\_UTILS\_NS::GlobalSettings](classSR__UTILS__NS_1_1GlobalSettings.md)

| Type | Name |
| ---: | :--- |
|   | [**~GlobalSettings**](classSR__UTILS__NS_1_1GlobalSettings.md#function-globalsettings) () override<br> |


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












## Public Attributes Documentation




### variable UNTAGGED 

```C++
SR_INLINE_STATIC const StringAtom SR_UTILS_NS::TagManager::UNTAGGED;
```




<hr>
## Public Functions Documentation




### function GetDefaultTag 

```C++
SR_NODISCARD StringAtom SR_UTILS_NS::TagManager::GetDefaultTag () const
```




<hr>



### function GetTagByIndex 

```C++
SR_NODISCARD StringAtom SR_UTILS_NS::TagManager::GetTagByIndex (
    uint16_t index
) const
```



NOLINT 


        

<hr>



### function GetTagIndex 

```C++
SR_NODISCARD uint16_t SR_UTILS_NS::TagManager::GetTagIndex (
    StringAtom tag
) const
```




<hr>



### function GetTags 

```C++
inline SR_NODISCARD const std::vector< StringAtom > & SR_UTILS_NS::TagManager::GetTags () const
```




<hr>
## Protected Functions Documentation




### function ClearSettings 

```C++
void SR_UTILS_NS::TagManager::ClearSettings () override
```




<hr>



### function InitializeResourcePath 

```C++
SR_NODISCARD SR_UTILS_NS::Path SR_UTILS_NS::TagManager::InitializeResourcePath () override const
```




<hr>



### function LoadSettings 

```C++
bool SR_UTILS_NS::TagManager::LoadSettings (
    const SR_XML_NS::Node & node
) override
```




<hr>



### function RegisterTag 

```C++
void SR_UTILS_NS::TagManager::RegisterTag (
    StringAtom tag
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/ECS/TagManager.h`

