

# Struct SR\_UTILS\_NS::ObjectDataAccessor&lt; std::set&lt; T, Less, Allocator &gt; &gt;

**template &lt;typename T, typename Less, typename Allocator&gt;**



[**ClassList**](annotated.md) **>** [**SR\_UTILS\_NS**](namespaceSR__UTILS__NS.md) **>** [**ObjectDataAccessor&lt; std::set&lt; T, Less, Allocator &gt; &gt;**](structSR__UTILS__NS_1_1ObjectDataAccessor_3_01std_1_1set_3_01T_00_01Less_00_01Allocator_01_4_01_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::set&lt; T, Less, Allocator &gt; | [**SetType**](#typedef-settype)  <br> |
| typedef typename SetType::value\_type | [**ValueType**](#typedef-valuetype)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load-12) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) & deserializer, SetT & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Load**](#function-load-22) ([**IDeserializer**](classSR__UTILS__NS_1_1IDeserializer.md) &, T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |
|  void | [**Save**](#function-save-12) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) & serializer, const SetType & value, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) & id) <br> |
|  void | [**Save**](#function-save-22) ([**ISerializer**](classSR__UTILS__NS_1_1ISerializer.md) &, const T &, const [**SerializationId**](structSR__UTILS__NS_1_1SerializationId.md) &) <br> |


























## Public Types Documentation




### typedef SetType 

```C++
using SR_UTILS_NS::ObjectDataAccessor< std::set< T, Less, Allocator > >::SetType =  std::set<T, Less, Allocator>;
```




<hr>



### typedef ValueType 

```C++
using SR_UTILS_NS::ObjectDataAccessor< std::set< T, Less, Allocator > >::ValueType =  typename SetType::value_type;
```




<hr>
## Public Static Functions Documentation




### function Load [1/2]

```C++
template<typename SetT>
static inline void SR_UTILS_NS::ObjectDataAccessor< std::set< T, Less, Allocator > >::Load (
    IDeserializer & deserializer,
    SetT & value,
    const SerializationId & id
) 
```




<hr>



### function Load [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::set< T, Less, Allocator > >::Load (
    IDeserializer &,
    T &,
    const SerializationId &
) 
```




<hr>



### function Save [1/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::set< T, Less, Allocator > >::Save (
    ISerializer & serializer,
    const SetType & value,
    const SerializationId & id
) 
```




<hr>



### function Save [2/2]

```C++
static inline void SR_UTILS_NS::ObjectDataAccessor< std::set< T, Less, Allocator > >::Save (
    ISerializer &,
    const T &,
    const SerializationId &
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/Core/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

