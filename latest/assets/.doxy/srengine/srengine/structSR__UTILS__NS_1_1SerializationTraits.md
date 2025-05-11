

# Struct SR\_UTILS\_NS::SerializationTraits

**template &lt;typename T&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**SerializationTraits**](structSR__UTILS__NS_1_1SerializationTraits.md)




























## Public Static Attributes

| Type | Name |
| ---: | :--- |
|  constexpr bool | [**HasEmpty**](#variable-hasempty)   = `IsDetectedV&lt;HasMethodEmptyT, T&gt;`<br> |
|  constexpr bool | [**IsSerializable**](#variable-isserializable)   = `std::is\_base\_of\_v&lt;[**SR\_UTILS\_NS::Serializable**](classSR__UTILS__NS_1_1Serializable.md), T&gt;`<br> |










































## Public Static Attributes Documentation




### variable HasEmpty 

```C++
constexpr bool SR_UTILS_NS::SerializationTraits< T >::HasEmpty;
```




<hr>



### variable IsSerializable 

```C++
constexpr bool SR_UTILS_NS::SerializationTraits< T >::IsSerializable;
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/Serialization.h`

