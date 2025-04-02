

# Struct SR\_HTYPES\_NS::TreeT::InsertionStackElement



[**ClassList**](annotated.md) **>** [**InsertionStackElement**](structSR__HTYPES__NS_1_1TreeT_1_1InsertionStackElement.md)



_The structure of elements on the insertion stack._ 






















## Public Attributes

| Type | Name |
| ---: | :--- |
|  bool | [**left**](#variable-left)  <br>_Flag to indicate whether_ `n` _should be inserted into the left or the right subtree of the current position in the tree._ |
|  [**Node**](structSR__HTYPES__NS_1_1TreeT_1_1Node.md) \* | [**n**](#variable-n)  <br>_The tree node to insert._  |












































## Public Attributes Documentation




### variable left 

_Flag to indicate whether_ `n` _should be inserted into the left or the right subtree of the current position in the tree._
```C++
bool SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::InsertionStackElement::left;
```




<hr>



### variable n 

_The tree node to insert._ 
```C++
Node* SR_HTYPES_NS::TreeT< HASH_SIZE, HASH_FUNCTION >::InsertionStackElement::n;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Types/MerkleTree.h`

