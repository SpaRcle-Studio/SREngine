

# Class SR\_UTILS\_NS::StringUtils



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**StringUtils**](classSR__UTILS__NS_1_1StringUtils.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const std::string | [**base64\_chars**](#variable-base64_chars)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**StringUtils**](#function-stringutils-12) () = delete<br> |
|   | [**StringUtils**](#function-stringutils-22) ([**StringUtils**](classSR__UTILS__NS_1_1StringUtils.md) &) = delete<br> |
|  SR\_NODISCARD SR\_INLINE\_STATIC std::string | [**ToLower**](#function-tolower) (std::string str) noexcept<br> |
|  SR\_INLINE\_STATIC void | [**ToLowerRef**](#function-tolowerref) (std::string\_view str) noexcept<br> |
|  SR\_INLINE\_STATIC void | [**ToUpperRef**](#function-toupperref) (std::string\_view str) noexcept<br> |
|   | [**~StringUtils**](#function-stringutils) () = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_FORCE\_INLINE std::string | [**BackRead**](#function-backread) (const std::string & str, const char c, const int offset=0) <br> |
|  std::string | [**BackSubstring**](#function-backsubstring) (const std::string & str, char c) <br> |
|  std::string | [**Base64Decode**](#function-base64decode) (const std::string & base64) <br> |
|  std::string | [**Base64Encode**](#function-base64encode) (const std::string & data) <br> |
|  SR\_NODISCARD bool | [**Contains**](#function-contains) (const std::string & str, const std::string & word) noexcept<br> |
|  SR\_NODISCARD std::string | [**CutName**](#function-cutname) (std::string str, unsigned int frompos) <br> |
|  unsigned long | [**FastStrLen**](#function-faststrlen) (const char \* str) noexcept<br> |
|  int32\_t | [**FindClosest**](#function-findclosest) (const std::string & str, const std::string & characters) <br> |
|  SR\_NODISCARD std::string | [**FromCharVector**](#function-fromcharvector) (const std::vector&lt; char &gt; & vs) noexcept<br> |
|  std::string | [**GetBetween**](#function-getbetween-13) (const std::string & source, int64\_t begin, uint64\_t end) <br> |
|  std::string\_view | [**GetBetween**](#function-getbetween-23) (std::string\_view source, char begin, char end, int8\_t \* pResult=nullptr) <br> |
|  std::string | [**GetBetween**](#function-getbetween-33) (const std::string & source, const std::string & begin, const std::string & end) <br> |
|  SR\_FORCE\_INLINE std::string | [**GetDirFromPath**](#function-getdirfrompath) (const std::string & path) <br> |
|  SR\_FORCE\_INLINE std::string | [**GetDirToFileFromFullPath**](#function-getdirtofilefromfullpath) (std::string full\_path) <br> |
|  std::string | [**GetExtensionFromFilePath**](#function-getextensionfromfilepath) (std::string path) <br> |
|  SR\_FORCE\_INLINE std::string | [**GetFileNameFromFullPath**](#function-getfilenamefromfullpath) (std::string full\_path) <br> |
|  SR\_FORCE\_INLINE int32\_t | [**IndexOf**](#function-indexof-12) (const std::string & str, const char & symbol, uint32\_t offset=0) <br> |
|  SR\_FORCE\_INLINE int32\_t | [**IndexOf**](#function-indexof-22) (const std::string & str, const std::string & subStr, uint32\_t offset=0) <br> |
|  glm::vec3 | [**IntToColor**](#function-inttocolor) (size\_t index) noexcept<br> |
|  bool | [**IsBase64**](#function-isbase64) (unsigned char c) <br> |
|  SR\_NODISCARD std::string | [**MakePath**](#function-makepath) (const std::string & str, bool toLower=false) noexcept<br> |
|  glm::vec2 | [**MakeVec2FromString**](#function-makevec2fromstring) (const char \* source, char chr, unsigned short start) <br> |
|  glm::vec3 | [**MakeVec3FromString**](#function-makevec3fromstring) (const char \* source, char chr, unsigned short start) <br> |
|  SR\_NODISCARD unsigned char | [**MathCount**](#function-mathcount) (const char \* str, char symb) noexcept<br> |
|  SR\_FORCE\_INLINE std::string | [**MultiConcat**](#function-multiconcat) (const std::string & target, int32\_t n) <br> |
|  std::string | [**ReadFrom**](#function-readfrom) (const std::string & str, const char & c, uint32\_t start) <br> |
|  std::string | [**ReadNumber**](#function-readnumber) (const std::string & str, uint32\_t start) <br> |
|  std::string | [**ReadTo**](#function-readto) (std::string str, const char c, int offset=0) <br> |
|  std::string | [**Remove**](#function-remove-12) (std::string source, uint32\_t count) <br> |
|  std::string | [**Remove**](#function-remove-22) (std::string source, uint32\_t start, uint32\_t count) <br> |
|  std::string | [**RemoveCharsFromString**](#function-removecharsfromstring) (std::string source, const std::string & charsToRemove) <br> |
|  SR\_NODISCARD stringType | [**ReplaceAll**](#function-replaceall) (stringType const & original, stringType const & from, stringType const & to) noexcept<br> |
|  SR\_NODISCARD std::string | [**ReplaceAllRecursive**](#function-replaceallrecursive) (const std::string & original, const std::vector&lt; std::string &gt; & fromList, const std::string & to) noexcept<br> |
|  std::string | [**Resize**](#function-resize) (std::string str, size\_t newSize) noexcept<br> |
|  std::string | [**Reverse**](#function-reverse) (const std::string & str) <br> |
|  SR\_NODISCARD std::vector&lt; std::string &gt; | [**Split**](#function-split-12) (std::string source, const std::string & delimiter) <br> |
|  SR\_NODISCARD char \*\* | [**Split**](#function-split-22) (const char \* source, char chr, unsigned short start, unsigned short count\_strs) <br> |
|  SR\_NODISCARD float \* | [**SplitFloats**](#function-splitfloats) (const char \* source, char chr, unsigned short start, unsigned short count\_floats) <br> |
|  SR\_NODISCARD std::pair&lt; std::string, std::string &gt; | [**SplitTwo**](#function-splittwo) (std::string source, const std::string & delimiter) <br> |
|  SR\_NODISCARD std::vector&lt; std::string\_view &gt; | [**SplitView**](#function-splitview) (std::string\_view source, std::string\_view delimiter) <br> |
|  SR\_NODISCARD std::vector&lt; std::string\_view &gt; | [**SplitViewWithEmpty**](#function-splitviewwithempty) (std::string\_view source, std::string\_view delimiter) <br> |
|  std::string | [**Substring**](#function-substring-13) (const std::string & source, char symbol, uint32\_t offset=0) <br> |
|  std::string | [**Substring**](#function-substring-23) (const std::string & source, const char \* subStr) <br> |
|  std::string | [**Substring**](#function-substring-33) (const std::string\_view & source, char symbol, uint32\_t offset=0) <br> |
|  std::string\_view | [**SubstringView**](#function-substringview-12) (const std::string\_view & source, char symbol, uint32\_t offset=0) <br> |
|  std::string\_view | [**SubstringView**](#function-substringview-22) (const std::string\_view & source, [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) substr, uint32\_t offset=0) <br> |
|  std::string | [**Tab**](#function-tab) (std::string code, uint32\_t count=1) <br> |
|  std::string | [**ToKebabCase**](#function-tokebabcase) (std::string\_view str) <br> |
|  bool | [**is\_base64**](#function-is_base64) (unsigned char c) <br> |
|  SR\_NODISCARD std::wstring | [**utf8\_to\_wstring**](#function-utf8_to_wstring) (const std::string & str) <br> |
|  SR\_NODISCARD std::string | [**wstring\_to\_utf8**](#function-wstring_to_utf8) (const std::wstring & str) <br> |


























## Public Static Attributes Documentation




### variable base64\_chars 

```C++
const std::string SR_UTILS_NS::StringUtils::base64_chars;
```




<hr>
## Public Functions Documentation




### function StringUtils [1/2]

```C++
SR_UTILS_NS::StringUtils::StringUtils () = delete
```




<hr>



### function StringUtils [2/2]

```C++
SR_UTILS_NS::StringUtils::StringUtils (
    StringUtils &
) = delete
```




<hr>



### function ToLower 

```C++
inline SR_NODISCARD SR_INLINE_STATIC std::string SR_UTILS_NS::StringUtils::ToLower (
    std::string str
) noexcept
```




<hr>



### function ToLowerRef 

```C++
inline SR_INLINE_STATIC void SR_UTILS_NS::StringUtils::ToLowerRef (
    std::string_view str
) noexcept
```




<hr>



### function ToUpperRef 

```C++
inline SR_INLINE_STATIC void SR_UTILS_NS::StringUtils::ToUpperRef (
    std::string_view str
) noexcept
```




<hr>



### function ~StringUtils 

```C++
SR_UTILS_NS::StringUtils::~StringUtils () = delete
```




<hr>
## Public Static Functions Documentation




### function BackRead 

```C++
static inline SR_FORCE_INLINE std::string SR_UTILS_NS::StringUtils::BackRead (
    const std::string & str,
    const char c,
    const int offset=0
) 
```




<hr>



### function BackSubstring 

```C++
static inline std::string SR_UTILS_NS::StringUtils::BackSubstring (
    const std::string & str,
    char c
) 
```




<hr>



### function Base64Decode 

```C++
static std::string SR_UTILS_NS::StringUtils::Base64Decode (
    const std::string & base64
) 
```




<hr>



### function Base64Encode 

```C++
static std::string SR_UTILS_NS::StringUtils::Base64Encode (
    const std::string & data
) 
```




<hr>



### function Contains 

```C++
static inline SR_NODISCARD bool SR_UTILS_NS::StringUtils::Contains (
    const std::string & str,
    const std::string & word
) noexcept
```




<hr>



### function CutName 

```C++
static inline SR_NODISCARD std::string SR_UTILS_NS::StringUtils::CutName (
    std::string str,
    unsigned int frompos
) 
```




<hr>



### function FastStrLen 

```C++
static inline unsigned long SR_UTILS_NS::StringUtils::FastStrLen (
    const char * str
) noexcept
```




<hr>



### function FindClosest 

```C++
static inline int32_t SR_UTILS_NS::StringUtils::FindClosest (
    const std::string & str,
    const std::string & characters
) 
```




<hr>



### function FromCharVector 

```C++
static inline SR_NODISCARD std::string SR_UTILS_NS::StringUtils::FromCharVector (
    const std::vector< char > & vs
) noexcept
```




<hr>



### function GetBetween [1/3]

```C++
static inline std::string SR_UTILS_NS::StringUtils::GetBetween (
    const std::string & source,
    int64_t begin,
    uint64_t end
) 
```




<hr>



### function GetBetween [2/3]

```C++
static inline std::string_view SR_UTILS_NS::StringUtils::GetBetween (
    std::string_view source,
    char begin,
    char end,
    int8_t * pResult=nullptr
) 
```




<hr>



### function GetBetween [3/3]

```C++
static inline std::string SR_UTILS_NS::StringUtils::GetBetween (
    const std::string & source,
    const std::string & begin,
    const std::string & end
) 
```




<hr>



### function GetDirFromPath 

```C++
static inline SR_FORCE_INLINE std::string SR_UTILS_NS::StringUtils::GetDirFromPath (
    const std::string & path
) 
```




<hr>



### function GetDirToFileFromFullPath 

```C++
static inline SR_FORCE_INLINE std::string SR_UTILS_NS::StringUtils::GetDirToFileFromFullPath (
    std::string full_path
) 
```




<hr>



### function GetExtensionFromFilePath 

```C++
static std::string SR_UTILS_NS::StringUtils::GetExtensionFromFilePath (
    std::string path
) 
```




<hr>



### function GetFileNameFromFullPath 

```C++
static inline SR_FORCE_INLINE std::string SR_UTILS_NS::StringUtils::GetFileNameFromFullPath (
    std::string full_path
) 
```




<hr>



### function IndexOf [1/2]

```C++
static inline SR_FORCE_INLINE int32_t SR_UTILS_NS::StringUtils::IndexOf (
    const std::string & str,
    const char & symbol,
    uint32_t offset=0
) 
```




<hr>



### function IndexOf [2/2]

```C++
static inline SR_FORCE_INLINE int32_t SR_UTILS_NS::StringUtils::IndexOf (
    const std::string & str,
    const std::string & subStr,
    uint32_t offset=0
) 
```




<hr>



### function IntToColor 

```C++
static inline glm::vec3 SR_UTILS_NS::StringUtils::IntToColor (
    size_t index
) noexcept
```




<hr>



### function IsBase64 

```C++
static inline bool SR_UTILS_NS::StringUtils::IsBase64 (
    unsigned char c
) 
```




<hr>



### function MakePath 

```C++
static inline SR_NODISCARD std::string SR_UTILS_NS::StringUtils::MakePath (
    const std::string & str,
    bool toLower=false
) noexcept
```




<hr>



### function MakeVec2FromString 

```C++
static glm::vec2 SR_UTILS_NS::StringUtils::MakeVec2FromString (
    const char * source,
    char chr,
    unsigned short start
) 
```




<hr>



### function MakeVec3FromString 

```C++
static glm::vec3 SR_UTILS_NS::StringUtils::MakeVec3FromString (
    const char * source,
    char chr,
    unsigned short start
) 
```




<hr>



### function MathCount 

```C++
static inline SR_NODISCARD unsigned char SR_UTILS_NS::StringUtils::MathCount (
    const char * str,
    char symb
) noexcept
```




<hr>



### function MultiConcat 

```C++
static inline SR_FORCE_INLINE std::string SR_UTILS_NS::StringUtils::MultiConcat (
    const std::string & target,
    int32_t n
) 
```




<hr>



### function ReadFrom 

```C++
static std::string SR_UTILS_NS::StringUtils::ReadFrom (
    const std::string & str,
    const char & c,
    uint32_t start
) 
```




<hr>



### function ReadNumber 

```C++
static std::string SR_UTILS_NS::StringUtils::ReadNumber (
    const std::string & str,
    uint32_t start
) 
```




<hr>



### function ReadTo 

```C++
static inline std::string SR_UTILS_NS::StringUtils::ReadTo (
    std::string str,
    const char c,
    int offset=0
) 
```




<hr>



### function Remove [1/2]

```C++
static std::string SR_UTILS_NS::StringUtils::Remove (
    std::string source,
    uint32_t count
) 
```




<hr>



### function Remove [2/2]

```C++
static std::string SR_UTILS_NS::StringUtils::Remove (
    std::string source,
    uint32_t start,
    uint32_t count
) 
```




<hr>



### function RemoveCharsFromString 

```C++
static inline std::string SR_UTILS_NS::StringUtils::RemoveCharsFromString (
    std::string source,
    const std::string & charsToRemove
) 
```




<hr>



### function ReplaceAll 

```C++
template<typename stringType>
static inline SR_NODISCARD stringType SR_UTILS_NS::StringUtils::ReplaceAll (
    stringType const & original,
    stringType const & from,
    stringType const & to
) noexcept
```




<hr>



### function ReplaceAllRecursive 

```C++
static inline SR_NODISCARD std::string SR_UTILS_NS::StringUtils::ReplaceAllRecursive (
    const std::string & original,
    const std::vector< std::string > & fromList,
    const std::string & to
) noexcept
```




<hr>



### function Resize 

```C++
static inline std::string SR_UTILS_NS::StringUtils::Resize (
    std::string str,
    size_t newSize
) noexcept
```




<hr>



### function Reverse 

```C++
static std::string SR_UTILS_NS::StringUtils::Reverse (
    const std::string & str
) 
```




<hr>



### function Split [1/2]

```C++
static SR_NODISCARD std::vector< std::string > SR_UTILS_NS::StringUtils::Split (
    std::string source,
    const std::string & delimiter
) 
```




<hr>



### function Split [2/2]

```C++
static inline SR_NODISCARD char ** SR_UTILS_NS::StringUtils::Split (
    const char * source,
    char chr,
    unsigned short start,
    unsigned short count_strs
) 
```




<hr>



### function SplitFloats 

```C++
static inline SR_NODISCARD float * SR_UTILS_NS::StringUtils::SplitFloats (
    const char * source,
    char chr,
    unsigned short start,
    unsigned short count_floats
) 
```




<hr>



### function SplitTwo 

```C++
static inline SR_NODISCARD std::pair< std::string, std::string > SR_UTILS_NS::StringUtils::SplitTwo (
    std::string source,
    const std::string & delimiter
) 
```




<hr>



### function SplitView 

```C++
static SR_NODISCARD std::vector< std::string_view > SR_UTILS_NS::StringUtils::SplitView (
    std::string_view source,
    std::string_view delimiter
) 
```




<hr>



### function SplitViewWithEmpty 

```C++
static SR_NODISCARD std::vector< std::string_view > SR_UTILS_NS::StringUtils::SplitViewWithEmpty (
    std::string_view source,
    std::string_view delimiter
) 
```




<hr>



### function Substring [1/3]

```C++
static inline std::string SR_UTILS_NS::StringUtils::Substring (
    const std::string & source,
    char symbol,
    uint32_t offset=0
) 
```




<hr>



### function Substring [2/3]

```C++
static inline std::string SR_UTILS_NS::StringUtils::Substring (
    const std::string & source,
    const char * subStr
) 
```




<hr>



### function Substring [3/3]

```C++
static inline std::string SR_UTILS_NS::StringUtils::Substring (
    const std::string_view & source,
    char symbol,
    uint32_t offset=0
) 
```




<hr>



### function SubstringView [1/2]

```C++
static inline std::string_view SR_UTILS_NS::StringUtils::SubstringView (
    const std::string_view & source,
    char symbol,
    uint32_t offset=0
) 
```




<hr>



### function SubstringView [2/2]

```C++
static inline std::string_view SR_UTILS_NS::StringUtils::SubstringView (
    const std::string_view & source,
    StringAtom substr,
    uint32_t offset=0
) 
```




<hr>



### function Tab 

```C++
static std::string SR_UTILS_NS::StringUtils::Tab (
    std::string code,
    uint32_t count=1
) 
```




<hr>



### function ToKebabCase 

```C++
static std::string SR_UTILS_NS::StringUtils::ToKebabCase (
    std::string_view str
) 
```




<hr>



### function is\_base64 

```C++
static inline bool SR_UTILS_NS::StringUtils::is_base64 (
    unsigned char c
) 
```




<hr>



### function utf8\_to\_wstring 

```C++
static inline SR_NODISCARD std::wstring SR_UTILS_NS::StringUtils::utf8_to_wstring (
    const std::string & str
) 
```




<hr>



### function wstring\_to\_utf8 

```C++
static inline SR_NODISCARD std::string SR_UTILS_NS::StringUtils::wstring_to_utf8 (
    const std::wstring & str
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/StringUtils.h`

