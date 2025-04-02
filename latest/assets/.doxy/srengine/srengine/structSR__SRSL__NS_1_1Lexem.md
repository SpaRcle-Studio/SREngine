

# Struct SR\_SRSL\_NS::Lexem



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**Lexem**](structSR__SRSL__NS_1_1Lexem.md)








Inherits the following classes: [SR\_SRSL\_NS::LocationEntity](structSR__SRSL__NS_1_1LocationEntity.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  LexemKind | [**kind**](#variable-kind)   = `LexemKind::Unknown`<br> |
|  std::string | [**value**](#variable-value)  <br> |


## Public Attributes inherited from SR_SRSL_NS::LocationEntity

See [SR\_SRSL\_NS::LocationEntity](structSR__SRSL__NS_1_1LocationEntity.md)

| Type | Name |
| ---: | :--- |
|  uint16\_t | [**fileIndex**](structSR__SRSL__NS_1_1LocationEntity.md#variable-fileindex)   = `0`<br> |
|  uint64\_t | [**length**](structSR__SRSL__NS_1_1LocationEntity.md#variable-length)   = `0`<br> |
|  uint64\_t | [**offset**](structSR__SRSL__NS_1_1LocationEntity.md#variable-offset)   = `0`<br> |






























## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Lexem**](#function-lexem-13) () = default<br> |
|   | [**Lexem**](#function-lexem-23) (uint64\_t offset, uint64\_t length, LexemKind kind, std::string && value, uint16\_t fileIndex) <br> |
|   | [**Lexem**](#function-lexem-33) (uint64\_t offset, uint64\_t length, LexemKind kind, uint16\_t fileIndex) <br> |


## Public Functions inherited from SR_SRSL_NS::LocationEntity

See [SR\_SRSL\_NS::LocationEntity](structSR__SRSL__NS_1_1LocationEntity.md)

| Type | Name |
| ---: | :--- |
|   | [**LocationEntity**](structSR__SRSL__NS_1_1LocationEntity.md#function-locationentity-12) () = default<br> |
|   | [**LocationEntity**](structSR__SRSL__NS_1_1LocationEntity.md#function-locationentity-22) (uint64\_t offset, uint64\_t length, uint16\_t fileIndex) <br> |






















































## Public Attributes Documentation




### variable kind 

```C++
LexemKind SR_SRSL_NS::Lexem::kind;
```




<hr>



### variable value 

```C++
std::string SR_SRSL_NS::Lexem::value;
```




<hr>
## Public Functions Documentation




### function Lexem [1/3]

```C++
SR_SRSL_NS::Lexem::Lexem () = default
```




<hr>



### function Lexem [2/3]

```C++
inline SR_SRSL_NS::Lexem::Lexem (
    uint64_t offset,
    uint64_t length,
    LexemKind kind,
    std::string && value,
    uint16_t fileIndex
) 
```




<hr>



### function Lexem [3/3]

```C++
inline SR_SRSL_NS::Lexem::Lexem (
    uint64_t offset,
    uint64_t length,
    LexemKind kind,
    uint16_t fileIndex
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/SRSL/LexerUtils.h`

