

# Class SR\_UTILS\_NS::StandardProperty



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md)



_-------------------------------------_  __[_**StandardProperty**_](classSR__UTILS__NS_1_1StandardProperty.md) _---------------------------------------------------_ __

* `#include <StandardProperty.h>`



Inherits the following classes: [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)
















## Public Types inherited from SR_UTILS_NS::Property

See [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; | [**ActiveConditionFn**](classSR__UTILS__NS_1_1Property.md#typedef-activeconditionfn)  <br> |
| typedef [**Property**](classSR__UTILS__NS_1_1Property.md) | [**Base**](classSR__UTILS__NS_1_1Property.md#typedef-base)  <br> |
| typedef SR\_HTYPES\_NS::Marshal::Ptr | [**MarshalPtr**](classSR__UTILS__NS_1_1Property.md#typedef-marshalptr)  <br> |
| typedef [**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) & | [**MarshalRef**](classSR__UTILS__NS_1_1Property.md#typedef-marshalref)  <br> |
| typedef std::unique\_ptr&lt; [**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) &gt; | [**MarshalUniquePtr**](classSR__UTILS__NS_1_1Property.md#typedef-marshaluniqueptr)  <br> |


























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_MATH\_NS::BVector3 | [**GetBVector3**](#function-getbvector3) () noexcept const<br> |
|  SR\_NODISCARD bool | [**GetBool**](#function-getbool) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetDrag**](#function-getdrag) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**GetFVector2**](#function-getfvector2) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector3 | [**GetFVector3**](#function-getfvector3) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector4 | [**GetFVector4**](#function-getfvector4) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetFloat**](#function-getfloat) () noexcept const<br> |
|  SR\_NODISCARD int16\_t | [**GetInt16**](#function-getint16) () noexcept const<br> |
|  SR\_NODISCARD int32\_t | [**GetInt32**](#function-getint32) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetResetValue**](#function-getresetvalue) () noexcept const<br> |
|  SR\_NODISCARD StandardType | [**GetStandardType**](#function-getstandardtype) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**GetString**](#function-getstring) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetStringAtom**](#function-getstringatom) () noexcept const<br> |
|  SR\_NODISCARD uint16\_t | [**GetUInt16**](#function-getuint16) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetUInt32**](#function-getuint32) () noexcept const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::UVector2 | [**GetUVector2**](#function-getuvector2) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) | [**GetUnicodeString**](#function-getunicodestring) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsMultiline**](#function-ismultiline) () noexcept const<br> |
| virtual void | [**LoadProperty**](#function-loadproperty) (MarshalRef marshal) noexcept override<br> |
| virtual void | [**SaveProperty**](#function-saveproperty) (MarshalRef marshal) noexcept override const<br> |
|  void | [**SetBVector3**](#function-setbvector3) (const SR\_MATH\_NS::BVector3 & value) noexcept<br> |
|  void | [**SetBool**](#function-setbool) (bool value) noexcept<br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**SetDrag**](#function-setdrag) (float\_t value) <br> |
|  void | [**SetFVector2**](#function-setfvector2) (const SR\_MATH\_NS::FVector2 & value) noexcept<br> |
|  void | [**SetFVector3**](#function-setfvector3) (const SR\_MATH\_NS::FVector3 & value) noexcept<br> |
|  void | [**SetFVector4**](#function-setfvector4) (const SR\_MATH\_NS::FVector4 & value) noexcept<br> |
|  void | [**SetFloat**](#function-setfloat) (float\_t value) noexcept<br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**SetGetter**](#function-setgetter) (GetterFn fn) <br> |
|  void | [**SetInt16**](#function-setint16) (int16\_t value) noexcept<br> |
|  void | [**SetInt32**](#function-setint32) (int32\_t value) noexcept<br> |
|  void | [**SetMultiline**](#function-setmultiline) () noexcept<br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**SetResetValue**](#function-setresetvalue) (float\_t value) <br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**SetSetter**](#function-setsetter) (SetterFn fn) <br> |
|  void | [**SetString**](#function-setstring) (const std::string & value) noexcept<br> |
|  void | [**SetStringAtom**](#function-setstringatom) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value) noexcept<br> |
|  [**StandardProperty**](classSR__UTILS__NS_1_1StandardProperty.md) & | [**SetType**](#function-settype) (StandardType type) <br> |
|  void | [**SetUInt16**](#function-setuint16) (uint16\_t value) noexcept<br> |
|  void | [**SetUInt32**](#function-setuint32) (uint32\_t value) noexcept<br> |
|  void | [**SetUVector2**](#function-setuvector2) (const SR\_MATH\_NS::UVector2 & value) noexcept<br> |
|  void | [**SetUnicodeString**](#function-setunicodestring) (const [**SR\_HTYPES\_NS::UnicodeString**](classSR__HTYPES__NS_1_1UnicodeString.md) & value) noexcept<br> |


## Public Functions inherited from SR_UTILS_NS::Property

See [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](classSR__UTILS__NS_1_1Property.md#function-getname) () noexcept const<br> |
|  SR\_NODISCARD bool | [**GetOptional**](classSR__UTILS__NS_1_1Property.md#function-getoptional) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetPropertyTypeName**](classSR__UTILS__NS_1_1Property.md#function-getpropertytypename) () noexcept const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetPropertyVersion**](classSR__UTILS__NS_1_1Property.md#function-getpropertyversion) () noexcept const = 0<br> |
|  SR\_NODISCARD PropertyPublicity | [**GetPublicity**](classSR__UTILS__NS_1_1Property.md#function-getpublicity) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetWidth**](classSR__UTILS__NS_1_1Property.md#function-getwidth) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsActive**](classSR__UTILS__NS_1_1Property.md#function-isactive) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDontSave**](classSR__UTILS__NS_1_1Property.md#function-isdontsave) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsOptionalMode**](classSR__UTILS__NS_1_1Property.md#function-isoptionalmode) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSameLine**](classSR__UTILS__NS_1_1Property.md#function-issameline) () noexcept const<br> |
| virtual void | [**LoadProperty**](classSR__UTILS__NS_1_1Property.md#function-loadproperty) (MarshalRef marshal) noexcept<br> |
|   | [**Property**](classSR__UTILS__NS_1_1Property.md#function-property-12) () = default<br> |
|   | [**Property**](classSR__UTILS__NS_1_1Property.md#function-property-22) ([**Property**](classSR__UTILS__NS_1_1Property.md) && other) noexcept<br> |
| virtual void | [**SaveProperty**](classSR__UTILS__NS_1_1Property.md#function-saveproperty) (MarshalRef marshal) noexcept const<br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetActiveCondition**](classSR__UTILS__NS_1_1Property.md#function-setactivecondition) (ActiveConditionFn value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetDontSave**](classSR__UTILS__NS_1_1Property.md#function-setdontsave) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetName**](classSR__UTILS__NS_1_1Property.md#function-setname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetOptional**](classSR__UTILS__NS_1_1Property.md#function-setoptional) (bool value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetOptionalMode**](classSR__UTILS__NS_1_1Property.md#function-setoptionalmode) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetPublicity**](classSR__UTILS__NS_1_1Property.md#function-setpublicity) (PropertyPublicity publicity) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetReadOnly**](classSR__UTILS__NS_1_1Property.md#function-setreadonly) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetSameLine**](classSR__UTILS__NS_1_1Property.md#function-setsameline) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetWidth**](classSR__UTILS__NS_1_1Property.md#function-setwidth) (float\_t value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**operator=**](classSR__UTILS__NS_1_1Property.md#function-operator) ([**Property**](classSR__UTILS__NS_1_1Property.md) && other) noexcept<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |






































































## Protected Functions inherited from SR_UTILS_NS::Property

See [SR\_UTILS\_NS::Property](classSR__UTILS__NS_1_1Property.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD MarshalUniquePtr | [**AllocatePropertyBlock**](classSR__UTILS__NS_1_1Property.md#function-allocatepropertyblock) () const<br> |
|  SR\_NODISCARD MarshalUniquePtr | [**LoadPropertyBase**](classSR__UTILS__NS_1_1Property.md#function-loadpropertybase) (MarshalRef marshal) const<br> |
|  void | [**SavePropertyBase**](classSR__UTILS__NS_1_1Property.md#function-savepropertybase) (MarshalRef marshal, MarshalUniquePtr pBlock) const<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Functions Documentation




### function GetBVector3 

```C++
inline SR_NODISCARD SR_MATH_NS::BVector3 SR_UTILS_NS::StandardProperty::GetBVector3 () noexcept const
```




<hr>



### function GetBool 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::StandardProperty::GetBool () noexcept const
```




<hr>



### function GetDrag 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::StandardProperty::GetDrag () noexcept const
```




<hr>



### function GetFVector2 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector2 SR_UTILS_NS::StandardProperty::GetFVector2 () noexcept const
```




<hr>



### function GetFVector3 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector3 SR_UTILS_NS::StandardProperty::GetFVector3 () noexcept const
```




<hr>



### function GetFVector4 

```C++
inline SR_NODISCARD SR_MATH_NS::FVector4 SR_UTILS_NS::StandardProperty::GetFVector4 () noexcept const
```




<hr>



### function GetFloat 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::StandardProperty::GetFloat () noexcept const
```




<hr>



### function GetInt16 

```C++
inline SR_NODISCARD int16_t SR_UTILS_NS::StandardProperty::GetInt16 () noexcept const
```




<hr>



### function GetInt32 

```C++
inline SR_NODISCARD int32_t SR_UTILS_NS::StandardProperty::GetInt32 () noexcept const
```




<hr>



### function GetResetValue 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::StandardProperty::GetResetValue () noexcept const
```




<hr>



### function GetStandardType 

```C++
inline SR_NODISCARD StandardType SR_UTILS_NS::StandardProperty::GetStandardType () noexcept const
```




<hr>



### function GetString 

```C++
inline SR_NODISCARD std::string SR_UTILS_NS::StandardProperty::GetString () noexcept const
```




<hr>



### function GetStringAtom 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::StandardProperty::GetStringAtom () noexcept const
```




<hr>



### function GetUInt16 

```C++
inline SR_NODISCARD uint16_t SR_UTILS_NS::StandardProperty::GetUInt16 () noexcept const
```




<hr>



### function GetUInt32 

```C++
inline SR_NODISCARD uint32_t SR_UTILS_NS::StandardProperty::GetUInt32 () noexcept const
```




<hr>



### function GetUVector2 

```C++
inline SR_NODISCARD SR_MATH_NS::UVector2 SR_UTILS_NS::StandardProperty::GetUVector2 () noexcept const
```




<hr>



### function GetUnicodeString 

```C++
inline SR_NODISCARD SR_HTYPES_NS::UnicodeString SR_UTILS_NS::StandardProperty::GetUnicodeString () noexcept const
```




<hr>



### function IsMultiline 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::StandardProperty::IsMultiline () noexcept const
```




<hr>



### function LoadProperty 

```C++
virtual void SR_UTILS_NS::StandardProperty::LoadProperty (
    MarshalRef marshal
) noexcept override
```



Implements [*SR\_UTILS\_NS::Property::LoadProperty*](classSR__UTILS__NS_1_1Property.md#function-loadproperty)


<hr>



### function SaveProperty 

```C++
virtual void SR_UTILS_NS::StandardProperty::SaveProperty (
    MarshalRef marshal
) noexcept override const
```



Implements [*SR\_UTILS\_NS::Property::SaveProperty*](classSR__UTILS__NS_1_1Property.md#function-saveproperty)


<hr>



### function SetBVector3 

```C++
inline void SR_UTILS_NS::StandardProperty::SetBVector3 (
    const SR_MATH_NS::BVector3 & value
) noexcept
```




<hr>



### function SetBool 

```C++
inline void SR_UTILS_NS::StandardProperty::SetBool (
    bool value
) noexcept
```




<hr>



### function SetDrag 

```C++
inline StandardProperty & SR_UTILS_NS::StandardProperty::SetDrag (
    float_t value
) 
```




<hr>



### function SetFVector2 

```C++
inline void SR_UTILS_NS::StandardProperty::SetFVector2 (
    const SR_MATH_NS::FVector2 & value
) noexcept
```




<hr>



### function SetFVector3 

```C++
inline void SR_UTILS_NS::StandardProperty::SetFVector3 (
    const SR_MATH_NS::FVector3 & value
) noexcept
```




<hr>



### function SetFVector4 

```C++
inline void SR_UTILS_NS::StandardProperty::SetFVector4 (
    const SR_MATH_NS::FVector4 & value
) noexcept
```




<hr>



### function SetFloat 

```C++
inline void SR_UTILS_NS::StandardProperty::SetFloat (
    float_t value
) noexcept
```




<hr>



### function SetGetter 

```C++
inline StandardProperty & SR_UTILS_NS::StandardProperty::SetGetter (
    GetterFn fn
) 
```




<hr>



### function SetInt16 

```C++
inline void SR_UTILS_NS::StandardProperty::SetInt16 (
    int16_t value
) noexcept
```




<hr>



### function SetInt32 

```C++
inline void SR_UTILS_NS::StandardProperty::SetInt32 (
    int32_t value
) noexcept
```




<hr>



### function SetMultiline 

```C++
inline void SR_UTILS_NS::StandardProperty::SetMultiline () noexcept
```




<hr>



### function SetResetValue 

```C++
inline StandardProperty & SR_UTILS_NS::StandardProperty::SetResetValue (
    float_t value
) 
```




<hr>



### function SetSetter 

```C++
inline StandardProperty & SR_UTILS_NS::StandardProperty::SetSetter (
    SetterFn fn
) 
```




<hr>



### function SetString 

```C++
inline void SR_UTILS_NS::StandardProperty::SetString (
    const std::string & value
) noexcept
```




<hr>



### function SetStringAtom 

```C++
inline void SR_UTILS_NS::StandardProperty::SetStringAtom (
    const SR_UTILS_NS::StringAtom & value
) noexcept
```




<hr>



### function SetType 

```C++
inline StandardProperty & SR_UTILS_NS::StandardProperty::SetType (
    StandardType type
) 
```




<hr>



### function SetUInt16 

```C++
inline void SR_UTILS_NS::StandardProperty::SetUInt16 (
    uint16_t value
) noexcept
```




<hr>



### function SetUInt32 

```C++
inline void SR_UTILS_NS::StandardProperty::SetUInt32 (
    uint32_t value
) noexcept
```




<hr>



### function SetUVector2 

```C++
inline void SR_UTILS_NS::StandardProperty::SetUVector2 (
    const SR_MATH_NS::UVector2 & value
) noexcept
```




<hr>



### function SetUnicodeString 

```C++
inline void SR_UTILS_NS::StandardProperty::SetUnicodeString (
    const SR_HTYPES_NS::UnicodeString & value
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/TypeTraits/StandardProperty.h`

