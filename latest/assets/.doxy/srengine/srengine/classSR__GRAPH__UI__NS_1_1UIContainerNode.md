

# Class SR\_GRAPH\_UI\_NS::UIContainerNode



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_UI\_NS**](namespaceSR__GRAPH__UI__NS.md) **>** [**UIContainerNode**](classSR__GRAPH__UI__NS_1_1UIContainerNode.md)








Inherits the following classes: [SR\_GRAPH\_UI\_NS::UIControlNode](classSR__GRAPH__UI__NS_1_1UIControlNode.md)


Inherited by the following classes: [SR\_GRAPH\_UI\_NS::UIHBoxContainerNode](classSR__GRAPH__UI__NS_1_1UIHBoxContainerNode.md),  [SR\_GRAPH\_UI\_NS::UIVBoxContainerNode](classSR__GRAPH__UI__NS_1_1UIVBoxContainerNode.md),  [SR\_GRAPH\_UI\_NS::UIViewportNode](classSR__GRAPH__UI__NS_1_1UIViewportNode.md)












## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**UIContainerNode**](classSR__GRAPH__UI__NS_1_1UIContainerNode.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_GRAPH_UI_NS::UIControlNode

See [SR\_GRAPH\_UI\_NS::UIControlNode](classSR__GRAPH__UI__NS_1_1UIControlNode.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**UIControlNode**](classSR__GRAPH__UI__NS_1_1UIControlNode.md) &gt; | [**Ptr**](classSR__GRAPH__UI__NS_1_1UIControlNode.md#typedef-ptr)  <br> |


## Public Types inherited from SR_GRAPH_UI_NS::UINode

See [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**UINode**](classSR__GRAPH__UI__NS_1_1UINode.md) &gt; | [**Ptr**](classSR__GRAPH__UI__NS_1_1UINode.md#typedef-ptr)  <br> |
























































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD SR\_UTILS\_NS::ECSNodeType | [**GetNodeType**](#function-getnodetype) () noexcept override const<br> |
| virtual void | [**Layout**](#function-layout) (const SR\_MATH\_NS::FRect & available) override<br> |


## Public Functions inherited from SR_GRAPH_UI_NS::UIControlNode

See [SR\_GRAPH\_UI\_NS::UIControlNode](classSR__GRAPH__UI__NS_1_1UIControlNode.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**CalculateContentSize**](classSR__GRAPH__UI__NS_1_1UIControlNode.md#function-calculatecontentsize) () override const<br> |
|  SR\_NODISCARD const UILayout & | [**GetLayout**](classSR__GRAPH__UI__NS_1_1UIControlNode.md#function-getlayout) () noexcept const<br> |
|  SR\_NODISCARD SR\_UTILS\_NS::ECSNodeType | [**GetNodeType**](classSR__GRAPH__UI__NS_1_1UIControlNode.md#function-getnodetype) () noexcept override const<br> |
| virtual void | [**Layout**](classSR__GRAPH__UI__NS_1_1UIControlNode.md#function-layout) (const SR\_MATH\_NS::FRect & available) override<br> |


## Public Functions inherited from SR_GRAPH_UI_NS::UINode

See [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**CalculateContentSize**](classSR__GRAPH__UI__NS_1_1UINode.md#function-calculatecontentsize) () const = 0<br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**GetCamera**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getcamera) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FRect & | [**GetFinalRect**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getfinalrect) () noexcept const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getmatrix) () noexcept override const<br> |
|  SR\_NODISCARD SR\_UTILS\_NS::ECSNodeType | [**GetNodeType**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getnodetype) () noexcept override const<br> |
|  SR\_NODISCARD RenderScene \* | [**GetRenderScene**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getrenderscene) () const<br> |
| virtual void | [**Layout**](classSR__GRAPH__UI__NS_1_1UINode.md#function-layout) (const SR\_MATH\_NS::FRect & available) = 0<br> |
|  SR\_NODISCARD RenderScene \* | [**TryGetRenderScene**](classSR__GRAPH__UI__NS_1_1UINode.md#function-trygetrenderscene) () const<br> |
|   | [**UINode**](classSR__GRAPH__UI__NS_1_1UINode.md#function-uinode) () <br> |
























## Protected Attributes inherited from SR_GRAPH_UI_NS::UINode

See [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FRect | [**m\_finalRect**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_finalrect)  <br> |
|  [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**m\_matrix**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_matrix)  <br> |
|  RenderScene \* | [**m\_renderScene**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_renderscene)   = `nullptr`<br> |
























































## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_UI_NS::UIContainerNode::Ptr =  SR_HTYPES_NS::SharedPtr<UIContainerNode>;
```




<hr>
## Public Functions Documentation




### function GetNodeType 

```C++
SR_NODISCARD SR_UTILS_NS::ECSNodeType SR_GRAPH_UI_NS::UIContainerNode::GetNodeType () noexcept override const
```




<hr>



### function Layout 

```C++
virtual void SR_GRAPH_UI_NS::UIContainerNode::Layout (
    const SR_MATH_NS::FRect & available
) override
```



Implements [*SR\_GRAPH\_UI\_NS::UINode::Layout*](classSR__GRAPH__UI__NS_1_1UINode.md#function-layout)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/UI/UIContainerNode.h`

