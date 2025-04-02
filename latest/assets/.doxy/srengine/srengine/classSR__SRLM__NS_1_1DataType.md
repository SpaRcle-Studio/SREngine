

# Class SR\_SRLM\_NS::DataType



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**DataType**](classSR__SRLM__NS_1_1DataType.md)



[More...](#detailed-description)

* `#include <DataType.h>`



Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_SRLM\_NS::DataTypeArray](classSR__SRLM__NS_1_1DataTypeArray.md),  [SR\_SRLM\_NS::DataTypeBool](classSR__SRLM__NS_1_1DataTypeBool.md),  [SR\_SRLM\_NS::DataTypeDouble](classSR__SRLM__NS_1_1DataTypeDouble.md),  [SR\_SRLM\_NS::DataTypeFloat](classSR__SRLM__NS_1_1DataTypeFloat.md),  [SR\_SRLM\_NS::DataTypeInt16](classSR__SRLM__NS_1_1DataTypeInt16.md),  [SR\_SRLM\_NS::DataTypeInt32](classSR__SRLM__NS_1_1DataTypeInt32.md),  [SR\_SRLM\_NS::DataTypeInt64](classSR__SRLM__NS_1_1DataTypeInt64.md),  [SR\_SRLM\_NS::DataTypeInt8](classSR__SRLM__NS_1_1DataTypeInt8.md),  [SR\_SRLM\_NS::DataTypeNone](classSR__SRLM__NS_1_1DataTypeNone.md),  [SR\_SRLM\_NS::DataTypeString](classSR__SRLM__NS_1_1DataTypeString.md),  [SR\_SRLM\_NS::DataTypeStruct](classSR__SRLM__NS_1_1DataTypeStruct.md),  [SR\_SRLM\_NS::DataTypeUInt16](classSR__SRLM__NS_1_1DataTypeUInt16.md),  [SR\_SRLM\_NS::DataTypeUInt32](classSR__SRLM__NS_1_1DataTypeUInt32.md),  [SR\_SRLM\_NS::DataTypeUInt64](classSR__SRLM__NS_1_1DataTypeUInt64.md),  [SR\_SRLM\_NS::DataTypeUInt8](classSR__SRLM__NS_1_1DataTypeUInt8.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Hash**](#typedef-hash)  <br> |
| typedef uint64\_t | [**Meta**](#typedef-meta)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Copy**](#function-copy) () const = 0<br> |
| virtual void | [**CopyTo**](#function-copyto) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData) const = 0<br> |
|  SR\_NODISCARD bool \* | [**GetBool**](#function-getbool) () const<br> |
| virtual SR\_NODISCARD DataTypeClass | [**GetClass**](#function-getclass) () noexcept const = 0<br> |
|  SR\_NODISCARD double\_t \* | [**GetDouble**](#function-getdouble) () const<br> |
|  SR\_NODISCARD int64\_t \* | [**GetEnum**](#function-getenum) () const<br> |
|  SR\_NODISCARD float\_t \* | [**GetFloat**](#function-getfloat) () const<br> |
| virtual SR\_NODISCARD Hash | [**GetHashName**](#function-gethashname) () noexcept const = 0<br> |
|  SR\_NODISCARD int16\_t \* | [**GetInt16**](#function-getint16) () const<br> |
|  SR\_NODISCARD int32\_t \* | [**GetInt32**](#function-getint32) () const<br> |
|  SR\_NODISCARD int64\_t \* | [**GetInt64**](#function-getint64) () const<br> |
|  SR\_NODISCARD int8\_t \* | [**GetInt8**](#function-getint8) () const<br> |
| virtual SR\_NODISCARD Meta | [**GetMeta**](#function-getmeta) () noexcept const = 0<br> |
| virtual SR\_NODISCARD std::vector&lt; [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* &gt; | [**GetMetaData**](#function-getmetadata) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetName**](#function-getname) () noexcept const = 0<br> |
| virtual SR\_NODISCARD void \* | [**GetRawValue**](#function-getrawvalue) () noexcept const<br> |
|  SR\_NODISCARD std::string \* | [**GetString**](#function-getstring) () const<br> |
|  SR\_NODISCARD uint16\_t \* | [**GetUInt16**](#function-getuint16) () const<br> |
|  SR\_NODISCARD uint32\_t \* | [**GetUInt32**](#function-getuint32) () const<br> |
|  SR\_NODISCARD uint64\_t \* | [**GetUInt64**](#function-getuint64) () const<br> |
|  SR\_NODISCARD uint8\_t \* | [**GetUInt8**](#function-getuint8) () const<br> |
| virtual void | [**Reset**](#function-reset) () = 0<br> |
|  void | [**SaveXml**](#function-savexml) (SR\_XML\_NS::Node & xmlNode) <br> |
|  [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**SetCustomValue**](#function-setcustomvalue) (const T & value) <br> |
| virtual [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**SetRawValue**](#function-setrawvalue) (void \* pValue) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**LoadXml**](#function-loadxml) (const SR\_XML\_NS::Node & xmlNode) <br> |














































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Detailed Description



 


    
## Public Types Documentation




### typedef Hash 

```C++
using SR_SRLM_NS::DataType::Hash =  uint64_t;
```




<hr>



### typedef Meta 

```C++
using SR_SRLM_NS::DataType::Meta =  uint64_t;
```




<hr>
## Public Functions Documentation




### function Copy 

```C++
virtual SR_NODISCARD DataType * SR_SRLM_NS::DataType::Copy () const = 0
```




<hr>



### function CopyTo 

```C++
virtual void SR_SRLM_NS::DataType::CopyTo (
    DataType * pData
) const = 0
```




<hr>



### function GetBool 

```C++
inline SR_NODISCARD bool * SR_SRLM_NS::DataType::GetBool () const
```




<hr>



### function GetClass 

```C++
virtual SR_NODISCARD DataTypeClass SR_SRLM_NS::DataType::GetClass () noexcept const = 0
```




<hr>



### function GetDouble 

```C++
inline SR_NODISCARD double_t * SR_SRLM_NS::DataType::GetDouble () const
```




<hr>



### function GetEnum 

```C++
inline SR_NODISCARD int64_t * SR_SRLM_NS::DataType::GetEnum () const
```




<hr>



### function GetFloat 

```C++
inline SR_NODISCARD float_t * SR_SRLM_NS::DataType::GetFloat () const
```




<hr>



### function GetHashName 

```C++
virtual SR_NODISCARD Hash SR_SRLM_NS::DataType::GetHashName () noexcept const = 0
```




<hr>



### function GetInt16 

```C++
inline SR_NODISCARD int16_t * SR_SRLM_NS::DataType::GetInt16 () const
```




<hr>



### function GetInt32 

```C++
inline SR_NODISCARD int32_t * SR_SRLM_NS::DataType::GetInt32 () const
```




<hr>



### function GetInt64 

```C++
inline SR_NODISCARD int64_t * SR_SRLM_NS::DataType::GetInt64 () const
```




<hr>



### function GetInt8 

```C++
inline SR_NODISCARD int8_t * SR_SRLM_NS::DataType::GetInt8 () const
```




<hr>



### function GetMeta 

```C++
virtual SR_NODISCARD Meta SR_SRLM_NS::DataType::GetMeta () noexcept const = 0
```




<hr>



### function GetMetaData 

```C++
inline virtual SR_NODISCARD std::vector< DataType * > SR_SRLM_NS::DataType::GetMetaData () const
```




<hr>



### function GetName 

```C++
virtual SR_NODISCARD std::string SR_SRLM_NS::DataType::GetName () noexcept const = 0
```




<hr>



### function GetRawValue 

```C++
inline virtual SR_NODISCARD void * SR_SRLM_NS::DataType::GetRawValue () noexcept const
```




<hr>



### function GetString 

```C++
inline SR_NODISCARD std::string * SR_SRLM_NS::DataType::GetString () const
```




<hr>



### function GetUInt16 

```C++
inline SR_NODISCARD uint16_t * SR_SRLM_NS::DataType::GetUInt16 () const
```




<hr>



### function GetUInt32 

```C++
inline SR_NODISCARD uint32_t * SR_SRLM_NS::DataType::GetUInt32 () const
```




<hr>



### function GetUInt64 

```C++
inline SR_NODISCARD uint64_t * SR_SRLM_NS::DataType::GetUInt64 () const
```




<hr>



### function GetUInt8 

```C++
inline SR_NODISCARD uint8_t * SR_SRLM_NS::DataType::GetUInt8 () const
```




<hr>



### function Reset 

```C++
virtual void SR_SRLM_NS::DataType::Reset () = 0
```




<hr>



### function SaveXml 

```C++
void SR_SRLM_NS::DataType::SaveXml (
    SR_XML_NS::Node & xmlNode
) 
```




<hr>



### function SetCustomValue 

```C++
template<typename T>
inline DataType * SR_SRLM_NS::DataType::SetCustomValue (
    const T & value
) 
```




<hr>



### function SetRawValue 

```C++
inline virtual DataType * SR_SRLM_NS::DataType::SetRawValue (
    void * pValue
) 
```




<hr>
## Public Static Functions Documentation




### function LoadXml 

```C++
static DataType * SR_SRLM_NS::DataType::LoadXml (
    const SR_XML_NS::Node & xmlNode
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/SRLM/DataType.h`

