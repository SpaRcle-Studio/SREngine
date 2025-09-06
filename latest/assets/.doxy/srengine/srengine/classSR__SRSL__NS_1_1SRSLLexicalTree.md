

# Class SR\_SRSL\_NS::SRSLLexicalTree



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**SRSLLexicalUnit**](classSR__SRSL__NS_1_1SRSLLexicalUnit.md) \* &gt; | [**lexicalTree**](#variable-lexicaltree)  <br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**AsExpression**](#function-asexpression) () const<br> |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD [**SRSLFunction**](classSR__SRSL__NS_1_1SRSLFunction.md) \* | [**FindFunction**](#function-findfunction) (const std::string & name) const<br> |
|   | [**SRSLLexicalTree**](#function-srsllexicaltree-12) () <br> |
|   | [**SRSLLexicalTree**](#function-srsllexicaltree-22) ([**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) && other) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint32\_t deep) override const<br> |
|  [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) & | [**operator=**](#function-operator) ([**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) && other) noexcept<br> |
|   | [**~SRSLLexicalTree**](#function-srsllexicaltree) () override<br> |


## Public Functions inherited from SR_SRSL_NS::SRSLLexicalUnit

See [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD LexicalUnitType | [**GetLexicalUnitType**](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-getlexicalunittype) () const<br> |
|   | [**SRSLLexicalUnit**](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-srsllexicalunit) (LexicalUnitType type) <br> |
| virtual SR\_NODISCARD std::string | [**ToString**](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-tostring) (uint32\_t deep) const<br> |


## Public Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-22) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |
| virtual [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) & | [**operator=**](classSR__UTILS__NS_1_1NonCopyable.md#function-operator) (const [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md) &) = delete<br> |








































































## Protected Functions inherited from SR_UTILS_NS::NonCopyable

See [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)

| Type | Name |
| ---: | :--- |
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Detailed Description



 


    
## Public Attributes Documentation




### variable lexicalTree 

```C++
std::vector<SRSLLexicalUnit*> SR_SRSL_NS::SRSLLexicalTree::lexicalTree;
```




<hr>
## Public Functions Documentation




### function AsExpression 

```C++
SR_NODISCARD SRSLExpr * SR_SRSL_NS::SRSLLexicalTree::AsExpression () const
```




<hr>



### function Clear 

```C++
inline void SR_SRSL_NS::SRSLLexicalTree::Clear () 
```




<hr>



### function FindFunction 

```C++
SR_NODISCARD SRSLFunction * SR_SRSL_NS::SRSLLexicalTree::FindFunction (
    const std::string & name
) const
```




<hr>



### function SRSLLexicalTree [1/2]

```C++
inline SR_SRSL_NS::SRSLLexicalTree::SRSLLexicalTree () 
```




<hr>



### function SRSLLexicalTree [2/2]

```C++
inline SR_SRSL_NS::SRSLLexicalTree::SRSLLexicalTree (
    SRSLLexicalTree && other
) noexcept
```




<hr>



### function ToString 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLLexicalTree::ToString (
    uint32_t deep
) override const
```



Implements [*SR\_SRSL\_NS::SRSLLexicalUnit::ToString*](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-tostring)


<hr>



### function operator= 

```C++
inline SRSLLexicalTree & SR_SRSL_NS::SRSLLexicalTree::operator= (
    SRSLLexicalTree && other
) noexcept
```




<hr>



### function ~SRSLLexicalTree 

```C++
inline SR_SRSL_NS::SRSLLexicalTree::~SRSLLexicalTree () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

