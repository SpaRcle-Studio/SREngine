

# Class SR\_UTILS\_NS::HashManager



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**HashManager**](classSR__UTILS__NS_1_1HashManager.md)



_Не можем наследоваться от_ [_**Singleton**_](classSR__UTILS__NS_1_1Singleton.md) _._

* `#include <HashManager.h>`



Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  Hash | [**AddHash**](#function-addhash-13) (const std::string & str) <br> |
|  Hash | [**AddHash**](#function-addhash-23) (const std::string\_view & str) <br> |
|  Hash | [**AddHash**](#function-addhash-33) (const char \* str) <br> |
|  SR\_NODISCARD bool | [**Exists**](#function-exists) (Hash hash) const<br> |
|  SR\_NODISCARD [**StringHashInfo**](structSR__UTILS__NS_1_1StringHashInfo.md) \* | [**GetOrAddInfo**](#function-getoraddinfo-13) (const std::string & str) <br> |
|  SR\_NODISCARD [**StringHashInfo**](structSR__UTILS__NS_1_1StringHashInfo.md) \* | [**GetOrAddInfo**](#function-getoraddinfo-23) (const std::string\_view & str) <br> |
|  SR\_NODISCARD [**StringHashInfo**](structSR__UTILS__NS_1_1StringHashInfo.md) \* | [**GetOrAddInfo**](#function-getoraddinfo-33) (const char \* str) <br> |
|  SR\_NODISCARD const Storage & | [**GetStorage**](#function-getstorage) () const<br> |
|  SR\_NODISCARD const std::string\_view & | [**HashToString**](#function-hashtostring) (Hash hash) const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**HashToStringAtom**](#function-hashtostringatom) (Hash hash) const<br> |
|  void | [**Lock**](#function-lock) () const<br> |
|  void | [**Unlock**](#function-unlock) () const<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED [**HashManager**](classSR__UTILS__NS_1_1HashManager.md) & | [**Instance**](#function-instance) () <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function AddHash [1/3]

```C++
Hash SR_UTILS_NS::HashManager::AddHash (
    const std::string & str
) 
```




<hr>



### function AddHash [2/3]

```C++
Hash SR_UTILS_NS::HashManager::AddHash (
    const std::string_view & str
) 
```




<hr>



### function AddHash [3/3]

```C++
Hash SR_UTILS_NS::HashManager::AddHash (
    const char * str
) 
```




<hr>



### function Exists 

```C++
SR_NODISCARD bool SR_UTILS_NS::HashManager::Exists (
    Hash hash
) const
```




<hr>



### function GetOrAddInfo [1/3]

```C++
SR_NODISCARD StringHashInfo * SR_UTILS_NS::HashManager::GetOrAddInfo (
    const std::string & str
) 
```




<hr>



### function GetOrAddInfo [2/3]

```C++
SR_NODISCARD StringHashInfo * SR_UTILS_NS::HashManager::GetOrAddInfo (
    const std::string_view & str
) 
```




<hr>



### function GetOrAddInfo [3/3]

```C++
SR_NODISCARD StringHashInfo * SR_UTILS_NS::HashManager::GetOrAddInfo (
    const char * str
) 
```




<hr>



### function GetStorage 

```C++
inline SR_NODISCARD const Storage & SR_UTILS_NS::HashManager::GetStorage () const
```




<hr>



### function HashToString 

```C++
SR_NODISCARD const std::string_view & SR_UTILS_NS::HashManager::HashToString (
    Hash hash
) const
```




<hr>



### function HashToStringAtom 

```C++
SR_NODISCARD StringAtom SR_UTILS_NS::HashManager::HashToStringAtom (
    Hash hash
) const
```




<hr>



### function Lock 

```C++
inline void SR_UTILS_NS::HashManager::Lock () const
```




<hr>



### function Unlock 

```C++
inline void SR_UTILS_NS::HashManager::Unlock () const
```




<hr>
## Public Static Functions Documentation




### function Instance 

```C++
static SR_MAYBE_UNUSED HashManager & SR_UTILS_NS::HashManager::Instance () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/HashManager.h`

