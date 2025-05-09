

# Class SR\_UTILS\_NS::StoreUtils::Storage



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**StoreUtils**](namespaceSR__UTILS__NS_1_1StoreUtils.md) **>** [**Storage**](classSR__UTILS__NS_1_1StoreUtils_1_1Storage.md)








Inherits the following classes: [SR\_UTILS\_NS::Singleton](classSR__UTILS__NS_1_1Singleton.md)














## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**StorageType**](#enum-storagetype)  <br> |
| enum  | [**ValueType**](#enum-valuetype)  <br> |
















































































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](#function-clear) () <br> |
|  bool | [**Drop**](#function-drop) (StorageType storageTepe, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key) <br> |
|  SR\_NODISCARD T | [**Get**](#function-get-12) (StorageType storageTepe, ValueType valueType, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, const std::optional&lt; T &gt; & def=std::nullopt) <br> |
|  T | [**Get**](#function-get-22) (const StorageType storageTepe, const ValueType valueType, const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, const std::optional&lt; T &gt; & def) <br> |
|  SR\_NODISCARD bool | [**Has**](#function-has) (StorageType storageTepe, ValueType valueType, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key) <br> |
|  void | [**Load**](#function-load) () <br> |
|  void | [**Save**](#function-save) () <br> |
|  void | [**Set**](#function-set) (StorageType storageTepe, ValueType valueType, [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) key, T value) <br> |




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




### enum StorageType 

```C++
enum SR_UTILS_NS::StoreUtils::Storage::StorageType {
    Temp,
    User
};
```




<hr>



### enum ValueType 

```C++
enum SR_UTILS_NS::StoreUtils::Storage::ValueType {
    AnyType,
    Float,
    Bool
};
```




<hr>
## Public Functions Documentation




### function Clear 

```C++
inline void SR_UTILS_NS::StoreUtils::Storage::Clear () 
```




<hr>



### function Drop 

```C++
bool SR_UTILS_NS::StoreUtils::Storage::Drop (
    StorageType storageTepe,
    SR_UTILS_NS::StringAtom key
) 
```




<hr>



### function Get [1/2]

```C++
template<typename T>
SR_NODISCARD T SR_UTILS_NS::StoreUtils::Storage::Get (
    StorageType storageTepe,
    ValueType valueType,
    SR_UTILS_NS::StringAtom key,
    const std::optional< T > & def=std::nullopt
) 
```




<hr>



### function Get [2/2]

```C++
template<typename T>
T SR_UTILS_NS::StoreUtils::Storage::Get (
    const StorageType storageTepe,
    const ValueType valueType,
    const StringAtom key,
    const std::optional< T > & def
) 
```




<hr>



### function Has 

```C++
SR_NODISCARD bool SR_UTILS_NS::StoreUtils::Storage::Has (
    StorageType storageTepe,
    ValueType valueType,
    SR_UTILS_NS::StringAtom key
) 
```




<hr>



### function Load 

```C++
void SR_UTILS_NS::StoreUtils::Storage::Load () 
```




<hr>



### function Save 

```C++
void SR_UTILS_NS::StoreUtils::Storage::Save () 
```




<hr>



### function Set 

```C++
template<typename T>
void SR_UTILS_NS::StoreUtils::Storage::Set (
    StorageType storageTepe,
    ValueType valueType,
    SR_UTILS_NS::StringAtom key,
    T value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/StoreUtils.h`

