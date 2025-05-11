

# Class SR\_UTILS\_NS::Reflection::EditorPropertyParams



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Reflection**](namespaceSR__UTILS__NS_1_1Reflection.md) **>** [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**EditorPropertyParams**](#function-editorpropertyparams) () = default<br> |
|  SR\_NODISCARD std::string\_view | [**GetCustomArg**](#function-getcustomarg) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) noexcept const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetDisplayName**](#function-getdisplayname) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetDragSpeed**](#function-getdragspeed) () noexcept const<br> |
|  SR\_NODISCARD float\_t | [**GetEditorWidth**](#function-geteditorwidth) () noexcept const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetInspector**](#function-getinspector) () noexcept const<br> |
|  SR\_NODISCARD [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetTooltip**](#function-gettooltip) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsNoHeader**](#function-isnoheader) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsNotNull**](#function-isnotnull) () noexcept const<br> |
|  [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**SetCustomArg**](#function-setcustomarg) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, std::string\_view value) noexcept<br> |
|  [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**SetDisplayName**](#function-setdisplayname) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & displayName) noexcept<br> |
|  [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**SetDragSpeed**](#function-setdragspeed) (float\_t speed) noexcept<br> |
|  [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**SetInspector**](#function-setinspector) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & inspector) noexcept<br> |
|  [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**SetNoHeader**](#function-setnoheader) () noexcept<br> |
|  [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**SetNotNull**](#function-setnotnull) () noexcept<br> |
|  [**EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**SetTooltip**](#function-settooltip) (const [**StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & tooltip) noexcept<br> |




























## Public Functions Documentation




### function EditorPropertyParams 

```C++
SR_UTILS_NS::Reflection::EditorPropertyParams::EditorPropertyParams () = default
```




<hr>



### function GetCustomArg 

```C++
inline SR_NODISCARD std::string_view SR_UTILS_NS::Reflection::EditorPropertyParams::GetCustomArg (
    const StringAtom & name
) noexcept const
```




<hr>



### function GetDisplayName 

```C++
inline SR_NODISCARD StringAtom SR_UTILS_NS::Reflection::EditorPropertyParams::GetDisplayName () noexcept const
```




<hr>



### function GetDragSpeed 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::Reflection::EditorPropertyParams::GetDragSpeed () noexcept const
```




<hr>



### function GetEditorWidth 

```C++
inline SR_NODISCARD float_t SR_UTILS_NS::Reflection::EditorPropertyParams::GetEditorWidth () noexcept const
```




<hr>



### function GetInspector 

```C++
inline SR_NODISCARD StringAtom SR_UTILS_NS::Reflection::EditorPropertyParams::GetInspector () noexcept const
```




<hr>



### function GetTooltip 

```C++
inline SR_NODISCARD StringAtom SR_UTILS_NS::Reflection::EditorPropertyParams::GetTooltip () noexcept const
```




<hr>



### function IsNoHeader 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::EditorPropertyParams::IsNoHeader () noexcept const
```




<hr>



### function IsNotNull 

```C++
inline SR_NODISCARD bool SR_UTILS_NS::Reflection::EditorPropertyParams::IsNotNull () noexcept const
```




<hr>



### function SetCustomArg 

```C++
inline EditorPropertyParams & SR_UTILS_NS::Reflection::EditorPropertyParams::SetCustomArg (
    const StringAtom & name,
    std::string_view value
) noexcept
```




<hr>



### function SetDisplayName 

```C++
inline EditorPropertyParams & SR_UTILS_NS::Reflection::EditorPropertyParams::SetDisplayName (
    const StringAtom & displayName
) noexcept
```




<hr>



### function SetDragSpeed 

```C++
inline EditorPropertyParams & SR_UTILS_NS::Reflection::EditorPropertyParams::SetDragSpeed (
    float_t speed
) noexcept
```




<hr>



### function SetInspector 

```C++
inline EditorPropertyParams & SR_UTILS_NS::Reflection::EditorPropertyParams::SetInspector (
    const StringAtom & inspector
) noexcept
```




<hr>



### function SetNoHeader 

```C++
inline EditorPropertyParams & SR_UTILS_NS::Reflection::EditorPropertyParams::SetNoHeader () noexcept
```




<hr>



### function SetNotNull 

```C++
inline EditorPropertyParams & SR_UTILS_NS::Reflection::EditorPropertyParams::SetNotNull () noexcept
```




<hr>



### function SetTooltip 

```C++
inline EditorPropertyParams & SR_UTILS_NS::Reflection::EditorPropertyParams::SetTooltip (
    const StringAtom & tooltip
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Reflection/Property.h`

