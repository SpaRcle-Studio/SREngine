

# Class SR\_ANIMATIONS\_NS::IAnimationDataSet



[**ClassList**](annotated.md) **>** [**SR\_ANIMATIONS\_NS**](namespaceSR__ANIMATIONS__NS.md) **>** [**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md)










Inherited by the following classes: [SR\_ANIMATIONS\_NS::AnimationGraph](classSR__ANIMATIONS__NS_1_1AnimationGraph.md),  [SR\_ANIMATIONS\_NS::AnimationStateMachine](classSR__ANIMATIONS__NS_1_1AnimationStateMachine.md)
































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::optional&lt; bool &gt; | [**GetBool**](#function-getbool) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD std::optional&lt; float\_t &gt; | [**GetFloat**](#function-getfloat) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD std::optional&lt; int32\_t &gt; | [**GetInt**](#function-getint) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  SR\_NODISCARD std::optional&lt; std::string &gt; | [**GetString**](#function-getstring) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name) const<br> |
|  void | [**SetAnimationDataSetParent**](#function-setanimationdatasetparent) ([**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md) \* pParent) <br> |
|  void | [**SetBool**](#function-setbool) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const bool value) <br> |
|  void | [**SetFloat**](#function-setfloat) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const float\_t value) <br> |
|  void | [**SetInt**](#function-setint) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const int32\_t value) <br> |
|  void | [**SetString**](#function-setstring) (const [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md) & name, const std::string & value) <br> |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), bool &gt; | [**m\_boolTable**](#variable-m_booltable)  <br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), float\_t &gt; | [**m\_floatTable**](#variable-m_floattable)  <br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), int32\_t &gt; | [**m\_intTable**](#variable-m_inttable)  <br> |
|  [**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md) \* | [**m\_parent**](#variable-m_parent)   = `nullptr`<br> |
|  std::map&lt; [**SR\_UTILS\_NS::StringAtom**](classSR__UTILS__NS_1_1StringAtom.md), std::string &gt; | [**m\_stringTable**](#variable-m_stringtable)  <br> |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|   | [**IAnimationDataSet**](#function-ianimationdataset-12) () = default<br> |
|   | [**IAnimationDataSet**](#function-ianimationdataset-22) ([**IAnimationDataSet**](classSR__ANIMATIONS__NS_1_1IAnimationDataSet.md) \* pParent) <br> |
| virtual  | [**~IAnimationDataSet**](#function-ianimationdataset) () = default<br> |




## Public Functions Documentation




### function GetBool 

```C++
SR_NODISCARD std::optional< bool > SR_ANIMATIONS_NS::IAnimationDataSet::GetBool (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function GetFloat 

```C++
SR_NODISCARD std::optional< float_t > SR_ANIMATIONS_NS::IAnimationDataSet::GetFloat (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function GetInt 

```C++
SR_NODISCARD std::optional< int32_t > SR_ANIMATIONS_NS::IAnimationDataSet::GetInt (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function GetString 

```C++
SR_NODISCARD std::optional< std::string > SR_ANIMATIONS_NS::IAnimationDataSet::GetString (
    const SR_UTILS_NS::StringAtom & name
) const
```




<hr>



### function SetAnimationDataSetParent 

```C++
inline void SR_ANIMATIONS_NS::IAnimationDataSet::SetAnimationDataSetParent (
    IAnimationDataSet * pParent
) 
```




<hr>



### function SetBool 

```C++
inline void SR_ANIMATIONS_NS::IAnimationDataSet::SetBool (
    const SR_UTILS_NS::StringAtom & name,
    const bool value
) 
```




<hr>



### function SetFloat 

```C++
inline void SR_ANIMATIONS_NS::IAnimationDataSet::SetFloat (
    const SR_UTILS_NS::StringAtom & name,
    const float_t value
) 
```




<hr>



### function SetInt 

```C++
inline void SR_ANIMATIONS_NS::IAnimationDataSet::SetInt (
    const SR_UTILS_NS::StringAtom & name,
    const int32_t value
) 
```




<hr>



### function SetString 

```C++
inline void SR_ANIMATIONS_NS::IAnimationDataSet::SetString (
    const SR_UTILS_NS::StringAtom & name,
    const std::string & value
) 
```




<hr>
## Protected Attributes Documentation




### variable m\_boolTable 

```C++
std::map<SR_UTILS_NS::StringAtom, bool> SR_ANIMATIONS_NS::IAnimationDataSet::m_boolTable;
```




<hr>



### variable m\_floatTable 

```C++
std::map<SR_UTILS_NS::StringAtom, float_t> SR_ANIMATIONS_NS::IAnimationDataSet::m_floatTable;
```




<hr>



### variable m\_intTable 

```C++
std::map<SR_UTILS_NS::StringAtom, int32_t> SR_ANIMATIONS_NS::IAnimationDataSet::m_intTable;
```




<hr>



### variable m\_parent 

```C++
IAnimationDataSet* SR_ANIMATIONS_NS::IAnimationDataSet::m_parent;
```




<hr>



### variable m\_stringTable 

```C++
std::map<SR_UTILS_NS::StringAtom, std::string> SR_ANIMATIONS_NS::IAnimationDataSet::m_stringTable;
```




<hr>
## Protected Functions Documentation




### function IAnimationDataSet [1/2]

```C++
SR_ANIMATIONS_NS::IAnimationDataSet::IAnimationDataSet () = default
```




<hr>



### function IAnimationDataSet [2/2]

```C++
inline explicit SR_ANIMATIONS_NS::IAnimationDataSet::IAnimationDataSet (
    IAnimationDataSet * pParent
) 
```




<hr>



### function ~IAnimationDataSet 

```C++
virtual SR_ANIMATIONS_NS::IAnimationDataSet::~IAnimationDataSet () = default
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/Animations/AnimationCommon.h`

