

# Struct SR\_HTYPES\_NS::TreeT::Node



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**TreeT**](classSR__HTYPES__NS_1_1TreeT.md) **>** [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md)



_The structure of tree nodes._ 

* `#include <MerkleTree.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**dirty**](#variable-dirty)  <br>_Dirty flag for the hash._  |
|  [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; | [**hash**](#variable-hash)  <br>_The MerkleHash of the node._  |
|  uint8\_t | [**height**](#variable-height)  <br>_The height of the subtree._  |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**left**](#variable-left)  <br>_The left child of the node._  |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**right**](#variable-right)  <br>_The right child of the node._  |
|  size\_t | [**size**](#variable-size)  <br>_The size of the subtree._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  bool | [**invariant**](#function-invariant) () <br>_Checks invariant of a tree node._  |
|  bool | [**is\_full**](#function-is_full) () const<br>_Indicates whether a subtree is full._  |
|  void | [**update\_sizes**](#function-update_sizes) () <br>_Updates the tree size and height of the subtree under a node._  |
|   | [**~Node**](#function-node) () <br> |


## Public Static Functions

| Type | Name |
| ---: | :--- |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**copy\_node**](#function-copy_node) (const [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* from, std::vector&lt; [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* &gt; \* leaf\_nodes=nullptr, size\_t \* num\_flushed=nullptr, size\_t min\_index=0, size\_t max\_index=SIZE\_MAX, size\_t indent=0) <br>_Copies a tree node._  |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**make**](#function-make-12) (const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; & hash) <br>_Constructs a new tree node._  |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**make**](#function-make-22) ([**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* left, [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* right) <br>_Constructs a new tree node._  |


























## Public Attributes Documentation




### variable dirty 

_Dirty flag for the hash._ 
```C++
bool SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Node::dirty;
```





**Note:**

The `hash` is only correct if this flag is false, otherwise it needs to be computed by calling hash() on the node. 





        

<hr>



### variable hash 

_The MerkleHash of the node._ 
```C++
HashT<HASH_SIZE> SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Node::hash;
```




<hr>



### variable height 

_The height of the subtree._ 
```C++
uint8_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Node::height;
```




<hr>



### variable left 

_The left child of the node._ 
```C++
Node* SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Node::left;
```




<hr>



### variable right 

_The right child of the node._ 
```C++
Node* SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Node::right;
```




<hr>



### variable size 

_The size of the subtree._ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Node::size;
```




<hr>
## Public Functions Documentation




### function invariant 

_Checks invariant of a tree node._ 
```C++
inline bool SR_HTYPES_NS::TreeT::Node::invariant () 
```





**Note:**

This indicates whether some basic properties of the tree construction are violated. 





        

<hr>



### function is\_full 

_Indicates whether a subtree is full._ 
```C++
inline bool SR_HTYPES_NS::TreeT::Node::is_full () const
```





**Note:**

A subtree is full if the number of nodes under a tree is 2\*\*height-1. 





        

<hr>



### function update\_sizes 

_Updates the tree size and height of the subtree under a node._ 
```C++
inline void SR_HTYPES_NS::TreeT::Node::update_sizes () 
```




<hr>



### function ~Node 

```C++
inline SR_HTYPES_NS::TreeT::Node::~Node () 
```




<hr>
## Public Static Functions Documentation




### function copy\_node 

_Copies a tree node._ 
```C++
static inline Node * SR_HTYPES_NS::TreeT::Node::copy_node (
    const Node * from,
    std::vector< Node * > * leaf_nodes=nullptr,
    size_t * num_flushed=nullptr,
    size_t min_index=0,
    size_t max_index=SIZE_MAX,
    size_t indent=0
) 
```





**Parameters:**


* `from` [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) to copy 
* `leaf_nodes` Current leaf nodes of the tree 
* `num_flushed` Number of flushed nodes of the tree 
* `min_index` Minimum leaf index of the tree 
* `max_index` Maximum leaf index of the tree 
* `indent` Indentation of trace output 




        

<hr>



### function make [1/2]

_Constructs a new tree node._ 
```C++
static inline Node * SR_HTYPES_NS::TreeT::Node::make (
    const HashT < HASH_SIZE > & hash
) 
```





**Parameters:**


* `hash` The hash of the node 




        

<hr>



### function make [2/2]

_Constructs a new tree node._ 
```C++
static inline Node * SR_HTYPES_NS::TreeT::Node::make (
    Node * left,
    Node * right
) 
```





**Parameters:**


* `left` The left child of the new node 
* `right` The right child of the new node 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/MerkleTree.h`

