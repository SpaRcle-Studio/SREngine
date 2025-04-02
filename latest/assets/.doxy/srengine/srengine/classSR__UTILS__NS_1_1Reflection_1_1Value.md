

# Class SR\_UTILS\_NS::Reflection::Value



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Reflection**](namespaceSR__UTILS__NS_1_1Reflection.md) **>** [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md)



[More...](#detailed-description)

* `#include <Value.h>`





































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**ValueSequenceContainer**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainer.md) | [**AsSequenceContainer**](#function-assequencecontainer-12) () <br> |
|  SR\_NODISCARD [**ValueSequenceContainer**](classSR__UTILS__NS_1_1Reflection_1_1ValueSequenceContainer.md) | [**AsSequenceContainer**](#function-assequencecontainer-22) () const<br> |
|  SR\_NODISCARD [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**Copy**](#function-copy) () const<br> |
|  SR\_NODISCARD void \* | [**Data**](#function-data-12) () <br> |
|  SR\_NODISCARD const void \* | [**Data**](#function-data-22) () const<br> |
|  [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & | [**Detach**](#function-detach) () <br> |
|  [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & | [**DetachIfConst**](#function-detachifconst) () <br> |
|  SR\_NODISCARD std::string\_view | [**GetEnumType**](#function-getenumtype) () const<br> |
|  SR\_NODISCARD [**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**GetSRClass**](#function-getsrclass) () const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::SharedPtrBase**](classSR__HTYPES__NS_1_1SharedPtrBase.md) \* | [**GetSharedPtrBase**](#function-getsharedptrbase) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetSharedPtrType**](#function-getsharedptrtype) () const<br> |
|  SR\_NODISCARD std::string\_view | [**GetTypeName**](#function-gettypename) () const<br> |
|  SR\_NODISCARD bool | [**IsArithmetic**](#function-isarithmetic) () const<br> |
|  SR\_NODISCARD bool | [**IsAssociativeContainer**](#function-isassociativecontainer) () const<br> |
|  SR\_NODISCARD bool | [**IsBitMap**](#function-isbitmap) () const<br> |
|  SR\_NODISCARD bool | [**IsBool**](#function-isbool) () const<br> |
|  SR\_NODISCARD bool | [**IsClass**](#function-isclass) () const<br> |
|  SR\_NODISCARD bool | [**IsConst**](#function-isconst) () const<br> |
|  SR\_NODISCARD bool | [**IsEnum**](#function-isenum) () const<br> |
|  SR\_NODISCARD bool | [**IsIntegral**](#function-isintegral) () const<br> |
|  SR\_NODISCARD bool | [**IsMathSize**](#function-ismathsize) () const<br> |
|  SR\_NODISCARD bool | [**IsMathVector**](#function-ismathvector) () const<br> |
|  SR\_NODISCARD bool | [**IsPath**](#function-ispath) () const<br> |
|  SR\_NODISCARD bool | [**IsPointer**](#function-ispointer) () const<br> |
|  SR\_NODISCARD bool | [**IsRef**](#function-isref) () const<br> |
|  SR\_NODISCARD bool | [**IsSequenceContainer**](#function-issequencecontainer) () const<br> |
|  SR\_NODISCARD bool | [**IsSigned**](#function-issigned) () const<br> |
|  SR\_NODISCARD bool | [**IsSmartPtr**](#function-issmartptr) () const<br> |
|  SR\_NODISCARD bool | [**IsString**](#function-isstring) () const<br> |
|  SR\_NODISCARD bool | [**IsStringAtom**](#function-isstringatom) () const<br> |
|  SR\_NODISCARD bool | [**IsStringView**](#function-isstringview) () const<br> |
|  SR\_NODISCARD bool | [**IsTemplate**](#function-istemplate) () const<br> |
|  SR\_NODISCARD bool | [**IsUnicodeString**](#function-isunicodestring) () const<br> |
|  SR\_NODISCARD [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**Ref**](#function-ref) () <br> |
|  SR\_NODISCARD uint64\_t | [**SizeOf**](#function-sizeof) () const<br> |
|  const T \* | [**TryCast**](#function-trycast-12) () const<br> |
|  T \* | [**TryCast**](#function-trycast-22) () <br> |
|   | [**Value**](#function-value-23) () = default<br> |
|   | [**Value**](#function-value-33) (const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & other) <br> |
|  SR\_NODISCARD | [**operator bool**](#function-operator-bool) () noexcept const<br> |
|  [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & | [**operator=**](#function-operator) (const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & other) noexcept<br> |
|  [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & | [**operator=**](#function-operator_1) ([**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) && other) noexcept<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**Create**](#function-create) (T && value) <br> |
|  [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**CreateCRef**](#function-createcref) (const T & value) <br> |
|  [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**CreateRef**](#function-createref) (T & value) <br> |


























## Detailed Description



 


    
## Public Functions Documentation




### function AsSequenceContainer [1/2]

```C++
SR_NODISCARD ValueSequenceContainer SR_UTILS_NS::Reflection::Value::AsSequenceContainer () 
```




<hr>



### function AsSequenceContainer [2/2]

```C++
SR_NODISCARD ValueSequenceContainer SR_UTILS_NS::Reflection::Value::AsSequenceContainer () const
```




<hr>



### function Copy 

```C++
SR_NODISCARD Value SR_UTILS_NS::Reflection::Value::Copy () const
```




<hr>



### function Data [1/2]

```C++
SR_NODISCARD void * SR_UTILS_NS::Reflection::Value::Data () 
```




<hr>



### function Data [2/2]

```C++
SR_NODISCARD const void * SR_UTILS_NS::Reflection::Value::Data () const
```




<hr>



### function Detach 

```C++
Value & SR_UTILS_NS::Reflection::Value::Detach () 
```




<hr>



### function DetachIfConst 

```C++
Value & SR_UTILS_NS::Reflection::Value::DetachIfConst () 
```




<hr>



### function GetEnumType 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Reflection::Value::GetEnumType () const
```




<hr>



### function GetSRClass 

```C++
SR_NODISCARD SRClass * SR_UTILS_NS::Reflection::Value::GetSRClass () const
```




<hr>



### function GetSharedPtrBase 

```C++
SR_NODISCARD SR_HTYPES_NS::SharedPtrBase * SR_UTILS_NS::Reflection::Value::GetSharedPtrBase () const
```




<hr>



### function GetSharedPtrType 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Reflection::Value::GetSharedPtrType () const
```




<hr>



### function GetTypeName 

```C++
SR_NODISCARD std::string_view SR_UTILS_NS::Reflection::Value::GetTypeName () const
```




<hr>



### function IsArithmetic 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsArithmetic () const
```




<hr>



### function IsAssociativeContainer 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsAssociativeContainer () const
```




<hr>



### function IsBitMap 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsBitMap () const
```




<hr>



### function IsBool 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsBool () const
```




<hr>



### function IsClass 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsClass () const
```




<hr>



### function IsConst 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsConst () const
```




<hr>



### function IsEnum 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsEnum () const
```




<hr>



### function IsIntegral 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsIntegral () const
```




<hr>



### function IsMathSize 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsMathSize () const
```




<hr>



### function IsMathVector 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsMathVector () const
```




<hr>



### function IsPath 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsPath () const
```




<hr>



### function IsPointer 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsPointer () const
```




<hr>



### function IsRef 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsRef () const
```




<hr>



### function IsSequenceContainer 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsSequenceContainer () const
```




<hr>



### function IsSigned 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsSigned () const
```




<hr>



### function IsSmartPtr 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsSmartPtr () const
```




<hr>



### function IsString 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsString () const
```




<hr>



### function IsStringAtom 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsStringAtom () const
```




<hr>



### function IsStringView 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsStringView () const
```




<hr>



### function IsTemplate 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsTemplate () const
```




<hr>



### function IsUnicodeString 

```C++
SR_NODISCARD bool SR_UTILS_NS::Reflection::Value::IsUnicodeString () const
```




<hr>



### function Ref 

```C++
SR_NODISCARD Value SR_UTILS_NS::Reflection::Value::Ref () 
```




<hr>



### function SizeOf 

```C++
SR_NODISCARD uint64_t SR_UTILS_NS::Reflection::Value::SizeOf () const
```




<hr>



### function TryCast [1/2]

```C++
template<typename T>
inline const T * SR_UTILS_NS::Reflection::Value::TryCast () const
```




<hr>



### function TryCast [2/2]

```C++
template<typename T>
inline T * SR_UTILS_NS::Reflection::Value::TryCast () 
```




<hr>



### function Value [2/3]

```C++
SR_UTILS_NS::Reflection::Value::Value () = default
```




<hr>



### function Value [3/3]

```C++
inline SR_UTILS_NS::Reflection::Value::Value (
    const Value & other
) 
```




<hr>



### function operator bool 

```C++
SR_NODISCARD SR_UTILS_NS::Reflection::Value::operator bool () noexcept const
```




<hr>



### function operator= 

```C++
inline Value & SR_UTILS_NS::Reflection::Value::operator= (
    const Value & other
) noexcept
```




<hr>



### function operator= 

```C++
inline Value & SR_UTILS_NS::Reflection::Value::operator= (
    Value && other
) noexcept
```




<hr>
## Public Static Functions Documentation




### function Create 

```C++
template<typename T>
static Value SR_UTILS_NS::Reflection::Value::Create (
    T && value
) 
```




<hr>



### function CreateCRef 

```C++
template<typename T>
static Value SR_UTILS_NS::Reflection::Value::CreateCRef (
    const T & value
) 
```




<hr>



### function CreateRef 

```C++
template<typename T>
static Value SR_UTILS_NS::Reflection::Value::CreateRef (
    T & value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Reflection/Value.h`

