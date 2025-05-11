

# Class SR\_HTYPES\_NS::SafeVar

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SafeVar**](classSR__HTYPES__NS_1_1SafeVar.md)








Inherits the following classes: NonCopyable


































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Do**](#function-do-16) (const std::function&lt; void(T &data)&gt; & func) noexcept<br> |
|  void | [**Do**](#function-do-26) (const std::function&lt; void(const T &data)&gt; & func) noexcept const<br> |
|  U | [**Do**](#function-do-36) (const std::function&lt; U(const T &data)&gt; & func) noexcept const<br> |
|  U | [**Do**](#function-do-46) (const std::function&lt; U(T &data)&gt; & func) noexcept<br> |
|  void | [**Do**](#function-do-56) (const std::function&lt; void(T &)&gt; & func) noexcept<br> |
|  void | [**Do**](#function-do-66) (const std::function&lt; void(const T &)&gt; & func) noexcept const<br> |
|  SR\_NODISCARD T & | [**Get**](#function-get-12) () noexcept<br> |
|  SR\_NODISCARD const T & | [**Get**](#function-get-22) () noexcept const<br> |
|  void | [**Increment**](#function-increment) () noexcept<br> |
|  void | [**Lock**](#function-lock) () noexcept const<br> |
|  void | [**RecursiveLock**](#function-recursivelock) () noexcept const<br> |
|   | [**SafeVar**](#function-safevar-12) (const T & data) <br> |
|   | [**SafeVar**](#function-safevar-22) () = default<br> |
|  void | [**Unlock**](#function-unlock) () noexcept const<br> |
|   | [**operator bool**](#function-operator-bool) () noexcept const<br>_NOLINT._  |
|   | [**operator const T &**](#function-operator-const-t-&) () noexcept const<br> |
|  SR\_NODISCARD bool | [**operator!=**](#function-operator) (const [**SafeVar**](classSR__HTYPES__NS_1_1SafeVar.md)&lt; T &gt; & right) noexcept const<br> |
|  T & | [**operator\***](#function-operator_1) () noexcept const<br>_NOLINT._  |
|  T | [**operator-&gt;**](#function-operator_2) () noexcept const<br> |
|  [**SafeVar**](classSR__HTYPES__NS_1_1SafeVar.md)&lt; T &gt; & | [**operator=**](#function-operator_3) (const T & data) <br> |
|  SR\_NODISCARD bool | [**operator==**](#function-operator_4) (const [**SafeVar**](classSR__HTYPES__NS_1_1SafeVar.md)&lt; T &gt; & right) noexcept const<br> |




























## Public Functions Documentation




### function Do [1/6]

```C++
void SR_HTYPES_NS::SafeVar::Do (
    const std::function< void(T &data)> & func
) noexcept
```




<hr>



### function Do [2/6]

```C++
void SR_HTYPES_NS::SafeVar::Do (
    const std::function< void(const T &data)> & func
) noexcept const
```




<hr>



### function Do [3/6]

```C++
template<typename U>
U SR_HTYPES_NS::SafeVar::Do (
    const std::function< U(const T &data)> & func
) noexcept const
```




<hr>



### function Do [4/6]

```C++
template<typename U>
U SR_HTYPES_NS::SafeVar::Do (
    const std::function< U(T &data)> & func
) noexcept
```




<hr>



### function Do [5/6]

```C++
template<typename T>
void SR_HTYPES_NS::SafeVar::Do (
    const std::function< void(T &)> & func
) noexcept
```




<hr>



### function Do [6/6]

```C++
template<typename T>
void SR_HTYPES_NS::SafeVar::Do (
    const std::function< void(const T &)> & func
) noexcept const
```




<hr>



### function Get [1/2]

```C++
SR_NODISCARD T & SR_HTYPES_NS::SafeVar::Get () noexcept
```




<hr>



### function Get [2/2]

```C++
SR_NODISCARD const T & SR_HTYPES_NS::SafeVar::Get () noexcept const
```




<hr>



### function Increment 

```C++
void SR_HTYPES_NS::SafeVar::Increment () noexcept
```




<hr>



### function Lock 

```C++
void SR_HTYPES_NS::SafeVar::Lock () noexcept const
```




<hr>



### function RecursiveLock 

```C++
void SR_HTYPES_NS::SafeVar::RecursiveLock () noexcept const
```




<hr>



### function SafeVar [1/2]

```C++
SR_HTYPES_NS::SafeVar::SafeVar (
    const T & data
) 
```




<hr>



### function SafeVar [2/2]

```C++
SR_HTYPES_NS::SafeVar::SafeVar () = default
```




<hr>



### function Unlock 

```C++
void SR_HTYPES_NS::SafeVar::Unlock () noexcept const
```




<hr>



### function operator bool 

_NOLINT._ 
```C++
SR_HTYPES_NS::SafeVar::operator bool () noexcept const
```




<hr>



### function operator const T & 

```C++
SR_HTYPES_NS::SafeVar::operator const T & () noexcept const
```




<hr>



### function operator!= 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SafeVar::operator!= (
    const SafeVar < T > & right
) noexcept const
```




<hr>



### function operator\* 

_NOLINT._ 
```C++
T & SR_HTYPES_NS::SafeVar::operator* () noexcept const
```




<hr>



### function operator-&gt; 

```C++
T SR_HTYPES_NS::SafeVar::operator-> () noexcept const
```




<hr>



### function operator= 

```C++
SafeVar < T > & SR_HTYPES_NS::SafeVar::operator= (
    const T & data
) 
```




<hr>



### function operator== 

```C++
SR_NODISCARD bool SR_HTYPES_NS::SafeVar::operator== (
    const SafeVar < T > & right
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/SafeVariable.h`

