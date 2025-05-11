

# Class SR\_GRAPH\_GUI\_NS::MenuItemSubWidget



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_GUI\_NS**](namespaceSR__GRAPH__GUI__NS.md) **>** [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::Function**](classSR__HTYPES__NS_1_1Function.md)&lt; void(const [**DrawPopupContext**](structSR__GRAPH__GUI__NS_1_1DrawPopupContext.md) &context)&gt; | [**Action**](#typedef-action)  <br> |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**PopupItemSubWidget**](classSR__GRAPH__GUI__NS_1_1PopupItemSubWidget.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |








































## Public Functions

| Type | Name |
| ---: | :--- |
|  [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md) & | [**AddMenu**](#function-addmenu) (const std::string & name) <br> |
|  void | [**Draw**](#function-draw) (const [**DrawPopupContext**](structSR__GRAPH__GUI__NS_1_1DrawPopupContext.md) & context) <br> |
|  SR\_NODISCARD const std::string & | [**GetName**](#function-getname) () noexcept const<br> |
|   | [**MenuItemSubWidget**](#function-menuitemsubwidget-12) () = default<br> |
|   | [**MenuItemSubWidget**](#function-menuitemsubwidget-22) (std::string name) <br> |
|  [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md) & | [**SetAction**](#function-setaction) (Action action) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |














## Protected Attributes

| Type | Name |
| ---: | :--- |
|  Action | [**m\_action**](#variable-m_action)  <br> |
|  std::vector&lt; [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**MenuItemSubWidget**](classSR__GRAPH__GUI__NS_1_1MenuItemSubWidget.md) &gt; &gt; | [**m\_menuItems**](#variable-m_menuitems)  <br> |
|  std::string | [**m\_name**](#variable-m_name)  <br> |


































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |






## Public Types Documentation




### typedef Action 

```C++
using SR_GRAPH_GUI_NS::MenuItemSubWidget::Action =  SR_HTYPES_NS::Function<void(const DrawPopupContext& context)>;
```




<hr>



### typedef Ptr 

```C++
using SR_GRAPH_GUI_NS::MenuItemSubWidget::Ptr =  SR_HTYPES_NS::SharedPtr<PopupItemSubWidget>;
```




<hr>
## Public Functions Documentation




### function AddMenu 

```C++
MenuItemSubWidget & SR_GRAPH_GUI_NS::MenuItemSubWidget::AddMenu (
    const std::string & name
) 
```




<hr>



### function Draw 

```C++
void SR_GRAPH_GUI_NS::MenuItemSubWidget::Draw (
    const DrawPopupContext & context
) 
```




<hr>



### function GetName 

```C++
inline SR_NODISCARD const std::string & SR_GRAPH_GUI_NS::MenuItemSubWidget::GetName () noexcept const
```




<hr>



### function MenuItemSubWidget [1/2]

```C++
SR_GRAPH_GUI_NS::MenuItemSubWidget::MenuItemSubWidget () = default
```




<hr>



### function MenuItemSubWidget [2/2]

```C++
inline explicit SR_GRAPH_GUI_NS::MenuItemSubWidget::MenuItemSubWidget (
    std::string name
) 
```




<hr>



### function SetAction 

```C++
MenuItemSubWidget & SR_GRAPH_GUI_NS::MenuItemSubWidget::SetAction (
    Action action
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_action 

```C++
Action SR_GRAPH_GUI_NS::MenuItemSubWidget::m_action;
```




<hr>



### variable m\_menuItems 

```C++
std::vector<SR_HTYPES_NS::SharedPtr<MenuItemSubWidget> > SR_GRAPH_GUI_NS::MenuItemSubWidget::m_menuItems;
```




<hr>



### variable m\_name 

```C++
std::string SR_GRAPH_GUI_NS::MenuItemSubWidget::m_name;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/GUI/PopupMenu.h`

