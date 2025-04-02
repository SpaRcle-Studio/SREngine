

# Namespace SR\_GRAPH\_GUI\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_GRAPH\_GUI\_NS**](namespaceSR__GRAPH__GUI__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**DrawPopupContext**](structSR__GRAPH__GUI__NS_1_1DrawPopupContext.md) <br> |
| class | [**ImGuiDisabledLockGuard**](classSR__GRAPH__GUI__NS_1_1ImGuiDisabledLockGuard.md) <br> |
| class | [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md) <br> |
| class | [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) <br> |
| class | [**NodeWidget**](classSR__GRAPH__GUI__NS_1_1NodeWidget.md) <br> |
| struct | [**NodeWidgetProperty**](structSR__GRAPH__GUI__NS_1_1NodeWidgetProperty.md) <br> |
| class | [**PopupItemSubWidget**](classSR__GRAPH__GUI__NS_1_1PopupItemSubWidget.md) <br> |
| class | [**Theme**](classSR__GRAPH__GUI__NS_1_1Theme.md) <br> |
| class | [**Widget**](classSR__GRAPH__GUI__NS_1_1Widget.md) <br> |
| class | [**WidgetContainer**](classSR__GRAPH__GUI__NS_1_1WidgetContainer.md) <br> |
| class | [**WidgetContainerElement**](classSR__GRAPH__GUI__NS_1_1WidgetContainerElement.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| union  | [**ImGuiDataTypeUnion**](#union-imguidatatypeunion)  <br> |
| typedef uint32\_t | [**WidgetFlagBits**](#typedef-widgetflagbits)  <br> |
| enum uint32\_t | [**WidgetFlags**](#enum-widgetflags)  <br> |
| typedef ImGuiWindowFlags | [**WindowFlags**](#typedef-windowflags)  <br> |






## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  const std::unordered\_map&lt; std::string, bool ImGuiStyle::\* &gt; | [**STYLE\_BOOL\_VALUES**](#variable-style_bool_values)   = `/* multi line expression */`<br> |
|  const std::unordered\_map&lt; std::string, ImGuiCol\_ &gt; | [**STYLE\_COLORS**](#variable-style_colors)  <br> |
|  const std::unordered\_map&lt; std::string, float ImGuiStyle::\* &gt; | [**STYLE\_FLOAT\_VALUES**](#variable-style_float_values)   = `/* multi line expression */`<br> |
|  const std::unordered\_map&lt; std::string, ImVec2 ImGuiStyle::\* &gt; | [**STYLE\_SIZE\_VALUES**](#variable-style_size_values)   = `/* multi line expression */`<br> |














## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**ButtonBehaviorNoNavFocus**](#function-buttonbehaviornonavfocus) (const ImRect & bb, ImGuiID id, bool \* out\_hovered, bool \* out\_held, ImGuiButtonFlags flags=0) <br> |
|  bool | [**CanCreateLink**](#function-cancreatelink) (Pin \* a, Pin \* b) <br> |
|  bool | [**CheckboxNoNavFocus**](#function-checkboxnonavfocus) (const char \* label, bool \* v) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) \* | [**CreateNode**](#function-createnode) (const SR\_MATH\_NS::FVector2 & pos, uint64\_t identifier) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawDataType**](#function-drawdatatype) ([**SR\_SRLM\_NS::DataType**](classSR__SRLM__NS_1_1DataType.md) \* pData, bool \* pIsEnum, void \* pProvider, float\_t width=0, uint32\_t deep=0) <br> |
|  bool | [**IsPinsCompatible**](#function-ispinscompatible) (SR\_SRLM\_NS::DataTypeClass first, SR\_SRLM\_NS::DataTypeClass second) <br> |
|  bool | [**RadioButton**](#function-radiobutton) (const char \* label, bool active, float\_t radius=1.f) <br> |
|   | [**SR\_ENUM\_NS\_CLASS**](#function-sr_enum_ns_class) (NodeType, None, Blueprint, Simple, Tree, Comment, Houdini, Connector) <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_MAYBE\_UNUSED uint32\_t | [**BeginForceEnabled**](#function-beginforceenabled) () <br> |
|  SR\_MAYBE\_UNUSED bool | [**BeginNodeCombo**](#function-beginnodecombo) (const char \* label, const char \* preview\_value, ImGuiComboFlags flags=0) <br> |
|  SR\_MAYBE\_UNUSED bool | [**Button**](#function-button) (const std::string & label, ImVec4 color=ImVec4(0, 0, 0, 0), ImVec4 hovered=ImVec4(0, 0, 0, 0), void \* pIdentifier=nullptr) <br> |
|  SR\_MAYBE\_UNUSED bool | [**Button**](#function-button) (const std::string & label, void \* pIdentifier) <br> |
|  SR\_MAYBE\_UNUSED float | [**CalcMaxPopupHeightFromItemCount**](#function-calcmaxpopupheightfromitemcount) (int items\_count) <br> |
|  SR\_MAYBE\_UNUSED bool | [**CheckBox**](#function-checkbox) (bool & value) <br> |
|  SR\_MAYBE\_UNUSED bool | [**CheckBox**](#function-checkbox) (const std::string & name, bool & value) <br> |
|  SR\_MAYBE\_UNUSED void | [**ColoredText**](#function-coloredtext) (const char \* text, const ImVec4 & color) <br> |
|  SR\_MAYBE\_UNUSED void | [**ColoredText**](#function-coloredtext) (const std::string & text, const ImVec4 & color) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DragInt32**](#function-dragint32) (const std::string & name, int32\_t & value, int32\_t drag=1) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DragUInt32**](#function-draguint32) (const std::string & name, uint32\_t & value, uint32\_t drag=1) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DragUnit**](#function-dragunit) (const std::string & name, SR\_MATH\_NS::Unit & value, float\_t drag=0.1f) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawBVec3Control**](#function-drawbvec3control) (const std::string & label, SR\_MATH\_NS::BVector3 & values, bool resetValue, float\_t columnWidth=70.0f) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawColorControl**](#function-drawcolorcontrol) (const std::string & label, SR\_MATH\_NS::FVector4 & values, float\_t resetValue=0.0f, float\_t columnWidth=40.0f) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawEditableSlider**](#function-draweditableslider) (const std::string & label, SR\_MATH\_NS::Unit & value, float\_t min=0.0f, float\_t max=0.0f, float\_t power=0.1, [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* storage=nullptr) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawFRect**](#function-drawfrect) (const std::array&lt; std::string, 4 &gt; & names, SR\_MATH\_NS::FRect & value, float\_t min=0.0f, float\_t max=0.0f, float\_t power=0.1, [**SR\_HTYPES\_NS::DataStorage**](classSR__HTYPES__NS_1_1DataStorage.md) \* storage=nullptr) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawIVec3Control**](#function-drawivec3control) (const std::string & label, SR\_MATH\_NS::IVector3 & values, int32\_t resetValue=0, float\_t columnWidth=70.0f, int32\_t drag=1, uint32\_t index=0, bool active=true) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawSlider**](#function-drawslider) (const std::string & label, SR\_MATH\_NS::Unit & value, float\_t min=0.0f, float\_t max=0.0f, uint32\_t index=0) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawUVec2Control**](#function-drawuvec2control) (const std::string & label, SR\_MATH\_NS::UVector2 & values, uint32\_t resetValue=0, float\_t columnWidth=70.0f, uint32\_t drag=1, uint32\_t index=0, bool active=true) <br> |
|  void | [**DrawValue**](#function-drawvalue) (const std::string & label, const T & value, uint32\_t index=0) <br> |
|  bool | [**DrawValueControl**](#function-drawvaluecontrol) (const char \* label, T & value, T reset, ImVec2 btnSize, ImVec4 btn, ImVec4 hovered, ImVec4 activeCol, ImFont \* font=nullptr, T drag=static\_cast&lt; T &gt;(0.1f)) <br> |
|  bool | [**DrawValueSlider**](#function-drawvalueslider) (const std::string & label, T & value, T reset, T min, T max, ImVec2 btnSize, ImVec4 btn, ImVec4 hovered, ImVec4 activeCol, ImFont \* font=nullptr, bool active=true) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawVec2Control**](#function-drawvec2control) (const std::string & label, SR\_MATH\_NS::FVector2 & values, float\_t resetValue=0.0f, float\_t columnWidth=70.0f, float\_t drag=0.1) <br> |
|  SR\_MAYBE\_UNUSED bool | [**DrawVec3Control**](#function-drawvec3control) (const std::string & label, SR\_MATH\_NS::FVector3 & values, float\_t resetValue=0.0f, float\_t drag=0.1, float\_t columnWidth=70.0f, uint32\_t index=0, bool active=true) <br> |
|  SR\_MAYBE\_UNUSED void | [**EndForceEnabled**](#function-endforceenabled) (uint32\_t stackSize) <br> |
|  SR\_MAYBE\_UNUSED void | [**EndNodeCombo**](#function-endnodecombo) () <br> |
|  SR\_MAYBE\_UNUSED static void | [**EnumCombo**](#function-enumcombo) (const std::string & label, [**SR\_UTILS\_NS::EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md) \* pReflector, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**SR\_UTILS\_NS::EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md) \*pReflector)&gt; & callback) <br> |
|  SR\_MAYBE\_UNUSED static void | [**EnumCombo**](#function-enumcombo) (const std::string & label, [**SR\_UTILS\_NS::EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md) \* pReflector, const std::optional&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & value, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md))&gt; & callback, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; bool(const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &)&gt; & filter) <br> |
|  SR\_MAYBE\_UNUSED static void | [**EnumCombo**](#function-enumcombo) (const std::string & label, [**SR\_UTILS\_NS::EnumReflector**](classSR__UTILS__NS_1_1EnumReflector.md) \* pReflector, const std::optional&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) &gt; & value, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md))&gt; & callback) <br> |
|  void | [**EnumCombo**](#function-enumcombo) (const std::string & label, T value, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T)&gt; & callback) <br> |
|  void | [**EnumCombo**](#function-enumcombo) (const std::string & label, T value, const [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(T)&gt; & callback, void \* pIdentifier) <br> |
|  SR\_MAYBE\_UNUSED ImGuiDataType\_ | [**GetImGuiDataType**](#function-getimguidatatype) (std::string\_view type) <br> |
|  SR\_MAYBE\_UNUSED ImGuiDataType\_ | [**GetImGuiDataType**](#function-getimguidatatype) (uint64\_t size, bool isSigned, bool isIntegral) <br> |
|  SR\_MAYBE\_UNUSED bool | [**InputInt**](#function-inputint) (const std::string & name, int32\_t & value, int32\_t step=1) <br> |
|  SR\_MAYBE\_UNUSED ImVec4 | [**MakeDisableColor**](#function-makedisablecolor) (ImVec4 color) <br> |
|  SR\_MAYBE\_UNUSED [**ImGuiDataTypeUnion**](unionSR__GRAPH__GUI__NS_1_1ImGuiDataTypeUnion.md) | [**ReadImGuiDataType**](#function-readimguidatatype) (void \* pData, ImGuiDataType\_ type) <br> |
|  SR\_MAYBE\_UNUSED void | [**Text**](#function-text) (const char \* text) <br> |
|  SR\_MAYBE\_UNUSED bool | [**UInputInt32**](#function-uinputint32) (const std::string & name, uint32\_t & value, uint32\_t step=1) <br> |
|  SR\_MAYBE\_UNUSED bool | [**Vec4Null**](#function-vec4null) (const ImVec4 & v1) <br> |
|  SR\_MAYBE\_UNUSED void | [**WriteImGuiDataType**](#function-writeimguidatatype) (void \* pData, ImGuiDataType\_ type, [**ImGuiDataTypeUnion**](unionSR__GRAPH__GUI__NS_1_1ImGuiDataTypeUnion.md) value) <br> |


























## Public Types Documentation




### union ImGuiDataTypeUnion 

```C++

```




<hr>



### typedef WidgetFlagBits 

```C++
typedef uint32_t SR_GRAPH_GUI_NS::WidgetFlagBits;
```




<hr>



### enum WidgetFlags 

```C++
enum SR_GRAPH_GUI_NS::WidgetFlags {
    WIDGET_FLAG_NONE = 1 << 0,
    WIDGET_FLAG_HOVERED = 1 << 1,
    WIDGET_FLAG_FOCUSED = 1 << 2
};
```




<hr>



### typedef WindowFlags 

```C++
typedef ImGuiWindowFlags SR_GRAPH_GUI_NS::WindowFlags;
```




<hr>
## Public Static Attributes Documentation




### variable STYLE\_BOOL\_VALUES 

```C++
const std::unordered_map<std::string, bool ImGuiStyle::*> SR_GRAPH_GUI_NS::STYLE_BOOL_VALUES;
```




<hr>



### variable STYLE\_COLORS 

```C++
const std::unordered_map<std::string, ImGuiCol_> SR_GRAPH_GUI_NS::STYLE_COLORS;
```




<hr>



### variable STYLE\_FLOAT\_VALUES 

```C++
const std::unordered_map<std::string, float ImGuiStyle::*> SR_GRAPH_GUI_NS::STYLE_FLOAT_VALUES;
```




<hr>



### variable STYLE\_SIZE\_VALUES 

```C++
const std::unordered_map<std::string, ImVec2 ImGuiStyle::*> SR_GRAPH_GUI_NS::STYLE_SIZE_VALUES;
```




<hr>
## Public Functions Documentation




### function ButtonBehaviorNoNavFocus 

```C++
bool SR_GRAPH_GUI_NS::ButtonBehaviorNoNavFocus (
    const ImRect & bb,
    ImGuiID id,
    bool * out_hovered,
    bool * out_held,
    ImGuiButtonFlags flags=0
) 
```




<hr>



### function CanCreateLink 

```C++
bool SR_GRAPH_GUI_NS::CanCreateLink (
    Pin * a,
    Pin * b
) 
```




<hr>



### function CheckboxNoNavFocus 

```C++
bool SR_GRAPH_GUI_NS::CheckboxNoNavFocus (
    const char * label,
    bool * v
) 
```




<hr>



### function CreateNode 

```C++
Node * SR_GRAPH_GUI_NS::CreateNode (
    const SR_MATH_NS::FVector2 & pos,
    uint64_t identifier
) 
```




<hr>



### function DrawDataType 

```C++
SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawDataType (
    SR_SRLM_NS::DataType * pData,
    bool * pIsEnum,
    void * pProvider,
    float_t width=0,
    uint32_t deep=0
) 
```




<hr>



### function IsPinsCompatible 

```C++
bool SR_GRAPH_GUI_NS::IsPinsCompatible (
    SR_SRLM_NS::DataTypeClass first,
    SR_SRLM_NS::DataTypeClass second
) 
```




<hr>



### function RadioButton 

```C++
bool SR_GRAPH_GUI_NS::RadioButton (
    const char * label,
    bool active,
    float_t radius=1.f
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS 

```C++
SR_GRAPH_GUI_NS::SR_ENUM_NS_CLASS (
    NodeType,
    None,
    Blueprint,
    Simple,
    Tree,
    Comment,
    Houdini,
    Connector
) 
```




<hr>
## Public Static Functions Documentation




### function BeginForceEnabled 

```C++
static SR_MAYBE_UNUSED uint32_t SR_GRAPH_GUI_NS::BeginForceEnabled () 
```




<hr>



### function BeginNodeCombo 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::BeginNodeCombo (
    const char * label,
    const char * preview_value,
    ImGuiComboFlags flags=0
) 
```




<hr>



### function Button 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::Button (
    const std::string & label,
    ImVec4 color=ImVec4(0, 0, 0, 0),
    ImVec4 hovered=ImVec4(0, 0, 0, 0),
    void * pIdentifier=nullptr
) 
```




<hr>



### function Button 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::Button (
    const std::string & label,
    void * pIdentifier
) 
```




<hr>



### function CalcMaxPopupHeightFromItemCount 

```C++
static SR_MAYBE_UNUSED float SR_GRAPH_GUI_NS::CalcMaxPopupHeightFromItemCount (
    int items_count
) 
```




<hr>



### function CheckBox 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::CheckBox (
    bool & value
) 
```




<hr>



### function CheckBox 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::CheckBox (
    const std::string & name,
    bool & value
) 
```




<hr>



### function ColoredText 

```C++
static SR_MAYBE_UNUSED void SR_GRAPH_GUI_NS::ColoredText (
    const char * text,
    const ImVec4 & color
) 
```




<hr>



### function ColoredText 

```C++
static SR_MAYBE_UNUSED void SR_GRAPH_GUI_NS::ColoredText (
    const std::string & text,
    const ImVec4 & color
) 
```




<hr>



### function DragInt32 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DragInt32 (
    const std::string & name,
    int32_t & value,
    int32_t drag=1
) 
```




<hr>



### function DragUInt32 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DragUInt32 (
    const std::string & name,
    uint32_t & value,
    uint32_t drag=1
) 
```




<hr>



### function DragUnit 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DragUnit (
    const std::string & name,
    SR_MATH_NS::Unit & value,
    float_t drag=0.1f
) 
```




<hr>



### function DrawBVec3Control 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawBVec3Control (
    const std::string & label,
    SR_MATH_NS::BVector3 & values,
    bool resetValue,
    float_t columnWidth=70.0f
) 
```




<hr>



### function DrawColorControl 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawColorControl (
    const std::string & label,
    SR_MATH_NS::FVector4 & values,
    float_t resetValue=0.0f,
    float_t columnWidth=40.0f
) 
```




<hr>



### function DrawEditableSlider 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawEditableSlider (
    const std::string & label,
    SR_MATH_NS::Unit & value,
    float_t min=0.0f,
    float_t max=0.0f,
    float_t power=0.1,
    SR_HTYPES_NS::DataStorage * storage=nullptr
) 
```




<hr>



### function DrawFRect 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawFRect (
    const std::array< std::string, 4 > & names,
    SR_MATH_NS::FRect & value,
    float_t min=0.0f,
    float_t max=0.0f,
    float_t power=0.1,
    SR_HTYPES_NS::DataStorage * storage=nullptr
) 
```




<hr>



### function DrawIVec3Control 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawIVec3Control (
    const std::string & label,
    SR_MATH_NS::IVector3 & values,
    int32_t resetValue=0,
    float_t columnWidth=70.0f,
    int32_t drag=1,
    uint32_t index=0,
    bool active=true
) 
```




<hr>



### function DrawSlider 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawSlider (
    const std::string & label,
    SR_MATH_NS::Unit & value,
    float_t min=0.0f,
    float_t max=0.0f,
    uint32_t index=0
) 
```




<hr>



### function DrawUVec2Control 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawUVec2Control (
    const std::string & label,
    SR_MATH_NS::UVector2 & values,
    uint32_t resetValue=0,
    float_t columnWidth=70.0f,
    uint32_t drag=1,
    uint32_t index=0,
    bool active=true
) 
```




<hr>



### function DrawValue 

```C++
template<typename T>
static void SR_GRAPH_GUI_NS::DrawValue (
    const std::string & label,
    const T & value,
    uint32_t index=0
) 
```




<hr>



### function DrawValueControl 

```C++
template<typename T>
static bool SR_GRAPH_GUI_NS::DrawValueControl (
    const char * label,
    T & value,
    T reset,
    ImVec2 btnSize,
    ImVec4 btn,
    ImVec4 hovered,
    ImVec4 activeCol,
    ImFont * font=nullptr,
    T drag=static_cast< T >(0.1f)
) 
```




<hr>



### function DrawValueSlider 

```C++
template<typename T>
static bool SR_GRAPH_GUI_NS::DrawValueSlider (
    const std::string & label,
    T & value,
    T reset,
    T min,
    T max,
    ImVec2 btnSize,
    ImVec4 btn,
    ImVec4 hovered,
    ImVec4 activeCol,
    ImFont * font=nullptr,
    bool active=true
) 
```




<hr>



### function DrawVec2Control 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawVec2Control (
    const std::string & label,
    SR_MATH_NS::FVector2 & values,
    float_t resetValue=0.0f,
    float_t columnWidth=70.0f,
    float_t drag=0.1
) 
```




<hr>



### function DrawVec3Control 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::DrawVec3Control (
    const std::string & label,
    SR_MATH_NS::FVector3 & values,
    float_t resetValue=0.0f,
    float_t drag=0.1,
    float_t columnWidth=70.0f,
    uint32_t index=0,
    bool active=true
) 
```




<hr>



### function EndForceEnabled 

```C++
static SR_MAYBE_UNUSED void SR_GRAPH_GUI_NS::EndForceEnabled (
    uint32_t stackSize
) 
```




<hr>



### function EndNodeCombo 

```C++
static SR_MAYBE_UNUSED void SR_GRAPH_GUI_NS::EndNodeCombo () 
```




<hr>



### function EnumCombo 

```C++
static SR_MAYBE_UNUSED static void SR_GRAPH_GUI_NS::EnumCombo (
    const std::string & label,
    SR_UTILS_NS::EnumReflector * pReflector,
    const SR_HTYPES_NS::Function < void( SR_UTILS_NS::EnumReflector *pReflector)> & callback
) 
```




<hr>



### function EnumCombo 

```C++
static SR_MAYBE_UNUSED static void SR_GRAPH_GUI_NS::EnumCombo (
    const std::string & label,
    SR_UTILS_NS::EnumReflector * pReflector,
    const std::optional< SR_UTILS_NS::StringAtom > & value,
    const SR_HTYPES_NS::Function < void( SR_UTILS_NS::StringAtom )> & callback,
    const SR_HTYPES_NS::Function < bool(const SR_UTILS_NS::StringAtom &)> & filter
) 
```




<hr>



### function EnumCombo 

```C++
static SR_MAYBE_UNUSED static void SR_GRAPH_GUI_NS::EnumCombo (
    const std::string & label,
    SR_UTILS_NS::EnumReflector * pReflector,
    const std::optional< SR_UTILS_NS::StringAtom > & value,
    const SR_HTYPES_NS::Function < void( SR_UTILS_NS::StringAtom )> & callback
) 
```




<hr>



### function EnumCombo 

```C++
template<typename T>
static void SR_GRAPH_GUI_NS::EnumCombo (
    const std::string & label,
    T value,
    const SR_HTYPES_NS::Function < void(T)> & callback
) 
```




<hr>



### function EnumCombo 

```C++
template<typename T>
static void SR_GRAPH_GUI_NS::EnumCombo (
    const std::string & label,
    T value,
    const SR_HTYPES_NS::Function < void(T)> & callback,
    void * pIdentifier
) 
```




<hr>



### function GetImGuiDataType 

```C++
static SR_MAYBE_UNUSED ImGuiDataType_ SR_GRAPH_GUI_NS::GetImGuiDataType (
    std::string_view type
) 
```




<hr>



### function GetImGuiDataType 

```C++
static SR_MAYBE_UNUSED ImGuiDataType_ SR_GRAPH_GUI_NS::GetImGuiDataType (
    uint64_t size,
    bool isSigned,
    bool isIntegral
) 
```




<hr>



### function InputInt 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::InputInt (
    const std::string & name,
    int32_t & value,
    int32_t step=1
) 
```




<hr>



### function MakeDisableColor 

```C++
static SR_MAYBE_UNUSED ImVec4 SR_GRAPH_GUI_NS::MakeDisableColor (
    ImVec4 color
) 
```




<hr>



### function ReadImGuiDataType 

```C++
static SR_MAYBE_UNUSED ImGuiDataTypeUnion SR_GRAPH_GUI_NS::ReadImGuiDataType (
    void * pData,
    ImGuiDataType_ type
) 
```




<hr>



### function Text 

```C++
static SR_MAYBE_UNUSED void SR_GRAPH_GUI_NS::Text (
    const char * text
) 
```




<hr>



### function UInputInt32 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::UInputInt32 (
    const std::string & name,
    uint32_t & value,
    uint32_t step=1
) 
```




<hr>



### function Vec4Null 

```C++
static SR_MAYBE_UNUSED bool SR_GRAPH_GUI_NS::Vec4Null (
    const ImVec4 & v1
) 
```




<hr>



### function WriteImGuiDataType 

```C++
static SR_MAYBE_UNUSED void SR_GRAPH_GUI_NS::WriteImGuiDataType (
    void * pData,
    ImGuiDataType_ type,
    ImGuiDataTypeUnion value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Editor/Theme.h`

