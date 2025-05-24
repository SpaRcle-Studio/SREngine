

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
| virtual void | [**Compile**](#function-compile) () <br> |
|  SR\_NODISCARD [**SR\_GTYPES\_NS::Camera**](classSR__GTYPES__NS_1_1Camera.md) \* | [**GetCamera**](#function-getcamera) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FRect & | [**GetFinalRect**](#function-getfinalrect) () noexcept const<br> |
|  SR\_NODISCARD const [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) & | [**GetMatrix**](#function-getmatrix) () noexcept override const<br> |
|  SR\_NODISCARD SR\_MATH\_NS::FVector4 | [**GetNDCVector**](#function-getndcvector) () noexcept const<br> |
|  SR\_NODISCARD uint64\_t | [**GetNodePriority**](#function-getnodepriority) () noexcept override const<br> |
|  SR\_NODISCARD SR\_UTILS\_NS::ECSNodeType | [**GetNodeType**](#function-getnodetype) () noexcept override const<br> |
|  SR\_NODISCARD RenderScene \* | [**GetRenderScene**](#function-getrenderscene) () const<br> |
|  SR\_NODISCARD const SR\_MATH\_NS::FVector2 & | [**GetViewportSize**](#function-getviewportsize) () noexcept const<br> |
| virtual void | [**Layout**](#function-layout) (const SR\_MATH\_NS::FRect & available) = 0<br> |
|  void | [**OnParentChanged**](#function-onparentchanged) (const SR\_UTILS\_NS::SceneObject::Ptr & pOldParent) override<br> |
| virtual void | [**Prepare**](#function-prepare) (uint64\_t & priority) <br> |
|  void | [**SetViewportSize**](#function-setviewportsize) (const SR\_MATH\_NS::FVector2 & size) noexcept<br> |
|  SR\_NODISCARD RenderScene \* | [**TryGetRenderScene**](#function-trygetrenderscene) () const<br> |
|   | [**UINode**](#function-uinode) () <br> |
|   | [**~UINode**](#function-uinode) () override<br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  SR\_MATH\_NS::FRect | [**m\_finalRect**](#variable-m_finalrect)  <br> |
|  bool | [**m\_hasParent**](#variable-m_hasparent)   = `false`<br> |
|  YGNode \* | [**m\_implNode**](#variable-m_implnode)   = `nullptr`<br> |
|  [**SR\_MATH\_NS::Matrix4x4**](classSR__MATH__NS_1_1Matrix4x4.md) | [**m\_matrix**](#variable-m_matrix)  <br> |
|  [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) | [**m\_parentName**](#variable-m_parentname)  <br> |
|  uint64\_t | [**m\_priority**](#variable-m_priority)   = `0`<br> |
|  RenderScene \* | [**m\_renderScene**](#variable-m_renderscene)   = `nullptr`<br> |
|  SR\_MATH\_NS::FVector2 | [**m\_viewportSize**](#variable-m_viewportsize)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD YGNode \* | [**GetYGNode**](#function-getygnode) () noexcept const<br> |




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



### function Compile 

```C++
virtual void SR_GRAPH_UI_NS::UINode::Compile () 
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



### function GetNDCVector 

```C++
SR_NODISCARD SR_MATH_NS::FVector4 SR_GRAPH_UI_NS::UINode::GetNDCVector () noexcept const
```




<hr>



### function GetNodePriority 

```C++
inline SR_NODISCARD uint64_t SR_GRAPH_UI_NS::UINode::GetNodePriority () noexcept override const
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



### function GetViewportSize 

```C++
inline SR_NODISCARD const SR_MATH_NS::FVector2 & SR_GRAPH_UI_NS::UINode::GetViewportSize () noexcept const
```




<hr>



### function Layout 

```C++
virtual void SR_GRAPH_UI_NS::UINode::Layout (
    const SR_MATH_NS::FRect & available
) = 0
```




<hr>



### function OnParentChanged 

```C++
void SR_GRAPH_UI_NS::UINode::OnParentChanged (
    const SR_UTILS_NS::SceneObject::Ptr & pOldParent
) override
```




<hr>



### function Prepare 

```C++
virtual void SR_GRAPH_UI_NS::UINode::Prepare (
    uint64_t & priority
) 
```




<hr>



### function SetViewportSize 

```C++
void SR_GRAPH_UI_NS::UINode::SetViewportSize (
    const SR_MATH_NS::FVector2 & size
) noexcept
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



### function ~UINode 

```C++
SR_GRAPH_UI_NS::UINode::~UINode () override
```




<hr>
## Protected Attributes Documentation




### variable m\_finalRect 

```C++
SR_MATH_NS::FRect SR_GRAPH_UI_NS::UINode::m_finalRect;
```




<hr>



### variable m\_hasParent 

```C++
bool SR_GRAPH_UI_NS::UINode::m_hasParent;
```




<hr>



### variable m\_implNode 

```C++
YGNode* SR_GRAPH_UI_NS::UINode::m_implNode;
```




<hr>



### variable m\_matrix 

```C++
SR_MATH_NS::Matrix4x4 SR_GRAPH_UI_NS::UINode::m_matrix;
```




<hr>



### variable m\_parentName 

```C++
SR_UTILS_NS::StringAtom SR_GRAPH_UI_NS::UINode::m_parentName;
```




<hr>



### variable m\_priority 

```C++
uint64_t SR_GRAPH_UI_NS::UINode::m_priority;
```




<hr>



### variable m\_renderScene 

```C++
RenderScene* SR_GRAPH_UI_NS::UINode::m_renderScene;
```




<hr>



### variable m\_viewportSize 

```C++
SR_MATH_NS::FVector2 SR_GRAPH_UI_NS::UINode::m_viewportSize;
```




<hr>
## Protected Functions Documentation




### function GetYGNode 

```C++
inline SR_NODISCARD YGNode * SR_GRAPH_UI_NS::UINode::GetYGNode () noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/UI/UINode.h`

