

# Struct SR\_HTYPES\_NS::TreeT::Statistics



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**TreeT**](classSR__HTYPES__NS_1_1TreeT.md) **>** [**Statistics**](structSR__HTYPES__NS_1_1TreeT_1_1Statistics.md)



_Structure to hold statistical information._ 

* `#include <MerkleTree.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  size\_t | [**num\_flush**](#variable-num_flush)   = `0`<br>_The number of flush\_to() opertations performed on the tree._  |
|  size\_t | [**num\_hash**](#variable-num_hash)   = `0`<br>_The number of hashes taken by the tree via hash()_  |
|  size\_t | [**num\_insert**](#variable-num_insert)   = `0`<br>_The number of insert() opertations performed on the tree._  |
|  size\_t | [**num\_past\_paths**](#variable-num_past_paths)   = `0`<br>_The number of past paths extracted from the tree via past\_path()_  |
|  size\_t | [**num\_past\_root**](#variable-num_past_root)   = `0`<br>_The number of past\_root() opertations performed on the tree._  |
|  size\_t | [**num\_paths**](#variable-num_paths)   = `0`<br>_The number of paths extracted from the tree via path()_  |
|  size\_t | [**num\_retract**](#variable-num_retract)   = `0`<br>_The number of retract\_to() opertations performed on the tree._  |
|  size\_t | [**num\_root**](#variable-num_root)   = `0`<br>_The number of root() opertations performed on the tree._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|  std::string | [**to\_string**](#function-to_string) () const<br>_String representation of the statistics._  |




























## Public Attributes Documentation




### variable num\_flush 

_The number of flush\_to() opertations performed on the tree._ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_flush;
```




<hr>



### variable num\_hash 

_The number of hashes taken by the tree via hash()_ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_hash;
```




<hr>



### variable num\_insert 

_The number of insert() opertations performed on the tree._ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_insert;
```




<hr>



### variable num\_past\_paths 

_The number of past paths extracted from the tree via past\_path()_ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_past_paths;
```




<hr>



### variable num\_past\_root 

_The number of past\_root() opertations performed on the tree._ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_past_root;
```




<hr>



### variable num\_paths 

_The number of paths extracted from the tree via path()_ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_paths;
```




<hr>



### variable num\_retract 

_The number of retract\_to() opertations performed on the tree._ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_retract;
```




<hr>



### variable num\_root 

_The number of root() opertations performed on the tree._ 
```C++
size_t SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::Statistics::num_root;
```




<hr>
## Public Functions Documentation




### function to\_string 

_String representation of the statistics._ 
```C++
inline std::string SR_HTYPES_NS::TreeT::Statistics::to_string () const
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/MerkleTree.h`

