

# Namespace SR\_GRAPH\_NS::GUI



[**Namespace List**](namespaces.md) **>** [**SR\_GRAPH\_NS**](namespaceSR__GRAPH__NS.md) **>** [**GUI**](namespaceSR__GRAPH__NS_1_1GUI.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**GlobalWidgetManager**](classSR__GRAPH__NS_1_1GUI_1_1GlobalWidgetManager.md) <br> |
| class | [**Link**](classSR__GRAPH__NS_1_1GUI_1_1Link.md) <br> |
| class | [**MessageBoxWidget**](classSR__GRAPH__NS_1_1GUI_1_1MessageBoxWidget.md) <br> |
| class | [**NodeBuilder**](classSR__GRAPH__NS_1_1GUI_1_1NodeBuilder.md) <br> |
| class | [**NodeManager**](classSR__GRAPH__NS_1_1GUI_1_1NodeManager.md) <br> |
| class | [**Pin**](classSR__GRAPH__NS_1_1GUI_1_1Pin.md) <br> |
| class | [**ViewportsTableManager**](classSR__GRAPH__NS_1_1GUI_1_1ViewportsTableManager.md) <br> |
| class | [**WidgetManager**](classSR__GRAPH__NS_1_1GUI_1_1WidgetManager.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef uint32\_t | [**MessageBoxButton**](#typedef-messageboxbutton)  <br> |
| enum  | [**MessageBoxButtonBits**](#enum-messageboxbuttonbits)  <br> |
| enum uint8\_t | [**MessageBoxType**](#enum-messageboxtype)  <br> |
| typedef ska::flat\_hash\_map&lt; void \*, Widget \* &gt; | [**ViewportsTable**](#typedef-viewportstable)  <br> |
| typedef ska::flat\_hash\_map&lt; std::string, Widget \* &gt; | [**Widgets**](#typedef-widgets)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SR\_ENUM\_NS\_CLASS**](#function-sr_enum_ns_class) (IconType, Flow, Circle, Square, Grid, RoundSquare, Diamond) <br> |
|   | [**SR\_ENUM\_NS\_CLASS**](#function-sr_enum_ns_class) (PinKind, None, Output, Input) <br> |




























## Public Types Documentation




### typedef MessageBoxButton 

```C++
typedef uint32_t SR_GRAPH_NS::GUI::MessageBoxButton;
```




<hr>



### enum MessageBoxButtonBits 

```C++
enum SR_GRAPH_NS::GUI::MessageBoxButtonBits {
    MESSAGE_BOX_CLOSE = 0,
    MESSAGE_BOX_OK = 1 << 0,
    MESSAGE_BOX_CONTINUE = 1 << 1,
    MESSAGE_BOX_CANCEL = 1 << 2
};
```




<hr>



### enum MessageBoxType 

```C++
enum SR_GRAPH_NS::GUI::MessageBoxType {
    Info,
    Warn,
    Error
};
```




<hr>



### typedef ViewportsTable 

```C++
typedef ska::flat_hash_map<void*, Widget*> SR_GRAPH_NS::GUI::ViewportsTable;
```




<hr>



### typedef Widgets 

```C++
typedef ska::flat_hash_map<std::string, Widget*> SR_GRAPH_NS::GUI::Widgets;
```




<hr>
## Public Functions Documentation




### function SR\_ENUM\_NS\_CLASS 

```C++
SR_GRAPH_NS::GUI::SR_ENUM_NS_CLASS (
    IconType,
    Flow,
    Circle,
    Square,
    Grid,
    RoundSquare,
    Diamond
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS 

```C++
SR_GRAPH_NS::GUI::SR_ENUM_NS_CLASS (
    PinKind,
    None,
    Output,
    Input
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/inc/Core/GUI/VisualScriptEditor.h`

