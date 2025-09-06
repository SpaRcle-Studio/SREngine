

# Class SR\_SRSL\_NS::SRSLVariable



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md) \* | [**pDecorators**](#variable-pdecorators)   = `nullptr`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pExpr**](#variable-pexpr)   = `nullptr`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pName**](#variable-pname)   = `nullptr`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pType**](#variable-ptype)   = `nullptr`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**GetName**](#function-getname) () const<br> |
|  SR\_NODISCARD std::string | [**GetType**](#function-gettype) () const<br> |
|   | [**SRSLVariable**](#function-srslvariable-12) () <br> |
|   | [**SRSLVariable**](#function-srslvariable-22) ([**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) && other) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint32\_t deep) override const<br> |
|  [**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) & | [**operator=**](#function-operator) ([**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) && other) noexcept<br> |
|   | [**~SRSLVariable**](#function-srslvariable) () override<br> |


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




### variable pDecorators 

```C++
SRSLDecorators* SR_SRSL_NS::SRSLVariable::pDecorators;
```




<hr>



### variable pExpr 

```C++
SRSLExpr* SR_SRSL_NS::SRSLVariable::pExpr;
```




<hr>



### variable pName 

```C++
SRSLExpr* SR_SRSL_NS::SRSLVariable::pName;
```




<hr>



### variable pType 

```C++
SRSLExpr* SR_SRSL_NS::SRSLVariable::pType;
```




<hr>
## Public Functions Documentation




### function GetName 

```C++
SR_NODISCARD std::string SR_SRSL_NS::SRSLVariable::GetName () const
```




<hr>



### function GetType 

```C++
SR_NODISCARD std::string SR_SRSL_NS::SRSLVariable::GetType () const
```




<hr>



### function SRSLVariable [1/2]

```C++
inline SR_SRSL_NS::SRSLVariable::SRSLVariable () 
```




<hr>



### function SRSLVariable [2/2]

```C++
inline SR_SRSL_NS::SRSLVariable::SRSLVariable (
    SRSLVariable && other
) noexcept
```




<hr>



### function ToString 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLVariable::ToString (
    uint32_t deep
) override const
```



Implements [*SR\_SRSL\_NS::SRSLLexicalUnit::ToString*](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-tostring)


<hr>



### function operator= 

```C++
inline SRSLVariable & SR_SRSL_NS::SRSLVariable::operator= (
    SRSLVariable && other
) noexcept
```




<hr>



### function ~SRSLVariable 

```C++
inline SR_SRSL_NS::SRSLVariable::~SRSLVariable () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

