

# Class SR\_GRAPH\_GUI\_NS::PopupItemSubWidget



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_GUI\_NS**](namespaceSR__GRAPH__GUI__NS.md) **>** [**PopupItemSubWidget**](classSR__GRAPH__GUI__NS_1_1PopupItemSubWidget.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**PopupItemSubWidget**](classSR__GRAPH__GUI__NS_1_1PopupItemSubWidget.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md) & | [**AddMenu**](#function-addmenu-12) (std::string name) <br> |
|  [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md) & | [**AddMenu**](#function-addmenu-22) (const std::vector&lt; std::string &gt; & category) <br> |
|  void | [**Draw**](#function-draw) (const [**DrawPopupContext**](structSR__GRAPH__GUI__NS_1_1DrawPopupContext.md) & context) <br> |
|   | [**PopupItemSubWidget**](#function-popupitemsubwidget) (std::string name) <br> |
|  void | [**SetName**](#function-setname) (std::string name) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md) &gt; &gt; | [**m\_menuItems**](#variable-m_menuitems)  <br> |
|  std::string | [**m\_name**](#variable-m_name)  <br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |






## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_GUI_NS::PopupItemSubWidget::Ptr =  SR_HTYPES_NS::SharedPtr<PopupItemSubWidget>;
```




<hr>
## Public Functions Documentation




### function AddMenu [1/2]

```C++
MenuItemSubWidget & SR_GRAPH_GUI_NS::PopupItemSubWidget::AddMenu (
    std::string name
) 
```




<hr>



### function AddMenu [2/2]

```C++
MenuItemSubWidget & SR_GRAPH_GUI_NS::PopupItemSubWidget::AddMenu (
    const std::vector< std::string > & category
) 
```




<hr>



### function Draw 

```C++
void SR_GRAPH_GUI_NS::PopupItemSubWidget::Draw (
    const DrawPopupContext & context
) 
```




<hr>



### function PopupItemSubWidget 

```C++
inline explicit SR_GRAPH_GUI_NS::PopupItemSubWidget::PopupItemSubWidget (
    std::string name
) 
```




<hr>



### function SetName 

```C++
inline void SR_GRAPH_GUI_NS::PopupItemSubWidget::SetName (
    std::string name
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_menuItems 

```C++
std::vector<SR_HTYPES_NS::SharedPtr<MenuItemSubWidget> > SR_GRAPH_GUI_NS::PopupItemSubWidget::m_menuItems;
```




<hr>



### variable m\_name 

```C++
std::string SR_GRAPH_GUI_NS::PopupItemSubWidget::m_name;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/GUI/PopupMenu.h`

