

# Class SR\_HTYPES\_NS::Regex



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Regex**](classSR__HTYPES__NS_1_1Regex.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  SR\_NODISCARD std::string | [**Prefix**](#function-prefix) () noexcept const<br> |
|   | [**Regex**](#function-regex-13) () = default<br> |
|   | [**Regex**](#function-regex-23) (const std::string & regex) <br> |
|   | [**Regex**](#function-regex-33) ([**Regex**](classSR__HTYPES__NS_1_1Regex.md) && other) noexcept<br> |
|  bool | [**Search**](#function-search) (const std::string & input) <br> |
|  SR\_NODISCARD uint64\_t | [**Size**](#function-size) () noexcept const<br> |
|  SR\_NODISCARD std::string | [**Suffix**](#function-suffix) () noexcept const<br> |
|  [**Regex**](classSR__HTYPES__NS_1_1Regex.md) & | [**operator=**](#function-operator) ([**Regex**](classSR__HTYPES__NS_1_1Regex.md) && other) noexcept<br> |
|  SR\_NODISCARD std::string | [**operator[]**](#function-operator_1) (int64\_t index) noexcept const<br> |




























## Public Functions Documentation




### function Prefix 

```C++
SR_NODISCARD std::string SR_HTYPES_NS::Regex::Prefix () noexcept const
```




<hr>



### function Regex [1/3]

```C++
SR_HTYPES_NS::Regex::Regex () = default
```




<hr>



### function Regex [2/3]

```C++
SR_HTYPES_NS::Regex::Regex (
    const std::string & regex
) 
```




<hr>



### function Regex [3/3]

```C++
SR_HTYPES_NS::Regex::Regex (
    Regex && other
) noexcept
```



NOLINT 


        

<hr>



### function Search 

```C++
bool SR_HTYPES_NS::Regex::Search (
    const std::string & input
) 
```




<hr>



### function Size 

```C++
SR_NODISCARD uint64_t SR_HTYPES_NS::Regex::Size () noexcept const
```




<hr>



### function Suffix 

```C++
SR_NODISCARD std::string SR_HTYPES_NS::Regex::Suffix () noexcept const
```




<hr>



### function operator= 

```C++
Regex & SR_HTYPES_NS::Regex::operator= (
    Regex && other
) noexcept
```




<hr>



### function operator[] 

```C++
SR_NODISCARD std::string SR_HTYPES_NS::Regex::operator[] (
    int64_t index
) noexcept const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Regex.h`

