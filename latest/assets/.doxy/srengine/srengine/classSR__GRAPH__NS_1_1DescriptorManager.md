

# Class SR\_GRAPH\_NS::DescriptorManager



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**DescriptorManager**](classSR__GRAPH__NS_1_1DescriptorManager.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum uint8\_t | [**BindResult**](#enum-bindresult)  <br> |
| typedef int32\_t | [**VirtualDescriptorSet**](#typedef-virtualdescriptorset)  <br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD VirtualDescriptorSet | [**AllocateDescriptorSet**](#function-allocatedescriptorset) (VirtualDescriptorSet reallocation=SR\_ID\_INVALID) <br> |
|  BindResult | [**Bind**](#function-bind) (VirtualDescriptorSet virtualDescriptorSet) <br> |
|  void | [**CollectUnused**](#function-collectunused) () <br> |
|  void | [**Flush**](#function-flush) () <br> |
|  bool | [**FreeDescriptorSet**](#function-freedescriptorset) (VirtualDescriptorSet \* pVirtualDescriptorSet) <br> |
|  void | [**SetPipeline**](#function-setpipeline) ([**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**Pipeline**](classSR__GRAPH__NS_1_1Pipeline.md) &gt; pipeline) noexcept<br> |




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




### enum BindResult 

```C++
enum SR_GRAPH_NS::DescriptorManager::BindResult {
    None,
    Success,
    Duplicated,
    Failed
};
```




<hr>



### typedef VirtualDescriptorSet 

```C++
using SR_GRAPH_NS::DescriptorManager::VirtualDescriptorSet =  int32_t;
```




<hr>
## Public Functions Documentation




### function AllocateDescriptorSet 

```C++
SR_NODISCARD VirtualDescriptorSet SR_GRAPH_NS::DescriptorManager::AllocateDescriptorSet (
    VirtualDescriptorSet reallocation=SR_ID_INVALID
) 
```




<hr>



### function Bind 

```C++
BindResult SR_GRAPH_NS::DescriptorManager::Bind (
    VirtualDescriptorSet virtualDescriptorSet
) 
```




<hr>



### function CollectUnused 

```C++
void SR_GRAPH_NS::DescriptorManager::CollectUnused () 
```




<hr>



### function Flush 

```C++
void SR_GRAPH_NS::DescriptorManager::Flush () 
```




<hr>



### function FreeDescriptorSet 

```C++
bool SR_GRAPH_NS::DescriptorManager::FreeDescriptorSet (
    VirtualDescriptorSet * pVirtualDescriptorSet
) 
```




<hr>



### function SetPipeline 

```C++
inline void SR_GRAPH_NS::DescriptorManager::SetPipeline (
    SR_HTYPES_NS::SharedPtr < Pipeline > pipeline
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Memory/DescriptorManager.h`

