

# Class SR\_GRAPH\_UI\_NS::UIControlNode



[**ClassList**](annotated.md) **>** [**SR\_GRAPH\_UI\_NS**](namespaceSR__GRAPH__UI__NS.md) **>** [**UIControlNode**](classSR__GRAPH__UI__NS_1_1UIControlNode.md)








Inherits the following classes: [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)














## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**UIControlNode**](classSR__GRAPH__UI__NS_1_1UIControlNode.md) &gt; | [**Ptr**](#typedef-ptr)  <br> |


## Public Types inherited from SR_GRAPH_UI_NS::UINode

See [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)

| Type | Name |
| ---: | :--- |
| typedef [**SR\_HTYPES\_NS::SharedPtr**](classSR__HTYPES__NS_1_1SharedPtr.md)&lt; [**UINode**](classSR__GRAPH__UI__NS_1_1UINode.md) &gt; | [**Ptr**](classSR__GRAPH__UI__NS_1_1UINode.md#typedef-ptr)  <br> |






































## Public Functions

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**CalculateContentSize**](#function-calculatecontentsize) () override const<br> |
|  SR\_NODISCARD const [**UILayout**](structSR__GRAPH__UI__NS_1_1UILayout.md) & | [**GetLayout**](#function-getlayout-12) () noexcept const<br> |
|  SR\_NODISCARD [**UILayout**](structSR__GRAPH__UI__NS_1_1UILayout.md) & | [**GetLayout**](#function-getlayout-22) () noexcept<br> |
|  SR\_NODISCARD SR\_UTILS\_NS::ECSNodeType | [**GetNodeType**](#function-getnodetype) () noexcept override const<br> |
| virtual void | [**Layout**](#function-layout) (const SR\_MATH\_NS::FRect & available) override<br> |
| virtual void | [**Prepare**](#function-prepare) (uint64\_t & priority) override<br> |


## Public Functions inherited from SR_GRAPH_UI_NS::UINode

See [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)

| Type | Name |
| ---: | :--- |
| virtual SR\_NODISCARD SR\_MATH\_NS::FVector2 | [**CalculateContentSize**](classSR__GRAPH__UI__NS_1_1UINode.md#function-calculatecontentsize) () const = 0<br> |
| virtual void | [**Compile**](classSR__GRAPH__UI__NS_1_1UINode.md#function-compile) () <br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**GetCamera**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getcamera) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FRect & | [**GetFinalRect**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getfinalrect) () noexcept const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getmatrix) () noexcept override const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector4 | [**GetNDCVector**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getndcvector) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetNodePriority**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getnodepriority) () noexcept override const<br> |
|  SR\_NODISCARD SR\_UTILS\_NS::ECSNodeType | [**GetNodeType**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getnodetype) () noexcept override const<br> |
|  SR\_NODISCARD RenderScene \* | [**GetRenderScene**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getrenderscene) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector2 & | [**GetViewportSize**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getviewportsize) () noexcept const<br> |
| virtual void | [**Layout**](classSR__GRAPH__UI__NS_1_1UINode.md#function-layout) (const SR\_MATH\_NS::FRect & available) = 0<br> |
|  void | [**OnParentChanged**](classSR__GRAPH__UI__NS_1_1UINode.md#function-onparentchanged) (const SR\_UTILS\_NS::SceneObject::Ptr & pOldParent) override<br> |
| virtual void | [**Prepare**](classSR__GRAPH__UI__NS_1_1UINode.md#function-prepare) (uint64\_t & priority) <br> |
|  void | [**SetViewportSize**](classSR__GRAPH__UI__NS_1_1UINode.md#function-setviewportsize) (const SR\_MATH\_NS::FVector2 & size) noexcept<br> |
|  SR\_NODISCARD RenderScene \* | [**TryGetRenderScene**](classSR__GRAPH__UI__NS_1_1UINode.md#function-trygetrenderscene) () const<br> |
|   | [**UINode**](classSR__GRAPH__UI__NS_1_1UINode.md#function-uinode) () <br> |
|   | [**~UINode**](classSR__GRAPH__UI__NS_1_1UINode.md#function-uinode) () override<br> |
















## Protected Attributes inherited from SR_GRAPH_UI_NS::UINode

See [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FRect | [**m\_finalRect**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_finalrect)  <br> |
|  bool | [**m\_hasParent**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_hasparent)   = `false`<br> |
|  YGNode \* | [**m\_implNode**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_implnode)   = `nullptr`<br> |
|  [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**m\_matrix**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_matrix)  <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**m\_parentName**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_parentname)  <br> |
|  uint64\_t | [**m\_priority**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_priority)   = `0`<br> |
|  RenderScene \* | [**m\_renderScene**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_renderscene)   = `nullptr`<br> |
|  SR\_MATH\_NS::FVector2 | [**m\_viewportSize**](classSR__GRAPH__UI__NS_1_1UINode.md#variable-m_viewportsize)  <br> |
































## Protected Functions inherited from SR_GRAPH_UI_NS::UINode

See [SR\_GRAPH\_UI\_NS::UINode](classSR__GRAPH__UI__NS_1_1UINode.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD YGNode \* | [**GetYGNode**](classSR__GRAPH__UI__NS_1_1UINode.md#function-getygnode) () noexcept const<br> |






## Public Types Documentation




### typedef Ptr 

```C++
using SR_GRAPH_UI_NS::UIControlNode::Ptr =  SR_HTYPES_NS::SharedPtr<UIControlNode>;
```




<hr>
## Public Functions Documentation




### function CalculateContentSize 

```C++
virtual SR_NODISCARD SR_MATH_NS::FVector2 SR_GRAPH_UI_NS::UIControlNode::CalculateContentSize () override const
```



Implements [*SR\_GRAPH\_UI\_NS::UINode::CalculateContentSize*](classSR__GRAPH__UI__NS_1_1UINode.md#function-calculatecontentsize)


<hr>



### function GetLayout [1/2]

```C++
SR_NODISCARD const UILayout & SR_GRAPH_UI_NS::UIControlNode::GetLayout () noexcept const
```




<hr>



### function GetLayout [2/2]

```C++
SR_NODISCARD UILayout & SR_GRAPH_UI_NS::UIControlNode::GetLayout () noexcept
```




<hr>



### function GetNodeType 

```C++
SR_NODISCARD SR_UTILS_NS::ECSNodeType SR_GRAPH_UI_NS::UIControlNode::GetNodeType () noexcept override const
```




<hr>



### function Layout 

```C++
virtual void SR_GRAPH_UI_NS::UIControlNode::Layout (
    const SR_MATH_NS::FRect & available
) override
```



Implements [*SR\_GRAPH\_UI\_NS::UINode::Layout*](classSR__GRAPH__UI__NS_1_1UINode.md#function-layout)


<hr>



### function Prepare 

```C++
virtual void SR_GRAPH_UI_NS::UIControlNode::Prepare (
    uint64_t & priority
) override
```



Implements [*SR\_GRAPH\_UI\_NS::UINode::Prepare*](classSR__GRAPH__UI__NS_1_1UINode.md#function-prepare)


<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/UI/UIControlNode.h`

