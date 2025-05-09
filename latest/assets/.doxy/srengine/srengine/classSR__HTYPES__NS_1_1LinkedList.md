

# Class SR\_HTYPES\_NS::LinkedList

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**LinkedList**](classSR__HTYPES__NS_1_1LinkedList.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|  void | [**Insert**](#function-insert) (uint64\_t index, T \* pData, uint64\_t size) <br> |
|  SR\_NODISCARD [**Node**](structSR__HTYPES__NS_1_1Node.md) \* | [**Iterate**](#function-iterate) (uint64\_t index) const<br> |
|   | [**LinkedList**](#function-linkedlist) () = default<br> |
|  void | [**Remove**](#function-remove) (uint64\_t index) <br> |
|  T \* | [**Retrieve**](#function-retrieve) (uint64\_t index) <br> |
|  uint64\_t | [**Search**](#function-search) (T \* pQuery, const Comparator & comparator) <br> |
|  void | [**Sort**](#function-sort) (const Comparator & comparator) <br> |
|   | [**~LinkedList**](#function-linkedlist) () override<br> |


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






## Public Functions Documentation




### function Insert 

```C++
void SR_HTYPES_NS::LinkedList::Insert (
    uint64_t index,
    T * pData,
    uint64_t size
) 
```




<hr>



### function Iterate 

```C++
SR_NODISCARD Node * SR_HTYPES_NS::LinkedList::Iterate (
    uint64_t index
) const
```




<hr>



### function LinkedList 

```C++
SR_HTYPES_NS::LinkedList::LinkedList () = default
```




<hr>



### function Remove 

```C++
void SR_HTYPES_NS::LinkedList::Remove (
    uint64_t index
) 
```




<hr>



### function Retrieve 

```C++
T * SR_HTYPES_NS::LinkedList::Retrieve (
    uint64_t index
) 
```




<hr>



### function Search 

```C++
uint64_t SR_HTYPES_NS::LinkedList::Search (
    T * pQuery,
    const Comparator & comparator
) 
```




<hr>



### function Sort 

```C++
void SR_HTYPES_NS::LinkedList::Sort (
    const Comparator & comparator
) 
```




<hr>



### function ~LinkedList 

```C++
SR_HTYPES_NS::LinkedList::~LinkedList () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/LinkedList.h`

