

# Class SR\_ANIMATIONS\_NS::AnimationGraph



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraph.md)








Inherits the following classes: [SR\_ANIMATIONS\_NS::IAnimationDataSet](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md),  [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; SR\_UTILS\_NS::GameObject::Ptr &gt; | [**m\_gameObjects**](#variable-m_gameobjects)  <br> |
|  ska::flat\_hash\_map&lt; [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \*, uint32\_t &gt; | [**m\_indices**](#variable-m_indices)  <br> |
|  bool | [**m\_isCompiled**](#variable-m_iscompiled)   = `false`<br> |
|  std::vector&lt; [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* &gt; | [**m\_nodes**](#variable-m_nodes)  <br>_первая нода всегда является Final_  |
|  [**Animator**](classSR__ANIMATIONS__NS_1_1Animator.md) \* | [**m\_pAnimator**](#variable-m_panimator)   = `nullptr`<br> |
|  [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) | [**m\_path**](#variable-m_path)  <br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  T \* | [**AddNode**](#function-addnode) (T \* pNode) <br> |
|   | [**AnimationGraph**](#function-animationgraph) ([**Animator**](classSR__ANIMATIONS__NS_1_1Animator.md) \* pAnimator) <br> |
|  T \* | [**CreateNode**](#function-createnode) (Args &&... args) <br> |
|  SR\_NODISCARD [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* | [**GetFinal**](#function-getfinal) () const<br> |
|  SR\_NODISCARD [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* | [**GetNode**](#function-getnode) (uint64\_t index) const<br> |
|  SR\_NODISCARD uint64\_t | [**GetNodeIndex**](#function-getnodeindex) (const [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* pNode) const<br> |
|  SR\_NODISCARD const std::vector&lt; [**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* &gt; & | [**GetNodes**](#function-getnodes) () noexcept const<br> |
|  SR\_NODISCARD uint32\_t | [**GetNodesCount**](#function-getnodescount) () noexcept const<br> |
|  SR\_NODISCARD const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & | [**GetPath**](#function-getpath) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsStateActive**](#function-isstateactive) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  void | [**Update**](#function-update) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context) <br> |
|   | [**~AnimationGraph**](#function-animationgraph) () override<br> |


## Public Functions inherited from SR_ANIMATIONS_NS::IAnimationDataSet

See [SR\_ANIMATIONS\_NS::IAnimationDataSet](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::optional&lt; bool &gt; | [**GetBool**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-getbool) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetFloat**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-getfloat) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD std::optional&lt; int32\_t &gt; | [**GetInt**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-getint) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD std::optional&lt; std::string &gt; | [**GetString**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-getstring) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  void | [**SetAnimationDataSetParent**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-setanimationdatasetparent) ([**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md) \* pParent) <br> |
|  void | [**SetBool**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-setbool) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const bool value) <br> |
|  void | [**SetFloat**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-setfloat) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const float\_t value) <br> |
|  void | [**SetInt**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-setint) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const int32\_t value) <br> |
|  void | [**SetString**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-setstring) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const std::string & value) <br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**AnimationGraph**](classSR__ANIMATIONS__NS_1_1AnimationGraph.md) \* | [**Load**](#function-load) ([**Animator**](classSR__ANIMATIONS__NS_1_1Animator.md) \* pAnimator, const [**SR\_UTILS\_NS::Path**](classSR__UTILS__NS_1_1Path.md) & path) <br> |




















## Protected Attributes inherited from SR_ANIMATIONS_NS::IAnimationDataSet

See [SR\_ANIMATIONS\_NS::IAnimationDataSet](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md)

| Type | Name |
| ---: | :--- |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), bool &gt; | [**m\_boolTable**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#variable-m_booltable)  <br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), float\_t &gt; | [**m\_floatTable**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#variable-m_floattable)  <br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), int32\_t &gt; | [**m\_intTable**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#variable-m_inttable)  <br> |
|  [**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md) \* | [**m\_parent**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#variable-m_parent)   = `nullptr`<br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), std::string &gt; | [**m\_stringTable**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#variable-m_stringtable)  <br> |
















































## Protected Functions inherited from SR_ANIMATIONS_NS::IAnimationDataSet

See [SR\_ANIMATIONS\_NS::IAnimationDataSet](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md)

| Type | Name |
| ---: | :--- |
|   | [**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-ianimationdataset-12) () = default<br> |
|   | [**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-ianimationdataset-22) ([**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md) \* pParent) <br> |
| virtual  | [**~IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md#function-ianimationdataset) () = default<br> |


## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Public Attributes Documentation




### variable m\_gameObjects 

```C++
std::vector<SR_UTILS_NS::GameObject::Ptr> SR_ANIMATIONS_NS::AnimationGraph::m_gameObjects;
```




<hr>



### variable m\_indices 

```C++
ska::flat_hash_map<AnimationGraphNode*, uint32_t> SR_ANIMATIONS_NS::AnimationGraph::m_indices;
```




<hr>



### variable m\_isCompiled 

```C++
bool SR_ANIMATIONS_NS::AnimationGraph::m_isCompiled;
```




<hr>



### variable m\_nodes 

_первая нода всегда является Final_ 
```C++
std::vector<AnimationGraphNode*> SR_ANIMATIONS_NS::AnimationGraph::m_nodes;
```




<hr>



### variable m\_pAnimator 

```C++
Animator* SR_ANIMATIONS_NS::AnimationGraph::m_pAnimator;
```




<hr>



### variable m\_path 

```C++
SR_UTILS_NS::Path SR_ANIMATIONS_NS::AnimationGraph::m_path;
```




<hr>
## Public Functions Documentation




### function AddNode 

```C++
template<class T>
inline T * SR_ANIMATIONS_NS::AnimationGraph::AddNode (
    T * pNode
) 
```




<hr>



### function AnimationGraph 

```C++
explicit SR_ANIMATIONS_NS::AnimationGraph::AnimationGraph (
    Animator * pAnimator
) 
```




<hr>



### function CreateNode 

```C++
template<class T, typename... Args>
inline T * SR_ANIMATIONS_NS::AnimationGraph::CreateNode (
    Args &&... args
) 
```




<hr>



### function GetFinal 

```C++
SR_NODISCARD AnimationGraphNode * SR_ANIMATIONS_NS::AnimationGraph::GetFinal () const
```




<hr>



### function GetNode 

```C++
SR_NODISCARD AnimationGraphNode * SR_ANIMATIONS_NS::AnimationGraph::GetNode (
    uint64_t index
) const
```




<hr>



### function GetNodeIndex 

```C++
SR_NODISCARD uint64_t SR_ANIMATIONS_NS::AnimationGraph::GetNodeIndex (
    const AnimationGraphNode * pNode
) const
```




<hr>



### function GetNodes 

```C++
inline SR_NODISCARD const std::vector< AnimationGraphNode * > & SR_ANIMATIONS_NS::AnimationGraph::GetNodes () noexcept const
```




<hr>



### function GetNodesCount 

```C++
inline SR_NODISCARD uint32_t SR_ANIMATIONS_NS::AnimationGraph::GetNodesCount () noexcept const
```




<hr>



### function GetPath 

```C++
inline SR_NODISCARD const SR_UTILS_NS::Path & SR_ANIMATIONS_NS::AnimationGraph::GetPath () noexcept const
```




<hr>



### function IsStateActive 

```C++
SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationGraph::IsStateActive (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function Update 

```C++
void SR_ANIMATIONS_NS::AnimationGraph::Update (
    UpdateContext & context
) 
```




<hr>



### function ~AnimationGraph 

```C++
SR_ANIMATIONS_NS::AnimationGraph::~AnimationGraph () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationGraph * SR_ANIMATIONS_NS::AnimationGraph::Load (
    Animator * pAnimator,
    const SR_UTILS_NS::Path & path
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/AnimationGraph.h`

