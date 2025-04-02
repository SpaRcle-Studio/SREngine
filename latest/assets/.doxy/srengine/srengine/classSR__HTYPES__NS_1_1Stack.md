

# Class SR\_HTYPES\_NS::Stack

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Stack**](classSR__HTYPES__NS_1_1Stack.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD bool | [**IsEmpty**](#function-isempty) () noexcept const<br> |
|  T | [**Pop**](#function-pop) () <br> |
|  void | [**Push**](#function-push-12) (T && value) <br> |
|  void | [**Push**](#function-push-22) (const T & value) <br> |
|  SR\_NODISCARD uint64\_t | [**Size**](#function-size) () noexcept const<br> |
|   | [**Stack**](#function-stack-13) () = default<br> |
|   | [**Stack**](#function-stack-23) (const [**Stack**](classSR__HTYPES__NS_1_1Stack.md) & other) <br> |
|   | [**Stack**](#function-stack-33) ([**Stack**](classSR__HTYPES__NS_1_1Stack.md) && other) noexcept<br> |
|  SR\_NODISCARD T & | [**Top**](#function-top) () <br> |
|  [**Stack**](classSR__HTYPES__NS_1_1Stack.md) & | [**operator=**](#function-operator) (const [**Stack**](classSR__HTYPES__NS_1_1Stack.md) & other) <br> |
|  [**Stack**](classSR__HTYPES__NS_1_1Stack.md) & | [**operator=**](#function-operator_1) ([**Stack**](classSR__HTYPES__NS_1_1Stack.md) && other) noexcept<br> |
|   | [**~Stack**](#function-stack) () <br> |




























## Public Functions Documentation




### function Clear 

```C++
inline void SR_HTYPES_NS::Stack::Clear () 
```




<hr>



### function IsEmpty 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::Stack::IsEmpty () noexcept const
```




<hr>



### function Pop 

```C++
inline T SR_HTYPES_NS::Stack::Pop () 
```




<hr>



### function Push [1/2]

```C++
inline void SR_HTYPES_NS::Stack::Push (
    T && value
) 
```




<hr>



### function Push [2/2]

```C++
inline void SR_HTYPES_NS::Stack::Push (
    const T & value
) 
```




<hr>



### function Size 

```C++
inline SR_NODISCARD uint64_t SR_HTYPES_NS::Stack::Size () noexcept const
```




<hr>



### function Stack [1/3]

```C++
SR_HTYPES_NS::Stack::Stack () = default
```




<hr>



### function Stack [2/3]

```C++
inline SR_HTYPES_NS::Stack::Stack (
    const Stack & other
) 
```




<hr>



### function Stack [3/3]

```C++
inline SR_HTYPES_NS::Stack::Stack (
    Stack && other
) noexcept
```




<hr>



### function Top 

```C++
inline SR_NODISCARD T & SR_HTYPES_NS::Stack::Top () 
```




<hr>



### function operator= 

```C++
inline Stack & SR_HTYPES_NS::Stack::operator= (
    const Stack & other
) 
```




<hr>



### function operator= 

```C++
inline Stack & SR_HTYPES_NS::Stack::operator= (
    Stack && other
) noexcept
```




<hr>



### function ~Stack 

```C++
inline SR_HTYPES_NS::Stack::~Stack () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/Stack.h`

