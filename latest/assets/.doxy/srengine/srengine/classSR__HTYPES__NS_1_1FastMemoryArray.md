

# Class SR\_HTYPES\_NS::FastMemoryArray

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef T | [**ValueType**](#typedef-valuetype)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**FastMemoryArray**](#function-fastmemoryarray-14) () = default<br> |
|   | [**FastMemoryArray**](#function-fastmemoryarray-24) (const [**FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md) & other) <br> |
|   | [**FastMemoryArray**](#function-fastmemoryarray-34) ([**FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md) && other) noexcept<br> |
|   | [**FastMemoryArray**](#function-fastmemoryarray-44) (const std::vector&lt; T &gt; & other) <br> |
|  SR\_NODISCARD SizeType | [**capacity**](#function-capacity) () noexcept const<br> |
|  void | [**clear**](#function-clear) () noexcept<br> |
|  SR\_NODISCARD T \* | [**data**](#function-data-12) () noexcept<br> |
|  SR\_NODISCARD const T \* | [**data**](#function-data-22) () noexcept const<br> |
|  SR\_NODISCARD bool | [**empty**](#function-empty) () noexcept const<br> |
|  [**FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md) & | [**operator=**](#function-operator) (const [**FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md) & other) <br> |
|  [**FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md) & | [**operator=**](#function-operator_1) ([**FastMemoryArray**](classSR__HTYPES__NS_1_1FastMemoryArray.md) && other) noexcept<br> |
|  SR\_NODISCARD T & | [**operator[]**](#function-operator_2) (SizeType index) noexcept<br> |
|  SR\_NODISCARD const T & | [**operator[]**](#function-operator_3) (SizeType index) noexcept const<br> |
|  void | [**push\_back**](#function-push_back-12) (const T & value) <br> |
|  void | [**push\_back**](#function-push_back-22) (T && value) <br> |
|  void | [**reserve**](#function-reserve) (SizeType newCapacity) <br> |
|  void | [**resize**](#function-resize) (SizeType newSize) <br> |
|  void | [**shrink\_to\_fit**](#function-shrink_to_fit) () <br> |
|  SR\_NODISCARD SizeType | [**size**](#function-size) () noexcept const<br> |
|   | [**~FastMemoryArray**](#function-fastmemoryarray) () <br> |




























## Public Types Documentation




### typedef ValueType 

```C++
using SR_HTYPES_NS::FastMemoryArray< T >::ValueType =  T;
```




<hr>
## Public Functions Documentation




### function FastMemoryArray [1/4]

```C++
SR_HTYPES_NS::FastMemoryArray::FastMemoryArray () = default
```




<hr>



### function FastMemoryArray [2/4]

```C++
inline SR_HTYPES_NS::FastMemoryArray::FastMemoryArray (
    const FastMemoryArray & other
) 
```




<hr>



### function FastMemoryArray [3/4]

```C++
inline SR_HTYPES_NS::FastMemoryArray::FastMemoryArray (
    FastMemoryArray && other
) noexcept
```




<hr>



### function FastMemoryArray [4/4]

```C++
inline SR_HTYPES_NS::FastMemoryArray::FastMemoryArray (
    const std::vector< T > & other
) 
```




<hr>



### function capacity 

```C++
inline SR_NODISCARD SizeType SR_HTYPES_NS::FastMemoryArray::capacity () noexcept const
```




<hr>



### function clear 

```C++
inline void SR_HTYPES_NS::FastMemoryArray::clear () noexcept
```




<hr>



### function data [1/2]

```C++
inline SR_NODISCARD T * SR_HTYPES_NS::FastMemoryArray::data () noexcept
```




<hr>



### function data [2/2]

```C++
inline SR_NODISCARD const T * SR_HTYPES_NS::FastMemoryArray::data () noexcept const
```




<hr>



### function empty 

```C++
inline SR_NODISCARD bool SR_HTYPES_NS::FastMemoryArray::empty () noexcept const
```




<hr>



### function operator= 

```C++
inline FastMemoryArray & SR_HTYPES_NS::FastMemoryArray::operator= (
    const FastMemoryArray & other
) 
```




<hr>



### function operator= 

```C++
inline FastMemoryArray & SR_HTYPES_NS::FastMemoryArray::operator= (
    FastMemoryArray && other
) noexcept
```




<hr>



### function operator[] 

```C++
inline SR_NODISCARD T & SR_HTYPES_NS::FastMemoryArray::operator[] (
    SizeType index
) noexcept
```




<hr>



### function operator[] 

```C++
inline SR_NODISCARD const T & SR_HTYPES_NS::FastMemoryArray::operator[] (
    SizeType index
) noexcept const
```




<hr>



### function push\_back [1/2]

```C++
inline void SR_HTYPES_NS::FastMemoryArray::push_back (
    const T & value
) 
```




<hr>



### function push\_back [2/2]

```C++
inline void SR_HTYPES_NS::FastMemoryArray::push_back (
    T && value
) 
```




<hr>



### function reserve 

```C++
inline void SR_HTYPES_NS::FastMemoryArray::reserve (
    SizeType newCapacity
) 
```




<hr>



### function resize 

```C++
inline void SR_HTYPES_NS::FastMemoryArray::resize (
    SizeType newSize
) 
```




<hr>



### function shrink\_to\_fit 

```C++
inline void SR_HTYPES_NS::FastMemoryArray::shrink_to_fit () 
```




<hr>



### function size 

```C++
inline SR_NODISCARD SizeType SR_HTYPES_NS::FastMemoryArray::size () noexcept const
```




<hr>



### function ~FastMemoryArray 

```C++
inline SR_HTYPES_NS::FastMemoryArray::~FastMemoryArray () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/FastMemoryArray.h`

