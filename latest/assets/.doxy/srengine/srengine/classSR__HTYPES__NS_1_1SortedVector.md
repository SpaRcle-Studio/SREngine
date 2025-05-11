

# Class SR\_HTYPES\_NS::SortedVector

**template &lt;typename T, typename Predicate&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**SortedVector**](classSR__HTYPES__NS_1_1SortedVector.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename std::vector&lt; T &gt;::const\_iterator | [**ConstIterator**](#typedef-constiterator)  <br> |
| typedef typename std::vector&lt; T &gt;::iterator | [**Iterator**](#typedef-iterator)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Add**](#function-add-12) (const T & value) <br> |
|  void | [**Add**](#function-add-22) (T && value) <br> |
|  SR\_NODISCARD SR\_CONSTEXPR uint64\_t | [**Capacity**](#function-capacity) () const<br> |
|  void | [**Clear**](#function-clear) () <br> |
|  SR\_NODISCARD SR\_CONSTEXPR T \* | [**Data**](#function-data-12) () <br> |
|  SR\_NODISCARD SR\_CONSTEXPR const T \* | [**Data**](#function-data-22) () const<br> |
|  SR\_NODISCARD SR\_CONSTEXPR bool | [**Empty**](#function-empty) () const<br> |
|  void | [**Erase**](#function-erase) (Iterator it) <br> |
|  SR\_NODISCARD Iterator | [**GetOrCreate**](#function-getorcreate) (const Ty & value, const CustomPred & predicate) <br> |
|  void | [**Insert**](#function-insert) (Iterator it, const T & value) <br> |
|  SR\_NODISCARD Iterator | [**LowerBound**](#function-lowerbound-12) (const Ty & value) <br> |
|  SR\_NODISCARD Iterator | [**LowerBound**](#function-lowerbound-22) (const Ty & value, const CustomPred & predicate) <br> |
|  bool | [**Remove**](#function-remove) (const T & value) <br> |
|  void | [**Reserve**](#function-reserve) (uint64\_t size) <br> |
|  void | [**ShrunkToFit**](#function-shrunktofit) () <br> |
|  SR\_NODISCARD SR\_CONSTEXPR uint64\_t | [**Size**](#function-size) () const<br> |
|   | [**SortedVector**](#function-sortedvector-12) () = default<br> |
|   | [**SortedVector**](#function-sortedvector-22) ([**SortedVector**](classSR__HTYPES__NS_1_1SortedVector.md) && other) noexcept<br> |
|  SR\_NODISCARD T \* | [**UpperBound**](#function-upperbound) (FwdIt pStart, const FwdIt pEnd, const Ty & value, const CustomPred & predicate=CustomPred()) <br> |
|  SR\_NODISCARD SR\_CONSTEXPR Iterator | [**begin**](#function-begin-12) () <br> |
|  SR\_NODISCARD SR\_CONSTEXPR ConstIterator | [**begin**](#function-begin-22) () const<br> |
|  SR\_NODISCARD SR\_CONSTEXPR uint64\_t | [**capacity**](#function-capacity) () const<br> |
|  SR\_NODISCARD SR\_CONSTEXPR T \* | [**data**](#function-data-12) () <br> |
|  SR\_NODISCARD SR\_CONSTEXPR const T \* | [**data**](#function-data-22) () const<br> |
|  SR\_NODISCARD SR\_CONSTEXPR bool | [**empty**](#function-empty) () const<br> |
|  SR\_NODISCARD SR\_CONSTEXPR Iterator | [**end**](#function-end-12) () <br> |
|  SR\_NODISCARD SR\_CONSTEXPR ConstIterator | [**end**](#function-end-22) () const<br> |
|  [**SortedVector**](classSR__HTYPES__NS_1_1SortedVector.md) & | [**operator=**](#function-operator) ([**SortedVector**](classSR__HTYPES__NS_1_1SortedVector.md) && other) noexcept<br> |
|  SR\_NODISCARD SR\_CONSTEXPR T & | [**operator[]**](#function-operator_1) (uint64\_t index) <br> |
|  SR\_NODISCARD SR\_CONSTEXPR const T & | [**operator[]**](#function-operator_2) (uint64\_t index) const<br> |
|  SR\_NODISCARD SR\_CONSTEXPR uint64\_t | [**size**](#function-size) () const<br> |




























## Public Types Documentation




### typedef ConstIterator 

```C++
using SR_HTYPES_NS::SortedVector< T, Predicate >::ConstIterator =  typename std::vector<T>::const_iterator;
```




<hr>



### typedef Iterator 

```C++
using SR_HTYPES_NS::SortedVector< T, Predicate >::Iterator =  typename std::vector<T>::iterator;
```




<hr>
## Public Functions Documentation




### function Add [1/2]

```C++
inline void SR_HTYPES_NS::SortedVector::Add (
    const T & value
) 
```




<hr>



### function Add [2/2]

```C++
inline void SR_HTYPES_NS::SortedVector::Add (
    T && value
) 
```




<hr>



### function Capacity 

```C++
inline SR_NODISCARD SR_CONSTEXPR uint64_t SR_HTYPES_NS::SortedVector::Capacity () const
```




<hr>



### function Clear 

```C++
inline void SR_HTYPES_NS::SortedVector::Clear () 
```




<hr>



### function Data [1/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR T * SR_HTYPES_NS::SortedVector::Data () 
```




<hr>



### function Data [2/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR const T * SR_HTYPES_NS::SortedVector::Data () const
```




<hr>



### function Empty 

```C++
inline SR_NODISCARD SR_CONSTEXPR bool SR_HTYPES_NS::SortedVector::Empty () const
```




<hr>



### function Erase 

```C++
inline void SR_HTYPES_NS::SortedVector::Erase (
    Iterator it
) 
```




<hr>



### function GetOrCreate 

```C++
template<class Ty, typename CustomPred>
inline SR_NODISCARD Iterator SR_HTYPES_NS::SortedVector::GetOrCreate (
    const Ty & value,
    const CustomPred & predicate
) 
```




<hr>



### function Insert 

```C++
inline void SR_HTYPES_NS::SortedVector::Insert (
    Iterator it,
    const T & value
) 
```




<hr>



### function LowerBound [1/2]

```C++
template<class Ty>
inline SR_NODISCARD Iterator SR_HTYPES_NS::SortedVector::LowerBound (
    const Ty & value
) 
```




<hr>



### function LowerBound [2/2]

```C++
template<class Ty, typename CustomPred>
inline SR_NODISCARD Iterator SR_HTYPES_NS::SortedVector::LowerBound (
    const Ty & value,
    const CustomPred & predicate
) 
```




<hr>



### function Remove 

```C++
inline bool SR_HTYPES_NS::SortedVector::Remove (
    const T & value
) 
```




<hr>



### function Reserve 

```C++
inline void SR_HTYPES_NS::SortedVector::Reserve (
    uint64_t size
) 
```




<hr>



### function ShrunkToFit 

```C++
inline void SR_HTYPES_NS::SortedVector::ShrunkToFit () 
```




<hr>



### function Size 

```C++
inline SR_NODISCARD SR_CONSTEXPR uint64_t SR_HTYPES_NS::SortedVector::Size () const
```




<hr>



### function SortedVector [1/2]

```C++
SR_HTYPES_NS::SortedVector::SortedVector () = default
```




<hr>



### function SortedVector [2/2]

```C++
inline SR_HTYPES_NS::SortedVector::SortedVector (
    SortedVector && other
) noexcept
```




<hr>



### function UpperBound 

```C++
template<class FwdIt, class Ty, typename CustomPred>
inline SR_NODISCARD T * SR_HTYPES_NS::SortedVector::UpperBound (
    FwdIt pStart,
    const FwdIt pEnd,
    const Ty & value,
    const CustomPred & predicate=CustomPred()
) 
```




<hr>



### function begin [1/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR Iterator SR_HTYPES_NS::SortedVector::begin () 
```




<hr>



### function begin [2/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR ConstIterator SR_HTYPES_NS::SortedVector::begin () const
```




<hr>



### function capacity 

```C++
inline SR_NODISCARD SR_CONSTEXPR uint64_t SR_HTYPES_NS::SortedVector::capacity () const
```




<hr>



### function data [1/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR T * SR_HTYPES_NS::SortedVector::data () 
```




<hr>



### function data [2/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR const T * SR_HTYPES_NS::SortedVector::data () const
```




<hr>



### function empty 

```C++
inline SR_NODISCARD SR_CONSTEXPR bool SR_HTYPES_NS::SortedVector::empty () const
```




<hr>



### function end [1/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR Iterator SR_HTYPES_NS::SortedVector::end () 
```




<hr>



### function end [2/2]

```C++
inline SR_NODISCARD SR_CONSTEXPR ConstIterator SR_HTYPES_NS::SortedVector::end () const
```




<hr>



### function operator= 

```C++
inline SortedVector & SR_HTYPES_NS::SortedVector::operator= (
    SortedVector && other
) noexcept
```




<hr>



### function operator[] 

```C++
inline SR_NODISCARD SR_CONSTEXPR T & SR_HTYPES_NS::SortedVector::operator[] (
    uint64_t index
) 
```




<hr>



### function operator[] 

```C++
inline SR_NODISCARD SR_CONSTEXPR const T & SR_HTYPES_NS::SortedVector::operator[] (
    uint64_t index
) const
```




<hr>



### function size 

```C++
inline SR_NODISCARD SR_CONSTEXPR uint64_t SR_HTYPES_NS::SortedVector::size () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/SortedVector.h`

