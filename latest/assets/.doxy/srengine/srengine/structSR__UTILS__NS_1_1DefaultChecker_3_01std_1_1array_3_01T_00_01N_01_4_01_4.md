

# Struct SR\_UTILS\_NS::DefaultChecker&lt; std::array&lt; T, N &gt; &gt;

**template &lt;class T, size\_t N&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**DefaultChecker&lt; std::array&lt; T, N &gt; &gt;**](structSR__UTILS__NS_1_1DefaultChecker_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::bool\_constant&lt;(N &gt; 0)&gt; | [**IsAlwaysFalse**](#typedef-isalwaysfalse-12)  <br> |
| typedef std::true\_type | [**IsAlwaysFalse**](#typedef-isalwaysfalse-22)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  bool | [**IsDefault**](#function-isdefault-12) (const std::array&lt; T, N &gt; & value) <br> |
|  bool | [**IsDefault**](#function-isdefault-22) (const T &) <br> |


























## Public Types Documentation




### typedef IsAlwaysFalse [1/2]

```C++
using SR_UTILS_NS::DefaultChecker< std::array< T, N > >::IsAlwaysFalse =  std::bool_constant<(N > 0)>;
```




<hr>



### typedef IsAlwaysFalse [2/2]

```C++
using SR_UTILS_NS::DefaultChecker< T, void >::IsAlwaysFalse = ;
```




<hr>
## Public Static Functions Documentation




### function IsDefault [1/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< std::array< T, N > >::IsDefault (
    const std::array< T, N > & value
) 
```




<hr>



### function IsDefault [2/2]

```C++
static inline bool SR_UTILS_NS::DefaultChecker< std::array< T, N > >::IsDefault (
    const T &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/DefaultCheckers.inl.h`

