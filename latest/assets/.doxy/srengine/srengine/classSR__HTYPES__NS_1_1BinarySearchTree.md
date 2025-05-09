

# Class SR\_HTYPES\_NS::BinarySearchTree

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**BinarySearchTree**](classSR__HTYPES__NS_1_1BinarySearchTree.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**BinarySearchTree**](#function-binarysearchtree) (Comparator && comparator) <br> |
|  SR\_NODISCARD SR\_FORCE\_INLINE int32\_t SR\_FASTCALL | [**Compare**](#function-compare) (T \* pFirst, T \* pSecond) const<br> |
|  void | [**Insert**](#function-insert) (T \* pData, uint64\_t size) <br> |
|  SR\_NODISCARD [**Node**](structSR__HTYPES__NS_1_1Node.md) \* | [**Iterate**](#function-iterate) ([**Node**](structSR__HTYPES__NS_1_1Node.md) \* pCursor, T \* pData, int32\_t \* direction) const<br> |
|  SR\_NODISCARD T \* | [**Search**](#function-search) (T \* pData) const<br> |


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




### function BinarySearchTree 

```C++
inline explicit SR_HTYPES_NS::BinarySearchTree::BinarySearchTree (
    Comparator && comparator
) 
```




<hr>



### function Compare 

```C++
inline SR_NODISCARD SR_FORCE_INLINE int32_t SR_FASTCALL SR_HTYPES_NS::BinarySearchTree::Compare (
    T * pFirst,
    T * pSecond
) const
```




<hr>



### function Insert 

```C++
void SR_HTYPES_NS::BinarySearchTree::Insert (
    T * pData,
    uint64_t size
) 
```




<hr>



### function Iterate 

```C++
SR_NODISCARD Node * SR_HTYPES_NS::BinarySearchTree::Iterate (
    Node * pCursor,
    T * pData,
    int32_t * direction
) const
```




<hr>



### function Search 

```C++
SR_NODISCARD T * SR_HTYPES_NS::BinarySearchTree::Search (
    T * pData
) const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/BinarySearchTree.h`

