

# Class SR\_UTILS\_NS::SingletonManager



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SingletonManager**](classSR__UTILS__NS_1_1SingletonManager.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**DestroyAll**](#function-destroyall) () <br> |
|  std::recursive\_mutex & | [**GetCreationMutex**](#function-getcreationmutex) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |
|  void \* | [**GetSingleton**](#function-getsingleton) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) noexcept<br> |
|  void | [**Register**](#function-register) ([**Singleton**](classSR__UTILS__NS_1_1Singleton.md)&lt; T &gt; \* pSingleton) <br> |
|  void | [**Remove**](#function-remove) ([**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
















































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function DestroyAll 

```C++
void SR_UTILS_NS::SingletonManager::DestroyAll () 
```




<hr>



### function GetCreationMutex 

```C++
std::recursive_mutex & SR_UTILS_NS::SingletonManager::GetCreationMutex (
    StringAtom name
) 
```




<hr>



### function GetSingleton 

```C++
void * SR_UTILS_NS::SingletonManager::GetSingleton (
    StringAtom name
) noexcept
```




<hr>



### function Register 

```C++
template<typename T>
void SR_UTILS_NS::SingletonManager::Register (
    Singleton < T > * pSingleton
) 
```




<hr>



### function Remove 

```C++
void SR_UTILS_NS::SingletonManager::Remove (
    StringAtom name
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Singleton.h`

