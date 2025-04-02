

# Struct SR\_HTYPES\_NS::HashT

**template &lt;size\_t SIZE&gt;**



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**HashT**](structSR__HTYPES__NS_1_1HashT.md)



_Template for fixed-size hashes._ [More...](#detailed-description)

* `#include <MerkleTree.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  uint8\_t | [**bytes**](#variable-bytes)  <br>_Holds the hash bytes._  |
















## Public Functions

| Type | Name |
| ---: | :--- |
|   | [**HashT**](#function-hasht-16) () <br>_Constructs a MerkleHash with all bytes set to zero._  |
|   | [**HashT**](#function-hasht-26) (const uint8\_t \* bytes) <br>_Constructs a MerkleHash from a byte buffer._  |
|   | [**HashT**](#function-hasht-36) (const std::string & s) <br>_Constructs a MerkleHash from a string._  |
|   | [**HashT**](#function-hasht-46) (const std::vector&lt; uint8\_t &gt; & bytes) <br>_Deserialises a MerkleHash from a vector of bytes._  |
|   | [**HashT**](#function-hasht-56) (const std::vector&lt; uint8\_t &gt; & bytes, size\_t & position) <br>_Deserialises a MerkleHash from a vector of bytes._  |
|   | [**HashT**](#function-hasht-66) (const std::array&lt; uint8\_t, SIZE &gt; & bytes) <br>_Deserialises a MerkleHash from an array of bytes._  |
|  void | [**deserialise**](#function-deserialise-12) (const std::vector&lt; uint8\_t &gt; & buffer, size\_t & position) <br>_Deserialises a hash._  |
|  void | [**deserialise**](#function-deserialise-22) (const std::vector&lt; uint8\_t &gt; & buffer) <br>_Deserialises a hash._  |
|   | [**vector&lt; uint8\_t &gt;**](#function-vector<-uint8_t->) () const<br>_Conversion operator to vector of bytes._  |
|  bool | [**operator!=**](#function-operator) (const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; SIZE &gt; & other) const<br>_MerkleHash inequality operator._  |
|  [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; SIZE &gt; | [**operator=**](#function-operator_1) (const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; SIZE &gt; & other) <br>_MerkleHash assignment operator._  |
|  bool | [**operator==**](#function-operator_2) (const [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; SIZE &gt; & other) const<br>_MerkleHash equality operator._  |
|  bool | [**operator==**](#function-operator_3) (const std::string & rawHash) const<br> |
|  void | [**serialise**](#function-serialise) (std::vector&lt; uint8\_t &gt; & buffer) const<br>_Serialises a hash._  |
|  size\_t | [**serialised\_size**](#function-serialised_size) () const<br>_The size of the serialisation of the hash (in number of bytes)_  |
|  size\_t | [**size**](#function-size) () const<br>_The size of the hash (in number of bytes)_  |
|  std::string | [**to\_string**](#function-to_string) (size\_t num\_bytes=SIZE, bool lower\_case=true) const<br>_Convert a hash to a hex-encoded string._  |
|  void | [**zero**](#function-zero) () <br>_zeros out all bytes in the hash_  |




























## Detailed Description




**Template parameters:**


* `SIZE` Size of the hash in number of bytes 




    
## Public Attributes Documentation




### variable bytes 

_Holds the hash bytes._ 
```C++
uint8_t SR_HTYPES_NS::HashT< SIZE >::bytes[SIZE];
```




<hr>
## Public Functions Documentation




### function HashT [1/6]

_Constructs a MerkleHash with all bytes set to zero._ 
```C++
inline SR_HTYPES_NS::HashT::HashT () 
```




<hr>



### function HashT [2/6]

_Constructs a MerkleHash from a byte buffer._ 
```C++
inline SR_HTYPES_NS::HashT::HashT (
    const uint8_t * bytes
) 
```





**Parameters:**


* `bytes` Buffer with hash value 




        

<hr>



### function HashT [3/6]

_Constructs a MerkleHash from a string._ 
```C++
inline SR_HTYPES_NS::HashT::HashT (
    const std::string & s
) 
```





**Parameters:**


* `s` String to read the hash value from 




        

<hr>



### function HashT [4/6]

_Deserialises a MerkleHash from a vector of bytes._ 
```C++
inline SR_HTYPES_NS::HashT::HashT (
    const std::vector< uint8_t > & bytes
) 
```





**Parameters:**


* `bytes` Vector to read the hash value from 




        

<hr>



### function HashT [5/6]

_Deserialises a MerkleHash from a vector of bytes._ 
```C++
inline SR_HTYPES_NS::HashT::HashT (
    const std::vector< uint8_t > & bytes,
    size_t & position
) 
```





**Parameters:**


* `bytes` Vector to read the hash value from 
* `position` Position of the first byte in `bytes` 




        

<hr>



### function HashT [6/6]

_Deserialises a MerkleHash from an array of bytes._ 
```C++
inline SR_HTYPES_NS::HashT::HashT (
    const std::array< uint8_t, SIZE > & bytes
) 
```





**Parameters:**


* `bytes` Array to read the hash value from 




        

<hr>



### function deserialise [1/2]

_Deserialises a hash._ 
```C++
inline void SR_HTYPES_NS::HashT::deserialise (
    const std::vector< uint8_t > & buffer,
    size_t & position
) 
```





**Parameters:**


* `buffer` Buffer to read the hash from 
* `position` Position of the first byte in `bytes` 




        

<hr>



### function deserialise [2/2]

_Deserialises a hash._ 
```C++
inline void SR_HTYPES_NS::HashT::deserialise (
    const std::vector< uint8_t > & buffer
) 
```





**Parameters:**


* `buffer` Buffer to read the hash from 




        

<hr>



### function vector&lt; uint8\_t &gt; 

_Conversion operator to vector of bytes._ 
```C++
inline SR_HTYPES_NS::HashT::vector< uint8_t > () const
```




<hr>



### function operator!= 

_MerkleHash inequality operator._ 
```C++
inline bool SR_HTYPES_NS::HashT::operator!= (
    const HashT < SIZE > & other
) const
```




<hr>



### function operator= 

_MerkleHash assignment operator._ 
```C++
inline HashT < SIZE > SR_HTYPES_NS::HashT::operator= (
    const HashT < SIZE > & other
) 
```




<hr>



### function operator== 

_MerkleHash equality operator._ 
```C++
inline bool SR_HTYPES_NS::HashT::operator== (
    const HashT < SIZE > & other
) const
```




<hr>



### function operator== 

```C++
inline bool SR_HTYPES_NS::HashT::operator== (
    const std::string & rawHash
) const
```




<hr>



### function serialise 

_Serialises a hash._ 
```C++
inline void SR_HTYPES_NS::HashT::serialise (
    std::vector< uint8_t > & buffer
) const
```





**Parameters:**


* `buffer` Buffer to serialise to 




        

<hr>



### function serialised\_size 

_The size of the serialisation of the hash (in number of bytes)_ 
```C++
inline size_t SR_HTYPES_NS::HashT::serialised_size () const
```




<hr>



### function size 

_The size of the hash (in number of bytes)_ 
```C++
inline size_t SR_HTYPES_NS::HashT::size () const
```




<hr>



### function to\_string 

_Convert a hash to a hex-encoded string._ 
```C++
inline std::string SR_HTYPES_NS::HashT::to_string (
    size_t num_bytes=SIZE,
    bool lower_case=true
) const
```





**Parameters:**


* `num_bytes` The maximum number of bytes to convert 
* `lower_case` Enables lower-case hex characters 




        

<hr>



### function zero 

_zeros out all bytes in the hash_ 
```C++
inline void SR_HTYPES_NS::HashT::zero () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/MerkleTree.h`

