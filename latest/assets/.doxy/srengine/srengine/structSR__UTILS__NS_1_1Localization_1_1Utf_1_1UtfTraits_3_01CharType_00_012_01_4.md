

# Struct SR\_UTILS\_NS::Localization::Utf::UtfTraits&lt; CharType, 2 &gt;

**template &lt;typename CharType&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Localization**](namespaceSR__UTILS__NS_1_1Localization.md) **>** [**Utf**](namespaceSR__UTILS__NS_1_1Localization_1_1Utf.md) **>** [**UtfTraits&lt; CharType, 2 &gt;**](structSR__UTILS__NS_1_1Localization_1_1Utf_1_1UtfTraits_3_01CharType_00_012_01_4.md)



_utf8_ 

* `#include <UTF.h>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef CharType | [**char\_type**](#typedef-char_type)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const int | [**MAX\_WIDTH**](#variable-max_width)   = `2`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  CodePoint | [**CombineSurrogate**](#function-combinesurrogate) (uint16\_t w1, uint16\_t w2) <br> |
|  CodePoint | [**Decode**](#function-decode) (It & current, It last) <br> |
|  CodePoint | [**DecodeValid**](#function-decodevalid) (It & current) <br> |
|  It | [**Encode**](#function-encode) (CodePoint u, It out) <br> |
|  bool | [**IsFirstSurrogate**](#function-isfirstsurrogate) (uint16\_t x) <br>_See RFC 2781._  |
|  bool | [**IsLead**](#function-islead) (char\_type c) <br> |
|  bool | [**IsSecondSurrogate**](#function-issecondsurrogate) (uint16\_t x) <br> |
|  bool | [**IsTrail**](#function-istrail) (char\_type c) <br> |
|  int | [**TrailLength**](#function-traillength) (char\_type c) <br> |
|  int | [**Width**](#function-width) (CodePoint u) <br> |


























## Public Types Documentation




### typedef char\_type 

```C++
typedef CharType SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::char_type;
```




<hr>
## Public Static Attributes Documentation




### variable MAX\_WIDTH 

```C++
const int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::MAX_WIDTH;
```




<hr>
## Public Static Functions Documentation




### function CombineSurrogate 

```C++
static inline CodePoint SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::CombineSurrogate (
    uint16_t w1,
    uint16_t w2
) 
```




<hr>



### function Decode 

```C++
template<typename It>
static inline CodePoint SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::Decode (
    It & current,
    It last
) 
```




<hr>



### function DecodeValid 

```C++
template<typename It>
static inline CodePoint SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::DecodeValid (
    It & current
) 
```




<hr>



### function Encode 

```C++
template<typename It>
static inline It SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::Encode (
    CodePoint u,
    It out
) 
```




<hr>



### function IsFirstSurrogate 

_See RFC 2781._ 
```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::IsFirstSurrogate (
    uint16_t x
) 
```




<hr>



### function IsLead 

```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::IsLead (
    char_type c
) 
```



Returns true if c is lead code unit, always true of UTF-32 


        

<hr>



### function IsSecondSurrogate 

```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::IsSecondSurrogate (
    uint16_t x
) 
```




<hr>



### function IsTrail 

```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::IsTrail (
    char_type c
) 
```



Returns true if c is trail code unit, always false for UTF-32 


        

<hr>



### function TrailLength 

```C++
static inline int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::TrailLength (
    char_type c
) 
```




<hr>



### function Width 

```C++
static inline int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 2 >::Width (
    CodePoint u
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Localization/UTF.h`

