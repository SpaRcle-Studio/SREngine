

# Struct ObjectDataAccessor&lt; std::map&lt; T, U, Compare, Allocator &gt; &gt;

**template &lt;typename T, typename U, typename Compare, typename Allocator&gt;**



[**ClassList**](annotated.md) **>** [**ObjectDataAccessor&lt; std::map&lt; T, U, Compare, Allocator &gt; &gt;**](structObjectDataAccessor_3_01std_1_1map_3_01T_00_01U_00_01Compare_00_01Allocator_01_4_01_4.md)






















## Public Types

| Type | Name |
| ---: | :--- |
| typedef std::map&lt; T, U, Compare, Allocator &gt; | [**MapType**](#typedef-maptype)  <br> |
| typedef typename MapType::value\_type | [**ValueType**](#typedef-valuetype)  <br> |






















## Public Static Functions

| Type | Name |
| ---: | :--- |
|  void | [**Load**](#function-load) (IDeserializer & deserializer, MapT & value, const SerializationId & id) <br> |
|  void | [**Save**](#function-save) (ISerializer & serializer, const MapType & value, const SerializationId & id) <br> |


























## Public Types Documentation




### typedef MapType 

```C++
using ObjectDataAccessor< std::map< T, U, Compare, Allocator > >::MapType =  std::map<T, U, Compare, Allocator>;
```




<hr>



### typedef ValueType 

```C++
using ObjectDataAccessor< std::map< T, U, Compare, Allocator > >::ValueType =  typename MapType::value_type;
```




<hr>
## Public Static Functions Documentation




### function Load 

```C++
template<typename MapT>
static inline void ObjectDataAccessor< std::map< T, U, Compare, Allocator > >::Load (
    IDeserializer & deserializer,
    MapT & value,
    const SerializationId & id
) 
```




<hr>



### function Save 

```C++
static inline void ObjectDataAccessor< std::map< T, U, Compare, Allocator > >::Save (
    ISerializer & serializer,
    const MapType & value,
    const SerializationId & id
) 
```




<hr>

------------------------------
The documentation for this class was generated from the following file `Engine/libs/Utils/inc/Utils/Serialization/ObjectDataAccessors.inl.h`

