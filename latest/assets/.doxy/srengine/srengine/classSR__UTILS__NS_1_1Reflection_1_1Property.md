

# Class SR\_UTILS\_NS::Reflection::Property



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Reflection**](namespaceSR__UTILS__NS_1_1Reflection.md) **>** [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**CheckSRClass**](#function-checksrclass) () <br> |
|  SR\_NODISCARD [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**Get**](#function-get) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* pOwner) noexcept const<br> |
|  SR\_NODISCARD const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & | [**GetDefaultValue**](#function-getdefaultvalue) () noexcept const<br> |
|  SR\_NODISCARD const [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**GetEditorParams**](#function-geteditorparams) () noexcept const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetName**](#function-getname) () noexcept const<br> |
|  SR\_NODISCARD PropertyPublicity | [**GetPublicity**](#function-getpublicity) () noexcept const<br> |
|  SR\_NODISCARD const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & | [**GetResetValue**](#function-getresetvalue) () noexcept const<br> |
|  SR\_NODISCARD PropertySRClassContainsMode | [**GetSRClassContainsMode**](#function-getsrclasscontainsmode) () noexcept const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetSerializeName**](#function-getserializename) () noexcept const<br> |
|  SR\_NODISCARD bool | [**HasExplicitSetter**](#function-hasexplicitsetter) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsActive**](#function-isactive) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* pOwner) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsHidden**](#function-ishidden) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* pOwner) noexcept const<br> |
|  SR\_NODISCARD bool | [**IsReadOnly**](#function-isreadonly) () noexcept const<br> |
|  void | [**OnChanged**](#function-onchanged) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* pOwner) noexcept const<br> |
|   | [**Property**](#function-property) () = default<br> |
|  void | [**Set**](#function-set) ([**SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* pOwner, const [**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) & value) noexcept const<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetChangeCallback**](#function-setchangecallback) (ChangeCallbackFn callback) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetDefaultValue**](#function-setdefaultvalue) ([**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) && value) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetEditorParams**](#function-seteditorparams) (const [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & params) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetGetter**](#function-setgetter) (GetCallbackFn callback) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetHasExplicitSetter**](#function-sethasexplicitsetter) (bool hasExplicitSetter) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetName**](#function-setname) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetPropertyCondition**](#function-setpropertycondition) (PropertyActiveCallbackFn callback) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetPublicity**](#function-setpublicity) (PropertyPublicity publicity) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetResetValue**](#function-setresetvalue) ([**Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) && value) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetSerializeName**](#function-setserializename) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & serializeName) noexcept<br> |
|  [**Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & | [**SetSetter**](#function-setsetter) (SetCallbackFn callback) noexcept<br> |




























## Public Functions Documentation




### function CheckSRClass 

```C++
template<typename T>
inline Property & SR_UTILS_NS::Reflection::Property::CheckSRClass () 
```




<hr>



### function Get 

```C++
inline SR_NODISCARD Value SR_UTILS_NS::Reflection::Property::Get (
    SRClass * pOwner
) noexcept const
```




<hr>



### function GetDefaultValue 

```C++
inline SR_NODISCARD const Value & SR_UTILS_NS::Reflection::Property::GetDefaultValue () noexcept const
```




<hr>



### function GetEditorParams 

```C++
inline SR_NODISCARD const EditorPropertyParams & SR_UTILS_NS::Reflection::Property::GetEditorParams () noexcept const
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD StringAtom SR_UTILS_NS::Reflection::Property::GetName () noexcept const
```




<hr>



### function GetPublicity 

```C++
inline SR_NODISCARD PropertyPublicity SR_UTILS_NS::Reflection::Property::GetPublicity () noexcept const
```




<hr>



### function GetResetValue 

```C++
inline SR_NODISCARD const Value & SR_UTILS_NS::Reflection::Property::GetResetValue () noexcept const
```




<hr>



### function GetSRClassContainsMode 

```C++
inline SR_NODISCARD PropertySRClassContainsMode SR_UTILS_NS::Reflection::Property::GetSRClassContainsMode () noexcept const
```




<hr>



### function GetSerializeName 

```C++
inline SR_NODISCARD StringAtom SR_UTILS_NS::Reflection::Property::GetSerializeName () noexcept const
```




<hr>



### function HasExplicitSetter 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::Property::HasExplicitSetter () noexcept const
```




<hr>



### function IsActive 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::Property::IsActive (
    SRClass * pOwner
) noexcept const
```




<hr>



### function IsHidden 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::Property::IsHidden (
    SRClass * pOwner
) noexcept const
```




<hr>



### function IsReadOnly 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::Property::IsReadOnly () noexcept const
```




<hr>



### function OnChanged 

```C++
inline void SR_UTILS_NS::Reflection::Property::OnChanged (
    SRClass * pOwner
) noexcept const
```




<hr>



### function Property 

```C++
SR_UTILS_NS::Reflection::Property::Property () = default
```




<hr>



### function Set 

```C++
inline void SR_UTILS_NS::Reflection::Property::Set (
    SRClass * pOwner,
    const Value & value
) noexcept const
```




<hr>



### function SetChangeCallback 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetChangeCallback (
    ChangeCallbackFn callback
) noexcept
```




<hr>



### function SetDefaultValue 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetDefaultValue (
    Value && value
) noexcept
```




<hr>



### function SetEditorParams 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetEditorParams (
    const EditorPropertyParams & params
) noexcept
```




<hr>



### function SetGetter 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetGetter (
    GetCallbackFn callback
) noexcept
```




<hr>



### function SetHasExplicitSetter 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetHasExplicitSetter (
    bool hasExplicitSetter
) noexcept
```




<hr>



### function SetName 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetName (
    const StringAtom & name
) noexcept
```




<hr>



### function SetPropertyCondition 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetPropertyCondition (
    PropertyActiveCallbackFn callback
) noexcept
```




<hr>



### function SetPublicity 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetPublicity (
    PropertyPublicity publicity
) noexcept
```




<hr>



### function SetResetValue 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetResetValue (
    Value && value
) noexcept
```




<hr>



### function SetSerializeName 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetSerializeName (
    const StringAtom & serializeName
) noexcept
```




<hr>



### function SetSetter 

```C++
inline Property & SR_UTILS_NS::Reflection::Property::SetSetter (
    SetCallbackFn callback
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Reflection/Property.h`

