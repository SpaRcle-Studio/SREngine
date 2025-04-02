

# Struct SR\_UTILS\_NS::ObjectDataAccessor&lt; std::array&lt; T, N &gt; &gt;

**template &lt;typename T, size\_t N&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ObjectDataAccessor&lt; std::array&lt; T, N &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1array_3_01T_00_01N_01_4_01_4.md)












































## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load-12) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, std::array&lt; T, N &gt; & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Load**](#function-load-22) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &, T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |
|  void | [**Save**](#function-save-12) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const std::array&lt; T, N &gt; & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Save**](#function-save-22) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &, const T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |


























## Public Static Functions Documentation




### function Load [1/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::array< T, N > >::Load (
    IDeserializer & deserializer,
    std::array< T, N > & value,
    const SerializationId & id
) 
```




<hr>



### function Load [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::array< T, N > >::Load (
    IDeserializer &,
    T &,
    const SerializationId &
) 
```




<hr>



### function Save [1/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::array< T, N > >::Save (
    ISerializer & serializer,
    const std::array< T, N > & value,
    const SerializationId & id
) 
```




<hr>



### function Save [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::array< T, N > >::Save (
    ISerializer &,
    const T &,
    const SerializationId &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

