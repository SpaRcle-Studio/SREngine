

# Class SR\_SRLM\_NS::DataTypeStruct



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**DataTypeStruct**](classSR__SRLM__NS_1_1DataTypeStruct.md)



[More...](#detailed-description)

* `#include <DataType.h>`



Inherits the following classes: [SR\_SRLM\_NS::DataType](classSR__SRLM__NS_1_1DataType.md)
















## Public Types inherited from SR_SRLM_NS::DataType

See [SR\_SRLM\_NS::DataType](classSR__SRLM__NS_1_1DataType.md)

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Hash**](classSR__SRLM__NS_1_1DataType.md#typedef-hash)  <br> |
| typedef uint64\_t | [**Meta**](classSR__SRLM__NS_1_1DataType.md#typedef-meta)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**AddVariable**](#function-addvariable-12) (Hash name, [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData) <br> |
|  void | [**AddVariable**](#function-addvariable-22) (const std::string & name, [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData) <br> |
| virtual SR\_NODISCARD [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Copy**](#function-copy) () override const<br> |
| virtual void | [**CopyTo**](#function-copyto) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData) override const<br> |
|   | [**DataTypeStruct**](#function-datatypestruct-12) () = default<br> |
|   | [**DataTypeStruct**](#function-datatypestruct-22) (Hash name) <br> |
| virtual SR\_NODISCARD std::vector&lt; [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* &gt; | [**GetMetaData**](#function-getmetadata) () override const<br> |
|  SR\_NODISCARD Hash | [**GetStructName**](#function-getstructname) () const<br> |
|  SR\_NODISCARD const std::map&lt; Hash, [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* &gt; & | [**GetVariables**](#function-getvariables) () const<br> |
| virtual void | [**Reset**](#function-reset) () override<br> |
|  void | [**SetStructHashName**](#function-setstructhashname) (Hash hashName) <br> |
|   | [**~DataTypeStruct**](#function-datatypestruct) () override<br> |


## Public Functions inherited from SR_SRLM_NS::DataType

See [SR\_SRLM\_NS::DataType](classSR__SRLM__NS_1_1DataType.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Copy**](classSR__SRLM__NS_1_1DataType.md#function-copy) () const = 0<br> |
| virtual void | [**CopyTo**](classSR__SRLM__NS_1_1DataType.md#function-copyto) ([**DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData) const = 0<br> |
|  SR\_NODISCARD bool \* | [**GetBool**](classSR__SRLM__NS_1_1DataType.md#function-getbool) () const<br> |
| virtual SR\_NODISCARD DataTypeClass | [**GetClass**](classSR__SRLM__NS_1_1DataType.md#function-getclass) () noexcept const = 0<br> |
|  SR\_NODISCARD double\_t \* | [**GetDouble**](classSR__SRLM__NS_1_1DataType.md#function-getdouble) () const<br> |
|  SR\_NODISCARD int64\_t \* | [**GetEnum**](classSR__SRLM__NS_1_1DataType.md#function-getenum) () const<br> |
|  SR\_NODISCARD float\_t \* | [**GetFloat**](classSR__SRLM__NS_1_1DataType.md#function-getfloat) () const<br> |
| virtual SR\_NODISCARD Hash | [**GetHashName**](classSR__SRLM__NS_1_1DataType.md#function-gethashname) () noexcept const = 0<br> |
|  SR\_NODISCARD int16\_t \* | [**GetInt16**](classSR__SRLM__NS_1_1DataType.md#function-getint16) () const<br> |
|  SR\_NODISCARD int32\_t \* | [**GetInt32**](classSR__SRLM__NS_1_1DataType.md#function-getint32) () const<br> |
|  SR\_NODISCARD int64\_t \* | [**GetInt64**](classSR__SRLM__NS_1_1DataType.md#function-getint64) () const<br> |
|  SR\_NODISCARD int8\_t \* | [**GetInt8**](classSR__SRLM__NS_1_1DataType.md#function-getint8) () const<br> |
| virtual SR\_NODISCARD Meta | [**GetMeta**](classSR__SRLM__NS_1_1DataType.md#function-getmeta) () noexcept const = 0<br> |
| virtual SR\_NODISCARD std::vector&lt; [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* &gt; | [**GetMetaData**](classSR__SRLM__NS_1_1DataType.md#function-getmetadata) () const<br> |
| virtual SR\_NODISCARD std::string | [**GetName**](classSR__SRLM__NS_1_1DataType.md#function-getname) () noexcept const = 0<br> |
| virtual SR\_NODISCARD void \* | [**GetRawValue**](classSR__SRLM__NS_1_1DataType.md#function-getrawvalue) () noexcept const<br> |
|  SR\_NODISCARD std::string \* | [**GetString**](classSR__SRLM__NS_1_1DataType.md#function-getstring) () const<br> |
|  SR\_NODISCARD uint16\_t \* | [**GetUInt16**](classSR__SRLM__NS_1_1DataType.md#function-getuint16) () const<br> |
|  SR\_NODISCARD uint32\_t \* | [**GetUInt32**](classSR__SRLM__NS_1_1DataType.md#function-getuint32) () const<br> |
|  SR\_NODISCARD uint64\_t \* | [**GetUInt64**](classSR__SRLM__NS_1_1DataType.md#function-getuint64) () const<br> |
|  SR\_NODISCARD uint8\_t \* | [**GetUInt8**](classSR__SRLM__NS_1_1DataType.md#function-getuint8) () const<br> |
| virtual void | [**Reset**](classSR__SRLM__NS_1_1DataType.md#function-reset) () = 0<br> |
|  void | [**SaveXml**](classSR__SRLM__NS_1_1DataType.md#function-savexml) (SR\_XML\_NS::Node & xmlNode) <br> |
|  [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**SetCustomValue**](classSR__SRLM__NS_1_1DataType.md#function-setcustomvalue) (const T & value) <br> |
| virtual [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**SetRawValue**](classSR__SRLM__NS_1_1DataType.md#function-setrawvalue) (void \* pValue) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |




## Public Static Functions inherited from SR_SRLM_NS::DataType

See [SR\_SRLM\_NS::DataType](classSR__SRLM__NS_1_1DataType.md)

| Type | Name |
| ---: | :--- |
|  [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**LoadXml**](classSR__SRLM__NS_1_1DataType.md#function-loadxml) (const SR\_XML\_NS::Node & xmlNode) <br> |




































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Detailed Description



 


    
## Public Functions Documentation




### function AddVariable [1/2]

```C++
void SR_SRLM_NS::DataTypeStruct::AddVariable (
    Hash name,
    DataType * pData
) 
```




<hr>



### function AddVariable [2/2]

```C++
void SR_SRLM_NS::DataTypeStruct::AddVariable (
    const std::string & name,
    DataType * pData
) 
```




<hr>



### function Copy 

```C++
virtual SR_NODISCARD DataType * SR_SRLM_NS::DataTypeStruct::Copy () override const
```



Implements [*SR\_SRLM\_NS::DataType::Copy*](classSR__SRLM__NS_1_1DataType.md#function-copy)


<hr>



### function CopyTo 

```C++
virtual void SR_SRLM_NS::DataTypeStruct::CopyTo (
    DataType * pData
) override const
```



Implements [*SR\_SRLM\_NS::DataType::CopyTo*](classSR__SRLM__NS_1_1DataType.md#function-copyto)


<hr>



### function DataTypeStruct [1/2]

```C++
SR_SRLM_NS::DataTypeStruct::DataTypeStruct () = default
```




<hr>



### function DataTypeStruct [2/2]

```C++
inline explicit SR_SRLM_NS::DataTypeStruct::DataTypeStruct (
    Hash name
) 
```




<hr>



### function GetMetaData 

```C++
virtual SR_NODISCARD std::vector< DataType * > SR_SRLM_NS::DataTypeStruct::GetMetaData () override const
```



Implements [*SR\_SRLM\_NS::DataType::GetMetaData*](classSR__SRLM__NS_1_1DataType.md#function-getmetadata)


<hr>



### function GetStructName 

```C++
inline SR_NODISCARD Hash SR_SRLM_NS::DataTypeStruct::GetStructName () const
```




<hr>



### function GetVariables 

```C++
inline SR_NODISCARD const std::map< Hash, DataType * > & SR_SRLM_NS::DataTypeStruct::GetVariables () const
```




<hr>



### function Reset 

```C++
virtual void SR_SRLM_NS::DataTypeStruct::Reset () override
```



Implements [*SR\_SRLM\_NS::DataType::Reset*](classSR__SRLM__NS_1_1DataType.md#function-reset)


<hr>



### function SetStructHashName 

```C++
inline void SR_SRLM_NS::DataTypeStruct::SetStructHashName (
    Hash hashName
) 
```




<hr>



### function ~DataTypeStruct 

```C++
SR_SRLM_NS::DataTypeStruct::~DataTypeStruct () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/SRLM/DataType.h`

