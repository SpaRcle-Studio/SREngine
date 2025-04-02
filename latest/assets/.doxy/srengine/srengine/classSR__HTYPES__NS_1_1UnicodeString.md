

# Class SR\_HTYPES\_NS::UnicodeString



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef char32\_t | [**CharType**](#typedef-chartype)  <br> |
| typedef std::u32string::const\_iterator | [**ConstIterator**](#typedef-constiterator)  <br> |
| typedef std::u32string::iterator | [**Iterator**](#typedef-iterator)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**UnicodeString**](#function-unicodestring-16) () = default<br> |
|   | [**UnicodeString**](#function-unicodestring-26) (const [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & other) <br> |
|   | [**UnicodeString**](#function-unicodestring-36) ([**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) && other) noexcept<br> |
|   | [**UnicodeString**](#function-unicodestring-46) (const std::string & str) <br> |
|   | [**UnicodeString**](#function-unicodestring-56) (const std::u16string & str) <br>_NOLINT(google-explicit-constructor)_  |
|   | [**UnicodeString**](#function-unicodestring-66) (const std::u32string & str) <br>_NOLINT(google-explicit-constructor)_  |
|  SR\_NODISCARD std::u32string\_view | [**View**](#function-view) () noexcept const<br> |
|  SR\_NODISCARD Iterator | [**begin**](#function-begin-12) () noexcept<br> |
|  SR\_NODISCARD ConstIterator | [**begin**](#function-begin-22) () noexcept const<br> |
|  SR\_NODISCARD const CharType \* | [**c\_str**](#function-c_str) () noexcept const<br> |
|  SR\_NODISCARD CharType \* | [**data**](#function-data) () noexcept<br> |
|  SR\_NODISCARD bool | [**empty**](#function-empty) () noexcept const<br> |
|  SR\_NODISCARD Iterator | [**end**](#function-end-12) () noexcept<br> |
|  SR\_NODISCARD ConstIterator | [**end**](#function-end-22) () noexcept const<br> |
|  SR\_NODISCARD | [**u32string**](#function-u32string) () noexcept const<br> |
|  SR\_NODISCARD | [**u32string\_view**](#function-u32string_view) () noexcept const<br>_NOLINT(google-explicit-constructor)_  |
|  bool | [**operator!=**](#function-operator) (const std::u32string & str) noexcept const<br> |
|  bool | [**operator!=**](#function-operator_1) (const [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & str) noexcept const<br> |
|  [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & | [**operator=**](#function-operator_2) (const [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & other) <br> |
|  [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & | [**operator=**](#function-operator_3) ([**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) && other) noexcept<br> |
|  [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & | [**operator=**](#function-operator_4) (const std::u32string & other) <br> |
|  [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & | [**operator=**](#function-operator_5) (std::u32string && other) noexcept<br> |
|  bool | [**operator==**](#function-operator_6) (const std::u32string & str) noexcept const<br> |
|  bool | [**operator==**](#function-operator_7) (const [**UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & str) noexcept const<br> |
|  SR\_NODISCARD CharType & | [**operator[]**](#function-operator_8) (size\_t position) noexcept<br> |
|  SR\_NODISCARD const CharType & | [**operator[]**](#function-operator_9) (size\_t position) noexcept const<br> |
|  void | [**resize**](#function-resize) (size\_t size) <br>_NOLINT(google-explicit-constructor)_  |
|  SR\_NODISCARD size\_t | [**size**](#function-size) () noexcept const<br> |
| virtual  | [**~UnicodeString**](#function-unicodestring) () = default<br>_NOLINT(google-explicit-constructor)_  |




























## Public Types Documentation




### typedef CharType 

```C++
using SR_HTYPES_NS::UnicodeString::CharType =  char32_t;
```




<hr>



### typedef ConstIterator 

```C++
using SR_HTYPES_NS::UnicodeString::ConstIterator =  std::u32string::const_iterator;
```




<hr>



### typedef Iterator 

```C++
using SR_HTYPES_NS::UnicodeString::Iterator =  std::u32string::iterator;
```




<hr>
## Public Functions Documentation




### function UnicodeString [1/6]

```C++
SR_HTYPES_NS::UnicodeString::UnicodeString () = default
```




<hr>



### function UnicodeString [2/6]

```C++
SR_HTYPES_NS::UnicodeString::UnicodeString (
    const UnicodeString & other
) 
```




<hr>



### function UnicodeString [3/6]

```C++
SR_HTYPES_NS::UnicodeString::UnicodeString (
    UnicodeString && other
) noexcept
```




<hr>



### function UnicodeString [4/6]

```C++
SR_HTYPES_NS::UnicodeString::UnicodeString (
    const std::string & str
) 
```




<hr>



### function UnicodeString [5/6]

_NOLINT(google-explicit-constructor)_ 
```C++
SR_HTYPES_NS::UnicodeString::UnicodeString (
    const std::u16string & str
) 
```




<hr>



### function UnicodeString [6/6]

_NOLINT(google-explicit-constructor)_ 
```C++
SR_HTYPES_NS::UnicodeString::UnicodeString (
    const std::u32string & str
) 
```




<hr>



### function View 

```C++
inline SR_NODISCARD std::u32string_view SR_HTYPES_NS::UnicodeString::View () noexcept const
```




<hr>



### function begin [1/2]

```C++
inline SR_NODISCARD Iterator SR_HTYPES_NS::UnicodeString::begin () noexcept
```




<hr>



### function begin [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_HTYPES_NS::UnicodeString::begin () noexcept const
```




<hr>



### function c\_str 

```C++
inline SR_NODISCARD const CharType * SR_HTYPES_NS::UnicodeString::c_str () noexcept const
```




<hr>



### function data 

```C++
inline SR_NODISCARD CharType * SR_HTYPES_NS::UnicodeString::data () noexcept
```




<hr>



### function empty 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::UnicodeString::empty () noexcept const
```




<hr>



### function end [1/2]

```C++
inline SR_NODISCARD Iterator SR_HTYPES_NS::UnicodeString::end () noexcept
```




<hr>



### function end [2/2]

```C++
inline SR_NODISCARD ConstIterator SR_HTYPES_NS::UnicodeString::end () noexcept const
```




<hr>



### function u32string 

```C++
inline SR_NODISCARD SR_HTYPES_NS::UnicodeString::u32string () noexcept const
```




<hr>



### function u32string\_view 

_NOLINT(google-explicit-constructor)_ 
```C++
inline SR_NODISCARD SR_HTYPES_NS::UnicodeString::u32string_view () noexcept const
```




<hr>



### function operator!= 

```C++
inline bool SR_HTYPES_NS::UnicodeString::operator!= (
    const std::u32string & str
) noexcept const
```




<hr>



### function operator!= 

```C++
inline bool SR_HTYPES_NS::UnicodeString::operator!= (
    const UnicodeString & str
) noexcept const
```




<hr>



### function operator= 

```C++
UnicodeString & SR_HTYPES_NS::UnicodeString::operator= (
    const UnicodeString & other
) 
```




<hr>



### function operator= 

```C++
UnicodeString & SR_HTYPES_NS::UnicodeString::operator= (
    UnicodeString && other
) noexcept
```




<hr>



### function operator= 

```C++
UnicodeString & SR_HTYPES_NS::UnicodeString::operator= (
    const std::u32string & other
) 
```




<hr>



### function operator= 

```C++
UnicodeString & SR_HTYPES_NS::UnicodeString::operator= (
    std::u32string && other
) noexcept
```




<hr>



### function operator== 

```C++
inline bool SR_HTYPES_NS::UnicodeString::operator== (
    const std::u32string & str
) noexcept const
```




<hr>



### function operator== 

```C++
inline bool SR_HTYPES_NS::UnicodeString::operator== (
    const UnicodeString & str
) noexcept const
```




<hr>



### function operator[] 

```C++
SR_NODISCARD CharType & SR_HTYPES_NS::UnicodeString::operator[] (
    size_t position
) noexcept
```




<hr>



### function operator[] 

```C++
SR_NODISCARD const CharType & SR_HTYPES_NS::UnicodeString::operator[] (
    size_t position
) noexcept const
```




<hr>



### function resize 

_NOLINT(google-explicit-constructor)_ 
```C++
void SR_HTYPES_NS::UnicodeString::resize (
    size_t size
) 
```




<hr>



### function size 

```C++
inline SR_NODISCARD size_t SR_HTYPES_NS::UnicodeString::size () noexcept const
```




<hr>



### function ~UnicodeString 

_NOLINT(google-explicit-constructor)_ 
```C++
virtual SR_HTYPES_NS::UnicodeString::~UnicodeString () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/UnicodeString.h`

