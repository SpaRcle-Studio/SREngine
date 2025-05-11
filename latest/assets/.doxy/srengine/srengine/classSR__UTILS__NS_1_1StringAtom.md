

# Class SR\_UTILS\_NS::StringAtom



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md)



_@scriptableClass_ 

* `#include <StringAtom.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains) (const char \* str) const<br> |
|  SR\_NODISCARD bool | [**Empty**](#function-empty) () const<br>_@method_  |
|  SR\_NODISCARD uint64\_t | [**GetHash**](#function-gethash) () const<br> |
|  SR\_NODISCARD uint64\_t | [**Size**](#function-size) () const<br>_@method_  |
|   | [**StringAtom**](#function-stringatom-16) () <br>_@constructor_  |
|   | [**StringAtom**](#function-stringatom-26) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & other) = default<br> |
|   | [**StringAtom**](#function-stringatom-36) ([**StringHashInfo**](structSR__UTILS__NS_1_1StringHashInfo.md) \* pInfo) <br> |
|   | [**StringAtom**](#function-stringatom-46) (const char \* str) <br>_@constructor_  |
|   | [**StringAtom**](#function-stringatom-56) (const std::string & str) <br>_NOLINT._  |
|   | [**StringAtom**](#function-stringatom-66) (std::string\_view str) <br>_NOLINT._  |
|  SR\_NODISCARD const char \* | [**ToCStr**](#function-tocstr) () const<br>_@method_  |
|  SR\_NODISCARD std::string | [**ToString**](#function-tostring) () const<br> |
|  SR\_NODISCARD const std::string & | [**ToStringRef**](#function-tostringref) () const<br> |
|  SR\_NODISCARD std::string\_view | [**ToStringView**](#function-tostringview) () const<br> |
|  SR\_NODISCARD const char \* | [**c\_str**](#function-c_str) () const<br>_@method_  |
|  void | [**clear**](#function-clear) () <br> |
|  SR\_NODISCARD const char \* | [**data**](#function-data) () const<br>_@method_  |
|  SR\_NODISCARD bool | [**empty**](#function-empty) () const<br>_@method_  |
|   | [**string &**](#function-string-&) () noexcept const<br>_NOLINT._  |
|   | [**string\_view**](#function-string_view) () noexcept const<br>_NOLINT._  |
|  SR\_NODISCARD | [**operator uint64\_t**](#function-operator-uint64_t) () noexcept const<br> |
|  bool | [**operator&lt;**](#function-operator) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & other) noexcept const<br>_@operator_  |
|  bool | [**operator&lt;**](#function-operator_1) (uint64\_t hash) noexcept const<br>_@operator_  |
|  [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & | [**operator=**](#function-operator_2) (const std::string & str) <br> |
|  [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & | [**operator=**](#function-operator_3) (const char \* str) <br>_@operator_  |
|  bool | [**operator==**](#function-operator_4) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & rhs) noexcept const<br>_@operator_  |
|  bool | [**operator==**](#function-operator_5) (const std::string & rhs) noexcept const<br> |
|  bool | [**operator==**](#function-operator_6) (const std::string\_view & rhs) noexcept const<br> |
|  bool | [**operator==**](#function-operator_7) (const char \* rhs) noexcept const<br>_@operator_  |
|  SR\_NODISCARD char | [**operator[]**](#function-operator_8) (size\_t index) noexcept const<br>_@operator_  |
|  SR\_NODISCARD uint64\_t | [**size**](#function-size) () const<br>_@method_  |




























## Public Functions Documentation




### function Clear 

```C++
void SR_UTILS_NS::StringAtom::Clear () 
```




<hr>



### function Contains 

```C++
SR_NODISCARD bool SR_UTILS_NS::StringAtom::Contains (
    const char * str
) const
```




<hr>



### function Empty 

_@method_ 
```C++
SR_NODISCARD bool SR_UTILS_NS::StringAtom::Empty () const
```




<hr>



### function GetHash 

```C++
SR_NODISCARD uint64_t SR_UTILS_NS::StringAtom::GetHash () const
```




<hr>



### function Size 

_@method_ 
```C++
SR_NODISCARD uint64_t SR_UTILS_NS::StringAtom::Size () const
```




<hr>



### function StringAtom [1/6]

_@constructor_ 
```C++
SR_UTILS_NS::StringAtom::StringAtom () 
```




<hr>



### function StringAtom [2/6]

```C++
SR_UTILS_NS::StringAtom::StringAtom (
    const StringAtom & other
) = default
```




<hr>



### function StringAtom [3/6]

```C++
SR_UTILS_NS::StringAtom::StringAtom (
    StringHashInfo * pInfo
) 
```




<hr>



### function StringAtom [4/6]

_@constructor_ 
```C++
SR_UTILS_NS::StringAtom::StringAtom (
    const char * str
) 
```



NOLINT 


        

<hr>



### function StringAtom [5/6]

_NOLINT._ 
```C++
SR_UTILS_NS::StringAtom::StringAtom (
    const std::string & str
) 
```




<hr>



### function StringAtom [6/6]

_NOLINT._ 
```C++
SR_UTILS_NS::StringAtom::StringAtom (
    std::string_view str
) 
```




<hr>



### function ToCStr 

_@method_ 
```C++
SR_NODISCARD const char * SR_UTILS_NS::StringAtom::ToCStr () const
```




<hr>



### function ToString 

```C++
SR_NODISCARD std::string SR_UTILS_NS::StringAtom::ToString () const
```




<hr>



### function ToStringRef 

```C++
SR_NODISCARD const std::string & SR_UTILS_NS::StringAtom::ToStringRef () const
```




<hr>



### function ToStringView 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::StringAtom::ToStringView () const
```




