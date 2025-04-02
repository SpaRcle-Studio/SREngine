

# File Hashes.h



[**FileList**](files.md) **>** [**Common**](dir_964cfbb3f15edef5ecfb3ae3bc01626c.md) **>** [**Hashes.h**](Hashes_8h.md)

[Go to the source code of this file](Hashes_8h_source.md)



* `#include <Utils/stdInclude.h>`
* `#include <Utils/Types/MerkleTree.h>`
* `#include <openssl/sha.h>`
* `#include <xxHash/xxhash.h>`













## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) <br> |
| namespace | [**Hash**](namespaceSR__UTILS__NS_1_1Hash.md) <br> |
| namespace | [**Detail**](namespaceSR__UTILS__NS_1_1Hash_1_1Detail.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Encoder**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1Encoder.md) &lt;S, N&gt;<br> |
| struct | [**Encoder&lt; S, 0 &gt;**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1Encoder_3_01S_00_010_01_4.md) &lt;S&gt;<br> |
| struct | [**MM**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1MM.md) &lt;size, idx, class dummy&gt;<br> |
| struct | [**MM&lt; size, size, dummy &gt;**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1MM_3_01size_00_01size_00_01dummy_01_4.md) &lt;size, class dummy&gt;<br> |
| struct | [**SRConditionallyEnabledHash**](structSR__UTILS__NS_1_1SRConditionallyEnabledHash.md) &lt;class T, Enabled&gt;<br> |
| struct | [**SRConditionallyEnabledHash&lt; T, false &gt;**](structSR__UTILS__NS_1_1SRConditionallyEnabledHash_3_01T_00_01false_01_4.md) &lt;class T&gt;<br> |
| struct | [**SRHash**](structSR__UTILS__NS_1_1SRHash.md) &lt;class T&gt;<br> |
| struct | [**SRHash&lt; double &gt;**](structSR__UTILS__NS_1_1SRHash_3_01double_01_4.md) &lt;&gt;<br> |
| struct | [**SRHash&lt; float &gt;**](structSR__UTILS__NS_1_1SRHash_3_01float_01_4.md) &lt;&gt;<br> |
| struct | [**SRHash&lt; long double &gt;**](structSR__UTILS__NS_1_1SRHash_3_01long_01double_01_4.md) &lt;&gt;<br> |
| struct | [**SRHash&lt; nullptr\_t &gt;**](structSR__UTILS__NS_1_1SRHash_3_01nullptr__t_01_4.md) &lt;&gt;<br> |
| struct | [**SRHash&lt; std::basic\_string&lt; Elem, std::char\_traits&lt; Elem &gt;, Alloc &gt; &gt;**](structSR__UTILS__NS_1_1SRHash_3_01std_1_1basic__string_3_01Elem_00_01std_1_1char__traits_3_01Elem_01_4_00_01Alloc_01_4_01_4.md) &lt;class Elem, class Alloc&gt;<br> |
| struct | [**SRHash&lt; std::basic\_string\_view&lt; Elem &gt; &gt;**](structSR__UTILS__NS_1_1SRHash_3_01std_1_1basic__string__view_3_01Elem_01_4_01_4.md) &lt;class Elem&gt;<br> |

















































## Macros

