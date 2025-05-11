

# Class SR\_SRSL\_NS::SRSLExpr



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* &gt; | [**args**](#variable-args)  <br> |
|  bool | [**isArray**](#variable-isarray)   = `false`<br>_function(arg1, arg2, arg3)_  |
|  bool | [**isCall**](#variable-iscall)   = `false`<br> |
|  bool | [**isList**](#variable-islist)   = `false`<br>_variable[expression]_  |
|  bool | [**isString**](#variable-isstring)   = `false`<br>_{ expr1, expr2, expr3 }_  |
|  std::string | [**token**](#variable-token)  <br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLExpr**](#function-srslexpr-16) () = default<br> |
|   | [**SRSLExpr**](#function-srslexpr-26) (std::string && token) <br> |
|   | [**SRSLExpr**](#function-srslexpr-36) (std::string && token, [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pAExpr) <br> |
|   | [**SRSLExpr**](#function-srslexpr-46) (std::string && token, [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pAExpr, [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pBExpr) <br> |
|   | [**SRSLExpr**](#function-srslexpr-56) ([**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pAExpr, [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* pBExpr) <br> |
|   | [**SRSLExpr**](#function-srslexpr-66) ([**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) && other) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint32\_t deep) override const<br> |
|   | [**~SRSLExpr**](#function-srslexpr) () override<br> |


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


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* | [**CreateStringExpression**](#function-createstringexpression) (std::string token) <br> |






































































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
std::vector<SRSLExpr*> SR_SRSL_NS::SRSLExpr::args;
```




<hr>



### variable isArray 

_function(arg1, arg2, arg3)_ 
```C++
bool SR_SRSL_NS::SRSLExpr::isArray;
```




<hr>



### variable isCall 

```C++
bool SR_SRSL_NS::SRSLExpr::isCall;
```




<hr>



### variable isList 

_variable[expression]_ 
```C++
bool SR_SRSL_NS::SRSLExpr::isList;
```




<hr>



### variable isString 

_{ expr1, expr2, expr3 }_ 
```C++
bool SR_SRSL_NS::SRSLExpr::isString;
```




<hr>



### variable token 

```C++
std::string SR_SRSL_NS::SRSLExpr::token;
```




<hr>
## Public Functions Documentation




### function SRSLExpr [1/6]

```C++
SR_SRSL_NS::SRSLExpr::SRSLExpr () = default
```




<hr>



### function SRSLExpr [2/6]

```C++
inline explicit SR_SRSL_NS::SRSLExpr::SRSLExpr (
    std::string && token
) 
```




<hr>



### function SRSLExpr [3/6]

```C++
inline explicit SR_SRSL_NS::SRSLExpr::SRSLExpr (
    std::string && token,
    SRSLExpr * pAExpr
) 
```




<hr>



### function SRSLExpr [4/6]

```C++
inline explicit SR_SRSL_NS::SRSLExpr::SRSLExpr (
    std::string && token,
    SRSLExpr * pAExpr,
    SRSLExpr * pBExpr
) 
```




<hr>



### function SRSLExpr [5/6]

```C++
inline explicit SR_SRSL_NS::SRSLExpr::SRSLExpr (
    SRSLExpr * pAExpr,
    SRSLExpr * pBExpr
) 
```




<hr>



### function SRSLExpr [6/6]

```C++
inline SR_SRSL_NS::SRSLExpr::SRSLExpr (
    SRSLExpr && other
) noexcept
```




<hr>



### function ToString 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLExpr::ToString (
    uint32_t deep
) override const
```



Implements [*SR\_SRSL\_NS::SRSLLexicalUnit::ToString*](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-tostring)


<hr>



### function ~SRSLExpr 

```C++
inline SR_SRSL_NS::SRSLExpr::~SRSLExpr () override
```




<hr>
## Public Static Functions Documentation




### function CreateStringExpression 

```C++
static inline SRSLExpr * SR_SRSL_NS::SRSLExpr::CreateStringExpression (
    std::string token
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

