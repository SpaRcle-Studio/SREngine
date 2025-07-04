

# Class SR\_SRSL\_NS::SRSLWhileStatement



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLWhileStatement**](classSR__SRSL__NS_1_1SRSLWhileStatement.md)








Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pCondition**](#variable-pcondition)   = `nullptr`<br> |
|  [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) \* | [**pLexicalTree**](#variable-plexicaltree)   = `nullptr`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLWhileStatement**](#function-srslwhilestatement) () = default<br> |
|   | [**~SRSLWhileStatement**](#function-srslwhilestatement) () override<br> |


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








## Public Attributes Documentation




### variable pCondition 

```C++
SRSLExpr* SR_SRSL_NS::SRSLWhileStatement::pCondition;
```




<hr>



### variable pLexicalTree 

```C++
SRSLLexicalTree* SR_SRSL_NS::SRSLWhileStatement::pLexicalTree;
```




<hr>
## Public Functions Documentation




### function SRSLWhileStatement 

```C++
SR_SRSL_NS::SRSLWhileStatement::SRSLWhileStatement () = default
```




<hr>



### function ~SRSLWhileStatement 

```C++
SR_SRSL_NS::SRSLWhileStatement::~SRSLWhileStatement () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

