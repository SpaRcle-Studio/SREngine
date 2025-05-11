

# File HashManager.h



[**FileList**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**HashManager.h**](HashManager_8h.md)

[Go to the source code of this file](HashManager_8h_source.md)



* `#include <Utils/Common/Hashes.h>`
* `#include <Utils/Common/Singleton.h>`
* `#include <Utils/Types/Map.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**ConstexprStringHashEntry**](structSR__UTILS__NS_1_1ConstexprStringHashEntry.md) <br> |
| struct | [**GlobalStringRegistry**](structSR__UTILS__NS_1_1GlobalStringRegistry.md) <br> |
| class | [**HashManager**](classSR__UTILS__NS_1_1HashManager.md) <br>_Не можем наследоваться от_ [_**Singleton**_](classSR__UTILS__NS_1_1Singleton.md) _._ |
| struct | [**StringHashInfo**](structSR__UTILS__NS_1_1StringHashInfo.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_HASH\_CONSTEXPR\_STR\_VIEW\_REGISTER**](HashManager_8h.md#define-sr_hash_constexpr_str_view_register) (x) `(SR\_UTILS\_NS::g\_StringRegistry.Register(x, SR\_HASH\_STR\_VIEW(x)))`<br> |
| define  | [**SR\_HASH\_STR\_REGISTER**](HashManager_8h.md#define-sr_hash_str_register) (x) `(SR\_UTILS\_NS::HashManager::Instance().AddHash(x))`<br> |
| define  | [**SR\_HASH\_TO\_STR**](HashManager_8h.md#define-sr_hash_to_str) (x) `SR\_UTILS\_NS::HashManager::Instance().HashToString(x)`<br> |
| define  | [**SR\_HASH\_TO\_STR\_ATOM**](HashManager_8h.md#define-sr_hash_to_str_atom) (x) `SR\_UTILS\_NS::HashManager::Instance().HashToStringAtom(x)`<br> |
| define  | [**SR\_HASH\_TYPE\_NAME\_STR\_REGISTER**](HashManager_8h.md#define-sr_hash_type_name_str_register) (x) `(SR\_UTILS\_NS::HashManager::Instance().AddHash(SR\_GET\_TYPE\_NAME(x)))`<br> |

## Macro Definition Documentation





### define SR\_HASH\_CONSTEXPR\_STR\_VIEW\_REGISTER 

```C++
#define SR_HASH_CONSTEXPR_STR_VIEW_REGISTER (
    x
) `(SR_UTILS_NS::g_StringRegistry.Register(x, SR_HASH_STR_VIEW(x)))`
```




<hr>



### define SR\_HASH\_STR\_REGISTER 

```C++
#define SR_HASH_STR_REGISTER (
    x
) `(SR_UTILS_NS::HashManager::Instance().AddHash(x))`
```




<hr>



### define SR\_HASH\_TO\_STR 

```C++
#define SR_HASH_TO_STR (
    x
) `SR_UTILS_NS::HashManager::Instance().HashToString(x)`
```




<hr>



### define SR\_HASH\_TO\_STR\_ATOM 

```C++
#define SR_HASH_TO_STR_ATOM (
    x
) `SR_UTILS_NS::HashManager::Instance().HashToStringAtom(x)`
```




<hr>



### define SR\_HASH\_TYPE\_NAME\_STR\_REGISTER 

```C++
#define SR_HASH_TYPE_NAME_STR_REGISTER (
    x
) `(SR_UTILS_NS::HashManager::Instance().AddHash(SR_GET_TYPE_NAME(x)))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/HashManager.h`

