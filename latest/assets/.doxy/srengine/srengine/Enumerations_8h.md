

# File Enumerations.h



[**FileList**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**Enumerations.h**](Enumerations_8h.md)

[Go to the source code of this file](Enumerations_8h_source.md)



* `#include <Utils/Common/EnumReflector.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |



















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_ENUM**](Enumerations_8h.md#define-sr_enum) (enumName, ...) `SR\_ENUM\_T(enumName, int32\_t, \_\_VA\_ARGS\_\_)`<br> |
| define  | [**SR\_ENUM\_CLASS**](Enumerations_8h.md#define-sr_enum_class) (enumName, ...) `SR\_ENUM\_CLASS\_T(enumName, int32\_t, \_\_VA\_ARGS\_\_)`<br>_------------------------------------_  _[Для объявления внутри классов]-------------------------------------------_ __ |
| define  | [**SR\_ENUM\_CLASS\_T**](Enumerations_8h.md#define-sr_enum_class_t) (enumName, type, ...) `/* multi line expression */`<br>_Declare an enumeration inside a class._  |
| define  | [**SR\_ENUM\_NS**](Enumerations_8h.md#define-sr_enum_ns) (enumName, ...) `SR\_ENUM\_NS\_T(enumName, int32\_t, \_\_VA\_ARGS\_\_)`<br> |
| define  | [**SR\_ENUM\_NS\_CLASS**](Enumerations_8h.md#define-sr_enum_ns_class) (enumName, ...) `SR\_ENUM\_NS\_CLASS\_T(enumName, int32\_t, \_\_VA\_ARGS\_\_)`<br>_-------------------------------_  _[Для объявления внутри пространств имен]---------------------------------------_ __ |
| define  | [**SR\_ENUM\_NS\_CLASS\_T**](Enumerations_8h.md#define-sr_enum_ns_class_t) (enumName, type, ...) `/* multi line expression */`<br>_Declare an enumeration inside a namespace._  |
| define  | [**SR\_ENUM\_NS\_STRUCT\_T**](Enumerations_8h.md#define-sr_enum_ns_struct_t) (enumName, type, ...) `/* multi line expression */`<br>_Declare an enumeration inside a namespace._  |
| define  | [**SR\_ENUM\_NS\_T**](Enumerations_8h.md#define-sr_enum_ns_t) (enumName, type, ...) `/* multi line expression */`<br>_Declare an enumeration inside a namespace._  |
| define  | [**SR\_ENUM\_T**](Enumerations_8h.md#define-sr_enum_t) (enumName, type, ...) `/* multi line expression */`<br>_--------------------------------------_  _[Базовые с настройкой типа]---------------------------------------------_ __ |

## Macro Definition Documentation





### define SR\_ENUM 

```C++
#define SR_ENUM (
    enumName,
    ...
) `SR_ENUM_T(enumName, int32_t, __VA_ARGS__)`
```




<hr>



### define SR\_ENUM\_CLASS 

_------------------------------------_  _[Для объявления внутри классов]-------------------------------------------_ __
```C++
#define SR_ENUM_CLASS (
    enumName,
    ...
) `SR_ENUM_CLASS_T(enumName, int32_t, __VA_ARGS__)`
```




<hr>



### define SR\_ENUM\_CLASS\_T 

_Declare an enumeration inside a class._ 
```C++
#define SR_ENUM_CLASS_T (
    enumName,
    type,
    ...
) `/* multi line expression */`
```




<hr>



### define SR\_ENUM\_NS 

```C++
#define SR_ENUM_NS (
    enumName,
    ...
) `SR_ENUM_NS_T(enumName, int32_t, __VA_ARGS__)`
```




<hr>



### define SR\_ENUM\_NS\_CLASS 

_-------------------------------_  _[Для объявления внутри пространств имен]---------------------------------------_ __
```C++
#define SR_ENUM_NS_CLASS (
    enumName,
    ...
) `SR_ENUM_NS_CLASS_T(enumName, int32_t, __VA_ARGS__)`
```




<hr>



### define SR\_ENUM\_NS\_CLASS\_T 

_Declare an enumeration inside a namespace._ 
```C++
#define SR_ENUM_NS_CLASS_T (
    enumName,
    type,
    ...
) `/* multi line expression */`
```




<hr>



### define SR\_ENUM\_NS\_STRUCT\_T 

_Declare an enumeration inside a namespace._ 
```C++
#define SR_ENUM_NS_STRUCT_T (
    enumName,
    type,
    ...
) `/* multi line expression */`
```



Declare an enumeration inside a namespace 


        

<hr>



### define SR\_ENUM\_NS\_T 

_Declare an enumeration inside a namespace._ 
```C++
#define SR_ENUM_NS_T (
    enumName,
    type,
    ...
) `/* multi line expression */`
```




<hr>



### define SR\_ENUM\_T 

_--------------------------------------_  _[Базовые с настройкой типа]---------------------------------------------_ __
```C++
#define SR_ENUM_T (
    enumName,
    type,
    ...
) `/* multi line expression */`
```



Declare an enumeration inside a class 


        

<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Enumerations.h`

