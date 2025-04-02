

# Class SR\_HTYPES\_NS::SharedRecursiveMutex



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SharedRecursiveMutex**](classSR__HTYPES__NS_1_1SharedRecursiveMutex.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SharedRecursiveMutex**](#function-sharedrecursivemutex) () = default<br> |
|  void | [**lock**](#function-lock) () <br> |
|  void | [**lock\_shared**](#function-lock_shared) () <br> |
|  bool | [**try\_lock**](#function-try_lock) () <br> |
|  bool | [**try\_lock\_shared**](#function-try_lock_shared) () <br> |
|  void | [**unlock**](#function-unlock) () <br> |
|  void | [**unlock\_shared**](#function-unlock_shared) () <br> |
|   | [**~SharedRecursiveMutex**](#function-sharedrecursivemutex) () override<br> |


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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Functions Documentation




### function SharedRecursiveMutex 

```C++
SR_HTYPES_NS::SharedRecursiveMutex::SharedRecursiveMutex () = default
```




<hr>



### function lock 

```C++
void SR_HTYPES_NS::SharedRecursiveMutex::lock () 
```




<hr>



### function lock\_shared 

```C++
void SR_HTYPES_NS::SharedRecursiveMutex::lock_shared () 
```




<hr>



### function try\_lock 

```C++
bool SR_HTYPES_NS::SharedRecursiveMutex::try_lock () 
```




<hr>



### function try\_lock\_shared 

```C++
bool SR_HTYPES_NS::SharedRecursiveMutex::try_lock_shared () 
```




<hr>



### function unlock 

```C++
void SR_HTYPES_NS::SharedRecursiveMutex::unlock () 
```




<hr>



### function unlock\_shared 

```C++
void SR_HTYPES_NS::SharedRecursiveMutex::unlock_shared () 
```




<hr>



### function ~SharedRecursiveMutex 

```C++
SR_HTYPES_NS::SharedRecursiveMutex::~SharedRecursiveMutex () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/Mutex.h`

