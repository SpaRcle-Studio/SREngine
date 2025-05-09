

# Class SR\_SRSL\_NS::SRSLReturn



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLReturn**](classSR__SRSL__NS_1_1SRSLReturn.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pExpr**](#variable-pexpr)   = `nullptr`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLReturn**](#function-srslreturn-12) ([**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pExpr) <br> |
|   | [**SRSLReturn**](#function-srslreturn-22) ([**SRSLReturn**](classSR__SRSL__NS_1_1SRSLReturn.md) && other) noexcept<br> |
|  [**SRSLReturn**](classSR__SRSL__NS_1_1SRSLReturn.md) & | [**operator=**](#function-operator) ([**SRSLReturn**](classSR__SRSL__NS_1_1SRSLReturn.md) && other) noexcept<br> |
|   | [**~SRSLReturn**](#function-srslreturn) () override<br> |


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




### variable pExpr 

```C++
SRSLExpr* SR_SRSL_NS::SRSLReturn::pExpr;
```




<hr>
## Public Functions Documentation




### function SRSLReturn [1/2]

```C++
inline explicit SR_SRSL_NS::SRSLReturn::SRSLReturn (
    SRSLExpr * pExpr
) 
```




<hr>



### function SRSLReturn [2/2]

```C++
inline SR_SRSL_NS::SRSLReturn::SRSLReturn (
    SRSLReturn && other
) noexcept
```




<hr>



### function operator= 

```C++
inline SRSLReturn & SR_SRSL_NS::SRSLReturn::operator= (
    SRSLReturn && other
) noexcept
```




<hr>



### function ~SRSLReturn 

```C++
inline SR_SRSL_NS::SRSLReturn::~SRSLReturn () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

