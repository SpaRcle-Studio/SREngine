

# Class SR\_HTYPES\_NS::TreeT

**template &lt;size\_t HASH\_SIZE, void  HASH\_FUNCTION&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**TreeT**](classSR__HTYPES__NS_1_1TreeT.md)



_Template for Merkle trees._ [More...](#detailed-description)

* `#include <MerkleTree.h>`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Statistics**](structSR__HTYPES__NS_1_1TreeT_1_1Statistics.md) <br>_Structure to hold statistical information._  |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; | [**MerkleHash**](#typedef-merklehash)  <br>_The type of hashes in the tree._  |
| typedef [**PathT**](classSR__HTYPES__NS_1_1PathT.md)&lt; HASH\_SIZE, HASH\_FUNCTION &gt; | [**MerklePath**](#typedef-merklepath)  <br>_The type of paths in the tree._  |
| typedef [**TreeT**](classSR__HTYPES__NS_1_1TreeT.md)&lt; HASH\_SIZE, HASH\_FUNCTION &gt; | [**MerkleTree**](#typedef-merkletree)  <br>_The type of the tree._  |




## Public Attributes

| Type | Name |
| ---: | :--- |
|  struct [**SR\_HTYPES\_NS::TreeT::Statistics**](structSR__HTYPES__NS_1_1TreeT_1_1Statistics.md) | [**statistics**](#variable-statistics)  <br>[_**Statistics**_](structSR__HTYPES__NS_1_1TreeT_1_1Statistics.md) _._ |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**TreeT**](#function-treet-16) () <br>_Constructs an empty tree._  |
|   | [**TreeT**](#function-treet-26) (const [**TreeT**](classSR__HTYPES__NS_1_1TreeT.md) & other) <br>_Copies a tree._  |
|   | [**TreeT**](#function-treet-36) ([**TreeT**](classSR__HTYPES__NS_1_1TreeT.md) && other) <br>_Moves a tree._  |
|   | [**TreeT**](#function-treet-46) (const std::vector&lt; uint8\_t &gt; & bytes) <br>_Deserialises a tree._  |
|   | [**TreeT**](#function-treet-56) (const std::vector&lt; uint8\_t &gt; & bytes, size\_t & position) <br>_Deserialises a tree._  |
|   | [**TreeT**](#function-treet-66) (const [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) & root) <br>_Constructs a tree containing one root hash._  |
|  void | [**deserialise**](#function-deserialise-12) (const std::vector&lt; uint8\_t &gt; & bytes) <br>_Deserialises a tree._  |
|  void | [**deserialise**](#function-deserialise-22) (const std::vector&lt; uint8\_t &gt; & bytes, size\_t & position) <br>_Deserialises a tree._  |
|  bool | [**empty**](#function-empty) () const<br>_Indicates whether the tree is empty._  |
|  void | [**flush\_to**](#function-flush_to) (size\_t index) <br>_Flush the tree to some leaf._  |
|  void | [**insert**](#function-insert-14) (const uint8\_t \* hash) <br>_Inserts a hash into the tree._  |
|  void | [**insert**](#function-insert-24) (const [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) & hash) <br>_Inserts a hash into the tree._  |
|  void | [**insert**](#function-insert-34) (const std::vector&lt; [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) &gt; & hashes) <br>_Inserts multiple hashes into the tree._  |
|  void | [**insert**](#function-insert-44) (const std::list&lt; [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) &gt; & hashes) <br>_Inserts multiple hashes into the tree._  |
|  bool | [**invariant**](#function-invariant) () <br>_Invariant of the tree._  |
|  const [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) & | [**leaf**](#function-leaf) (size\_t index) const<br>_Extract a leaf hash from the tree._  |
|  size\_t | [**max\_index**](#function-max_index) () const<br>_Maximum leaf index._  |
|  size\_t | [**min\_index**](#function-min_index) () const<br>_Minimum leaf index._  |
|  size\_t | [**num\_leaves**](#function-num_leaves) () const<br>_Number of leaves in the tree._  |
|   | [**vector&lt; uint8\_t &gt;**](#function-vector<-uint8_t->) () const<br>_Operator to serialise the tree._  |
|  [**MerkleTree**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merkletree) & | [**operator=**](#function-operator) (const [**MerkleTree**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merkletree) & other) <br>_Assigns a tree._  |
|  const [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) & | [**operator[]**](#function-operator_1) (size\_t index) const<br>_Operator to extract a leaf hash from the tree._  |
|  std::shared\_ptr&lt; [**MerklePath**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklepath) &gt; | [**past\_path**](#function-past_path) (size\_t index, size\_t as\_of) <br>_Extracts a past path from a leaf index to the root of the tree._  |
|  std::shared\_ptr&lt; [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) &gt; | [**past\_root**](#function-past_root) (size\_t index) <br>_Extracts a past root hash._  |
|  std::shared\_ptr&lt; [**MerklePath**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklepath) &gt; | [**path**](#function-path) (size\_t index) <br>_Extracts the path from a leaf index to the root of the tree._  |
|  void | [**retract\_to**](#function-retract_to) (size\_t index) <br>_Retracts a tree up to some leaf index._  |
|  const [**MerkleHash**](classSR__HTYPES__NS_1_1TreeT.md#typedef-merklehash) & | [**root**](#function-root) () <br>_Extracts the root hash of the tree._  |
|  void | [**serialise**](#function-serialise-12) (std::vector&lt; uint8\_t &gt; & bytes) <br>_Serialises the tree._  |
|  void | [**serialise**](#function-serialise-22) (size\_t from, size\_t to, std::vector&lt; uint8\_t &gt; & bytes) <br>_Serialises a segment of the tree._  |
|  size\_t | [**serialised\_size**](#function-serialised_size-12) () <br>_Computes the minumal number of bytes required to serialise the tree._  |
|  size\_t | [**serialised\_size**](#function-serialised_size-22) (size\_t from, size\_t to) <br>_The number of bytes required to serialise a segment of the tree._  |
|  size\_t | [**size**](#function-size) () <br>_Computes the size of the tree._  |
|  std::string | [**to\_string**](#function-to_string) (size\_t num\_bytes=HASH\_SIZE) const<br>_Prints an ASCII representation of the tree to a stream._  |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**walk\_to**](#function-walk_to) (size\_t index, bool update, const std::function&lt; bool([**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \*&, bool)&gt; && f) <br>_Walks along the path from the root of a tree to a leaf._  |
|   | [**~TreeT**](#function-treet) () <br>_Deconstructor._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**\_root**](#variable-_root)   = `nullptr`<br>_Current root node of the tree._  |
|  std::vector&lt; [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* &gt; | [**leaf\_nodes**](#variable-leaf_nodes)  <br>_Vector of leaf nodes current in the tree._  |
|  size\_t | [**num\_flushed**](#variable-num_flushed)   = `0`<br>_Number of flushed nodes._  |
|  std::vector&lt; [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* &gt; | [**uninserted\_leaf\_nodes**](#variable-uninserted_leaf_nodes)  <br>_Vector of leaf nodes to be inserted in the tree._  |
















## Protected Functions

| Type | Name |
| ---: | :--- |
|  void | [**compute\_root**](#function-compute_root) () <br>_Computes the root hash of the tree._  |
|  void | [**continue\_insertion\_stack**](#function-continue_insertion_stack) ([**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* n, [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* new\_leaf) <br>_Inserts one new leaf into the insertion stack._  |
|  void | [**hash**](#function-hash) ([**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* n, size\_t indent=2) const<br>_Computes the hash of a tree node._  |
|  void | [**insert\_leaf**](#function-insert_leaf) ([**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \*& root, [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* n) <br>_Inserts a new leaf into the tree._  |
|  void | [**insert\_leaves**](#function-insert_leaves) (bool complete=false) <br>_Inserts multiple new leaves into the tree._  |
|  const [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**leaf\_node**](#function-leaf_node) (size\_t index) const<br>_Finds the leaf node corresponding to_ `index` _._ |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**process\_insertion\_stack**](#function-process_insertion_stack) (bool complete=true) <br>_Processes the insertion stack/continuation._  |




## Detailed Description




**Template parameters:**


* `HASH_SIZE` Size of each hash in number of bytes 
* `HASH_FUNCTION` The hash function 




    
## Public Types Documentation




### typedef MerkleHash 

_The type of hashes in the tree._ 
```C++
typedef HashT<HASH_SIZE> SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::MerkleHash;
```




<hr>



### typedef MerklePath 

_The type of paths in the tree._ 
```C++
typedef PathT<HASH_SIZE, HASH_FUNCTION> SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::MerklePath;
```




<hr>



### typedef MerkleTree 

_The type of the tree._ 
```C++
typedef TreeT<HASH_SIZE, HASH_FUNCTION> SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::MerkleTree;
```




<hr>
## Public Attributes Documentation




### variable statistics 

[_**Statistics**_](structSR__HTYPES__NS_1_1TreeT_1_1Statistics.md) _._
```C++
struct SR_HTYPES_NS::TreeT::Statistics SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::statistics;
```




<hr>
## Public Functions Documentation




### function TreeT [1/6]

_Constructs an empty tree._ 
```C++
inline SR_HTYPES_NS::TreeT::TreeT () 
```




<hr>



### function TreeT [2/6]

_Copies a tree._ 
```C++
inline SR_HTYPES_NS::TreeT::TreeT (
    const TreeT & other
) 
```




<hr>



### function TreeT [3/6]

_Moves a tree._ 
```C++
inline SR_HTYPES_NS::TreeT::TreeT (
    TreeT && other
) 
```





**Parameters:**


* `other` MerkleTree to move 




        

<hr>



### function TreeT [4/6]

_Deserialises a tree._ 
```C++
inline SR_HTYPES_NS::TreeT::TreeT (
    const std::vector< uint8_t > & bytes
) 
```





**Parameters:**


* `bytes` Byte buffer containing a serialised tree 




        

<hr>



### function TreeT [5/6]

_Deserialises a tree._ 
```C++
inline SR_HTYPES_NS::TreeT::TreeT (
    const std::vector< uint8_t > & bytes,
    size_t & position
) 
```





**Parameters:**


* `bytes` Byte buffer containing a serialised tree 
* `position` Position of the first byte within `bytes` 




        

<hr>



### function TreeT [6/6]

_Constructs a tree containing one root hash._ 
```C++
inline SR_HTYPES_NS::TreeT::TreeT (
    const MerkleHash & root
) 
```





**Parameters:**


* `root` Root hash of the tree 




        

<hr>



### function deserialise [1/2]

_Deserialises a tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::deserialise (
    const std::vector< uint8_t > & bytes
) 
```





**Parameters:**


* `bytes` The vector of bytes to deserialise from 




        

<hr>



### function deserialise [2/2]

_Deserialises a tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::deserialise (
    const std::vector< uint8_t > & bytes,
    size_t & position
) 
```





**Parameters:**


* `bytes` The vector of bytes to deserialise from 
* `position` Position of the first byte in `bytes` 




        

<hr>



### function empty 

_Indicates whether the tree is empty._ 
```C++
inline bool SR_HTYPES_NS::TreeT::empty () const
```





**Returns:**

Boolean that indicates whether the tree is empty 





        

<hr>



### function flush\_to 

_Flush the tree to some leaf._ 
```C++
inline void SR_HTYPES_NS::TreeT::flush_to (
    size_t index
) 
```





**Parameters:**


* `index` Leaf index to flush the tree to 



**Note:**

This invalidates all indicies smaller than `index` and no paths from them to the root can be extracted anymore. 





        

<hr>



### function insert [1/4]

_Inserts a hash into the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::insert (
    const uint8_t * hash
) 
```





**Parameters:**


* `hash` MerkleHash to insert 




        

<hr>



### function insert [2/4]

_Inserts a hash into the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::insert (
    const MerkleHash & hash
) 
```





**Parameters:**


* `hash` MerkleHash to insert 




        

<hr>



### function insert [3/4]

_Inserts multiple hashes into the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::insert (
    const std::vector< MerkleHash > & hashes
) 
```





**Parameters:**


* `hashes` Vector of hashes to insert 




        

<hr>



### function insert [4/4]

_Inserts multiple hashes into the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::insert (
    const std::list< MerkleHash > & hashes
) 
```





**Parameters:**


* `hashes` [**List**](classSR__HTYPES__NS_1_1List.md) of hashes to insert 




        

<hr>



### function invariant 

_Invariant of the tree._ 
```C++
inline bool SR_HTYPES_NS::TreeT::invariant () 
```




<hr>



### function leaf 

_Extract a leaf hash from the tree._ 
```C++
inline const MerkleHash & SR_HTYPES_NS::TreeT::leaf (
    size_t index
) const
```





**Parameters:**


* `index` Leaf index of the leaf to extract 



**Returns:**

The leaf hash 





        

<hr>



### function max\_index 

_Maximum leaf index._ 
```C++
inline size_t SR_HTYPES_NS::TreeT::max_index () const
```





**Note:**

The greatest leaf index for which it is safe to extract roots and paths. 




**Returns:**

The maximum leaf index 





        

<hr>



### function min\_index 

_Minimum leaf index._ 
```C++
inline size_t SR_HTYPES_NS::TreeT::min_index () const
```





**Note:**

The smallest leaf index for which it is safe to extract roots and paths. 




**Returns:**

The minumum leaf index 





        

<hr>



### function num\_leaves 

_Number of leaves in the tree._ 
```C++
inline size_t SR_HTYPES_NS::TreeT::num_leaves () const
```





**Note:**

This is the abstract number of leaves in the tree (including flushed leaves), not the number of nodes in memory. 




**Returns:**

The number of leaves in the tree 





        

<hr>



### function vector&lt; uint8\_t &gt; 

_Operator to serialise the tree._ 
```C++
inline SR_HTYPES_NS::TreeT::vector< uint8_t > () const
```




<hr>



### function operator= 

_Assigns a tree._ 
```C++
inline MerkleTree & SR_HTYPES_NS::TreeT::operator= (
    const MerkleTree & other
) 
```





**Parameters:**


* `other` The tree to assign 



**Returns:**

The tree 





        

<hr>



### function operator[] 

_Operator to extract a leaf hash from the tree._ 
```C++
inline const MerkleHash & SR_HTYPES_NS::TreeT::operator[] (
    size_t index
) const
```





**Parameters:**


* `index` Leaf index of the leaf to extract 



**Returns:**

The leaf hash 





        

<hr>



### function past\_path 

_Extracts a past path from a leaf index to the root of the tree._ 
```C++
inline std::shared_ptr< MerklePath > SR_HTYPES_NS::TreeT::past_path (
    size_t index,
    size_t as_of
) 
```





**Parameters:**


* `index` The leaf index of the path to extract 
* `as_of` The maximum leaf index to consider 



**Returns:**

The past path 




**Note:**

This extracts a path at a past state, when `as_of` was the last, right-most leaf index in the tree. It is equivalent to retracting the tree to `as_of` and then extracting the path of `index`. 





        

<hr>



### function past\_root 

_Extracts a past root hash._ 
```C++
inline std::shared_ptr< MerkleHash > SR_HTYPES_NS::TreeT::past_root (
    size_t index
) 
```





**Parameters:**


* `index` The last leaf index to consider 



**Returns:**

The root hash 




**Note:**

This extracts the root hash of the tree at a past state, when `index` was the last, right-most leaf index in the tree. It is equivalent to retracting the tree to `index` and then extracting the root. 





        

<hr>



### function path 

_Extracts the path from a leaf index to the root of the tree._ 
```C++
inline std::shared_ptr< MerklePath > SR_HTYPES_NS::TreeT::path (
    size_t index
) 
```





**Parameters:**


* `index` The leaf index of the path to extract 



**Returns:**

The path 





        

<hr>



### function retract\_to 

_Retracts a tree up to some leaf index._ 
```C++
inline void SR_HTYPES_NS::TreeT::retract_to (
    size_t index
) 
```





**Parameters:**


* `index` Leaf index to retract the tree to 



**Note:**

This invalidates all indicies greater than `index` and no paths from them to the root can be extracted anymore. 





        

<hr>



### function root 

_Extracts the root hash of the tree._ 
```C++
inline const MerkleHash & SR_HTYPES_NS::TreeT::root () 
```





**Returns:**

The root hash 





        

<hr>



### function serialise [1/2]

_Serialises the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::serialise (
    std::vector< uint8_t > & bytes
) 
```





**Parameters:**


* `bytes` The vector of bytes to serialise to 




        

<hr>



### function serialise [2/2]

_Serialises a segment of the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::serialise (
    size_t from,
    size_t to,
    std::vector< uint8_t > & bytes
) 
```





**Parameters:**


* `from` Smalles leaf index to include 
* `to` Greatest leaf index to include 
* `bytes` The vector of bytes to serialise to 




        

<hr>



### function serialised\_size [1/2]

_Computes the minumal number of bytes required to serialise the tree._ 
```C++
inline size_t SR_HTYPES_NS::TreeT::serialised_size () 
```





**Returns:**

The number of bytes required to serialise the tree 





        

<hr>



### function serialised\_size [2/2]

_The number of bytes required to serialise a segment of the tree._ 
```C++
inline size_t SR_HTYPES_NS::TreeT::serialised_size (
    size_t from,
    size_t to
) 
```





**Parameters:**


* `from` The smallest leaf index to include 
* `to` The greatest leaf index to include 



**Returns:**

The number of bytes required to serialise the tree segment 





        

<hr>



### function size 

_Computes the size of the tree._ 
```C++
inline size_t SR_HTYPES_NS::TreeT::size () 
```





**Note:**

This is the number of nodes in the tree, including leaves and internal nodes. 




**Returns:**

The size of the tree 





        

<hr>



### function to\_string 

_Prints an ASCII representation of the tree to a stream._ 
```C++
inline std::string SR_HTYPES_NS::TreeT::to_string (
    size_t num_bytes=HASH_SIZE
) const
```





**Parameters:**


* `num_bytes` The number of bytes of each node hash to print 



**Returns:**

A string representing the tree 





        

<hr>



### function walk\_to 

_Walks along the path from the root of a tree to a leaf._ 
```C++
inline Node * SR_HTYPES_NS::TreeT::walk_to (
    size_t index,
    bool update,
    const std::function< bool( Node *&, bool)> && f
) 
```





**Parameters:**


* `index` The leaf index to walk to 
* `update` Flag to enable re-computation of node fields (like subtree size) while walking 
* `f` [**Function**](classSR__HTYPES__NS_1_1Function.md) to call for each node on the path; the Boolean indicates whether the current step is a right or left turn. 



**Returns:**

The final leaf node in the walk 





        

<hr>



### function ~TreeT 

_Deconstructor._ 
```C++
inline SR_HTYPES_NS::TreeT::~TreeT () 
```




<hr>
## Protected Attributes Documentation




### variable \_root 

_Current root node of the tree._ 
```C++
Node* SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::_root;
```




<hr>



### variable leaf\_nodes 

_Vector of leaf nodes current in the tree._ 
```C++
std::vector<Node*> SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::leaf_nodes;
```




<hr>



### variable num\_flushed 

_Number of flushed nodes._ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::num_flushed;
```




<hr>



### variable uninserted\_leaf\_nodes 

_Vector of leaf nodes to be inserted in the tree._ 
```C++
std::vector<Node*> SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::uninserted_leaf_nodes;
```





**Note:**

These nodes are conceptually inserted, but no [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) objects have been inserted for them yet. 





        

<hr>
## Protected Functions Documentation




### function compute\_root 

_Computes the root hash of the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::compute_root () 
```




<hr>



### function continue\_insertion\_stack 

_Inserts one new leaf into the insertion stack._ 
```C++
inline void SR_HTYPES_NS::TreeT::continue_insertion_stack (
    Node * n,
    Node * new_leaf
) 
```





**Parameters:**


* `n` Current root node 
* `new_leaf` New leaf node to insert 



**Note:**

This adds one new [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) to the insertion stack/continuation for efficient processing by process\_insertion\_stack() later. 





        

<hr>



### function hash 

_Computes the hash of a tree node._ 
```C++
inline void SR_HTYPES_NS::TreeT::hash (
    Node * n,
    size_t indent=2
) const
```





**Parameters:**


* `n` The tree node 
* `indent` Indentation of trace output 



**Note:**

This recurses down the child nodes to compute intermediate hashes, if required. 





        

<hr>



### function insert\_leaf 

_Inserts a new leaf into the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::insert_leaf (
    Node *& root,
    Node * n
) 
```





**Parameters:**


* `root` Current root node 
* `n` New leaf node to insert 




        

<hr>



### function insert\_leaves 

_Inserts multiple new leaves into the tree._ 
```C++
inline void SR_HTYPES_NS::TreeT::insert_leaves (
    bool complete=false
) 
```





**Parameters:**


* `complete` Indicates whether the insertion stack should be processed to completion after insertion 




        

<hr>



### function leaf\_node 

_Finds the leaf node corresponding to_ `index` _._
```C++
inline const Node * SR_HTYPES_NS::TreeT::leaf_node (
    size_t index
) const
```





**Parameters:**


* `index` The leaf node index 




        

<hr>



### function process\_insertion\_stack 

_Processes the insertion stack/continuation._ 
```C++
inline Node * SR_HTYPES_NS::TreeT::process_insertion_stack (
    bool complete=true
) 
```





**Parameters:**


* `complete` Indicates whether one element or the entire stack should be processed 




        

<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/MerkleTree.h`

