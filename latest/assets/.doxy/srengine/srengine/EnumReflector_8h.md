

# File EnumReflector.h



[**FileList**](files.md) **>** [**Common**](dir_3494e32b0a79d085f92ff9f3955f97da.md) **>** [**EnumReflector.h**](EnumReflector_8h.md)

[Go to the source code of this file](EnumReflector_8h_source.md)



* `#include <Utils/Common/Singleton.h>`
* `#include <Utils/Common/HashManager.h>`
* `#include <Utils/Types/Map.h>`
* `#include <Utils/Types/StringAtom.h>`
* `#include <Utils/Types/Function.h>`
* `#include <Codegen/EnumsFwd.generated.hpp>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md) <br> |
| struct | [**Enumerator**](structSR__UTILS__NS_1_1EnumReflector_1_1Enumerator.md) <br> |
| class | [**EnumReflectorManager**](classSR__UTILS__NS_1_1EnumReflectorManager.md) <br> |
| struct | [**EnumTraits**](structSR__UTILS__NS_1_1EnumTraits.md) &lt;typename EnumType&gt;<br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_ENUM\_DETAIL\_MAKE**](EnumReflector_8h.md#define-sr_enum_detail_make) (enumVariant, enumClass, spec, enumName, enumNameStr, integral, ...) <br> |
| define  | [**SR\_ENUM\_DETAIL\_SPEC\_class**](EnumReflector_8h.md#define-sr_enum_detail_spec_class)  `friend`<br> |
| define  | [**SR\_ENUM\_DETAIL\_SPEC\_namespace**](EnumReflector_8h.md#define-sr_enum_detail_spec_namespace)  `/* multi line expression */`<br> |
| define  | [**SR\_ENUM\_DETAIL\_STR**](EnumReflector_8h.md#define-sr_enum_detail_str) (x) `#x`<br> |

## Macro Definition Documentation





### define SR\_ENUM\_DETAIL\_MAKE 

```C++
#define SR_ENUM_DETAIL_MAKE (
    enumVariant,
    enumClass,
    spec,
    enumName,
    enumNameStr,
    integral,
    ...
) 
```




<hr>



### define SR\_ENUM\_DETAIL\_SPEC\_class 

```C++
#define SR_ENUM_DETAIL_SPEC_class `friend`
```




<hr>



### define SR\_ENUM\_DETAIL\_SPEC\_namespace 

```C++
#define SR_ENUM_DETAIL_SPEC_namespace `/* multi line expression */`
```




<hr>



### define SR\_ENUM\_DETAIL\_STR 

```C++
#define SR_ENUM_DETAIL_STR (
    x
) `#x`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/EnumReflector.h`

