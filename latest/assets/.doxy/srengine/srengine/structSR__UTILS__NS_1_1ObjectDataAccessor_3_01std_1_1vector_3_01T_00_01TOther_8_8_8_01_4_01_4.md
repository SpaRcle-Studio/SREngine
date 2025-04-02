

# Struct SR\_UTILS\_NS::ObjectDataAccessor&lt; std::vector&lt; T, TOther... &gt; &gt;

**template &lt;typename T, class... TOther&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ObjectDataAccessor&lt; std::vector&lt; T, TOther... &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1vector_3_01T_00_01TOther_8_8_8_01_4_01_4.md)








Inherits the following classes: [SR\_UTILS\_NS::ObjectDataAccessorVector](structSR__UTILS__NS_1_1ObjectDataAccessorVector.md)


























































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &, T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |
|  void | [**Save**](#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &, const T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |


## Public Static Functions inherited from SR_UTILS_NS::ObjectDataAccessorVector

See [SR\_UTILS\_NS::ObjectDataAccessorVector](structSR__UTILS__NS_1_1ObjectDataAccessorVector.md)

| Type | Name |
| ---: | :--- |
|  void | [**Load**](structSR__UTILS__NS_1_1ObjectDataAccessorVector.md#function-load) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, T & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Save**](structSR__UTILS__NS_1_1ObjectDataAccessorVector.md#function-save) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const T & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |


















































## Public Static Functions Documentation




### function Load 

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::vector< T, TOther... > >::Load (
    IDeserializer &,
    T &,
    const SerializationId &
) 
```




<hr>



### function Save 

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::vector< T, TOther... > >::Save (
    ISerializer &,
    const T &,
    const SerializationId &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

