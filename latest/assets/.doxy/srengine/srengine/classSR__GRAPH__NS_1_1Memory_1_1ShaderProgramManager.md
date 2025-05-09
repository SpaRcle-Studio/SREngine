

# Class SR\_GRAPH\_NS::Memory::ShaderProgramManager



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**ShaderProgramManager**](classSR__GRAPH__NS_1_1Memory_1_1ShaderProgramManager.md)



[More...](#detailed-description)

* `#include <ShaderProgramManager.h>`



Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; | [**PipelinePtr**](#typedef-pipelineptr)  <br> |
| typedef int32\_t | [**ShaderProgram**](#typedef-shaderprogram)  <br> |
| typedef int32\_t | [**VirtualProgram**](#typedef-virtualprogram)  <br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD VirtualProgram | [**Allocate**](#function-allocate) (const [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) & createInfo) <br> |
|  ShaderBindResult | [**BindProgram**](#function-bindprogram) (VirtualProgram virtualProgram) noexcept<br> |
|  void | [**CollectUnused**](#function-collectunused) () <br> |
|  bool | [**FreeProgram**](#function-freeprogram-12) (VirtualProgram \* program) <br> |
|  bool | [**FreeProgram**](#function-freeprogram-22) (VirtualProgram program) <br> |
|  SR\_NODISCARD const [**VirtualProgramInfo**](structSR__GRAPH__NS_1_1Memory_1_1VirtualProgramInfo.md) \* | [**GetInfo**](#function-getinfo) (VirtualProgram virtualProgram) noexcept const<br> |
|  SR\_NODISCARD ShaderProgram | [**GetProgram**](#function-getprogram) (VirtualProgram virtualProgram) noexcept const<br> |
|  SR\_NODISCARD bool | [**HasProgram**](#function-hasprogram) (VirtualProgram virtualProgram) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsAvailable**](#function-isavailable) (VirtualProgram virtualProgram) noexcept const<br> |
|  SR\_NODISCARD VirtualProgram | [**ReAllocate**](#function-reallocate) (VirtualProgram program, const [**SRShaderCreateInfo**](structSR__GRAPH__NS_1_1SRShaderCreateInfo.md) & createInfo) <br> |
|  void | [**SetPipeline**](#function-setpipeline) (PipelinePtr pPipeline) <br> |




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




























































## Protected Functions

| Type | Name |
| ---: | :--- |
| virtual void | [**OnSingletonDestroy**](#function-onsingletondestroy) () override<br> |


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










## Detailed Description


Класс реализует возможность рендера одного объекта в несколько кадровых буферов 


    
## Public Types Documentation




### typedef PipelinePtr 

```C++
using SR_GRAPH_NS::Memory::ShaderProgramManager::PipelinePtr =  SR_HTYPES_NS::SharedPtr<Pipeline>;
```




<hr>



### typedef ShaderProgram 

```C++
using SR_GRAPH_NS::Memory::ShaderProgramManager::ShaderProgram =  int32_t;
```




<hr>



### typedef VirtualProgram 

```C++
using SR_GRAPH_NS::Memory::ShaderProgramManager::VirtualProgram =  int32_t;
```




<hr>
## Public Functions Documentation




### function Allocate 

```C++
SR_NODISCARD VirtualProgram SR_GRAPH_NS::Memory::ShaderProgramManager::Allocate (
    const SRShaderCreateInfo & createInfo
) 
```




<hr>



### function BindProgram 

```C++
ShaderBindResult SR_GRAPH_NS::Memory::ShaderProgramManager::BindProgram (
    VirtualProgram virtualProgram
) noexcept
```




<hr>



### function CollectUnused 

```C++
void SR_GRAPH_NS::Memory::ShaderProgramManager::CollectUnused () 
```




<hr>



### function FreeProgram [1/2]

```C++
bool SR_GRAPH_NS::Memory::ShaderProgramManager::FreeProgram (
    VirtualProgram * program
) 
```




<hr>



### function FreeProgram [2/2]

```C++
bool SR_GRAPH_NS::Memory::ShaderProgramManager::FreeProgram (
    VirtualProgram program
) 
```




<hr>



### function GetInfo 

```C++
SR_NODISCARD const VirtualProgramInfo * SR_GRAPH_NS::Memory::ShaderProgramManager::GetInfo (
    VirtualProgram virtualProgram
) noexcept const
```




<hr>



### function GetProgram 

```C++
SR_NODISCARD ShaderProgram SR_GRAPH_NS::Memory::ShaderProgramManager::GetProgram (
    VirtualProgram virtualProgram
) noexcept const
```




<hr>



### function HasProgram 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Memory::ShaderProgramManager::HasProgram (
    VirtualProgram virtualProgram
) noexcept const
```




<hr>



### function IsAvailable 

```C++
SR_NODISCARD bool SR_GRAPH_NS::Memory::ShaderProgramManager::IsAvailable (
    VirtualProgram virtualProgram
) noexcept const
```




<hr>



### function ReAllocate 

```C++
SR_NODISCARD VirtualProgram SR_GRAPH_NS::Memory::ShaderProgramManager::ReAllocate (
    VirtualProgram program,
    const SRShaderCreateInfo & createInfo
) 
```




<hr>



### function SetPipeline 

```C++
inline void SR_GRAPH_NS::Memory::ShaderProgramManager::SetPipeline (
    PipelinePtr pPipeline
) 
```




<hr>
## Protected Functions Documentation




### function OnSingletonDestroy 

```C++
virtual void SR_GRAPH_NS::Memory::ShaderProgramManager::OnSingletonDestroy () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::OnSingletonDestroy*](classSR__UTILS__NS_1_1SingletonBase.md#function-onsingletondestroy)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Memory/ShaderProgramManager.h`