| Type | Name |
| ---: | :--- |
| define  | [**SR\_COMBINE\_HASHES**](Hashes_8h.md#define-sr_combine_hashes) (x1, x2) `(SR\_UTILS\_NS::CombineTwoHashes(x1, x2))`<br> |
| define  | [**SR\_COMPILE\_TIME\_CRC32\_STD\_STR**](Hashes_8h.md#define-sr_compile_time_crc32_std_str) (x) `(SR\_COMPILE\_TIME\_CRC32\_STR(x.c\_str()))`<br> |
| define  | [**SR\_COMPILE\_TIME\_CRC32\_STR**](Hashes_8h.md#define-sr_compile_time_crc32_str) (x) `(static\_cast&lt;uint64\_t&gt;([**SR\_UTILS\_NS::Hash::Detail::MM**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1MM.md)&lt;sizeof(x)-1&gt;::crc32(x)))`<br> |
| define  | [**SR\_COMPILE\_TIME\_CRC32\_TYPE\_NAME**](Hashes_8h.md#define-sr_compile_time_crc32_type_name) (x) `(SR\_COMPILE\_TIME\_CRC32\_TYPE\_NAME\_DETAIL(SR\_GET\_TYPE\_NAME(x)))`<br> |
| define  | [**SR\_COMPILE\_TIME\_CRC32\_TYPE\_NAME\_DETAIL**](Hashes_8h.md#define-sr_compile_time_crc32_type_name_detail) (x) `(static\_cast&lt;uint64\_t&gt;([**SR\_UTILS\_NS::Hash::Detail::MM**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1MM.md)&lt;x.size()&gt;::crc32(x.data())))`<br> |
| define  | [**SR\_GET\_TYPE\_NAME**](Hashes_8h.md#define-sr_get_type_name) (x) `SR\_UTILS\_NS::Hash::Detail::GetTypeName&lt;x&gt;()`<br> |
| define  | [**SR\_HASH**](Hashes_8h.md#define-sr_hash) (x) `(SR\_UTILS\_NS::CalculateHash(x))`<br> |
| define  | [**SR\_HASH\_STR**](Hashes_8h.md#define-sr_hash_str) (x) `(SR\_UTILS\_NS::CalculateHash&lt;std::string&gt;(x))`<br> |
| define  | [**SR\_HASH\_STR\_VIEW**](Hashes_8h.md#define-sr_hash_str_view) (x) `(SR\_UTILS\_NS::CalculateHash&lt;std::string\_view&gt;(x))`<br> |
| define  | [**SR\_RUNTIME\_TIME\_CRC32\_STD\_STR**](Hashes_8h.md#define-sr_runtime_time_crc32_std_str) (x) `(SR\_RUNTIME\_TIME\_CRC32\_STR(x.c\_str()))`<br> |
| define  | [**SR\_RUNTIME\_TIME\_CRC32\_STR**](Hashes_8h.md#define-sr_runtime_time_crc32_str) (x) `(static\_cast&lt;uint64\_t&gt;(SR\_UTILS\_NS::Hash::Detail::crc32(x)))`<br> |
| define  | [**SR\_RUNTIME\_TIME\_CRC32\_TYPE\_NAME**](Hashes_8h.md#define-sr_runtime_time_crc32_type_name) (x) `(SR\_COMPILE\_TIME\_CRC32\_TYPE\_NAME\_DETAIL(SR\_GET\_TYPE\_NAME(x)))`<br> |

## Macro Definition Documentation





### define SR\_COMBINE\_HASHES 

```C++
#define SR_COMBINE_HASHES (
    x1,
    x2
) `(SR_UTILS_NS::CombineTwoHashes(x1, x2))`
```




<hr>



### define SR\_COMPILE\_TIME\_CRC32\_STD\_STR 

```C++
#define SR_COMPILE_TIME_CRC32_STD_STR (
    x
) `(SR_COMPILE_TIME_CRC32_STR(x.c_str()))`
```




<hr>



### define SR\_COMPILE\_TIME\_CRC32\_STR 

```C++
#define SR_COMPILE_TIME_CRC32_STR (
    x
) `(static_cast<uint64_t>( SR_UTILS_NS::Hash::Detail::MM <sizeof(x)-1>::crc32(x)))`
```




<hr>



### define SR\_COMPILE\_TIME\_CRC32\_TYPE\_NAME 

```C++
#define SR_COMPILE_TIME_CRC32_TYPE_NAME (
    x
) `(SR_COMPILE_TIME_CRC32_TYPE_NAME_DETAIL(SR_GET_TYPE_NAME(x)))`
```




<hr>



### define SR\_COMPILE\_TIME\_CRC32\_TYPE\_NAME\_DETAIL 

```C++
#define SR_COMPILE_TIME_CRC32_TYPE_NAME_DETAIL (
    x
) `(static_cast<uint64_t>( SR_UTILS_NS::Hash::Detail::MM <x.size()>::crc32(x.data())))`
```




<hr>



### define SR\_GET\_TYPE\_NAME 

```C++
#define SR_GET_TYPE_NAME (
    x
) `SR_UTILS_NS::Hash::Detail::GetTypeName<x>()`
```




<hr>



### define SR\_HASH 

```C++
#define SR_HASH (
    x
) `(SR_UTILS_NS::CalculateHash(x))`
```




<hr>



### define SR\_HASH\_STR 

```C++
#define SR_HASH_STR (
    x
) `(SR_UTILS_NS::CalculateHash<std::string>(x))`
```




<hr>



### define SR\_HASH\_STR\_VIEW 

```C++
#define SR_HASH_STR_VIEW (
    x
) `(SR_UTILS_NS::CalculateHash<std::string_view>(x))`
```




<hr>



### define SR\_RUNTIME\_TIME\_CRC32\_STD\_STR 

```C++
#define SR_RUNTIME_TIME_CRC32_STD_STR (
    x
) `(SR_RUNTIME_TIME_CRC32_STR(x.c_str()))`
```




<hr>



### define SR\_RUNTIME\_TIME\_CRC32\_STR 

```C++
#define SR_RUNTIME_TIME_CRC32_STR (
    x
) `(static_cast<uint64_t>(SR_UTILS_NS::Hash::Detail::crc32(x)))`
```




<hr>



### define SR\_RUNTIME\_TIME\_CRC32\_TYPE\_NAME 

```C++
#define SR_RUNTIME_TIME_CRC32_TYPE_NAME (
    x
) `(SR_COMPILE_TIME_CRC32_TYPE_NAME_DETAIL(SR_GET_TYPE_NAME(x)))`
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Hashes.h`

