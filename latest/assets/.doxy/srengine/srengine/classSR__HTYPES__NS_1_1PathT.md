

# Class SR\_HTYPES\_NS::PathT

**template &lt;size\_t HASH\_SIZE, void  HASH\_FUNCTION&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**PathT**](classSR__HTYPES__NS_1_1PathT.md)



_Template for Merkle paths._ [More...](#detailed-description)

* `#include <MerkleTree.h>`















## Classes

| Type | Name |
| ---: | :--- |
| struct | [**Element**](structSR__HTYPES__NS_1_1PathT_1_1Element.md) <br>_MerklePath element._  |


## Public Types

| Type | Name |
| ---: | :--- |
| enum  | [**Direction**](#enum-direction)  <br>_MerklePath direction._  |
| typedef std::list&lt; [**Element**](structSR__HTYPES__NS_1_1PathT_1_1Element.md) &gt;::const\_iterator | [**const\_iterator**](#typedef-const_iterator)  <br>_Iterator for path elements._  |




















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**PathT**](#function-patht-15) (const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; & leaf, size\_t leaf\_index, std::list&lt; [**Element**](structSR__HTYPES__NS_1_1PathT_1_1Element.md) &gt; && elements, size\_t max\_index) <br>_MerklePath constructor._  |
|   | [**PathT**](#function-patht-25) (const [**PathT**](classSR__HTYPES__NS_1_1PathT.md) & other) <br>_MerklePath copy constructor._  |
|   | [**PathT**](#function-patht-35) ([**PathT**](classSR__HTYPES__NS_1_1PathT.md) && other) <br>_MerklePath move constructor._  |
|   | [**PathT**](#function-patht-45) (const std::vector&lt; uint8\_t &gt; & bytes) <br>_Deserialises a path._  |
|   | [**PathT**](#function-patht-55) (const std::vector&lt; uint8\_t &gt; & bytes, size\_t & position) <br>_Deserialises a path._  |
|  [**const\_iterator**](classSR__HTYPES__NS_1_1PathT.md#typedef-const_iterator) | [**begin**](#function-begin) () const<br>_Start iterator for path elements._  |
|  void | [**deserialise**](#function-deserialise-12) (const std::vector&lt; uint8\_t &gt; & bytes, size\_t & position) <br>_Deserialises a path._  |
|  void | [**deserialise**](#function-deserialise-22) (const std::vector&lt; uint8\_t &gt; & bytes) <br>_Deserialises a path._  |
|  [**const\_iterator**](classSR__HTYPES__NS_1_1PathT.md#typedef-const_iterator) | [**end**](#function-end) () const<br>_End iterator for path elements._  |
|  const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; & | [**leaf**](#function-leaf) () const<br>_The leaf hash of the path._  |
|  size\_t | [**leaf\_index**](#function-leaf_index) () const<br>_Index of the leaf of the path._  |
|  size\_t | [**max\_index**](#function-max_index) () const<br>_Maximum index of the tree at the time the path was extracted._  |
|   | [**vector&lt; uint8\_t &gt;**](#function-vector-uint8_t) () const<br>_Conversion operator to vector of bytes._  |
|  bool | [**operator!=**](#function-operator) (const [**PathT**](classSR__HTYPES__NS_1_1PathT.md)&lt; HASH\_SIZE, HASH\_FUNCTION &gt; & other) <br>_Inequality operator for paths._  |
|  bool | [**operator==**](#function-operator_1) (const [**PathT**](classSR__HTYPES__NS_1_1PathT.md)&lt; HASH\_SIZE, HASH\_FUNCTION &gt; & other) const<br>_Equality operator for paths._  |
|  const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; & | [**operator[]**](#function-operator_2) (size\_t i) const<br>_Operator to extract the hash of a given path element._  |
|  std::shared\_ptr&lt; [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; &gt; | [**root**](#function-root) () const<br>_Computes the root at the end of the path._  |
|  void | [**serialise**](#function-serialise) (std::vector&lt; uint8\_t &gt; & bytes) const<br>_Serialises a path._  |
|  size\_t | [**serialised\_size**](#function-serialised_size) () const<br>_The size of the serialised path in number of bytes._  |
|  size\_t | [**size**](#function-size) () const<br>_The number of elements on the path._  |
|  std::string | [**to\_string**](#function-to_string) (size\_t num\_bytes=HASH\_SIZE, bool lower\_case=true) const<br>_Convert a path to a string._  |
|  bool | [**verify**](#function-verify) (const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; & expected\_root) const<br>_Verifies that the root at the end of the path is expected._  |








## Protected Attributes

| Type | Name |
| ---: | :--- |
|  [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; | [**\_leaf**](#variable-_leaf)  <br>_The leaf hash._  |
|  size\_t | [**\_leaf\_index**](#variable-_leaf_index)  <br>_The index of the leaf._  |
|  size\_t | [**\_max\_index**](#variable-_max_index)  <br>_The maximum leaf index of the tree at the time of path extraction._  |
|  std::list&lt; [**Element**](structSR__HTYPES__NS_1_1PathT_1_1Element.md) &gt; | [**elements**](#variable-elements)  <br>_The elements of the path._  |




















## Detailed Description




**Template parameters:**


* `HASH_SIZE` Size of each hash in number of bytes 
* `HASH_FUNCTION` The hash function 




    
## Public Types Documentation




### enum Direction 

_MerklePath direction._ 
```C++
enum SR_HTYPES_NS::PathT::Direction {
    PATH_LEFT,
    PATH_RIGHT
};
```




<hr>



### typedef const\_iterator 

_Iterator for path elements._ 
```C++
typedef std::list<Element>::const_iterator SR_HTYPES_NS::PathT< HASH_SIZE, HASH_FUNCTION >::const_iterator;
```




<hr>
## Public Functions Documentation




### function PathT [1/5]

_MerklePath constructor._ 
```C++
inline SR_HTYPES_NS::PathT::PathT (
    const HashT < HASH_SIZE > & leaf,
    size_t leaf_index,
    std::list< Element > && elements,
    size_t max_index
) 
```





**Parameters:**


* `leaf` 
* `leaf_index` 
* `elements` 
* `max_index` 




        

<hr>



### function PathT [2/5]

_MerklePath copy constructor._ 
```C++
inline SR_HTYPES_NS::PathT::PathT (
    const PathT & other
) 
```





**Parameters:**


* `other` MerklePath to copy 




        

<hr>



### function PathT [3/5]

_MerklePath move constructor._ 
```C++
inline SR_HTYPES_NS::PathT::PathT (
    PathT && other
) 
```





**Parameters:**


* `other` MerklePath to move 




        

<hr>



### function PathT [4/5]

_Deserialises a path._ 
```C++
inline SR_HTYPES_NS::PathT::PathT (
    const std::vector< uint8_t > & bytes
) 
```





**Parameters:**


* `bytes` Vector to deserialise from 




        

<hr>



### function PathT [5/5]

_Deserialises a path._ 
```C++
inline SR_HTYPES_NS::PathT::PathT (
    const std::vector< uint8_t > & bytes,
    size_t & position
) 
```





**Parameters:**


* `bytes` Vector to deserialise from 
* `position` Position of the first byte in `bytes` 




        

<hr>



### function begin 

_Start iterator for path elements._ 
```C++
inline const_iterator SR_HTYPES_NS::PathT::begin () const
```




<hr>



### function deserialise [1/2]

_Deserialises a path._ 
```C++
inline void SR_HTYPES_NS::PathT::deserialise (
    const std::vector< uint8_t > & bytes,
    size_t & position
) 
```





**Parameters:**


* `bytes` Vector of bytes to serialise from 
* `position` Position of the first byte in `bytes` 




        

<hr>



### function deserialise [2/2]

_Deserialises a path._ 
```C++
inline void SR_HTYPES_NS::PathT::deserialise (
    const std::vector< uint8_t > & bytes
) 
```





**Parameters:**


* `bytes` Vector of bytes to serialise from 




        

<hr>



### function end 

_End iterator for path elements._ 
```C++
inline const_iterator SR_HTYPES_NS::PathT::end () const
```




<hr>



### function leaf 

_The leaf hash of the path._ 
```C++
inline const HashT < HASH_SIZE > & SR_HTYPES_NS::PathT::leaf () const
```




<hr>



### function leaf\_index 

_Index of the leaf of the path._ 
```C++
inline size_t SR_HTYPES_NS::PathT::leaf_index () const
```




<hr>



### function max\_index 

_Maximum index of the tree at the time the path was extracted._ 
```C++
inline size_t SR_HTYPES_NS::PathT::max_index () const
```




<hr>



### function vector&lt; uint8\_t &gt; 

_Conversion operator to vector of bytes._ 
```C++
inline SR_HTYPES_NS::PathT::vector< uint8_t > () const
```




<hr>



### function operator!= 

_Inequality operator for paths._ 
```C++
inline bool SR_HTYPES_NS::PathT::operator!= (
    const PathT < HASH_SIZE, HASH_FUNCTION > & other
) 
```




<hr>



### function operator== 

_Equality operator for paths._ 
```C++
inline bool SR_HTYPES_NS::PathT::operator== (
    const PathT < HASH_SIZE, HASH_FUNCTION > & other
) const
```




<hr>



### function operator[] 

_Operator to extract the hash of a given path element._ 
```C++
inline const HashT < HASH_SIZE > & SR_HTYPES_NS::PathT::operator[] (
    size_t i
) const
```





**Parameters:**


* `i` Index of the path element 




        

<hr>



### function root 

_Computes the root at the end of the path._ 
```C++
inline std::shared_ptr< HashT < HASH_SIZE > > SR_HTYPES_NS::PathT::root () const
```





**Note:**

This (re-)computes the root by hashing the path elements, it does not return a previously saved root hash. 





        

<hr>



### function serialise 

_Serialises a path._ 
```C++
inline void SR_HTYPES_NS::PathT::serialise (
    std::vector< uint8_t > & bytes
) const
```





**Parameters:**


* `bytes` Vector of bytes to serialise to 




        

<hr>



### function serialised\_size 

_The size of the serialised path in number of bytes._ 
```C++
inline size_t SR_HTYPES_NS::PathT::serialised_size () const
```




<hr>



### function size 

_The number of elements on the path._ 
```C++
inline size_t SR_HTYPES_NS::PathT::size () const
```




<hr>



### function to\_string 

_Convert a path to a string._ 
```C++
inline std::string SR_HTYPES_NS::PathT::to_string (
    size_t num_bytes=HASH_SIZE,
    bool lower_case=true
) const
```





**Parameters:**


* `num_bytes` The maximum number of bytes to convert 
* `lower_case` Enables lower-case hex characters 




        

<hr>



### function verify 

_Verifies that the root at the end of the path is expected._ 
```C++
inline bool SR_HTYPES_NS::PathT::verify (
    const HashT < HASH_SIZE > & expected_root
) const
```





**Parameters:**


* `expected_root` The root hash that the elements on the path are expected to hash to. 




        

<hr>
## Protected Attributes Documentation




### variable \_leaf 

_The leaf hash._ 
```C++
HashT<HASH_SIZE> SR_HTYPES_NS::PathT< HASH_SIZE, HASH_FUNCTION >::_leaf;
```




<hr>



### variable \_leaf\_index 

_The index of the leaf._ 
```C++
size_t SR_HTYPES_NS::PathT< HASH_SIZE, HASH_FUNCTION >::_leaf_index;
```




<hr>



### variable \_max\_index 

_The maximum leaf index of the tree at the time of path extraction._ 
```C++
size_t SR_HTYPES_NS::PathT< HASH_SIZE, HASH_FUNCTION >::_max_index;
```




<hr>



### variable elements 

_The elements of the path._ 
```C++
std::list<Element> SR_HTYPES_NS::PathT< HASH_SIZE, HASH_FUNCTION >::elements;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/MerkleTree.h`