<hr>



### function c\_str 

_@method_ 
```C++
SR_NODISCARD const char * SR_UTILS_NS::StringAtom::c_str () const
```




<hr>



### function clear 

```C++
void SR_UTILS_NS::StringAtom::clear () 
```




<hr>



### function data 

_@method_ 
```C++
SR_NODISCARD const char * SR_UTILS_NS::StringAtom::data () const
```




<hr>



### function empty 

_@method_ 
```C++
SR_NODISCARD bool SR_UTILS_NS::StringAtom::empty () const
```




<hr>



### function string & 

_NOLINT._ 
```C++
SR_UTILS_NS::StringAtom::string & () noexcept const
```




<hr>



### function string\_view 

_NOLINT._ 
```C++
SR_UTILS_NS::StringAtom::string_view () noexcept const
```




<hr>



### function operator uint64\_t 

```C++
SR_NODISCARD SR_UTILS_NS::StringAtom::operator uint64_t () noexcept const
```




<hr>



### function operator&lt; 

_@operator_ 
```C++
bool SR_UTILS_NS::StringAtom::operator< (
    const StringAtom & other
) noexcept const
```




<hr>



### function operator&lt; 

_@operator_ 
```C++
bool SR_UTILS_NS::StringAtom::operator< (
    uint64_t hash
) noexcept const
```




<hr>



### function operator= 

```C++
StringAtom & SR_UTILS_NS::StringAtom::operator= (
    const std::string & str
) 
```




<hr>



### function operator= 

_@operator_ 
```C++
StringAtom & SR_UTILS_NS::StringAtom::operator= (
    const char * str
) 
```




<hr>



### function operator== 

_@operator_ 
```C++
bool SR_UTILS_NS::StringAtom::operator== (
    const StringAtom & rhs
) noexcept const
```



NOLINT 


        

<hr>



### function operator== 

```C++
bool SR_UTILS_NS::StringAtom::operator== (
    const std::string & rhs
) noexcept const
```




<hr>



### function operator== 

```C++
bool SR_UTILS_NS::StringAtom::operator== (
    const std::string_view & rhs
) noexcept const
```




<hr>



### function operator== 

_@operator_ 
```C++
bool SR_UTILS_NS::StringAtom::operator== (
    const char * rhs
) noexcept const
```




<hr>



### function operator[] 

_@operator_ 
```C++
SR_NODISCARD char SR_UTILS_NS::StringAtom::operator[] (
    size_t index
) noexcept const
```




<hr>



### function size 

_@method_ 
```C++
SR_NODISCARD uint64_t SR_UTILS_NS::StringAtom::size () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/StringAtom.h`

