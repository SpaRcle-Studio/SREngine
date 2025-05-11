

# Class SR\_SCRIPTING\_NS::ScriptSystem



[**ClassList**](annotated.md) **>** [**SR\_SCRIPTING\_NS**](namespaceSR__SCRIPTING__NS.md) **>** [**ScriptSystem**](classSR__SCRIPTING__NS_1_1ScriptSystem.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**ScriptSystem**](classSR__SCRIPTING__NS_1_1ScriptSystem.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |
























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const std::set&lt; std::string\_view &gt; | [**ALLOWED\_CPP\_EXTENSIONS**](#variable-allowed_cpp_extensions)   = `{ "cpp", "h", "hpp", "cxx" }`<br> |
|  const std::set&lt; std::string\_view &gt; | [**ALLOWED\_CPP\_MODULE\_EXTENSIONS**](#variable-allowed_cpp_module_extensions)   = `{ "dll", "so" }`<br> |
|  const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**ENGINE\_MODULE\_FILE\_NAME**](#variable-engine_module_file_name)   = `".module"`<br> |
























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetBuildFolderPath**](#function-getbuildfolderpath) () const<br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) &gt; & | [**GetEngineSourcesIncludePaths**](#function-getenginesourcesincludepaths) () const<br> |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetEngineSourcesPath**](#function-getenginesourcespath) () const<br> |
|  SR\_NODISCARD const [**ModuleManager**](classSR__SCRIPTING__NS_1_1ModuleManager.md) \* | [**GetModuleManager**](#function-getmodulemanager-12) () const<br> |
|  SR\_NODISCARD [**ModuleManager**](classSR__SCRIPTING__NS_1_1ModuleManager.md) \* | [**GetModuleManager**](#function-getmodulemanager-22) () <br> |
|  SR\_NODISCARD bool | [**Init**](#function-init) () <br> |
|  SR\_NODISCARD bool | [**IsInitialized**](#function-isinitialized) () const<br> |
|  void | [**ReloadModulesIfNeeded**](#function-reloadmodulesifneeded) () <br> |




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
|  std::string\_view | [**GetDynamicLibraryExtension**](#function-getdynamiclibraryextension) () <br> |


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




### typedef Ptr 

```C++
using SR_SCRIPTING_NS::ScriptSystem::Ptr =  SR_HTYPES_NS::SharedPtr<ScriptSystem>;
```




<hr>
## Public Static Attributes Documentation




### variable ALLOWED\_CPP\_EXTENSIONS 

```C++
const std::set<std::string_view> SR_SCRIPTING_NS::ScriptSystem::ALLOWED_CPP_EXTENSIONS;
```




<hr>



### variable ALLOWED\_CPP\_MODULE\_EXTENSIONS 

```C++
const std::set<std::string_view> SR_SCRIPTING_NS::ScriptSystem::ALLOWED_CPP_MODULE_EXTENSIONS;
```




<hr>



### variable ENGINE\_MODULE\_FILE\_NAME 

```C++
const SR_UTILS_NS::StringAtom SR_SCRIPTING_NS::ScriptSystem::ENGINE_MODULE_FILE_NAME;
```




<hr>
## Public Functions Documentation




### function GetBuildFolderPath 

```C++
inline SR_NODISCARD const SR_UTILS_NS::Path & SR_SCRIPTING_NS::ScriptSystem::GetBuildFolderPath () const
```




<hr>



### function GetEngineSourcesIncludePaths 

```C++
inline SR_NODISCARD const std::vector< SR_UTILS_NS::Path > & SR_SCRIPTING_NS::ScriptSystem::GetEngineSourcesIncludePaths () const
```




<hr>



### function GetEngineSourcesPath 

```C++
inline SR_NODISCARD const SR_UTILS_NS::Path & SR_SCRIPTING_NS::ScriptSystem::GetEngineSourcesPath () const
```




<hr>



### function GetModuleManager [1/2]

```C++
inline SR_NODISCARD const ModuleManager * SR_SCRIPTING_NS::ScriptSystem::GetModuleManager () const
```




<hr>



### function GetModuleManager [2/2]

```C++
inline SR_NODISCARD ModuleManager * SR_SCRIPTING_NS::ScriptSystem::GetModuleManager () 
```




<hr>



### function Init 

```C++
SR_NODISCARD bool SR_SCRIPTING_NS::ScriptSystem::Init () 
```




<hr>



### function IsInitialized 

```C++
inline SR_NODISCARD bool SR_SCRIPTING_NS::ScriptSystem::IsInitialized () const
```




<hr>



### function ReloadModulesIfNeeded 

```C++
void SR_SCRIPTING_NS::ScriptSystem::ReloadModulesIfNeeded () 
```




<hr>
## Public Static Functions Documentation




### function GetDynamicLibraryExtension 

```C++
static std::string_view SR_SCRIPTING_NS::ScriptSystem::GetDynamicLibraryExtension () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Scripting/inc/Scripting/Cpp/ScriptSystem.h`

