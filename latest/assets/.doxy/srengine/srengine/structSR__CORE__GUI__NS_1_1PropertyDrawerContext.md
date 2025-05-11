

# Struct SR\_CORE\_GUI\_NS::PropertyDrawerContext



[**ClassList**](annotated.md) **>** [**SR\_CORE\_GUI\_NS**](namespaceSR__CORE__GUI__NS.md) **>** [**PropertyDrawerContext**](structSR__CORE__GUI__NS_1_1PropertyDrawerContext.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  float\_t | [**axisButtonWidth**](#variable-axisbuttonwidth)   = `30.f`<br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**customDisplayName**](#variable-customdisplayname)  <br> |
|  [**SR\_UTILS\_NS::Reflection::EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) | [**editorPropertyParams**](#variable-editorpropertyparams)  <br> |
|  float\_t | [**fieldHeight**](#variable-fieldheight)   = `0.f`<br> |
|  float\_t | [**fieldTitleWidth**](#variable-fieldtitlewidth)   = `90.f`<br> |
|  float\_t | [**fieldWidth**](#variable-fieldwidth)   = `250.f`<br> |
|  float\_t | [**lineHeight**](#variable-lineheight)   = `1.f`<br> |
|  uint32\_t | [**maxPartsInLine**](#variable-maxpartsinline)   = `3`<br> |
|  bool | [**noHeader**](#variable-noheader)   = `false`<br> |
|  [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(bool drag)&gt; | [**onBeforeChangeCallback**](#variable-onbeforechangecallback)  <br> |
|  bool | [**openedByDefault**](#variable-openedbydefault)   = `false`<br> |
|  SR\_UTILS\_NS::Component::Ptr | [**pComponent**](#variable-pcomponent)  <br> |
|  [**EditorGUI**](classSR__CORE__GUI__NS_1_1EditorGUI.md) \* | [**pEditor**](#variable-peditor)   = `nullptr`<br> |
|  [**SR\_UTILS\_NS::SRClass**](classSR__UTILS__NS_1_1SRClass.md) \* | [**pOwner**](#variable-powner)   = `nullptr`<br> |
|  [**SR\_UTILS\_NS::Reflection::Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) const  \* | [**pProperty**](#variable-pproperty)   = `nullptr`<br> |
|  [**SR\_UTILS\_NS::Reflection::Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) \* | [**pValue**](#variable-pvalue)   = `nullptr`<br> |
|  uint64\_t | [**propertyIndex**](#variable-propertyindex)   = `0`<br> |
|  float\_t | [**spaceWidth**](#variable-spacewidth)   = `1.f`<br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD float\_t | [**GetArrowWidth**](#function-getarrowwidth) () const<br> |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::Reflection::EditorPropertyParams**](classSR__UTILS__NS_1_1Reflection_1_1EditorPropertyParams.md) & | [**GetEditorParams**](#function-geteditorparams) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Reflection::Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) const & | [**GetProperty**](#function-getproperty) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetPropertyDisplayName**](#function-getpropertydisplayname) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**GetPropertyName**](#function-getpropertyname) () const<br> |
|  SR\_NODISCARD [**SR\_UTILS\_NS::Reflection::Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) | [**GetValue**](#function-getvalue) () const<br> |
|  SR\_NODISCARD bool | [**HasExplicitSetter**](#function-hasexplicitsetter) () const<br> |
|   | [**PropertyDrawerContext**](#function-propertydrawercontext-12) (const [**SR\_UTILS\_NS::Reflection::Property**](classSR__UTILS__NS_1_1Reflection_1_1Property.md) & property) <br> |
|   | [**PropertyDrawerContext**](#function-propertydrawercontext-22) ([**SR\_UTILS\_NS::Reflection::Value**](classSR__UTILS__NS_1_1Reflection_1_1Value.md) \* pValue) <br> |




























## Public Attributes Documentation




### variable axisButtonWidth 

```C++
float_t SR_CORE_GUI_NS::PropertyDrawerContext::axisButtonWidth;
```




<hr>



### variable customDisplayName 

```C++
SR_UTILS_NS::StringAtom SR_CORE_GUI_NS::PropertyDrawerContext::customDisplayName;
```




<hr>



### variable editorPropertyParams 

```C++
SR_UTILS_NS::Reflection::EditorPropertyParams SR_CORE_GUI_NS::PropertyDrawerContext::editorPropertyParams;
```




<hr>



### variable fieldHeight 

```C++
float_t SR_CORE_GUI_NS::PropertyDrawerContext::fieldHeight;
```




<hr>



### variable fieldTitleWidth 

```C++
float_t SR_CORE_GUI_NS::PropertyDrawerContext::fieldTitleWidth;
```




<hr>



### variable fieldWidth 

```C++
float_t SR_CORE_GUI_NS::PropertyDrawerContext::fieldWidth;
```




<hr>



### variable lineHeight 

```C++
float_t SR_CORE_GUI_NS::PropertyDrawerContext::lineHeight;
```




<hr>



### variable maxPartsInLine 

```C++
uint32_t SR_CORE_GUI_NS::PropertyDrawerContext::maxPartsInLine;
```




<hr>



### variable noHeader 

```C++
bool SR_CORE_GUI_NS::PropertyDrawerContext::noHeader;
```




<hr>



### variable onBeforeChangeCallback 

```C++
SR_HTYPES_NS::Function<void(bool drag)> SR_CORE_GUI_NS::PropertyDrawerContext::onBeforeChangeCallback;
```




<hr>



### variable openedByDefault 

```C++
bool SR_CORE_GUI_NS::PropertyDrawerContext::openedByDefault;
```




<hr>



### variable pComponent 

```C++
SR_UTILS_NS::Component::Ptr SR_CORE_GUI_NS::PropertyDrawerContext::pComponent;
```




<hr>



### variable pEditor 

```C++
EditorGUI* SR_CORE_GUI_NS::PropertyDrawerContext::pEditor;
```




<hr>



### variable pOwner 

```C++
SR_UTILS_NS::SRClass* SR_CORE_GUI_NS::PropertyDrawerContext::pOwner;
```




<hr>



### variable pProperty 

```C++
SR_UTILS_NS::Reflection::Property const* SR_CORE_GUI_NS::PropertyDrawerContext::pProperty;
```




<hr>



### variable pValue 

```C++
SR_UTILS_NS::Reflection::Value* SR_CORE_GUI_NS::PropertyDrawerContext::pValue;
```




<hr>



### variable propertyIndex 

```C++
uint64_t SR_CORE_GUI_NS::PropertyDrawerContext::propertyIndex;
```




<hr>



### variable spaceWidth 

```C++
float_t SR_CORE_GUI_NS::PropertyDrawerContext::spaceWidth;
```




<hr>
## Public Functions Documentation




### function GetArrowWidth 

```C++
inline SR_NODISCARD float_t SR_CORE_GUI_NS::PropertyDrawerContext::GetArrowWidth () const
```




<hr>



### function GetEditorParams 

```C++
inline SR_NODISCARD const SR_UTILS_NS::Reflection::EditorPropertyParams & SR_CORE_GUI_NS::PropertyDrawerContext::GetEditorParams () const
```




<hr>



### function GetProperty 

```C++
inline SR_NODISCARD SR_UTILS_NS::Reflection::Property const & SR_CORE_GUI_NS::PropertyDrawerContext::GetProperty () const
```




<hr>



### function GetPropertyDisplayName 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_CORE_GUI_NS::PropertyDrawerContext::GetPropertyDisplayName () const
```




<hr>



### function GetPropertyName 

```C++
inline SR_NODISCARD SR_UTILS_NS::StringAtom SR_CORE_GUI_NS::PropertyDrawerContext::GetPropertyName () const
```




<hr>



### function GetValue 

```C++
inline SR_NODISCARD SR_UTILS_NS::Reflection::Value SR_CORE_GUI_NS::PropertyDrawerContext::GetValue () const
```




<hr>



### function HasExplicitSetter 

```C++
inline SR_NODISCARD bool SR_CORE_GUI_NS::PropertyDrawerContext::HasExplicitSetter () const
```




<hr>



### function PropertyDrawerContext [1/2]

```C++
inline explicit SR_CORE_GUI_NS::PropertyDrawerContext::PropertyDrawerContext (
    const SR_UTILS_NS::Reflection::Property & property
) 
```




<hr>



### function PropertyDrawerContext [2/2]

```C++
inline explicit SR_CORE_GUI_NS::PropertyDrawerContext::PropertyDrawerContext (
    SR_UTILS_NS::Reflection::Value * pValue
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/GUI/PropertyDrawer.h`

