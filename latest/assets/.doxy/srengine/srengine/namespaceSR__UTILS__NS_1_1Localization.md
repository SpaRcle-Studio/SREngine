

# Namespace SR\_UTILS\_NS::Localization



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Localization**](namespaceSR__UTILS__NS_1_1Localization.md)


















## Namespaces

| Type | Name |
| ---: | :--- |
| namespace | [**Utf**](namespaceSR__UTILS__NS_1_1Localization_1_1Utf.md) <br> |


## Classes

| Type | Name |
| ---: | :--- |
| class | [**LocalizationFile**](classSR__UTILS__NS_1_1Localization_1_1LocalizationFile.md) <br> |
| class | [**LocalizationManager**](classSR__UTILS__NS_1_1Localization_1_1LocalizationManager.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**EncMethodType**](#enum-encmethodtype)  <br> |
| typedef std::string | [**Locale**](#typedef-locale)  <br>_TODO: стоит ли Locale делать через enum или следует использовать коды типа "en"._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**ConvertFrom**](#function-convertfrom) (const CharType \* begin, const CharType \* end, const char \* charset, EncMethodType how=EncMethodType::Default) <br> |
|  std::basic\_string&lt; CharType &gt; | [**ConvertTo**](#function-convertto) (const char \* begin, const char \* end, const char \* charset, EncMethodType how=EncMethodType::Default) <br> |
|  std::string | [**FromUtf**](#function-fromutf) (const CharType \* begin, const CharType \* end, const std::string & charset, EncMethodType how=EncMethodType::Default) <br> |
|  std::basic\_string&lt; CharType &gt; | [**ToUtf**](#function-toutf) (const char \* begin, const char \* end, const std::string & charset, EncMethodType how=EncMethodType::Default) <br> |
|  std::basic\_string&lt; CharOut &gt; | [**UtfToUtf**](#function-utftoutf) (CharIn const \* begin, CharIn const \* end, EncMethodType how=EncMethodType::Default) <br> |
|  std::basic\_string&lt; CharOut &gt; | [**UtfToUtf**](#function-utftoutf) (CharIn const \* str, EncMethodType how=EncMethodType::Default) <br> |
|  std::basic\_string&lt; CharOut &gt; | [**UtfToUtf**](#function-utftoutf) (std::basic\_string&lt; CharIn &gt; const & str, EncMethodType how=EncMethodType::Default) <br> |
|  std::basic\_string&lt; CharOut &gt; | [**UtfToUtf**](#function-utftoutf) (std::basic\_string\_view&lt; CharIn &gt; const & str, EncMethodType how=EncMethodType::Default) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED void | [**SetLocale**](#function-setlocale) () <br> |


























## Public Types Documentation




### enum EncMethodType 

```C++
enum SR_UTILS_NS::Localization::EncMethodType {
    Skip = 0,
    Stop = 1,
    Default = Skip
};
```




<hr>



### typedef Locale 

_TODO: стоит ли Locale делать через enum или следует использовать коды типа "en"._ 
```C++
using SR_UTILS_NS::Localization::Locale =  std::string;
```




<hr>
## Public Functions Documentation




### function ConvertFrom 

```C++
template<typename CharType>
std::string SR_UTILS_NS::Localization::ConvertFrom (
    const CharType * begin,
    const CharType * end,
    const char * charset,
    EncMethodType how=EncMethodType::Default
) 
```




<hr>



### function ConvertTo 

```C++
template<typename CharType>
std::basic_string< CharType > SR_UTILS_NS::Localization::ConvertTo (
    const char * begin,
    const char * end,
    const char * charset,
    EncMethodType how=EncMethodType::Default
) 
```




<hr>



### function FromUtf 

```C++
template<typename CharType>
std::string SR_UTILS_NS::Localization::FromUtf (
    const CharType * begin,
    const CharType * end,
    const std::string & charset,
    EncMethodType how=EncMethodType::Default
) 
```




<hr>



### function ToUtf 

```C++
template<typename CharType>
std::basic_string< CharType > SR_UTILS_NS::Localization::ToUtf (
    const char * begin,
    const char * end,
    const std::string & charset,
    EncMethodType how=EncMethodType::Default
) 
```



std::string Between(const char\* begin, const char\* end, const std::string& to\_charset, const std::string& from\_charset, EncMethodType how = EncMethodType::Default ) { return ConvertBetween(begin, end, to\_charset, from\_charset, how); } 


        

<hr>



### function UtfToUtf 

```C++
template<typename CharOut, typename CharIn>
std::basic_string< CharOut > SR_UTILS_NS::Localization::UtfToUtf (
    CharIn const * begin,
    CharIn const * end,
    EncMethodType how=EncMethodType::Default
) 
```




<hr>



### function UtfToUtf 

```C++
template<typename CharOut, typename CharIn>
std::basic_string< CharOut > SR_UTILS_NS::Localization::UtfToUtf (
    CharIn const * str,
    EncMethodType how=EncMethodType::Default
) 
```



Convert a Unicode NUL terminated string _str_ other Unicode encoding 


        

<hr>



### function UtfToUtf 

```C++
template<typename CharOut, typename CharIn>
std::basic_string< CharOut > SR_UTILS_NS::Localization::UtfToUtf (
    std::basic_string< CharIn > const & str,
    EncMethodType how=EncMethodType::Default
) 
```



Convert a Unicode string _str_ other Unicode encoding 


        

<hr>



### function UtfToUtf 

```C++
template<typename CharOut, typename CharIn>
std::basic_string< CharOut > SR_UTILS_NS::Localization::UtfToUtf (
    std::basic_string_view< CharIn > const & str,
    EncMethodType how=EncMethodType::Default
) 
```




<hr>
## Public Static Functions Documentation




### function SetLocale 

```C++
static SR_MAYBE_UNUSED void SR_UTILS_NS::Localization::SetLocale () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Localization/Convert.h`

