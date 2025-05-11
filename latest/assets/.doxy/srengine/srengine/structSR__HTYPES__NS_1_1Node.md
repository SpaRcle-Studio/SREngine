

# Struct SR\_HTYPES\_NS::Node



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**Node**](structSR__HTYPES__NS_1_1Node.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  void \* | [**pData**](#variable-pdata)   = `nullptr`<br> |
|  [**Node**](structSR__HTYPES__NS_1_1Node.md) \* | [**pNext**](#variable-pnext)   = `nullptr`<br> |
|  [**Node**](structSR__HTYPES__NS_1_1Node.md) \* | [**pPrev**](#variable-pprev)   = `nullptr`<br> |
|  uint64\_t | [**size**](#variable-size)   = `0`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Node**](#function-node) (void \* pData, uint64\_t size) <br> |
|   | [**~Node**](#function-node) () override<br> |


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






## Public Attributes Documentation




### variable pData 

```C++
void* SR_HTYPES_NS::Node::pData;
```




<hr>



### variable pNext 

```C++
Node* SR_HTYPES_NS::Node::pNext;
```




<hr>



### variable pPrev 

```C++
Node* SR_HTYPES_NS::Node::pPrev;
```




<hr>



### variable size 

```C++
uint64_t SR_HTYPES_NS::Node::size;
```




<hr>
## Public Functions Documentation




### function Node 

```C++
inline SR_HTYPES_NS::Node::Node (
    void * pData,
    uint64_t size
) 
```




<hr>



### function ~Node 

```C++
inline SR_HTYPES_NS::Node::~Node () override
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/Node.h`

