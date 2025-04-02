

# Class SR\_SRLM\_NS::DataTypeEnum



[**ClassList**](annotated.md) **>** [**SR\_SRLM\_NS**](namespaceSR__SRLM__NS.md) **>** [**DataTypeEnum**](classSR__SRLM__NS_1_1DataTypeEnum.md)



[More...](#detailed-description)

* `#include <DataType.h>`



Inherits the following classes: [SR\_SRLM\_NS::DataTypeInt64](classSR__SRLM__NS_1_1DataTypeInt64.md)


Inherited by the following classes: [SR\_SRLM\_NS::DataTypeFlow](classSR__SRLM__NS_1_1DataTypeFlow.md)
















## Public Types inherited from SR_SRLM_NS::DataType

See [SR\_SRLM\_NS::DataType](classSR__SRLM__NS_1_1DataType.md)

| Type | Name |
| ---: | :--- |
| typedef uint64\_t | [**Hash**](classSR__SRLM__NS_1_1DataType.md#typedef-hash)  <br> |
| typedef uint64\_t | [**Meta**](classSR__SRLM__NS_1_1DataType.md#typedef-meta)  <br> |












































































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD [**DataType**](classSR__SRLM__NS_1_1DataType.md) \* | [**Copy**](#function-copy) () override const<br> |
|   | [**DataTypeEnum**](#function-datatypeenum-13) () = default<br> |
|   | [**DataTypeEnum**](#function-datatypeenum-23) (int64\_t value, EnumReflector \* pReflector) <br> |
|   | [**DataTypeEnum**](#function-datatypeenum-33) (EnumReflector \* pReflector) <br> |
| virtual SR\_NODISCARD Hash | [**GetHashName**](#function-gethashname) () noexcept override const<br> |
| virtual SR\_NODISCARD std::string | [**GetName**](#function-getname) () noexcept override const<br> |
|  SR\_NODISCARD EnumReflector \* | [**GetReflector**](#function-getreflector) () const<br> |
|  void | [**SetReflector**](#function-setreflector) (EnumReflector \* pReflector) <br> |




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




### function Copy 

```C++
inline virtual SR_NODISCARD DataType * SR_SRLM_NS::DataTypeEnum::Copy () override const
```



Implements [*SR\_SRLM\_NS::DataType::Copy*](classSR__SRLM__NS_1_1DataType.md#function-copy)


<hr>



### function DataTypeEnum [1/3]

```C++
SR_SRLM_NS::DataTypeEnum::DataTypeEnum () = default
```




<hr>



### function DataTypeEnum [2/3]

```C++
inline explicit SR_SRLM_NS::DataTypeEnum::DataTypeEnum (
    int64_t value,
    EnumReflector * pReflector
) 
```




<hr>



### function DataTypeEnum [3/3]

```C++
inline explicit SR_SRLM_NS::DataTypeEnum::DataTypeEnum (
    EnumReflector * pReflector
) 
```




<hr>



### function GetHashName 

```C++
virtual SR_NODISCARD Hash SR_SRLM_NS::DataTypeEnum::GetHashName () noexcept override const
```



Implements [*SR\_SRLM\_NS::DataType::GetHashName*](classSR__SRLM__NS_1_1DataType.md#function-gethashname)


<hr>



### function GetName 

```C++
virtual SR_NODISCARD std::string SR_SRLM_NS::DataTypeEnum::GetName () noexcept override const
```



Implements [*SR\_SRLM\_NS::DataType::GetName*](classSR__SRLM__NS_1_1DataType.md#function-getname)


<hr>



### function GetReflector 

```C++
inline SR_NODISCARD EnumReflector * SR_SRLM_NS::DataTypeEnum::GetReflector () const
```




<hr>



### function SetReflector 

```C++
inline void SR_SRLM_NS::DataTypeEnum::SetReflector (
    EnumReflector * pReflector
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/SRLM/DataType.h`

