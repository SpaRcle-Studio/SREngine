

# Struct SR\_HTYPES\_NS::PathT::Element



[**ClassList**](annotated.md) **>** [**SR\_HTYPES\_NS**](namespaceSR__HTYPES__NS.md) **>** [**PathT**](classSR__HTYPES__NS_1_1PathT.md) **>** [**Element**](structSR__HTYPES__NS_1_1PathT_1_1Element.md)



_MerklePath element._ 

* `#include <MerkleTree.h>`





















## Public Attributes

| Type | Name |
| ---: | :--- |
|  [**Direction**](classSR__HTYPES__NS_1_1PathT.md#enum-direction) | [**direction**](#variable-direction)  <br>_The direction at which_ `hash` _joins at this path element._ |
|  [**HashT**](structSR__HTYPES__NS_1_1HashT.md)&lt; HASH\_SIZE &gt; | [**hash**](#variable-hash)  <br>_The hash of the path element._  |












































## Public Attributes Documentation




### variable direction 

_The direction at which_ `hash` _joins at this path element._
```C++
Direction SR_HTYPES_NS::PathT< HASH_SIZE, HASH_FUNCTION >::Element::direction;
```





**Note:**

If `direction` == PATH\_LEFT, `hash` joins at the left, i.e. if t is the current hash, e.g. a leaf, then t' = MerkleHash( `hash`, t ); 





        

<hr>



### variable hash 

_The hash of the path element._ 
```C++
HashT<HASH_SIZE> SR_HTYPES_NS::PathT< HASH_SIZE, HASH_FUNCTION >::Element::hash;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Types/MerkleTree.h`

