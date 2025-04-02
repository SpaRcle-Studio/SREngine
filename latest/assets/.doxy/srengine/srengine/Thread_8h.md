

# File Thread.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**Types**](dir_e2eff6081ed67c5bc03a553ef17d8efc.md) **>** [**Thread.h**](Thread_8h.md)

[Go to the source code of this file](Thread_8h_source.md)



* `#include <Utils/Debug.h>`
* `#include <Utils/Common/ThreadUtils.h>`
* `#include <Utils/Common/Singleton.h>`
* `#include <Utils/Types/Function.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Thread**](classSR__HTYPES__NS_1_1Thread.md) <br> |
| class | [**Factory**](classSR__HTYPES__NS_1_1Thread_1_1Factory.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_LOCK\_GUARD**](Thread_8h.md#define-sr_lock_guard)  `std::lock\_guard&lt;std::recursive\_mutex&gt; codegen\_lock(m\_mutex)`<br> |
| define  | [**SR\_LOCK\_GUARD\_INHERIT**](Thread_8h.md#define-sr_lock_guard_inherit) (baseClass) `std::lock\_guard&lt;std::recursive\_mutex&gt; codegen\_lock(baseClass::m\_mutex)`<br> |
| define  | [**SR\_READ\_LOCK**](Thread_8h.md#define-sr_read_lock)  `std::shared\_lock&lt;std::shared\_mutex&gt; SR\_MACRO\_CONCAT(codegen\_read\_lock, SR\_LINE)(m\_mutex)`<br> |
| define  | [**SR\_SCOPED\_LOCK**](Thread_8h.md#define-sr_scoped_lock)  `std::lock\_guard&lt;std::recursive\_mutex&gt; codegen\_lock(m\_mutex)`<br> |
| define  | [**SR\_THIS\_THREAD**](Thread_8h.md#define-sr_this_thread)  `(SR\_HTYPES\_NS::Thread::Factory::Instance().GetThisThread())`<br> |
| define  | [**SR\_THREAD\_SAFE\_CHECKS**](Thread_8h.md#define-sr_thread_safe_checks)  `1`<br> |
| define  | [**SR\_WRITE\_LOCK**](Thread_8h.md#define-sr_write_lock)  `std::lock\_guard&lt;std::shared\_mutex&gt; SR\_MACRO\_CONCAT(codegen\_write\_lock, SR\_LINE)(m\_mutex)`<br> |

## Macro Definition Documentation





### define SR\_LOCK\_GUARD 

```C++
#define SR_LOCK_GUARD `std::lock_guard<std::recursive_mutex> codegen_lock(m_mutex)`
```




<hr>



### define SR\_LOCK\_GUARD\_INHERIT 

```C++
#define SR_LOCK_GUARD_INHERIT (
    baseClass
) `std::lock_guard<std::recursive_mutex> codegen_lock(baseClass::m_mutex)`
```




<hr>



### define SR\_READ\_LOCK 

```C++
#define SR_READ_LOCK `std::shared_lock<std::shared_mutex> SR_MACRO_CONCAT(codegen_read_lock, SR_LINE)(m_mutex)`
```




<hr>



### define SR\_SCOPED\_LOCK 

```C++
#define SR_SCOPED_LOCK `std::lock_guard<std::recursive_mutex> codegen_lock(m_mutex)`
```




<hr>



### define SR\_THIS\_THREAD 

```C++
#define SR_THIS_THREAD `(SR_HTYPES_NS::Thread::Factory::Instance().GetThisThread())`
```



Warning: этот метод очень медленный! 


        

<hr>



### define SR\_THREAD\_SAFE\_CHECKS 

```C++
#define SR_THREAD_SAFE_CHECKS `1`
```




<hr>



### define SR\_WRITE\_LOCK 

```C++
#define SR_WRITE_LOCK `std::lock_guard<std::shared_mutex> SR_MACRO_CONCAT(codegen_write_lock, SR_LINE)(m_mutex)`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/Thread.h`

