

# Class SR\_GRAPH\_NS::MaterialProperty



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md)








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
|  SR\_NODISCARD const ShaderPropertyVariant & | [**GetData**](#function-getdata) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetDisplayName**](#function-getdisplayname) () noexcept const<br> |
|  SR\_NODISCARD [**BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md) \* | [**GetMaterial**](#function-getmaterial) () noexcept const<br> |
|  SR\_NODISCARD ShaderVarType | [**GetShaderVarType**](#function-getshadervartype) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsPushConstant**](#function-ispushconstant) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSampler**](#function-issampler) () noexcept const<br> |
| virtual void | [**LoadProperty**](#function-loadproperty) (MarshalRef marshal) noexcept override<br> |
|   | [**MaterialProperty**](#function-materialproperty-13) () = default<br> |
|   | [**MaterialProperty**](#function-materialproperty-23) (ShaderVarType type) <br> |
|   | [**MaterialProperty**](#function-materialproperty-33) ([**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) && other) noexcept<br> |
| virtual void | [**SaveProperty**](#function-saveproperty) (MarshalRef marshal) noexcept override const<br> |
|  [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) & | [**SetData**](#function-setdata) (const T & value) noexcept<br> |
|  [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) & | [**SetDisplayName**](#function-setdisplayname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) value) noexcept<br> |
|  [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) & | [**SetMaterial**](#function-setmaterial) ([**BaseMaterial**](classSR__GRAPH__NS_1_1BaseMaterial.md) \* value) noexcept<br> |
|  [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) & | [**SetPushConstant**](#function-setpushconstant) (bool value) noexcept<br> |
|  [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) & | [**SetShaderVarType**](#function-setshadervartype) (ShaderVarType value) noexcept<br> |
|  void | [**Use**](#function-use) ([**SR\_GTYPES\_NS::Shader**](classSR__GTYPES__NS_1_1Shader.md) \* pShader) noexcept const<br> |
|  [**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) & | [**operator=**](#function-operator) ([**MaterialProperty**](classSR__GRAPH__NS_1_1MaterialProperty.md) && other) noexcept<br> |
|   | [**~MaterialProperty**](#function-materialproperty) () override<br> |


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




### function GetData 

```C++
inline SR_NODISCARD const ShaderPropertyVariant & SR_GRAPH_NS::MaterialProperty::GetData () noexcept const
```




<hr>



### function GetDisplayName 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_GRAPH_NS::MaterialProperty::GetDisplayName () noexcept const
```




<hr>



### function GetMaterial 

```C++
inline SR_NODISCARD BaseMaterial * SR_GRAPH_NS::MaterialProperty::GetMaterial () noexcept const
```




<hr>



### function GetShaderVarType 

```C++
inline SR_NODISCARD ShaderVarType SR_GRAPH_NS::MaterialProperty::GetShaderVarType () noexcept const
```




<hr>



### function IsPushConstant 

```C++
inline SR_NODISCARD bool SR_GRAPH_NS::MaterialProperty::IsPushConstant () noexcept const
```




<hr>



### function IsSampler 

```C++
SR_NODISCARD bool SR_GRAPH_NS::MaterialProperty::IsSampler () noexcept const
```




<hr>



### function LoadProperty 

```C++
virtual void SR_GRAPH_NS::MaterialProperty::LoadProperty (
    MarshalRef marshal
) noexcept override
```



Implements [*SR\_UTILS\_NS::Property::LoadProperty*](classSR__UTILS__NS_1_1Property.md#function-loadproperty)


<hr>



### function MaterialProperty [1/3]

```C++
SR_GRAPH_NS::MaterialProperty::MaterialProperty () = default
```




<hr>



### function MaterialProperty [2/3]

```C++
inline explicit SR_GRAPH_NS::MaterialProperty::MaterialProperty (
    ShaderVarType type
) 
```




<hr>



### function MaterialProperty [3/3]

```C++
inline SR_GRAPH_NS::MaterialProperty::MaterialProperty (
    MaterialProperty && other
) noexcept
```




<hr>



### function SaveProperty 

```C++
virtual void SR_GRAPH_NS::MaterialProperty::SaveProperty (
    MarshalRef marshal
) noexcept override const
```



Implements [*SR\_UTILS\_NS::Property::SaveProperty*](classSR__UTILS__NS_1_1Property.md#function-saveproperty)


<hr>



### function SetData 

```C++
template<typename T>
inline MaterialProperty & SR_GRAPH_NS::MaterialProperty::SetData (
    const T & value
) noexcept
```




<hr>



### function SetDisplayName 

```C++
inline MaterialProperty & SR_GRAPH_NS::MaterialProperty::SetDisplayName (
    SR_UTILS_NS::StringAtom value
) noexcept
```




<hr>



### function SetMaterial 

```C++
inline MaterialProperty & SR_GRAPH_NS::MaterialProperty::SetMaterial (
    BaseMaterial * value
) noexcept
```




<hr>



### function SetPushConstant 

```C++
inline MaterialProperty & SR_GRAPH_NS::MaterialProperty::SetPushConstant (
    bool value
) noexcept
```




<hr>



### function SetShaderVarType 

```C++
inline MaterialProperty & SR_GRAPH_NS::MaterialProperty::SetShaderVarType (
    ShaderVarType value
) noexcept
```




<hr>



### function Use 

```C++
void SR_GRAPH_NS::MaterialProperty::Use (
    SR_GTYPES_NS::Shader * pShader
) noexcept const
```




<hr>



### function operator= 

```C++
inline MaterialProperty & SR_GRAPH_NS::MaterialProperty::operator= (
    MaterialProperty && other
) noexcept
```




<hr>



### function ~MaterialProperty 

```C++
SR_GRAPH_NS::MaterialProperty::~MaterialProperty () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Material/MaterialProperty.h`

