

# Class SR\_SRSL\_NS::SRSLIfStatement



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLIfStatement**](classSR__SRSL__NS_1_1SRSLIfStatement.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**isElse**](#variable-iselse)   = `false`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pExpr**](#variable-pexpr)   = `nullptr`<br> |
|  [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) \* | [**pLexicalTree**](#variable-plexicaltree)   = `nullptr`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLIfStatement**](#function-srslifstatement-12) () = default<br> |
|   | [**SRSLIfStatement**](#function-srslifstatement-22) (bool isElse) <br> |
|   | [**~SRSLIfStatement**](#function-srslifstatement) () override<br> |


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
|   | [**NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable-12) () <br> |
| virtual  | [**~NonCopyable**](classSR__UTILS__NS_1_1NonCopyable.md#function-noncopyable) () <br> |








## Detailed Description



 


    
## Public Attributes Documentation




### variable isElse 

```C++
bool SR_SRSL_NS::SRSLIfStatement::isElse;
```




<hr>



### variable pExpr 

```C++
SRSLExpr* SR_SRSL_NS::SRSLIfStatement::pExpr;
```




<hr>



### variable pLexicalTree 

```C++
SRSLLexicalTree* SR_SRSL_NS::SRSLIfStatement::pLexicalTree;
```




<hr>
## Public Functions Documentation




### function SRSLIfStatement [1/2]

```C++
SR_SRSL_NS::SRSLIfStatement::SRSLIfStatement () = default
```




<hr>



### function SRSLIfStatement [2/2]

```C++
explicit SR_SRSL_NS::SRSLIfStatement::SRSLIfStatement (
    bool isElse
) 
```




<hr>



### function ~SRSLIfStatement 

```C++
SR_SRSL_NS::SRSLIfStatement::~SRSLIfStatement () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

