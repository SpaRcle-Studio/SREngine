

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
| typedef uint32\_t | [**WidgetFlagBits**](#typedef-widgetflagbits)  <br> |
| enum uint32\_t | [**WidgetFlags**](#enum-widgetflags)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**CanCreateLink**](#function-cancreatelink) (Pin \* a, Pin \* b) <br> |
|  [**Node**](classSR__GRAPH__GUI__NS_1_1Node.md) \* | [**CreateNode**](#function-createnode) (const SR\_MATH\_NS::FVector2 & pos, uint64\_t identifier) <br> |
|  bool | [**IsPinsCompatible**](#function-ispinscompatible) (SR\_SRLM\_NS::DataTypeClass first, SR\_SRLM\_NS::DataTypeClass second) <br> |
|  bool | [**RadioButton**](#function-radiobutton) (const char \* label, bool active, float\_t radius=1.f) <br> |
|   | [**SR\_ENUM\_NS\_CLASS**](#function-sr_enum_ns_class) (NodeType, None, Blueprint, Simple, Tree, Comment, Houdini, Connector) <br> |
|   | [**SR\_ENUM\_NS\_STRUCT\_T**](#function-sr_enum_ns_struct_t) (WindowFlags, uint32\_t, None=0, NoTitleBar=1&lt;&lt; 0, NoResize=1&lt;&lt; 1, NoMove=1&lt;&lt; 2, NoScrollbar=1&lt;&lt; 3, NoScrollWithMouse=1&lt;&lt; 4, NoCollapse=1&lt;&lt; 5, AlwaysAutoResize=1&lt;&lt; 6, NoBackground=1&lt;&lt; 7, NoSavedSettings=1&lt;&lt; 8, NoMouseInputs=1&lt;&lt; 9, MenuBar=1&lt;&lt; 10, HorizontalScrollbar=1&lt;&lt; 11, NoFocusOnAppearing=1&lt;&lt; 12, NoBringToFrontOnFocus=1&lt;&lt; 13, AlwaysVerticalScrollbar=1&lt;&lt; 14, AlwaysHorizontalScrollbar=1&lt;&lt; 15, AlwaysUseWindowPadding=1&lt;&lt; 16, NoNavInputs=1&lt;&lt; 18, NoNavFocus=1&lt;&lt; 19, UnsavedDocument=1&lt;&lt; 20, NoDocking=1&lt;&lt; 21, NoNav=NoNavInputs\|NoNavFocus, NoDecoration=NoTitleBar\|NoResize\|NoScrollbar\|NoCollapse, NoInputs=NoMouseInputs\|NoNavInputs\|NoNavFocus, NavFlattened=1&lt;&lt; 23, ChildWindow=1&lt;&lt; 24, Tooltip=1&lt;&lt; 25, Popup=1&lt;&lt; 26, Modal=1&lt;&lt; 27, ChildMenu=1&lt;&lt; 28, DockNodeHost=1&lt;&lt; 29) <br> |




























## Public Types Documentation




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
## Public Functions Documentation




### function CanCreateLink 

```C++
bool SR_GRAPH_GUI_NS::CanCreateLink (
    Pin * a,
    Pin * b
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



### function SR\_ENUM\_NS\_STRUCT\_T 

```C++
SR_GRAPH_GUI_NS::SR_ENUM_NS_STRUCT_T (
    WindowFlags,
    uint32_t,
    None=0,
    NoTitleBar=1<< 0,
    NoResize=1<< 1,
    NoMove=1<< 2,
    NoScrollbar=1<< 3,
    NoScrollWithMouse=1<< 4,
    NoCollapse=1<< 5,
    AlwaysAutoResize=1<< 6,
    NoBackground=1<< 7,
    NoSavedSettings=1<< 8,
    NoMouseInputs=1<< 9,
    MenuBar=1<< 10,
    HorizontalScrollbar=1<< 11,
    NoFocusOnAppearing=1<< 12,
    NoBringToFrontOnFocus=1<< 13,
    AlwaysVerticalScrollbar=1<< 14,
    AlwaysHorizontalScrollbar=1<< 15,
    AlwaysUseWindowPadding=1<< 16,
    NoNavInputs=1<< 18,
    NoNavFocus=1<< 19,
    UnsavedDocument=1<< 20,
    NoDocking=1<< 21,
    NoNav=NoNavInputs|NoNavFocus,
    NoDecoration=NoTitleBar|NoResize|NoScrollbar|NoCollapse,
    NoInputs=NoMouseInputs|NoNavInputs|NoNavFocus,
    NavFlattened=1<< 23,
    ChildWindow=1<< 24,
    Tooltip=1<< 25,
    Popup=1<< 26,
    Modal=1<< 27,
    ChildMenu=1<< 28,
    DockNodeHost=1<< 29
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/Editor/Theme.h`

