

# Class SR\_SRSL\_NS::SRSLDecorators



[**ClassList**](annotated.md) **>** [**SR\_SRSL\_NS**](namespaceSR__SRSL__NS.md) **>** [**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md)



[More...](#detailed-description)

* `#include <LexicalTree.h>`



Inherits the following classes: [SR\_SRSL\_NS::SRSLLexicalUnit](classSR__SRSL__NS_1_1SRSLLexicalUnit.md)


























## Public Attributes

| Type | Name |
| ---: | :--- |
|  std::vector&lt; [**SRSLDecorator**](classSR__SRSL__NS_1_1SRSLDecorator.md) &gt; | [**decorators**](#variable-decorators)  <br> |
















































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD [**SRSLDecorator**](classSR__SRSL__NS_1_1SRSLDecorator.md) \* | [**Find**](#function-find) (const std::string & name) <br> |
|   | [**SRSLDecorators**](#function-srsldecorators-12) () <br> |
|   | [**SRSLDecorators**](#function-srsldecorators-22) ([**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md) && other) noexcept<br> |
| virtual SR\_NODISCARD std::string | [**ToString**](#function-tostring) (uint32\_t deep) override const<br> |
|  [**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md) & | [**operator=**](#function-operator) ([**SRSLDecorators**](classSR__SRSL__NS_1_1SRSLDecorators.md) && other) noexcept<br> |


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




### variable decorators 

```C++
std::vector<SRSLDecorator> SR_SRSL_NS::SRSLDecorators::decorators;
```




<hr>
## Public Functions Documentation




### function Find 

```C++
SR_NODISCARD SRSLDecorator * SR_SRSL_NS::SRSLDecorators::Find (
    const std::string & name
) 
```




<hr>



### function SRSLDecorators [1/2]

```C++
inline SR_SRSL_NS::SRSLDecorators::SRSLDecorators () 
```




<hr>



### function SRSLDecorators [2/2]

```C++
inline SR_SRSL_NS::SRSLDecorators::SRSLDecorators (
    SRSLDecorators && other
) noexcept
```




<hr>



### function ToString 

```C++
virtual SR_NODISCARD std::string SR_SRSL_NS::SRSLDecorators::ToString (
    uint32_t deep
) override const
```



Implements [*SR\_SRSL\_NS::SRSLLexicalUnit::ToString*](classSR__SRSL__NS_1_1SRSLLexicalUnit.md#function-tostring)


<hr>



### function operator= 

```C++
inline SRSLDecorators & SR_SRSL_NS::SRSLDecorators::operator= (
    SRSLDecorators && other
) noexcept
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Graphics/inc/Graphics/SRSL/LexicalTree.h`

