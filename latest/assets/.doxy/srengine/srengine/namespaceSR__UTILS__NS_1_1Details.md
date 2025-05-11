

# Namespace SR\_UTILS\_NS::Details



[**Namespace List**](namespaces.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**Details**](namespaceSR__UTILS__NS_1_1Details.md)




















## Classes

| Type | Name |
| ---: | :--- |
| class | [**AtomFormatter**](classSR__UTILS__NS_1_1Details_1_1AtomFormatter.md) <br> |
| class | [**Formatter**](classSR__UTILS__NS_1_1Details_1_1Formatter.md) <br> |


## Public Types

| Type | Name |
| ---: | :--- |
| typedef typename [**DefaultChecker**](structSR__UTILS__NS_1_1DefaultChecker.md)&lt; T &gt;::IsAlwaysFalse | [**IsDefaultCheckerAlwaysFalseT**](#typedef-isdefaultcheckeralwaysfalset)  <br> |
| typedef decltype(std::declval&lt; T &gt;().reserve(size\_t())) | [**ReserveMethodT**](#typedef-reservemethodt)  <br> |
















































## Public Types Documentation




### typedef IsDefaultCheckerAlwaysFalseT 

```C++
using SR_UTILS_NS::Details::IsDefaultCheckerAlwaysFalseT = typedef typename DefaultChecker<T>::IsAlwaysFalse;
```




<hr>



### typedef ReserveMethodT 

```C++
using SR_UTILS_NS::Details::ReserveMethodT = typedef decltype(std::declval<T>().reserve(size_t()));
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Common/StringAtomLiterals.h`

