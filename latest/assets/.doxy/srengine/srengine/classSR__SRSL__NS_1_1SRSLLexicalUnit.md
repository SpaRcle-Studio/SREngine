

# Class SR\_SRSL\_NS::SRSLLexicalUnit



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLLexicalUnit**](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)



_минимальная лексическая единица_ 

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)


Inherited by the following classes: [SR\_SRSL\_NS::SRSLDecorator](classSR__SRSL__NS_1_1SRSLDecorator.md),  [SR\_SRSL\_NS::SRSLDecorators](classSR__SRSL__NS_1_1SRSLDecorators.md),  [SR\_SRSL\_NS::SRSLExpr](classSR__SRSL__NS_1_1SRSLExpr.md),  [SR\_SRSL\_NS::SRSLForStatement](classSR__SRSL__NS_1_1SRSLForStatement.md),  [SR\_SRSL\_NS::SRSLFunction](classSR__SRSL__NS_1_1SRSLFunction.md),  [SR\_SRSL\_NS::SRSLIfStatement](classSR__SRSL__NS_1_1SRSLIfStatement.md),  [SR\_SRSL\_NS::SRSLLexicalTree](classSR__SRSL__NS_1_1SRSLLexicalTree.md),  [SR\_SRSL\_NS::SRSLReturn](classSR__SRSL__NS_1_1SRSLReturn.md),  [SR\_SRSL\_NS::SRSLStructureStatement](classSR__SRSL__NS_1_1SRSLStructureStatement.md),  [SR\_SRSL\_NS::SRSLVariable](classSR__SRSL__NS_1_1SRSLVariable.md),  [SR\_SRSL\_NS::SRSLWhileStatement](classSR__SRSL__NS_1_1SRSLWhileStatement.md)




















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD LexicalUnitType | [**GetLexicalUnitType**](#function-getlexicalunittype) () const<br> |
|   | [**SRSLLexicalUnit**](#function-srsllexicalunit) (LexicalUnitType type) <br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint32\_t deep) const<br> |


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






## Public Functions Documentation




### function GetLexicalUnitType 

```C++
inline SR_NODISCARD LexicalUnitType SR_SRSL_NS::SRSLLexicalUnit::GetLexicalUnitType () const
```




<hr>



### function SRSLLexicalUnit 

```C++
inline explicit SR_SRSL_NS::SRSLLexicalUnit::SRSLLexicalUnit (
    LexicalUnitType type
) 
```




<hr>



### function ToString 

```C++
inline virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLLexicalUnit::ToString (
    uint32_t deep
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

