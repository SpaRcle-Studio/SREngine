

# Class SR\_SRSL\_NS::SRSLDecorator



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLDecorator**](classSR__SRSL__NS_1_1SRSLDecorator.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**SRSLExpr**](classSR__SRSL__NS_1_1SRSLExpr.md) \* &gt; | [**args**](#variable-args)  <br> |
|  std::string | [**name**](#variable-name)  <br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**SRSLDecorator**](#function-srsldecorator-12) () = default<br> |
|   | [**SRSLDecorator**](#function-srsldecorator-22) ([**SRSLDecorator**](classSR__SRSL__NS_1_1SRSLDecorator.md) && other) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint32\_t deep) override const<br> |
|   | [**~SRSLDecorator**](#function-srsldecorator) () override<br> |


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




### variable args 

```C++
std::vector<SRSLExpr*> SR_SRSL_NS::SRSLDecorator::args;
```




<hr>



### variable name 

```C++
std::string SR_SRSL_NS::SRSLDecorator::name;
```




<hr>
## Public Functions Documentation




### function SRSLDecorator [1/2]

```C++
SR_SRSL_NS::SRSLDecorator::SRSLDecorator () = default
```




<hr>



### function SRSLDecorator [2/2]

```C++
inline SR_SRSL_NS::SRSLDecorator::SRSLDecorator (
    SRSLDecorator && other
) noexcept
```




<hr>



### function ToString 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLDecorator::ToString (
    uint32_t deep
) override const
```



Implements [*SR\_SRSL\_NS::SRSLLexicalUnit::ToString*](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-tostring)


<hr>



### function ~SRSLDecorator 

```C++
inline SR_SRSL_NS::SRSLDecorator::~SRSLDecorator () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

