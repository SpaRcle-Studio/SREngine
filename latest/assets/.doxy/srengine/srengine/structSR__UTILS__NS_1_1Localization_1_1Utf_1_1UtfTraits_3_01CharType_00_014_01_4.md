

# Struct SR\_UTILS\_NS::Localization::Utf::UtfTraits&lt; CharType, 4 &gt;

**template &lt;typename CharType&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Localization**](namespaceSR__UTILS__NS_1_1Localization.md) **>** [**Utf**](namespaceSR__UTILS__NS_1_1Localization_1_1Utf.md) **>** [**UtfTraits&lt; CharType, 4 &gt;**](structSR__UTILS__NS_1_1Localization_1_1Utf_1_1UtfTraits_3_01CharType_00_014_01_4.md)



_utf16;_ 

* `#include <UTF.h>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef CharType | [**char\_type**](#typedef-char_type)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const int | [**MAX\_WIDTH**](#variable-max_width)   = `1`<br> |
















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  CodePoint | [**Decode**](#function-decode) (It & current, It last) <br> |
|  CodePoint | [**DecodeValid**](#function-decodevalid) (It & current) <br> |
|  It | [**Encode**](#function-encode) (CodePoint u, It out) <br> |
|  bool | [**IsLead**](#function-islead) (char\_type) <br> |
|  bool | [**IsTrail**](#function-istrail) (char\_type) <br> |
|  int | [**TrailLength**](#function-traillength) (char\_type c) <br> |
|  int | [**Width**](#function-width) (CodePoint) <br> |


























## Public Types Documentation




### typedef char\_type 

```C++
typedef CharType SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::char_type;
```




<hr>
## Public Static Attributes Documentation




### variable MAX\_WIDTH 

```C++
const int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::MAX_WIDTH;
```




<hr>
## Public Static Functions Documentation




### function Decode 

```C++
template<typename It>
static inline CodePoint SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::Decode (
    It & current,
    It last
) 
```




<hr>



### function DecodeValid 

```C++
template<typename It>
static inline CodePoint SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::DecodeValid (
    It & current
) 
```




<hr>



### function Encode 

```C++
template<typename It>
static inline It SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::Encode (
    CodePoint u,
    It out
) 
```




<hr>



### function IsLead 

```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::IsLead (
    char_type
) 
```




<hr>



### function IsTrail 

```C++
static inline bool SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::IsTrail (
    char_type
) 
```




<hr>



### function TrailLength 

```C++
static inline int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::TrailLength (
    char_type c
) 
```




<hr>



### function Width 

```C++
static inline int SR_UTILS_NS::Localization::Utf::UtfTraits< CharType, 4 >::Width (
    CodePoint
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Localization/UTF.h`

