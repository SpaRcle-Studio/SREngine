

# Class SR\_HTYPES\_NS::Function&lt; ReturnType(ArgumentTypes...)&gt;

**template &lt;typename ReturnType, typename... ArgumentTypes&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Function&lt; ReturnType(ArgumentTypes...)&gt;**](classSR__HTYPES__NS_1_1Function_3_01ReturnType_07ArgumentTypes_8_8_8_08_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef ReturnType | [**signature\_type**](#typedef-signature_type)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Function**](#function-function-15) () <br> |
|   | [**Function**](#function-function-25) (FunctionT f) <br>_NOLINT._  |
|   | [**Function**](#function-function-35) ([**Function**](classSR__HTYPES__NS_1_1Function.md) && function) noexcept<br> |
|   | [**Function**](#function-function-45) (FunctionType ClassType::\* f) <br>_NOLINT._  |
|   | [**Function**](#function-function-55) (const [**Function**](classSR__HTYPES__NS_1_1Function.md) & other) <br> |
|   | [**operator bool**](#function-operator-bool) () const<br> |
|  ReturnType | [**operator()**](#function-operator) (ArgumentTypes... args) noexcept const<br> |
|  [**Function**](classSR__HTYPES__NS_1_1Function.md) & | [**operator=**](#function-operator_1) ([**Function**](classSR__HTYPES__NS_1_1Function.md) && function) noexcept<br> |
|  [**Function**](classSR__HTYPES__NS_1_1Function.md) & | [**operator=**](#function-operator_2) (const [**Function**](classSR__HTYPES__NS_1_1Function.md) & other) <br> |




























## Public Types Documentation




### typedef signature\_type 

```C++
typedef ReturnType SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::signature_type(ArgumentTypes...);
```




<hr>
## Public Functions Documentation




### function Function [1/5]

```C++
inline SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::Function () 
```




<hr>



### function Function [2/5]

_NOLINT._ 
```C++
template<typename FunctionT>
inline SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::Function (
    FunctionT f
) 
```




<hr>



### function Function [3/5]

```C++
inline SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::Function (
    Function && function
) noexcept
```




<hr>



### function Function [4/5]

_NOLINT._ 
```C++
template<typename FunctionType, typename ClassType>
inline SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::Function (
    FunctionType ClassType::* f
) 
```




<hr>



### function Function [5/5]

```C++
inline SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::Function (
    const Function & other
) 
```




<hr>



### function operator bool 

```C++
inline SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::operator bool () const
```




<hr>



### function operator() 

```C++
inline ReturnType SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::operator() (
    ArgumentTypes... args
) noexcept const
```




<hr>



### function operator= 

```C++
inline Function & SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::operator= (
    Function && function
) noexcept
```




<hr>



### function operator= 

```C++
inline Function & SR_HTYPES_NS::Function< ReturnType(ArgumentTypes...)>::operator= (
    const Function & other
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Function.h`

