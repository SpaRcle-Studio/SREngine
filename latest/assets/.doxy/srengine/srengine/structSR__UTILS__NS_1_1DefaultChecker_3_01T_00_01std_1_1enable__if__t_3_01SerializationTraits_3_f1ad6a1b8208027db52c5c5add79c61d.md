

# Struct SR\_UTILS\_NS::DefaultChecker&lt; T, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::HasEmpty &&!IsTypeFromStdArrayTemplateV&lt; T &gt; &gt; &gt;

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**DefaultChecker&lt; T, std::enable\_if\_t&lt; SerializationTraits&lt; T &gt;::HasEmpty &&!IsTypeFromStdArrayTemplateV&lt; T &gt; &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01T_00_01std_1_1enable__if__t_3_01SerializationTraits_3_f1ad6a1b8208027db52c5c5add79c61d.md)



_Specialization for types with "empty" method (std::vector, std::string, std::array, etc...)_ 

* `#include <Serialization.h>`

















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::true\_type | [**IsAlwaysFalse**](#typedef-isalwaysfalse)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**IsDefault**](#function-isdefault-12) (const T & value) <br> |
|  bool | [**IsDefault**](#function-isdefault-22) (const T &) <br> |


























## Public Types Documentation




### typedef IsAlwaysFalse 

```C++
using SR_UTILS_NS::DefaultChecker< T, std::enable_if_t< SerializationTraits< T >::HasEmpty &&!IsTypeFromStdArrayTemplateV< T > > >::IsAlwaysFalse = ;
```




<hr>
## Public Static Functions Documentation




### function IsDefault [1/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< T, std::enable_if_t< SerializationTraits< T >::HasEmpty &&!IsTypeFromStdArrayTemplateV< T > > >::IsDefault (
    const T & value
) 
```




<hr>



### function IsDefault [2/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< T, std::enable_if_t< SerializationTraits< T >::HasEmpty &&!IsTypeFromStdArrayTemplateV< T > > >::IsDefault (
    const T &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/DefaultCheckers.inl.h`

