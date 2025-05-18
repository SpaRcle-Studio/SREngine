

# Namespace SR\_GRAPH\_UI\_NS



[**Namespace List**](namespaces.md) **>** [**SR\_GRAPH\_UI\_NS**](namespaceSR__GRAPH__UI__NS.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**Canvas**](classSR__GRAPH__UI__NS_1_1Canvas.md) <br> |
| class | [**Gizmo**](classSR__GRAPH__UI__NS_1_1Gizmo.md) <br> |
| class | [**UICanvasComponent**](classSR__GRAPH__UI__NS_1_1UICanvasComponent.md) <br> |
| class | [**UIContainerNode**](classSR__GRAPH__UI__NS_1_1UIContainerNode.md) <br> |
| class | [**UIControlNode**](classSR__GRAPH__UI__NS_1_1UIControlNode.md) <br>_подстраивается под содержимое (например, текст)_  |
| class | [**UIHBoxContainerNode**](classSR__GRAPH__UI__NS_1_1UIHBoxContainerNode.md) <br> |
| class | [**UINode**](classSR__GRAPH__UI__NS_1_1UINode.md) <br> |
| class | [**UISizeComponent**](classSR__GRAPH__UI__NS_1_1UISizeComponent.md) <br> |
| class | [**UIVBoxContainerNode**](classSR__GRAPH__UI__NS_1_1UIVBoxContainerNode.md) <br> |
| class | [**UIViewportNode**](classSR__GRAPH__UI__NS_1_1UIViewportNode.md) <br> |
| class | [**UIWindow**](classSR__GRAPH__UI__NS_1_1UIWindow.md) <br> |






## Public Attributes

| Type | Name |
| ---: | :--- |
|   | [**Content**](#variable-content)  <br>_размер в % от доступного пространства_  |
|   | [**Fixed**](#variable-fixed)  <br> |
|   | [**Percent**](#variable-percent)  <br>_размер задаётся явно_  |
|   | [**uint8\_t**](#variable-uint8_t)  <br> |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (GizmoMode, uint8\_t, Local, Global) <br> |
|   | [**SR\_ENUM\_NS\_CLASS\_T**](#function-sr_enum_ns_class_t) (UIPositionType, uint8\_t, Relative, Absolute) <br> |
|   | [**SR\_ENUM\_NS\_STRUCT\_T**](#function-sr_enum_ns_struct_t) (GizmoOperation, uint64\_t, None=0, Center=1&lt;&lt; 0, Alternative=1&lt;&lt; 1, X=1&lt;&lt; 2, Y=1&lt;&lt; 3, Z=1&lt;&lt; 4, Translate=1&lt;&lt; 5, Rotate=1&lt;&lt; 6, Scale=1&lt;&lt; 7, Bounds=1&lt;&lt; 8, Space2D=1&lt;&lt; 9, Rotate2D=Space2D\|Rotate\|Z, TranslateX=X\|Translate, TranslateY=Y\|Translate, TranslateZ=Z\|Translate, TranslateAltX=Y\|Z\|Translate\|Alternative, TranslateAltY=X\|Z\|Translate\|Alternative, TranslateAltZ=X\|Y\|Translate\|Alternative, TranslateCenter=Translate\|Center, TranslateAll=X\|Y\|Z\|Translate\|Center\|Alternative, RotateX=X\|Rotate, RotateY=Y\|Rotate, RotateZ=Z\|Rotate, RotateCenter=Rotate\|Center, RotateAll=X\|Y\|Z\|Rotate\|Center, ScaleX=X\|Scale, ScaleY=Y\|Scale, ScaleZ=Z\|Scale, ScaleCenter=Scale\|Center, ScaleAll=X\|Y\|Z\|Scale\|Center, BoundsX=X\|Bounds, BoundsY=Y\|Bounds, BoundsZ=Z\|Bounds, Universal=TranslateAll\|RotateAll\|ScaleAll) <br> |
|   | [**SR\_ENUM\_NS\_STRUCT\_T**](#function-sr_enum_ns_struct_t) (UIWindowAttributes, uint32\_t, None=0, Dockable=1&lt;&lt; 0, Resizable=1&lt;&lt; 1, Movable=1&lt;&lt; 2, Closable=1&lt;&lt; 3, Minimizable=1&lt;&lt; 4, Maximizable=1&lt;&lt; 5) <br> |




























## Public Attributes Documentation




### variable Content 

_размер в % от доступного пространства_ 
```C++
SR_GRAPH_UI_NS::Content;
```




<hr>



### variable Fixed 

```C++
SR_GRAPH_UI_NS::Fixed;
```




<hr>



### variable Percent 

_размер задаётся явно_ 
```C++
SR_GRAPH_UI_NS::Percent;
```




<hr>



### variable uint8\_t 

```C++
SR_GRAPH_UI_NS::uint8_t;
```




<hr>
## Public Functions Documentation




### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_GRAPH_UI_NS::SR_ENUM_NS_CLASS_T (
    GizmoMode,
    uint8_t,
    Local,
    Global
) 
```




<hr>



### function SR\_ENUM\_NS\_CLASS\_T 

```C++
SR_GRAPH_UI_NS::SR_ENUM_NS_CLASS_T (
    UIPositionType,
    uint8_t,
    Relative,
    Absolute
) 
```




<hr>



### function SR\_ENUM\_NS\_STRUCT\_T 

```C++
SR_GRAPH_UI_NS::SR_ENUM_NS_STRUCT_T (
    GizmoOperation,
    uint64_t,
    None=0,
    Center=1<< 0,
    Alternative=1<< 1,
    X=1<< 2,
    Y=1<< 3,
    Z=1<< 4,
    Translate=1<< 5,
    Rotate=1<< 6,
    Scale=1<< 7,
    Bounds=1<< 8,
    Space2D=1<< 9,
    Rotate2D=Space2D|Rotate|Z,
    TranslateX=X|Translate,
    TranslateY=Y|Translate,
    TranslateZ=Z|Translate,
    TranslateAltX=Y|Z|Translate|Alternative,
    TranslateAltY=X|Z|Translate|Alternative,
    TranslateAltZ=X|Y|Translate|Alternative,
    TranslateCenter=Translate|Center,
    TranslateAll=X|Y|Z|Translate|Center|Alternative,
    RotateX=X|Rotate,
    RotateY=Y|Rotate,
    RotateZ=Z|Rotate,
    RotateCenter=Rotate|Center,
    RotateAll=X|Y|Z|Rotate|Center,
    ScaleX=X|Scale,
    ScaleY=Y|Scale,
    ScaleZ=Z|Scale,
    ScaleCenter=Scale|Center,
    ScaleAll=X|Y|Z|Scale|Center,
    BoundsX=X|Bounds,
    BoundsY=Y|Bounds,
    BoundsZ=Z|Bounds,
    Universal=TranslateAll|RotateAll|ScaleAll
) 
```




<hr>



### function SR\_ENUM\_NS\_STRUCT\_T 

```C++
SR_GRAPH_UI_NS::SR_ENUM_NS_STRUCT_T (
    UIWindowAttributes,
    uint32_t,
    None=0,
    Dockable=1<< 0,
    Resizable=1<< 1,
    Movable=1<< 2,
    Closable=1<< 3,
    Minimizable=1<< 4,
    Maximizable=1<< 5
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/inc/Engine/GUI/SceneTools.h`

