

# File Singleton.h



[**FileList**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**Singleton.h**](Singleton_8h.md)

[Go to the source code of this file](Singleton_8h_source.md)



* `#include <Utils/Common/NonCopyable.h>`
* `#include <Utils/Common/Breakpoint.h>`
* `#include <Utils/Platform/Stacktrace.h>`
* `#include <Utils/Types/StringAtom.h>`
* `#include <Utils/Types/SafePtrLockGuard.h>`
* `#include <Utils/Types/Map.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**Singleton**](classSR__UTILS__NS_1_1Singleton.md) &lt;typename T&gt;<br> |
| class | [**SingletonBase**](classSR__UTILS__NS_1_1SingletonBase.md) <br> |
| class | [**SingletonManager**](classSR__UTILS__NS_1_1SingletonManager.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_REGISTER\_SINGLETON**](Singleton_8h.md#define-sr_register_singleton) (className) `/* multi line expression */`<br> |
| define  | [**SR\_REGISTER\_TEMPLATE\_SINGLETON**](Singleton_8h.md#define-sr_register_template_singleton) (className, T) `/* multi line expression */`<br> |

## Macro Definition Documentation





### define SR\_REGISTER\_SINGLETON 

```C++
#define SR_REGISTER_SINGLETON (
    className
) `/* multi line expression */`
```




<hr>



### define SR\_REGISTER\_TEMPLATE\_SINGLETON 

```C++
#define SR_REGISTER_TEMPLATE_SINGLETON (
    className,
    T
) `/* multi line expression */`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/Singleton.h`

