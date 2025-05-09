

# Class SR\_UTILS\_NS::LabelProperty



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**LabelProperty**](classSR__UTILS__NS_1_1LabelProperty.md)








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
|  SR\_NODISCARD [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) | [**GetColor**](#function-getcolor) () noexcept const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetLabel**](#function-getlabel) () noexcept const<br> |
|  [**LabelProperty**](classSR__UTILS__NS_1_1LabelProperty.md) & | [**SetColor**](#function-setcolor) (const [**SR\_MATH\_NS::FColor**](classSR__MATH__NS_1_1FColor.md) & value) <br> |
|  [**LabelProperty**](classSR__UTILS__NS_1_1LabelProperty.md) & | [**SetLabel**](#function-setlabel) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & value) <br> |


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




### function GetColor 

```C++
inline SR_NODISCARD SR_MATH_NS::FColor SR_UTILS_NS::LabelProperty::GetColor () noexcept const
```




<hr>



### function GetLabel 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_UTILS_NS::LabelProperty::GetLabel () noexcept const
```




<hr>



### function SetColor 

```C++
inline LabelProperty & SR_UTILS_NS::LabelProperty::SetColor (
    const SR_MATH_NS::FColor & value
) 
```




<hr>



### function SetLabel 

```C++
inline LabelProperty & SR_UTILS_NS::LabelProperty::SetLabel (
    const SR_UTILS_NS::StringAtom & value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/TypeTraits/Property.h`

