

# Class SR\_SRSL\_NS::SRSLForStatement



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLForStatement**](classSR__SRSL__NS_1_1SRSLForStatement.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pCondition**](#variable-pcondition)   = `nullptr`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pExpr**](#variable-pexpr)   = `nullptr`<br> |
|  [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) \* | [**pLexicalTree**](#variable-plexicaltree)   = `nullptr`<br> |
|  [**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) \* | [**pVar**](#variable-pvar)   = `nullptr`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLForStatement**](#function-srslforstatement) () = default<br> |
|   | [**~SRSLForStatement**](#function-srslforstatement) () override<br> |


## Public Functions inherited from SR_SRSL_NS::SRSLLexicalUnit

See [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)

| Type | Name |
| ---: | :--- |
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
|  constexpr | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () = default<br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () = default<br> |








## Detailed Description



 


    
## Public Attributes Documentation




### variable pCondition 

```C++
SRSLExpr* SR_SRSL_NS::SRSLForStatement::pCondition;
```




<hr>



### variable pExpr 

```C++
SRSLExpr* SR_SRSL_NS::SRSLForStatement::pExpr;
```




<hr>



### variable pLexicalTree 

```C++
SRSLLexicalTree* SR_SRSL_NS::SRSLForStatement::pLexicalTree;
```




<hr>



### variable pVar 

```C++
SRSLVariable* SR_SRSL_NS::SRSLForStatement::pVar;
```




<hr>
## Public Functions Documentation




### function SRSLForStatement 

```C++
SR_SRSL_NS::SRSLForStatement::SRSLForStatement () = default
```




<hr>



### function ~SRSLForStatement 

```C++
SR_SRSL_NS::SRSLForStatement::~SRSLForStatement () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

