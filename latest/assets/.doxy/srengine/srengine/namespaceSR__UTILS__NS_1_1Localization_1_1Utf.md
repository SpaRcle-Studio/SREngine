

# Namespace SR\_UTILS\_NS::Localization::Utf



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Localization**](namespaceSR__UTILS__NS_1_1Localization.md) **>** [**Utf**](namespaceSR__UTILS__NS_1_1Localization_1_1Utf.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**UtfTraits**](structSR__UTILS__NS_1_1Localization_1_1Utf_1_1UtfTraits.md) &lt;typename CharType, size&gt;<br> |
| struct | [**UtfTraits&lt; CharType, 1 &gt;**](structSR__UTILS__NS_1_1Localization_1_1Utf_1_1UtfTraits_3_01CharType_00_011_01_4.md) &lt;typename CharType&gt;<br> |
| struct | [**UtfTraits&lt; CharType, 2 &gt;**](structSR__UTILS__NS_1_1Localization_1_1Utf_1_1UtfTraits_3_01CharType_00_012_01_4.md) &lt;typename CharType&gt;<br>_utf8_  |
| struct | [**UtfTraits&lt; CharType, 4 &gt;**](structSR__UTILS__NS_1_1Localization_1_1Utf_1_1UtfTraits_3_01CharType_00_014_01_4.md) &lt;typename CharType&gt;<br>_utf16;_  |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef uint32\_t | [**CodePoint**](#typedef-codepoint)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const CodePoint | [**Illegal**](#variable-illegal)   = `0xFFFFFFFFu`<br> |
|  const CodePoint | [**Incomplete**](#variable-incomplete)   = `0xFFFFFFFEu`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_INLINE\_STATIC bool | [**IsValidCodePoint**](#function-isvalidcodepoint) (CodePoint v) <br> |




























## Public Types Documentation




### typedef CodePoint 

```C++
typedef uint32_t SR_UTILS_NS::Localization::Utf::CodePoint;
```




<hr>
## Public Static Attributes Documentation




### variable Illegal 

```C++
const CodePoint SR_UTILS_NS::Localization::Utf::Illegal;
```




<hr>



### variable Incomplete 

```C++
const CodePoint SR_UTILS_NS::Localization::Utf::Incomplete;
```




<hr>
## Public Functions Documentation




### function IsValidCodePoint 

```C++
SR_INLINE_STATIC bool SR_UTILS_NS::Localization::Utf::IsValidCodePoint (
    CodePoint v
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Localization/UTF.h`

