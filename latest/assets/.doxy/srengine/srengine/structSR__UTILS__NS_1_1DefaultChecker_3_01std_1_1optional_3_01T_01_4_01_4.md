

# Struct SR\_UTILS\_NS::DefaultChecker&lt; std::optional&lt; T &gt; &gt;

**template &lt;class T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**DefaultChecker&lt; std::optional&lt; T &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01std_1_1optional_3_01T_01_4_01_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::true\_type | [**IsAlwaysFalse**](#typedef-isalwaysfalse)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**IsDefault**](#function-isdefault-12) (const std::optional&lt; T &gt; & value) <br> |
|  bool | [**IsDefault**](#function-isdefault-22) (const T &) <br> |


























## Public Types Documentation




### typedef IsAlwaysFalse 

```C++
using SR_UTILS_NS::DefaultChecker< T, void >::IsAlwaysFalse = ;
```




<hr>
## Public Static Functions Documentation




### function IsDefault [1/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< std::optional< T > >::IsDefault (
    const std::optional< T > & value
) 
```




<hr>



### function IsDefault [2/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< std::optional< T > >::IsDefault (
    const T &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/DefaultCheckers.inl.h`

