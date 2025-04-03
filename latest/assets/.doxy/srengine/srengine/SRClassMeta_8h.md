

# File SRClassMeta.h



[**FileList**](files.md) **>** [**Core**](dir_0e25eeab45a2a860e54b41439eaf8784.md) **>** [**libs**](dir_ec277bd8bac57730a602f096f68de393.md) **>** [**Utils**](dir_f3d6dc6978aa78088efd06c6b2710310.md) **>** [**inc**](dir_e0f1b8570fc577fb78354cd460e9e760.md) **>** [**Utils**](dir_06a42b3e946fb631201a76a22d1aab06.md) **>** [**TypeTraits**](dir_16c2d3fce5275752976e0da6f3af1bdb.md) **>** [**SRClassMeta.h**](SRClassMeta_8h.md)

[Go to the source code of this file](SRClassMeta_8h_source.md)



* `#include <Utils/Types/StringAtom.h>`
* `#include <Utils/Serialization/Serializer.h>`
* `#include <Utils/Serialization/Deserializer.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**Codegen**](namespaceCodegen.md) <br> |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**Reflection**](namespaceSR__UTILS__NS_1_1Reflection.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**SRClassMeta**](classSR__UTILS__NS_1_1SRClassMeta.md) <br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_CLASS**](SRClassMeta_8h.md#define-sr_class) () `/* multi line expression */`<br> |
| define  | [**SR\_CLASS\_BASE**](SRClassMeta_8h.md#define-sr_class_base) () `/* multi line expression */`<br> |
| define  | [**SR\_CLASS\_REGISTER\_PROPERTY\_BASE**](SRClassMeta_8h.md#define-sr_class_register_property_base) (className, propertyName, propertyType) `\`<br> |
| define  | [**SR\_STRUCT**](SRClassMeta_8h.md#define-sr_struct) () `/* multi line expression */`<br> |
| define  | [**SR\_VIRTUAL\_PROPERTY**](SRClassMeta_8h.md#define-sr_virtual_property)  `typedef bool SR\_COMBINE(SR\_CODEGEN\_VIRTUAL\_PROP\_LINE\_, \_\_LINE\_\_);                                                   \`<br> |

## Macro Definition Documentation





### define SR\_CLASS 

```C++
#define SR_CLASS (
    
) `/* multi line expression */`
```




<hr>



### define SR\_CLASS\_BASE 

```C++
#define SR_CLASS_BASE (
    
) `/* multi line expression */`
```




<hr>



### define SR\_CLASS\_REGISTER\_PROPERTY\_BASE 

```C++
#define SR_CLASS_REGISTER_PROPERTY_BASE (
    className,
    propertyName,
    propertyType
) `\`
```




<hr>



### define SR\_STRUCT 

```C++
#define SR_STRUCT (
    
) `/* multi line expression */`
```




<hr>



### define SR\_VIRTUAL\_PROPERTY 

```C++
#define SR_VIRTUAL_PROPERTY `typedef bool SR_COMBINE(SR_CODEGEN_VIRTUAL_PROP_LINE_, __LINE__);                                                   \`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/SRClassMeta.h`

