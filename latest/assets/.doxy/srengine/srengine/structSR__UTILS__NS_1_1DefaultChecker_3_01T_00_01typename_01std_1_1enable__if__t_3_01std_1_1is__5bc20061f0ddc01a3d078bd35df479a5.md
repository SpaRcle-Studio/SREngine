

# Struct SR\_UTILS\_NS::DefaultChecker&lt; T, typename std::enable\_if\_t&lt; std::is\_default\_constructible\_v&lt; T &gt; &&CheckOperatorUsableV&lt; CheckerEqualityComparable, T, T &gt; &&!SerializationTraits&lt; T &gt;::HasEmpty &&!std::is\_same\_v&lt; T, SR\_UTILS\_NS::StringAtom &gt; &gt; &gt;

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**DefaultChecker&lt; T, typename std::enable\_if\_t&lt; std::is\_default\_constructible\_v&lt; T &gt; &&CheckOperatorUsableV&lt; CheckerEqualityComparable, T, T &gt; &&!SerializationTraits&lt; T &gt;::HasEmpty &&!std::is\_same\_v&lt; T, SR\_UTILS\_NS::StringAtom &gt; &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01T_00_01typename_01std_1_1enable__if__t_3_01std_1_1is__5bc20061f0ddc01a3d078bd35df479a5.md)



_Default checkers for serialization._ 

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
using SR_UTILS_NS::DefaultChecker< T, typename std::enable_if_t< std::is_default_constructible_v< T > &&CheckOperatorUsableV< CheckerEqualityComparable, T, T > &&!SerializationTraits< T >::HasEmpty &&!std::is_same_v< T, SR_UTILS_NS::StringAtom > > >::IsAlwaysFalse = ;
```




<hr>
## Public Static Functions Documentation




### function IsDefault [1/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< T, typename std::enable_if_t< std::is_default_constructible_v< T > &&CheckOperatorUsableV< CheckerEqualityComparable, T, T > &&!SerializationTraits< T >::HasEmpty &&!std::is_same_v< T, SR_UTILS_NS::StringAtom > > >::IsDefault (
    const T & value
) 
```




<hr>



### function IsDefault [2/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< T, typename std::enable_if_t< std::is_default_constructible_v< T > &&CheckOperatorUsableV< CheckerEqualityComparable, T, T > &&!SerializationTraits< T >::HasEmpty &&!std::is_same_v< T, SR_UTILS_NS::StringAtom > > >::IsDefault (
    const T &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/DefaultCheckers.inl.h`

