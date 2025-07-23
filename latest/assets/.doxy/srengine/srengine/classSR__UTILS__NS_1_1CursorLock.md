

# Class SR\_UTILS\_NS::CursorLock



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**CursorLock**](classSR__UTILS__NS_1_1CursorLock.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**CursorLock**](#function-cursorlock-12) (CursorLockMode lockMode, std::optional&lt; SR\_MATH\_NS::FRect &gt; lockRect=std::nullopt) <br> |
|   | [**CursorLock**](#function-cursorlock-22) ([**CursorLock**](classSR__UTILS__NS_1_1CursorLock.md) && other) noexcept<br> |
|  [**CursorLock**](classSR__UTILS__NS_1_1CursorLock.md) & | [**operator=**](#function-operator) ([**CursorLock**](classSR__UTILS__NS_1_1CursorLock.md) && other) noexcept<br> |
|   | [**~CursorLock**](#function-cursorlock) () override<br> |


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




### function CursorLock [1/2]

```C++
explicit SR_UTILS_NS::CursorLock::CursorLock (
    CursorLockMode lockMode,
    std::optional< SR_MATH_NS::FRect > lockRect=std::nullopt
) 
```




<hr>



### function CursorLock [2/2]

```C++
SR_UTILS_NS::CursorLock::CursorLock (
    CursorLock && other
) noexcept
```




<hr>



### function operator= 

```C++
CursorLock & SR_UTILS_NS::CursorLock::operator= (
    CursorLock && other
) noexcept
```




<hr>



### function ~CursorLock 

```C++
SR_UTILS_NS::CursorLock::~CursorLock () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Input/InputSystem.h`

