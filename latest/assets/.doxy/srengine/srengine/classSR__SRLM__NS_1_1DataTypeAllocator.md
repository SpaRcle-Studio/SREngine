

# Class SR\_SRLM\_NS::DataTypeAllocator



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**DataTypeAllocator**](classSR__SRLM__NS_1_1DataTypeAllocator.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)






























































































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Allocate**](#function-allocate-12) (DataTypeClass dataTypeClass) <br> |
|  [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Allocate**](#function-allocate-22) (Hash hashName) <br> |
| virtual SR\_NODISCARD bool | [**IsSingletonCanBeDestroyed**](#function-issingletoncanbedestroyed) () override const<br> |
|  bool | [**Register**](#function-register) (DataTypeClass dataTypeClass, Hash hashName, Allocator allocator) <br> |




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




### function Allocate [1/2]

```C++
DataType * SR_SRLM_NS::DataTypeAllocator::Allocate (
    DataTypeClass dataTypeClass
) 
```




<hr>



### function Allocate [2/2]

```C++
DataType * SR_SRLM_NS::DataTypeAllocator::Allocate (
    Hash hashName
) 
```




<hr>



### function IsSingletonCanBeDestroyed 

```C++
inline virtual SR_NODISCARD bool SR_SRLM_NS::DataTypeAllocator::IsSingletonCanBeDestroyed () override const
```



Implements [*SR\_UTILS\_NS::SingletonBase::IsSingletonCanBeDestroyed*](classSR__UTILS__NS_1_1SingletonBase.md#function-issingletoncanbedestroyed)


<hr>



### function Register 

```C++
bool SR_SRLM_NS::DataTypeAllocator::Register (
    DataTypeClass dataTypeClass,
    Hash hashName,
    Allocator allocator
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/SRLM/DataType.h`

