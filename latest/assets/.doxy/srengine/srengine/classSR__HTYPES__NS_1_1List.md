

# Class SR\_HTYPES\_NS::List

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**List**](classSR__HTYPES__NS_1_1List.md)










































## Public Functions

| Type | Name |
| ---: | :--- |
|  T | [**Get**](#function-get) (unsigned int id) <br> |
|   | [**List**](#function-list-14) () <br> |
|   | [**List**](#function-list-24) ([**List**](classSR__HTYPES__NS_1_1List.md) & list) <br> |
|   | [**List**](#function-list-34) (const [**List**](classSR__HTYPES__NS_1_1List.md) & list) <br> |
|   | [**List**](#function-list-44) (std::vector&lt; T &gt; list) <br> |
|  void | [**PushBack**](#function-pushback) (T value) <br> |
|  void | [**Set**](#function-set) (unsigned int id, T value) <br> |
|  size\_t | [**Size**](#function-size) () const<br> |
|  const T & | [**operator[]**](#function-operator) (size\_t id) const<br> |
|  T & | [**operator[]**](#function-operator_1) (size\_t id) <br> |
|   | [**~List**](#function-list) () <br> |




























## Public Functions Documentation




### function Get 

```C++
inline T SR_HTYPES_NS::List::Get (
    unsigned int id
) 
```




<hr>



### function List [1/4]

```C++
inline SR_HTYPES_NS::List::List () 
```




<hr>



### function List [2/4]

```C++
inline SR_HTYPES_NS::List::List (
    List & list
) 
```




<hr>



### function List [3/4]

```C++
inline SR_HTYPES_NS::List::List (
    const List & list
) 
```




<hr>



### function List [4/4]

```C++
inline explicit SR_HTYPES_NS::List::List (
    std::vector< T > list
) 
```




<hr>



### function PushBack 

```C++
inline void SR_HTYPES_NS::List::PushBack (
    T value
) 
```




<hr>



### function Set 

```C++
inline void SR_HTYPES_NS::List::Set (
    unsigned int id,
    T value
) 
```




<hr>



### function Size 

```C++
inline size_t SR_HTYPES_NS::List::Size () const
```




<hr>



### function operator[] 

```C++
inline const T & SR_HTYPES_NS::List::operator[] (
    size_t id
) const
```




<hr>



### function operator[] 

```C++
inline T & SR_HTYPES_NS::List::operator[] (
    size_t id
) 
```




<hr>



### function ~List 

```C++
inline SR_HTYPES_NS::List::~List () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/List.h`

