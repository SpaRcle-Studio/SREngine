

# Class SR\_SRSL\_NS::SRSLStructureStatement



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLStructureStatement**](classSR__SRSL__NS_1_1SRSLStructureStatement.md)








Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) \* | [**pLexicalTree**](#variable-plexicaltree)   = `nullptr`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pName**](#variable-pname)   = `nullptr`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLStructureStatement**](#function-srslstructurestatement) () = default<br> |
|   | [**~SRSLStructureStatement**](#function-srslstructurestatement) () override<br> |


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




### variable pLexicalTree 

```C++
SRSLLexicalTree* SR_SRSL_NS::SRSLStructureStatement::pLexicalTree;
```




<hr>



### variable pName 

```C++
SRSLExpr* SR_SRSL_NS::SRSLStructureStatement::pName;
```




<hr>
## Public Functions Documentation




### function SRSLStructureStatement 

```C++
SR_SRSL_NS::SRSLStructureStatement::SRSLStructureStatement () = default
```




<hr>



### function ~SRSLStructureStatement 

```C++
SR_SRSL_NS::SRSLStructureStatement::~SRSLStructureStatement () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

