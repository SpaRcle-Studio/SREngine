

# Namespace SR\_UTILS\_NS::Hash::Detail



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Hash**](namespaceSR__UTILS__NS_1_1Hash.md) **>** [**Detail**](namespaceSR__UTILS__NS_1_1Hash_1_1Detail.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Encoder**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1Encoder.md) &lt;S, N&gt;<br> |
| struct | [**Encoder&lt; S, 0 &gt;**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1Encoder_3_01S_00_010_01_4.md) &lt;S&gt;<br> |
| struct | [**MM**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1MM.md) &lt;size, idx, class dummy&gt;<br> |
| struct | [**MM&lt; size, size, dummy &gt;**](structSR__UTILS__NS_1_1Hash_1_1Detail_1_1MM_3_01size_00_01size_00_01dummy_01_4.md) &lt;size, class dummy&gt;<br> |








## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  unsigned int | [**crc\_table**](#variable-crc_table)  <br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string\_view | [**GetTypeName**](#function-gettypename) () <br> |
|  auto | [**crc32**](#function-crc32) (const char \* in) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SRHashType | [**InitialHash**](#function-initialhash) () noexcept<br> |
|  SRHashType | [**MagicPrime**](#function-magicprime) () noexcept<br> |


























## Public Static Attributes Documentation




### variable crc\_table 

```C++
unsigned int SR_UTILS_NS::Hash::Detail::crc_table[256];
```




<hr>
## Public Functions Documentation




### function GetTypeName 

```C++
template<class T>
std::string_view SR_UTILS_NS::Hash::Detail::GetTypeName () 
```




<hr>



### function crc32 

```C++
auto SR_UTILS_NS::Hash::Detail::crc32 (
    const char * in
) 
```




<hr>
## Public Static Functions Documentation




### function InitialHash 

```C++
static SRHashType SR_UTILS_NS::Hash::Detail::InitialHash () noexcept
```




<hr>



### function MagicPrime 

```C++
static SRHashType SR_UTILS_NS::Hash::Detail::MagicPrime () noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/Hashes.h`

