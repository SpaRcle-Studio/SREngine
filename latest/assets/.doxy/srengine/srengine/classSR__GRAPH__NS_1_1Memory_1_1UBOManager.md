

# Class SR\_GRAPH\_NS::Memory::UBOManager



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**Memory**](namespaceSR__GRAPH__NS_1_1Memory.md) **>** [**UBOManager**](classSR__GRAPH__NS_1_1Memory_1_1UBOManager.md)



[More...](#detailed-description)

* `#include <UBOManager.h>`



Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**BindResult**](#enum-bindresult)  <br> |
| typedef int32\_t | [**UBO**](#typedef-ubo)  <br> |
| typedef int32\_t | [**VirtualUBO**](#typedef-virtualubo)  <br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD VirtualUBO | [**AllocateUBO**](#function-allocateubo-13) (VirtualUBO virtualUbo, uint32\_t uboSize, bool shared) <br> |
|  SR\_NODISCARD VirtualUBO | [**AllocateUBO**](#function-allocateubo-23) (VirtualUBO virtualUbo, uint32\_t uboSize) <br> |
|  SR\_NODISCARD VirtualUBO | [**AllocateUBO**](#function-allocateubo-33) (VirtualUBO virtualUbo) <br> |
|  BindResult | [**BindNoDublicateUBO**](#function-bindnodublicateubo) (VirtualUBO virtualUbo) noexcept<br> |
|  BindResult | [**BindUBO**](#function-bindubo-12) (VirtualUBO virtualUbo) noexcept<br> |
|  BindResult | [**BindUBO**](#function-bindubo-22) (VirtualUBO virtualUbo, uint32\_t uboSize) noexcept<br> |
|  void | [**CollectUnused**](#function-collectunused) () <br> |
|  bool | [**FreeUBO**](#function-freeubo) (VirtualUBO \* ubo) <br> |
|  SR\_NODISCARD UBO | [**GetUBO**](#function-getubo) (VirtualUBO virtualUbo) noexcept const<br> |
| virtual void | [**InitSingleton**](#function-initsingleton) () override<br> |
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


Класс реализует возможность рендера в несколько камер с нескольких ракурсов 


    
## Public Types Documentation




### enum BindResult 

```C++
enum SR_GRAPH_NS::Memory::UBOManager::BindResult {
    None,
    Success,
    Duplicated,
    Failed
};
```




<hr>



### typedef UBO 

```C++
using SR_GRAPH_NS::Memory::UBOManager::UBO =  int32_t;
```




<hr>



### typedef VirtualUBO 

```C++
using SR_GRAPH_NS::Memory::UBOManager::VirtualUBO =  int32_t;
```




<hr>
## Public Functions Documentation




### function AllocateUBO [1/3]

```C++
SR_NODISCARD VirtualUBO SR_GRAPH_NS::Memory::UBOManager::AllocateUBO (
    VirtualUBO virtualUbo,
    uint32_t uboSize,
    bool shared
) 
```




<hr>



### function AllocateUBO [2/3]

```C++
SR_NODISCARD VirtualUBO SR_GRAPH_NS::Memory::UBOManager::AllocateUBO (
    VirtualUBO virtualUbo,
    uint32_t uboSize
) 
```




<hr>



### function AllocateUBO [3/3]

```C++
SR_NODISCARD VirtualUBO SR_GRAPH_NS::Memory::UBOManager::AllocateUBO (
    VirtualUBO virtualUbo
) 
```




<hr>



### function BindNoDublicateUBO 

```C++
BindResult SR_GRAPH_NS::Memory::UBOManager::BindNoDublicateUBO (
    VirtualUBO virtualUbo
) noexcept
```




<hr>



### function BindUBO [1/2]

```C++
BindResult SR_GRAPH_NS::Memory::UBOManager::BindUBO (
    VirtualUBO virtualUbo
) noexcept
```




<hr>



### function BindUBO [2/2]

```C++
BindResult SR_GRAPH_NS::Memory::UBOManager::BindUBO (
    VirtualUBO virtualUbo,
    uint32_t uboSize
) noexcept
```




<hr>



### function CollectUnused 

```C++
void SR_GRAPH_NS::Memory::UBOManager::CollectUnused () 
```




<hr>



### function FreeUBO 

```C++
bool SR_GRAPH_NS::Memory::UBOManager::FreeUBO (
    VirtualUBO * ubo
) 
```




<hr>



### function GetUBO 

```C++
SR_NODISCARD UBO SR_GRAPH_NS::Memory::UBOManager::GetUBO (
    VirtualUBO virtualUbo
) noexcept const
```




<hr>



### function InitSingleton 

```C++
virtual void SR_GRAPH_NS::Memory::UBOManager::InitSingleton () override
```



Implements [*SR\_UTILS\_NS::SingletonBase::InitSingleton*](classSR__UTILS__NS_1_1SingletonBase.md#function-initsingleton)


<hr>



### function SetPipeline 

```C++
void SR_GRAPH_NS::Memory::UBOManager::SetPipeline (
    PipelinePtr pPipeline
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Memory/UBOManager.h`

