

# Struct SR\_UTILS\_NS::Localization::Utf::UtfTraits&lt; CharType, 1 &gt;

**template &lt;typename CharType&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Localization**](namespaceSR__UTILS__NS_1_1Localization.md) **>** [**Utf**](namespaceSR__UTILS__NS_1_1Localization_1_1Utf.md) **>** [**UtfTraits&lt; CharType, 1 &gt;**](structSR__UTILS__NS_1_1Localization_1_1Utf_1_1UtfTraits_3_01CharType_00_011_01_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef CharType | [**char\_type**](#typedef-char_type)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const int | [**MAX\_WIDTH**](#variable-max_width)   = `4`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  CodePoint | [**Decode**](#function-decode) (Iterator & p, Iterator e) <br> |
|  CodePoint | [**DecodeValid**](#function-decodevalid) (Iterator & p) <br> |
|  Iterator | [**Encode**](#function-encode) (CodePoint value, Iterator out) <br> |
|  bool | [**IsLead**](#function-islead) (char\_type ci) <br> |
|  bool | [**IsTrail**](#function-istrail) (char\_type ci) <br> |
|  int | [**TrailLength**](#function-traillength) (char\_type ci) <br> |
|  int | [**Width**](#function-width) (CodePoint value) <br> |


























## Public Types Documentation




### typedef char\_type 

```C++
typedef CharType SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::char_type;
```




<hr>
## Public Static Attributes Documentation




### variable MAX\_WIDTH 

```C++
const int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::MAX_WIDTH;
```




<hr>
## Public Static Functions Documentation




### function Decode 

```C++
template<typename Iterator>
static inline CodePoint SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::Decode (
    Iterator & p,
    Iterator e
) 
```




<hr>



### function DecodeValid 

```C++
template<typename Iterator>
static inline CodePoint SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::DecodeValid (
    Iterator & p
) 
```




<hr>



### function Encode 

```C++
template<typename Iterator>
static inline Iterator SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::Encode (
    CodePoint value,
    Iterator out
) 
```




<hr>



### function IsLead 

```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::IsLead (
    char_type ci
) 
```




<hr>



### function IsTrail 

```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::IsTrail (
    char_type ci
) 
```




<hr>



### function TrailLength 

```C++
static inline int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::TrailLength (
    char_type ci
) 
```




<hr>



### function Width 

```C++
static inline int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 1 >::Width (
    CodePoint value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Localization/UTF.h`

