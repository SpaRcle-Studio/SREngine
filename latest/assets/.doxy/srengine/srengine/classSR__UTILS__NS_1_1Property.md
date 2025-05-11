

# Class SR\_UTILS\_NS::Property



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Property**](classSR__UTILS__NS_1_1Property.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_GRAPH\_NS::MaterialProperty](classSR__GRAPH__NS_1_1MaterialProperty.md),  [SR\_GRAPH\_NS::MeshMaterialProperty](classSR__GRAPH__NS_1_1MeshMaterialProperty.md),  [SR\_UTILS\_NS::ArrayReferenceProperty](classSR__UTILS__NS_1_1ArrayReferenceProperty.md),  [SR\_UTILS\_NS::EntityRefProperty](classSR__UTILS__NS_1_1EntityRefProperty.md),  [SR\_UTILS\_NS::EnumProperty](classSR__UTILS__NS_1_1EnumProperty.md),  [SR\_UTILS\_NS::ExternalProperty](classSR__UTILS__NS_1_1ExternalProperty.md),  [SR\_UTILS\_NS::LabelProperty](classSR__UTILS__NS_1_1LabelProperty.md),  [SR\_UTILS\_NS::PathProperty](classSR__UTILS__NS_1_1PathProperty.md),  [SR\_UTILS\_NS::PropertyContainer](classSR__UTILS__NS_1_1PropertyContainer.md),  [SR\_UTILS\_NS::StandardProperty](classSR__UTILS__NS_1_1StandardProperty.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool()&gt; | [**ActiveConditionFn**](#typedef-activeconditionfn)  <br> |
| typedef [**Property**](classSR__UTILS__NS_1_1Property.md) | [**Base**](#typedef-base)  <br> |
| typedef SR\_HTYPES\_NS::Marshal::Ptr | [**MarshalPtr**](#typedef-marshalptr)  <br> |
| typedef [**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) & | [**MarshalRef**](#typedef-marshalref)  <br> |
| typedef std::unique\_ptr&lt; [**SR\_HTYPES\_NS::Marshal**](classSR__HTYPES__NS_1_1Marshal.md) &gt; | [**MarshalUniquePtr**](#typedef-marshaluniqueptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () noexcept const<br> |
|  SR\_NODISCARD bool | [**GetOptional**](#function-getoptional) () noexcept const<br> |
| virtual SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetPropertyTypeName**](#function-getpropertytypename) () noexcept const = 0<br> |
| virtual SR\_NODISCARD uint16\_t | [**GetPropertyVersion**](#function-getpropertyversion) () noexcept const = 0<br> |
|  SR\_NODISCARD PropertyPublicity | [**GetPublicity**](#function-getpublicity) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetWidth**](#function-getwidth) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsActive**](#function-isactive) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsDontSave**](#function-isdontsave) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsOptionalMode**](#function-isoptionalmode) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsSameLine**](#function-issameline) () noexcept const<br> |
| virtual void | [**LoadProperty**](#function-loadproperty) (MarshalRef marshal) noexcept<br> |
|   | [**Property**](#function-property-12) () = default<br> |
|   | [**Property**](#function-property-22) ([**Property**](classSR__UTILS__NS_1_1Property.md) && other) noexcept<br> |
| virtual void | [**SaveProperty**](#function-saveproperty) (MarshalRef marshal) noexcept const<br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetActiveCondition**](#function-setactivecondition) (ActiveConditionFn value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetDontSave**](#function-setdontsave) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetName**](#function-setname) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetOptional**](#function-setoptional) (bool value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetOptionalMode**](#function-setoptionalmode) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetPublicity**](#function-setpublicity) (PropertyPublicity publicity) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetReadOnly**](#function-setreadonly) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetSameLine**](#function-setsameline) () <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**SetWidth**](#function-setwidth) (float\_t value) <br> |
|  [**Property**](classSR__UTILS__NS_1_1Property.md) & | [**operator=**](#function-operator) ([**Property**](classSR__UTILS__NS_1_1Property.md) && other) noexcept<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














































## Protected Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD MarshalUniquePtr | [**AllocatePropertyBlock**](#function-allocatepropertyblock) () const<br> |
|  SR\_NODISCARD MarshalUniquePtr | [**LoadPropertyBase**](#function-loadpropertybase) (MarshalRef marshal) const<br> |
|  void | [**SavePropertyBase**](#function-savepropertybase) (MarshalRef marshal, MarshalUniquePtr pBlock) const<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef ActiveConditionFn 

```C++
using SR_UTILS_NS::Property::ActiveConditionFn =  SR_HTYPES_NS::Function<bool()>;
```




<hr>



### typedef Base 

```C++
using SR_UTILS_NS::Property::Base =  Property;
```




<hr>



### typedef MarshalPtr 

```C++
using SR_UTILS_NS::Property::MarshalPtr =  SR_HTYPES_NS::Marshal::Ptr;
```




<hr>



### typedef MarshalRef 

```C++
using SR_UTILS_NS::Property::MarshalRef =  SR_HTYPES_NS::Marshal&;
```




<hr>



### typedef MarshalUniquePtr 

```C++
using SR_UTILS_NS::Property::MarshalUniquePtr =  std::unique_ptr<SR_HTYPES_NS::Marshal>;
```




<hr>
## Public Functions Documentation




### function GetName 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::Property::GetName () noexcept const
```




<hr>



### function GetOptional 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Property::GetOptional () noexcept const
```




<hr>



### function GetPropertyTypeName 

```C++
virtual SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::Property::GetPropertyTypeName () noexcept const = 0
```




<hr>



### function GetPropertyVersion 

```C++
virtual SR_NODISCARD uint16_t SR_UTILS_NS::Property::GetPropertyVersion () noexcept const = 0
```




<hr>



### function GetPublicity 

```C++
inline SR_NODISCARD PropertyPublicity SR_UTILS_NS::Property::GetPublicity () noexcept const
```




<hr>



### function GetWidth 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::Property::GetWidth () noexcept const
```




<hr>



### function IsActive 

```C++
SR_NODISCARD bool SR_UTILS_NS::Property::IsActive () noexcept const
```




<hr>



### function IsDontSave 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Property::IsDontSave () noexcept const
```




<hr>



### function IsOptionalMode 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Property::IsOptionalMode () noexcept const
```




<hr>



### function IsSameLine 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Property::IsSameLine () noexcept const
```




<hr>



### function LoadProperty 

```C++
inline virtual void SR_UTILS_NS::Property::LoadProperty (
    MarshalRef marshal
) noexcept
```




<hr>



### function Property [1/2]

```C++
SR_UTILS_NS::Property::Property () = default
```




<hr>



### function Property [2/2]

```C++
inline SR_UTILS_NS::Property::Property (
    Property && other
) noexcept
```




<hr>



### function SaveProperty 

```C++
inline virtual void SR_UTILS_NS::Property::SaveProperty (
    MarshalRef marshal
) noexcept const
```




<hr>



### function SetActiveCondition 

```C++
inline Property & SR_UTILS_NS::Property::SetActiveCondition (
    ActiveConditionFn value
) 
```




<hr>



### function SetDontSave 

```C++
inline Property & SR_UTILS_NS::Property::SetDontSave () 
```




<hr>



### function SetName 

```C++
inline Property & SR_UTILS_NS::Property::SetName (
    SR_UTILS_NS::StringAtom value
) 
```




<hr>



### function SetOptional 

```C++
inline Property & SR_UTILS_NS::Property::SetOptional (
    bool value
) 
```




<hr>



### function SetOptionalMode 

```C++
inline Property & SR_UTILS_NS::Property::SetOptionalMode () 
```




<hr>



### function SetPublicity 

```C++
inline Property & SR_UTILS_NS::Property::SetPublicity (
    PropertyPublicity publicity
) 
```




<hr>



### function SetReadOnly 

```C++
inline Property & SR_UTILS_NS::Property::SetReadOnly () 
```




<hr>



### function SetSameLine 

```C++
inline Property & SR_UTILS_NS::Property::SetSameLine () 
```




<hr>



### function SetWidth 

```C++
inline Property & SR_UTILS_NS::Property::SetWidth (
    float_t value
) 
```




<hr>



### function operator= 

```C++
inline Property & SR_UTILS_NS::Property::operator= (
    Property && other
) noexcept
```




<hr>
## Protected Functions Documentation




### function AllocatePropertyBlock 

```C++
SR_NODISCARD MarshalUniquePtr SR_UTILS_NS::Property::AllocatePropertyBlock () const
```




<hr>



### function LoadPropertyBase 

```C++
SR_NODISCARD MarshalUniquePtr SR_UTILS_NS::Property::LoadPropertyBase (
    MarshalRef marshal
) const
```




<hr>



### function SavePropertyBase 

```C++
void SR_UTILS_NS::Property::SavePropertyBase (
    MarshalRef marshal,
    MarshalUniquePtr pBlock
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/TypeTraits/Property.h`

