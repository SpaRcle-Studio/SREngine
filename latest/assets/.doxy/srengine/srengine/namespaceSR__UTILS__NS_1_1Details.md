

# Namespace SR\_UTILS\_NS::Details



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Details**](namespaceSR__UTILS__NS_1_1Details.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**AtomFormatter**](classSR__UTILS__NS_1_1Details_1_1AtomFormatter.md) <br> |
| struct | [**Detector**](structSR__UTILS__NS_1_1Details_1_1Detector.md) &lt;class Default, class AlwaysVoid, Op, Args&gt;<br> |
| struct | [**Detector&lt; Default, std::void\_t&lt; Op&lt; Args... &gt; &gt;, Op, Args... &gt;**](structSR__UTILS__NS_1_1Details_1_1Detector_3_01Default_00_01std_1_1void__t_3_01Op_3_01Args_8_8_86bb0dd47b703eedb0ac0acb502b0839c.md) &lt;class Default, Op, Args&gt;<br> |
| struct | [**Empty**](structSR__UTILS__NS_1_1Details_1_1Empty.md) <br> |
| class | [**Formatter**](classSR__UTILS__NS_1_1Details_1_1Formatter.md) <br> |
| struct | [**GetPromPack**](structSR__UTILS__NS_1_1Details_1_1GetPromPack.md) &lt;I, class T, Types&gt;<br> |
| struct | [**GetPromPack&lt; 0, T, Types... &gt;**](structSR__UTILS__NS_1_1Details_1_1GetPromPack_3_010_00_01T_00_01Types_8_8_8_01_4.md) &lt;class T, Types&gt;<br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename [**DefaultChecker**](structSR__UTILS__NS_1_1DefaultChecker.md)&lt; T &gt;::IsAlwaysFalse | [**IsDefaultCheckerAlwaysFalseT**](#typedef-isdefaultcheckeralwaysfalset)  <br> |
| typedef decltype(std::declval&lt; T &gt;().reserve(size\_t())) | [**ReserveMethodT**](#typedef-reservemethodt)  <br> |




















## Public Functions

| Type | Name |
| ---: | :--- |
|  auto | [**GetFromPackResolver**](#function-getfrompackresolver) () <br> |




























## Public Types Documentation




### typedef IsDefaultCheckerAlwaysFalseT 

```C++
using SR_UTILS_NS::Details::IsDefaultCheckerAlwaysFalseT =  typename DefaultChecker<T>::IsAlwaysFalse;
```




<hr>



### typedef ReserveMethodT 

```C++
using SR_UTILS_NS::Details::ReserveMethodT =  decltype(std::declval<T>().reserve(size_t()));
```




<hr>
## Public Functions Documentation




### function GetFromPackResolver 

```C++
template<size_t Index, class... Types>
auto SR_UTILS_NS::Details::GetFromPackResolver () 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Common/StringAtomLiterals.h`

