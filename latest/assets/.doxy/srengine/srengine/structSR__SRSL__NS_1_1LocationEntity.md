

# Struct SR\_SRSL\_NS::LocationEntity



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**LocationEntity**](structSR__SRSL__NS_1_1LocationEntity.md)










Inherited by the following classes: [SR\_SRSL\_NS::Lexem](structSR__SRSL__NS_1_1Lexem.md)
















## Public Attributes

| Type | Name |
| ---: | :--- |
|  uint16\_t | [**fileIndex**](#variable-fileindex)   = `0`<br> |
|  uint64\_t | [**length**](#variable-length)   = `0`<br> |
|  uint64\_t | [**line**](#variable-line)   = `0`<br> |
|  uint64\_t | [**offset**](#variable-offset)   = `0`<br> |
|  uint64\_t | [**position**](#variable-position)   = `0`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**LocationEntity**](#function-locationentity-12) () = default<br> |
|   | [**LocationEntity**](#function-locationentity-22) (uint64\_t offset, uint64\_t length, uint16\_t fileIndex, uint64\_t line, uint64\_t position) <br> |




























## Public Attributes Documentation




### variable fileIndex 

```C++
uint16_t SR_SRSL_NS::LocationEntity::fileIndex;
```




<hr>



### variable length 

```C++
uint64_t SR_SRSL_NS::LocationEntity::length;
```




<hr>



### variable line 

```C++
uint64_t SR_SRSL_NS::LocationEntity::line;
```




<hr>



### variable offset 

```C++
uint64_t SR_SRSL_NS::LocationEntity::offset;
```




<hr>



### variable position 

```C++
uint64_t SR_SRSL_NS::LocationEntity::position;
```




<hr>
## Public Functions Documentation




### function LocationEntity [1/2]

```C++
SR_SRSL_NS::LocationEntity::LocationEntity () = default
```




<hr>



### function LocationEntity [2/2]

```C++
inline SR_SRSL_NS::LocationEntity::LocationEntity (
    uint64_t offset,
    uint64_t length,
    uint16_t fileIndex,
    uint64_t line,
    uint64_t position
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexerUtils.h`

