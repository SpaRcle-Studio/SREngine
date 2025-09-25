

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
|  void | [**DeInitialize**](#function-deinitialize) () <br> |
|  bool | [**Destroy**](#function-destroy) (const IResource::Ptr & pResource) <br>_Register resource to destroy in resource manager._  |
|  void | [**EnableStackTraceProfiling**](#function-enablestacktraceprofiling) () <br> |
|  void | [**Execute**](#function-execute) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void()&gt; & fun) <br> |
|  SR\_NODISCARD IResource::Ptr | [**Find**](#function-find-13) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) typeName) const<br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Find**](#function-find-23) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & id) <br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**Find**](#function-find-33) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |
|  SR\_NODISCARD IResource::Ptr | [**FindAnyType**](#function-findanytype) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) id) const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetCachePath**](#function-getcachepath) () const<br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetEngineResPath**](#function-getenginerespath) () const<br> |
|  SR\_NODISCARD const [**Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetEngineResPathRef**](#function-getenginerespathref) () const<br> |
|  SR\_NODISCARD [**FileSystemWatcher::Ptr**](classSR__HTYPES__NS_1_1SharedPtr.md) | [**GetFileSystemWatcher**](#function-getfilesystemwatcher) () const<br> |
|  [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; T &gt; | [**GetOrLoadResource**](#function-getorloadresource) (const [**Path**](classSR__UTILS__NS_1_1Path.md) & rawPath, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T &)&gt; & loadCallback=[**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T &)&gt;(), const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; std::string()&gt; & getPrefix=[**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; std::string()&gt;()) <br> |
|  SR\_NODISCARD [**Path**](classSR__UTILS__NS_1_1Path.md) | [**GetResPath**](#function-getrespath) () const<br> |
|  SR\_NODISCARD const [**Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetResPathRef**](#function-getrespathref) () const<br> |
|  bool | [**Initialize**](#function-initialize) (const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & resourcesFolder, const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & engineResourcesFolder) <br> |
|  void | [**InspectResources**](#function-inspectresources) (const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(ResourcesTypes &)&gt; & callback) <br> |
|  SR\_NODISCARD bool | [**IsInitialized**](#function-isinitialized) () const<br> |
|  SR\_NODISCARD bool | [**IsLastResource**](#function-islastresource) (const IResource::Ptr & pResource) <br> |
| virtual bool | [**IsSingletonCanBeDestroyed**](#function-issingletoncanbedestroyed) () override const<br> |
|  SR\_NODISCARD bool | [**IsUsePointStackTraceProfilingEnabled**](#function-isusepointstacktraceprofilingenabled) () const<br> |
|  void | [**PrintMemoryDump**](#function-printmemorydump) () <br> |
|  void | [**PullWatchers**](#function-pullwatchers) () <br> |
|  bool | [**RegisterReloader**](#function-registerreloader-12) (Args &&... args) <br> |
|  void | [**RegisterResource**](#function-registerresource) (const IResource::Ptr & pResource) <br>_Register resource in resource manager._  |
|  void | [**ReloadAll**](#function-reloadall) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) typeName) <br> |
|  void | [**ReloadResource**](#function-reloadresource) (const IResource::Ptr & pResource) <br> |
|  void | [**ReloadResources**](#function-reloadresources) (float\_t dt) <br>_Проверить хэши ресурсов и перезагрузить их, если это требуется_  |
|  bool | [**ReviveResource**](#function-reviveresource) (const IResource::Ptr & pResource) <br> |
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




### function DeInitialize 

```C++
void SR_UTILS_NS::ResourceManager::DeInitialize () 
```




<hr>



### function Destroy 

_Register resource to destroy in resource manager._ 
```C++
bool SR_UTILS_NS::ResourceManager::Destroy (
    const IResource::Ptr & pResource
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
SR_NODISCARD IResource::Ptr SR_UTILS_NS::ResourceManager::Find (
    SR_UTILS_NS::StringAtom id,
    SR_UTILS_NS::StringAtom typeName
) const
```




<hr>



### function Find [2/3]

```C++
template<typename T>
inline SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::ResourceManager::Find (
    const SR_UTILS_NS::StringAtom & id
) 
```




<hr>



### function Find [3/3]

```C++
template<typename T>
inline SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::ResourceManager::Find (
    const Path & path
) 
```




<hr>



### function FindAnyType 

```C++
SR_NODISCARD IResource::Ptr SR_UTILS_NS::ResourceManager::FindAnyType (
    SR_UTILS_NS::StringAtom id
) const
```




<hr>



### function GetCachePath 

```C++
SR_NODISCARD Path SR_UTILS_NS::ResourceManager::GetCachePath () const
```




<hr>



### function GetEngineResPath 

```C++
inline SR_NODISCARD Path SR_UTILS_NS::ResourceManager::GetEngineResPath () const
```




<hr>



### function GetEngineResPathRef 

```C++
inline SR_NODISCARD const Path & SR_UTILS_NS::ResourceManager::GetEngineResPathRef () const
```




<hr>



### function GetFileSystemWatcher 

```C++
inline SR_NODISCARD FileSystemWatcher::Ptr SR_UTILS_NS::ResourceManager::GetFileSystemWatcher () const
```




<hr>



### function GetOrLoadResource 

```C++
template<typename T>
SR_HTYPES_NS::SharedPtr < T > SR_UTILS_NS::ResourceManager::GetOrLoadResource (
    const Path & rawPath,
    const SR_HTYPES_NS::Function < void(T &)> & loadCallback=SR_HTYPES_NS::Function < void(T &)>(),
    const SR_HTYPES_NS::Function < std::string()> & getPrefix=SR_HTYPES_NS::Function < std::string()>()
) 
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



### function Initialize 

```C++
bool SR_UTILS_NS::ResourceManager::Initialize (
    const SR_UTILS_NS::Path & resourcesFolder,
    const SR_UTILS_NS::Path & engineResourcesFolder
) 
```




<hr>



### function InspectResources 

```C++
void SR_UTILS_NS::ResourceManager::InspectResources (
    const SR_HTYPES_NS::Function < void(ResourcesTypes &)> & callback
) 
```




<hr>



### function IsInitialized 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::ResourceManager::IsInitialized () const
```




<hr>



### function IsLastResource 

```C++
SR_NODISCARD bool SR_UTILS_NS::ResourceManager::IsLastResource (
    const IResource::Ptr & pResource
) 
```




<hr>



### function IsSingletonCanBeDestroyed 

```C++
inline virtual bool SR_UTILS_NS::ResourceManager::IsSingletonCanBeDestroyed () override const
```



Implements [*SR\_UTILS\_NS::SingletonBase::IsSingletonCanBeDestroyed*](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed)


<hr>



### function IsUsePointStackTraceProfilingEnabled 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::ResourceManager::IsUsePointStackTraceProfilingEnabled () const
```




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
    const IResource::Ptr & pResource
) 
```





**Warning:**

Call only from [**IResource**](classSR__UTILS__NS_1_1IResource.md) parents 





        

<hr>



### function ReloadAll 

```C++
void SR_UTILS_NS::ResourceManager::ReloadAll (
    SR_UTILS_NS::StringAtom typeName
) 
```




<hr>



### function ReloadResource 

```C++
void SR_UTILS_NS::ResourceManager::ReloadResource (
    const IResource::Ptr & pResource
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
    const IResource::Ptr & pResource
) 
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
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Resources/ResourceManager.h`

