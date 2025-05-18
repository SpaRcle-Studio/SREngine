

# Class SR\_GRAPH\_UI\_NS::UINode



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_UI\_NS**](namespaceSR__GRAPH__UI__NS.md) **>** [**UINode**](classSR__GRAPH__UI__NS_1_1UINode.md)








Inherits the following classes: SR_UTILS_NS::Node


Inherited by the following classes: [SR\_GRAPH\_UI\_NS::UIControlNode](classSR__GRAPH__UI__NS_1_1UIControlNode.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**UINode**](classSR__GRAPH__UI__NS_1_1UINode.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**CalculateContentSize**](#function-calculatecontentsize) () const = 0<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**GetCamera**](#function-getcamera) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FRect & | [**GetFinalRect**](#function-getfinalrect) () noexcept const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](#function-getmatrix) () noexcept override const<br> |
|  SR\_NODISCARD SR\_UTILS\_NS::ECSNodeType | [**GetNodeType**](#function-getnodetype) () noexcept override const<br> |
|  SR\_NODISCARD RenderScene \* | [**GetRenderScene**](#function-getrenderscene) () const<br> |
| virtual void | [**Layout**](#function-layout) (const SR\_MATH\_NS::FRect & available) = 0<br> |
|  SR\_NODISCARD RenderScene \* | [**TryGetRenderScene**](#function-trygetrenderscene) () const<br> |
|   | [**UINode**](#function-uinode) () <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FRect | [**m\_finalRect**](#variable-m_finalrect)  <br> |
|  [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**m\_matrix**](#variable-m_matrix)  <br> |
|  RenderScene \* | [**m\_renderScene**](#variable-m_renderscene)   = `nullptr`<br> |




















## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_UI_NS::UINode::Ptr =  SR_HTYPES_NS::SharedPtr<UINode>;
```




<hr>
## Public Functions Documentation




### function CalculateContentSize 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector2 SR_GRAPH_UI_NS::UINode::CalculateContentSize () const = 0
```




<hr>



### function GetCamera 

```C++
SR_NODISCARD SR_GTYPES_NS::Camera * SR_GRAPH_UI_NS::UINode::GetCamera () const
```




<hr>



### function GetFinalRect 

```C++
inline SR_NODISCARD const SR_MATH_NS::FRect & SR_GRAPH_UI_NS::UINode::GetFinalRect () noexcept const
```




<hr>



### function GetMatrix 

```C++
SR_NODISCARD const SR_MATH_NS::Matrix4x4 & SR_GRAPH_UI_NS::UINode::GetMatrix () noexcept override const
```




<hr>



### function GetNodeType 

```C++
SR_NODISCARD SR_UTILS_NS::ECSNodeType SR_GRAPH_UI_NS::UINode::GetNodeType () noexcept override const
```




<hr>



### function GetRenderScene 

```C++
SR_NODISCARD RenderScene * SR_GRAPH_UI_NS::UINode::GetRenderScene () const
```




<hr>



### function Layout 

```C++
virtual void SR_GRAPH_UI_NS::UINode::Layout (
    const SR_MATH_NS::FRect & available
) = 0
```




<hr>



### function TryGetRenderScene 

```C++
SR_NODISCARD RenderScene * SR_GRAPH_UI_NS::UINode::TryGetRenderScene () const
```




<hr>



### function UINode 

```C++
SR_GRAPH_UI_NS::UINode::UINode () 
```




<hr>
## Protected Attributes Documentation




### variable m\_finalRect 

```C++
SR_MATH_NS::FRect SR_GRAPH_UI_NS::UINode::m_finalRect;
```




<hr>



### variable m\_matrix 

```C++
SR_MATH_NS::Matrix4x4 SR_GRAPH_UI_NS::UINode::m_matrix;
```




<hr>



### variable m\_renderScene 

```C++
RenderScene* SR_GRAPH_UI_NS::UINode::m_renderScene;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/UI/UINode.h`

