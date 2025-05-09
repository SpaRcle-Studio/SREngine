

# Class SR\_UTILS\_NS::EnumReflector



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)












## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Enumerator**](structSR__UTILS__NS_1_1EnumReflector_1_1Enumerator.md) <br> |










































## Public Functions

| Type | Name |
| ---: | :--- |
|  EnumType | [**At**](#function-at-12) (uint64\_t index) <br> |
|  int64\_t | [**AtAsInt**](#function-atasint-12) (uint64\_t index) <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED std::optional&lt; int64\_t &gt; | [**AtInternal**](#function-atinternal) (uint64\_t index) const<br> |
|  uint64\_t | [**Count**](#function-count-12) () <br> |
|   | [**EnumReflector**](#function-enumreflector) (EnumVariant enumVariant, const Integral \* values, size\_t count, const char \* name, const char \* body) <br> |
|  void | [**ForEach**](#function-foreach-12) (Types::Function&lt; void(EnumType)&gt; func) <br> |
|  EnumType | [**FromString**](#function-fromstring-14) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value) <br> |
|  bool | [**FromString**](#function-fromstring-24) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value, EnumType & result) <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED std::optional&lt; int64\_t &gt; | [**FromStringInternal**](#function-fromstringinternal) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  EnumType | [**FromStringLowerCase**](#function-fromstringlowercase-12) (const std::string & value) <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED std::optional&lt; int64\_t &gt; | [**FromStringLowerCaseInternal**](#function-fromstringlowercaseinternal) (const std::string & value) const<br> |
|  EnumVariant | [**GetEnumVariant**](#function-getenumvariant-12) () <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED EnumVariant | [**GetEnumVariantInternal**](#function-getenumvariantinternal) () const<br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED uint64\_t | [**GetHashNameInternal**](#function-gethashnameinternal) () const<br> |
|  int64\_t | [**GetIndex**](#function-getindex-14) (EnumType value) <br> |
|  int64\_t | [**GetIndex**](#function-getindex-24) (int64\_t value) <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED std::optional&lt; int64\_t &gt; | [**GetIndexInternal**](#function-getindexinternal) (int64\_t value) const<br> |
|  uint64\_t | [**GetIntegralTypeSize**](#function-getintegraltypesize-12) () <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED uint64\_t | [**GetIntegralTypeSizeInternal**](#function-getintegraltypesizeinternal) () const<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname-12) () <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & | [**GetNameInternal**](#function-getnameinternal) () const<br> |
|  const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & | [**GetNames**](#function-getnames-12) () <br> |
|  std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**GetNamesFilter**](#function-getnamesfilter-12) (const std::function&lt; bool(EnumType)&gt; & filter) <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & | [**GetNamesInternal**](#function-getnamesinternal) () const<br> |
|  [**EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md) \* | [**GetReflector**](#function-getreflector-12) () <br> |
|  const std::vector&lt; [**SR\_UTILS\_NS::EnumReflector::Enumerator**](structSR__UTILS__NS_1_1EnumReflector_1_1Enumerator.md) &gt; & | [**GetValues**](#function-getvalues-12) () <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED int64\_t | [**ReadEnumValueFromPointerInternal**](#function-readenumvaluefrompointerinternal) (const void \* pEnum) const<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**ToStringAtom**](#function-tostringatom-14) (EnumType value) <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**ToStringAtom**](#function-tostringatom-24) (int64\_t value) <br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED std::optional&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**ToStringInternal**](#function-tostringinternal) (int64\_t value) const<br> |
|  SR\_NODISCARD SR\_MAYBE\_UNUSED void | [**WriteEnumValueToPointerInternal**](#function-writeenumvaluetopointerinternal) (void \* pEnum, int64\_t value) const<br> |
|   | [**~EnumReflector**](#function-enumreflector) () override<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD EnumType | [**At**](#function-at-22) (uint64\_t index) <br> |
|  SR\_NODISCARD int64\_t | [**AtAsInt**](#function-atasint-22) (uint64\_t index) <br> |
|  SR\_NODISCARD uint64\_t | [**Count**](#function-count-22) () <br> |
|  void | [**ForEach**](#function-foreach-22) ([**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(EnumType)&gt; func) <br> |
|  SR\_NODISCARD EnumType | [**FromString**](#function-fromstring-34) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value) <br> |
|  SR\_NODISCARD bool | [**FromString**](#function-fromstring-44) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value, EnumType & result) <br> |
|  SR\_NODISCARD EnumType | [**FromStringLowerCase**](#function-fromstringlowercase-22) (const std::string & value) <br> |
|  SR\_NODISCARD EnumVariant | [**GetEnumVariant**](#function-getenumvariant-22) () <br> |
|  SR\_NODISCARD int64\_t | [**GetIndex**](#function-getindex-34) (EnumType value) <br> |
|  SR\_NODISCARD int64\_t | [**GetIndex**](#function-getindex-44) (int64\_t value) <br> |
|  SR\_NODISCARD uint64\_t | [**GetIntegralTypeSize**](#function-getintegraltypesize-22) () <br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname-22) () <br> |
|  SR\_NODISCARD const std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & | [**GetNames**](#function-getnames-22) () <br> |
|  SR\_NODISCARD std::vector&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; | [**GetNamesFilter**](#function-getnamesfilter-22) (const std::function&lt; bool(EnumType)&gt; & filter) <br> |
|  SR\_NODISCARD [**EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md) \* | [**GetReflector**](#function-getreflector-22) () <br> |
|  SR\_NODISCARD const std::vector&lt; [**Enumerator**](structSR__UTILS__NS_1_1EnumReflector_1_1Enumerator.md) &gt; & | [**GetValues**](#function-getvalues-22) () <br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**ToStringAtom**](#function-tostringatom-34) (EnumType value) <br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**ToStringAtom**](#function-tostringatom-44) (int64\_t value) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Functions Documentation




### function At [1/2]

```C++
template<typename EnumType>
EnumType SR_UTILS_NS::EnumReflector::At (
    uint64_t index
) 
```




<hr>



### function AtAsInt [1/2]

```C++
template<typename EnumType>
int64_t SR_UTILS_NS::EnumReflector::AtAsInt (
    uint64_t index
) 
```




<hr>



### function AtInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED std::optional< int64_t > SR_UTILS_NS::EnumReflector::AtInternal (
    uint64_t index
) const
```




<hr>



### function Count [1/2]

```C++
template<typename EnumType>
uint64_t SR_UTILS_NS::EnumReflector::Count () 
```




<hr>



### function EnumReflector 

```C++
template<typename Integral>
SR_UTILS_NS::EnumReflector::EnumReflector (
    EnumVariant enumVariant,
    const Integral * values,
    size_t count,
    const char * name,
    const char * body
) 
```




<hr>



### function ForEach [1/2]

```C++
template<typename EnumType>
void SR_UTILS_NS::EnumReflector::ForEach (
    Types::Function< void(EnumType)> func
) 
```




<hr>



### function FromString [1/4]

```C++
template<typename EnumType>
EnumType SR_UTILS_NS::EnumReflector::FromString (
    const SR_UTILS_NS::StringAtom & value
) 
```




<hr>



### function FromString [2/4]

```C++
template<typename EnumType>
bool SR_UTILS_NS::EnumReflector::FromString (
    const SR_UTILS_NS::StringAtom & value,
    EnumType & result
) 
```




<hr>



### function FromStringInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED std::optional< int64_t > SR_UTILS_NS::EnumReflector::FromStringInternal (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function FromStringLowerCase [1/2]

```C++
template<typename EnumType>
EnumType SR_UTILS_NS::EnumReflector::FromStringLowerCase (
    const std::string & value
) 
```




<hr>



### function FromStringLowerCaseInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED std::optional< int64_t > SR_UTILS_NS::EnumReflector::FromStringLowerCaseInternal (
    const std::string & value
) const
```




<hr>



### function GetEnumVariant [1/2]

```C++
template<typename EnumType>
EnumVariant SR_UTILS_NS::EnumReflector::GetEnumVariant () 
```




<hr>



### function GetEnumVariantInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED EnumVariant SR_UTILS_NS::EnumReflector::GetEnumVariantInternal () const
```




<hr>



### function GetHashNameInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED uint64_t SR_UTILS_NS::EnumReflector::GetHashNameInternal () const
```




<hr>



### function GetIndex [1/4]

```C++
template<typename EnumType>
int64_t SR_UTILS_NS::EnumReflector::GetIndex (
    EnumType value
) 
```




<hr>



### function GetIndex [2/4]

```C++
template<typename EnumType>
int64_t SR_UTILS_NS::EnumReflector::GetIndex (
    int64_t value
) 
```




<hr>



### function GetIndexInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED std::optional< int64_t > SR_UTILS_NS::EnumReflector::GetIndexInternal (
    int64_t value
) const
```




<hr>



### function GetIntegralTypeSize [1/2]

```C++
template<typename EnumType>
uint64_t SR_UTILS_NS::EnumReflector::GetIntegralTypeSize () 
```




<hr>



### function GetIntegralTypeSizeInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED uint64_t SR_UTILS_NS::EnumReflector::GetIntegralTypeSizeInternal () const
```




<hr>



### function GetName [1/2]

```C++
template<typename EnumType>
SR_UTILS_NS::StringAtom SR_UTILS_NS::EnumReflector::GetName () 
```




<hr>



### function GetNameInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED const SR_UTILS_NS::StringAtom & SR_UTILS_NS::EnumReflector::GetNameInternal () const
```




<hr>



### function GetNames [1/2]

```C++
template<typename EnumType>
const std::vector< SR_UTILS_NS::StringAtom > & SR_UTILS_NS::EnumReflector::GetNames () 
```




<hr>



### function GetNamesFilter [1/2]

```C++
template<typename EnumType>
std::vector< SR_UTILS_NS::StringAtom > SR_UTILS_NS::EnumReflector::GetNamesFilter (
    const std::function< bool(EnumType)> & filter
) 
```




<hr>



### function GetNamesInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED const std::vector< SR_UTILS_NS::StringAtom > & SR_UTILS_NS::EnumReflector::GetNamesInternal () const
```




<hr>



### function GetReflector [1/2]

```C++
template<typename EnumType>
EnumReflector * SR_UTILS_NS::EnumReflector::GetReflector () 
```




<hr>



### function GetValues [1/2]

```C++
template<typename EnumType>
const std::vector< SR_UTILS_NS::EnumReflector::Enumerator > & SR_UTILS_NS::EnumReflector::GetValues () 
```




<hr>



### function ReadEnumValueFromPointerInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED int64_t SR_UTILS_NS::EnumReflector::ReadEnumValueFromPointerInternal (
    const void * pEnum
) const
```




<hr>



### function ToStringAtom [1/4]

```C++
template<typename EnumType>
SR_UTILS_NS::StringAtom SR_UTILS_NS::EnumReflector::ToStringAtom (
    EnumType value
) 
```




<hr>



### function ToStringAtom [2/4]

```C++
template<typename EnumType>
SR_UTILS_NS::StringAtom SR_UTILS_NS::EnumReflector::ToStringAtom (
    int64_t value
) 
```




<hr>



### function ToStringInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED std::optional< SR_UTILS_NS::StringAtom > SR_UTILS_NS::EnumReflector::ToStringInternal (
    int64_t value
) const
```




<hr>



### function WriteEnumValueToPointerInternal 

```C++
SR_NODISCARD SR_MAYBE_UNUSED void SR_UTILS_NS::EnumReflector::WriteEnumValueToPointerInternal (
    void * pEnum,
    int64_t value
) const
```




<hr>



### function ~EnumReflector 

```C++
SR_UTILS_NS::EnumReflector::~EnumReflector () override
```




<hr>
## Public Static Functions Documentation




### function At [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD EnumType SR_UTILS_NS::EnumReflector::At (
    uint64_t index
) 
```




<hr>



### function AtAsInt [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD int64_t SR_UTILS_NS::EnumReflector::AtAsInt (
    uint64_t index
) 
```




<hr>



### function Count [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD uint64_t SR_UTILS_NS::EnumReflector::Count () 
```




<hr>



### function ForEach [2/2]

```C++
template<typename EnumType>
static void SR_UTILS_NS::EnumReflector::ForEach (
    SR_HTYPES_NS::Function < void(EnumType)> func
) 
```




<hr>



### function FromString [3/4]

```C++
template<typename EnumType>
static SR_NODISCARD EnumType SR_UTILS_NS::EnumReflector::FromString (
    const SR_UTILS_NS::StringAtom & value
) 
```




<hr>



### function FromString [4/4]

```C++
template<typename EnumType>
static SR_NODISCARD bool SR_UTILS_NS::EnumReflector::FromString (
    const SR_UTILS_NS::StringAtom & value,
    EnumType & result
) 
```




<hr>



### function FromStringLowerCase [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD EnumType SR_UTILS_NS::EnumReflector::FromStringLowerCase (
    const std::string & value
) 
```




<hr>



### function GetEnumVariant [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD EnumVariant SR_UTILS_NS::EnumReflector::GetEnumVariant () 
```




<hr>



### function GetIndex [3/4]

```C++
template<typename EnumType>
static SR_NODISCARD int64_t SR_UTILS_NS::EnumReflector::GetIndex (
    EnumType value
) 
```




<hr>



### function GetIndex [4/4]

```C++
template<typename EnumType>
static SR_NODISCARD int64_t SR_UTILS_NS::EnumReflector::GetIndex (
    int64_t value
) 
```




<hr>



### function GetIntegralTypeSize [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD uint64_t SR_UTILS_NS::EnumReflector::GetIntegralTypeSize () 
```




<hr>



### function GetName [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::EnumReflector::GetName () 
```




<hr>



### function GetNames [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD const std::vector< SR_UTILS_NS::StringAtom > & SR_UTILS_NS::EnumReflector::GetNames () 
```




<hr>



### function GetNamesFilter [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD std::vector< SR_UTILS_NS::StringAtom > SR_UTILS_NS::EnumReflector::GetNamesFilter (
    const std::function< bool(EnumType)> & filter
) 
```




<hr>



### function GetReflector [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD EnumReflector * SR_UTILS_NS::EnumReflector::GetReflector () 
```




<hr>



### function GetValues [2/2]

```C++
template<typename EnumType>
static SR_NODISCARD const std::vector< Enumerator > & SR_UTILS_NS::EnumReflector::GetValues () 
```




<hr>



### function ToStringAtom [3/4]

```C++
template<typename EnumType>
static SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::EnumReflector::ToStringAtom (
    EnumType value
) 
```




<hr>



### function ToStringAtom [4/4]

```C++
template<typename EnumType>
static SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::EnumReflector::ToStringAtom (
    int64_t value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/EnumReflector.h`

