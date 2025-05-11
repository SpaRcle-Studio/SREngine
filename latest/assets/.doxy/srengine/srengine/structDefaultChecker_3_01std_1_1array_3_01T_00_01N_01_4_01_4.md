

# Struct DefaultChecker&lt; std::array&lt; T, N &gt; &gt;

**template &lt;class T, size\_t N&gt;**



[**ClassList**](annotated.md) **>** [**DefaultChecker&lt; std::array&lt; T, N &gt; &gt;**](structDefaultChecker_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::bool\_constant&lt;(N &gt; 0)&gt; | [**IsAlwaysFalse**](#typedef-isalwaysfalse)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**IsDefault**](#function-isdefault) (const std::array&lt; T, N &gt; & value) <br> |


























## Public Types Documentation




### typedef IsAlwaysFalse 

```C++
using DefaultChecker< std::array< T, N > >::IsAlwaysFalse =  std::bool_constant<(N > 0)>;
```




<hr>
## Public Static Functions Documentation




### function IsDefault 

```C++
static inline constexpr bool DefaultChecker< std::array< T, N > >::IsDefault (
    const std::array< T, N > & value
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/DefaultCheckers.inl.h`

