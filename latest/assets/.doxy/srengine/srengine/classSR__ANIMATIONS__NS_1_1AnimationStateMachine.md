

# Class SR\_ANIMATIONS\_NS::AnimationStateMachine



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md)








Inherits the following classes: [SR\_ANIMATIONS\_NS::IAnimationDataSet](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md),  [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)










































































## Public Functions

| Type | Name |
| ---: | :--- |
|  T \* | [**AddState**](#function-addstate) (T \* pState) <br> |
|   | [**AnimationStateMachine**](#function-animationstatemachine) () <br> |
|  void | [**Compile**](#function-compile) ([**CompileContext**](structSR__ANIMATIONS__NS_1_1CompileContext.md) & context) <br> |
|  T \* | [**CreateState**](#function-createstate) (Args &&... args) <br> |
|  SR\_NODISCARD [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**FindState**](#function-findstate) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  SR\_NODISCARD [**AnimationEntryPointState**](classSR__ANIMATIONS__NS_1_1AnimationEntryPointState.md) \* | [**GetEntryPoint**](#function-getentrypoint) () const<br> |
|  SR\_NODISCARD [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* | [**GetState**](#function-getstate) (uint32\_t index) const<br> |
|  SR\_NODISCARD const std::vector&lt; [**AnimationState**](classSR__ANIMATIONS__NS_1_1AnimationState.md) \* &gt; & | [**GetStates**](#function-getstates) () noexcept const<br> |
|  SR\_NODISCARD bool | [**IsStateActive**](#function-isstateactive) ([**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) name) const<br> |
|  void | [**SetNode**](#function-setnode) ([**AnimationGraphNode**](classSR__ANIMATIONS__NS_1_1AnimationGraphNode.md) \* pNode) <br> |
|  void | [**Update**](#function-update) ([**UpdateContext**](structSR__ANIMATIONS__NS_1_1UpdateContext.md) & context) <br> |
|   | [**~AnimationStateMachine**](#function-animationstatemachine) () override<br> |


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
|  SR\_NODISCARD [**AnimationStateMachine**](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md) \* | [**Load**](#function-load) (const SR\_XML\_NS::Node & nodeXml) <br> |




















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








## Public Functions Documentation




### function AddState 

```C++
template<class T>
inline T * SR_ANIMATIONS_NS::AnimationStateMachine::AddState (
    T * pState
) 
```




<hr>



### function AnimationStateMachine 

```C++
SR_ANIMATIONS_NS::AnimationStateMachine::AnimationStateMachine () 
```




<hr>



### function Compile 

```C++
void SR_ANIMATIONS_NS::AnimationStateMachine::Compile (
    CompileContext & context
) 
```




<hr>



### function CreateState 

```C++
template<class T, typename... Args>
inline T * SR_ANIMATIONS_NS::AnimationStateMachine::CreateState (
    Args &&... args
) 
```




<hr>



### function FindState 

```C++
SR_NODISCARD AnimationState * SR_ANIMATIONS_NS::AnimationStateMachine::FindState (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function GetEntryPoint 

```C++
SR_NODISCARD AnimationEntryPointState * SR_ANIMATIONS_NS::AnimationStateMachine::GetEntryPoint () const
```




<hr>



### function GetState 

```C++
SR_NODISCARD AnimationState * SR_ANIMATIONS_NS::AnimationStateMachine::GetState (
    uint32_t index
) const
```




<hr>



### function GetStates 

```C++
inline SR_NODISCARD const std::vector< AnimationState * > & SR_ANIMATIONS_NS::AnimationStateMachine::GetStates () noexcept const
```




<hr>



### function IsStateActive 

```C++
SR_NODISCARD bool SR_ANIMATIONS_NS::AnimationStateMachine::IsStateActive (
    SR_UTILS_NS::StringAtom name
) const
```




<hr>



### function SetNode 

```C++
inline void SR_ANIMATIONS_NS::AnimationStateMachine::SetNode (
    AnimationGraphNode * pNode
) 
```




<hr>



### function Update 

```C++
void SR_ANIMATIONS_NS::AnimationStateMachine::Update (
    UpdateContext & context
) 
```




<hr>



### function ~AnimationStateMachine 

```C++
SR_ANIMATIONS_NS::AnimationStateMachine::~AnimationStateMachine () override
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
static SR_NODISCARD AnimationStateMachine * SR_ANIMATIONS_NS::AnimationStateMachine::Load (
    const SR_XML_NS::Node & nodeXml
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/Animations/AnimationStateMachine.h`

