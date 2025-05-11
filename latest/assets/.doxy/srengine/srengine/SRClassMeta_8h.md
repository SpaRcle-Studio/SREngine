

# File SRClassMeta.h



[**FileList**](files.md) **>** [**Engine**](dir_0b6ee6e7e9547e675db4add2e5de97da.md) **>** [**libs**](dir_864715c2a33e3813fa4e93cb9390f3e1.md) **>** [**Utils**](dir_3df27e53d7cc6cea988e3644dbf87b98.md) **>** [**inc**](dir_27b05de82864f3a1e6ade431259242d5.md) **>** [**Utils**](dir_800651e705081dade93279ddf25689e7.md) **>** [**TypeTraits**](dir_ff18ecc11fc9e76cd78ef60ea36d3728.md) **>** [**SRClassMeta.h**](SRClassMeta_8h.md)

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
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/TypeTraits/SRClassMeta.h`

