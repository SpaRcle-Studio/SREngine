

# Class SR\_UTILS\_NS::ResourceManager



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ResourceManager**](classSR__UTILS__NS_1_1ResourceManager.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)






































## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const uint64\_t | [**ResourceLifeTime**](#variable-resourcelifetime)  <br> |
























































## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**Destroy**](#function-destroy) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br>_Register resource to destroy in resource manager._  |
|  void | [**EnableStackTraceProfiling**](#function-enablestacktraceprofiling) () <br> |
|  void | [**Execute**](#function-execute) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void()&gt; & fun) <br> |
|  SR\_NODISCARD [**IResource**](classSR__UTILS__NS_1_1IResource.md) \* | [**Find**](#function-find-13) (uint64\_t hashTypeName, const std::string & ID) <br> |
|  T \* | [**Find**](#function-find-23) (const std::string & id) <br> |
|  T \* | [**Find**](#function-find-33) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetCachePath**](#function-getcachepath) () const<br> |
|  SR\_NODISCARD [**FileSystemWatcher::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**GetFileSystemWatcher**](#function-getfilesystemwatcher) () const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetResPath**](#function-getrespath) () const<br> |
|  SR\_NODISCARD const [**Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetResPathRef**](#function-getrespathref) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetTypeName**](#function-gettypename) (Hash hashName) const<br> |
|  bool | [**Init**](#function-init) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & resourcesFolder) <br> |
|  void | [**InspectResources**](#function-inspectresources) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const ResourcesTypes &)&gt; & callback) <br> |
|  SR\_NODISCARD bool | [**IsLastResource**](#function-islastresource) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* resource) <br> |
|  SR\_NODISCARD bool | [**IsUsePointStackTraceProfilingEnabled**](#function-isusepointstacktraceprofilingenabled) () const<br> |
| virtual void | [**OnSingletonDestroy**](#function-onsingletondestroy) () override<br> |
|  void | [**PrintMemoryDump**](#function-printmemorydump) () <br> |
|  void | [**PullWatchers**](#function-pullwatchers) () <br> |
|  bool | [**RegisterReloader**](#function-registerreloader-12) (Args &&... args) <br> |
|  void | [**RegisterResource**](#function-registerresource) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br>_Register resource in resource manager._  |
|  bool | [**RegisterType**](#function-registertype-12) () <br> |
|  void | [**ReloadResource**](#function-reloadresource) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  void | [**ReloadResources**](#function-reloadresources) (float\_t dt) <br>_Проверить хэши ресурсов и перезагрузить их, если это требуется_  |
|  bool | [**ReviveResource**](#function-reviveresource) ([**IResource**](classSR__UTILS__NS_1_1IResource.md) \* pResource) <br> |
|  bool | [**Run**](#function-run) () <br> |
|  void | [**Synchronize**](#function-synchronize) (bool force) <br> |




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










## Public Static Attributes Documentation




### variable ResourceLifeTime 

```C++
const uint64_t SR_UTILS_NS::ResourceManager::ResourceLifeTime;
```




<hr>
## Public Functions Documentation




### function Destroy 

_Register resource to destroy in resource manager._ 
```C++
bool SR_UTILS_NS::ResourceManager::Destroy (
    IResource * pResource
) 
```





**Warning:**

Call only from [**IResource**](classSR__UTILS__NS_1_1IResource.md) parents 





        

<hr>



### function EnableStackTraceProfiling 

```C++
void SR_UTILS_NS::ResourceManager::EnableStackTraceProfiling () 
```




<hr>



### function Execute 

```C++
void SR_UTILS_NS::ResourceManager::Execute (
    const SR_HTYPES_NS::Function < void()> & fun
) 
```




<hr>



### function Find [1/3]

```C++
SR_NODISCARD IResource * SR_UTILS_NS::ResourceManager::Find (
    uint64_t hashTypeName,
    const std::string & ID
) 
```




<hr>



### function Find [2/3]

```C++
template<typename T>
inline T * SR_UTILS_NS::ResourceManager::Find (
    const std::string & id
) 
```




<hr>



### function Find [3/3]

```C++
template<typename T>
inline T * SR_UTILS_NS::ResourceManager::Find (
    const Path & path
) 
```




<hr>



### function GetCachePath 

```C++
SR_NODISCARD Path SR_UTILS_NS::ResourceManager::GetCachePath () const
```




<hr>



### function GetFileSystemWatcher 

```C++
inline SR_NODISCARD FileSystemWatcher::Ptr SR_UTILS_NS::ResourceManager::GetFileSystemWatcher () const
```




<hr>



### function GetResPath 

```C++
SR_NODISCARD Path SR_UTILS_NS::ResourceManager::GetResPath () const
```




<hr>



### function GetResPathRef 

```C++
SR_NODISCARD const Path & SR_UTILS_NS::ResourceManager::GetResPathRef () const
```




<hr>



### function GetTypeName 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::ResourceManager::GetTypeName (
    Hash hashName
) const
```




<hr>



### function Init 

```C++
bool SR_UTILS_NS::ResourceManager::Init (
    const SR_UTILS_NS::Path & resourcesFolder
) 
```




<hr>



### function InspectResources 

```C++
void SR_UTILS_NS::ResourceManager::InspectResources (
    const SR_HTYPES_NS::Function < void(const ResourcesTypes &)> & callback
) 
```




<hr>



### function IsLastResource 

```C++
SR_NODISCARD bool SR_UTILS_NS::ResourceManager::IsLastResource (
    IResource * resource
) 
```




<hr>



### function IsUsePointStackTraceProfilingEnabled 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::ResourceManager::IsUsePointStackTraceProfilingEnabled () const
```




<hr>



### function OnSingletonDestroy 

```C++
virtual void SR_UTILS_NS::ResourceManager::OnSingletonDestroy () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::OnSingletonDestroy*](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy)


<hr>



### function PrintMemoryDump 

```C++
void SR_UTILS_NS::ResourceManager::PrintMemoryDump () 
```




<hr>



### function PullWatchers 

```C++
void SR_UTILS_NS::ResourceManager::PullWatchers () 
```




<hr>



### function RegisterReloader [1/2]

```C++
template<typename ResourceT, typename ReloaderT, typename ... Args>
inline bool SR_UTILS_NS::ResourceManager::RegisterReloader (
    Args &&... args
) 
```




<hr>



### function RegisterResource 

_Register resource in resource manager._ 
```C++
void SR_UTILS_NS::ResourceManager::RegisterResource (
    IResource * pResource
) 
```





**Warning:**

Call only from [**IResource**](classSR__UTILS__NS_1_1IResource.md) parents 





        

<hr>



### function RegisterType [1/2]

```C++
template<typename T>
inline bool SR_UTILS_NS::ResourceManager::RegisterType () 
```




<hr>



### function ReloadResource 

```C++
void SR_UTILS_NS::ResourceManager::ReloadResource (
    IResource * pResource
) 
```




<hr>



### function ReloadResources 

_Проверить хэши ресурсов и перезагрузить их, если это требуется_ 
```C++
void SR_UTILS_NS::ResourceManager::ReloadResources (
    float_t dt
) 
```




<hr>



### function ReviveResource 

```C++
bool SR_UTILS_NS::ResourceManager::ReviveResource (
    IResource * pResource
) 
```




<hr>



### function Run 

```C++
bool SR_UTILS_NS::ResourceManager::Run () 
```




<hr>



### function Synchronize 

```C++
void SR_UTILS_NS::ResourceManager::Synchronize (
    bool force
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Resources/ResourceManager.h`

