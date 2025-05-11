

# Class SR\_SRSL\_NS::SRSLFunction



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLFunction**](classSR__SRSL__NS_1_1SRSLFunction.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**SRSLVariable**](classSR__SRSL__NS_1_1SRSLVariable.md) \* &gt; | [**args**](#variable-args)  <br> |
|  [**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md) \* | [**pDecorators**](#variable-pdecorators)   = `nullptr`<br> |
|  [**SRSLLexicalTree**](classSR__SRSL__NS_1_1SRSLLexicalTree.md) \* | [**pLexicalTree**](#variable-plexicaltree)   = `nullptr`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pName**](#variable-pname)   = `nullptr`<br> |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**pType**](#variable-ptype)   = `nullptr`<br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**GetName**](#function-getname) () const<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint32\_t deep) override const<br> |
|   | [**~SRSLFunction**](#function-srslfunction) () override<br> |


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




### variable args 

```C++
std::vector<SRSLVariable*> SR_SRSL_NS::SRSLFunction::args;
```




<hr>



### variable pDecorators 

```C++
SRSLDecorators* SR_SRSL_NS::SRSLFunction::pDecorators;
```




<hr>



### variable pLexicalTree 

```C++
SRSLLexicalTree* SR_SRSL_NS::SRSLFunction::pLexicalTree;
```




<hr>



### variable pName 

```C++
SRSLExpr* SR_SRSL_NS::SRSLFunction::pName;
```




<hr>



### variable pType 

```C++
SRSLExpr* SR_SRSL_NS::SRSLFunction::pType;
```




<hr>
## Public Functions Documentation




### function GetName 

```C++
inline SR_NODISCARD std::string SR_SRSL_NS::SRSLFunction::GetName () const
```




<hr>



### function ToString 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLFunction::ToString (
    uint32_t deep
) override const
```



Implements [*SR\_SRSL\_NS::SRSLLexicalUnit::ToString*](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-tostring)


<hr>



### function ~SRSLFunction 

```C++
SR_SRSL_NS::SRSLFunction::~SRSLFunction () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

