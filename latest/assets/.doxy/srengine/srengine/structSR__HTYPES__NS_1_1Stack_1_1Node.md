

# Struct SR\_HTYPES\_NS::Stack::Node



[**ClassList**](annotated.md) **>** [**Node**](structSR__HTYPES__NS_1_1Stack_1_1Node.md)








Inherits the following classes: [SR\_UTILS\_NS::NonCopyable](classSR__UTILS__NS_1_1NonCopyable.md)






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  T | [**data**](#variable-data)  <br> |
|  Node \* | [**pData**](#variable-pdata)   = `nullptr`<br> |
































## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**Node**](#function-node-12) (T && data) <br> |
|   | [**Node**](#function-node-22) (const T & data) <br> |


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




### variable data 

```C++
T SR_HTYPES_NS::Stack< T >::Node::data;
```




<hr>



### variable pData 

```C++
Node* SR_HTYPES_NS::Stack< T >::Node::pData;
```




<hr>
## Public Functions Documentation




### function Node [1/2]

```C++
inline explicit Node::Node (
    T && data
) 
```




<hr>



### function Node [2/2]

```C++
inline explicit Node::Node (
    const T & data
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/Stack.h`

