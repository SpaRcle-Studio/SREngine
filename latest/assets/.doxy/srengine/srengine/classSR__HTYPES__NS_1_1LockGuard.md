

# Class SR\_HTYPES\_NS::LockGuard

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**LockGuard**](classSR__HTYPES__NS_1_1LockGuard.md)








Inherits the following classes: NonCopyable


































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LockGuard**](#function-lockguard-12) (T & mutex) <br> |
|   | [**LockGuard**](#function-lockguard-22) ([**LockGuard**](classSR__HTYPES__NS_1_1LockGuard.md) && other) noexcept<br> |
|  [**LockGuard**](classSR__HTYPES__NS_1_1LockGuard.md) & | [**operator=**](#function-operator) ([**LockGuard**](classSR__HTYPES__NS_1_1LockGuard.md) && rhs) noexcept<br> |
|   | [**~LockGuard**](#function-lockguard) () override<br> |




























## Public Functions Documentation




### function LockGuard [1/2]

```C++
inline explicit SR_HTYPES_NS::LockGuard::LockGuard (
    T & mutex
) 
```




<hr>



### function LockGuard [2/2]

```C++
SR_HTYPES_NS::LockGuard::LockGuard (
    LockGuard && other
) noexcept
```




<hr>



### function operator= 

```C++
LockGuard & SR_HTYPES_NS::LockGuard::operator= (
    LockGuard && rhs
) noexcept
```




<hr>



### function ~LockGuard 

```C++
inline SR_HTYPES_NS::LockGuard::~LockGuard () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/LockGuard.h`

